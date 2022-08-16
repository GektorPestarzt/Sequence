#include <iostream>
#include "ArraySequence.hpp"

int main() {
    auto array = new array_sequence<int>();

    // array->insert(0, 0);
    for (std::size_t i = 0; i < 200; ++i) array->prepend(i);

    for (std::size_t i = 0; i < 200; ++i) array->erase(0);

    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";

    std::cout << std::endl;
    delete array;
    return 0;
}
