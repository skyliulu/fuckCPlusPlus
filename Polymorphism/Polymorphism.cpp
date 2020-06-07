#include <iostream>

using namespace std;

class base
{
    int a;

public:
    base() { Func1(); } //没有多态
    virtual void Func1() { cout << "base" << endl; }
    virtual void Func2() { cout << "base" << endl; }
    void func() { Func1(); } //多态
};

class drive : public base
{
    int a;
};

class drive1 : public base
{
    int b;

public:
    void Func2() { cout << "drive1" << endl; }
    virtual void Func1() { cout << "drive1" << endl; }
    //不加virtual也是虚函数，只要基类中是虚函数且同名同参数
};
class drive2 : public base
{
    int b;

public:
    virtual void Func3() {}
};
class moreDrive : public drive, drive1
{
    int b;
};
class moreDrive1 : public drive1, drive2
{
    int b;
};
class moreDrive2 : public drive1, drive2, drive
{
    int c;

public:
    virtual void Func4() {}
};

int main()
{
    base A;
    drive B;
    drive1 C;
    drive2 D;
    moreDrive E;
    moreDrive1 F;
    moreDrive2 G;
    base *ptr;
    ptr = &A;
    // ptr->baseFunc1();
    // ptr->func();
    // ptr = &B;
    // ptr->baseFunc1();
    // ptr->func();
    // base &ptr2 = B;
    // ptr2.baseFunc1();
}