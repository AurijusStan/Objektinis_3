#include "Vector.h"
#include <bits/stdc++.h>

int main() {
    int sz = 100000000;
    int resize_count_v1 = 0;
    int resize_count_v2 = 0;
    std::vector<int> v1;
    Vector<int> v2;
    for (int i = 0; i < sz; ++i){
        v1.push_back(i);
        if(v1.capacity() == v1.size()) {
            resize_count_v1++;
        }
    }
    v1.clear();

    for (int i = 0; i < sz; ++i) {
        v2.push_back(i);
        if(v2.capacity() == v2.getSize()) {
            resize_count_v2++;
        }
    }
    v2.clear();

    std::cout << "std::vector: " << resize_count_v1 << std::endl;
    std::cout << "Vector: " << resize_count_v2 << std::endl;

    return 0;
}
