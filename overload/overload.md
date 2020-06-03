# 重载

## 运算符重载
- c++中预定义的运算符最初只能对基本的数据类型进行操作。
- 对已有的运算符赋予多重的含义。
- 使同一运算符作用于不同类型的数据时，有不同类型的行为。
- 目的扩展C++中提供的运算符的适用范围, 以用于类所表示的抽象数据类型。

**运算符重载需要注意：**
1. 运算符重载不改变运算符的优先级
2. 以下运算符不能被重载： “.”, “.*”, “::”, “?:”, sizeof
3. 重载运算符(), [ ], ->或者赋值运算符=时, 重载函数必须声明
为类的成员函数

---
#### 原理
在程序编译时:
- 把含运算符的表达式 --> 对运算符函数的调用
- 把运算符的操作数 --> 运算符函数的参数
- 运算符被多次重载时, 根据实参的类型决定调用哪个运算符函数

#### 重载为普通函数
>参数个数为运算符目数
```c++
class complex
{
public:
    double r, i;
    complex(double a, double b)
    {
        a = r;
        b = i;
    }
};

complex operator+ (const complex& a,const complex& b) {
    return complex(a.r+b.r,a.i+b.i);
}
int main()
{
    complex a(1,1),b(2,1),c;
    c=a+b;//==>c=operator+(a,b)
}
```
#### 重载为成员函数
>参数个数为运算符目数**减一**
```c++
class complex
{
public:
    double r, i;
    complex(){};
    complex(double a, double b)
    {
        a = r;
        b = i;
    }
    //重载为成员函数
    complex operator-(const complex& b) {
        return complex(r-b.r,i-b.i);
    }
};
int main()
{
    complex a(1,1),b(2,1),c;
    c = a-b;//==>c = a.operator-(b)
}
```
---
### 赋值运算符重载
正常情况下，赋值运算符可作用于自定义的数据类型上，比如定义了一个字符串类：
```c++
class myString
{
    char *str;
    int size;
public:
    myString() : str(NULL),size(0) {}
    myString(const char *s);
    myString(const myString &s);
    void printaddr() { cout << (void *)str << endl; }
    void printstring() { cout << str << endl; }
    int length() {return size;}
    ~myString() { if(str) delete [] str; }
};
```
如果使用=来进行赋值操作会发生什么呢?
```c++
int main()
{
    myString str1("abc"),str2("cde");
    str1.printaddr();//0x7ffff01bce70
    str2.printaddr();//0x7ffff01bce90
    str2 = str1;//浅拷贝
    str2.printstring();//abc
    str1.printaddr();//0x7ffff01bce70
    str2.printaddr();//0x7ffff01bce70
}
```
所以原始的=赋值只会简单把成员变量的值变得相同，这种赋值就是**浅拷贝**，对于上面这个例子，仅仅是将两个指针变得指向同一份数据。这种浅拷贝的方式会有如下问题：
1. 指针原来指向的数据没有被释放，变成垃圾内存。
2. 如果一个指针提前释放内存中的数据，那么另一个指针就会变成野指针。
3. 指针指向内存地址会被释放两次，可能会出现内存错误。

为了避免上述问题，我们需要另一种赋值方式-**深拷贝**。深拷贝是将**指针指向的值**拷贝过去，而不是指针本身。
为了在自己定义的类中实现这个目标，需要我们定义**赋值运算符重载函数**
```c++
myString &myString::operator=(const myString &s)
{
    if (str == s.str)
        return *this;
    if (s.str)
    {
        if (size<s.size)
            if(str) delete[] str;
            str = new char[s.size + 1];
        strcpy(str, s.str);
        size = strlen(s.str);
    }
    else
    {
        str = NULL;
        size = 0;
    }
    return *this;
}
int main()
{
    myString str1("abc"),str2("cde");
    str1.printaddr();//0x7fffd11c0e70
    str2.printaddr();//0x7fffd11c0e90
    str2 = str1;//浅拷贝
    str2.printstring();//abc
    str1.printaddr();//0x7fffd11c0e70
    str2.printaddr();//0x7fffd11c0e90
}
```
这里将返回值定义为myString&是为了能实现连续赋值，考虑以下情形：
```c++
myString str1("abc"),str2("cde"),str3("efg");
(str1 = str2) = str3;
//(str1.opreator=(str2)).opreator=(str3)
str1.printstring();//efg
```
第一次赋值为str1=str2,其返回值我们暂记作xxx;
第二次赋值为xxx=str3;
这段代码的目的是将str3的值赋给str1，如果返回值不为引用myString&，那么xxx就是一个临时产生对象，不会对str1有任何影象。
### []运算符重载
>[]运算重载需要注意返回值的类型，应当返回引用类型，这样才可以去修改数组指定下标的值。
```c++
char& myString::operator[](int i) {
    return str[i];
}
int main()
{
    myString str1("abc");
    cout<<str1[1]<<endl;//a
    str1[0]='9';
    str1.printstring();//abc
}
```
---
### <<和>>运算符重载
运算符<<和运算符>>原始含义是二进制算数左移和二进制算术右移，在ostream类和istream类中将他们重载为输出流和输入流。
```c++
ostream & ostream::operator<<(int n)
{
    …… //输出n的代码
    return * this;
}
istream & istream::operator>>(int& n)
{
    …… //输入s的代码
    return * this;
}
```
可以看到返回值均为ostream和istream类的引用，这里为了能实现输出/输入拼接。
```c++
cout<<"hello"<<"world";
```
那么如果想用ostream或istream对我们自定义的myString类执行输入输出是否可行呢？
```c++
myString str("hello");
cout <<str<<endl;//error
```
显然不行，因为ostream类中并没有将<<重载为适合myString类的输出函数，所以需要我们自己重载<<运算符，显然我们无法在ostream的成员函数中重载，因此我们只能重载一个普通的全局函数。为了方便访问对象中的私有数据，声明为友元函数。
```c++
class myString
{
    char *str;
    int size;
public:
    ...
    friend ostream& operator<<(ostream& out,const myString& s);
    friend istream& operator>>(istream& in,myString& s);
};
ostream& operator<<(ostream& out,const myString& s) {
    out<<s.str;
    return out;
}
istream& operator>>(istream& in,myString& s) {
    if(!s.str) {
        s.str = new char[20];
    }
    in >>s.str;
    return in;
}
```
这样便可以使用cin和cout来自输入输出了
```c++
myString str;
cin >> str;
cout<<str<<endl;
```
---
### ++和--运算符重载
++和--运算符有前置/后置之分，即++i和i++是有区别的。
- 前置是一元运算符：++i/--i
  - 重载为成员函数:
    - T & operator++();
    - T & operator--();
  - 重载为全局函数：
    - T & operator++(T &);
    - T & operator--(T &);
- 后置运算符作为二元运算符重载:i++/i--
  - 多写一个参数, 仅为了区分前后置，具体无意义
  - 重载为成员函数:
    - T operator++(int);
    - T operator--(int);
  - 重载为全局函数:
    - T operator++(T &, int);
    - T operator--(T &, int);



