#include <iostream>

using namespace std;

bool isBigEnd() {
    short x = 0x1234;
    char ch = *(char *)&x;
    return ch == 0x12;
}


uint32_t reversebytes_uint32t(uint32_t value){
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 | 
        (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24; 
}

int main() {
    cout << isBigEnd() <<endl;
}