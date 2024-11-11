#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Point
{
public:
    Point()
        : _x(0), _y(0)
    {}

    Point(int x, int y)
        : _x(x), _y(y)
    {}

    void print() const
    {
        cout << "x=" << _x << ",";
        cout << "y=" << _y << endl;
    }

private:
    int _x;
    int _y;
};

void test0()
{
    Point pt1;
    Point pt2(1, 2);

    Point pt3(2, 5);
    Point pt4(10, 20);
    vector<Point> points{pt1, pt2, pt3};
    // 下标方式遍历
    for (int idx = 0; idx < points.size(); ++idx)
    {
        points[idx].print();
    }
    points.push_back(pt4);
    points.push_back({5, 8});
    // 迭代器方式遍历
    for (auto it = points.begin(); it != points.end(); ++it)
    {
        (*it).print();
        it->print();
    }

    vector<Point> p2{{1, 1}, {2, 2}, {3, 3}};
    // 增强for循环
    for (auto &pt : p2)
    {
        pt.print();
    }
}

void test1(){
	vector <vector <int>> nums {{0,1,2,3}, {5,6,7}, {10}};
	nums.push_back({1,2,3,4,5});
	for(auto & m : nums){
		cout << &m << endl;
		for(auto & n : m){
			cout << n << " ";
			cout << &n << endl;
		}
		cout << endl;
	}
}

int main()
{
    test0();
    test1();
    return 0;
}
