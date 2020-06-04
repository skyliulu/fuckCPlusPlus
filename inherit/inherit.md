# 继承和派生

继承和派生是一件事，指的是子类/派生类通过某种方式继承了父类/基类的成员变量和成员函数。
- 派生类拥有基类的全部成员函数和成员变量。
- 派生类中可以扩充新的成员变量和成员函数。
- 派生类一经定义后，可以独立使用，不依赖于基类。
- 在派生类的各个成员函数中，不能访问基类中的private成员。
<!--more-->
c++中有三种继承方式，分别为public继承、private继承和protected继承。对于基类base:
```c++
class base
{
private:
    int priv;
    void priFunc() {}

protected:
    int pro;
    void proFunc() {}

public:
    int pub;
    void pubFunc() {}
    base()
    {
        cout << "base constructor called" << endl;
    }
};
```
---
## public继承
>public继承表达的是"is"关系，即子类必须是父类，例如”男人“可以public继承”人“，因为”男人“is"人”
```c++
class drive1 : public base
{
public:
    void access()
    {
        // cout<<priv<<endl;//error!无法访问基类的私有成员
        cout << pro << endl; //ok
        cout << pub << endl; //ok
    }
    drive1() {
        cout << "drive1 constructor called!"<<endl;
    }
};
```
public继承会保留基类非私有成员的可见性
```c++
drive1 d1;
// d1.pri;//error
// d1.priFunc();//error
// d1.pro;//error
// d1.proFunc();//error
d1.pub;
d1.pubFunc();
```
### public继承的赋值兼容规则
```c++
class base { };
class derived : public base { };
base b;
derived d;
```
1. 派生类的对象可以赋值给基类对象
   - b = d;
2. 派生类对象可以初始化基类引用
   - base & br = d;
3. 派生类对象的地址可以赋值给基类指针
   - base * pb = & d;
4. 如果派生方式是 private或protected，则上述三条不可行。
---
## private继承
>private继承表达的是"根据某物实现出"的关系，即子类通过父类可实现自己成员函数，例如圆形可通过二维点坐标实现自己的一系列方法。
```c++
class drive2 : private base
{
public:
    void access()
    {
        // cout<<priv<<endl;//error!无法访问基类的私有成员
        cout << pro << endl; //ok
        cout << pub << endl; //ok
    }
    drive2() {
        cout << "drive2 constructor called!"<<endl;
    }
};
```
private继承会保留基类非私有成员的可见性全部变为private
```c++
drive2 d2;
// d2.pub;//error
// d2.pubFunc();//error
```
---
## protected继承
protected继承会保留基类非私有成员的可见性全部变为protected
```c++
class drive3 : protected base
{
public:
    void access()
    {
        // cout<<priv<<endl;//error!无法访问基类的私有成员
        cout << pro << endl; //ok
        cout << pub << endl; //ok
    }
    drive3() {
        cout << "drive3 constructor called!"<<endl;
    }
};
drive3 d3;
// d3.pubFunc();//error
```
---
## 派生类的构造
>派生类构造的时候总是先构造基类，即执行基类的构造函数，然后再执行派生类的构造函数。
```c++
drive1 d1;
drive2 d2;
drive3 d3;
---
base constructor called
drive1 constructor called!
base constructor called
drive2 constructor called!
base constructor called
drive3 constructor called!
```
**调用基类构造函数的两种方式**
- 显式方式:
  - 派生类的构造函数中基类的构造函数提供参数
derived::derived(arg_derived-list):base(arg_base-list)
- 隐式方式:
  - 派生类的构造函数中, 省略基类构造函数时
  - 派生类的构造函数, 自动调用基类的默认构造函数
---
## 派生类的析构
>派生类析构的时候总是先执行派生类的析构函数，然后再执行基类的析构函数。
```c++
drive3 d3;
---
base constructor called
drive3 constructor called!
drive3 destructor called
base destructor called
```