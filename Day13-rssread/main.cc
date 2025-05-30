#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <regex>

using namespace std;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    // RssReader();
    void parseRss();                   // 解析
    void dump(const string &filename); // 输出
private:
    vector<RssItem> _rss;
};

void RssReader::parseRss()
{
    XMLDocument *doc = new XMLDocument();
    doc->LoadFile("coolshell.xml");

    if (doc->ErrorID())
    {
        cerr << "open xml file failed" << endl;
        return;
    }
    // doc->Print();
    cout << "打开xml文件成功" << endl;

    XMLElement *rootnode = doc->RootElement();
    if (!rootnode)
    {
        cerr << "未找到根节点" << endl;
        return;
    }
    cout << "success find rootnode" << endl;

    XMLElement *channel = rootnode->FirstChildElement("channel");
    if (!channel)
    {
        cerr << "not find channel" << endl;
        return;
    }
    cout << "success find channel" << endl;

    XMLElement *item = channel->FirstChildElement("item");
    if (!item)
    {
        cerr << "not find item" << endl;
        return;
    }
    cout << "success find item" << endl;

    while (item)
    {
        RssItem ritem;
        XMLElement *title = item->FirstChildElement("title");
        ritem.title = title->GetText();

        XMLElement *link = item->FirstChildElement("link");
        ritem.link = link->GetText();

        XMLElement *descript = item->FirstChildElement("description");
        string description = descript->GetText();

        XMLElement *xcontent = item->FirstChildElement("content:encoded");
        string content = xcontent->GetText();

        regex reg("<[^>]+>");                                    // 通用正则表达式(主要研究一下正则表达式的规则)
        ritem.description = regex_replace(description, reg, ""); // regex_replace函数的使用
        ritem.content = regex_replace(content, reg, "");

        _rss.push_back(ritem);

        item = item->NextSiblingElement("item");
    }
}

void RssReader::dump(const string &filename){
    ofstream ofs(filename);
    if(!ofs){
        cerr << "ofstream error" << endl;
        return;
    }

    for (int i = 0; i < _rss.size(); i++)
    {
        ofs << "<doc>" << endl;
        ofs << "\t" << "<docid>" << i + 1 << "</docid>" << "\n";
        ofs << "\t" << "<title>" << _rss[i].title << "</title>" << "\n";
        ofs << "\t" << "<link>" << _rss[i].link << "</link>" << "\n";
        ofs << "\t" << "<description>" << _rss[i].description << "</description>" << "\n";
        ofs << "\t" << "<content>" << _rss[i].content << "</content>" << "\n";
        ofs << "</doc>" << endl;
    }

    ofs.close();
}

void test0()
{
    static const char *xml =
        "<?xml version=\"1.0\"?>"
        "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
        "<PLAY>"
        "<TITLE>A Midsummer Night's Dream</TITLE>"
        "</PLAY>";

    XMLDocument doc;
    doc.Parse(xml);

    XMLElement *titleElement = doc.FirstChildElement("PLAY")->FirstChildElement("TITLE");
    /* const char *title = titleElement->GetText(); */
    /* printf("Name of play (1): %s\n", title); */

    XMLText *textNode = titleElement->FirstChild()->ToText();
    /* title = textNode->Value(); */
    printf("Name of play (2): %s\n", textNode->Value());

    cout << doc.ErrorID() << endl;
}

int main()
{
    /* RssReader rread; */
    /* rread.parseRss(); */
    /* rread.dump("pagelib.dat"); */
    test0();
    return 0;
}
