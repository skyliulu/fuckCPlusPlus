#include <iostream>

using namespace std;

int& test1() {
    int x = 10;
    return x;
}

int& test2() {
    int *x = new int(11);
    return *x;
}

int& test3() {
    static int x = 12;
    return x;
}

static int y = 20;
int& test4() {
    return y;
}

int main() {
    cout << test1() <<endl;
    cout << test2() <<endl;
    cout << test3() <<endl;
    cout << test4() <<endl;
}