#include <iostream>

using namespace std;

class testStatic
{
private:
    int m;
public:
    static int n;
    static void prinfs(){
        cout<<n<<endl;
        //cout<<m<<endl;//error,不能访问非static成员变量
    }
};
//外部初始化
int testStatic::n = 0;

int main() {
    cout<<sizeof(testStatic)<<endl;//4
    testStatic t1;
    // testStatic::n = 1;
    cout<<t1.n<<endl;
    cout<<testStatic::n<<endl;
}