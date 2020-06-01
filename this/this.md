# this指针

- this指针指向成员函数所作用的对象
- 静态成员函数不能使用this指针
  - 因为静态成员函数不属于某个对象

```c++
class testThis
{
    int n;

public:
    void hello() { cout << "hello" << endl; }
    void printn() { cout << this->n << endl; }
};

int main()
{
    testThis *ptr = NULL;
    ptr->hello();//ok,函数体为用到this指针
    ptr->printn();//error,this指针为空
}
```
