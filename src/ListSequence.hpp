#ifndef SRC_LISTSEQUENCE_HPP_
#define SRC_LISTSEQUENCE_HPP_

#include <iostream>
#include <assert.h>

#include "LinkedList.hpp"
#include "Sequence.hpp"

using namespace std;

template <typename T>
class ListSequence : public Sequence<T> {
public:
	ListSequence() : data(new LinkedList<T>()) {}

	ListSequence(T* items, std::size_t size) : data(new LinkedList<T>(items, size)) {}
	
    ListSequence(ListSequence<T>* list) : data(new LinkedList<T>(list->data)) {}

    ~ListSequence() { delete data; }

public:
    class iterator {
        node<T>* it;

        public:
            iterator(node<T>* it) : it(it) {}

            T& operator*() { return this->it->data; }

            bool operator==(const iterator &it_compare) noexcept {
                return this->it == it_compare.it;
            }

            bool operator!=(const iterator &it_compare) noexcept {
                return this->it != it_compare.it;
            }

            iterator operator++() noexcept {
                this->it = this->it->next;
                return *this;
            }
    };

    iterator begin() noexcept { return iterator(this->data->get_head()); }
    iterator end() noexcept { return iterator(this->data->get_tail()->next); }


	std::size_t get_size() const noexcept override { return this->data->get_size(); }

    bool empty() const noexcept override { return this->data->empty(); }

    void set_head(node<T> *head) noexcept { this->data->set_head(head); }

    node<T>* get_head() const noexcept { return this->data->get_head(); }

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
	LinkedList<T>* data;
};

#endif  // SRC_LISTSEQUENCE_HPP_
