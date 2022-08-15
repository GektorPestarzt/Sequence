#include <iostream>
#include "DynamicArray.hpp"
#include "Sequence.hpp"

using namespace std;

template <class T>
class array_sequence: public sequence<T>
{
private:
	dynamic_array<T>* data;

public:
	array_sequence() : data(nullptr) {}

	array_sequence(T* items, std::size_t length) : data(new dynamic_array<T>(items, length, 2 * length)) {}

    ~array_sequence() {}

public:
	T& get(const std::size_t& index) override {
		return this->data->get(index);
	}

	int get_length() override {
		return this->data->get_size();
	}

	void push(const T& item) override {
		if (this->data->get_size() == this->data->get_capacity())
			this->data->resize(this->data->get_capacity() * 2);

		this->data->set(this->data->get_size(), item);
		this->data->set_size(this->data->get_size() + 1);
	}

	void set(const std::size_t& index, const T& item) override {
        if (index < 0)
            throw exception("Negative index");

        if (index >= this->size)
            throw exception("Index is out of range");

		this->data->Set(index, item);
	}

	void pop(const std::size_t& index) override {
        if (index < 0)
            throw exception("Negative index");

        if (index >= this->size)
            throw exception("Index is out of range");

		for (int i = index; i < this->data->get_capacity() - 1; i++)
			this->data->set(i, this->data->get(i + 1));

		this->data->set_capacity(this->data->get_capacity() - 1);

		if (this->data->get_capacity() * 3 < this->data->get_size())
			this->data->resize(this->data->get_size() / 2);
	}

	T& operator[](const std::size_t& index) {
        if (index < 0)
            throw exception("Negative index");

        if (index >= this->size)
            throw exception("Index is out of range");

		return this->data->get(index);
	}
};
