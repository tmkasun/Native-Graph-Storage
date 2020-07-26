#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
void pointers();
int addressing(int data);
void refHandling(string &name);
void acceptPointers(char* name[]);

int main(int argc, const char** argv) {
    cout << "Sample store" << endl;
    char* kname[10];
    std::cout << "Sending just char array to name setter with address " << &kname << std::endl;
    std::cout << "before sending data =  " << kname << std::endl;

    acceptPointers(kname);

    std::cout << "after completing function data =  " << kname << std::endl;

    return -1;
    int mainData = -456;
    std::cout << "I'm in main sending data in address" << &mainData << std::endl;
    int returnedData = addressing(mainData);
    std::cout << "I have in main received data from addressing as " << returnedData << std::endl;
    std::cout << "I have in main received data from addressing and it's mem address is " << returnedData << std::endl;
    std::cout << "Main data value is " << mainData << std::endl;

    string oriString = "Kasun";
    std::cout << "Original string is "<< oriString << std::endl;
    string &refString = oriString;
    std::cout << "Ref string value is "<< refString << std::endl;

    refHandling(refString);

    std::cout << "new Original string is "<< oriString << std::endl;
    std::cout << "new Ref string value is "<< refString << std::endl;

    // pointers();
    // readData();
    return 1;
}

void acceptPointers(char* name[]) {
    string names = "kasun";
    strcpy(*name, names.c_str());
    std::cout << "Inside the function param name address " << &name << std::endl;
}

void refHandling(string &name) {
    name += " Thennakoon"; 
}

int addressing(int data){
    std::cout << "I received data in address" << &data << std::endl;
    std::cout << "I received data " << data << std::endl;
    data = 123;
    std::cout << "Update data to " << data << std::endl;
    return data;
}

void pointers() {
    // https://www3.ntu.edu.sg/home/ehchua/programming/cpp/cp4_PointerReference.html
    int* pNum;
    int age = 29;
    std::cout << "Address of the age variable is " << pNum << std::endl;
    std::cout << "Which is same as " << &age << std::endl;
    std::cout << "Content of pNum is " << *pNum << std::endl;
    std::cout << "As same as " << age << std::endl;

    // string *myName;
    // *myName = "wola i'm crashing";
    // std::cout << *myName << std::endl;

    float cash;
    cash = 123.65;
    float &myCash = cash;

    std::cout << "cash is " << cash << std::endl;
    std::cout << "my cash is " << myCash << std::endl;

    myCash = 1548795.15654;
    std::cout << "new cash is " << cash << std::endl;
    std::cout << "new my cash is " << myCash << std::endl;

    return;
}