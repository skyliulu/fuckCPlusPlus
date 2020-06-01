#include <iostream>

using namespace std;

class testThis
{
    int n;

public:
    void hello() { cout << "hello" << endl; }
    void printn() { cout << this->n << endl; }
};

int main()
{
    testThis *ptr = NULL;
    ptr->hello();
    ptr->printn();
}
