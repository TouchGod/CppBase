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
    release();
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

// 提高代码复用
void CowString::release()
{
    decreaseRefcount();
    if (use_count() == 0)
    {
        delete[] (_pstr - kRefcountLength);
        _pstr = nullptr;
    }
}

std::ostream &operator<<(std::ostream &os, const CowString &rhs)
{
    if (rhs._pstr)
    {
        os << rhs._pstr;
    }
    return os;
}

CowString &CowString::operator=(const CowString &rhs)
{
    if (this != &rhs)
    {
        // 先把自己的引用计数减1，减为0则删除
        release();

        _pstr = rhs._pstr;
        increaseRefcount();
    }
    return *this;
}

// char & CowString::operator[](size_t idx)
// {
//     if(idx < size())
//     {
//         return _pstr[idx];
//     }else{
//         std::cout << "out of range" << std::endl;
//         static char nullchar = '\0';
//         return nullchar;
//     }
// }

// 考虑两种情况：
// 1. 如果是左值，则返回一个左值，可以修改原字符串，str[0] = 'H'
// 2. 如果是右值，则返回一个右值，不能修改原字符串，str[0]

// char & CowString::operator[](size_t idx)
// {
//     if (idx >= size())
//     {
//         // throw std::out_of_range("index out of range");

//         // 模拟std::string
//         std::cout << "out of range" << std::endl;
//         static char nullchar = '\0';
//         return nullchar;
//     }
//     else
//     {
//         if(use_count() > 1)
//         {
//             //原本空间的引用计数-1
//             decreaseRefcount();
//             //进行深拷贝
//             char * ptemp = malloc(_pstr);
//             strcpy(ptemp, _pstr);
//             //改变指向，让对象的_pstr指向新空间
//             _pstr = ptemp;
//             //初始化新空间的引用计数
//             initRefcount();
//         }
//         return _pstr[idx];
//     }
// }

//str1[0]得到一个CharProxy对象
//能够提供的材料只有str1这个CowString对象和下标
CowString::CharProxy CowString::operator[](size_t idx)
{
    return CharProxy(*this,idx);
}


//str1[0] = 'H';
char CowString::CharProxy::operator=(char ch)
{
    if(_idx < _self.size()) 
    {
        if(_self.use_count() > 1)
        {
            //原本空间的引用计数-1
            _self.decreaseRefcount();
            //进行深拷贝
            char * ptemp = _self.malloc(_self._pstr);
            strcpy(ptemp,_self._pstr);
            //改变指向，让对象的_pstr指向新空间
            _self._pstr = ptemp;
            //初始化新空间的引用计数
            _self.initRefcount();
        }
        //进行写操作
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    }else{
        std::cout << "out of range" << std::endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

// cout << str[0] << endl;
std::ostream &operator<<(std::ostream &os, const CowString::CharProxy &rhs)
{
    if(rhs._idx < rhs._self.size()) 
    {   
        os << rhs._self._pstr[rhs._idx];
    }else{
        os << "out of range" << std::endl;
    }
    return os;
}


