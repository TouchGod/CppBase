#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
	virtual void print() {
		cout << "Base::print()" << endl;
		}
	virtual void display() {
		cout << "Base::display()" << endl;
	}
	virtual void show() {
		cout << "Base::show()" << endl;
	}
private:
	long _base = 10;
};

class Derived
: public Base
{
/* public: */
    //虚函数表中虚函数入口地址的排布顺序
    //与基类中虚函数声明顺序一致
    //如果派生类中定义了新的虚函数
    //会往虚表中最后一条内容后面放
	virtual void display() {
		cout << "Derived::display()" << endl;
	}
	virtual void show() {
		cout << "Derived::show()" << endl;
	}
 	virtual void print() {
		cout << "Derived::print()" << endl;
	}

    virtual void func()
    {
        cout << "Derived::func()" << endl;
    }
private:
	long _derived = 100;
};

void test0(){
    /* cout << sizeof(Base) << endl; */
    /* cout << sizeof(Derived) << endl; */

	const char * str1 = "find";
	cout << reinterpret_cast<uintptr_t>(&"find") << endl;
	cout << endl;
    Derived d1;
    long * pderived = (long*)(&d1);
    cout << pderived[0] << endl;
    cout << pderived[1] << endl;
    cout << pderived[2] << endl;
    /* pderived[2] = 1000; */

    cout << endl;
    long * pVtable = (long*)(pderived[0]);
    /* cout << pVtable << endl; */
    cout << pVtable[0] << endl;
    cout << pVtable[1] << endl;
    cout << pVtable[2] << endl;

    cout << endl;
    typedef void (*Function)();
    Function fp = (Function)(pVtable[0]);
    fp();
    fp = (Function)(pVtable[1]);
    fp();
    fp = (Function)(pVtable[2]);
    fp();
    fp = (Function)(pVtable[3]);
    fp();

	int * n = new int(1);
	cout << reinterpret_cast<uintptr_t>(n) << endl;

	static int a = 10;
	cout << reinterpret_cast<uintptr_t>(&a) << endl;

	const char * str = "hello";
	cout << reinterpret_cast<uintptr_t>(&str) << endl;
	cout << reinterpret_cast<uintptr_t>(&"hello") << endl;



}

int main(void){
    test0();
	printf("%p\n", &main);
    return 0;
}
