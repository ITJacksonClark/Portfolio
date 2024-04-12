// Program showing off rule ERR56 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/**
 * @brief An example program showing off strong exception safety
 * 
 */

class StringArray {
    string *strArr;
    size_t numElems;
public:
    StringArray() {}
    ~StringArray() {
        delete[] strArr;
    }

    StringArray(const StringArray& that);
    StringArray& operator=(const StringArray &rhs) {
        /*Pointer for safetly copying the memory allocated to strArr*/
        string *tmp = nullptr;
        if (rhs.numElems) {
            tmp = new string[rhs.numElems];
            memcpy(tmp, rhs.strArr, rhs.numElems * sizeof(*strArr));
        }
        delete[] strArr;
        strArr = tmp;
        numElems = rhs.numElems;
        return *this;
    }
};

int main() {
    StringArray *arr = new StringArray;
    StringArray *arrCpy = arr;
    cout<<"This program ran and performed with strong exception safety!"<<endl;
}