// Program showing off rule CTR52 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/**
 * @brief Guaranteeing that library functions do not overflow
 * 
 * @return int The multiples of whatever the num variable's value is
 */
int main()
{
    int multiples = 1;
    int num = 10;
    /* Define the size of the vector before attempting to fill it with values which prevents overflow*/
    vector<int> nums(5);
    for(int i = 0; i < nums.size() - 1; i++)
    {
        fill_n(nums.begin() + multiples, 1, num);
        multiples++;
        num = num * multiples;
    }
    
    for(int i = 0; i < nums.size(); i++)
    {
        cout<<nums[i]<<endl;
    }
}