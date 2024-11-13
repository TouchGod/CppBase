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
	cin >> num;
	while (!cin.eof())
	{
		if (cin.bad())
		{
			cout << "There is a broken stream" << endl;
			return;
		}
		else if (cin.fail())
		{
			// 重置流状态
			cin.clear();
			// 清除缓冲
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please input a int num" << endl;
			cin >> num;
		}
		else
		{
			cout << "num is " << num << endl;
			break;
		}
	}
}

void test1()
{
	cout << "Please input a int num" << endl;
	int num;
	// 逗号表达式的使用
	while (cin >> num, !cin.eof())
	{
		if (cin.bad())
		{
			cout << "There is a broken stream" << endl;
			return;
		}
		else if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please input a int num" << endl;
		}
		else
		{
			cout << "num is " << num << endl;
			break;
		}
	}
}

void test2()
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

int main()
{
	// test0();
	// test1();
	test2();
	return 0;
}
