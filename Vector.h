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
    void resize(size_t count, const T& x);
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
    // template <typename InputIt>
    // void append_range(InputIt first, InputIt last);

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

    template <typename... Args>
    void emplace_back(Args&&... args);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

};

template <typename T>
Vector<T>::Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ > 0) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = allocator_.allocate(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            allocator_.construct(&data_[i], other.data_[i]);
        }
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : data_(nullptr), size_(0), capacity_(0) {
    swap(other);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init_list) : data_(nullptr), size_(0), capacity_(0) {
    size_ = init_list.size();
    capacity_ = init_list.size();
    data_ = allocator_.allocate(capacity_);
    size_t i = 0;
    for (const auto& elem : init_list) {
        allocator_.construct(&data_[i++], elem);
    }
}

template <typename T>
Vector<T>::~Vector() {
    clear();
    allocator_.deallocate(data_, capacity_);
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
        clear();
        allocator_.deallocate(data_, capacity_);
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
    Vector temp(init_list);
    swap(temp);
    return *this;
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
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        T* new_data = allocator_.allocate(new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            allocator_.construct(&new_data[i], std::move(data_[i]));
            allocator_.destroy(&data_[i]);
        }
        allocator_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_capacity;
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ > size_) {
        T* new_data = allocator_.allocate(size_);
        for (size_t i = 0; i < size_; ++i) {
            allocator_.construct(&new_data[i], std::move(data_[i]));
            allocator_.destroy(&data_[i]);
        }
        allocator_.deallocate(data_, capacity_);
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
        for (size_t i = size_; i < count; ++i) {
            allocator_.construct(&data_[i], T());
        }
    } else {
        for (size_t i = count; i < size_; ++i) {
            allocator_.destroy(&data_[i]);
        }
    }
    size_ = count;
}

template <typename T>
void Vector<T>::resize(size_t count, const T& x) {
    if (count > capacity_) {
        reserve(count);
    }
    if (count > size_) {
        for (size_t i = size_; i < count; ++i) {
            allocator_.construct(&data_[i], x);
        }
    } else {
        for (size_t i = count; i < size_; ++i) {
            allocator_.destroy(&data_[i]);
        }
    }
    size_ = count;
}

template <typename T>
void Vector<T>::push_back(const T& x) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    allocator_.construct(&data_[size_], x);
    ++size_;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        allocator_.destroy(&data_[size_ - 1]);
        --size_;
    } else {
        throw std::out_of_range("Vector is empty");
    }
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
    for (size_t i = 0; i < size_; ++i) {
        allocator_.destroy(&data_[i]);
    }
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
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
void Vector<T>::assign(size_t count, const T& x) {
    clear();
    if (capacity_ < count) {
        allocator_.deallocate(data_, capacity_);
        capacity_ = count;
        data_ = allocator_.allocate(capacity_);
    }
    for (size_t i = 0; i < count; ++i) {
        allocator_.construct(&data_[i], x);
    }
    size_ = count;
}

template <typename T>
template <typename InputIt>
void Vector<T>::assign(InputIt first, InputIt last) {
    clear();
    size_t count = std::distance(first, last);
    if (capacity_ < count) {
        allocator_.deallocate(data_, capacity_);
        capacity_ = count;
        data_ = allocator_.allocate(capacity_);
    }
    size_t i = 0;
    for (auto it = first; it != last; ++it) {
        allocator_.construct(&data_[i++], *it);
    }
    size_ = count;
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
    return allocator_;
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
        allocator_.construct(&data_[i], std::move(data_[i - 1]));
        allocator_.destroy(&data_[i - 1]);
    }
    allocator_.construct(&data_[index], x);
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
        allocator_.construct(&data_[i], std::move(data_[i - 1]));
        allocator_.destroy(&data_[i - 1]);
    }
    allocator_.construct(&data_[index], std::move(x));
    ++size_;
    return data_ + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_t count, const T& x) {
    size_t index = pos - cbegin();
    if (size_ + count > capacity_) {
        reserve(size_ + count);
    }
    for (size_t i = size_; i > index; --i) {
        allocator_.construct(&data_[i + count - 1], std::move(data_[i - 1]));
        allocator_.destroy(&data_[i - 1]);
    }
    for (size_t i = 0; i < count; ++i) {
        allocator_.construct(&data_[index + i], x);
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
        reserve(size_ + count);
    }
    for (size_t i = size_; i > index; --i) {
        allocator_.construct(&data_[i + count - 1], std::move(data_[i - 1]));
        allocator_.destroy(&data_[i - 1]);
    }
    size_t i = 0;
    for (auto it = first; it != last; ++it, ++i) {
        allocator_.construct(&data_[index + i], *it);
    }
    size_ += count;
    return data_ + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args) {
    size_t index = pos - cbegin();
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    if (index < size_) {
        for (size_t i = size_; i > index; --i) {
            allocator_.construct(&data_[i], std::move(data_[i - 1]));
            allocator_.destroy(&data_[i - 1]);
        }
    }
    allocator_.construct(&data_[index], std::forward<Args>(args)...);
    ++size_;
    return data_ + index;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args&&... args) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    allocator_.construct(&data_[size_], std::forward<Args>(args)...);
    ++size_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
    if (pos < cbegin() || pos >= cend()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_t index = pos - cbegin();
    allocator_.destroy(&data_[index]);
    for (size_t i = index; i < size_ - 1; ++i) {
        allocator_.construct(&data_[i], std::move(data_[i + 1]));
        allocator_.destroy(&data_[i + 1]);
    }
    --size_;
    return data_ + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last) {
    if (first < cbegin() || last > cend() || first >= last) {
        throw std::out_of_range("Iterator range out of range");
    }

    size_t first_index = first - cbegin();
    size_t last_index = last - cbegin();
    size_t count = last_index - first_index;

    for (size_t i = first_index; i < last_index; ++i) {
        allocator_.destroy(&data_[i]);
    }

    for (size_t i = last_index; i < size_; ++i) {
        allocator_.construct(&data_[i - count], std::move(data_[i]));
        allocator_.destroy(&data_[i]);
    }

    size_ -= count;
    return data_ + first_index;
}

#endif