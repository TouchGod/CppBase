// 给你两个集合，计算其并集，即 {A} + {B}。
// 注：不允许出现重复元素，但是  {A} 与 {B}之间可能存在相同元素。A = 1, 2, 3  B = 1 3 5

// 输入格式
// 输入数据分为三行，第一行有两个数字n,m(0 < n,m<=10000) ，分别表示集合A和集合B的元素个数。
// 后两行分别表示集合 A 和集合 B。每个元素为不超出int范围的整数，每个元素之间用一个空格隔开。

// 输出格式
// 输出一行数据，表示合并后的集合，要求从小到大输出，每个元素之间用一个空格隔开。

#include <iostream>
#include <set>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::set;

template <class Container>
void display(Container c)
{
    for (auto &ele : c)
    {
        cout << ele << " ";
    }
    cout << endl;
}

void test0()
{
    int n, m, temp;
    set<int> set1, set2;
    cin >> n >> m;
    for (int i = 0; i < n;)
    {
        cin >> temp;
        auto ret = set1.insert(temp);
        if (!ret.second)
        {
            cout << "重复元素，请重新输入" << endl;
            continue;
        }
        ++i;
    }
    for (int i = 0; i < m;)
    {
        cin >> temp;
        auto ret = set2.insert(temp);
        if (!ret.second)
        {
            cout << "重复元素，请重新输入" << endl;
            continue;
        }
        ++i;
    }

    set1.insert(set2.begin(), set2.end());
    display(set1);
}

int main()
{
    test0();
    return 0;
}