#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
    //static const int b = 2;
    virtual void f(){cout << "a0" << endl;}
    virtual void g(){cout << "a1" << endl;}
    virtual void h(){cout << "a2" << endl;}
};
class B: public A
{
public:
    void g(){cout << "b1" << endl;} 
};
class C: public B
{
public:
    void h(){cout << "c2" << endl;}
};

int main()
{
    //cout << sizeof(A) << sizeof(B) << sizeof(C) << endl;
    A a;
    B b;
    C c;
    uint64_t* pa =(uint64_t*) &a;
    uint64_t* pb =(uint64_t*) &b;
    uint64_t* pc =(uint64_t*) &c;
    cout << pa << endl;
    cout << pb << endl;
    cout << pc << endl;
}
