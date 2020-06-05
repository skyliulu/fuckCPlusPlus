# GDB简明教程（翻译）

GDB是GNU调试器。它用于调试由GCC (GNU编译器集合)编译的代码。它是一个非常强大的调试器，允许您调试甚至是最复杂的软件。这个文档是为初学者或高级程序员准备的，不是作为一个全面的指南，而是gdb的介绍。本指南假设读者对C语言有一定程度的熟悉。

## 1.GDB基础

并不是每个可执行二进制文件都可以简单地装载到gdb中进行调试。这是因为它不包含调试符号。这些符号会告诉gdb在运行程序时在源代码中查找什么。因此gdb需要做两件事才能调试代码。

1. 您需要使源树处于与编译程序时相同的状态。因此，例如，如果所有源文件都在/home/user/program/src/中编译，而二进制文件在/home/user/program/ui/中编译，那么您就不能将源文件移动到其他地方而期望gdb“神奇地”知道这一点。

2. 您需要告诉gcc/g++将这些符号“植入”到二进制文件中。可以通过在编译期间指定-g标志来实现这一点。例如，将example.cpp编译成二进制:
    ```bash
    $ gcc -g example.cpp -o example
    ```
### 1.1 启动gdb
可以通过多种方式启动GNU调试器。最简单的方法是通过二进制可执行文件启动：
```
gdb binary
```
此外你也可以启动gdb后再加载调试程序：
```
(gdb) file binary
```
### 1.2 list
list命令命令会列出你的源代码，为了方便，你可以简化为l:
```
(gdb) l
25      };
26
27      int main()
28      {
29          base A;
30          drive1 B;
31          base *ptr;
32          ptr = &A;
33          ptr->baseFunc1();
34          ptr->func();
```
理解上面显示的输出很重要。在左侧，gdb输出行号。在它旁边，它显示了代码行。
list还可以指定函数名来查看：
```
(gdb) l base()
5       class base
6       {
7           int a;
8
9       public:
10          base() { baseFunc1(); } //没有多态
11          virtual void baseFunc1() { cout << "base1" << endl; }
12          virtual void baseFunc2() { cout << "base1" << endl; }
13          void func() { baseFunc1(); } //多态
14      };
```
### 1.3 running
将带有符号的二进制文件加载到gdb之后，需要显式地告诉gdb执行它。你这样做通过使用命令运行。这里有一个例子:
```
(gdb) run
Starting program: /home/lashi/University/csse_club/gdb/excercises/binary
Hello GDB!
Hello GDB!
```
您还可以通过将命令行参数放在run命令旁边来传递它们。如果已经指定了参数，那么独立运行将自动加载以前使用的命令行参数。
### 1.4 printing
在调试应用程序时，重要的是您可以看到实例化对象（即变量）的状态。这可以通过使用print(或p)命令来完成。您希望看到的对象可以像在C或C++中一样被取消引用和强制转换。使用print的示例：
```

```