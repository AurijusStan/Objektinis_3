#include <iostream>
#include <numeric> // For std::accumulate
#include "Vector.h" // Include your Vector header

int main() {
    Vector<int> nums = {1, 2, 3, 4, 5};

    // Print the vector
    std::cout << "Vector elements: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Use std::accumulate to sum the elements
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "Sum of elements: " << sum << std::endl;

    // Print the vector in reverse
    std::cout << "Vector elements in reverse: ";
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
