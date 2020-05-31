#include <iostream>


using namespace std;

int main() {

    const int val = 20;
    // val = 22;//error
    // val = 20;//error
    cout<<val<<endl;
    int val2 = 30;
    const int * ptr = &val2;
    // *ptr = 40;//error
    val2 = 40;
    int * const ptr2 = &val2;
    *ptr2 = 50;//ok
    // ptr2 = ptr;//error

}