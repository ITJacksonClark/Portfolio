// Implementation of the randomizer class
// By Jackson Clark, Brian Nicollelis, Dylan Benoit, John Lagrisola, Jakob Syvertsen, & Noah Pearson 
// 3/17/24

#include <iostream>
#include <string>
#include <random>
using namespace std;

/**
 *  @brief returns a random value between 0 and 100
 *  MSC50
 *  
 *  @brief Ensure your random number generator is properly seeded
 *  MSC51
 * 
 */

int randomizer()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0,100);

    return dist(engine);
}
