#include <iostream>

using namespace std;

template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr = nullptr) : ptr_(ptr) {}
    ~smart_ptr() {
        cout << "释放资源"<<ptr_ <<endl;
        delete ptr_;
    }
    T* get() const {
        return ptr_;
    }
    T& operator*() const {
        return *ptr_;
    }
    T* operator->() const {
        return ptr_;
    }
    operator bool() const {
        return ptr_;
    }
    smart_ptr(smart_ptr&& other);
    smart_ptr& operator=(smart_ptr other);
private:
    T* ptr_;
    T* release() {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& other) {
        using std::swap;
        swap(ptr_,other.ptr_);
    }
};

template <typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& other) {
    ptr_ = other.release();
    cout << "拷贝构造" <<ptr_<<endl;
}
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr other) {
    other.swap(*this);
    cout << "复制构造" <<ptr_<<endl;
    return *this;
}

int main() {
    int * test = new int[1];
    smart_ptr<int> ptr1(test);
    // smart_ptr<int> ptr2(ptr1);
    smart_ptr<int> ptr2(move(ptr1));
    smart_ptr<int> ptr3;
    // ptr3 = ptr1;
    // ptr3 = ptr2;
    ptr3 = move(ptr2);
    // cout << ptr1 << ptr2 << ptr3;
}
