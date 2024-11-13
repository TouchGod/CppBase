#include <iostream>
#include <fstream>
#include <string>
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Usage:" << argv[0] << " src" << endl;
		exit(1);
	}
	// 用文件输入流打开文件
	// 同时文件游标指向文件末尾
	// “空头支票”处理
	ifstream ifs(argv[1], std::ios::ate);
	if (!ifs)
	{
		cerr << "fail to open file" << endl;
		return -1;
	}

	// 获得文件长度
	size_t file_size = ifs.tellg();
	// 文件游标重新指向文件首
	ifs.seekg(0, std::ios::beg);

	// read将整个文件读入buf
	char *buf = new char[file_size + 1]();
	ifs.read(buf, file_size);

	string str(buf);
	cout << str << endl;
	cout << "file_size:" << file_size << endl;

	// 回收堆空间，关闭文件流
	delete[] buf;
	ifs.close();
	return 0;
}
