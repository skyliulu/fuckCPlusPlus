#include <memory>
#include <iostream>

struct B;
struct A {
  std::shared_ptr<B> b;  
  ~A() { std::cout << "~A()\n"; }
};

struct B {
//   std::shared_ptr<A> a;
  std::weak_ptr<A> a;
  ~B() { std::cout << "~B()\n"; }  
};

void useAnB() {
  auto a = std::make_shared<A>();
  auto b = std::make_shared<B>();
  a->b = b;
  b->a = a;
  std::cout<<a.use_count()<<std::endl;//1
  std::cout<<b.use_count()<<std::endl;//2
}

int main() {
   useAnB();
   std::cout << "Finished using A and B\n";
}