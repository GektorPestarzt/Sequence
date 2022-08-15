#include <iostream>

template <class T>
class sequence
{
public:
	virtual T& get(const std::size_t&) = 0;
	virtual int get_length() = 0;
	virtual void push(const T&) = 0;
	virtual void set(const std::size_t&, const T&) = 0;
	virtual void pop(const std::size_t&) = 0;
};
