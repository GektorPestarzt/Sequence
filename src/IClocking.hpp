#ifndef SRC_CLOCKING_HPP_
#define SRC_CLOCKING_HPP_

#include <chrono>
#include "Sorter.hpp"
#include "Sequence.hpp"

using namespace std::chrono;

template <class Contain, typename T>
class IClocking {
public:
    static duration<double> sort_clocking(Contain *array, void sort(Contain*, bool(*)(T, T)), bool (*cmpf)(T, T)) {
        auto start_clock = high_resolution_clock::now();
        sort(array, cmpf);

        auto stop_clock = high_resolution_clock::now();
        duration<double> duration = stop_clock - start_clock;

        return duration;
    }

    static duration<double> sort_clocking_random_set(std::size_t size, void sort(Contain*, bool(*)(T, T)), bool (*cmpf)(T, T)) {
        Contain *array = new Contain();

        for (std::size_t i = 0; i < size; ++i) {
            array->append(1 + rand() % size);
        }

        duration<double> duration = sort_clocking(array, sort, cmpf);
        return duration;
    }

    static duration<double> sort_clocking_sorted_set(std::size_t size, void sort(Contain*, bool(*)(T, T)), bool (*cmpf)(T, T)) {
        Contain *array = new Contain();

        for (std::size_t i = 1; i <= size; ++i) {
            array->append(i);
        }

        duration<double> duration = sort_clocking(array, sort, cmpf);
        return duration;
    }

    static duration<double> sort_clocking_reverse_set(std::size_t size, void sort(Contain*, bool(*)(T, T)), bool (*cmpf)(T, T)) {
        Contain *array = new Contain();

        for (std::size_t i = 0; i < size; ++i) {
            array->append(size - i);
        }

        duration<double> duration = sort_clocking(array, sort, cmpf);
        return duration;
    }

};

#endif  // SRC_CLOCKING_HPP_
