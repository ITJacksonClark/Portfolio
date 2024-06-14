// Program showing off rule MEM51 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <new>
#include <cstdlib>
#include <memory>
#include <string>
using namespace std;

/**
 * @brief An example of how to properly deallocate dynamically allocated resources
 * 
 */

struct PlacementNew {
    PlacementNew() { cout<<"PlacementNew::PlacementNew()"<<endl; }
    ~PlacementNew() { cout<<"PlacementNew::~PlacementNew()"<<endl; }
};

struct Empty {};

class DoubleFree {
    Empty *empty;

    public:
        /*Copy constructor for Empty*/
        DoubleFree(Empty *empty) : empty(empty) {}
        DoubleFree(const DoubleFree&) = delete;
        ~DoubleFree() { delete empty; }

        void operator=(const DoubleFree&) = delete;

        void nothing() {}
};

struct ClassNew {
    /*Class-specific implementation of operator new()*/
    static void *operator new(size_t size) noexcept(true) {
        return malloc(size);
    }

    /*Class-specific implementation of operator delete()*/
    static void operator delete(void *ptr) noexcept(true) {
        free(ptr);
    }
};

/**
 * @brief Function that properly deallocates memory
 * 
 */
void properDealloc() {
    /*Placement new()*/
    alignas(struct PlacementNew) char space[sizeof(struct PlacementNew)];
    PlacementNew *newObj = new (&space) PlacementNew;

    /*Uninitialized delete*/
    /*Initializing both pointers to nullptr allows for the use 
    of delete as nullptr is a valid value to pass to delete*/
    string *str1 = nullptr, *str2 = nullptr;
    try {
        str1 = new string;
        str2 = new string;
    } catch (bad_alloc &) {
        delete str1;
        delete str2;
    }

    /*Allocated array (array new[])*/
    string *allocArr = new string[100];

    /*malloc()*/
    string *mallocStr = static_cast<string *>(malloc(sizeof(string)));

    /*new*/
    Empty *empty = new Empty();

    ClassNew *cNew = new ClassNew;
    /*Nonscoped delete call results in ClassNew delete 
    being called instead of the global operator delete()*/
    delete cNew;

    /*std::unique_ptr implmentation to hold an array 
    of objects instead of a pointer to an object*/
    unique_ptr<Empty[]> empty1 = make_unique<Empty[]>(100);

    /*std::shared_ptr implmentation without using std::make_shared() as you 
    should be manually specifying a custom deleter for the shared pointer type*/
    shared_ptr<Empty> empty2{new Empty[100], [](const Empty *ptr) {delete [] ptr; }};

    /*Invoking the destructor for placement new()*/
    newObj->~PlacementNew();

    /*Proper deallocation of an allocated array with delete[]*/
    delete[] allocArr;

    /*mallocStr with how it is allocated should be 
    deallocated with free() instead of delete*/
    free(mallocStr);

    /*pointers allocated using new should be 
    deallocated using delete instead of free()*/
    delete empty;
}

/**
 * @brief Simply calls a function using the parameter dbf while not creating a double-free error
 * 
 * @param dbf Reference to a pointer object of type DoubleFree
 */
void deallocFunc1(DoubleFree &dbf) {
    dbf.nothing();
}

/**
 * @brief Function used to setup deallocFunc1 that prevents a double-free error
 * 
 */
void deallocFunc2() {
    Empty *empty = new Empty;
    DoubleFree dbf(empty);
    deallocFunc1(dbf);
}

int main() {
    properDealloc();
    deallocFunc2();
    cout << "All dynamically allocated resources were successfully deallocated!" << endl;
}