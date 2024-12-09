#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Person
{
public:
    void display()
    {
        cout << "name:" << _name << endl;
        cout << "age:" << _age << endl;
    }

    Person(const char *name, const int age)
        : _name(new char[strlen(name) + 1]()), _age(age)
    {
        strcpy(_name, name);
    }

    Person()
        : _name(new char[1]()), _age()
    {
    }

    ~Person()
    {
        if (_name)
        {
            delete[] _name;
            _name = nullptr;
        }
    }

    Person(const Person &rhs)
        : _name(new char[strlen(rhs._name) + 1]()), _age(rhs._age)
    {
        strcpy(_name, rhs._name);
    }

    Person &operator=(const Person &rhs)
    {
        if (this != &rhs)
        {
            delete[] _name;
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
        }
        /* cout << "operator=" << endl; */
        return *this;
    }

private:
    char *_name;
    int _age;
};

class Employee
    : public Person
{
public:
    void display()
    {
        Person::display();
        cout << "department:" << _department << endl;
        cout << "salary:" << _salary << endl;
    }

    Employee(const char *name, const int age, const char *dep, const int salary)
        : Person(name, age), _department(new char[strlen(dep) + 1]()), _salary(salary)
    {
        strcpy(_department, dep);
        _totalsalary += salary;
        _number++;
    }

    ~Employee()
    {
        if (_department)
        {
            delete[] _department;
            _department = nullptr;
        }
        _totalsalary -= _salary;
        --_number;
    }

    Employee(const Employee &rhs)
        : Person(rhs), _department(new char[strlen(rhs._department) + 1]()), _salary(rhs._salary)
    {
        strcpy(_department, rhs._department);
        _totalsalary += _salary;
        _number++;
    }

    Employee &operator=(const Employee &rhs)
    {
        if (this != &rhs)
        {
            Person::operator=(rhs);
            delete[] _department;
            _department = new char[strlen(rhs._department) + 1]();
            strcpy(_department, rhs._department);
            _totalsalary -= _salary;
            _salary = rhs._salary;
            _totalsalary += _salary;
        }
        return *this;
    }

    static void show_avg_salary()
    {
        cout << (_totalsalary / _number) << endl;
    }

private:
    char *_department;
    int _salary;
    static int _number;
    static double _totalsalary;
};
int Employee::_number = 0;
double Employee::_totalsalary = 0;

void test0()
{
    Employee ee1("zs", 25, "transfer", 10000);
    ee1.display();

    Employee ee2 = ee1;
    ee2.display();

    Employee ee3("ls", 25, "manage", 15000);
    ee3.display();
    ee3 = ee2;
    ee3.display();

    Employee::show_avg_salary();
}

void test1()
{
    Employee ee1("zs", 25, "transfer", 10000);
    Employee ee2("wu", 25, "hr", 12000);
    Employee ee3("ls", 25, "manage", 15000);

    Employee::show_avg_salary();
}

int main()
{
    /* test0(); */
    test1();
    return 0;
}