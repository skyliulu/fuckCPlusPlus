#include <iostream>

using namespace std;

void print(int & n) {
    cout << "left reference "<<n<<endl;
}
void print(int && n) {
    cout << "right reference "<<n<<endl;
}
int main() {
    int n = 4;
    int &ref = n;
    cout <<ref<<endl;
    n = 5;
    cout<<ref<<endl;
    int &ref2 = ref;
    cout<<ref2<<endl;
    // int &ref2 = 2;//error
    // int &ref3 = n*5;//error
    // cout<<ref2<<endl;
    int m = 6;
    ref = m;//ok,赋值操作
    // ref = &m;//error

    const int &c_ref = n;
    int &ref3 = n;
    // c_ref = 9;//error
    ref3 = 9;
    cout<<n<<endl;
    cout<<"右值引用测试"<<endl;
    int && x = 5;
    int y = 6;
    print(10);
    print(x);
    print(y);
}
