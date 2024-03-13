#include <iostream>
#include "belly.h"
#include <string>
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
    
    return print("size: {0}", list.size());
}