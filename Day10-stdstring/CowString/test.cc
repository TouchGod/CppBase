#include "CowString.h"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    CowString str1;
    CowString str2 = str1;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << "str1.use_count:" << str1.use_count() << endl;
    cout << "str2.use_count:" << str2.use_count() << endl;
    cout << endl;
    CowString str3("hello");
    CowString str4 = str3;
    cout << "str3:" << str3 << endl;
    cout << "str4:" << str4 << endl;
    cout << "str3.use_count:" << str3.use_count() << endl;
    cout << "str4.use_count:" << str4.use_count() << endl;
}

void test1()
{
    CowString str3("hello");
    CowString str4;
    cout << "str4:" << str4 << endl;
    cout << "str4.use_count:" << str4.use_count() << endl;
    str4 = str3;
    cout << "str3:" << str3 << endl;
    cout << "str4:" << str4 << endl;
    cout << "str3.use_count:" << str3.use_count() << endl;
    cout << "str4.use_count:" << str4.use_count() << endl;
}

// 处理方式：代理模式区分读写
// []运算符重载 + 赋值运算符重载
// 输出采用<<运算符重载
void test2()
{
    CowString s1("hello");
    CowString s2 = s1;
    cout << s1[0] << endl;
    s1[0] = 'H';
    cout << s1 << endl;
    cout << s2 << endl;
}

void test3()
{
    CowString s1("hello");
    CowString s2 = s1;

    //此时输出的操作也可以通过类型转换函数解决了
    //可以取消CharProxy对输出流运算符的重载
    cout << s1[0] << endl;
    s1[0] = 'H';
    cout << s1 << endl;
    cout << s2 << endl;

    //问题
    //可以通过类型转换函数解决
    char ch = 'a';
    ch = s1[0];
    cout << ch << endl;
}
int main()
{
    // test2();
    test3();
    return 0;
}