#ifndef SRC_LISTSEQUENCE_HPP_
#define SRC_LISTSEQUENCE_HPP_

#include <iostream>
#include <assert.h>

#include "LinkedList.hpp"
#include "Sequence.hpp"

using namespace std;

template <typename T>
class list_sequence : public sequence<T> {
public:
	list_sequence() : data(new linked_list<T>()) {}

	list_sequence(T* items, std::size_t size) : data(new linked_list<T>(items, size)) {}
	
    list_sequence(list_sequence<T>* list) : data(new linked_list<T>(list->data)) {}

    ~list_sequence() { delete data; }

public:
	std::size_t get_size() const noexcept override { return this->data->get_size(); }

    bool empty() const noexcept override { return this->data->empty(); }

	T& get(std::size_t index) const override {
		assert(index < this->data->get_size());

		return this->data->get(index);
	}

    T get_first() const override {
        assert(!this->data->empty());

        return this->data->get(this->data->get_size() - 1);        
    }

    T get_last() const override {
        assert(!this->data->empty());

        return this->data->get(0);
    }

	void push_back(const T& item) noexcept override {
        this->data->insert(item, this->data->get_size());
	}

	void pop_back() override {
        assert(!this->data->empty());

		this->data->pop(this->data->get_size() - 1);
	}

    void append(const T& item) noexcept override { this->push_back(item); }

    void prepend(const T& item) noexcept override { this->data->insert(item, 0); }

    void insert(const T& item, std::size_t index) override {
        assert(index <= this->data->get_size());

        this->data->insert(item, index);
    }

    void erase(std::size_t index) override {
        assert(index < this->data->get_size());

        this->data->pop(index);
    }

    T& operator[](std::size_t index) {
        assert(index < this->data->get_size());

        return this->data->get(index);
    }

private:
	linked_list<T>* data;
};

#endif  // SRC_LISTSEQUENCE_HPP_
