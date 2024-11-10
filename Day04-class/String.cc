#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class String
{
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print();
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

String::String()
	: _pstr(new char[1]())
{}

String::String(const char *pstr)
	: _pstr(new char[strlen(pstr) + 1]())
{
	strcpy(_pstr, pstr);
}

String::String(const String &rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
{
	strcpy(_pstr, rhs._pstr);
}

String & String::operator=(const String &rhs)
{
	if (_pstr){
		delete [] _pstr;
		_pstr = nullptr;
	}
	_pstr = new char[strlen(rhs._pstr) + 1]();
	strcpy(_pstr, rhs._pstr);
	return *this;
}

String::~String()
{
	if (_pstr){
		delete [] _pstr;
		_pstr = nullptr;
	}
}

void String::print()
{
	printf("%s\n", _pstr);
}

size_t String::length() const
{
	return strlen(_pstr);
}

const char * String::c_str() const
{
	return _pstr;
}

void test0(){
	String str1;
    cout << str1.length();
    str1.print();
    cout << str1.length() << endl;


	String str2 = "Hello,world";
	String str3("wangdao");

	str2.print();
	str3.print();
	cout << str2.length() << endl;
	cout << str3.length() << endl;

	String str4 = str3;
	str4.print();

	str4 = str2;
	str4.print();
	
	const char *str = str4.c_str();
	printf("%s\n", str);
}

int main()
{
	test0();
    return 0;
}
