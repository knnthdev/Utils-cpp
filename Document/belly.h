#if !defined(Program_H)
#define Program_H
#include <iostream>
#include "utils.h"
#include <functional>
using namespace std;

#pragma warning(disable : 4200)


template <typename t>
class Belly;

#pragma region "BELLY"

template <class t>
class Belly
{
private:
    using self = Belly<t>;
    using t_ptr = t *;
    struct node
    {
        int id;
        t value;
        node *next = nullptr;
    };
    node *_first_node;
    node *_seq_nodes;
    int _size;
    int InstanceCode = NULL;
    void init()
    {
        InstanceCode = reinterpret_cast<intptr_t>(this);
        _seq_nodes = new node();
        _first_node = _seq_nodes;
        _size = 0;
    };
    bool _valid_index(int id)
    {
        return id < _size && id >= 0;
    }
    void _add_node(t &value)
    {
        if (InstanceCode)
        {
            if (!_size)
            {
                if (_first_node != _seq_nodes){
                    _seq_nodes = new node();
                    _first_node = _seq_nodes;
                }
                _first_node->id = _size++;
                _first_node->value = value;
                _first_node->next = nullptr;
                return;
            }
            node *aux = new node(); // the next element?
            aux->id = _size++;
            aux->value = value;
            aux->next = nullptr;
            _seq_nodes->next = aux;
            _seq_nodes = _seq_nodes->next;
        }
    }
    constexpr node *_get_node(int id) const
    {
        if (id >= (signed)_size)
        {
            throw range_error(utils::concat("the index {{{0}}} is outrange", id));
        }
        node *aux = _first_node; // id: 0
        while (aux->id != id)
        {
            aux = aux->next;
        }
        return aux;
    }
    t _get_node_value(int id)
    {
        return _get_node(id)->value;
    }
    void reballing(int pos, node *&start)
    {
        if (!_valid_index(pos))
            return;
        node *aux = start;
        while (aux != nullptr)
        {
            aux->id = pos++;
            aux = aux->next;
        }
    }
    int _delete_node(int index)
    {
        if (!_valid_index(index))
            return 0;
        if (!index)
        {
            auto aux = _first_node;
            _first_node = aux->next;
            delete aux;
            reballing(0, _first_node);
        }
        else if (index == _seq_nodes->id)
        {
            auto aux = _get_node(index - 1);
            _seq_nodes = aux;
            delete aux->next;
            aux->next = nullptr;
        }
        else
        {
            auto aux_p = _get_node(index - 1);
            auto aux_a = aux_p->next;
            auto aux_n = aux_a->next;
            aux_p->next = aux_n;
            reballing(aux_a->id, aux_n);
            delete aux_a;
        }
        --_size;
        return 1;
    }
    int _insert_node(int id, t &value)
    {
        if (!_valid_index(id))
            return 0;
        node *new_element = new node();
        new_element->value = value;
        if (!id)
        {
            auto aux = _first_node;
            _first_node = new_element;
            _first_node->next = aux;
            reballing(0, _first_node);
            ++_size;
        }
        else if (id == _seq_nodes->id)
        {
            _add_node(value);
        }
        else
        {
            auto aux_a = _get_node(id - 1);
            auto aux_n = aux_a->next;

            aux_a->next = new_element;
            new_element->next = aux_n;

            reballing(aux_n->id, new_element);
            ++_size;
        }
        return 1;
    }
    void _add_initializer_list(std::initializer_list<t> values)
    {
        if (!InstanceCode)
            init();
        const t *temp = values.begin();
        for (t i = *temp; temp != values.end(); i = *(++temp))
        {
            _add_node(i);
        }
        temp = nullptr;
    };
    template <typename func>
    void _for_each_node(func action_nodeptr)
    {
        auto cv = std::_Pass_fn(action_nodeptr);
        node *aux = _first_node;
        while (aux != nullptr)
        {
            auto next = aux->next;
            cv(aux);
            aux = next;
        }
    }
    void _clean_belly()
    {
        _for_each_node([this](node *&_node)
                       {
            delete _node;
            --this->_size; });
    }
    bool _copy_belly(self right) noexcept
    {
        if (this->InstanceCode != right.InstanceCode)
        {
            this->_clean_belly();
            right._for_each_node([this, right](node *&it)
                                 { this->_add_node(it->value); });
            return this->_size == right._size && this->_first_node->value == right._first_node->value && this->_seq_nodes->value == right._seq_nodes->value;
        }
        return false;
    }

public:
    Belly()
    {
        init();
    };
    Belly(int _size, t _array[])
    {
        init();
        for (int i = 0; i < _size; i++)
        {
            _add_node(_array[i]);
        }
    };
    Belly(std::initializer_list<t> values)
    {
        _add_initializer_list(values);
    };
    ~Belly()
    {
        if (_size)
            _clean_belly();
        _first_node = nullptr;
        _seq_nodes = nullptr;
    };
    //IEnumerator
    struct nodestream
    {
        node *ptr;
        operator t_ptr()
        {
            return &ptr->value;
        };
        nodestream &operator++()
        { // prefix
            this->ptr = this->ptr->next;
            return *this;
        };
        nodestream operator++(int)
        { // postfix
            nodestream aux{this->ptr};
            this->ptr = this->ptr->next;
            return aux;
        };
        nodestream &operator--()
        { // prefix
            this->ptr = _get_node(this->ptr->id - 1);
            return *this;
        };
        nodestream operator--(int)
        { // postfix
            nodestream aux{this->ptr};
            this->ptr = _get_node(this->ptr->id - 1);
            return aux;
        }
    };
    nodestream begin() const
    {
        return {_get_node(0)};
    }
    const nodestream end()
    {
        return {nullptr};
    }
    int size() const
    {
        return this->_size;
    }
    //basic implementation
    void Add(t &item) noexcept
    {
        _add_node(item);
    };
    void Add(const t item) noexcept
    {
        _add_node(item);
    };
    t At(int index)
    {
        return _get_node_value(index);
    };
    void Replace(int index, t value)
    {
        _get_node(index)->value = value;
    }
    bool Remove(int index)
    {
        return _delete_node(index);
    }
    bool Insert(t &value, int pos)
    {
        return _insert_node(pos, value);
    }
    bool Insert(const t value, int pos)
    {
        t ref = value;
        return _insert_node(pos, ref);
    }
    void Clean()
    {
        _clean_belly();
    }
    void Print()
    {
        try
        {
            auto aux = _get_node(0);
            while (aux != nullptr)
            {
                cout << aux->id << ": " << aux->value << endl;
                aux = aux->next;
            }
        }
        catch (const std::range_error &ex)
        {
            std::cerr << ex.what() << '\n';
        }
    };
    //API
    template <typename func>
    self &ForEach(func action_it)
    {
        auto cv = std::_Pass_fn(action_it);
        _for_each_node([=](node *it)
                       { cv(it->value); });
        return *(this);
    }
    template <typename tr>
    Belly<tr> Map(std::function<tr(t)> func_it_tr){
        Belly<tr> group;
        _for_each_node([&group, func_it_tr](node *it)
        { 
            auto result = func_it_tr(it->value);
            group._add_node(result);
        });
        return group;
    }
    template <typename predicated>
    self Filter(predicated func_it_bool){
        auto cv = std::_Pass_fn(func_it_bool);
        self group;
        _for_each_node([&group, cv](node *it)
                       { if (cv(it->value)) { group._add_node(it->value); } });
        return group;
    }

    //operators
    t operator[](int index) const
    {
        return this->At(index);
    }
    t &operator[](int index)
    {
        return _get_node(index)->value;
    }
    self &operator+=(std::initializer_list<t> data)
    {
        this->_add_initializer_list(data);
        return *this;
    };
    self &operator+=(t data)
    {
        this->_add_node(data);
        return *this;
    };

};

#pragma endregion

#endif