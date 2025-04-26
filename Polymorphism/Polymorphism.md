# 多态与虚函数
>在面向对象的程序设计中使用多态，能够增强程序的可扩充性，即程序需要修改或增加功能的时候，需要改动和增加的代码较少。

## 多态
派生类的指针可以赋给基类指针。
通过基类指针调用基类和派生类中的同名虚函数时:
- 若该指针指向一个基类的对象，那么被调用是基类的虚函数；
- 若该指针指向一个派生类的对象，那么被调用的是派生类的虚函数。
<!--more-->
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
C++给每个声明虚函数的类增加隐藏成员——虚函数表指针（vptr）。虚函数表指针指向一个函数地址数组，这个数组被成为虚函数表（vtable）。虚函数表中存储了类对象声明的虚函数的地址。虚函数表在编译期创建的。
基类包含一个虚函数指针vptr1指向虚函数表vtable1，则派生类类将包含指向独立地址表的指针vptr2（不管有没有声明虚函数）指向虚函数表vtable2。
1. 如果派生类提供了基类虚函数的新定义，vfpt2将保存新的函数地址（在vtable1基础上覆盖）;
2. 如果派生类声明了新的虚函数，vtable2将添加该函数地址（在vtable1基础上添加）;
3. 如果派生类仅仅是继承基类的虚函数，那么vtable2将保留原始函数地址（和vtable1保持一致）。

#### 拥有虚函数的基类base
```c++
class base
{
    int a;
public:
    base() { baseFunc1(); } //没有多态
    virtual void baseFunc1() { cout << "base" << endl; }
    virtual void baseFunc2() { cout << "base" << endl; }
    void func() { baseFunc1(); } //多态
};
```
创建一个base类的实例A，则A在内存中的布局：
```s
A = {_vptr.base = 0x8201cb0 <vtable for base+16>, a = -20237175}
(gdb) p sizeof(A)
$3 = 16
```
可以看到A的第一个成员为虚函数表指针vptr，vptr并不是指向vtable的起始处，而是<vtable for base+16>处，即在vtable表头的16偏移处，为了方便我们打印0x8201cb0-16处的内存：
```s
(gdb) x /100b 0x8201cb0-16
0x8201ca0 <_ZTV4base>:  0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
0x8201ca8 <_ZTV4base+8>:        0x78    0x1d    0x20    0x08    0x00    0x00    0x00    0x00
0x8201cb0 <_ZTV4base+16>:       0x64    0x0f    0x00    0x08    0x00    0x00    0x00    0x00
0x8201cb8 <_ZTV4base+24>:       0x9c    0x0f    0x00    0x08    0x00    0x00    0x00    0x00
```
ZTV4base是指vtable for base，即base类的虚函数表。可以看到base的vtable一共占36字节，具体内容如下：
```s
(gdb) x /w 0x8201ca0
0x8201ca0 <_ZTV4base>:  0x00000000
(gdb) x /w 0x8201ca8
0x8201ca8 <_ZTV4base+8>:        0x08201d78
(gdb) x 0x08201d78
0x8201d78 <_ZTI4base>:  0xff3ea7f8
(gdb) x /w 0x8201cb0
0x8201cb0 <_ZTV4base+16>:       0x08000f64
(gdb) x 0x08000f64
0x8000f64 <base::Func1()>:      0xe5894855
(gdb) x /w 0x8201cb8
0x8201cb8 <_ZTV4base+24>:       0x08000f9c
(gdb) x 0x08000f9c
0x8000f9c <base::Func2()>:      0xe5894855
```
这里ZTI4base指typeinfo of base类，即base的类型声明信息。
```s
                   0x8201ca0-->+-----------------------+
                               |     0 (top_offset)    |             
                               +-----------------------+
A --> +----------+ 0x8201cb0   | ptr to typeinfo for A |
      |   vptr   |-----------> +-----------------------+
      +----------+             | ptr to base::Func1()  |
      |     a    |             +-----------------------+
      +----------+             | ptr to base::Func2()  |
                               +-----------------------+
```
#### 继承base但没有声明/重写`虚函数的派生类drive
```c++
class drive : public base
{
    int a;
};
```
创建一个drive类的实例B，则B在内存中的布局：
```s
(gdb) p B
$7 = {<base> = {_vptr.base = 0x8201c90 <vtable for drive
(gdb) p sizeof(B)
$8 = 16
```
可以看到B的第一个成员为虚函数表指针vptr,注意到vptr和base没有声明或重写任何一个虚函数,但是编译期仍为drive生成了新的虚函数表。我们打印0x8201c90
```s
(gdb) x /100b 0x8201c90-16
0x8201c80 <_ZTV5drive>: 0x00    0x00    0x00    0x00    
0x8201c88 <_ZTV5drive+8>:       0x60    0x1d    0x20     0x00
0x8201c90 <_ZTV5drive+16>:      0x64    0x0f    0x00     0x00
0x8201c98 <_ZTV5drive+24>:      0x9c    0x0f    0x00     0x00
0x8201ca0 <_ZTV4base>:  0x00    0x00    0x00    0x00    
8201ca8 <_ZTV4base+8>:        0x78    0x1d    0x20    0xx00
0x8201cb0 <_ZTV4base+16>:       0x64    0x0f    0x00     0x00
0x8201cb8 <_ZTV4base+24>:       0x9c    0x0f    0x00     0x00
```
_ZTV5drive是指vtable for drive，即drive类的虚函数表。可且drive的虚函数表其后紧跟着base的虚函数表。drive的虚函数表具体内容如下：
```s
(gdb) x /w 0x8201c80
0x8201c80 <_ZTV5drive>: 0x00000000
(gdb) x /w 0x8201c88
0x8201c88 <_ZTV5drive+8>:       0x08201d60
(gdb) x /w 0x8201c90
0x8201c90 <_ZTV5drive+16>:      0x08000f64
(gdb) x /w 0x8201c98
0x8201c98 <_ZTV5drive+24>:      0x08000f9c
(gdb) x /w 0x08201d60
0x8201d60 <_ZTI5drive>: 0xff3eb438
(gdb) x /w 0x08000f64
0x8000f64 <base::Func1()>:      0xe5894855
(gdb) x /w 0x08000f9c
0x8000f9c <base::Func2()>:     0xe5894855
```
```s
                   0x8201c80-->+-----------------------+
                               |     0 (top_offset)    |
                               +-----------------------+
B --> +----------+ 0x8201c90   | ptr to typeinfo for B |
      |   vptr   |-----------> +-----------------------+
      +----------+             | ptr to base::Func1()  |
      |   A::a   |             +-----------------------+
      +----------+             | ptr to base::Func2()  |
      |   B::a   |             +-----------------------+
      +----------+           
```

#### 继承base且重写base类虚函数的派生类drive1
```c++
class drive1 : public base
{
    int b;
public:
    //不加virtual也是虚函数，只要基类中是虚函数且同名同参数
    void baseFunc2() { cout << "drive1" << endl; }
    virtual void baseFunc1() { cout << "drive1" << endl; }
};
```
创建一个drive类的实例B，则B在内存中的布局：
```s
(gdb) p C
$11 = {<base> = {_vptr.base = 0x8201c70 <vtable for drive1+16>, a = 136321944}, b = 0}
(gdb) p sizeof(C)
$12 = 16
```
可以看到C的第一个成员为虚函数表指针vptr,注意到vptr和base的vptr不一样。这说明编译器给drive1生产了新的虚函数表,0x8201c70-16处的内存：
```s
(gdb) x /100b 0x8201c70-16
0x8201c60 <_ZTV6drive1>:        0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
0x8201c68 <_ZTV6drive1+8>:      0x48    0x1d    0x20    0x08    0x00    0x00    0x00    0x00
0x8201c70 <_ZTV6drive1+16>:     0x0c    0x10    0x00    0x08    0x00    0x00    0x00    0x00
0x8201c78 <_ZTV6drive1+24>:     0xd4    0x0f    0x00    0x08    0x00    0x00    0x00    0x00
0x8201c80 <_ZTV5drive>: 0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
```
_ZTV6drive1是指vtable for drive1，即drive1类的虚函数表。drive1的虚函数表具体内容如下：
```s
(gdb) x /w 0x8201c60
0x8201c60 <_ZTV6drive1>:        0x00000000
(gdb) x /w 0x8201c68
0x8201c68 <_ZTV6drive1+8>:      0x08201d48
(gdb) x /w 0x08201d48
0x8201d48 <_ZTI6drive1>:        0xff3eb438
(gdb) x /w 0x8201c70
0x8201c70 <_ZTV6drive1+16>:     0x0800100c
(gdb) x /w 0x0800100c
0x800100c <drive1::Func1()>:    0xe5894855
(gdb) x /w 0x8201c78
0x8201c78 <_ZTV6drive1+24>:     0x08000fd4
(gdb) x /w 0x08000fd4
0x8000fd4 <drive1::Func2()>:    0xe5894855
```
```s
                   0x8201c60-->+------------------------+
                               |     0 (top_offset)     |             
                               +------------------------+
C --> +----------+ 0x8201c70   | ptr to typeinfo for C  |
      |   vptr   |-----------> +------------------------+
      +----------+             | ptr to drive1::Func1() |
      |   A::a   |             +------------------------+
      +----------+             | ptr to drive1::Func2() |
      |   C::b   |             +------------------------+
      +----------+           
```
可以看到drive1的虚函数表中的Func1()和Func2()的函数地址被覆盖为drive1定义的函数。

#### 继承base且声明新的虚函数的派生类drive2
```c++
class drive2 : public base
{
    int b;
public:
    virtual void Func3() {}
};
```
创建一个drive类的实例B，则B在内存中的布局：
```s
$3 = {<base> = {_vptr.base = 0x8201c48 <vtable for drive2+16>, a = 134221601}, b = 0}
(gdb) p sizeof(D)
$4 = 16
```
可以看到D的第一个成员为虚函数表指针vptr,注意到vptr和base的vptr不一样。这说明编译器给drive2生产了新的虚函数表,0x8201c48-16处的内存：
```s
(gdb) x /100b 0x8201c48-16
0x8201c38 <_ZTV6drive2>:        0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
0x8201c40 <_ZTV6drive2+8>:      0x30    0x1d    0x20    0x08    0x00    0x00    0x00    0x00
0x8201c48 <_ZTV6drive2+16>:     0x64    0x0f    0x00    0x08    0x00    0x00    0x00    0x00
0x8201c50 <_ZTV6drive2+24>:     0x9c    0x0f    0x00    0x08    0x00    0x00    0x00    0x00
0x8201c58 <_ZTV6drive2+32>:     0x44    0x10    0x00    0x08    0x00    0x00    0x00    0x00
0x8201c60 <_ZTV6drive1>:        0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
```
drive2的虚函数表具体内容如下：
```s
(gdb) x /w 0x8201c38
0x8201c38 <_ZTV6drive2>:        0x00000000
(gdb) x /w 0x8201c40
0x8201c40 <_ZTV6drive2+8>:      0x08201d30
(gdb) x /w 0x08201d30
0x8201d30 <_ZTI6drive2>:        0xff3eb438
(gdb) x /w 0x8201c48
0x8201c48 <_ZTV6drive2+16>:     0x08000f64
(gdb) x /w 0x08000f64
0x8000f64 <base::Func1()>:      0xe5894855
(gdb) x /w 0x8201c50
0x8201c50 <_ZTV6drive2+24>:     0x08000f9c
(gdb) x /w 0x08000f9c
0x8000f9c <base::Func2()>:      0xe5894855
(gdb) x /w 0x8201c58
0x8201c58 <_ZTV6drive2+32>:     0x08001044
(gdb) x /w 0x08001044
0x8001044 <drive2::Func3()>:    0xe5894855
```
```s
                   0x8201c38-->+------------------------+
                               |     0 (top_offset)     |             
                               +------------------------+
D --> +----------+ 0x8201c48   | ptr to typeinfo for D  |
      |   vptr   |-----------> +------------------------+
      +----------+             | ptr to base::Func1()   |
      |   A::a   |             +------------------------+
      +----------+             | ptr to base::Func2()   |
      |   D::b   |             +------------------------+
      +----------+             | ptr to drive2::Func3() |
                               +------------------------+ 
```                     
可以看到drive1的虚函数表中的Func1()和Func2()的函数地址被
#### 继承drive和drive1的派生类moreDrive
```c++
class moreDrive : public drive,drive1
{
    int b;
};
```
创建一个moreDrive类的实例E，则E在内存中的布局：
```s
(gdb) p E
$5 = {<drive> = {<base> = {_vptr.base = 0x8201c08 <vtable for moreDrive+16>, a = 65535}, a = 1}, <drive1> = {<base> = {_vptr.base = 0x8201c28 <vtable for moreDrive+48>, a = 134221623}, b = 0}, b = 2}
(gdb) p sizeof(E)
$7 = 40
```
可以看到有2个虚函数表指针，但是这两个指针指向的是同一个虚数表，只不过这两个指针相对表头的偏移不一样。0x8201c08-16处的内存：
```s
(gdb) x /100w 0x8201c08-16
0x8201bf8 <_ZTV9moreDrive>:     0x00000000      0x00000000      0x08201cf8      0x00000000
0x8201c08 <_ZTV9moreDrive+16>:  0x08000f64      0x00000000      0x08000f9c      0x00000000
0x8201c18 <_ZTV9moreDrive+32>:  0xfffffff0      0xffffffff      0x08201cf8      0x00000000
0x8201c28 <_ZTV9moreDrive+48>:  0x0800100c      0x00000000      0x08000fd4      0x00000000
```
moreDrive的虚函数表具体内容如下：
```s
(gdb) x /w 0x08201cf8
0x8201cf8 <_ZTI9moreDrive>:     0xff3eb4f8
(gdb) x /w 0x08000f64
0x8000f64 <base::Func1()>:      0xe5894855
(gdb) x /w 0x08000f9c
0x8000f9c <base::Func2()>:      0xe5894855
(gdb) p /d 0xfffffff0
$8 = -16
(gdb) x /w 0x0800100c
0x800100c <drive1::Func1()>:    0xe5894855
(gdb) x /w 0x08000fd4
0x8000fd4 <drive1::Func2()>:    0xe5894855
```
```s
                   0x8201bf8-->+------------------------+
                               |     0 (top_offset)     |             
                               +------------------------+
E --> +----------+ 0x8201c08   | ptr to typeinfo for E  |
      |   vptr   |-----------> +------------------------+
      +----------+             | ptr to base::Func1()   |
      | base::a  |             +------------------------+
      +----------+             | ptr to base::Func2()   |
      | drive::a |             +------------------------+
      +----------+             |     -16 (top_offset)   |
      |   vptr   |--           +------------------------+
      +----------+ | 0x8201c28 | ptr to typeinfo for E  |
      | base::a  | ----------> +------------------------+
      +----------+             | ptr to drive1::Func1() |
      | drive1::b|             +------------------------+
      +----------+             | ptr to drive1::Func2() |
      |    b     |             +------------------------+
      +----------+
``` 
#### 继承drive1和drive2的派生类moreDrive1
```c++
class moreDrive1 : public drive1,drive2
{
    int b;
};
```
创建一个moreDrive1类的实例F，则F在内存中的布局：
```s
(gdb) p F
$1 = {<drive1> = {<base> = {_vptr.base = 0x8201bc0 <vtable for moreDrive1+16>, a = 0}, b = 0}, <drive2> = {<base> = {_vptr.base = 0x8201be0 <vtable for moreDrive1+48>, 
      a = 134221120}, b = 0}, b = -75408}
(gdb) p sizeof(F)
$2 = 40
```
可以看到有2个虚函数表指针，指向的是同一个虚数表，只不过这两个指针相对表头的偏移不一样。0x8201bc0-16处的内存：
```s
(gdb) x /100w 0x8201bc0-16
0x8201bb0 <_ZTV10moreDrive1>:           0x00000000      0x00000000      0x08201cc0      0x00000000
0x8201bc0 <_ZTV10moreDrive1+16>:        0x0800100c      0x00000000      0x08000fd4      0x00000000
0x8201bd0 <_ZTV10moreDrive1+32>:        0xfffffff0      0xffffffff      0x08201cc0      0x00000000
0x8201be0 <_ZTV10moreDrive1+48>:        0x08000f64      0x00000000      0x08000f9c      0x00000000
0x8201bf0 <_ZTV10moreDrive1+64>:        0x08001044      0x00000000      0x00000000      0x00000000
```
```s
                   0x8201bb0-->+------------------------+
                               |     0 (top_offset)     |             
                               +------------------------+
F --> +----------+ 0x8201bc0   | ptr to typeinfo for F  |
      |   vptr   |-----------> +------------------------+
      +----------+             | ptr to drive1::Func1() |
      | base::a  |             +------------------------+
      +----------+             | ptr to drive1::Func2() |
      | drive1::b|             +------------------------+
      +----------+             |     -16 (top_offset)   |
      |   vptr   |--           +------------------------+
      +----------+ | 0x8201be0 | ptr to typeinfo for F  |
      | base::a  | ----------> +------------------------+
      +----------+             | ptr to base::Func1()   |
      | drive2::b|             +------------------------+
      +----------+             | ptr to base::Func2()   |
      |    b     |             +------------------------+
      +----------+             | ptr to drive2::Func3() |
                               +------------------------+
``` 
#### 更进一步
#### 继承drive, drive1和drive2的派生类moreDrive2
```c++
class moreDrive2 : public drive,drive1,drive2
{
    int c;
};
```
```s
(gdb) p G
$1 = {<drive> = {<base> = {_vptr.base = 0x8201b10 <vtable for moreDrive2+16>, a = 134222733}, a = 0}, <drive1> = {<base> = {
      _vptr.base = 0x8201b30 <vtable for moreDrive2+48>, a = 0}, b = 0}, <drive2> = {<base> = {_vptr.base = 0x8201b50 <vtable for moreDrive2+80>, a = 134221472}, 
    b = 0}, c = -75456}
(gdb) p sizeof(G)
$2 = 56
```
可以看到有3个虚函数表指针，指向的是同一个虚数表。0x8201b10-16处的内存：
```s
(gdb) x /100w 0x8201b10-16
0x8201b00 <_ZTV10moreDrive2>:           0x00000000      0x00000000      0x08201c78      0x00000000
0x8201b10 <_ZTV10moreDrive2+16>:        0x080010d8      0x00000000      0x08001110      0x00000000
0x8201b20 <_ZTV10moreDrive2+32>:        0xfffffff0      0xffffffff      0x08201c78      0x00000000
0x8201b30 <_ZTV10moreDrive2+48>:        0x08001180      0x00000000      0x08001148      0x00000000
0x8201b40 <_ZTV10moreDrive2+64>:        0xffffffe0      0xffffffff      0x08201c78      0x00000000
0x8201b50 <_ZTV10moreDrive2+80>:        0x080010d8      0x00000000      0x08001110      0x00000000
0x8201b60 <_ZTV10moreDrive2+96>:        0x080011b8      0x00000000
```

```s
                   0x8201b00-->+------------------------+
                               |     0 (top_offset)     |             
                               +------------------------+
G --> +----------+ 0x8201b10   | ptr to typeinfo for G  |
      |   vptr   |-----------> +------------------------+
      +----------+             | ptr to base::Func1()   |
      | base::a  |             +------------------------+
      +----------+             | ptr to base::Func2()   |
      | drive::a |             +------------------------+
      +----------+             |     -16 (top_offset)   |
      |   vptr   |--           +------------------------+
      +----------+ | 0x8201b30 | ptr to typeinfo for G  |
      | base::a  | ----------> +------------------------+
      +----------+             | ptr to drive1::Func1() |
      | drive1::b|             +------------------------+
      +----------+             | ptr to drive1::Func2() |
      |   vptr   |--           +------------------------+
      +----------+ |           |     -32 (top_offset)   |
      | base::a  | |0x8201b50  +------------------------+
      +----------+ ----------> | ptr to typeinfo for G  |
      | drive2::b|             +------------------------+
      +----------+             | ptr to base::Func1()   |
      |    c     |             +------------------------+
      +----------+             | ptr to base::Func2()   |
                               +------------------------+
                               | ptr to drive2::Func3() |
                               +------------------------+
```
**如果我们将继承的父类换一下顺序呢？**
```c++
class moreDrive2 : public drive1,drive2,drive
{
    int c;
};
```
```s
(gdb) p /x
$2 = {<drive1> = {<base> = {_vptr.base = 0x8201b10 <vtable for moreDrive2+16>, a = 0x800138d}, b = 0x0}, <drive2> = {<base> = {
      _vptr.base = 0x8201b30 <vtable for moreDrive2+48>, a = 0x0}, b = 0x0}, <drive> = {<base> = {_vptr.base = 0x8201b58 <vtable for moreDrive2+88>, a = 0x8000ea0}, 
    a = 0x0}, c = 0xfffed940}
```
```s
(gdb) x /100w 0x8201b10-16
0x8201b00 <_ZTV10moreDrive2>:           0x00000000      0x00000000      0x08201c78      0x00000000
0x8201b10 <_ZTV10moreDrive2+16>:        0x08001180      0x00000000      0x08001148      0x00000000
0x8201b20 <_ZTV10moreDrive2+32>:        0xfffffff0      0xffffffff      0x08201c78      0x00000000
0x8201b30 <_ZTV10moreDrive2+48>:        0x080010d8      0x00000000      0x08001110      0x00000000
0x8201b40 <_ZTV10moreDrive2+64>:        0x080011b8      0x00000000      0xffffffe0      0xffffffff
0x8201b50 <_ZTV10moreDrive2+80>:        0x08201c78      0x00000000      0x080010d8      0x00000000
0x8201b60 <_ZTV10moreDrive2+96>:        0x08001110      0x00000000      
```
```s
                   0x8201b00-->+------------------------+
                               |     0 (top_offset)     |             
                               +------------------------+
G --> +----------+ 0x8201b10   | ptr to typeinfo for G  |
      |   vptr   |-----------> +------------------------+
      +----------+             | ptr to drive1::Func1() |
      | base::a  |             +------------------------+
      +----------+             | ptr to drive1::Func2() |
      | drive1::b|             +------------------------+
      +----------+             |     -16 (top_offset)   |
      |   vptr   |--           +------------------------+
      +----------+ | 0x8201b30 | ptr to typeinfo for G  |
      | base::a  | ----------> +------------------------+
      +----------+             | ptr to base::Func1()   |
      | drive2::b|             +------------------------+
      +----------+             | ptr to base::Func2()   |
      |   vptr   |--           +------------------------+
      +----------+ |           | ptr to drive2::Func3() |
      | base::a  | |           +------------------------+
      +----------+ |           |     -32 (top_offset)   |
      | drive::a | |           +------------------------+
      +----------+ | 0x8201b58 | ptr to typeinfo for G  |
      |    c     | ----------->+------------------------+
      +----------+             | ptr to base::Func1()   |
                               +------------------------+
                               | ptr to base::Func2()   |
                               +------------------------+
```
可以看到虚函数表中各个类的成员函数的顺序和声明类的时候父类顺序是一致的。

```c++
class moreDrive2 : public drive1, drive2, drive
{
    int c;

public:
    virtual void Func4() {}
};
```
```s
(gdb) p G
$1 = {<drive1> = {<base> = {_vptr.base = 0x8201b08 <vtable for moreDrive2+16>, a = 134222781}, b = 0}, <drive2> = {<base> = {
      _vptr.base = 0x8201b30 <vtable for moreDrive2+56>, a = 0}, b = 0}, <drive> = {<base> = {_vptr.base = 0x8201b58 <vtable for moreDrive2+96>, a = 134221504}, a = 0}, 
  c = -75472}
(gdb) p sizeof(G)
$2 = 56
```
```s
(gdb) x /100w 0x8201b08-16
0x8201af8 <_ZTV10moreDrive2>:           0x00000000      0x00000000      0x08201c78      0x00000000
0x8201b08 <_ZTV10moreDrive2+16>:        0x080011a0      0x00000000      0x08001168      0x00000000
0x8201b18 <_ZTV10moreDrive2+32>:        0x080011e4      0x00000000      0xfffffff0      0xffffffff
0x8201b28 <_ZTV10moreDrive2+48>:        0x08201c78      0x00000000      0x080010f8      0x00000000
0x8201b38 <_ZTV10moreDrive2+64>:        0x08001130      0x00000000      0x080011d8      0x00000000
0x8201b48 <_ZTV10moreDrive2+80>:        0xffffffe0      0xffffffff      0x08201c78      0x00000000
0x8201b58 <_ZTV10moreDrive2+96>:        0x080010f8      0x00000000      0x08001130      0x00000000
```
```s
                   0x8201af8-->+----------------------------+
                               |     0 (top_offset)         |             
                               +----------------------------+
G --> +----------+ 0x8201b08   | ptr to typeinfo for G      |
      |   vptr   |-----------> +----------------------------+
      +----------+             | ptr to drive1::Func1()     |
      | base::a  |             +----------------------------+
      +----------+             | ptr to drive1::Func2()     |
      | drive1::b|             +----------------------------+
      +----------+             | ptr to moredrive2::Func4() |
      |   vptr   |--           +----------------------------+
      +----------+ |           |     -16 (top_offset)       |
      | base::a  | |           +----------------------------+
      +----------+ | 0x8201b30 | ptr to typeinfo for G      |
      | drive2::b| ----------> +----------------------------+
      +----------+             | ptr to base::Func1()       |
      |   vptr   |--           +----------------------------+
      +----------+ |           | ptr to base::Func2()       |
      | base::a  | |           +----------------------------+
      +----------+ |           | ptr to drive2::Func3()     |
      | drive::a | |           +----------------------------+
      +----------+ |           |     -32 (top_offset)       |
      |    c     | |           +----------------------------+
      +----------+ | 0x8201b58 | ptr to typeinfo for G      |
                   ----------->+----------------------------+
                               | ptr to base::Func1()       |
                               +----------------------------+
                               | ptr to base::Func2()       |
                               +----------------------------+
                                                                  
```
可以看到派生类新定义的虚函数会放在第一个基类的虚函数后面。
#### 问题
**top_offset有何用处？**


### 使用虚函数需要注意
1. **构造函数可以是虚函数吗?**
不可以。
- 虚函数表指针vptr是调用构造函数时创建的。
- 如果构造函数是虚的，那么调用构造函数时需要通过vptr来访问vtable。
- 所以构造函数显然不能为虚函数。
2. **析构函数可以是虚函数吗?**
可以。
- 如果我们需要删除一个指向派生类的基类指针时，应该把析构函数声明为虚函数。 
- 如果一个类有可能会被其它类所继承， 就应该声明虚析构函数。否则析构时派生类的成员变量会被遗漏。
3. **静态成员函数可以是虚函数吗?**
**不可以。**
- static成员函数不属于任何类对象，所以即使给此函数加上virutal也是没有任何意义。
- 虚函数依靠vptr和vtable来处理。vptr是一个指针，在类的构造函数中创建生成，并且只能用this指针来访问它，静态成员函数没有this指针，所以无法访问vptr。
4. **友元函数可以是虚函数吗?**
不可以。
- 友元函数不能继承。
5. **虚函数可以被内联吗？**
- 虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。
- 内联是在编译器建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。

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
<!-- - 在成员函数内可以调用纯虚函数 -->
- 在构造函数/析构函数内部不能调用纯虚函数，**为什么？**
  - 纯虚函数在抽象基类中声明，但没有在类本身中提供实现 (= 0)。它的实现必须由派生类提供
  - 如果在构造函数或析构函数中调用纯虚函数，由于在当前正在执行的构造函数或析构函数所属的类中没有该纯虚函数的实现，就没有实际的代码可以执行。
  - 在构造阶段，派生类的部分尚未构造，其提供的纯虚函数实现不可用。
  - 在析构阶段，派生类的部分已经被销毁，其提供的纯虚函数实现也已不可用

### 虚函数的开销和优化
虚函数在 C++ 中是实现多态性的重要机制，但它们确实会带来一定的开销。理解这些开销以及如何进行优化对于编写高性能的 C++ 代码至关重要。

**虚函数的开销主要体现在以下几个方面：**

1.  **内存开销：**
    * **虚函数表 (vtable)：** 每一个包含虚函数的类都会有一个虚函数表。这个表存储了该类及其基类中虚函数的地址。
    * **虚函数指针 (vptr)：** 每一个包含虚函数的类的对象都会有一个指向其对应 vtable 的指针。这个指针通常占用对象内存空间的一部分（通常是一个指针的大小）。
    * 对于有很多类和很多虚函数的复杂继承体系，vtable 会占用额外的内存空间。对于创建大量对象的场景，每个对象额外的 vptr 也会增加内存占用。

2.  **调用开销：**
    * **间接调用：** 调用虚函数不像普通函数那样是直接调用地址，而是通过 vptr 查找 vtable，然后根据虚函数在 vtable 中的偏移量找到对应的函数地址进行间接调用。这比直接函数调用多了一些步骤。
    * **分支预测失败：** 间接调用地址在编译时通常是不确定的，这会干扰处理器的分支预测。如果分支预测失败，会导致流水线中断，带来性能损失。
    * **缓存未命中：** 访问 vtable 和实际的虚函数代码可能会导致缓存未命中，尤其是在处理大量分散在内存中的多态对象时。

3.  **编译器优化受限：**
    * **内联限制：** 编译器很难内联虚函数调用，因为在编译时无法确定具体会调用哪个函数实现。内联是编译器重要的优化手段之一，它可以消除函数调用的开销，并将函数体直接嵌入到调用处，从而 enabling 更多的上下文相关的优化。虚函数的动态绑定特性限制了这种优化。
    * **其他优化受限：** 虚函数的存在也可能限制编译器进行其他一些优化，例如常量传播和死代码消除等。

**然而，需要强调的是，虚函数的开销在很多情况下是可接受的，尤其是在函数体本身比较复杂或者不是在紧密的循环中频繁调用的情况下。与虚函数带来的设计灵活性和可扩展性相比，这点开销往往是值得的。**

**虚函数的优化：**

虽然虚函数本身带来开销，但编译器和程序员都可以采取一些措施来减轻或优化这些开销：

1.  **编译器优化：**
    * **去虚化 (Devirtualization)：** 在某些情况下，编译器可以通过静态分析确定虚函数调用的实际目标函数，从而将虚函数调用转换为直接调用。这通常发生在对象类型已知（例如，通过对象本身而不是指针或引用调用虚函数），或者当类被声明为 `final` 时（C++11 引入），因为 `final` 类不能被继承，其虚函数不会再被重写。
    * **Devirtualization Enabled by LTO (Link Time Optimization)：** 链接时优化可以跨越编译单元进行分析，从而在更广的范围内实现去虚化。
    * **分支预测改进：** 现代处理器有先进的分支预测硬件，可以在一定程度上减轻虚函数调用的分支预测失败带来的损失。

2.  **程序员层面的优化：**
    * **避免在性能关键的紧密循环中频繁调用虚函数：** 如果某个操作需要在性能敏感的循环中重复执行，并且涉及多态性，可以考虑其他实现方式，例如使用非虚函数配合 `if/else` 或 `switch`，或者使用基于模板的技术（例如 CRTP - Curiously Recurring Template Pattern）来避免运行时多态的开销。
    * **减小虚函数的大小：** 如果虚函数体非常小，其调用开销相对于函数本身的执行时间就会显得更突出。对于非常小的可能被频繁调用的函数，考虑将其设计为非虚函数。
    * **使用 `final` 关键字：** 如果确定一个类不会被继承，或者一个虚函数不会在派生类中被重写，使用 `final` 关键字可以帮助编译器进行去虚化优化。
    * **数据局部性优化：** 尽量将相关联的对象存储在连续的内存区域，这有助于改善缓存的利用率，减轻虚函数调用可能带来的缓存未命中问题。例如，使用 `std::vector<Object>` 而不是 `std::vector<Object*>` 或 `std::vector<Base*>` (当多态性不是绝对必要时)。如果必须使用指针或引用，考虑按类型对对象进行分组存储，以提高访问同一类型对象的局部性。
    * **考虑非多态设计：** 在某些情况下，如果多态性不是设计的核心需求，可以考虑使用其他设计模式来避免虚函数，例如策略模式配合函数指针或 `std::function`。

**总结：**

虚函数确实存在一定的开销，包括额外的内存占用（vtable 和 vptr）以及调用时的间接性和对编译器优化的限制。然而，这些开销通常是可以接受的，并且编译器和程序员都可以采取措施来减轻其影响。在进行性能优化时，应该首先关注算法和数据结构的效率，以及避免不必要的对象创建和内存分配。只有在确定虚函数是性能瓶颈时，才需要考虑针对虚函数本身的优化。过早地避免使用虚函数可能会导致代码的可读性、可维护性和可扩展性下降。
