#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include <initializer_list>
#include <algorithm> // For std::copy
#include <memory> // For std::allocator

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;
    Allocator allocator;

    void resize(size_t new_capacity);

public:
    Vector() : data(nullptr), size(0), capacity(0), allocator(Allocator()) {}
    Vector(const Vector& other); // Copy constructor
    Vector(Vector&& other) noexcept; // Move constructor
    Vector(std::initializer_list<T> init_list); // Initializer list constructor
    ~Vector();

    Vector& operator=(const Vector& other); // Copy assignment operator
    Vector& operator=(Vector&& other) noexcept; // Move assignment operator
    Vector& operator=(std::initializer_list<T> init_list); // Initializer list assignment operator

    void assign(size_t count, const T& value); // Fill with count copies of value
    void assign(std::initializer_list<T> init_list); // From initializer list

    template <typename InputIt>
    void assign_range(InputIt first, InputIt last); // From range

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void swap(Vector& other) noexcept;
    void push_back(const T& value);
    void pop_back();
    size_t getSize() const;
    bool empty() const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T* data() noexcept;
    const T* data() const noexcept;

    Allocator get_allocator() const;
};

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& other) : data(nullptr), size(other.size), capacity(other.capacity), allocator(other.allocator) {
    if (capacity > 0) {
        data = allocator.allocate(capacity);
        for (size_t i = 0; i < size; ++i) {
            allocator.construct(&data[i], other.data[i]);
        }
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity), allocator(std::move(other.allocator)) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init_list) : data(nullptr), size(init_list.size()), capacity(init_list.size()), allocator(Allocator()) {
    data = allocator.allocate(capacity);
    std::uninitialized_copy(init_list.begin(), init_list.end(), data);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector() {
    for (size_t i = 0; i < size; ++i) {
        allocator.destroy(&data[i]);
    }
    allocator.deallocate(data, capacity);
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < size; ++i) {
            allocator.destroy(&data[i]);
        }
        allocator.deallocate(data, capacity);

        data = other.data;
        size = other.size;
        capacity = other.capacity;
        allocator = std::move(other.allocator);

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(std::initializer_list<T> init_list) {
    Vector temp(init_list);
    swap(temp);
    return *this;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::assign(size_t count, const T& value) {
    Vector temp;
    temp.data = allocator.allocate(count);
    temp.size = count;
    temp.capacity = count;
    for (size_t i = 0; i < count; ++i) {
        temp.allocator.construct(&temp.data[i], value);
    }
    swap(temp);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::assign(std::initializer_list<T> init_list) {
    Vector temp(init_list);
    swap(temp);
}

template <typename T, typename Allocator>
template <typename InputIt>
void Vector<T, Allocator>::assign_range(InputIt first, InputIt last) {
    Vector temp;
    size_t new_size = std::distance(first, last);
    temp.data = allocator.allocate(new_size);
    temp.size = new_size;
    temp.capacity = new_size;
    std::uninitialized_copy(first, last, temp.data);
    swap(temp);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::swap(Vector& other) noexcept {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(allocator, other.allocator);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    allocator.construct(&data[size++], value);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(size_t new_capacity) {
    T* new_data = allocator.allocate(new_capacity);
    for (size_t i = 0; i < size; ++i) {
        allocator.construct(&new_data[i], std::move(data[i]));
        allocator.destroy(&data[i]);
    }
    allocator.deallocate(data, capacity);
    data = new_data;
    capacity = new_capacity;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::pop_back() {
    if (size > 0) {
        allocator.destroy(&data[--size]);
    } else {
        throw std::out_of_range("Vector is empty");
    }
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T, typename Allocator>
const T& Vector<T, Allocator>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T, typename Allocator>
size_t Vector<T, Allocator>::getSize() const {
    return size;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const {
    return size == 0;
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::front() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[0];
}

template <typename T, typename Allocator>
const T& Vector<T, Allocator>::front() const {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[0];
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::back() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[size - 1];
}

template <typename T, typename Allocator>
const T& Vector<T, Allocator>::back() const {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[size - 1];
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::at(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T, typename Allocator>
const T& Vector<T, Allocator>::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::data() noexcept {
    return data;
}

template <typename T, typename Allocator>
const T* Vector<T, Allocator>::data() const noexcept {
    return data;
}

template <typename T, typename Allocator>
Allocator Vector<T, Allocator>::get_allocator() const {
    return allocator;
}

#endif
