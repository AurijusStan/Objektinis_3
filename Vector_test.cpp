#include "Vector.h"
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int main() {
    int sz = 100000000;
    
    auto start = high_resolution_clock::now();

    std::vector<int> v1;

    for (int i = 0; i < sz; ++i){
        v1.push_back(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout<<"std::vector laikas: "<<duration.count()<<endl;

    v1.clear();

    start = high_resolution_clock::now();

    Vector<int> v2;

    for (int i = 0; i < sz; ++i) {
        v2.push_back(i);
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    cout<<"Vector laikas: "<<duration.count()<<endl;

    v2.clear();

    return 0;
}
