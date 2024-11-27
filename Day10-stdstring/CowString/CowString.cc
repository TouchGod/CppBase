#include "CowString.h"

CowString::CowString()
    : _pstr(malloc())
{
    initRefcount();
}

CowString::CowString(const char *str)
    : _pstr(malloc(str))
{
    strcpy(_pstr, str);
    initRefcount();
}

CowString::~CowString()
{
    decreaseRefcount();
    if (use_count() == 0)
    {
        delete[] (_pstr - kRefcountLength);
        _pstr = nullptr;
    }
}

CowString::CowString(const CowString &rhs)
    : _pstr(rhs._pstr) // 浅拷贝
{
    increaseRefcount();
}

const char *CowString::c_str() const
{
    return _pstr;
}

size_t CowString::size() const
{
    return strlen(_pstr);
}

int CowString::use_count()
{
    return *(int *)(_pstr - kRefcountLength);
}

// 函数定义时不用写默认值(const char *pstr = nullptr),否则报错
char *CowString::malloc(const char *pstr)
{
    if (pstr)
    {
        // 如果提供了字符串参数，分配足够的内存以存储字符串内容、空字符和引用计数
        return new char[strlen(pstr) + 1 + kRefcountLength]() + kRefcountLength;
    }
    else
    {
        // 如果没有提供字符串参数，仅分配足够存放空字符串和引用计数的内存
        return new char[1 + kRefcountLength]() + kRefcountLength;
    }
}

void CowString::initRefcount()
{
    *(int *)(_pstr - kRefcountLength) = 1;
}

void CowString::increaseRefcount()
{
    ++*(int *)(_pstr - kRefcountLength);
}

void CowString::decreaseRefcount()
{
    --*(int *)(_pstr - kRefcountLength);
}

std::ostream &operator<<(std::ostream &os, const CowString &rhs)
{
    if (rhs._pstr)
    {
        os << rhs._pstr;
    }
    return os;
}
