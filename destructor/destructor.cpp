#include <iostream>

using namespace std;

class String
{
private:
    char *p;
    int id;

public:
    String()
    {
        p = new char[10];
    };
    String(int i);
    String(char ch);
    ~String();
};

String::~String()
{
    delete[] p;
    cout << id << " destructor called" << endl;
}
String::String(int i)
{
    id = i;
    cout << id << " constructor called" << endl;
    p = new char[10];
};
String::String(char ch)
{
    id = ch - '0';
    cout << id << " constructor called" << endl;
    p = new char[10];
}
int main()
{
    String str1(1);
    str1 = '6';
    if (1)
    {
        String str2(2);
    }
    String str3(3);
}