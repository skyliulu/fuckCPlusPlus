# 多态与虚函数
>在面向对象的程序设计中使用多态，能够增强程序的可扩充性，即程序需要修改或增加功能的时候，需要改动和增加的代码较少。

## 多态
派生类的指针可以赋给基类指针。
通过基类指针调用基类和派生类中的同名虚函数时:
- 若该指针指向一个基类的对象，那么被调用是基类的虚函数；
- 若该指针指向一个派生类的对象，那么被调用的是派生类的虚函数。
```c++
#include <iostream>

using namespace std;

class base
{
public:
    virtual void baseFunc1() { cout << "base1" << endl; }
};

class drive1 : public base
{
public:
    virtual void baseFunc1() { cout << "drive1" << endl; }
};

int main()
{
    base A;drive1 B;base *ptr;
    ptr = &A;
    ptr->baseFunc1();//base1
    ptr = &B;
    ptr->baseFunc1();//drive1
}
```
派生类的对象可以赋给基类引用,通过基类引用调用基类和派生类中的同名虚函数时:
- 若该引用引用的是一个基类的对象，那么被调用是基类的虚函数；
- 若该引用引用的是一个派生类的对象，那么被调用的是派生类的虚函数。
```c++
drive1 B;
base &ptr2 = B;
ptr2.baseFunc1();//drive1
```
**非构造和非析构函数调用虚函数也是多态**
```c++
class base
{
public:
    base() {baseFunc1();}//没有多态
    virtual void baseFunc1() { cout << "base1" << endl; }
    void func() {baseFunc1();}//多态
};

class drive1 : public base
{
public:
    //不加virtual也是虚函数，只要基类中是虚函数且同名同参数
    void baseFunc1() { cout << "drive1" << endl;}
};
int main()
{
    base A;drive1 B;base *ptr;
    ptr = &A;
    ptr->func();
    ptr = &B;
    ptr->func();
}
```

**为什么构造函数和析构函数调用虚函数没有多态？**
- new一个派生类对象时，先调用基类的构造函数，此时派生类的成员没有初始化，如果此时去调用派生类的虚函数，那么结果会有问题，无法保证正确性。所以只会用基类定义的虚函数。
- delete一个派生类对象时,先调用派生类的析构函数，然后执行基类的析构函数，此时派生类的成员已经被释放掉了，如果此时去调用派生类的虚函数，那么同理，结果会有问题，无法保证正确性。所以只会用基类定义的虚函数。

## 虚函数
在类的定义中，前面有virtual关键字的成员函数就是虚函数。virtual关键字只用在类定义里的函数声明中，写函数体时不用。
```c++
class base {
virtual int vfunc() ;
};
int base::vfunc() { }
```
### 虚函数的实现原理



### 使用虚函数需要注意
#### 1. **构造函数可以是虚函数吗?**
2. **析构函数可以是虚函数吗?**
3. **静态成员函数可以是虚函数吗?**
4. **友元函数可以是虚函数吗?**

### 纯虚函数和抽象类
**纯虚函数**: 没有函数体的虚函数
```c++
class A {
 public:
 virtual void Print( ) = 0 ; //纯虚函数
};
```
**抽象类**：包含纯虚函数的类
- 只能作为基类来派生新类使用
- 不能创建抽象类的对象
- 抽象类的指针和引用-->由抽象类派生出来的类的对象
  - A a; // 错, A 是抽象类, 不能创建对象
  - A * pa; // ok, 可以定义抽象类的指针和引用
  - pa = new A; //错误, A 是抽象类, 不能创建对象
- 在成员函数内可以调用纯虚函数
- 在构造函数/析构函数内部不能调用纯虚函数，**为什么？**