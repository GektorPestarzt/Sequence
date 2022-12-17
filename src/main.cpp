#include <iostream>
#include <fstream>

#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Sorter.hpp"
#include "IClocking.hpp"

#include "progressbar.hpp"

#define ELEMENTS_MAX 10000
#define ELEMENTS_MIN 10
#define POINTS 15

bool int_cmpf(int a, int b) { return a > b; }

int list_sort() {
    auto array = new ListSequence<int>();

    for (std::size_t i = 0; i < 20; ++i) {
        array->append(rand() % 100);
    }

    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    // SorterList<int>::merge_sort_list(array, int_cmpf);
    SorterList<int>::qsort_list(array, int_cmpf);
    
    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;
    delete array;
    return 0;
}

int array_sort() {
    auto array = new ArraySequence<int>();

    for (std::size_t i = 0; i < 20; ++i) {
        array->push_back(rand() % 100);
    }

    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    Sorter<int>::merge_sort(array, int_cmpf);

    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    delete array;
    return 0;
}

int test_clocking() {
    auto array = new ArraySequence<int>();
    IClocking<ArraySequence<int>, int> clock;

    for (std::size_t i = 0; i < 100000; ++i) {
        array->append(1 + rand() % 100000);
    }
    
    double time = clock.sort_clocking_random_set(1000000, Sorter<int>::qsort, int_cmpf);
    std::cout << time << std::endl;
    time = clock.sort_clocking_random_set(10000, Sorter<int>::bubble_sort, int_cmpf);
    std::cout << time << std::endl;
    time = clock.sort_clocking_random_set(1000000, Sorter<int>::merge_sort, int_cmpf);
    std::cout << time << std::endl;
/*
    time = clock.sort_clocking(array, Sorter<int>::merge_sort, int_cmpf);
    std::cout << time.count() << std::endl;

    time = clock.sort_clocking(array, Sorter<int>::bubble_sort, int_cmpf);
    std::cout << time.count() << std::endl;
    
    time = clock.sort_clocking(array, Sorter<int>::shaker_sort, int_cmpf);
    std::cout << time.count() << std::endl;
*/
    return 0;
}

int test_clocking_list() {
    auto array = new ListSequence<int>();
    IClocking<ListSequence<int>, int> clock;

    for (std::size_t i = 0; i < 100000; ++i) {
        array->append(1 + rand() % 100000);
    }
    
    double time = clock.sort_clocking_random_set(100000, SorterList<int>::qsort_list, int_cmpf);
    std::cout << time << std::endl;
    time = clock.sort_clocking_random_set(100000, SorterList<int>::merge_sort_list, int_cmpf);
    std::cout << time << std::endl;
/*
    time = clock.sort_clocking(array, Sorter<int>::merge_sort, int_cmpf);
    std::cout << time.count() << std::endl;

    time = clock.sort_clocking(array, Sorter<int>::bubble_sort, int_cmpf);
    std::cout << time.count() << std::endl;
    
    time = clock.sort_clocking(array, Sorter<int>::shaker_sort, int_cmpf);
    std::cout << time.count() << std::endl;
*/
    return 0;
}

template<class Contain, typename T>
void push_to_file(const std::string& name, progressbar &bar, void sort(Contain*, bool(*)(T, T)), std::ofstream &out) {
    IClocking<Contain, T> clock;
    out << name << std::endl;

    for (std::size_t t = 0; t < POINTS; ++t) {
        std::size_t number = ELEMENTS_MIN + (ELEMENTS_MAX - ELEMENTS_MIN) * t / (POINTS - 1);
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, sort, int_cmpf);
        out << (int)(time * 10000) << "\n";

        bar.update();
    }
}

void file_clocking(progressbar &bar) {
    std::ofstream out;
    out.open("data/file1.txt");

    push_to_file<ArraySequence<int>, int>("ARRAY-QSORT", bar, Sorter<int>::qsort, out);
    push_to_file<ArraySequence<int>, int>("ARRAY-MERGE_SORT", bar, Sorter<int>::merge_sort, out);
    push_to_file<ArraySequence<int>, int>("ARRAY-BUBBLE_SORT", bar, Sorter<int>::bubble_sort, out);
    push_to_file<ArraySequence<int>, int>("ARRAY-SHAKER_SORT", bar, Sorter<int>::shaker_sort, out);

    out.close();
}

void file_clocking_list(progressbar &bar) {
    std::ofstream out;
    out.open("data/file2.txt");

    push_to_file<ListSequence<int>, int>("LIST-QSORT", bar, SorterList<int>::qsort_list, out);
    push_to_file<ListSequence<int>, int>("LIST-MERGE_SORT", bar, SorterList<int>::merge_sort_list, out);

    out.close();
}

int main() {
    std::ofstream out;
    out.open("data/options.txt");
    out << POINTS << "\n";
    out.close();

    progressbar bar(6 * POINTS);
    file_clocking(bar);
    file_clocking_list(bar);

    std::cout << std::endl;
    system("python3 main.py");

    return 0;
}
