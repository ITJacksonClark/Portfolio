// Program showing off recommendation PRE09 of SEI CERT C Coding Standard
// By Jackson Clark
// 3/17/24

#include "PRE09.h"
#include <iostream>
using namespace std;

/**
 * @brief An example program that doesn't replace secure functions with deprecated or obsolescent functions which is done by creating and implmenting a library's function
 * 
 */

/**
 * @brief Independent implementation of the math libraries power function
 * 
 * @param number The base
 * @param pow The exponent
 * @return int The base to the power of the exponent
 */
int PRE09::power(int number, int pow)
{
    int copy = number;
    for(int i = 0; i < pow - 1; i++)
    {
        copy = copy * number;
    }
    return copy;
}

int main()
{
    PRE09 pre09 = PRE09();
    int number = 5;
    int pow = 6;
    cout<<pre09.power(number, pow)<<endl;
}