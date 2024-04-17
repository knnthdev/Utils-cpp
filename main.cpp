#include <iostream>
#include <string>
#include <belly.h>
using namespace std;

int main()
{
    Belly<int> list = {23, 42, 2, 452, 908, 28399, 654, 8};
    list.Print();
    list.Map<int>([](auto it) ->int {
        return it - 2;
    }).Filter([](auto it){
        return it % 2 == 0;
    }).Print();
    
    return print("size: {}", list.size());
}