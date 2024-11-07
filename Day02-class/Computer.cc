#include "Computer.hh"
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

void Computer::setBrand(const char *brand)
{
	if(_brand){
		delete[] _brand;
	}
	_brand = new char[strlen(brand) + 1]();
	strcpy(_brand, brand);
}

void Computer::setPrice(double price)
{
	_price = price;
}

void Computer::print()
{
	cout << "brand:" << _brand << endl;
	cout << "price:" << _price << endl;
}

Computer::Computer(const char *brand, double price)
	: _brand(new char[strlen(brand) + 1]()), _price(price)
{
	strcpy(_brand, brand);
	cout << "Computer(const char *,double)" << endl;
}

Computer::Computer()
	: _brand(new char[6]()), _price(20000)
{
	strcpy(_brand, "Apple");
	cout << "Computer" << endl;
}

Computer::Computer(const Computer &rhs)
	: _brand(new char[strlen(rhs._brand) + 1]()), _price(rhs._price)
{
	strcpy(_brand, rhs._brand);
	cout << "Computer(const Computer &)" << endl;
}

Computer &Computer::operator=(const Computer &rhs)
{
	//考虑自赋值
	if (this != &rhs)
	{
		delete[] _brand;
		_brand = new char[strlen(rhs._brand) + 1]();
		strcpy(_brand, rhs._brand);
		_price = rhs._price;
	}
	cout << "operator=" << endl;
	return *this;
}

Computer::~Computer()
{
	if (_brand)
	{
		delete[] _brand;
		_brand = nullptr;
	}
	cout << "~Computer()" << endl;
}
