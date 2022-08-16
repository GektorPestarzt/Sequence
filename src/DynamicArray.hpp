#ifndef SRC_DYNAMICARRAY_HPP_
#define SRC_DYNAMICARRAY_HPP_

#include <iostream>

template <class T>
class dynamic_array {
public:
	dynamic_array() : array(new T[10]), size(0), capacity(10) {}
	
    dynamic_array(std::size_t size) : size(size), array(new T[size]) {}
	
    dynamic_array(T* items, std::size_t _size, std::size_t _capacity)
        : array(new T[_capacity]), size(_size), capacity(_capacity) {
        std::copy(items, items + _size, array);
    }
	
    ~dynamic_array() { delete[] array; }

public:
	inline T& get(std::size_t index) const noexcept { return this->array[index]; }

	inline std::size_t get_size() const noexcept { return this->size; }

	inline std::size_t get_capacity() const noexcept { return this->capacity; }

	inline void set_capacity(std::size_t capacity) noexcept { this->capacity = capacity; }

    inline void set_size(std::size_t size) noexcept { this->size = size; }

	inline void set(const T& value, std::size_t index) noexcept { this->array[index] = value; }

	void resize(std::size_t new_capacity) noexcept {
		auto new_array = new T[new_capacity];

		for (std::size_t i = 0; i < new_capacity && i < this->size; i++)
			new_array[i] = this->array[i];

		this->array = std::move(new_array);
		this->capacity = std::move(new_capacity);
		if (new_capacity < this->size) this->size = std::move(new_capacity);
	} // MOVES?????? and delete ????

private:
	T* array;
	std::size_t size = 0;
	std::size_t capacity = 0;
};

#endif  // SRC_DYNAMICARRAY_HPP_
