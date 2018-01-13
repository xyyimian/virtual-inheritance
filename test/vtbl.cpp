/// the output of the program can be operated only in windows
#include <iostream> 

using namespace std;

class Base{
public:
	virtual void f(){
		cout << "Base::f!" << endl;
	}
	virtual void g(){
		cout << "Base::g!" << endl;
	}
	virtual void h(){
		cout << "Base::h!" << endl;
	}
};

class Base2{
public:
	virtual void f(){
		cout << "Base2::f!" << endl;
	}
	virtual void g(){
		cout << "Base2::g!" << endl;
	}
	virtual void h(){
		cout << "Base2::h!" << endl;
	}	
};

class Derived{
public:
	virtual void f(){
		cout << "Derived::f!" << endl;
	}
	virtual void g1(){
		cout << "Derived::g1!" << endl;
	}	

};

int main(){
	Base b;
	Derived d;
	cout << "the addr of vbtl is :" << (int*)(&b) << endl;
	typedef void(*Fun)(void);
	Fun pFun = NULL;
	pFun = (Fun)*((int*)*(int*)(&b));
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d));
	pFun();
	pFun = (Fun)*((int*)*((int*)(&d) + 4));
}