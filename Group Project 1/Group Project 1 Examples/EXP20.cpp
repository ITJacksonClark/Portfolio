// Program showing off recommendation EXP20 of SEI CERT C Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include<cstring>
using namespace std;

/**
 * @brief An example program that performs explicit tests to determine success, true and false, and equality
 * 
 * @param number1 First int for compare
 * @param number2 Second int for compare
 * @return int 1 if true and 0 if false
 */

/**
 * @brief Determines if the two given parameter numbers are the same
 * 
 * @param number1 First number to compare
 * @param number2 Second number to compare
 * @return int Returns a non zero number if true and zero if false
 */
int sameNum(int number1, int number2) {
    int x = 0;
    if(number1 == number2)
    {
        x++;
    }
    return x;
}

/**
 * @brief Prints a statement saying if the two int parameter from sameNum are the same or not
 * 
 * @param sameNum Return value from sameNum
 */
void sameOrNot(int sameNum) {
    if(sameNum != 0)
    {
        cout<<"They are the same!"<<endl;
    }
    else
    {
        cout<<"They are different!"<<endl;
    }
}

int main() {
    int number1 = 1;
    int number2 = 1;
    int number3 = 2;
    sameOrNot(sameNum(number1, number2));
    sameOrNot(sameNum(number1, number3));
}