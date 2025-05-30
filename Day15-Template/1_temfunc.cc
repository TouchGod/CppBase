#include <iostream>
#include <set>
using std::pair;
using std::set;
using std::cout;
using std::endl;

template <class T>
T add(T t1,T t2)
{
	return t1 + t2;
}
template <>
set<int> add<set<int>>(set<int> s1,set<int> s2)
{
	/* for(auto & a : s2){ */
	/* 	s1.insert(a); */
	/* } */
	s1.insert(s2.begin(), s2.end());
	return s1;
}

void test0(){
	int ia = 1;
	int ib = 2;
	double da = 3.14;
	double db = 2.74;
	set<int> sa = {1,3,9};
	set<int> sb = {5,9};


	cout << "ia + ib=" << ia + ib << endl;
	cout << "da + db=" << da + db << endl;
	set<int> sc = add(sa,sb);
	for (auto & ele : sc){
		cout << ele << " ";
	}
	cout << endl;
}

int main()
{
	test0();
	return 0;
}

