#include <iostream>

using namespace std;

class myInt
{
private:
    int n;
public:
    myInt(int i):n(i){}
    myInt & operator++(); //用于前置++形式
    myInt operator++(int); //用于后置++形式
    operator int () { return n; }
    friend myInt & operator--(myInt &); //用于前置--形式
    friend myInt operator--(myInt &, int); //用于后置--形式
};
myInt & myInt::operator++() { //前置 ++
    n++;
    return * this;
}
myInt myInt::operator++(int i) {//后置++
    myInt tmp(*this); //记录修改前的对象
    n++;
    return tmp; //返回修改前的对象
}

int main() {



}