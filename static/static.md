# static关键字

## 静态成员变量
- 成员变量前有static关键字
- 不具体作用于某一个对象
- 只有一份，所有对象共享一份
- 不通过对象也能访问，是全局变量
- 使用静态变量必须在类外部初始化

```c++
class testStatic
{
private:
    int m;
public:
    static int n;
};
//外部初始化
int testStatic::n = 0;
int main() {
    cout<<sizeof(testStatic)<<endl;//4
}
```
如何访问?
1. 类名::成员变量名
   ```c++
   testStatic::n
   ```
2. 对象名.成员变量名
   ```c++
   testStatic t1;
   t1.n;
   ```
3. 指针->成员变量名
   ```c++
   testStatic *ptr = t2;
   t2->n;
   ```
4. 引用->成员变量名
   ```c++
   testStatic &ptr = t2;
   t2->n;
   ```

## 静态成员函数
- 成员函数前有static关键字
- 不具体作用于某一个对象
- 只有一份，所有对象共享一份
- 不通过对象也能访问，是全局函数
- **不能访问**非静态成员变量
- **不能调用**非静态成员函数
```c++
class testStatic
{
private:
    int m;
public:
    static int n;
    static void prinfs(){
        cout<<n<<endl;
        //cout<<m<<endl;//error,不能访问非static成员变量
    }
};
```
静态成员函数访问方法和静态成员变量一致。
