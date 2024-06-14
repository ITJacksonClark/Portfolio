// Header file for EXP60.cpp
// By Jackson Clark
// 3/17/24

#ifndef EXP60_H
#define EXP60_H

#include <iostream>
#include <type_traits>
using namespace std;

/**
 * @brief Header file for EXP60.cpp
 * 
 */

struct EXP60 {
    /**
     * @brief Simple print statement
     * 
     */
    void print() {
        cout<<"This example shows the proper way to handle nonstandard-layout type objects across execution boundaries!"<<endl;
    }
};
static_assert(is_standard_layout<EXP60>::value, "EXP60 is required to be a standard layout type");


/**
 * @brief Implemented by the EXP60.h and calls EXP60::print()
 * 
 * @param exp60 EXP60 object being used to call print()
 */
void callPrint(EXP60 &exp60)
{
    exp60.print();
}

#endif