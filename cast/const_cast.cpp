#include <iostream>

using namespace std;


int main() {
    const int n = 10;
    // int m = const_cast<int>(n);//error
    int& x = const_cast<int&>(n);//ok
    int *y = const_cast<int *>(&n);//ok

}