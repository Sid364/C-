#include <iostream>
#include "smrt_ptr.h"

using namespace std;
class A {
    public:
    int a;
    A(int arg) : a(arg) {}
};

void f(smart_ptr<A> ptr) {
    std::cout << "i'm in fuction";
}

int main() {
    cout << "Hello, World!" << endl;
    A *a = new A(2);
    A *b = new A(3);
    smart_ptr<A> s(new A(2));
    smart_ptr<A> p(nullptr);
    if (p == s) cout << "p == s \n";
    else cout << "p != s\n";
    p = s;
    //f(p);
    smart_ptr<A> q = p;
    cout << (p.get())->a << " \n";
    *p = *b;
    cout << (p.get())->a << "   " << (s.get())->a <<"  " << (*p).a <<"\n";
    if (p == s) cout << "p == s\n";
    if (s == p) cout <<"s == p\n";
    if  (p != s) cout << "p != s\n";
    if (p > s) cout << "p > s";
    if (p < s) cout << "p < s";
    if (s <= p) cout << "s <= p\n";
    if (p >= s) cout <<"p >= s\n";
    if (s >= p) cout << "s >= p\n";
    if (p <= s) cout << "p <= s\n";
    if (p == a) cout << "p == a\n";
    if (p != a) cout << "p != a\n";
    if (a != p) cout << "a != p\n";
    return 0;
}
