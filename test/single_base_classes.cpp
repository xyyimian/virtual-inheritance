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
    uint32_t a_vptr_address =*((uint32_t*)&a);      //address of vptr a
    uint32_t b_vptr_address =*((uint32_t*)&b);      //address of vptr b
    uint32_t c_vptr_address =*((uint32_t*)&c);      //address of vptr c
    uint32_t* a_vptr = (uint32_t*)a_vptr_address;
    uint32_t* b_vptr = (uint32_t*)b_vptr_address;
    uint32_t* c_vptr = (uint32_t*)c_vptr_address;
    cout << std::hex;
    cout << "A func f: 0x" << a_vptr[0] << endl;
    cout << "B func f: 0x" << b_vptr[0] << endl;
    cout << "C func f: 0x" << c_vptr[0] << endl;
    cout << "A func g: 0x" << a_vptr[1] << endl;
    cout << "B func g: 0x" << b_vptr[1] << endl;
    cout << "C func g: 0x" << c_vptr[1] << endl;
    cout << "A func h: 0x" << a_vptr[2] << endl;
    cout << "B func h: 0x" << b_vptr[2] << endl;
    cout << "C func h: 0x" << c_vptr[2] << endl;
}
