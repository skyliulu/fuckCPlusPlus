#include <iostream>

using namespace std;

inline int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

class testInline
{
public:
    void func1(){}; //inline
    void func2();
};
inline void testInline::func2() {} //inline
int main()
{
    cout << max(1, 3) << endl;
}