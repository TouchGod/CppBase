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
            _pInstance = new Computer("Apple", 20000);
            cout << "getInstance" << endl;
        }
        return _pInstance;
    }

    // 删除destory函数，避免手动调用导致double free
    // static void destroy()
    // {
    //     if (_pInstance)
    //     {
    //         delete _pInstance;
    //         _pInstance = nullptr;
    //     }
    //     cout << "Destroy" << endl;
    // }

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

    // 声明友元类，当AutoRelease对象释放
    // 自动调用Computer析构函数，回收堆空间
    friend class AutoRelease;

private:
    Computer(const char *brand, const double price)
        : _brand(new char[strlen(brand) + 1]()), _price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *, double)" << endl;
    }

    Computer()
        : _brand(new char[1]()), _price() {}

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
};
Computer *Computer::_pInstance = nullptr;

class AutoRelease
{
public:
    AutoRelease(Computer *p)
        : _pcom(p)
    {
        cout << "AutoRelease()" << endl;
    }

    ~AutoRelease()
    {
        if (_pcom)
        {
            delete _pcom;
            _pcom = nullptr;
        }
        cout << "~AutoRelease()" << endl;
    }

private:
    Computer *_pcom;
};

void test0()
{
    AutoRelease ar(Computer::getInstance());
    Computer::getInstance()->print();
    Computer::getInstance()->init("Huawei", 10000);
    Computer::getInstance()->print();
    Computer::getInstance()->init("Lenovo", 12000);
    Computer::getInstance()->print();
    // Computer::destroy();
}

int main()
{
    test0();
    return 0;
}
