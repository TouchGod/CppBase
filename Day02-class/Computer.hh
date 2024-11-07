#ifndef __Computer_HH__
#define __Computer_HH__

class Computer
{
public:
	//构造函数
	Computer();
	Computer(const char * brand, double price);
	//拷贝构造函数
	Computer(const Computer & rhs);
	//赋值运算符函数
	Computer & operator=(const Computer & rhs);
	//析构函数
	~Computer();
    //设置品牌
    void setBrand(const char * brand);
    //设置价格
    void setPrice(double price);
    //打印信息
    void print();
private:
    char * _brand;
    double _price;
};



#endif
