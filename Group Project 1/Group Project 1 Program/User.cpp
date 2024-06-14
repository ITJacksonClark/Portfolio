// Implementation of the user class
// By Jackson Clark, Brian Nicollelis, Dylan Benoit, John Lagrisola, Jakob Syvertsen, & Noah Pearson 
// 3/17/24

#include <string>
 
#include "User.h"
#include <iostream>

using namespace userNamespace;

/**
 * @brief Construct a new User:: User object
 * 
 */
User::User(void) {
    name = "";
    id = 0;
    branch_id = 2;
    balance = 0;
    principle = 0;
    rate = 0;
}

/**
 * @brief Construct a new User:: User object
 * 
 * @param name 
 * @param id 
 */
User::User(std::string name, int id) {
    this->name = name;
    this->id = id;
    balance = 0;
    branch_id = 7;
    principle = 0;
    rate=0;
}
//DCL57
User::~User()
try { 

}
catch (std::exception exc){
    std::cout << "An Exception has occurred: " << std::endl;
    return;
}

//EXP50
void User::processTransactions(int depositAmount, int withdrawalAmount) {
    std::cout << "Starting transactions for " << name << ".\n";

    //Deposit deposit
    this->deposit(depositAmount);
    std::cout << "Deposited " << depositAmount << ".\n";

    //Withdrawal
    if (withdrawalAmount <= depositAmount) {
        this->withdraw(withdrawalAmount);
        std::cout << "Withdrew " << withdrawalAmount << ".\n";
    } else {
        std::cout << "Withdrawal amount exceeds the deposited amount, transaction not processed.\n";
    }
}

/**
 * @brief Withdraw amount from user's blance
 * 
 * @param amount 
 * @return float 
 */
float User::withdraw(float amount) {
    if (amount > balance) {
        std::cout << "Withdrawal failed. Insufficient balance.\n";
        return balance; // Could use a specific value or throw an exception to indicate failure.
    }
    balance -= amount;
    std::cout << "Withdrawal of $" << amount << " successful. New balance: $" << balance << ".\n";
    return balance;
}

/**
 * @brief Add amount to user's balance
 * 
 * @param amount 
 * @return float 
 */
float User::deposit(float amount) {
    if (amount < 0) {
        std::cout << "Deposit failed. Negative amount.\n";
        return balance; // Could use a specific value or throw an exception to indicate failure.
    }
    balance += amount;
    std::cout << "Deposit of $" << amount << " successful. New balance: $" << balance << ".\n";
    return balance;
}

/**
 * @brief Get the user's name
 * 
 * @return std::string 
 */
std::string User::getName(void) {
    return name;
}

/**
 * @brief Get the user's ID
 * 
 * @return int 
 */
int User::getID(void) {
    return id;
}

/**
 * @brief Get the user's balance
 * 
 * @return float 
 */
float User::getBalance(void) {
    return balance;
}


 /** 
 * @brief gets User's branch id
 * 
 * @return int branch value
 */
int User::getBranchID(){
    return branch_id;
}

/**
 * @brief Take a loan with given amount and rate
 * 
 * @param amount 
 * @param rate 
 */
void User::takeLoan(int amount, float rate) {
    principle = amount;
    this->rate = rate;
}

/**
 * @brief Get the user's principle amount
 * 
 * @return long 
 */
long User::getPrinciple(void) {
    return principle;
}

/**
 * @brief Get the users interest rate
 * 
 * @return long 
 */
long User::getRate() {
    return rate;
}

/**
 * @brief Compares user1 and user2 based on name
 * 
 * @param user1 
 * @param user2 
 */
void comparison(User &user1, User &user2)
{
    if(user1 != user2)
    {
        std::cout<<"These differ.\n";
    }
}