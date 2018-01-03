#include <iostream>
using std::cout;
using std::endl;

class A{
public:
	int ii;
	int a;
	void f(){cout << "func a" << endl;}
};

class B{
public:
	int* ii;
	void f(){cout << "func b" << endl;}
};

class C:public A, public B{
    int c;
};

int main(){
	C* pc = 0;
	B* pb = 0;
	cout << sizeof(A) << '\t' << sizeof(B) << '\t' << sizeof(C) << endl;
	cout << "pb = (pc == 0)?0:(B*)((char*)pc + delta(B));" << endl;
	cout << std::hex;
	cout << "pc is assigned to " << (uint32_t)pc << endl;
	pb = pc;
	cout << "pb is casted to " << (uint32_t)pb << endl;		//can be normally operated
	pc = (C*)0xffff;
	cout << "pc is assigned to " << (uint32_t)pc << endl;
	pb = pc;
	cout << "pb is casted to " << (uint32_t)pb << endl;
	C c;
	c.A::f();
	c.B::f();
}
