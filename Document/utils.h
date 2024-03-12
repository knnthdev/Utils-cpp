#ifndef EasyStream_H
#define EasyStream_H
#include <iostream>
#include <cstdarg>
#include <sstream>
#include <string>
#include <execution>

namespace utils
{
  template <typename... Args>
  class Tuple;

  constexpr bool Contains(const std::string str, const std::string substr) noexcept
  {
    return str.find(substr) != std::string::npos;
  }

  template <typename... Args>
  std::string concat(const char *msg, Args &&...args) noexcept
  {
    Tuple tup = Tuple(args...);
    if (!tup.Length)
    {
      return std::string(msg);
    }
    std::stringstream ss, temp;
    const char *target = msg;
    size_t index = 0;
    bool open = false;
    while (*target != char())
    {
      if (*target == '{')
      {
        if (open && *target == '{')
        {
          open = false;
          goto output;
        }
        open = true; // open the journal;
        ++target;
        continue;
      }
      if (open)
      {
        if (std::isdigit(*target))
        {
          temp << *target++;
          continue;
        }
        else if (*target == '}')
        {
          open = false; // close the journal;
          // make conversion to integer;
          int number;
          temp >> number;
          // get argument and convert the argument in string;
          if (number < (int signed)tup.Length)
            ss << tup[number];
          // clean memory about temp varieble;
          temp.clear();
          ++target;
          continue;
        }
        else
        {
          target++;
          continue;
        }
      }
    output:
      ss << *(target++);
    }
    target = nullptr;
    return ss.str();
  }
  template <typename... Args>
  std::string concat(std::string &msg, Args &&...args) noexcept
  {
    return concat(msg.c_str(), args...);
  }
  template <typename type>
  std::pair<size_t, type *> filter(size_t count, type *obj, bool func(type &))
  {
    size_t rest = 0;
    type *result;
    for (size_t i = 0; i < count; i++)
    {
      if (func(obj[i]))
        result[rest++] = obj[i];
    }
    return {rest, result};
  }
  template <typename type>
  std::pair<size_t, type *> foreach (size_t count, type * obj, type func(type &))
  {
    type *target = new type[count];
    for (int i = 0; i < count; i++)
    {
      target[i] = func(obj[i]);
    }
    return {count, target};
  }
  template <typename type, typename _func_i_it>
  void foreach_action(size_t count, type *obj, _func_i_it action)
  {
    auto method = std::_Pass_fn(action);
    for (int i = 0; (int unsigned)i < count; i++)
    {
      method(i, obj[i]);
    }
  }
  template <typename type>
  type *map(size_t count, type *obj, type func(type &))
  {
    return foreach (count, obj, func).second;
  }
}

// statics
template <typename... Args>
int print(const char msg[], Args &&...args) noexcept
{
  // std::string cap = std::string(_msg);
  std::cout << utils::concat(msg, args...) << std::endl;
  return 0;
}
template <typename... Args>
int print(std::string &msg, Args &&...args) noexcept
{
  return print(msg.c_str(), args...);
}

template <typename... Args>
class utils::Tuple
{
private:
  int index = 0;

  using rubble = std::pair<std::stringstream, intptr_t>;
  
  rubble *_elements;

  template <typename return_type>
  return_type convertTo(rubble value)
  {
    return_type backout;
    value.first >> backout;
    return backout;
  };

  template <typename... args>
  void recursion() {}
  template <typename t, typename... args>
  void recursion(t first, args&&... rest)
  {
    rubble &element = _elements[index++];
    element.first << first;
    element.second = reinterpret_cast<intptr_t>(&first);

    recursion(rest...);
  }

public:
  __readonly size_t Length;
  Tuple(Args... args)
  {
    Length = sizeof...(args);
    if (Length)
    {
      _elements = new rubble[Length];
      recursion(args...);
    }
  }

  template <typename request>
  request GetArg(int i) const
  {
    if (Length ? i < (signed)Length : false){
      rubble &aux = _elements[i];
      if (typeid(request) == typeid(std::string))
        return aux.first.str();
      else if (typeid(request) == typeid(const char*))
        return (const char*)aux.first.str().c_str();
      else
        return *reinterpret_cast<request*>((intptr_t)aux.second);
    }
    throw std::range_error("out range of index");
  }
  std::string operator[](int _ind) const
  {
    return GetArg<std::string>(_ind);
  }
  template <typename typeof>
  bool Typeof(int ind) { return ind < Length ? sizeof(reinterpret_cast<typeof>(_elements[ind])) > 0 : false; }
  template <typename T>
  T ConverTo(int ind) { return ind < Length ? convertTo<T>(_elements[ind]) : *((T *)nullptr); }

  ~Tuple() { delete [] _elements; }

  friend std::ostream &operator<<(std::ostream &os, Tuple &tup)
  {
    os << "{ ";
    for (int i = 0; i < tup.Length; i++)
    {
      os << "(" << tup.Typeof(i) << "): " << tup[i] << (i != (tup.Length - 1) ? ", " : " ");
    }
    os << "}";
    return os;
  }
};
#endif