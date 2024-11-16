#include <iostream>
using std::cout;
using std::endl;

// 前向声明
class Point;

class Complex
{
    int _real;
    int _image;

public:
    Complex(int real, int image)
        : _real(real), _image(image) {}

    void print()
    {
        cout << "(" << _real << ",";
        cout << _image << ")" << endl;
    }

    // 2
    Complex(const Point &);

    // 3
    Complex &operator=(const Point &);
};

class Point
{
    int _x;
    int _y;

public:
    Point(int x, int y)
        : _x(x), _y(y) {}

    // 1
    operator Complex()
    {
        cout << "类型转换函数 P->C" << endl;
        return Complex(_x, _y);
    }

    // 2
    friend class Complex;
};

// 2
Complex::Complex(const Point &rhs)
    : _real(rhs._x), _image(rhs._y)
{
    cout << "特殊的构造函数" << endl;
}

// 3
Complex &Complex::operator=(const Point &rhs)
{
    cout << "特殊的赋值运算符函数" << endl;
    _real = rhs._x;
    _image = rhs._y;
    return *this;
}

void test0()
{
    Point pt(8, 9);
    Complex cx(4, 6);
    cx = pt;
    cx.print();

    // 1.类型转换函数
    // 2.隐式转换
    // 3.运算符重载
}

int main()
{
    test0();
    return 0;
}