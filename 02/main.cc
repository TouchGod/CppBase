#include "add.hh"
#include <iostream>
using std::cout;
using std::endl;



int main()
{
	int a = 1;
	int b = 2;
	double c = 1.3;
	double d = 2.4;
	cout << a << "+" << b << " = " << MySpace::add(a,b) << endl;
	cout << c << "+" << b << " = " << MySpace::add(c,b) << endl;
	cout << a << "+" << d << " = " << MySpace::add(a,d) << endl;
	cout << a << "+" << d << "-1 = " << add(a,d) << endl;

    return 0;
}

