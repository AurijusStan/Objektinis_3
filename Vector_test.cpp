// #include "Vector.h"

// using namespace std;

// int main(){   
    
//     Vector<int> v;

//     for(int i=0; i<15; i++){
//         v.push_back(i);
//     }

//     for(int i=0; i<15; i++){
//         cout<<v[i];
//         cout<<endl;
//     }



//     return 0;
// }

#include "Vector.h"
#include <iostream>

int main() {
    Vector<int> v;
    std::allocator<int> alloc = v.get_allocator();

    int* p = alloc.allocate(1); // Use the allocator to allocate memory
    alloc.construct(p, 42); // Use the allocator to construct an object

    std::cout << *p << std::endl; // Should output 42

    alloc.destroy(p); // Use the allocator to destroy the object
    alloc.deallocate(p, 1); // Use the allocator to deallocate the memory

    return 0;
}