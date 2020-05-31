# 常量const

1. 常量
   >常量值不可更改
   ```c++
    const int val = 20;
    val = 22;//error
    val = 20;//error,不允许有赋值操作
   ```
2. 常量指针 
    **const type ***
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