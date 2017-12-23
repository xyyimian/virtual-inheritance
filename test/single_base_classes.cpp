#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
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
    cout << "class A size: " << sizeof(A) << endl;
    cout << "class B size: " << sizeof(B) << endl;
    cout << "class C size: " << sizeof(C) << endl;
    A a;
    B b;
    C c;
    uint64_t a_vptr_address =*((uint64_t*)&a);      //address of vptr a
    uint64_t b_vptr_address =*((uint64_t*)&b);      //address of vptr b
    uint64_t c_vptr_address =*((uint64_t*)&c);      //address of vptr c
    uint64_t* a_vptr = (uint64_t*)a_vptr_address;
    uint64_t* b_vptr = (uint64_t*)b_vptr_address;
    uint64_t* c_vptr = (uint64_t*)c_vptr_address;
    cout << "A func f:" << a_vptr[0] << endl;
    cout << "B func f:" << b_vptr[0] << endl;
    cout << "C func f:" << c_vptr[0] << endl;
    cout << "A func g:" << a_vptr[1] << endl;
    cout << "B func g:" << b_vptr[1] << endl;
    cout << "C func g:" << c_vptr[1] << endl;
    cout << "A func h:" << a_vptr[2] << endl;
    cout << "B func h:" << b_vptr[2] << endl;
    cout << "C func h:" << c_vptr[2] << endl;
}