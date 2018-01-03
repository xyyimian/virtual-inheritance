## C++的多重继承实现机制

### 内存分布
给定两个类：
```
class A {...};
class B {...};
```
多重继承定义为
```
class C : A , B {...};
```
如果不考虑构造函数的生成次序等作用，其等价于
```
class C : B, A {....};
```

对于一个C对象，其内存分布为：
```
------------------------------------
|								   |
|        members of class A  	   |
|								   |
------------------------------------
|								   |
|        members of class B 	   |
|								   |
------------------------------------
|								   |
|        members of class C 	   |
|								   |
------------------------------------
```
### 成员调用
下面一个C对象对自己成员的调用，其中假设C无自己的成员，C继承了B的bf成员
```
C* pc;
pc -> bf(2);
```
在编译器的内部实现中，相当于计算出了相对指针pc的一个偏移量（记作delta（B)，其加到pc上得到bf，delta对编译器已知，所以上述调用会被转化为
```
bf__F1B((B*)((Char*)pc + delta(B)),2);
```
其中记
```
 p = (B*)((Char*)pc + delta(B))

 pc---------->	------------------------------------
				|								   |
				|        members of class A  	   |
				|								   |
p------------>  ------------------------------------
				|								   |
				|        members of class B 	   |
				|								   |
				------------------------------------
				|								   |
				|        members of class C 	   |
				|								   |
				------------------------------------
```
注意到，这种成员继承方式没有造成空间的浪费，对于时间上也仅仅是在每次对成员进行调用时会计算一下p造成的开销
### 二义性
考虑A和B有同名成员的情形
```
class A {int ii; };
class B {char * ii; };
class C : A, B {};
```
这样C的对象在调用ii时就会出现二义性：
```
C* pc;
pc->ii;
```
编译器报错，要求显式声明
```
pc->A::ii;
pc->B::ii;
```
要调用的成员是A,B中同名的函数时要求同上
```
pc->A::f();
pc->B::f();
```
一种比较好的解决方法是，在class C中重载该成员,让程序员来决定要调用的是哪个f();
```c++
class C: A, B {
	int f(){
		return A::f();	//choose A::f();
	}
};
C* pc;
pc->f();
```
因为它将派生类函数的含义局部化，无需作上述delta的计算，避免了二义性。
### 类型转换
类型转换实质就是delta的计算
```c++
C* pc;
B* pb;
pb = (B*)pc;		//pb  = (B*)((char*)pc + delta(B))
pb = pc;			//pb = (B*)((char*)pc + delta(B))
pc = pb;			//error: 基类指针不能被隐式转化为派生类
pc = (C*) pb;		//pc = (C*)((char *)pb - delta(B))
```
需要注意的一点是，无论是C还是C++, 类型转化都是一种操作，用以把一个值转化为另一个值，而不仅仅是对位模式的重新解释。就像（float)(int)0.2 != 0.2, (char\*)(B\*)v != (char\*)v;但是如果B是C的基类，有(B\*)v == (C\*)v == v.

### 零值指针
值为零的指针在多继承中会导致问题。考虑将上述规则应用于零值指针：
```c++
C* pc = 0;
B* pb = 0;
if(pb == 0){...}
pb = pc;		//pb = (B*)((char*)pc + delta(B));
if(pb == 0){...}
```
这样就会让第二个if语句判断为false。
所以对于编译器来说，只能将隐式转换设计得更复杂一些，额外考虑这种特殊情形
```c++
C* pc = 0;
B* pb = 0;
if(pb == 0){...}
pb = pc;		//pb = (pc == 0)?0:(B*)((char*)pc + delta(B));
if(pb == 0){...}
```
这样又会增加复杂度和运行时时间

### 虚函数

* 内存模型

当成员函数为虚函数时，考虑下面的例子

```
class A{ virtual void f(); };
class B{ virtual void f(); virtual void g(); };
class : A, B{void f();};
A* pa = new C();
B* pb = new C();
C* pc = new C();
pa->f();
pb->f();
pc->f();
```

`pa`,`pb`,`pc`在调用f()时，都应该是调用`C::f()`。

然而，当pb调用f()时，编译器无法知晓当前的指针pb是指向一个类型为C的对象或是类型为B的对象，因此不能单纯地减去常数delta(B)。我们需要存储delta(B)，而由于只有调用虚函数时需要用到delta(B)，将其存储在vtbl(table of virtual functions)是最佳的。

vbtl的条目结构如下：

```c++
struct vbtl_entry{
  	void (*fct)();		//function pointer
  	int delta;
};
```

C的内存模型如下：

```
--------------
|			|			vtbl:
|	vptr	---------->	----------------
|	A part	|			| C::f	|	0	|
|			|			----------------
--------------
|			|
|	vptr	---------->	-----------------
|	B part	|			|C::f	|-delta(B)|
|			|			|B::g	|	0	|
--------------			-------------------
|	C part	|
--------------
```

调用pb->f()时，相当于

```c++
pb->f();			//call C::f
//vtbl_entry* vt = pb->vptr[index(f)];
//(*vt->fct)((B*)((chat*)pb+vt->delta))
```

可以看到，对象C中对象B的vtbl和单纯的对象B对应的vtbl是不一样的。此时我们需要为每一个基类和当前派生类分配一个vtbl。

* 二义性

考虑这样一个例子

```c++
class A{virtual void f();};
class B{virtual void f();};
class C : A, B{void f();};
C* pc = new C;
pc->f();
```

若需要调用基类的虚函数，需显示地声明函数命名空间，此时命名空间会压制`virtual`的表达。例如：`pc->A::f()`，`pc->B::f()`。

若需要调用派生类自己`override`的函数，直接调用`pc->f()`是无二义的。如果派生类未定义自己的函数，那么此时需加上命名空间消除二义性。例如：

```c++
class A{virtual void f();};
class B{virtual void f();};
class C: A, B{};

C* pc = new C;
pc->f();				//error, ambiguous
A* pa = pc;
pa->f();				//not ambiguous, calls A::f()
```

