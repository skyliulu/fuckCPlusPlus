#include <memory>
#include <iostream>
using namespace std;
struct A {
  int n;
  ~A() { std::cout << "~A()\n"; }
};


int main() 
{ 
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
} 