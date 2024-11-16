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
            cout << "getInstance()" << endl;
            // 注册程序正常终止时要调用的函数
            atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy()
    {
        if (_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
        cout << "Destroy" << endl;
    }

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
};
Computer *Computer::_pInstance = nullptr;
// 饱汉式(懒汉式) —— 懒加载，在需要使用Singleton对象时才创建

// 饿汉式 —— 即使代码中不使用Singleton对象，
// 也把这个堆对象创建出来
// 即使是多线程环境，也能够确保这次getInstance的调用是第一次
// Singleton * Singleton::_pInstance = Singleton::getInstance();

void test0()
{
    // 单例对象的规范使用方式
    Computer::getInstance()->print();
    Computer::getInstance()->init("Huawei", 10000);
    Computer::getInstance()->print();
    Computer::getInstance()->init("Lenovo", 12000);
    Computer::getInstance()->print();

    // atexit注册了destroy函数
    // 相当于有了一次必然会进行的destroy（程序结束时）
    // 即使手动调用了destroy
    // 因为安全回收的机制，也不会有问题。
    Computer::destroy();
}

int main()
{
    test0();
    return 0;
}
