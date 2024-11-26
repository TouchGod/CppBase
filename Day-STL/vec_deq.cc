// 评委打分的例子：
// 要求：有五名选手ABCDE，10个评委打分，去掉最高分和最低分，求出每个选手的平均分。
// 思路：
// 1.创建Person类，定义name，score成员属性；创建五名选手存放到vector容器中；
// 2.遍历vector容器，首先10个评委的打分存放到deque容器中，sort算法对分数排序，去掉最高最低分；
// 3.deque容器遍历，进行剩余分数的累加，求平均；
// 4.输出每个选手的姓名，成绩

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>

using std::cout;
using std::deque;
using std::endl;
using std::string;
using std::uniform_real_distribution;
using std::vector;

class Person
{
public:
    Person(const string name, const double score = 0)
        : _name(name), _score(score)
    {}

    Person(const Person &rhs)
        : _name(rhs._name), _score(rhs._score)
    {}

    void set_score(const double &rhs)
    {
        _score = rhs;
    }

    void print() const
    {
        cout << "|" << "name: " << _name << endl;
        cout << "|" << "score:" << _score << endl;
        cout << endl;
    }

private:
    string _name;
    double _score;
};

// 测试函数，用于演示如何为一组人员生成并处理分数
void test0()
{
    // 创建一个Person对象的vector容器，用于存储人员信息
    vector<Person> person;
    person.push_back({"A"});
    person.push_back({"B"});
    person.push_back({"C"});
    person.push_back({"D"});
    person.push_back({"E"});

    // 初始化随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());

    // 创建一个均匀分布的实数分布器，用于生成6到10之间的随机分数
    uniform_real_distribution<double> dis(6, 10);

    // 遍历人员容器，为每个人员生成并处理分数
    for (auto &p : person)
    {
        // 创建一个双端队列，用于存储每个人员的10个随机分数
        deque<double> sc;

        // 生成10个随机分数，并添加到队列中
        for (int i = 0; i < 10; ++i)
        {
            sc.push_back(dis(gen));
        }

        // 对分数进行排序，以便后续去除最高和最低分
        sort(sc.begin(), sc.end());

        // 移除队列中的最低分和最高分，以减少极端值的影响
        sc.pop_front();
        sc.pop_back();

        // 初始化总分变量，用于累加剩余8个分数的总和
        double total = 0;

        // 遍历剩余的分数，计算总和
        for (auto &s : sc)
        {
            total += s;
        }

        // 计算平均分，并设置为人员的分数
        p.set_score(total / 8);

        // 打印人员信息，包括姓名和计算后的平均分数
        p.print();
    }
}

int main()
{
    test0();
    return 0;
}


