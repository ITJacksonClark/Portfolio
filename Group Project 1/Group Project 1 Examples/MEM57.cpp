// Program showing off rule MEM57 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <new>
using namespace std;

/**
 * @brief An example of how to handle the new operator for over-aligned types
 * 
 */

int const globSize = 64;

struct alignas(globSize) Vector {
    char elems[globSize];
    static void *operator new(size_t numBytes) {
        /*Use _aligned_malloc instead of aligned_alloc because 
        Microsoft C Runtime library doesn't support aligned_alloc*/
        if(void *ptr = _aligned_malloc(alignof(Vector), numBytes)) {
            return ptr;
        }
        throw bad_alloc();
    }
    static void operator delete(void *ptr) noexcept(true) {
        free(ptr);
    }
};

Vector *mem57()
{
    Vector *vecPtr = new Vector;
    return vecPtr;
}

int main() {
    Vector *vecPtr = mem57();
    cout<<"Memory has been allocated to the Vector object!"<<endl;
}