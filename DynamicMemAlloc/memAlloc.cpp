#include <iostream>
using namespace std;
int main() {
    int m = 6,n =5;
    int ** v = (int **)malloc(sizeof(int *)*m);
    for(int i=0;i<m;i++) {
        v[i] = (int *)malloc(sizeof(int)*n);
    }
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            v[i][j] = i+j;
        }
    }
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            cout << v[i][j]<<" ";
        }
        cout<<endl;
    }
    
    long * a = NULL;
    cout << a+1<<endl;
}