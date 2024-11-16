#include <pthread.h>
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
    static Computer *getInstance()
    {
        // pthread_once控制getInstance函数只执行一次
        pthread_once(&_once, init_once);
        return _pInstance;
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
    // 如果手动调用init_once创建对象
    // 没有通过getInstance创建对象
    // 实际上绕开了pthread_once的控制
    // 必然造成内存泄露
    // 需要将init_once私有
    static void init_once()
    {
        _pInstance = new Computer();
        atexit(destroy);
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
    static pthread_once_t _once;
};
Computer *Computer::_pInstance = nullptr;
pthread_once_t Computer::_once = PTHREAD_ONCE_INIT;

void test0()
{
    // 单例对象的规范使用方式
    Computer::getInstance()->print();
    Computer::getInstance()->init("Huawei", 10000);
    Computer::getInstance()->print();
    Computer::getInstance()->init("Lenovo", 12000);
    Computer::getInstance()->print();

    //destroy一旦被手动调用
    //后续再通过getInstance是不能创建出Singleton对象的
    /* Singleton::destroy(); */
    /* Singleton::getInstance()->init("HP",10000); */
    /* Singleton::getInstance()->print(); */
    /* Singleton::getInstance()->func(); */

    //如果手动调用init_r
    //那么会绕过pthread_once的管理，导致内存泄露
    /* Singleton::init_r(); */
    /* Singleton::init_r(); */
    /* Singleton::init_r(); */
}

int main()
{
    test0();
    return 0;
}
