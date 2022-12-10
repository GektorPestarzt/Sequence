#ifndef SRC_SORTER_HPP_
#define SRC_SORTER_HPP_

#include "ListSequence.hpp"

template <typename T>
class SorterList {
public:
    using namespace ListSequence<T>;

    static void merge_sort_list(ListSequence<T>* list, bool (*cmpf)(T, T)) {
        list->set_head(merge_sort_list_recursive(list->begin(), cmpf));
    }

    static void qsort_list(ListSequence<T>* list, bool (*cmpf)(T, T)) {
        list->set_head(qsort_list_recursive(list->begin(), cmpf));
    }

private:
// ----------------------------------- MERGE SORT LIST -----------------------------------

    static node<T>* merge_sort_list_recursive(iterator it, bool (*cmpf)(T, T)) { 
        if (!(*it) || !(*it)->next) {
            return *it;
        }

        iterator first, second;
        merge_sort_list_split(it, &first, &second);

        first = merge_sort_list_recursive(first, cmpf);
        second = merge_sort_list_recursive(second, cmpf);

        node<T> *result = merge_sort_list_merge(first, second, cmpf);
        return result;
    }

    static void merge_sort_list_split(iterator head, iterator* first, iterator* second) {
        iterator it = head;
        iterator slow = it, fast = ++it;
        while (*fast && (*fast)->next) {
            ++slow;
            ++(++fast);
        }

        first = head;
        second = ++slow;
        (*slow)->next = nullptr;
    }

    static node<T>* merge_sort_list_merge(iterator first, iterator second, bool (*cmpf)(T, T)) {
        node<T>* result = nullptr;

        if (*first && (!*second || !cmpf((*first)->data, (*second)->data))) {
            result = *first;
            result->next = merge_sort_list_merge(++first, second, cmpf);
        } else if (*second && (!*first || cmpf((*first)->data, (*second)->data))) {
            result = *second;
            result->next = merge_sort_list_merge(first, ++second, cmpf);
        }

        return result;
    }

// ----------------------------------- QUICK SORT LIST -----------------------------------

    static node<T>* qsort_list_recursive(iterator head, bool (*cmpf)(T, T)) {
        if (!*head || !(*head)->next) {
            return *head;
        }

        iterator current = head;
        while ((*current)->next) { ++current; }

        head = qsort_list_split(head, current, cmpf);

        iterator tmp;

        (*current)->next = qsort_list_recursive(current->next, cmpf);
        if (head != current) {
            tmp = head;
            while ((*tmp)->next != *current) { ++tmp; }
            (*tmp)->next = nullptr;

            head = qsort_list_recursive(head, cmpf);
   
            tmp = head;
            while ((*tmp)->next) { ++tmp; }
            (*tmp)->next = *current;
        } else {
            head = current;
        }

        return head;
    }

    static node<T>* qsort_list_split(iterator head, iterator current, bool (*cmpf)(T, T)) {
        iterator tmp = head;
        node<T>* new_head = *head;
        iterator prev = nullptr;
        iterator last = current;

        while (tmp != current) {
            if (cmpf((*tmp)->data, (*current)->data)) {
                if (!*prev) {
                    new_head = *tmp;
                    ++new_head;
                } else {
                    (*prev)->next = (*tmp)->next;
                }
                (*last)->next = *tmp;
                last = tmp;
                ++tmp;
                (*last)->next = nullptr;
            } else {
                prev = tmp;
                ++tmp;
            }
        }

        return new_head;
    }
};

template<typename T>
class Sorter {
public:
    using namespace ArraySequence<T>;

    static void merge_sort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        merge_sort_recursive(array, 0, array->get_size() - 1, cmpf);
    }

    static void qsort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        qsort_recursive(array->begin(), array->end() - 1, cmpf);
    }

    static void bubble_sort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        bubble_sort_primary(array, cmpf);
    }

    static void shaker_sort(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        shaker_sort_primary(array, cmpf);
    }

private:

// ----------------------------------- MERGE SORT -----------------------------------

	static void merge_sort_recursive(iterator left, iterator right, bool (*cmpf)(T, T)) {
		if (left < right)
		{
			iterator mid = (right + left) / 2;
			merge_sort_recursive(array, left, mid, cmpf);
			merge_sort_recursive(array, mid + 1, right, cmpf);
			merge_sort_fusion(array, left, right, cmpf);
		}
	}

    static void merge_sort_fusion(ArraySequence<T>* array, std::size_t left, std::size_t right, bool (*cmpf)(T, T))
	{
		T* buff_array = new T[right - left + 1];
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

    static void qsort_recursive(iterator left, iterator right, bool (*cmpf)(T, T)) {
        if (left < right) {
            iterator current = qsort_split(left, right, cmpf);

            if (current > left) qsort_recursive(left, current - 1, cmpf);
            if (current < right) qsort_recursive(current + 1, right, cmpf);
        }
    }

    static iterator qsort_split(iterator left, iterator right, bool (*cmpf)(T, T)) {
        iterator pivot = right;
        iterator i = left;

        for (iterator j = left; j < right; ++j) {
            if (!cmpf(*j, *pivot)) {
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

        for (iterator i = array->end() - 1; i != array->begin(); --i) {
            for (iterator j = i; j != array->end() && cmpf(*(j - 1), *j); ++j) {
                array->swap(j - 1, j);
            }
        }
    }

// ----------------------------------- SHAKER SORT -----------------------------------

   static void shaker_sort_primary(ArraySequence<T>* array, bool (*cmpf)(T, T)) {
        for (iterator i = array->begin(); i != array->end(); ++i) {
            for (iterator l = i; l != array->end() - 1; ++l) {
                if (cmpf(*l, *(l + 1))) array->swap(l, l + 1);
            }
            for (iterator t = array->end() - 1; t > i; --t) {
                if (cmpf(*(t - 1), *t)) array->swap(t - 1, t);
            }
        }
   }

};

#endif // SRC_SORTER_HPP_
