#ifndef SRC_ARRAYSEQUENCE_HPP_
#define SRC_ARRAYSEQUENCE_HPP_

#include <iostream>
#include <assert.h>

#include "DynamicArray.hpp"
#include "Sequence.hpp"

#define MIN_CAPACITY 10

template <class T>
class array_sequence: public sequence<T> {
private:
    std::size_t min_capacity(const std::size_t& capacity) {
        return capacity < MIN_CAPACITY ? MIN_CAPACITY : capacity;
    }

public:
	array_sequence() noexcept
        : data(new dynamic_array<T>()) {}

	array_sequence(T* items, std::size_t size) noexcept
        : data(new dynamic_array<T>(items, size, min_capacity(size * 2))) {}

    ~array_sequence() {}

public:
	int get_size() const noexcept override { return this->data->get_size(); }

    bool empty() const noexcept override { return this->data->get_size() == 0; }

    T& get(std::size_t index) const override {
        assert(index < this->data->get_size());

		return this->data->get(index);
	}

    T& get_last() const override {
        assert(!this->empty());

        return this->data->get(this->data->get_size() - 1);
    }

    T& get_first() const override {
        assert(!this->empty());

        return this->data->get(0);
    }

	void push_back(const T& item) noexcept override {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

		if (size == capacity)
            this->data->resize(capacity * 2);

		this->data->set(item, size);
		this->data->set_size(size + 1);
	}

	void pop_back() override {
        assert(!this->empty());

        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

		this->data->set_size(size - 1);

		if (size * 3 < capacity && capacity > MIN_CAPACITY)
			this->data->resize(min_capacity(capacity / 2));
	}

    void append(const T& item) noexcept override { push_back(item); }

    void prepend(const T& item) noexcept {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

        if (size == capacity)
            this->data->resize(capacity * 2);

        for (std::size_t i = size - 1; i > 0; --i)
            this->data->set(this->data->get(i), i + 1);

        this->data->set(this->data->get(0), 1);
        this->data->set(item, 0);
        this->data->set_size(size + 1);
    }

	void insert(const T& item, std::size_t index) override {
        assert(index < this->data->get_size());

		this->data->set(item, index);
	}

	T& operator[](std::size_t index) {
        assert(index < this->data->get_size());

		return this->data->get(index);
	}

private:
	dynamic_array<T>* data;
};

#endif  // SRC_ARRAYSEQUENCE_HPP_
