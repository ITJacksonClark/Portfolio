// Program to simulate banking operations.
// Implements many SEI CERT C++ Coding Standard rules &
// many SEI CERT C Coding Standard recommendations.
// By Jackson Clark, Brian Nicollelis, Dylan Benoit, John Lagrisola, Jakob Syvertsen, & Noah Pearson 
// 3/17/24

#include <iostream>
#include <new>
#include<cstring>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include "Bank.cpp"
#include "User.cpp"
#include "Randomizer.cpp"
 
using namespace std;
#define VAR_NAME(a) cout<<#a<<" with a value of: "<<(a)<<endl 
enum { MAX_SIZE_ALLOWED_CHAR_ARRAY = 1024 };

/**
 * @brief Allocates and returns a pointer to a list of User objects
 * 
 */
User* createUsers() {       
    std::aligned_storage<sizeof(User[10]), alignof(User[10])>::type buffer; //MEM54
    //OOP55 and EXP54
    User* arrptr = ::new (&buffer) User[10];
    if(!arrptr) { //MEM52
        std::cout << "Could not create userArr";
        return nullptr;
    }
    return arrptr;
}

/**
 * @brief Calls createUsers(), catches any exceptions
 * 
 * @return bool
 */
bool createUsersHelper(User* arrptr) { //ERR58
    try {
        createUsers();
        return true;
    } catch (...) {
        std::cout << "An exception occured";
        return false;
    }
}

User* userArr = nullptr;
bool value = createUsersHelper(userArr);

struct enumObj { //Rule MEM55
    static void *operator new(size_t size) {
        if (void *ret = malloc(size)) {
            return ret;
        }

        throw bad_alloc();
    }

    static void operator delete(void *ptr) noexcept(true) {
        free(ptr);
    }
};

/**
 * @brief Copies the parameter ptr into list and prints out list taking into account freeing memory at the same level of abstraction
 * 
 * @param ptr An array of characters
 * @param number The size of the array ptr
 */
void printCharArray(char *ptr, size_t number) { //Recommendation MEM00
    //MEM04
    if(number == 0){
        std::cout << "Invalid Length!" << std::endl;
        return;
    }
    int* list = (int*) malloc(number * sizeof(int));
    //MEM05
    if(ptr == NULL) {
        cerr<<"No memory allocated to ptr"<<endl;
    }
    if(number <= MAX_SIZE_ALLOWED_CHAR_ARRAY) {
        for(int i = 0; i < number; i++) {
            list[i] = ptr[i];
        }
    }
    else {
        cerr<<"The size of array ptr is less than the minimum allowed size for an array"<<endl;
        free(list);
        return;
    }
    for(int i = 0; i < number; i++) {
        cout<<list[i];
    }
    cout<<endl;
    free(list);
}

/**
 * @brief A printing function that takes into account not passing nonstandard-layout type object across execution boundaries (can be found in User.h)
 * 
 */
void mainPrint() //Rule EXP60
{
    Printing printing;
    callPrint(printing);
}

/**
 * @brief This function is an implementation of std::max from the algorithm library
 * 
 * @param num1 First number to compare
 * @param num2 Second number to compare
 * @return int Larger of the two integer parameters
 */
int maxNumber (int num1, int num2) //Recommendation PRE09
{
    if(num1 > num2)
    {
        return num1;
    }
    else
    {
        return num2;
    }
}

int main() {

    enumObj *obj = new enumObj;

    mainPrint();

    //Rule FIO50
    const string &fileName = "Banned Users.txt";
    fstream file(fileName);

    if(!file.is_open()) {
        cerr<<"Could not open file"<<endl;
        return 1;
    }
    string line;
    string fileStr = "";

    file.seekg(0, ios::beg);
    while(getline(file, line)) {
        cout<<line<<endl;
        fileStr += line;
        fileStr += " ";
    }

    //Recommendation STR06
    char *token;
    char str[MAX_SIZE_ALLOWED_CHAR_ARRAY];
    strncpy(str, fileStr.c_str(), sizeof(str) - 1);
    str[sizeof(str) - 1];
    printCharArray(str, strlen(str));
    
    void *ptr = (char *)malloc(strlen(str) + 1); //Rule MEM53
    char *copy = new (ptr) char;
    if(copy == NULL){
        cerr<<"The copied string is empty"<<endl;
        exit(1);
    }
    strcpy(copy, str);
    token = strtok(copy," ,");

    while(token!=NULL){
        cout<<token<<endl;
        token = strtok(NULL," ,");
    }

    int principle = 10000;
    cout<<"Between principle and MAX_SIZE_ALLOWED_CHAR_ARRAY, the larger of the two is ";
    if(principle == maxNumber(principle, MAX_SIZE_ALLOWED_CHAR_ARRAY))
    {
        VAR_NAME(principle);
    }
    else
    {
        VAR_NAME(MAX_SIZE_ALLOWED_CHAR_ARRAY);
    }
    int time = 7;
    float rate = 6.25;

    float result = conSimpleInterest(principle, time, rate);
    std::cout << result << "\n";
  
    int n = 4;

    compoundInterest(result, principle, time, n, rate);
    std::cout << result << "\n";

    //STR50 and STR51
    std::cout << "Please input a username: \n";
    string username;
    std::cin >> username;

    if(username == "")
    {
        std:cout << "Null value found. Defaulting...\n";
        username = "User 1";
    }
    //EXP63
    User user1(std::move(username), 1);
    std::cout << user1.deposit(1000) << "\n";
    std::cout << user1.withdraw(100) << "\n";

    User user2("User 2", 2);
    User user3("User 3", 3);

    //INT 50
    cout << getBranch(user1.getBranchID()) << "\n";
    cout << getBranch(user2.getBranchID()) << "\n";

    int randomLoan = randomizer();
    cout << randomLoan << " is the random loan taken by " << username <<"\n";
    

    user1.takeLoan(randomLoan, 5.0);
    user2.takeLoan(10000, 6.25);
    //INT18-C
    if( (long)randomLoan + 10000 > user2.getPrinciple() + 50){
        user2.takeLoan(10050, 6.25);
    }
    user3.takeLoan(100000, 10.0);

    calculateInterest(user1.getPrinciple(), user1.getRate(),
                      user2.getPrinciple(), user2.getRate(),
                      user3.getPrinciple(), user3.getRate());
  
    std::vector<User> users(3); // Rule CTR52
    users.emplace_back(user1);
    users.emplace_back(user2);
    users.emplace_back(user3);
    //= {user1, user2, user3};
    std::vector<User>::iterator it = users.begin();
    
    while(it != users.end())
    {
        if(it >= users.begin() && it < users.end())
        {
            std::cout << it->getName() << " " << it->getID() << " "<< it->getBalance() << " " << it->getPrinciple() << " " << it->getRate() << "\n";
        }
        else
        {
            cerr<<"Index out of range"<<endl;
        }
        advance(it, 1);
    }
    cout<< "Compare User2 and User3 for posterity: \n";
    comparison(user2, user3);

    // delete userArr;
    //EXP54
    //Deallocate userArr.
    delete[] userArr; // Using delete[] on userArr is rule MEM51
    userArr = nullptr;

    free(ptr);
    ptr = NULL;

    delete obj;

    //FIO51
    file.close();
}
