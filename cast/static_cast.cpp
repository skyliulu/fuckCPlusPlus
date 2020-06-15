#include <iostream>

using namespace std;

class A {
public:
    operator char *() {return NULL;}//定义类型转换函数
};

class B:public A {

};

int main() {
    int x, *p;
    char *p2;
    x = static_cast<int>(3.14);//ok
    // x = static_cast<int>("3.14");//error，不能将字符串转为int
    p = &x;
    // p2 = static_cast<char *>(p);//error,不同类型的指针不能相互转换
    // x = static_cast<int>(p);//error,指针和整形不能转换
    A a;
    p2 = static_cast<char *>(a);//ok
    B b;
    // b = static_cast<B>(a);//error，父类转子类
    a = static_cast<A>(b);//ok,子类转父类
}