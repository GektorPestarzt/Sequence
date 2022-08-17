#ifndef SRC_LINKEDLIST_HPP_
#define SRC_LINKEDLIST_HPP_

#include <iostream>
#include <assert.h>

template<typename T>
struct node {
	T data;
	node* next;

		node(const T& _item, node* _next = nullptr) : data(_item), next(_next) {}
};

template<typename T>
class linked_list {
private:
	node<T>* head;
	node<T>* tail;
	std::size_t size;

public:
    linked_list() noexcept : head(nullptr), tail(nullptr), size(0) {}

	linked_list(const T* const items, std::size_t _size) noexcept : size(_size) {
		node<T>* tmp {nullptr};
		node<T>* prev = new node<T>(items[0]);
		this->head = prev;

		for (std::size_t i = 1; i < _size; ++i) {
			tmp = new node<T>(items[i]);

			prev->next = tmp;
			prev = tmp;
		}

		this->tail = tmp;
	}
	
	linked_list(linked_list<T>* list) : size(list->size) { //ERROR if size = 0; head = tail = nullptr
		node<T>* oldList = list->head;
		node<T>* tmp {nullptr};
		node<T>* prev = new node<T>(oldList->data);
		this->head = prev;

		oldList = oldList->next;

		for (std::size_t i = 1; i < list->size; ++i) {
			tmp = new node<T>(oldList->data);
			prev->next = tmp;

			prev = tmp;
			oldList = oldList->next;
		}

		this->tail = tmp;
	}

	~linked_list() {
		node<T>* tmp = this->head;

		while (tmp != nullptr) {
			delete tmp;
			tmp = tmp->next;
		}
	}

public:
    std::size_t get_size() const noexcept { return this->size; }

    bool empty() const noexcept { return this->head == nullptr; }

	T& get(std::size_t index) const noexcept {
		node<T>* tmp = this->head;

		for (std::size_t i = 0; i < index; ++i) tmp = tmp->next;
		return tmp->data;
	}

	void insert(const T& item, std::size_t index) noexcept {
		node<T>* tmp = new node<T>(item);

		if (this->head == nullptr) {
			this->head = tmp;
			this->tail = tmp;
			this->size = 1;
			return;
		}

		if (index == 0) {
			tmp->next = this->head;
            this->head = tmp;
            this->size++;
			return;
		}

		node<T>* prev = this->head;
		for (std::size_t i = 0; i < index - 1; ++i) prev = prev->next;

		tmp->next = prev->next;
		prev->next = tmp;
		this->size++;

		if (tmp->next == nullptr) this->tail = tmp;
	}

	void pop(std::size_t index) {
		node<T>* tmp = this->head;

		if (this->size == 1) {
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			this->size = 0;
            return;
		}

		if (index == 0) {
			tmp = tmp->next;
			delete(this->head);
			this->head = tmp;
			this->size--;
			return;
		}

		if (index == this->size - 1) {
			for (std::size_t i = 0; i < this->size - 2; ++i) tmp = tmp->next;
			delete this->tail;
			this->tail = tmp;
			tmp->next = nullptr;
			this->size--;
			return;
		}

		for (std::size_t i = 0; i < index - 1; ++i) tmp = tmp->next;

		node<T>* del = tmp->next;
		tmp->next = tmp->next->next;
		delete del;
		this->size--;
	}
	
	linked_list<T>* Concat(linked_list<T>* list) {
		linked_list<T> *new_list = new linked_list<T>(this);

		node<T>* old_list = list->head;
		node<T>* tmp {nullptr};
		node<T>* prev = new node<T>(old_list->data);

		new_list->tail->next = prev;
		new_list->tail = prev;

		old_list = old_list->next;

		for (std::size_t i = 1; i < list->size; ++i) {
			tmp = new node<T>(old_list->data);
			prev->next = tmp;

			prev = tmp;
			old_list = old_list->next;
		}

		new_list->tail = tmp;
		new_list->size = this->size + list->size;

		return new_list;
	}

	linked_list<T>* GetSubList(std::size_t startIndex, std::size_t endIndex) const noexcept {
		node<T>* tmp = this->head;

		for (std::size_t i = 0; i < startIndex; ++i) tmp = tmp->next;

		const std::size_t N = endIndex - startIndex + 1;
		T *data = new T[N];
		for (std::size_t i = 0; i < N; ++i) {
			data[i] = tmp->data;
			tmp = tmp->next;
		}

		linked_list<T>* newList = new linked_list<T>(data, N);
		return newList;
	}
};

#endif  // SRC_LINKEDLIST_HPP_
