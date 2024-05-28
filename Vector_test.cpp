#include "Vector.h"
#include <iostream>
#include <numeric>

int main() {
    Vector<int> nums = {1, 2, 3, 4, 5};

    nums.push_back(6);
    nums.push_back(7);

    std::cout << "Vector elements: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Sum of elements: " << std::accumulate(nums.begin(), nums.end(), 0) << std::endl;

    nums.resize(10);

    std::cout << "Vector elements after resize: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    nums.reserve(20);

    std::cout << "size after resize: " << nums.getSize() << std::endl;

    std::cout << "max size: " << nums.max_size() << std::endl;

    std::cout << "capacity after reserve: " << nums.capacity() << std::endl;

    nums.shrink_to_fit();

    std::cout << "capacity after shrink: " << nums.capacity() << std::endl;

    nums.insert(nums.begin()+4, 21);

    std::cout << "Vector elements after resize: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    Vector<int> vec;
    vec.reserve(10);

    vec.emplace(vec.begin(), 1);
    vec.emplace(vec.end(), 4, 5);
    vec.emplace(vec.begin() + 1, 3, 2);

    std::cout << "Vector elements after resize: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
