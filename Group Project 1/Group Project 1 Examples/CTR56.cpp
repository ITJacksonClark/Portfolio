// Program showing off rule CTR56 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
using namespace std;

/**
 * @brief An example program of how to handle pointer arithmetic on polymorphic objects
 */
int globInt = 7;
double globDb = 7;

struct CTR56Int {
  int num1;
  CTR56Int() : num1(globInt--) {}
};

/*CTR56Db will be our polymorphic object*/
struct CTR56Db : CTR56Int {
  double num2;
  CTR56Db() : CTR56Int(), num2(globDb--) {}
};

/**
 * @brief Subtraction function that uses a pointer array of type CTR56Int as a parameter with the number of 
 * times the funtion subtracts being based on the number of objects in the array using the size parameter
 * 
 * @param numArr Array of CTR56Int objects
 * @param size Size of numArr
 */
void subtraction(const CTR56Int * const *numArr, size_t size) {
  for (const CTR56Int * const *end = numArr + size; numArr != end; ++numArr) {
    cout<<(*numArr)->num1<<endl;
  }
}

int main()
{
  /*Array of polymorphic objects*/
  CTR56Int *ptrArr[] = {new CTR56Db, new CTR56Db, new CTR56Db, new CTR56Db, new CTR56Db, new CTR56Db, new CTR56Db};
  subtraction(ptrArr, 7);

  /*Deleting all array objects to help with deallocation*/
  for (auto v : ptrArr) {
    delete v;
  }
}