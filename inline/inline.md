# 内联函数
>函数调用是有开销的，对于函数体较小却又多次执行的函数，总的开销就会显得比较大

编译期处理内敛函数的调用语句时，是将函数体的代码插入到调用语句出，这样就不会避免了函数调用。
```c++
inline int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int main()
{
    cout << max(1, 3) << endl;
}
```
