# 强制类型转换

## static_cast
- 执行低风险的转换，比如整数，浮点数相互转换。
- 不能再不同类型的指针之间相互转换。
- 不执行运行时类型检查（转换安全性不如 dynamic_cast）
- 可以将子类转化为父类，不能将父类转化为子类

```c++
class A {
public:
    operator char *() {return NULL;}//定义类型转换函数
};
class B:public A {};
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
```

## dynamic_cast
- 用于多态类型的转换，将多态基类的指针或引用转换为派生类的指针或引用
- 对于不安全的转换返回空指针
- 不能用于非多态基类的转换
```c++
class Base
{ //有虚函数，因此是多态基类
public:
    virtual ~Base() {}
};
class Derived : public Base
{
};
int main()
{
    Base b;Derived d;Derived *pd;
    pd = reinterpret_cast<Derived *>(&b);
    if (pd == NULL) //此处pd不会为NULL。
        //reinterpret_cast不检查安全性，总是进行转换
        cout << "unsafe reinterpret_cast" << endl;//不会执行
    pd = dynamic_cast<Derived *>(&b);
    if (pd == NULL)
        //结果会是NULL，因为 &b不是指向派生类对象，此转换不安全
        cout << "unsafe dynamic_cast1" << endl; //会执行
    Base *pb = &d;
    pd = dynamic_cast<Derived *>(pb);           //安全的转换
    if (pd == NULL)                             //此处pd 不会为NULL
        cout << "unsafe dynamic_cast2" << endl; //不会执行
    return 0;
}
```
## const_cast
- 去除常量性（const）转换,只针对指针，引用类型
- 将const指针转成非const指针，const引用转成非const引用
```c++
int main() {
    const int n = 10;
    // int m = const_cast<int>(n);//error
    int& x = const_cast<int&>(n);//ok
    int *y = const_cast<int *>(&n);//ok

}
```
## reinterpret_cast
- 不同类型间的指针转换
- 不同类型的引用转换
- 指针和能装下指针的整数类型间的转换
- 转换的时候是逐比特拷贝
- 不检查转换安全性
```c++
class A
{
public:
    int i;
    int j;
    A(int n) : i(n), j(n) {}
};
int main()
{
    A a(100);
    int &r = reinterpret_cast<int &>(a); //强行让 r 引用 a
    r = 200;                             //把 a.i 变成了 200
    cout << a.i << "," << a.j << endl;   // 输出 200,100
    int n = 300;
    A *pa = reinterpret_cast<A *>(&n); //强行让 pa 指向 n
    pa->i = 400;                       // n 变成 400
    pa->j = 500;                       //此条语句不安全，很可能导致程序崩溃
    cout << n << endl;                 // 输出 400
    long long la = 0x12345678abcdLL;
    pa = reinterpret_cast<A *>(la);                      // la太长，只取低32位0x5678abcd拷贝给pa
    unsigned int u = reinterpret_cast<unsigned int>(pa); //pa逐个比特拷贝到u
    cout << hex << u << endl;                            //输出 5678abcd
    typedef void (*PF1)(int);
    typedef int (*PF2)(int, char *);
    PF1 pf1;
    PF2 pf2;
    pf2 = reinterpret_cast<PF2>(pf1); //两个不同类型的函数指针之间可以互相转换
}
```
