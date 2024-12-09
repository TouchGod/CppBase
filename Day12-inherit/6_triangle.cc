#include <iostream>
#include <cstring>
#include <cmath>
using std::cout;
using std::endl;
using std::string;

class Point
{
public:
	Point(const float x, const float y)
		: _ix(x), _iy(y)
	{
	}
	friend class Line;

private:
	float _ix;
	float _iy;
};

class Color
{
public:
	Color(const string &color)
		: _color(color)
	{
	}

	void show_color()
	{
		cout << "The Color is " << _color << endl;
	}

private:
	string _color;
};

class Line
{
public:
	Line(float x1, float y1, float x2, float y2)
		: _start(x1, y1), _end(x2, y2)
	{
	}

	float getline()
	{
		return sqrt(pow((_start._ix - _end._ix), 2) + pow((_start._iy - _end._iy), 2));
	}

private:
	Point _start;
	Point _end;
};

class Triangle
	: public Line,
	  public Color
{
public:
	Triangle(const float x1, float y1, float x2, float y2, string color, const float height)
		: Line(x1, y1, x2, y2), Color(color), _height(height)
	{
	}

	void print_perimeter()
	{
		float line = getline();
		float hypotenuse = sqrt(pow(line, 2) + pow(_height, 2));
		cout << "The Triangle's perimeter is ";
		cout << line + _height + hypotenuse << endl;
	}

	void print_area()
	{
		cout << "The Triangle's area is ";
		cout << _height * getline() / 2 << endl;
	}

private:
	float _height;
};
void test0()
{
	Triangle t(0, 0, 3, 0, "red", 4);
	t.show_color();
	t.print_area();
	t.print_perimeter();
}

int main()
{
	test0();
	return 0;
}
