#include "String.hh"
#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

void test0()
{
    String str1;
    String str2 = "good";
    String str3 = str2;
    cout << strcmp("good", "good") << endl;
    cout << (str2 == str3) << endl;
    cout << (str2 != str3) << endl;
    str1 = "hello";
    /* str1.print(); */
    cout << str1 << endl;
    cin >> str1;
    str1 += str2;
    str1.print();
    str1 += "nice";
    str1.print();
    cout << str1[5] << endl;
    const char a = str1[2];
    cout << "const a = " << a << endl;
    cout << (str1 + str2) << endl;
}

int main()
{
    test0();
    return 0;
}
