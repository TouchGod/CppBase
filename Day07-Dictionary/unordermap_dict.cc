#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;    
using std::istringstream;
using std::ofstream;
using std::string;
using std::unordered_map;

class Dictionary
{
public:
    void read(const string &filename)
    {
        ifstream ifs(filename);
        if (!ifs)
        {
            cerr << "fail to open file" << endl;
            return;
        }

        string line;
        while (std::getline(ifs, line))
        {
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                // word 处理函数
                deal_word(word);

                // 处理好的word, 插入map
                insert(word);
            }
        }

        ifs.close();
    }

    void deal_word(string &word)
    {
        auto it = word.begin();
        while (it != word.end())
        {
            // if (!isalpha(*it))
            // {
            //     // 删除非字母的字符，更新迭代器
            //     it = word.erase(it);
            // }
            // else
            // {
            //     ++it;
            // }

            // 若word不符合条件，则置空
            if (!isalpha(*it))
            {
                word.clear();
                break;
            }
        }
    }

    void insert(const string &word)
    {
        if (word.size() == 0)
        {
            return;
        }

        // 优化形式
        ++_dict[word];
    }

    void store(const string &filename)
    {
        ofstream ofs(filename);
        if (!ofs)
        {
            cerr << "fail to open file" << endl;
            return;
        }

        // 遍历map
        for (auto &w : _dict)
        {
            ofs << "|" << w.first << "  " << w.second << "|" << endl;
        }

        ofs.close();
    }

private:
    unordered_map<string, int> _dict;
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: dict file" << endl;
        return 0;
    }

    Dictionary dic1;
    dic1.read(argv[1]);
    dic1.store("dict.dat");
    return 0;
}
