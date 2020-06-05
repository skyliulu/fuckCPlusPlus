#include <iostream>

using namespace std;

class base
{
    int a;

public:
    base() { baseFunc1(); } //没有多态
    virtual void baseFunc1() { cout << "base1" << endl; }
    virtual void baseFunc2() { cout << "base1" << endl; }
    void func() { baseFunc1(); } //多态
};

class drive : public base
{
    int a;
};

class drive1 : public base
{
    int b;

public:
    void baseFunc2() { cout << "drive1" << endl; }
    virtual void baseFunc1() { cout << "drive1" << endl; }
    //不加virtual也是虚函数，只要基类中是虚函数且同名同参数
    virtual void drive1Func() { cout << "drive1" << endl; }
};

int main()
{
    base A;
    drive C;
    drive1 B;
    base *ptr;
    ptr = &A;
    ptr->baseFunc1();
    ptr->func();
    ptr = &B;
    ptr->baseFunc1();
    ptr->func();
    base &ptr2 = B;
    ptr2.baseFunc1();
}