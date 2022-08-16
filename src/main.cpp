#include <iostream>
#include "ArraySequence.hpp"

int main() {
    auto array = new array_sequence<int>();

    for (int i = 0; i < 100; ++i) array->push_back(i);

    for (int i = 0; i < 100; ++i) {
        array->pop_back();
    }

    for (int i = 0; i < 100; ++i) array->push_back(i);

    std::cout << array->get_size() << " " << std::endl;

    array->prepend(-1);
    array->prepend(-2);
    array->prepend(-3);
    array->prepend(-4);

    std::cout << array->get_size() << std::endl;
    for (std::size_t i = 0; i < array->get_size(); ++i)
        std::cout << (*array)[i] << ' ';

    std::cout << std::endl;
    return 0;
}
