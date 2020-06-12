# 引用和指针

## 引用
>变量的引用等价于该变量，引用就是变量的别名
```c++
int n = 4;
int &ref = n;//ref引用n
cout <<ref<<endl;//4
n = 5;//改变n
cout<<ref<<endl;//5
int &ref2 = ref;
cout<<ref2<<endl;//5
```
>引用必须初始化为某个变量
```c++
int &ref2 = 2;//常量，error
int &ref3 = n*5;//表达式，error
```
>引用不能更换引用其他变量
```c++
int &ref = n;//ref引用n
int m = 6;
ref = m;//ok,赋值操作
ref = &m;//error
```
### 常引用
>不能通过常引用去修改其引用的内容
```c++
const int &c_ref = n;
int &ref3 = n;
c_ref = 9;//error,常引用
ref3 = 9;//ok,ref3不是常引用
```
### 左值引用和右值引用
>本节转自[https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/]

右值引用 (Rvalue Referene) 是 C++11中引入的新特性 , 它实现了转移语义 (Move Sementics) 和精确传递 (Perfect Forwarding)。它的主要目的有两个方面：
1. 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率。
2. 能够更简洁明确地定义泛型函数

>C++( 包括 C) 中所有的表达式和变量要么是左值，要么是右值。通俗的左值的定义就是非临时对象，那些可以在多条语句中使用的对象。所有的变量都满足这个定义，在多条代码中都可以使用，都是左值。右值是指临时的对象，它们只在当前的语句中有效。
```c++
int i = 0;//0是右值，i是左值
i>10?i:j;//10是右值,i,j是左值
```
c++11之前是无法引用右值的，c++11之后变支持引用右值。为了和左值引用区分，右值引用的符号是"&&"。
```c++
void print(int & n) {
    cout << "left reference "<<n<<endl;
}
void print(int && n) {
    cout << "right reference "<<n<<endl;
}
int main {
    int && x = 5;//右值引用
    int y = 6;
    print(10);
    print(x);
    print(y);
}
```
运行结果：
```s
right reference 10
left reference 5
left reference 6
```
可以看到用临时对象传参时，调用的时使用右值引用的print。注意到使用"x"传参时，并不是作为右值引用，而是作为左值引用。因为x并不是一个临时对象，5是临时对象。
#### move语义

右值引用是用来支持转移语义的。转移语义可以将资源 ( 堆，系统对象等 ) 从一个对象转移到另一个对象，这样能够减少不必要的临时对象的创建、拷贝以及销毁，能够大幅度提高 C++ 应用程序的性能。
临时对象的维护 ( 创建和销毁 ) 对性能有严重影响。通过转移语义，临时对象中的资源能够转移其它的对象里。 
转移语义是和拷贝语义相对的，可以类比文件的剪切与拷贝，当我们将文件从一个目录拷贝到另一个目录时，速度比剪切慢很多。

在现有的 C++ 机制中，我们可以定义拷贝构造函数和赋值函数。要实现转移语义，需要定义转移构造函数，还可以定义转移赋值操作符。对于右值的拷贝和赋值会调用转移构造函数和转移赋值操作符。
如果转移构造函数和转移拷贝操作符没有定义，那么就遵循现有的机制，拷贝构造函数和赋值操作符会被调用。
普通的函数和操作符也可以利用右值引用操作符实现转移语义
```c++
class MyString
{
private:
    char *_data;
    size_t _len;
    void _init_data(const char *s)
    {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }

public:
    MyString()
    {
        _data = NULL;
        _len = 0;
    }

    MyString(const char *p)
    {
        _len = strlen(p);
        _init_data(p);
    }

    MyString(const MyString &str)
    {
        _len = str._len;
        _init_data(str._data);
        std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
    }

    MyString &operator=(const MyString &str)
    {
        if (this != &str)
        {
            _len = str._len;
            _init_data(str._data);
        }
        std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
        return *this;
    }

    virtual ~MyString()
    {
        if (_data)
            free(_data);
    }
};
int main()
{
    MyString a;
    a = MyString("Hello");
    std::vector<MyString> vec;
    vec.push_back(MyString("World"));
}
```
运行结果：
```s
Copy Assignment is called! source: Hello 
Copy Constructor is called! source: World
```
MyString(“Hello”) 和 MyString(“World”) 都是临时对象，也就是右值。虽然它们是临时的，但程序仍然调用了拷贝构造和拷贝赋值，造成了没有意义的资源申请和释放的操作。如果能够直接使用临时对象已经申请的资源，既能节省资源，有能节省资源申请和释放的时间。这正是定义转移语义的目的。
定义转移构造函数和转移赋值函数：
```c++
MyString(MyString &&str)
{
    std::cout << "Move Constructor is called! source: " << str._data << std::endl;
    _len = str._len;
    _data = str._data;
    str._len = 0;
    str._data = NULL;
}
MyString &operator=(MyString &&str)
{
    std::cout << "Move Assignment is called! source: " << str._data << std::endl;
    if (this != &str)
    {
        _len = str._len;
        _data = str._data;
        str._len = 0;
        str._data = NULL;
    }
    return *this;
}
```
需要注意以下几点：
1. 参数（右值）的符号必须是右值引用符号，即“&&”。
2. 参数（右值）不可以是常量，因为我们需要修改右值。
3. 参数（右值）的资源链接和标记必须修改。否则，右值的析构函数就会释放资源。转移到新对象的资源也就无效了。

运行结果
```s
Move Assignment is called! source: Hello 
Move Constructor is called! source: World
```
由此看出，编译器区分了左值和右值，对右值调用了转移构造函数和转移赋值操作符。节省了资源，提高了程序运行的效率。

有了右值引用和转移语义，我们在设计和实现类时，对于需要动态申请大量资源的类，应该设计转移构造函数和转移赋值函数，以提高应用程序的效率。

#### 标准库函数 std::move
既然编译器只对右值引用才能调用转移构造函数和转移赋值函数，而所有命名对象都只能是左值引用，如果已知一个命名对象不再被使用而想对它调用转移构造函数和转移赋值函数，也就是把一个左值引用当做右值引用来使用，怎么做呢？标准库提供了函数 std::move，这个函数以非常简单的方式将左值引用转换为右值引用。

示例程序 :
```c++
void ProcessValue(int& i) { 
 std::cout << "LValue processed: " << i << std::endl; 
} 
 
void ProcessValue(int&& i) { 
 std::cout << "RValue processed: " << i << std::endl; 
} 
 
int main() { 
 int a = 0; 
 ProcessValue(a); 
 ProcessValue(std::move(a)); 
}
```
运行结果 :
```s
LValue processed: 0 
RValue processed: 0
```
std::move在提高 swap 函数的的性能上非常有帮助，一般来说，swap函数的通用定义如下：
```c++
template <class T> swap(T& a, T& b) 
{ 
    T tmp(a);   // copy a to tmp 
    a = b;      // copy b to a 
    b = tmp;    // copy tmp to b 
}
```
有了 std::move，swap 函数的定义变为 :
```c++
template <class T> swap(T& a, T& b) 
{ 
    T tmp(std::move(a)); // move a to tmp 
    a = std::move(b);    // move b to a 
    b = std::move(tmp);  // move tmp to b 
}
```
通过 std::move，一个简单的 swap 函数就避免了 3 次不必要的拷贝操作。

#### 精确传递 (Perfect Forwarding)
本文采用精确传递表达这个意思。”Perfect Forwarding”也被翻译成完美转发，精准转发等，说的都是一个意思。

精确传递适用于这样的场景：需要将一组参数原封不动的传递给另一个函数。

“原封不动”不仅仅是参数的值不变，在 C++ 中，除了参数值之外，还有一下两组属性：

左值／右值和 const/non-const。 精确传递就是在参数传递过程中，所有这些属性和参数值都不能改变。在泛型函数中，这样的需求非常普遍。

下面举例说明。函数 forward_value 是一个泛型函数，它将一个参数传递给另一个函数 process_value。

forward_value 的定义为：
```c++
template <typename T> void forward_value(const T& val) { 
 process_value(val); 
} 
template <typename T> void forward_value(T& val) { 
 process_value(val); 
}
```
函数 forward_value 为每一个参数必须重载两种类型，T& 和 const T&，否则，下面四种不同类型参数的调用中就不能同时满足  :
```c++
int a = 0; 
const int &b = 1; 
forward_value(a); // int& 
forward_value(b); // const int& 
forward_value(2); // int&
```
对于一个参数就要重载两次，也就是函数重载的次数和参数的个数是一个正比的关系。这个函数的定义次数对于程序员来说，是非常低效的。我们看看右值引用如何帮助我们解决这个问题  :
```c++
template <typename T> void forward_value(T&& val) { 
 process_value(val); 
}
```
只需要定义一次，接受一个右值引用的参数，就能够将所有的参数类型原封不动的传递给目标函数。四种不用类型参数的调用都能满足，参数的左右值属性和 const/non-cosnt 属性完全传递给目标函数 process_value。这个解决方案不是简洁优雅吗？

```c++
int a = 0; 
const int &b = 1; 
forward_value(a); // int& 
forward_value(b); // const int& 
forward_value(2); // int&&
```
C++11 中定义的 T&& 的推导规则为：

右值实参为右值引用，左值实参仍然为左值引用。

一句话，就是参数的属性不变。这样也就完美的实现了参数的完整传递。

右值引用，表面上看只是增加了一个引用符号，但它对 C++ 软件设计和类库的设计有非常大的影响。它既能简化代码，又能提高程序运行效率。每一个 C++ 软件设计师和程序员都应该理解并能够应用它。我们在设计类的时候如果有动态申请的资源，也应该设计转移构造函数和转移拷贝函数。在设计类库时，还应该考虑 std::move 的使用场景并积极使用它。
## 指针
