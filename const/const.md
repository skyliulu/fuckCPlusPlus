# 常量const

1. 常量
   >常量值不可更改
   ```c++
    const int val = 20;
    val = 22;//error
    val = 20;//error,不允许有赋值操作
   ```
2. 常量指针 
    
    **const type \***
    >不可通过常量指针修改其指向的内容
    ```c++
        int val2 = 30;
        const int * ptr = &val2;
        *ptr = 40;//error
        val2 = 40;//ok,val2不是常量可以更改
    ```
    **type * const**
    >不可更改指针值
    ```c++
        int * const ptr2 = &val2;
        *ptr2 = 50;//ok
        ptr2 = ptr;//error
    ```
3. 常量引用
   >不能通过常引用去修改其引用的内容
    ```c++
    const int &c_ref = n;
    int &ref3 = n;
    c_ref = 9;//error,常引用
    ref3 = 9;//ok,ref3不是常引用
    ```
4. 常成员函数
   1. 类成员函数后面加const关键字
   2. 常成员函数不能修改对象的成员变量的值
      1. 除了静态成员变量，因为静态成员变量不属于某个对象
   3. 常成员函数不能调用类的非常成员函数
      1. 非常成员函数可能会修改成员变量的值
      2. 除了静态成员函数，因为静态成员函数不属于某个对象
    ```c++
    class test
    {
        int n;

    public:
        test() { n = 1; };
        // int set(int i) const {n=i;}//error,常成员函数不能更改成员变量
        int set(int i) {}
        int get() const { return n; }
        int get() { return n; } //重载
        void print() const;
    };
    void test::print() const {
        cout<<n<<endl;
    }
    int main() {
        const test t1;
        test t2;
        //t1.set(2);//error,常量对象不能调用非常量成员函数
        t2.set(2);
        cout << t1.get() << " " << t2.get() << endl;
    }
    ```