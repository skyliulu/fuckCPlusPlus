#include <iostream>
#include <memory>

using namespace std;

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
    A *ptr = sp1.get();
    cout << "A' ptr "<<ptr->n<<endl;
    sp1.reset();
    if(!sp1) cout << "sp1放弃托管" <<endl;
    ptr = new A(2);
    sp1.reset(ptr);//sp1托管A(2)
    cout << "sp1 "<<sp1->n<<endl;
    shared_ptr<A> sp4(ptr);//错误！sp4托管A(2)，并不会增加A(2)的计数，导致资源会被多次删除
    cout << "sp4 "<<sp4->n<<endl;
}