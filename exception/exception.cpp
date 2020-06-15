#include <iostream>

using namespace std;

class CException
{
public:
    string msg;
    CException(string s) : msg(s) {}
};

int main()
{
    int m, n;
    cin >> m >> n;
    try
    {
        if (n == 0)
            throw - 1;
        if (m == 0)
            throw "error";
        if (m<n) throw CException("except");
    }
    catch (int)
    {
        cout << "catch(int)" << endl;
    }
    catch (CException e) { //自定义类型
        cout << e.msg <<endl;
    }
    catch (...)//默认类型，得放在最后，否则会掩盖住其他的异常类型
    {
        cout << "catch someting" << endl;
    }
}