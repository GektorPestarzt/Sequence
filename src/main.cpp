#include <iostream>
#include "ArraySequence.hpp"

int main() {
    // int data[1] = {1};
    auto array = new array_sequence<int>();
    // (*array)[0] = 0;

    for (int i = 1; i < 15; ++i) {
        array->push_back(i);
        // std::cout << array->get_size() << ' ';
    }

    for (int i = 0; i < 14; ++i) {
        std::cout << array->get(i) << '-';
    }

    return 0;
}
