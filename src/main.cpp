#include <iostream>
#include <fstream>

#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Sorter.hpp"
#include "IClocking.hpp"

#define ELEMENTS_MAX 10000
#define ELEMENTS_MIN 10
#define POINTS 5

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
        array->append(rand() % 100);
    }

    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    Sorter<int>::bubble_sort(array, int_cmpf);

    for (std::size_t i = 0; i < array->get_size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

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

void file_clocking(std::size_t min_elements, std::size_t max_elements, std::size_t points) {
    std::ofstream out;
    IClocking<ArraySequence<int>, int> clock;

    out.open("file1.txt");
    std::cout << "[      ]" << std::endl;

    out << "ARRAY-QSORT\n";
    for (std::size_t t = 0; t <= points; ++t) {
        std::size_t number = min_elements + (max_elements - min_elements) * t / points;
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, Sorter<int>::qsort, int_cmpf);
        out << (int)(time * 100) << "\n";
    }
    std::cout << "[-     ]" << std::endl;

    out << "ARRAY-MERGE_SORT\n";
    for (std::size_t t = 0; t <= points; ++t) {
        std::size_t number = min_elements + (max_elements - min_elements) * t / points;
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, Sorter<int>::merge_sort, int_cmpf);
        out << (int)(time * 100) << "\n";
    }
    std::cout << "[--    ]" << std::endl;

    out << "ARRAY-BUBBLE_SORT\n";
    for (std::size_t t = 0; t <= points; ++t) {
        std::size_t number = min_elements + (max_elements - min_elements) * t / points;
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, Sorter<int>::bubble_sort, int_cmpf);
        out << (int)(time * 100) << "\n";
    }
    std::cout << "[---   ]" << std::endl;

    out << "ARRAY-BUBBLE_SORT\n";
    for (std::size_t t = 0; t <= points; ++t) {
        std::size_t number = min_elements + (max_elements - min_elements) * t / points;
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, Sorter<int>::shaker_sort, int_cmpf);
        out << (int)(time * 100) << "\n";
    }
    std::cout << "[----  ]" << std::endl;

    out.close();
}

void file_clocking_list(std::size_t min_elements, std::size_t max_elements, std::size_t points) {
    std::ofstream out;
    IClocking<ListSequence<int>, int> clock;

    out.open("file2.txt");

    out << "LIST-QSORT\n";
    for (std::size_t t = 0; t <= points; ++t) {
        std::size_t number = min_elements + (max_elements - min_elements) * t / points;
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, SorterList<int>::qsort_list, int_cmpf);
        out << (int)(time * 100) << "\n";
    }
    std::cout << "[----- ]" << std::endl;

    out << "List-MERGE_SORT\n";
    for (std::size_t t = 0; t <= points; ++t) {
        std::size_t number = min_elements + (max_elements - min_elements) * t / points;
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, SorterList<int>::merge_sort_list, int_cmpf);
        out << (int)(time * 100) << "\n";
    }
    std::cout << "[------]" << std::endl;

    out.close();
}

int main() {
    // test_clocking();
    file_clocking(ELEMENTS_MIN, ELEMENTS_MAX, POINTS);
    file_clocking_list(ELEMENTS_MIN, ELEMENTS_MAX, POINTS);

    system("python3 main.py");
    // array_sort();
    // list_sort();
/*
    auto array = new ArraySequence<int>();

    for (std::size_t i = 0; i < 100; ++i) {
        array->append(i + 1);
    }

    for (ArraySequence<int>::iterator it = array->begin(); it != array->end(); ++it) {
        std::cout << (*it) << ' ';
    }
*/
    return 0;
}
