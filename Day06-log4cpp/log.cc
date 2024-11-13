#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

using namespace log4cpp;

using std::cout;
using std::endl;

void test0()
{
    // 1.准备好布局
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn3 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    // 2.创建目的地对象,目的地与布局必须一一对应
    OstreamAppender *pos = new OstreamAppender("console", &cout);
    pos->setLayout(ptn1);

    FileAppender *f_pos = new FileAppender("file", "elog.log");
    f_pos->setLayout(ptn2);

    RollingFileAppender *rf_pos = new RollingFileAppender("r-file",
                                                          "rollingfile.log",
                                                          4096,
                                                          9);
    rf_pos->setLayout(ptn3);

    // 3.创建日志记录器
    Category &cg = Category::getInstance("cg");

    // 4.设置优先级、输出器
    cg.setPriority(Priority::DEBUG);
    cg.addAppender(pos);
    cg.addAppender(f_pos);
    cg.addAppender(rf_pos);

    // 5.利用记录器写日志
    for (int i = 0; i < 30; i++)
    {
        cg.emerg("This is an emerg msg.");
        cg.fatal("This is a fatal msg.");
        cg.alert("This is an alert msg.");
        cg.crit("This is a crit msg.");
        cg.error("This is an error msg.");
        cg.warn("This is a warn msg.");
        cg.notice("This is a notice msg.");
        cg.info("This is a info msg.");
        cg.debug("This is a debug msg.");
    }

    Category::shutdown();
}

int main()
{
    test0();
    return 0;
}