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

void test2()
{
    CowString s1("hello");
    CowString s2 = s1;
    cout << s1[0] << endl;
    s1[0] = 'H';
    cout << s1 << endl;
    cout << s2 << endl;
}
int main()
{
    test2();

    return 0;
}