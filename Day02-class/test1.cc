#include "Computer.hh"

void test1(){
    Computer pc;
    pc.print();
    Computer pc2 = pc;
    pc2.print();
    pc2.setBrand("Lenovo");
    pc2.setPrice(12000);
    pc2.print();
}