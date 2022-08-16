#include <iostream>
#include "ArraySequence.hpp"

int main() {
    auto array = new array_sequence<int>();
    array->push_back(100);
    array->push_back(101);
    array->push_back(102);

    std::cout << array->get_first() << " " << array->get_last();

    std::cout << std::endl;
    return 0;
}
