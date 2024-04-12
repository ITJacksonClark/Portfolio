// Program showing off rule FIO50 of SEI CERT C++ Coding Standard
// By Jackson Clark
// 3/17/24

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
 * @brief Example program that shows the proper way to use a position call to 
 * prevent undefined behavior when alternately input and output from a file stream
 * 
 * @return int If file cannot be opened, returns 1
 */
int main() {
    string compare1 = "My name is Jackson Clark";
    string compare2 = "My name is Jackson Clark.";
    const string &fileName = "FIO50 file.txt";
    fstream file(fileName);

    /*Handles any file errors*/
    if(!file.is_open()) {
        cerr<<"Could not open file"<<endl;
        return 1;
    }

    file << "My name is Jackson Clark.";
    string line;

    /*seekg eliminates undefined behaviors in file 
    because it is called between the output and the input*/
    file.seekg(0, ios::beg);
    while(getline(file, line)) {
        
    }
    if(line == compare1) {
        cout<<"The file and the string compare1 are the same!"<<endl;
    }
    else if(line == compare2) {
        cout<<"The file and the string compare2 are the same!"<<endl;
    }
    else {
        cout<<"The file and the strings are not the same!"<<endl;
    }
    file.close();
}
