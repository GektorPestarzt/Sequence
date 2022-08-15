#include <iostream>
#include "ArraySequence.hpp"

int main() {
    int static_data[5] = {1, 2, 3, 4, 5};
    int *data = new int[5];
    std::copy(static_data, static_data + 5, data);

    auto array = new array_sequence<int>(data, 5);
    return 0;
}
