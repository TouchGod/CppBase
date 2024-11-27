#ifndef __COWSTRING_H__
#define __COWSTRING_H__
#include <cstddef>
#include <iostream>
#include <string.h>

class CowString
{
public:
    CowString();
    CowString(const char *);
    ~CowString();
    CowString(const CowString &);
    /* CowString & operator=(const CowString &); */

    const char *c_str() const;
    size_t size() const;
    int use_count();

    friend std::ostream &operator<<(std::ostream &os, const CowString &rhs);

private:
    char *malloc(const char *pstr = nullptr);
    void initRefcount();
    void increaseRefcount();
    void decreaseRefcount();

    static const int kRefcountLength = 4;
    char *_pstr;
};

#endif