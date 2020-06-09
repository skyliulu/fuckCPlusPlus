# 函数对象


## 什么是函数对象？
若一个类如果重载了运算符 "()"，则该类的对象就成为函数对象。一个典型的函数对象：
```c++
class Mycompare
{
public:
    int operator()(const int &a, const int &b)
    {
        return a > b;
    }
};
```
当然函数类可以定义为模板类
```c++
template <typename T>
class Mycompare2
{
public:
    int operator()(const T &a, const T &b)
    {
        return a < b;
    }
};
```
函数类也可以拥有自己的成员变量，譬如：
```c++
class Mycompare
{
int maxVal;
public:
    int operator()(const int &a, const int &b)
    {
        return a > b;
    }
};
```
## 函数对象使用场景
函数定义了对数据的操作，有了函数对象，我们在泛型编程中可以充分发挥想象力，让算法中的对数据的操作变成我们想要的。
比如对排序算法：
```c++
sort(nums.begin(),nums.end(),Mycompare());//降序排
sort(nums.begin(),nums.end(),Mycompare2<int>());//升序拍
```

## 函数指针
我们可以将函数的入口地址赋给一个指针变量，使该指针变量指向该函数。然后通过指针变量就可以调用这个函数。这种指向函数的指针变量称为“函数指针”。
```c++
template <typename T>
T MyPower( T a, int power) {
    T tmp = a;
    for(int i=0;i<power-1;i++) tmp *= a;
    a = tmp;
    return a;
}
int (* pf)(int,int);
pf = MyPower<int>;
cout << pf(10,2)<<endl;
```

## 函数对象和函数指针的区别
用函数对象代替函数指针有几个优点：
1. 首先，因为对象可以在内部修改而不用改动外部接口，因此设计更灵活，更富有弹性。函数对象也具备有存储先前调用结果的数据成员。在使用普通函数时需要将先前调用的结果存储在全局或者本地静态变量中，但是全局或者本地静态变量有某些我们不愿意看到的缺陷。
2. 其次，在函数对象中编译器能实现内联调用(编译器能内联重载的操作符代码，所以就避免了与函数调用相关的运行时问题)，从而更进一步增强了性能。这在函数指针中几乎是不可能实现的。
3. 模板函数对象: 增加函数对象的通用性。