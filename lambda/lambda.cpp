#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    int x = 10,y =x,z =100;
    auto f1 = [](int i,int j)->int { //不使用外部变量
        return i+j;
    };
    cout<<"f1:"<<f1(x,z)<<endl; 
    auto f2 = [=]()->int { //外部变量传值
        return x*y;
    };
    cout<<"f2:"<<f2()<<endl;
    auto f3 = [&]() { //引用外部变量
        x = 5;
    };
    f3();
    cout << x <<endl;
    auto f4 = [x,&y]() { //x传值,y引用
        // x = 10;
        return x>y;
    };
    cout<<"f4:"<<f4()<<endl;

    int nums[6] = {1,3,2,7,5,9};
    sort(nums,nums+6,[](int i,int j){return i<j;});
    for_each(nums,nums+6,[](int i){cout<<i<<" ";});
    cout << endl;
    //斐波那契数列
    function<int(int)> fib = [&](int n) {
        return n<=2?1:fib(n-1)+fib(n-2);
    };
    cout << "fib: "<<fib(10) <<endl;

}