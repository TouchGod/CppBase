#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Computer {
public:
	static Computer * getInstance()
	{
		if (_pInstance == nullptr){
			_pInstance = new Computer("Apple", 20000);
			cout << "getInstance" << endl;
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
		}
		cout << "Destroy" << endl;
	}

	void init(const char * brand, double price)
	{
		if(_brand){
			delete [] _brand;
			_brand = nullptr;
		}
		_brand = new char[strlen(brand) + 1]();
		strcpy(_brand, brand);
		_price = price;
	}

	void print()
	{
		cout << "Brand: " << _brand << endl;
		cout << "Price: " << _price << endl;
		cout << endl;
	}

private:
	Computer(const char * brand, double price)
		: _brand(new char[strlen(brand) + 1]())
		  , _price(price)
	{
		strcpy(_brand, brand);
		cout << "Computer(const char *, double)" <<endl;
	}

	~Computer()
	{
		if(_brand){
			delete [] _brand;
			_brand = nullptr;
		}
		cout << "~Computer" << endl;
	}

	Computer(const Computer & rhs) = delete;
	Computer & operator=(const Computer & rhs) = delete;

	char * _brand;
	double _price;
	static Computer * _pInstance;
};
Computer * Computer::_pInstance = nullptr;


void test0(){
	//单例对象的规范使用方式
	Computer::getInstance()->print();
	Computer::getInstance()->init("Huawei", 10000);
	Computer::getInstance()->print();
	Computer::getInstance()->init("Lenovo", 12000);
	Computer::getInstance()->print();

	//即使多次调用，也不会出现double free
	Computer::destroy();
}

int main()
{
	test0();
	return 0;
}
