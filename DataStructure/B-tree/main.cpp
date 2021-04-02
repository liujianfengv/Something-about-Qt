#include <iostream>
#include "BTree.h"

int main()
{
    BTree t(3);
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    std::cout << "The B-tree is: ";
    t.traverse();
}
