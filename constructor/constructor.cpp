#include <iostream>

using namespace std;

class Node
{
private:
    /* data */
    double key, value;

public:
    Node(){};
    Node(double k, double v);
    Node(double k);
    Node(const Node &node); //复制构造函数
    Node(int k);            //类型转换构造函数
    Node(int k, int v);
    double getKey() { return key; }
    ~Node(){};
};
Node::Node(int k)
{
    key = double(k);
    value = 0;
    cout << "typeTrans constructor called" << endl;
}
Node::Node(int k, int v)
{
    key = double(k);
    value = double(v);
    cout << "constructor called" << endl;
}
Node::Node(double k, double v)
{
    key = k;
    value = v;
    cout << "constructor called" << endl;
}
Node::Node(double k)
{
    key = k;
    value = 0;
    cout << "constructor called" << endl;
}
Node::Node(const Node &node)
{
    key = node.key;
    value = node.value;
    cout << "copy constructor called" << endl;
}
void func(Node node) {}
Node func1()
{
    Node n(3, 5);
    return n;
}
int main()
{
    Node n1;
    Node n2(1);
    Node n3(2, 3);
    // Node n4(1,2,3);//error，参数个数不匹配
    Node *ptr1 = new Node;
    Node *ptr2 = new Node(1);
    Node *ptr3 = new Node(1, 2);
    Node *ptr4 = new Node(1.2, 2.2);
    Node *ptr5 = new Node(1.2);
    // Node *ptr6 = new Node(1.2,2);//error,参数类型不匹配
    //调用复制构造函数
    Node n4(n3);
    Node *ptr6 = new Node(*ptr5);
    cout << func1().getKey() << endl; //编译器做了优化，不再产生临时对象

    Node n5;
    n5 = 6;
}
