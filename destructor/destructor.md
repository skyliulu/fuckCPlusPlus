# 析构函数
1. 析构函数在对象消亡时会被自动调用，用于释放内存空间等操作
2. 析构函数与类名相同
3. 没有参数和返回值
4. 不能重载，只能有一个析构函数
5. 没有定义析构函数，编译期会自动生成析构函数，该析构函数不做任何事
```c++
class String
{
private:
    char *p;

public:
    String()
    {
        p = new char[10];
    };
    ~String();
};

String::~String()
{
    delete[] p;
    cout << "destructor called"<<endl;
}
```
- 一个对象生命周期结束时会调用析构函数；
- 如果是对象数组，则数组中的每个对象的析构函数都会被调用;
- 如果是指针类型，需要通过delete来调用析构函数
```c++
int main() {
    String str;
    String strlist[3];
    String * ptr = new String;
    delete ptr;
}
```
输出
```shell
destructor called //str
destructor called //strlist[0]
destructor called //strlist[1]
destructor called //strlist[2]
destructor called //*ptr
```
>同一作用域内，先构造的对象后析构
```c++
class String
{
private:
    int id;

public:
    String(){};
    String(int i);
    String(char ch);
    ~String();
};

String::~String()
{
    cout << id << " destructor called" << endl;
}
String::String(int i)
{
    id = i;
    cout << id << " constructor called" << endl;
};
String::String(char ch)
{
    id = ch - '0';
    cout << id << " constructor called" << endl;
}
int main()
{
    String str1(1);
    str1 = '6';
    if (1)
    {
        String str2(2);
    }
    String str3(3);
}
```
输出
```shell
1 constructor called
6 constructor called 
6 destructor called //赋值是生成的临时变量
2 constructor called
2 destructor called
3 constructor called
3 destructor called
6 destructor called
```


