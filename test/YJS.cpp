// YJS.cpp: 定义应用程序的入口点。
//

#include "YJS.h"


using YJS_NAMESPACE::Doc;
using YJS_NAMESPACE::YAlloc;

// 259778
constexpr int MAX = 10000;


int main()
{	

	Doc test(YAlloc::BTREE);

	std::ifstream infile(".\\..\\..\\..\\test\\output_for_cin.txt", std::ios::in);
	if (!infile) {
		std::cerr << "无法打开文件" << std::endl;
		return 1;
	}

	

	int n;
	infile >> n;
	
	std::vector<std::tuple<int, int, char>> data(n);
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < n; ++i) {
		infile >> a >> b;
		if (b == 0) {
			infile >> c;
			data[i] = std::make_tuple(a, b, (char)c);
		}
		else
			data[i] = std::make_tuple(a, b, '\0');
	}

	std::cout << MAX <<'/' << n << std::endl;
	system("pause");

	for (int i = 0; i < MAX; i++){
		std::tuple<int, int, char> p = data[i];
		
		// if (i % 100 == 0)
		std::cout << ((double)i / MAX) << std::endl;
		std::cout << test.getText() << std::endl;
		std::cout << std::endl;
		std::apply([&test](int a, int b, char c) {
			test.testF(a,b,c);
		}, p);
		
		//std::cout << std::get<0>(p)<< ' ' << std::get<1>(p) << ' ' << (char)std::get<2>(p) << std::endl;
	}


	std::cout << test.getText() << std::endl;

	
	system("pause");

	//std::string s = "hello world!";

	//std::cout << "====start====" << std::endl;

	//for (int i = 0; i < s.size(); i++)
	//{
	//	test.localInsert(i, s[i]);
	//}
	//std::cout << test.getText() << std::endl;

	//test.localInsert(5, 'X');

	//std::cout << test.getText() << std::endl;


	//for (int i = 0; i < 5; ++i) {
	//	test.localDelete(i);
	//}

	//std::cout << test.getText() << std::endl;

	return 0;
}
