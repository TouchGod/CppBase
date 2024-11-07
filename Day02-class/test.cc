#include "Computer.hh"
#include <iostream>
using std::cout;
using std::endl;

extern void test1(); 

void test0(){
    Computer pc("Huawei", 10000);
    pc.print();
	Computer pc2;
	pc2.print();
	pc = pc2;
	pc.print();
}

int main(void){
    test0();
    cout << endl;
    test1();
    return 0;
}
