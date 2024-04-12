// Program showing off recommendation STR06 of SEI CERT C Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include<cstring>
using namespace std;

/**
 * @brief An example program that does not assume that strtok() leaves the parse string unchanged
 * 
 * @return int Returns zero when the program finishes running
 */

int main(){
    char *token;
    char str[] = "Hello World!";

    /*Temporary buffer so that we can still access the original string*/
    char *copy = (char *)malloc(strlen(str) + 1);
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

    free(copy);
    copy = NULL;

    return 0;
}