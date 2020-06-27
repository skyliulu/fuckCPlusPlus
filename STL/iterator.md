# 迭代器

- 迭代器是一种泛化的指针，将容器和算法粘合在一起
- 迭代器是一种类似指针的对象，需要重载operator*()、operator->()、operator++()、operator++(T)等操作。
- 迭代器类型：随机访问迭代器，双向迭代器，单项迭代器，输入迭代器，输出迭代器
- 迭代器必须定义5种关联类型，以便能够回答STL算法问询的问题：
  ```c++
  struct _List_iterator {
  typedef ptrdiff_t                  difference_type; //距离类型
  typedef bidirectional_iterator_tag iterator_category;//迭代器种类
  typedef _Tp value_type; //value类型
  typedef _Ptr pointer; //指针类型
  typedef _Ref reference; //引用类型
  ```
- 指针是退化的迭代器，但是却没有定义上述5种关联种类，当STL接受指针参数时，如何获取想要的结果呢？STL中使用iterator_traits（迭代器萃取机）来提迭代器/指针回答算法的问题。iterator_traits用以区分class iterator 和 non-class iterator（原生指针）

## 迭代器失效

### vector
1. 删除元素后，后继的元素会前移，所以当前的迭代器以及所有后继的迭代器都会失效。
2. vector动态增加大小，引起空间重配置时，会使得当前vector的迭代器全部失效。这是因为空间重配置会申请新的内存空间，并将原内容拷贝到新的空间，然后释放原空间。

### list
1. 删除元素后，指向当前元素的迭代器会失效。

