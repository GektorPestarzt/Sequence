#ifndef SRC_SORTER_HPP_
#define SRC_SORTER_HPP_

#include "ListSequence.hpp"

template <typename T>
class SorterList {

public:
    static void merge_sort_list(ListSequence<T>* list, bool (*cmpf)(T, T)) {
        list->set_head(merge_sort_list_recursive(list->get_head(), cmpf));
    }

    static void qsort_list(ListSequence<T>* list, bool (*cmpf)(T, T)) {
        list->set_head(qsort_list_recursive(list->get_head(), cmpf));
    }

private:
    static node<T>* merge_sort_list_recursive(node<T>* head, bool (*cmpf)(T, T)) { 
        if (!head || !head->next) {
            return head;
        }

        node<T> *first, *second;
        merge_sort_list_split(head, &first, &second);

        first = merge_sort_list_recursive(first, cmpf);
        second = merge_sort_list_recursive(second, cmpf);

        node<T> *result = merge_sort_list_merge(first, second, cmpf);
        
        return result;
    }

     static void merge_sort_list_split(node<T>* head, node<T>** first, node<T>** second) {
        node<T> *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *first = head;
        *second = slow->next;
        slow->next = nullptr;
    }

    static node<T>* merge_sort_list_merge(node<T>* first, node<T>* second, bool (*cmpf)(T, T)) {
        node<T>* result = nullptr;

        if (first && (!second || !cmpf(first->data, second->data))) {
            result = first;
            result->next = merge_sort_list_merge(first->next, second, cmpf);
        } else if (second && (!first || cmpf(first->data, second->data))) {
            result = second;
            result->next = merge_sort_list_merge(first, second->next, cmpf);
        }

        return result;
    }

// ----------------------------------- QUICK SORT LIST -----------------------------------

    static node<T>* qsort_list_recursive(node<T>* head, bool (*cmpf)(T, T)) {
        if (!head || !head->next) {
            return head;
        }

        node<T> *current = head;
        while (current->next) { current = current->next; }

        head = qsort_list_split(head, current, cmpf);

        node<T>* tmp;

        current->next = qsort_list_recursive(current->next, cmpf);
        if (head != current) {
            tmp = head;
            while (tmp->next != current) { tmp = tmp->next; }
            tmp->next = nullptr;

            head = qsort_list_recursive(head, cmpf);
   
            tmp = head;
            while (tmp->next) { tmp = tmp->next; }
            tmp->next = current;
        } else {
            head = current;
        }

        return head;
    }

    static node<T>* qsort_list_split(node<T>* head, node<T>* current, bool (*cmpf)(T, T)) {
        node<T>* tmp = head;
        node<T>* new_head = head;
        node<T>* prev = nullptr;
        node<T>* last = current;

        while (tmp != current) {
            if (cmpf(tmp->data, current->data)) {
                if (!prev) {
                    new_head = tmp->next;
                } else {
                    prev->next = tmp->next;
                }
                last->next = tmp;
                last = tmp;
                tmp = tmp->next;
                last->next = nullptr;
            } else {
                prev = tmp;
                tmp = tmp->next;
            }
        }

        return new_head;
    }
};

template<typename T>
class Sorter {
public:
    static void merge_sort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        merge_sort_recursive(array, 0, array->get_size() - 1, cmpf);
    }

    static void qsort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        qsort_recursive(array, 0, array->get_size() - 1, cmpf);
    }

    static void bubble_sort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        bubble_sort_primary(array, cmpf);
    }

    static void shaker_sort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        shaker_sort_primary(array, cmpf);
    }

private:

// ----------------------------------- MERGE SORT -----------------------------------

	static void merge_sort_recursive(ArraySequence<T>* array, std::size_t left, std::size_t right, bool (*cmpf)(T, T))
	{
		if (left < right)
		{
			std::size_t mid = (right + left) / 2;
			merge_sort_recursive(array, left, mid, cmpf);
			merge_sort_recursive(array, mid + 1, right, cmpf);
			merge_sort_fusion(array, left, right, cmpf);
		}
	}

    static void merge_sort_fusion(ArraySequence<T>* array, std::size_t left, std::size_t right, bool (*cmpf)(T, T))
	{
		T buff_array[right - left + 1];
		std::size_t mid = (right + left) / 2;
		std::size_t p1 = left;
		std::size_t p2 = mid + 1;
		std::size_t current = 0;

		while (p1 <= mid && p2 <= right)
		{
			if (cmpf(array->get(p1), array->get(p2)))
			{
				buff_array[current] = array->get(p2);
				p2++;
			} else {
			    buff_array[current] = array->get(p1);
			    p1++;
            }
			current++;
		}

		if (p1 == mid + 1) for (; p2 < right + 1; ++p2, ++current) buff_array[current] = array->get(p2);
		else for (; p1 <= mid; ++p1, ++current) buff_array[current] = array->get(p1);

		for (std::size_t j = 0; j < right - left + 1; ++j) array->get(left + j) = buff_array[j];
	}

// ----------------------------------- QSORT SORT -----------------------------------

    static void qsort_recursive(ArraySequence<T>* array, std::size_t left, std::size_t right, bool (*cmpf)(T, T)) {
        if (left < right) {
            std::size_t current = qsort_split(array, left, right, cmpf);

            if (current > left) qsort_recursive(array, left, current - 1, cmpf);
            if (current < right) qsort_recursive(array, current + 1, right, cmpf);
        }
    }

    static std::size_t qsort_split(ArraySequence<T> *array, std::size_t left, std::size_t right, bool (*cmpf)(T, T)) {
        std::size_t pivot = right;
        std::size_t i = left;

        for (std::size_t j = left; j < right; ++j) {
            if (!cmpf(array->get(j), array->get(pivot))) {
                array->swap(i++, j);
            }
        }
        array->swap(i, pivot);

        return i;
    }


// ----------------------------------- BUBBLE SORT -----------------------------------

    static void bubble_sort_primary(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        std::size_t size = array->get_size();
        if (size < 2) return;

        for (std::size_t i = size - 1; i > 0; --i) {
            for (std::size_t j = i; j < size && cmpf(array->get(j - 1), array->get(j)); ++j) {
                array->swap(j - 1, j);
            }
        }
    }

// ----------------------------------- SHAKER SORT -----------------------------------

   static void shaker_sort_primary(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        std::size_t size = array->get_size();

        for (std::size_t i = 0; i < size; ++i) {
            for (std::size_t l = i; l < size - 1; ++l) {
                if (cmpf(array->get(l), array->get(l + 1))) array->swap(l, l + 1);
            }
            for (std::size_t t = size - 1; t > i; --t) {
                if (cmpf(array->get(t - 1), array->get(t))) array->swap(t - 1, t);
            }
        }
   }

};

#endif // SRC_SORTER_HPP_
