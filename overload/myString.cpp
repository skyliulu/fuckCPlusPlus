#include <iostream>
#include <string.h>

using namespace std;

class myString
{
    char *str;
    int size;
public:
    myString() : str(NULL),size(0) {}
    myString(const char *s);
    myString(int len,const char ch);
    myString(const myString &s);
    myString &operator=(const myString &s);
    void printaddr() { cout << (void *)str << endl; }
    void printstring() { cout << str << endl; }
    int length() {return size;}
    void push_back(char ch);
    char& operator[](int i);//返回值必须是引用类型，为了能够更改数组中的值
    friend ostream& operator<<(ostream& out,const myString& s);
    friend istream& operator>>(istream& in,myString& s);
    ~myString()
    {
        if(str) delete [] str;
    }
};
myString::myString(const char *s)
{
    if (s)
    {   size = strlen(s);
        str = new char[size + 1];
        strcpy(str, s);
    } else {
        str = NULL;
        size = 0;
    }
}
myString::myString(int len,const char ch) {
    if(len) {
        size = len;
        str = new char[len+1];
        for(int i=0;i<len;i++) {str[i]=ch;}
        str[len] = '\0';
    } else {
        str = NULL;
        size =0;
    }
}
myString::myString(const myString &s) {
    if (s.str)
    {
        size = strlen(s.str);
        str = new char[ size + 1];
        strcpy(str, s.str);
    } else {
        str = NULL;
        size = 0;
    }
}
myString &myString::operator=(const myString &s)
{
    if (str == s.str)
        return *this;
    if (s.str)
    {
        if (size<s.size)
            if(str) delete[] str;
            str = new char[s.size + 1];
        strcpy(str, s.str);
        size = strlen(s.str);
    }
    else
    {
        str = NULL;
        size = 0;
    }
    return *this;
}
void myString::push_back(char ch) {

}
char& myString::operator[](int i) {
    return str[i];
}

ostream& operator<<(ostream& out,const myString& s) {
    out<<s.str;
    return out;
}
istream& operator>>(istream& in,myString& s) {
    if(!s.str) {
        s.str = new char[20];
    }
    in >>s.str;
    return in;
}

int main()
{
    myString str1("abc"), str2("cde"), str3("efg");
    str1.printaddr();
    str2.printaddr();
    str2 = str1; //ok
    cout<<str2<<endl;
    // str2.printstring();
    str1.printaddr();
    str2.printaddr();
    (str1 = str2) = str3;
    // str1 = str2 = str3;
    str1.printstring();
    str2.printstring();
    cout<<str1[1]<<endl;
    str1[0]='9';
    str1.printstring();
    myString str;
    cin >> str;
    cout<<str<<endl;

}