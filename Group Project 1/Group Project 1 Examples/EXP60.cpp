// Program showing off rule EXP60 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include "EXP60.h"
#include <iostream>
using namespace std;

/**
 * @brief Example program that shows the proper way to handle nonstandard-layout type objects across execution boundaries
 * 
 */

/**
 * @brief A printing function that takes into account not passing nonstandard-layout type object across execution boundaries (can be found in EXP60.h)
 * 
 */
void mainPrint() {
    EXP60 exp60;
    callPrint(exp60);
}

int main()
{
    mainPrint();
}