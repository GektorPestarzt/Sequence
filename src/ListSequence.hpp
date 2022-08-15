#include <iostream>
#include "LinkedList.h"
#include "Sequence.h"

using namespace std;

template <class T>
class ListSequence : public Sequence<T>
{
private:
	LinkedList<T>* data;

public:
	ListSequence() : data(new LinkedList<T>()) {}
	ListSequence(T* items, int count) : data(new LinkedList<T>(items, count)) {}
	ListSequence(ListSequence<T>* list) : data(new LinkedList<T>(list->data)) {}

public:
	T& Get(int index) override
	{
		if (index == 0) return data->GetFirst();
		if (index + 1 == data->GetCapacity()) return data->GetLast();

		return data->Get(index);
	}

	int GetLength() override
	{
		return data->GetCapacity();
	}

	void Push(T item) override
	{
		data->Append(item);
	}

	void Set(int index, T item) override
	{
		data->InsertAt(index, item);
	}

	void Pop(int index) override
	{
		data->Pop(index);
	}
};

//HEHE
