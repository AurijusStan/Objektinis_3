#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <memory> 
#include <iterator> 
#include <limits>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    std::allocator<T> allocator_;

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T> init_list);
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    Vector& operator=(std::initializer_list<T> init_list);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    void reserve(size_t new_capacity);
    void shrink_to_fit(); 
    void resize(size_t count);
    void swap(Vector& other) noexcept;
    void push_back(const T& x);
    void pop_back();
    size_t getSize() const;
    size_t max_size() const;
    size_t capacity() const;
    bool empty() const;
    void clear() noexcept;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void assign(size_t count, const T& x);
    template <typename InputIt>
    void assign(InputIt first, InputIt last);

    T& at(size_t index);
    const T& at(size_t index) const;
    T* data() noexcept;
    const T* data() const noexcept;
    std::allocator<T> get_allocator() const;

    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend() const noexcept { return data_ + size_; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    iterator insert(const_iterator pos, const T& x);
    iterator insert(const_iterator pos, T&& x);
    iterator insert(const_iterator pos, size_t count, const T& x);
    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
};

template <typename T>
Vector<T>::Vector(const Vector& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
}

template <typename T>
Vector<T>::~Vector() {
    clear();
    allocator_.deallocate(data_, capacity_);
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init_list) : data_(new T[init_list.size()]), size_(init_list.size()), capacity_(init_list.size()) {
    std::copy(init_list.begin(), init_list.end(), data_);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> init_list) {
    delete[] data_;
    size_ = init_list.size();
    capacity_ = init_list.size();
    data_ = new T[capacity_];
    std::copy(init_list.begin(), init_list.end(), data_);
    return *this;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
void Vector<T>::push_back(const T& x) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = x;
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        T* new_data = new T[new_capacity];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ > size_) {
        T* new_data = new T[size_];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }
}

template <typename T>
void Vector<T>::resize(size_t count) {
    if (count > capacity_) {
        reserve(count);
    }
    if (count > size_) {
        std::fill(data_ + size_, data_ + count, T());
    }
    size_ = count;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    } else {
        throw std::out_of_range("Vector is empty");
    }
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
size_t Vector<T>::getSize() const {
    return size_;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void Vector<T>::clear() noexcept {
    size_ = 0;
}

template <typename T>
T& Vector<T>::front() {
    if (size_ == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data_[0];
}

template <typename T>
const T& Vector<T>::front() const {
    if (size_ == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data_[0];
}

template <typename T>
T& Vector<T>::back() {
    if (size_ == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T>
const T& Vector<T>::back() const {
    if (size_ == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T>
void Vector<T>::assign(size_t count, const T& x) {
    delete[] data_;
    size_ = count;
    capacity_ = count;
    data_ = new T[capacity_];
    std::fill(data_, data_ + size_, x);
}

template <typename T>
template <typename InputIt>
void Vector<T>::assign(InputIt first, InputIt last) {
    delete[] data_;
    size_ = std::distance(first, last);
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(first, last, data_);
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
T* Vector<T>::data() noexcept {
    return data_;
}

template <typename T>
const T* Vector<T>::data() const noexcept {
    return data_;
}

template <typename T>
std::allocator<T> Vector<T>::get_allocator() const {
    return std::allocator<T>();
}

template <typename T>
size_t Vector<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T& x) {
    size_t index = pos - cbegin();
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    for (size_t i = size_; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = x;
    ++size_;
    return data_ + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T&& x) {
    size_t index = pos - cbegin();
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    for (size_t i = size_; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = std::move(x);
    ++size_;
    return data_ + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_t count, const T& x) {
    size_t index = pos - cbegin();
    if (size_ + count > capacity_) {
        reserve(capacity_ + count);
    }
    for (size_t i = size_ + count - 1; i >= index + count; --i) {
        data_[i] = std::move(data_[i - count]);
    }
    for (size_t i = 0; i < count; ++i) {
        data_[index + i] = x;
    }
    size_ += count;
    return data_ + index;
}

template <typename T>
template <class InputIt>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, InputIt first, InputIt last) {
    size_t index = pos - cbegin();
    size_t count = std::distance(first, last);
    if (size_ + count > capacity_) {
        reserve(capacity_ + count);
    }
    for (size_t i = size_ + count - 1; i >= index + count; --i) {
        data_[i] = std::move(data_[i - count]);
    }
    for (size_t i = 0; i < count; ++i, ++first) {
        data_[index + i] = *first;
    }
    size_ += count;
    return data_ + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, std::initializer_list<T> ilist) {
    size_t index = pos - cbegin();
    size_t count = ilist.size();
    if (size_ + count > capacity_) {
        reserve(capacity_ + count);
    }
    for (size_t i = size_ + count - 1; i >= index + count; --i) {
        data_[i] = std::move(data_[i - count]);
    }
    std::copy(ilist.begin(), ilist.end(), data_ + index);
    size_ += count;
    return data_ + index;
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args) {
    size_t index = pos - cbegin();
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    // Shift elements to the right to make space for the new element
    if (index < size_) {
        for (size_t i = size_; i > index; --i) {
            allocator_.construct(&data_[i], std::move(data_[i - 1]));
            allocator_.destroy(&data_[i - 1]);
        }
    }
    // Construct the new element in place using the allocator
    allocator_.construct(&data_[index], std::forward<Args>(args)...);
    ++size_;
    return data_ + index;
}


#endif 
