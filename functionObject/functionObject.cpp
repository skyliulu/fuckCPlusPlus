#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
class Mycompare
{
public:
    int operator()(const int &a, const int &b)
    {
        return a > b;
    }
};

template <typename T>
class Mycompare2
{
public:
    int operator()(const T &a, const T &b)
    {
        return a < b;
    }
};
template <typename T>
T MyPower( T a, int power) {
    T tmp = a;
    for(int i=0;i<power-1;i++) tmp *= a;
    a = tmp;
    return a;
}

template <typename T>
class MyPrint {
public:
    void operator()(T lo,T hi) {
        while(lo!=hi) {
            cout<<*lo++<<" ";
        }
        cout <<endl;
    }
};

int main()
{
    vector<int> nums = {1,43,8,1,5,9,0,3,6,8};
    MyPrint<vector<int>::iterator> print;
    // sort(nums.begin(),nums.end());
    // sort(nums.begin(),nums.end(),Mycompare());
    // print(nums.begin(),nums.end());
    // sort(nums.begin(),nums.end(),Mycompare2<int>());
    print(nums.begin(),nums.end());
    int (* pf)(int,int);
    pf = MyPower<int>;
    cout << pf(10,2)<<endl;
}
