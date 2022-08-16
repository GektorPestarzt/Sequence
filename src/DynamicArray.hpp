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
	T& get(const std::size_t& index) {
		return this->array[index];
	}

	std::size_t get_size() {
		return this->size;
	}

	std::size_t get_capacity() {
		return this->capacity;
	}

	void set_capacity(const std::size_t& capacity) {
		this->capacity = capacity;
	}

    void set_size(const std::size_t& size) {
        this->size = size;
    }

	void set(const std::size_t& index, const T& value) {
		this->array[index] = value;
	}

	void resize(const std::size_t& new_capacity) {
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
