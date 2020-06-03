#include <iostream>
#include <string.h>

using namespace std;

class complex
{
public:
    double r, i;
    complex(){};
    complex(double a, double b)
    {
        a = r;
        b = i;
    }
    //重载为成员函数
    complex operator-(const complex &b)
    {
        return complex(r - b.r, i - b.i);
    }
};
//重载为普通函数
complex operator+(const complex &a, const complex &b)
{
    return complex(a.r + b.r, a.i + b.i);
}

int main() {
    complex a(1, 1), b(2, 1), c;
    c = a + b;
    c = a - b;
}