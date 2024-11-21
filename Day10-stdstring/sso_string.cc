#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ostream;

class String
{
public:
    String(const char *pstr)
        : _size(strlen(pstr))
        , _capacity(strlen(pstr) > 15 ? strlen(pstr) : 15)
    {
        if (strlen(pstr) > 15)
        {
            _buffer._pointer = new char[strlen(pstr) + 1]();
            strcpy(_buffer._pointer, pstr);
        }
        else
        {
            memset(_buffer._local, 0, sizeof(_buffer._local));
            strcpy(_buffer._local, pstr);
            // _buffer._pointer = nullptr;
        }
        // 共用体的特性：
        // 1.所有成员都存在同一内存空间上，
        // 一次只能使用一个成员
        // 2.对union的某个成员进行写操作
        // 可能会导致整个union的内存被重新初始化
    }

    String(const String &rhs)
    : _size(rhs._size)
    , _capacity(rhs._capacity)
    {
        if (rhs._size > 15)
        {
            _buffer._pointer = new char[rhs._size + 1]();
            strcpy(_buffer._pointer, rhs._buffer._pointer);
        }
        else
        {
            // memcpy(_buffer._local, rhs._buffer._local, rhs._size);
            strcpy(_buffer._local, rhs._buffer._local);
        }
    }

    ~String()
    {
        //对于短字符串，_local保存了内容，
        //会导致_pointer也不再是空指针
        //这种情况也不应该直接使用_pointer这个成员
        /* if(_buffer._pointer){ */
        if (_size > 15)
        {
            delete[] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }

    size_t size()
    {
        return _size;
    }

    size_t capacity()
    {
        return _capacity;
    }
    char &operator[](size_t idx)
    {
        if(idx > _size - 1){
            cout << "out of range!" << endl;
            static char nullchar = '\0';
            return nullchar;
        }

        if (_size <= 15)
        {
            return _buffer._local[idx];
        }
        else
        {
            return _buffer._pointer[idx];
        }
    }

    friend ostream &operator<<(ostream &os, const String &rhs);

private:
    union Buffer
    {
        char *_pointer;
        char _local[16];
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

ostream &operator<<(ostream &os, const String &rhs)
{
    if (rhs._size > 15)
    {
        os << rhs._buffer._pointer;
    }
    else
    {
        os << rhs._buffer._local;
    }
    return os;
}

void test0()
{
    String str1("hello");
    String str2("hello,world!!!!!");

    cout << "str1.size:" << str1.size() << endl;
    cout << "str2.size:" << str2.size() << endl;
    cout << "str1.capacity:" << str1.capacity() << endl;
    cout << "str2.capacity:" << str2.capacity() << endl;

    cout << str1 << endl;
    cout << &str1 << endl;
    printf("%p\n",&str1[0]);
    cout << str1[0] << endl;
    str1[0] = 'H';
    cout << str1 << endl;

    cout << endl;
    cout << str2 << endl;
    cout << &str2 << endl;
    printf("%p\n",&str2[0]);
    cout << str2[0] << endl;
    str2[0] = 'X';
    cout << str2 << endl;

    cout << endl;
    String str3 = str1;
    cout << str3 << endl;
    printf("%p\n",&str3[0]);
    cout << "str3.size:" << str3.size() << endl;
    cout << "str3.capacity:" << str3.capacity() << endl;

    String str4 = str2;
    cout << str4 << endl;
    printf("%p\n",&str4[0]);
    cout << "str4.size:" << str4.size() << endl;
    cout << "str4.capacity:" << str4.capacity() << endl;
}

int main()
{
    test0();
    return 0;
}