#include <iostream>
using std::cout;
using std::endl;

class Point {
public:
    // 将单例模式对象创立在堆上
	static Point * getInstance(){
		if (_pInstance == nullptr){
			_pInstance = new Point(0,0);
		}
		return _pInstance;
	}

	void init(int x, int y){
		_ix = x;
		_iy = y;
	}

	static void destory(){
		if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	void print() const
	{
		cout << "(" << _ix 
            << "," << _iy
			<< ")" << endl;
	}
private:
    // 构造函数和析构函数私有
    // 删除默认拷贝构造和默认赋值运算符函数
	Point(int x, int y)
	: _ix(x)
	, _iy(y)
	{}

	Point() = default;
	~Point() = default;
	Point(const Point & rhs) = delete;
	Point & operator=(const Point & rhs) = delete;

private:
	int _ix;
	int _iy;
	static Point * _pInstance;
};
Point * Point::_pInstance = nullptr;

void test0(){
	Point::getInstance()->print();
	Point::getInstance()->init(1,2);
	Point::getInstance()->print();
	Point::getInstance()->init(2,5);
	Point::getInstance()->print();

	// 多次destroy，也不会double free
	Point::destory();
	Point::getInstance()->print();
	Point::destory();
}

int main()
{
	test0();
    return 0;
}
