# 异常处理
- 把异常与函数的接口分开，并且能够区分不同的异常
- 在函数体外捕获所发生的异常,并提供更多的异常信息
<!-- more -->
## 抛出（Throw）--> 检测（Try） --> 捕获（Catch）

```c++
class CException
{
public:
    string msg;
    CException(string s) : msg(s) {}
};

int main()
{
    int m, n;
    cin >> m >> n;
    try
    {
        if (n == 0)
            throw - 1;
        if (m == 0)
            throw "error";
        if (m<n) throw CException("except");
    }
    catch (int)
    {
        cout << "catch(int)" << endl;
    }
    catch (CException e) { //自定义类型
        cout << e.msg <<endl;
    }
    catch (...)//默认类型，得放在最后，否则会掩盖住其他的异常类型
    {
        cout << "catch someting" << endl;
    }
}
```
运行结果：
```s
2 0
catch(int)
0 2
catch someting
1 2
except
```
## c++标准异常类
C++标准库中有一些类代表异常，这些类都是从exception类派生而来。常用的几个异常类如下：
```s
exception |---> bad_typeid
          |---> bad_cast
          |---> bad_alloc
          |---> ios_base::failure
          |---> logic_error--->out_of_range
```
### bad_cast
在用 dynamic_cast进行从多态基类对象（或引用）,到派生类的引用的强制类型转换时，如果转换是不安全的，则会抛出此异常。

### bad_alloc
在用new运算符进行动态内存分配时，如果没有足够的内存，则会引发此异常。

### out_of_range
用vector或string的at成员函数根据下标访问元素时，如果下标越界，就会抛出此异常。

