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

};

int main(){
	
	C* pc = 0;
	B* pb = 0;
	if(pb == 0){
		cout << "pb is assigned to zero" << endl;
	}
	pb = pc;		//pb = (pc == 0)?0:(B*)((char*)pc + delta(B));
	if(pb == 0){
		cout << "pb is casted to zero" << endl;		//can be normally operated
	}
}
