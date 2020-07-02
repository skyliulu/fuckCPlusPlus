# 智能指针

**为什么要用智能指针？**
c++的内存管理是让很多人头疼的事，当我们new一个资源时，需要相应的delete语句把资源释放了。但是当程序变得十分庞大时，亦或程序员的粗心大意所致，delete语句没有写或没有执行是难以避免的。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域是，类会自动调用析构函数，析构函数会自动释放资源。
<!-- more -->
## shared_ptr
- 多个share_ptr可以共享同一个对象，对象的最末一个拥有着有责任销毁对象，并清理与该对象相关的所有资源。 
- 每次复制之后引用计数加一，不再指向对象（自身销毁或指向其他对象）时时引用计数减一，减至零值调用所管理资源对象的析构函数。
- 支持定制型删除器（custom deleter），可防范 Cross-DLL 问题（对象在动态链接库（DLL）中被 new 创建，却在另一个 DLL 内被 delete 销毁）、自动解除互斥锁。
```c++
struct A {
    int n;
    A(){}
    A (int i):n(i) {}
    ~A() {cout<<n<<" destruct"<<endl;}
};
int main() {
    cout << "使用share_ptr托管资源"<<endl;
    shared_ptr<A> sp1(new A(1));//sp1托管A(1)
    shared_ptr<A> sp2(sp1);//sp2也托管A(1)
    shared_ptr<A> sp3 = sp2;//sp3也托管A(1)
    // shared_ptr<A> sp4(new A[10]);//错误！智能指针不能管理数组类型
    cout << "访问托管资源"<<endl;
    cout << "sp1 "<<sp1->n<<" sp2 "<<sp2->n<<" sp3 "<<sp3->n<<endl;
    A *ptr = sp1.get();//获取托管的资源
    cout << "A' ptr "<<ptr->n<<endl;
    sp1.reset();//放弃托管资源
    if(!sp1) cout << "sp1放弃托管" <<endl;
}
```
使用share_ptr时，需要注意对资源进行托管的方式。
```c++
ptr = new A(2);
sp1.reset(ptr);//sp1托管A(2)
cout << "sp1 "<<sp1->n<<endl;
shared_ptr<A> sp4(ptr);//错误！sp4托管A(2)，并不会增加A(2)的计数，导致资源会被多次删除
cout << "sp4 "<<sp4->n<<endl;
```
如果用两个智能指针以资源指针的形式托管同一个资源，这样并不会增加计数，而且会导致资源的多次释放，导致程序错误。
 
## weak_ptr
- weak_ptr 允许共享但不拥有某对象，一旦最末一个拥有该对象的智能指针失去了所有权，任何 weak_ptr 都会自动成空（empty）。
- 在 default 和 copy 构造函数之外，weak_ptr 只提供 “接受一个 shared_ptr” 的构造函数。
- 可打破环状引用的问题。
```c++
struct B;
struct A {
  std::shared_ptr<B> b;  
  ~A() { std::cout << "~A()\n"; }
};

struct B {
  std::shared_ptr<A> a;
  ~B() { std::cout << "~B()\n"; }  
};
```
可以看到A和B是环状引用的，这种情况下shared_ptr是无法释放资源的。
```c++
auto a = std::make_shared<A>();
auto b = std::make_shared<B>();
a->b = b;
b->a = a;
std::cout<<a.use_count()<<std::endl;//2
std::cout<<b.use_count()<<std::endl;//2
```
如上所示，每个资源的引用计数均为2。A被a和b->a引用，B被b和a->b引用，这样程序结束时不会调用A和B的析构函数的。
使用weak_ptr可打破环状引用。将struct B改为：
```c++
struct B {
//   std::shared_ptr<A> a;
  std::weak_ptr<A> a;
  ~B() { std::cout << "~B()\n"; }  
};
auto a = std::make_shared<A>();
auto b = std::make_shared<B>();
a->b = b;
b->a = a;
std::cout<<a.use_count()<<std::endl;//1
std::cout<<b.use_count()<<std::endl;//2
```
weak_ptr不会增加引用计数，所以A被b引用，B被a->b和b引用。当A被释放后，B的引用变成1，自然也可以被释放了。

## unique_ptr
- unique_ptr 是 C++11 才开始提供的类型，是一种在异常时可以帮助避免资源泄漏的智能指针。
- 采用独占式拥有，意味着可以确保一个对象和其相应的资源同一时间只被一个 pointer 拥有。
- unique_ptr不能被拷贝
- 一旦拥有着被销毁或编程 empty，或开始拥有另一个对象，先前拥有的那个对象就会被销毁，其任何相应资源亦会被释放。
- unique_ptr 可以管理数组（析构调用 delete[] ）
```c++
unique_ptr<A> p1(new A); 
// returns the memory address of p1 
cout << p1.get() << endl; //0x7fffefb06e70
// transfers ownership to p2 
unique_ptr<A> p2 = move(p1); 
cout << p1.get() << endl; //0
cout << p2.get() << endl; //0x7fffefb06e70

// transfers ownership to p3 
unique_ptr<A> p3 = move(p2); 
cout << p1.get() << endl; //0
cout << p2.get() << endl; //0
cout << p3.get() << endl;//0x7fffefb06e70

unique_ptr<A[]> p4(new A[5]);
cout << p4.get() << endl; //0x7fffefb072a8
// unique_ptr<A> p5 = p4; 
```
## auto_ptr
被 c++11 弃用，原因是缺乏语言特性如 “针对构造和赋值” 的 std::move 语义，以及其他瑕疵。auto_ptr 与 unique_ptr 比较
- auto_ptr 可以赋值拷贝，复制拷贝后所有权转移；unqiue_ptr 无拷贝赋值语义，但实现了move 语义；
- auto_ptr 对象不能管理数组（析构调用 delete），unique_ptr 可以管理数组（析构调用 delete[] ）；

