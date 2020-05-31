#include <iostream>

using namespace std;

inline int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int main()
{
    cout << max(1, 3) << endl;
}