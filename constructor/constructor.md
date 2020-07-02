# 构造函数

构造函数是一种特殊的成员函数，具有如下特点：
1. 名字和类名相同，可以有参数，但是**不能有返回值**。
2. 负责对对象进行初始化操作，生成对象时调用1次，此后不会被调用。
3. 未定义构造函数，编译器会自动生成一个无参的构造函数，该函数没有任何操作。
4. 构造函数可以被重载。

```c++
class Node
{
private:
    /* data */
    double key,value;
public:
    Node(){};
    Node(int k,int v=0);
    Node(double k,double v);
    double getKey() {return key;}
    ~Node(){};
};
Node::Node(int k,int v) {
    key = double(k);value = double(v);
}
Node::Node(double k,double v) {
    key=k;value=v;
}
int main() {
    Node n1;
    Node n2(1);
    Node n3(2,3);
    Node n4(1,2,3);//error，参数个数不匹配
    Node *ptr4 = new Node(1.2,2.2);
    Node *ptr6 = new Node(1.2,2);//error,参数类型不匹配
}
```
## 复制构造函数
1. 复制构造函数**只能有一个参数：同类对象的引用**(type & or const type &)
2. 未定义复制构造函数，编译器会自动生成一个复制构造函数。
3. 避免浅拷贝，需要自己定义复制构造函数。
```c++
class Node
{
private:
    /* data */
    double key,value;
public:
    Node(){};
    Node(const Node& node);
    ~Node(){};
};
Node::Node(const Node& node) {
    key = node.key;
    value = node.value;
    cout << "copy constructor called"<<endl;
}
int main() {
    Node n1;
    Node n4(n1);
    Node * ptr6 = new Node(n1);
}
```
### 复制构造函数的使用
1. 初始化对象时
   ```c++
   Node n2(n1);
   ```
2. 函数参数为对象时
   ```c++
   void func(Node node){};
   int main() {
       Node n4(3);
       func(n4);//调用复制构造函数
   }
   ```
3. 函数返回值为对象时,如果没有调用，则是编译期做了优化
   ```c++
    Node func1() {
        Node n(3);
        return n;
    }
    int main() {
        cout << func1().getKey()<<endl;
        //如果没有调用复制构造函数，是编译器做了优化，不再产生临时对象
    }
   ```
## 类型转换构造函数
1. 实现类型的自动转换
2. 只有一个参数
3. 转换构造函数会建立一个临时对象

```c++
class Node
{
private:
    /* data */
    double key,value;
public:
    Node(){};
    Node(int k);//类型转换构造函数
    double getKey() {return key;}
    ~Node(){};
};
Node::Node(int k) {
    key = double(k);value = 0;
    cout << "typeTrans constructor called"<<endl;
}
int main(){
    Node n5;
    n5 = 6;//类型转换
}
```



