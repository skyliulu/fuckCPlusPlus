#include <iostream>

using namespace std;

void func(int a) {
    cout << "int" <<endl;
}

void func(double d) {
    cout << "double" <<endl;
}

int main() {
    func(1.0f);
}