#ifndef __COWSTRING_H__
#define __COWSTRING_H__
#include <cstddef>
#include <iostream>
#include <string.h>

class CowString
{
    class CharProxy
    {
    public:
        CharProxy(CowString & self,size_t idx)
        : _self(self)
        , _idx(idx)
        {}

        char operator=(char ch);

        operator char() const;

        // friend 
        // std::ostream & operator<<(std::ostream & os,const CharProxy & rhs);
    private:
        CowString & _self;
        size_t _idx;
    };
public:
    CowString();
    CowString(const char *);
    ~CowString();
    CowString(const CowString &);
    CowString & operator=(const CowString &);
    //char & operator[](size_t);
    // 把取下标操作交由CharProxy处理
    CharProxy operator[](size_t idx);

    const char *c_str() const;
    size_t size() const;
    int use_count();

    friend std::ostream &operator<<(std::ostream &os, const CowString &rhs);
    // 嵌套类对象访问外层类私有成员，利用友元
    // friend std::ostream & operator<<(std::ostream & os,const CowString::CharProxy & rhs);

private:
    char *malloc(const char *pstr = nullptr);
    void initRefcount();
    void increaseRefcount();
    void decreaseRefcount();
    void release();

    static const int kRefcountLength = 4;
    char *_pstr;
};

#endif