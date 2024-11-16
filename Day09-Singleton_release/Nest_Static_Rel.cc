#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
    static Computer *getInstance()
    {
        if (_pInstance == nullptr)
        {
            _pInstance = new Computer();
            cout << "getInstance" << endl;
        }
        return _pInstance;
    }

    /* static void destroy() */
    /* { */
    /* 	if(_pInstance){ */
    /* 		delete _pInstance; */
    /* 		_pInstance = nullptr; */
    /* 	} */
    /* 	cout << "Destroy" << endl; */
    /* } */

    void init(const char *brand, double price)
    {
        if (_brand)
        {
            delete[] _brand;
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
    // 嵌套类
    class AutoRelease
    {
    public:
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if (_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

    Computer(const char *brand = "Apple", double price = 20000)
        : _brand(new char[strlen(brand) + 1]()), _price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *, double)" << endl;
    }

    ~Computer()
    {
        if (_brand)
        {
            delete[] _brand;
            _brand = nullptr;
        }
        cout << "~Computer" << endl;
    }

    Computer(const Computer &rhs) = delete;
    Computer &operator=(const Computer &rhs) = delete;

    char *_brand;
    double _price;
    static Computer *_pInstance;
    static AutoRelease _ar;
};
Computer *Computer::_pInstance = nullptr;
Computer::AutoRelease Computer::_ar;

void test0()
{
    // 单例对象的规范使用方式
    Computer::getInstance()->print();
    Computer::getInstance()->init("Huawei", 10000);
    Computer::getInstance()->print();
    Computer::getInstance()->init("Lenovo", 12000);
    Computer::getInstance()->print();

    // 嵌套类 + 静态对象
    // 在静态对象被回收时，调用~AutoRelease()
    // 其中实现了destroy()功能，回收了堆空间
    /* Computer::destroy(); */
}

int main()
{
    test0();
    return 0;
}
