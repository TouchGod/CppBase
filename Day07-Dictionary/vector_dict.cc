#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Record
{
	string _word;
	int _frequency;
};

class Dictionary
{
public:
	void read(const std::string &filename)
	{
		ifstream ifs(filename);
		if (!ifs)
		{
			cerr << "fail to open file" << endl;
			return;
		}

		// string line;
		// while(std::getline(ifs,line))
		// string word;
		// std::istringstream iss(line);
		
		// 一个一个单词读，效率较低
		string word;
		while (ifs >> word)
		{
			/* cout << word << endl; */
			bool isword = true;
			for (auto &c : word)
			{
				if (!isalpha(c))
				{
					isword = false;
				}
			}
			if (!isword)
			{
				continue;
			}
			// 遍历词典，存在则++，不存在
			auto it = _dict.begin();
			for (; it != _dict.end(); it++)
			{
				if (word == it->_word)
				{
					it->_frequency += 1;
					break;
				}
			}
			if (it == _dict.end())
			{
				Record r;
				r._word = word;
				r._frequency = 1;
				_dict.push_back(r);
			}
		}

		/* for(auto & w : _dict){ */
		/* 	cout << w._word << " " << w._frequency << endl; */
		/* } */

		ifs.close();
	}
	void store(const std::string &filename)
	{
		ofstream ofs(filename, std::ios::app);
		for (auto &w : _dict)
		{
			ofs << "|\t" << w._word << " \t" << w._frequency << " \t" << "|\t" << endl;
		}

		ofs.close();
	}

private:
	vector<Record> _dict;
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Usage: dict file" << endl;
		return 0;
	}

	Dictionary dictionary;
	dictionary.read(argv[1]);
	dictionary.store("dict.txt");
	return 0;
}
