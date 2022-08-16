#ifndef SRC_SEQUENCE_HPP_
#define SRC_SEQUENCE_HPP_

#include <iostream>

template <class T>
class sequence {
public:
	virtual int get_size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

    virtual T& get_first() const = 0;
    virtual T& get_last() const = 0;
    virtual T& get(std::size_t) const = 0;

	virtual void push_back(const T&) noexcept = 0;
    virtual void pop_back() = 0;

	virtual void append(const T&) noexcept = 0;
    virtual void prepend(const T&) noexcept = 0;
    virtual void insert(const T&, std::size_t) = 0;
};

#endif  // SRC_SEQUENCE_HPP_
