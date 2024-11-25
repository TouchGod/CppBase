#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
using std::cerr;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::map;
using std::ofstream;
using std::set;
using std::string;
using std::vector;

class TextQuery
{
public:
    //......
    void readFile(const string &filename);
    void query(const string &word);
    void deal_word(string &);
    void insert(const string &, int);

private:
    //......
    vector<string> _lines;              // O(1)
    map<string, set<int>> _wordNumbers; // the the
    map<string, int> _dict;             //
};

int main(int argc, char *argv[])
{
    string queryWord("because");

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    return 0;
}

void TextQuery::readFile(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cerr << "fail to open file:" << filename << endl;
    }

    string line;
    int no_line = 1;
    while (getline(ifs, line))
    {
        // 存line
        _lines.push_back(line);

        // 处理line，得到word
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            deal_word(word);
            insert(word, no_line);
        }

        ++no_line;
    }

    ifs.close();
}

void TextQuery::deal_word(string &word)
{
    auto it = word.begin();
    while (it != word.end())
    {
        if (!isalpha(*it))
        {
            it = word.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void TextQuery::insert(const string &word, int n)
{
    if (word.size() == 0)
        return;

    _wordNumbers[word].insert(n);
    // Todo 插入失败判断

    // 先查询map
    auto it = _dict.find(word);
    if (it != _dict.end())
    {
        // map 中已存在该word
        it->second++;
    }
    else
    {
        auto ret = _dict.insert({word, 1});
        if (!ret.second)
        {
            cerr << "insert into map failed" << endl;
        }
    }
}

void TextQuery::query(const string &word)
{
    auto it = _dict.find(word);
    if (it == _dict.end())
    {
        cout << "There is no " << word << " in the file" << endl;
        return;
    }
    else
    {
        cout << word << " occurs " << (*it).second << " times." << endl;
        auto it2 = _wordNumbers.find(word);
        for (auto &number : (*it2).second)
        {
            cout << "(line " << number << ") ";
            cout << _lines[number - 1] << endl;
        }
    }
}