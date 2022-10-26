#ifndef SRC_ARRAYSEQUENCE_HPP_
#define SRC_ARRAYSEQUENCE_HPP_

#include <iostream>

#include "DynamicArray.hpp"
#include "Sequence.hpp"

#define MIN_CAPACITY 10

template <class T>
class ArraySequence: public Sequence<T> {
private:
    std::size_t min_capacity(const std::size_t& capacity) {
        return capacity < MIN_CAPACITY ? MIN_CAPACITY : capacity;
    }

public:
	ArraySequence() noexcept
        : data(new DynamicArray<T>()) {}

	ArraySequence(T* items, std::size_t size) noexcept
        : data(new DynamicArray<T>(items, size, min_capacity(size * 2))) {}

    ~ArraySequence() noexcept { delete data; }

public:
	std::size_t get_size() const noexcept override { return this->data->get_size(); }

    bool empty() const noexcept override { return this->data->get_size() == 0; }

    T& get(std::size_t index) const noexcept override { return this->data->get(index); }

    T get_last() const noexcept override { return this->data->get(this->data->get_size() - 1); }

    T get_first() const noexcept override { return this->data->get(0); }

	void push_back(const T& item) noexcept override {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

		if (size == capacity)
            this->data->resize(capacity * 2);

		this->data->set(item, size);
		this->data->set_size(size + 1);
	}

	void pop_back() noexcept override {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

		this->data->set_size(size - 1);

		if (size * 3 < capacity && capacity > MIN_CAPACITY)
			this->data->resize(min_capacity(capacity / 2));
	}

    void append(const T& item) noexcept override { this->push_back(item); }

    void prepend(const T& item) noexcept {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

        if (size == capacity)
            this->data->resize(capacity * 2);

        if (size != 0) {
            for (std::size_t i = size - 1; i > 0; --i)
                this->data->set(this->data->get(i), i + 1);
        }

        this->data->set(this->data->get(0), 1);
        this->data->set(item, 0);
        this->data->set_size(++size);
    }

	void insert(const T& item, std::size_t index) noexcept override {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

        if (size == capacity)
            this->data->resize(capacity * 2);

        if (size != 0) {
            for (std::size_t i = size - 1; i >= index; --i) {
                this->data->set(this->data->get(i), i + 1);
                if (i == 0) break;
            }
        }

		this->data->set(item, index);
        this->data->set_size(++size);
	}

    void erase(std::size_t index) noexcept override {
        std::size_t size = this->data->get_size();
        std::size_t capacity = this->data->get_capacity();

        for (std::size_t i = index + 1; i <= size; ++i)
            this->data->set(this->data->get(i), i - 1);

        this->data->set_size(size - 1);

        if (size * 3 < capacity && capacity > MIN_CAPACITY)
			this->data->resize(min_capacity(capacity / 2));
	}

    void swap(std::size_t first, std::size_t second) noexcept {
        T buffer = this->data->get(first);
        this->data->set(this->data->get(second), first);
        this->data->set(buffer, second);
    }

	T& operator[](std::size_t index) { return this->data->get(index); }

private:
	DynamicArray<T>* data;
};

#endif  // SRC_ARRAYSEQUENCE_HPP_
