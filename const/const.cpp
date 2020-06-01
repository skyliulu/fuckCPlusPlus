#include <iostream>

using namespace std;

class test
{
    int n;

public:
    test() { n = 1; };
    // int set(int i) const {n=i;}//error,常成员函数不能更改成员变量
    int set(int i) {}
    int get() const { return n; }
    int get() { return n; } //重载
};

int main()
{
    const test t1;
    test t2;
    //t1.set(2);//error,常量对象不能调用非常量成员函数
    t2.set(2);
    cout << t1.get() << " " << t2.get() << endl;
    const int val = 20;
    // val = 22;//error
    // val = 20;//error
    cout << val << endl;
    int val2 = 30;
    const int *ptr = &val2;
    // *ptr = 40;//error
    val2 = 40;
    int *const ptr2 = &val2;
    *ptr2 = 50; //ok
    // ptr2 = ptr;//error
}