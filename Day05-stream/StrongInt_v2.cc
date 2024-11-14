#include <iostream>
#include <sstream>
#include <limits>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::string;

void test0()
{
    cout << "Please input a int num" << endl;
    int num;
    string s_num;
    while (cin >> s_num, !cin.eof())
    {
        if (cin.bad())
        {
            cout << "There is a broken stream" << endl;
            return;
        }
        bool flag = true;
        for (auto &n : s_num)
        {
            if (n < '0' || n > '9')
            {
                flag = false;
            }
        }

        if (flag)
        {
            istringstream iss(s_num);
            iss >> num;
            cout << "The num is " << num << endl;
            break;
        }
        else
        {
            cout << "Not int, try again." << endl;
            s_num.clear();
        }
    }
}

void test1()
{
    cout << "Please input a int num" << endl;
    int num;
    string s_num;
    while (cin >> s_num, !cin.eof())
    {
        if (cin.bad())
        {
            cout << "There is a broken stream" << endl;
            return;
        }

        auto it = s_num.begin();
        for (; it != s_num.end(); ++it)
        {
            if (!isdigit(*it))
            {
                break;
            }
        }

        if (it == s_num.end())
        {
            istringstream iss(s_num);
            iss >> num;
            cout << "The num is " << num << endl;
            return;
        }
        else
        {
            cout << "Not int, try again." << endl;
        }
    }
}

int main()
{
    test1();
    return 0;
}