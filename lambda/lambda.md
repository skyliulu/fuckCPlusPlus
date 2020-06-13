# lambda表达式
c++11中引入了lambda表达式，通过lambda表达式可以方便的创建出匿名函数。当我们需要临时编写一个函数或者函数只用一次，编写函数对象是有些多余的，这时候用lambda表达式是非常合适的。

## 形式
```c++
[外部变量访问方式说明符](参数表) ->返回值类型
{
    语句组
}
```
**访问方式说明符的形式如下：**
- [=] 以传值的形式使用所有外部变量
- [] 不使用任何外部变量
- [&] 以引用形式使用所有外部变量
- [x, &y] x 以传值形式使用，y 以引用形式使用
- [=,&x,&y] x,y 以引用形式使用，其余变量以传值形式使用
- [&,x,y] x,y 以传值的形式使用，其余变量以引用形式使用

>->返回值类型”也可以没有， 没有则编译器自动判断返回值类型。

**示例代码：**
```c++
int x = 10,y =x,z =100;
auto f1 = [](int i,int j)->int { //不使用外部变量
    return i+j;
};
cout<<"f1:"<<f1(x,z)<<endl; 
auto f2 = [=]()->int { //外部变量传值
    return x*y;
};
cout<<"f2:"<<f2()<<endl;
auto f3 = [&]() { //引用外部变量
    x = 5;
};
f3();
cout << x <<endl;
auto f4 = [x,&y]() { //x传值,y引用
    // x = 10;
    return x>y;
};
cout<<"f4:"<<f4()<<endl;

int nums[6] = {1,3,2,7,5,9};
sort(nums,nums+6,[](int i,int j){return i<j;});
for_each(nums,nums+6,[](int i){cout<<i<<" ";});
cout << endl;
//斐波那契数列
function<int(int)> fib = [&](int n) {
    return n<=2?1:fib(n-1)+fib(n-2);
};
cout << "fib: "<<fib(10) <<endl;
```

