// Program showing off recommendation MEM00 of SEI CERT C Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include<cstring>
using namespace std;

/**
 * @brief An example program that allocates and frees memory in the same module at the same level of abstraction
 * 
 */

enum { MAX_SIZE_ALLOWED = 5 };

/**
 * @brief Gets the element at that position in the ptr array
 * 
 * @param ptr Pointer to the inputted array
 * @param pos Current place in the ptr array
 * @return int The integer at that point in the ptr array 
 */
int getElement(const int *ptr, int pos) {
    return ptr[pos];
}

/**
 * @brief Copies integers into copy array while incrementing by 10
 * 
 * @param copy Array of integers of a specified size
 * @param size Size of copy
 */
void copyElements(int copy[], size_t size) {
    int* ptr = (int*) malloc(size * sizeof(int));
    if(ptr == NULL) {
        cerr<<"No memory allocated to ptr"<<endl;
    }
    int numbers = 0;
    if(size <= MAX_SIZE_ALLOWED) {
        for(int i = 0; i < size; i++) {
            numbers = numbers + 10;
            ptr[i] = numbers;
        }
        for(int i = 0; i < size; i++) {
            copy[i] = getElement(ptr, i);
        }
    }
    else {
        cerr<<"The size of array ptr is more than the maximum allowed size for an array"<<endl;
        free(ptr);
        return;
    }
    free(ptr);
    for(int i = 0; i < size; i++) {
        cout<<copy[i]<<"\n"<<endl;
    }
}

int main() {
    int copy[5];
    int size = sizeof(copy) / sizeof(int);
    copyElements(copy, size);
}