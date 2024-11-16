#include "String.hh"
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
using std::cout;
using std::endl;
using std::istringstream;
using std::vector;
#define MAXSIZE 1024

String::String()
    : _pstr(new char[1]())
{
}

String::String(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1]())
{
    strcpy(_pstr, pstr);
}

String::String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
{
    strcpy(_pstr, rhs._pstr);
}

String::~String()
{
    if (_pstr)
    {
        delete[] _pstr;
        _pstr = nullptr;
    }
}

String &String::operator=(const String &rhs)
{
    if (_pstr)
    {
        delete[] _pstr;
        _pstr = nullptr;
    }
    _pstr = new char[strlen(rhs._pstr) + 1]();
    strcpy(_pstr, rhs._pstr);
    return *this;
}

String &String::operator=(const char *rhs)
{
    if (_pstr)
    {
        delete[] _pstr;
        _pstr = nullptr;
    }
    _pstr = new char[strlen(rhs) + 1]();
    strcpy(_pstr, rhs);
    return *this;
}

String &String::operator+=(const String &rhs)
{
    int length = strlen(rhs._pstr);
    if (length == 0)
    {
        return *this;
    }
    char *temp = nullptr;
    if (_pstr)
    {
        length += strlen(_pstr);
        temp = _pstr;
    }
    _pstr = new char[length + 1]();
    strcpy(_pstr, temp);
    strcat(_pstr, rhs._pstr);
    if (temp)
    {
        delete[] temp;
    }
    return *this;
}

String &String::operator+=(const char *rhs)
{
    int length = strlen(rhs);
    if (length == 0)
    {
        return *this;
    }
    char *temp = nullptr;
    if (_pstr)
    {
        length += strlen(_pstr);
        temp = _pstr;
    }
    _pstr = new char[length + 1]();
    strcpy(_pstr, temp);
    strcat(_pstr, rhs);
    if (temp)
    {
        delete[] temp;
    }
    return *this;
}

/* String & String::operator+=(const char rhs) */

char &String::operator[](std::size_t index)
{
    return this->_pstr[index];
}

const char &String::operator[](std::size_t index) const
{
    return this->_pstr[index];
}

size_t String::size() const
{
    return strlen(_pstr);
}

const char *String::c_str() const
{
    return _pstr;
}

bool operator==(const String &lhs, const String &rhs)
{
    if (!strcmp(lhs._pstr, rhs._pstr))
    {
        return true;
    }
    return false;
}

bool operator!=(const String &lhs, const String &rhs)
{
    if (strcmp(lhs._pstr, rhs._pstr))
    {
        return true;
    }
    return false;
}

bool operator<(const String &lhs, const String &rhs)
{
    if (strcmp(lhs._pstr, rhs._pstr) < 0)
    {
        return true;
    }
    return false;
}

bool operator>(const String &lhs, const String &rhs)
{
    if (strcmp(lhs._pstr, rhs._pstr) > 0)
    {
        return true;
    }
    return false;
}

bool operator<=(const String &lhs, const String &rhs)
{
    if (strcmp(lhs._pstr, rhs._pstr) <= 0)
    {
        return true;
    }
    return false;
}

bool operator>=(const String &lhs, const String &rhs)
{
    if (strcmp(lhs._pstr, rhs._pstr) >= 0)
    {
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    /* char *temp = new char[MAXSIZE](); */
    /* is >> temp; */
    /* int length = strlen(temp); */
    /* if(s._pstr){ */
    /* 	delete [] s._pstr; */
    /* } */
    /* s._pstr = new char[length + 1](); */
    /* strcpy(s._pstr, temp); */
    /* delete [] temp; */
    /* return is; */

    if (s._pstr)
    {
        delete[] s._pstr;
        s._pstr = nullptr;
    }
    vector<char> temp;
    char c;
    while ((c = is.get()) != '\n')
    {
        temp.push_back(c);
    }

    s._pstr = new char[temp.size() + 1]();
    /* for (auto & m : temp){ */
    /* 	s._pstr += m; */
    /* } */
    strncpy(s._pstr, &temp[0], temp.size());
    return is;
}

String operator+(const String &lhs, const String &rhs)
{
    /* const char *pl = lhs.c_str(); */
    /* const char *pr = rhs.c_str(); */
    /* char * temp = new char[strlen(pl) + strlen(pr) + 1](); */
    /* strcpy(temp, pl); */
    /* strcat(temp, pr); */
    /* String s(temp); */
    /* delete [] temp; */
    String s = lhs;
    s += rhs;
    return s;
}

String operator+(const String &lhs, const char *rhs)
{
    /* const char * p = lhs.c_str(); */
    /* char * temp = new char[strlen(p) + strlen(rhs) + 1](); */
    /* strcpy(temp, p); */
    /* strcat(temp, rhs); */
    /* String s(temp); */
    /* delete [] temp; */
    String s = lhs;
    s += rhs;
    return s;
}
String operator+(const char *lhs, const String &rhs)
{
    /* const char * p = rhs.c_str(); */
    /* char * temp = new char[strlen(p) + strlen(lhs) + 1](); */
    /* strcpy(temp, lhs); */
    /* strcat(temp, p); */
    /* String s(temp); */
    /* delete [] temp; */
    /* return s; */
    String s = lhs;
    s += rhs;
    return s;
}

void String::print()
{
    printf("%s\n", _pstr);
}
