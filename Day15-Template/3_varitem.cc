#include <iostream>
using std::cout;
using std::endl;

double add()
{
	return 0;
}

template <class T, class ...Args>
double add(T x, Args ...args)
{
	return x + add(args...);
}
void test0(){
	int a = 1;
	int b = 2;
	double c = 32.41231;
	double d = 2.8640;
	cout << a+b+c+d << endl;
}

int main()
{
	test0();
    return 0;
}

