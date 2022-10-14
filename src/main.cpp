#include <iostream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Sorter.hpp"

int main() {
    auto array = new ListSequence<int>();

    // array->insert(0, 0);
    for (std::size_t i = 0; i < 200; ++i) {
        array->append(i);
        // std::cout << array->get_size() << '\n';
    }
    // array->erase(0);
    for (std::size_t i = 0; i < 200; ++i) {
        array->erase(0);
        // std::cout << array->get_size() << '\n';
    }


    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";

    std::cout << std::endl;
    delete array;
    return 0;
}
