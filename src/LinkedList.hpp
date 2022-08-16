#ifndef SRC_LINKEDLIST_HPP_
#define SRC_LINKEDLIST_HPP_

#include <iostream>

template<typename T>
struct node {
	T data;
	node* next;

		node(const T& _item, node _next) : data(_item), next(_next) {}
};

template<typename T>
class linked_list {
private:
	node* head;
	node* tail;
	std::size_t size;

public:
	linked_list(const T* const items, std::size_t count) noexcept : size(count) {
		node<T>* tmp {nullptr};
		node<T>* prev = new node<T>(items[0]);
		this->head = prev;

		for (std::size_t i = 1; i < count; ++i) {
			tmp = new node<T>(items[i], nullptr);

			prev->next = tmp;
			prev = tmp;
		}

		this->tail = tmp;
	}
	
	linked_list(linked_list<T>* list) : size(list->size) //ERROR if size = 0; head = tail = nullptr
	{
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

	~LinkedList() {
		auto tmp = this->head;
		auto next_one = tmp->next;

		for (std::size_t i = 0; i < size; ++i) {
			delete tmp;
			tmp = next_one;
			next_one = next_one->next;
		}
	}

public:
	T& get_first() {
		if (this->head == nullptr)
			throw exception("Nullptr");

		return this->head->data;
	}

	T& GetLast()
	{
		if (this->tail == nullptr)
			throw exception("Nullptr");

		return this->tail->data;
	}

	T& Get(int index)
	{
		if (index < 0)
			throw exception("Negative index");

		if (index >= this->size)
			throw exception("Index is out of range");

		if (this->head == nullptr)
			throw exception("Nullptr");

		LinkedList<T>::Data* tmp = this->head;

		int i;
		for (i = 0; i < index; i++) tmp = tmp->next;

		return tmp->data;
	}

	int GetCapacity()
	{
		return this->size;
	}

	LinkedList<T>* GetSubList(int startIndex, int endIndex)
	{
		if (startIndex < 0)
			throw exception("Negative index");

		if (endIndex >= this->size)
			throw exception("Index is out of range");

		if (startIndex > endIndex)
			throw exception("Wrong index");

		LinkedList<T>::Data* tmp = this->head;

		for (int i = 0; i < startIndex; i++) tmp = tmp->next;

		const int N = endIndex - startIndex + 1;
		T *data = new T[N];
		for (int i = 0; i < N; ++i)
		{
			data[i] = tmp->data;
			tmp = tmp->next;
		}

		LinkedList<T>* newList = new LinkedList<T>(data, N);

		return newList;
	}

	void Append(T item) //Добавляет элемент в конец списка
	{
		auto tmp = new LinkedList<T>::Data(item);

		if (this->tail == nullptr)
		{
			this->tail = tmp;
			this->head = tmp;
			this->size = 1;
			return;
		}

		this->tail->next = tmp;
		this->tail = tmp;
		this->size++;
	}

	void Prepend(T item) //Добавляет элемент в начало списка
	{
		auto tmp = new LinkedList<T>::Data(item);

		if (this->head == nullptr)
		{
			this->head = tmp;
			this->tail = tmp;
			this->size = 1;
			return;
		}

		tmp->next = this->head;
		this->head = tmp;
		this->size++;
	}

	void InsertAt(int index, T item) //Вставляет элемент в заданную позицию
	{
		if (index < 0)
			throw exception("Negative index");

		if (index > this->size)
			throw exception("Index is out of range");

		auto tmp = new LinkedList<T>::Data(item);

		if (this->head == nullptr)
		{
			this->head = tmp;
			this->tail = tmp;
			this->size = 1;
			return;
		}

		if (index == 0)
		{
			this->Prepend(item);
			return;
		}

		LinkedList<T>::Data* prev = this->head;

		for (int i = 0; i < index - 1; ++i) prev = prev->next;

		tmp->next = prev->next;
		prev->next = tmp;
		this->size++;

		if (tmp->next == nullptr) this->tail = tmp;
	}

	void Pop(int index)
	{
		if (index < 0)
			throw exception("Negative index");

		if (index >= this->size)
			throw exception("Index is out of range");

		LinkedList<T>::Data* tmp = this->head;

		if (this->size == 1)
		{
			delete(this->head);
			this->head = nullptr;
			this->tail = nullptr;
			this->size = 0;
		}

		if (index == 0)
		{
			tmp = tmp->next;
			delete(this->head);
			this->head = tmp;
			this->size -= 1;
			return;
		}

		if (index == this->size - 1)
		{
			for (int i = 0; i < this->size - 2; i++) tmp = tmp->next;
			delete(this->tail);
			this->tail = tmp;
			tmp->next = nullptr;
			this->size -= 1;
			return;
		}

		for (int i = 0; i < index - 1; i++) tmp = tmp->next;

		LinkedList<T>::Data* del = tmp->next;
		tmp->next = tmp->next->next;
		delete(del);
		this->size -= 1;
	}
	
	LinkedList<T>* Concat(LinkedList<T>* list) //Сцепляет два списка
	{
		LinkedList<T> *newList = new LinkedList<T>(this);

		LinkedList<T>::Data* oldList = list->head;
		LinkedList<T>::Data* tmp {nullptr};
		LinkedList<T>::Data* prev = new LinkedList<T>::Data(oldList->data);

		newList->tail->next = prev;
		newList->tail = prev;

		oldList = oldList->next;

		int i;
		for (i = 1; i < list->size; i++)
		{
			tmp = new LinkedList<T>::Data(oldList->data);
			prev->next = tmp;

			prev = tmp;
			oldList = oldList->next;
		}

		newList->tail = tmp;
		newList->size = this->size + list->size;

		return newList;
	}
};

#endif  // SRC_LINKEDLIST_HPP_
