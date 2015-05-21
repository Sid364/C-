#ifndef SMRT_PTR_H_
#define SMRT_PTR_H_

#include <atomic>
#include <iostream>

template<typename T>
class smart_ptr {
    //trick from book Modern C++ Design
    //allows casting T*, but avoids deleting pointer from outside of class
    class Tester {
        void operator delete(void*);
    };
    std::atomic<T*> pointee_;
    unsigned int *ref_count;
    void delete_pointer_if_needed();
    // casting to int or void* is forbidden
    operator int();
    operator void*();
public:
    smart_ptr(smart_ptr& other) {
        pointee_.store(other.pointee_.load());
        ref_count = other.ref_count;
        *(ref_count)++;
    }

//    operator bool() const {
//        return pointee_ != 0;
//    }
    //allows if (sp) ..., where sp is smart_ptr objec
    operator Tester*() const {
        if (!pointee_)
            return 0;
        static Tester tester;
        return &tester;
    }
    //implementations for operators
    bool operator!() const {
        return pointee_.load() == nullptr;
    }
    inline friend bool operator==(const smart_ptr& left, const T* right) {
        return left.pointee_.load() == right;
    }
    inline friend bool operator==(const T* left, const smart_ptr &right)  {
        return left == right.pointee_.load();
    }
    inline friend bool operator !=(const T* left, const smart_ptr &right) {
        return left != right.pointee_.load();
    }
    inline friend bool operator !=(const smart_ptr &left, const T* right) {
        return left.pointee_.load() != right;
    }
    template <class U> bool operator<( const smart_ptr<U>& right) {
        return pointee_.load() < right.pointee_.load();
    }
    template <class U> bool operator>(const smart_ptr<U>& right) {
        return pointee_.load() > right.pointee_.load();
    }
    template <class U> bool operator<=(const smart_ptr<U>& right) {
        return pointee_.load() <= right.pointee_.load();
    }
    template <class U> bool operator>=(const smart_ptr<U>& right) {
        return pointee_.load() >= right.pointee_.load();
    }
    template <class U>
    bool operator==(const smart_ptr<U>& other) {
        return pointee_.load() == other.pointee_.load();
    }
    template <class U>
    bool operator!=(const smart_ptr<U>& other) {
        return pointee_.load() != other.pointee_.load();
    }

    explicit smart_ptr(T * ptr) : pointee_(ptr) {
        ref_count = new unsigned int(1);
    }
    //copy assigment operator
    smart_ptr<T>& operator=(const smart_ptr &other ) {
        if (this != &other){
            delete_pointer_if_needed();
            pointee_.store(other.pointee_);
            ref_count = other.ref_count;
            *(ref_count)++;
        }
        return *this;
    }
    // returns raw pointer
    T * get() const;

    T & operator *() const {
        return *pointee_;
    }
    T * operator ->() const {
        return pointee_;
    }
    //changes value of pointer to new_value
    void reset(T * new_value = 0) ;
    ~smart_ptr();
};

template <typename T> void smart_ptr<T>::reset(T* new_value) {
    delete_pointer_if_needed();
    pointee_.store( new_value);
    ref_count = new unsigned int(1);
}

template <typename T> smart_ptr<T>::~smart_ptr() {
    delete_pointer_if_needed();

}
template <typename T> void smart_ptr<T>::delete_pointer_if_needed() {
    if (!--(*ref_count)) {
        delete pointee_;
    }
}
template <typename T> T * smart_ptr<T>::get() const {
    return pointee_;
}

#endif // SMRT_PTR_H_
