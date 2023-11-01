// YJS.cpp: 定义应用程序的入口点。
//

#include "YJS.h"


using YJS_NAMESPACE::Doc;
using YJS_NAMESPACE::YAlloc;

int main()
{
	//std::ifstream infile("output_for_cin.txt", std::ios::in);
	
	//std::ifstream infile(".\\..\\..\\..\\test\\output_for_cin.txt", std::ios::in);
	//if (!infile) {
	//	std::cerr << "无法打开文件" << std::endl;
	//	return 1;
	//}

	////system("pause");

	//int n;
	//infile >> n;
	//
	//std::vector<std::tuple<int, int, char>> data(n);
	//int a = 0, b = 0, c = 0;
	//for (int i = 0; i < n; ++i) {
	//	infile >> a >> b;
	//	if (b == 0) {
	//		infile >> c;
	//		data[i] = std::make_tuple(a, b, (char)c);
	//	}
	//	else
	//		data[i] = std::make_tuple(a, b, '\0');
	//}


	//for (auto& p : data) {
	//	std::cout << std::get<0>(p)<< ' ' << std::get<1>(p) << ' ' << (char)std::get<2>(p) << std::endl;
	//}




	Doc test(YAlloc::LIST);
	

	std::string s = "hello world!";

	std::cout << "====start====" << std::endl;

	for (int i = 0; i < s.size(); i++)
	{
		test.localInsert(i, s[i]);
	}
	std::cout << "====start 1====" << std::endl;
	std::cout << test.getText() << std::endl;
	std::cout << "====start 2====" << std::endl;
	for (int i = 0; i < 5; ++i) {
		test.localDelete(0);
	}

	std::cout << test.getText() << std::endl;

	return 0;
}
