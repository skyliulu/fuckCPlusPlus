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


## 指针
