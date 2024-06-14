// Program showing off rule MEM53 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

/**
 * @brief An example of explicitly constructing and destructing objects when manually managing object lifetime
 * 
 */

struct MEM53 {
    MEM53() { cout<<"MEM53::MEM53()"<<endl; }
    ~MEM53() { cout<<"MEM53::~MEM53()"<<endl; }

    void nothing() {}
};

/**
 * @brief The proper way to handle the lifetime of an object
 * 
 */
void lifetime() {
    /*Underlying storage*/
    void *ptr = malloc(sizeof(MEM53));
    /*Live object*/
    MEM53 *mem53 = new (ptr) MEM53;

    mem53->nothing();

    mem53->~MEM53();
    free(ptr);
}

int main() {
    lifetime();
    cout << "Successfully manually managed an objects lifetime!" << endl;
}