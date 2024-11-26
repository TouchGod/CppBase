// 学生成绩管理系统

// 题目要求：
// 1 .制作一个学生成绩单管理系统
// 2 .将student自定义数据类型进行排序，student中属性有姓名、语文成绩、数学成绩、英语成绩、总成绩。
// **排序规则**：按照总成绩sum进行降序，如果总成绩sum相同按照语文成绩进行降序

#include <iostream>
#include <string>
#include <list>

using std::cout;
using std::endl;
using std::list;
using std::ostream;
using std::string;

class Student
{
public:
    Student(const string &name, const int &age, const double &chinese, const double &math, const double &english)
        : _name(name), _age(age), _chinese(chinese), _math(math), _english(english)
    {}

    double get_sum() const
    {
        return _chinese + _math + _english;
    }

    double get_chinese() const
    {
        return _chinese;
    }
    double get_math() const
    {
        return _math;
    }

    double get_english() const
    {
        return _english;
    }
    friend ostream &operator<<(ostream &, const Student &);

private:
    string _name;
    int _age;
    double _chinese;
    double _math;
    double _english;
};

ostream &operator<<(ostream &os, const Student &rhs)
{
    os << rhs._name << " " << rhs._age << " ";
    os << rhs._chinese << " " << rhs._math << " " << rhs._english << endl;
    return os;
}

// 普通函数形式
bool compare(const Student &lhs, const Student &rhs)
{
    if (lhs.get_sum() == rhs.get_sum())
    {
        return lhs.get_chinese() > rhs.get_chinese();
    }
    return lhs.get_sum() > rhs.get_sum();
}

// 函数对象形式
struct StudentCompare
{
    bool operator()(const Student &p1, const Student &p2) const // 定义sort排序从大到小
    {
        if (p1.get_sum() > p2.get_sum())
        {
            return true;
        }
        else if (p1.get_sum() == p2.get_sum())
        {
            return p1.get_chinese() > p2.get_chinese();
        }
        else
        {
            return false;
        }
    }
};

// 运算符重载方式
bool operator>(const Student &p1, const Student &p2)
{
    if (p1.get_sum() > p2.get_sum())
    {
        return true;
    }
    else if (p1.get_sum() == p2.get_sum())
    {
        return p1.get_chinese() > p2.get_chinese();
    }
    else
    {
        return false;
    }
}

void test0()
{
    list<Student> students;
    students.push_back({"zhao", 20, 92, 90, 95});
    students.push_back({"qian", 20, 95, 92, 90});
    students.push_back({"sun", 20, 90, 92, 95});
    students.push_back({"li", 20, 90, 95, 92});
    students.push_back({"zhou", 20, 78, 98, 80});
    
    for (auto &s : students)
    {
        cout << s;
    }
    // 普通比较函数
    // students.sort(compare);

    // 仿函数
    // students.sort(StudentCompare());

    // 运算符重载
    students.sort(std::greater<Student>());

    cout << "排序后：" << endl;
    for (auto &s : students)
    {
        cout << s;
    }
}

int main()
{
    test0();
    return 0;
}
