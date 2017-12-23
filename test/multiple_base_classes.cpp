#include <iostream>
using namespace std;

class A{
public:
	int ii;
};

class B{
public:
	char* ii;
};

class C:public A, public B{
    int c;
};

int main(){
	C* pc = 0;
	B* pb = 0;
	cout << "pc is assigned to " << (uint64_t)pc << endl;
	pb = pc;		//pb = (pc == 0)?0:(B*)((char*)pc + delta(B));
	cout << "pb is casted to " << (uint64_t)pb << endl;		//can be normally operated
	pc = (C*)0xffff;
	cout << "pc is assigned to " << hex << (uint64_t)pc << endl;
	pb = pc;
	cout << "pb is casted to " << (uint64_t)pb << endl;
}
