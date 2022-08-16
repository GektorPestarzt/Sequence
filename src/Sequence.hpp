#include <iostream>

template <class T>
class sequence
{
public:
	virtual int get_size() = 0;
    virtual bool empty() = 0;

    virtual T& get_first() = 0;
    virtual T& get_last() = 0;
    virtual T& get(const std::size_t&) = 0;

	virtual void push_back(const T&) = 0;
    virtual void pop_back() = 0;

	virtual void append(const T&) = 0;
    virtual void prepend(const T&) = 0;
    virtual void insert(const T&, const std::size_t&) = 0;
};
