// Program showing off rule MEM55 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <new>
using namespace std;

/**
 * @brief An example on how to honor replacement dynamic storage management requirements
 * 
 */

struct MEM55 {
    /*Class-specific implementation of operator new()*/
    static void *operator new(size_t size) {
        if (void *ret = malloc(size)) {
            return ret;
        }
        /*Required behavior implemented as throwing bad_alloc when the allocation 
        fails protects against the replacement function returning a null pointer*/
        throw bad_alloc();
    }

    /*Class-specific implementation of operator delete()*/
    static void operator delete(void *ptr) noexcept(true) {
        free(ptr);
    }
};

int main() {
    MEM55 *mem55 = new MEM55;
    delete mem55;
    cout << "Honored replacement dynamic storage management requirements!" << endl;
}