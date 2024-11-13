#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
using namespace log4cpp;
using std::cout;
using std::endl;
using std::string;

// #define DEBUG_LOG(message) DebugLog(message, __FILE__, __LINE__)

#define addPrefix(msg) string("[").append(__FILE__).append(":").append(__func__).append(":").append(std::to_string(__LINE__)).append("]").append(msg).c_str()

#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg))

#define LogDebug(message)                            \
    {                                                \
        string str;                                  \
        str += __FILE__;                             \
        str += " ";                                  \
        str += __FUNCTION__;                         \
        str += " ";                                  \
        str += std::to_string(__LINE__);             \
        str += " ";                                  \
        str += message;                              \
        Mylogger::getInstance()->debug(str.c_str()); \
    }

class Mylogger
{
public:
    static Mylogger *getInstance()
    {
        if (_pInstance == nullptr)
        {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }

    static void Destroy()
    {
        if (_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void warn(const char *msg)
    {
        _category.warn(msg);
    }
    void error(const char *msg)
    {
        _pInstance->_category.error(msg);
    }
    void debug(const char *msg)
    {
        _pInstance->_category.debug(msg);
    }
    void info(const char *msg)
    {
        _pInstance->_category.info(msg);
    }
    void fatal(const char *msg)
    {
        _pInstance->_category.fatal(msg);
    }
    void crit(const char *msg)
    {
        _pInstance->_category.crit(msg);
    }

private:
    Mylogger()
        : _category(Category::getInstance("category"))
    {
        PatternLayout *ptn1 = new PatternLayout();
        ptn1->setConversionPattern("%d %c [%p]  %m%n");
        PatternLayout *ptn2 = new PatternLayout();
        ptn2->setConversionPattern("%d %c [%p] %m%n");

        OstreamAppender *pos = new OstreamAppender("console", &cout);
        pos->setLayout(ptn1);

        FileAppender *f_pos = new FileAppender("file", "Mylogger.log");
        f_pos->setLayout(ptn2);

        _category.setPriority(Priority::DEBUG);
        _category.addAppender(pos);
        _category.addAppender(f_pos);

        /* cout << "Mylogger" << endl; */
    }

    ~Mylogger()
    {
        Category::shutdown();
    }

private:
    Category &_category;
    static Mylogger *_pInstance;
};
Mylogger *Mylogger::_pInstance = nullptr;

/* 测试获取代码执行的文件名，函数名，行号
void DebugLog(std::string message, std::string fileName, int line)
{
    std::cerr << "[" << fileName << ":" << line << "] " << message << std::endl;
}
*/

void test0()
{
    // 第一步，完成单例模式的写法
    Mylogger::getInstance()->info("The log is info message");
    Mylogger::getInstance()->error("The log is error message");
    Mylogger::getInstance()->fatal("The log is fatal message");
    Mylogger::getInstance()->crit("The log is crit message");

    Mylogger::Destroy();
}

void test1()
{
    // 第二步，像使用printf一样
    // 只要求能输出纯字符串信息即可，不需要做到格式化输出
    /* LogInfo("The log is info message"); */
    /* LogError("The log is error message"); */
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

int main()
{
    // test0();
    test1();
    return 0;
}
