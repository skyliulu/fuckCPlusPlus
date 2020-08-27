#include <iostream>

using namespace std;

class base
{
private:
    int priv;
    void priFunc() {}

protected:
    int pro;
    void proFunc() {}

public:
    int pub;
    void pubFunc() {}
    base()
    {
        cout << "base constructor called" << endl;
    }
    ~base() {
        cout << "base destructor called" << endl;
    }
};

class drive1 : public base
{
public:
    void access()
    {
        // cout<<priv<<endl;//error!无法访问基类的私有成员
        cout << pro << endl; //ok
        cout << pub << endl; //ok
    }
    drive1() {
        cout << "drive1 constructor called!"<<endl;
    }
    ~drive1() {
        cout << "drive1 destructor called" << endl;
    }
};
class drive2 : private base
{
public:
    void access()
    {
        // cout<<priv<<endl;//error!无法访问基类的私有成员
        cout << pro << endl; //ok
        cout << pub << endl; //ok
    }
    drive2() {
        cout << "drive2 constructor called!"<<endl;
    }
    ~drive2() {
        cout << "drive2 destructor called" << endl;
    }
};
class drive3 : protected base
{
public:
    void access()
    {
        // cout<<priv<<endl;//error!无法访问基类的私有成员
        cout << pro << endl; //ok
        cout << pub << endl; //ok
    }
    drive3() {
        cout << "drive3 constructor called!"<<endl;
    }
    ~drive3() {
        cout << "drive3 destructor called" << endl;
    }
};
class base1 {
public:
    void pubFunc() {
        cout << "base1 pubFunc"<<endl;
    }
    base1()
    {
        cout << "base1 constructor called" << endl;
    }
    ~base1() {
        cout << "base1 destructor called" << endl;
    }
};

class mutilDrive : public base,base1 {

};

int main()
{
    drive1 d1;
    // d1.pri;//error
    // d1.priFunc();//error
    // d1.pro;//error
    // d1.proFunc();//error
    d1.pub;
    d1.pubFunc();
    drive2 d2;
    // d2.pub;//error
    // d2.pubFunc();//error
    drive3 d3;
    // d3.pubFunc();//error
    mutilDrive d4;
    // d4.pubFunc();//语义不明确，错误
}