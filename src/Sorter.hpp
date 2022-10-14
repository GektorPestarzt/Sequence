#ifndef SRC_SORTER_HPP_
#define SRC_SORTER_HPP_

template <typename T>
class Sorter_list {

// ----------------------------------- MERGE SORT -----------------------------------

private:
    void merge_sort_list_split(node<T>* head, node<T>** first, node<T>** second) {
        node<T> *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *first = head;
        *second = slow->next;
        slow->next = nullptr;
    }

    node<T>* merge_sort_list_merge(node<T>* first, node<T>* second, bool (*cmpf)(T, T)) {
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

    node<T>* merge_sort_list_recursive(node<T>* head, bool (*cmpf)(T, T)) { 
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

public:
    static void merge_sort_list(ListSequence<T>* list, bool (*cmpf)(T, T)) { // private: head, tail, next
        list->head = merge_list_recursive(list->head, cmpf);
        node<T>* tmp = list->head;

        while (!tmp->next)
            tmp = tmp->next;
        list->tail = tmp;
    }

    static void qsort_list() {

    }

    static void bubble_sort_list() {

    }

    static void shaker_sort_list() {

    }
};

class Sorter {
public:
    static void merge_sort() {

    }

    static void qsort() {

    }

    static void bubble_sort() {

    }

    static void shaker_sort() {

    }
};

#endif  // SRC_SORTER_HPP_
