// YJS.cpp: 定义应用程序的入口点。
//

#include "YJS.h"


using YJS_NAMESPACE::Doc;
using YJS_NAMESPACE::YAlloc;

// 259778

// 26355 26356
// 125287 125300
constexpr int MAX = 259778;


int main()
{	

	Doc test(YAlloc::BTREE);
	
	Doc test2(YAlloc::LISTNEW);

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
	//system("pause");

	clock_t beginTest = clock();

	for (int i = 0; i < MAX; i++){
		// if (i % 100 == 0)
		// std::cout << ((double)i / MAX) << std::endl;
		//std::cout << test.getText() << std::endl;
		//std::cout << std::endl;

		/*if (i == 26353) {
			std::cout << 1;
		}*/



		std::apply([&test](int a, int b, char c) {
			if (b == 0)
				test.localInsert(a, c);
			else
				test.localDelete(a);
		}, data[i]);
		
		//std::cout << std::get<0>(p)<< ' ' << std::get<1>(p) << ' ' << (char)std::get<2>(p) << std::endl;
	}
	((YJS_NAMESPACE::BPlusTree *)test.yStruct)->checkPool();
	clock_t endTest = clock();
	
	std::cout << test.getText() << std::endl;
	double duration = double(endTest - beginTest) / CLK_TCK;
	std::cout << "time: " << duration << std::endl;
	//system("pause");

	// =============================== 

	beginTest = clock();

	for (int i = 0; i < MAX; i++) {
		// if (i % 100 == 0)
		// std::cout << ((double)i / MAX) << std::endl;
		//std::cout << test.getText() << std::endl;
		//std::cout << std::endl;

		/*if (i == 26353) {
			std::cout << 1;
		}*/



		std::apply([&test2, &i](int a, int b, char c) {
			if (b == 0)
				test2.localInsert(a, c);
			else
				test2.localDelete(a);
			}, data[i]);

		//std::cout << std::get<0>(p)<< ' ' << std::get<1>(p) << ' ' << (char)std::get<2>(p) << std::endl;
	}
	endTest = clock();

	std::cout << test2.getText() << std::endl;
	duration = double(endTest - beginTest) / CLK_TCK;
	std::cout << "time: " << duration << std::endl;
	//system("pause");


	// ===================================
	
	/*
	beginTest = clock();
	
	std::deque<char> duqueTest;

	for (int i = 0; i < MAX; i++) {
		std::apply([&duqueTest](int a, int b, char c) {
			if (b == 0)
				duqueTest.emplace(duqueTest.begin() + a, c);
			else
				duqueTest.erase(duqueTest.begin() + a);
			}, data[i]);

		//std::cout << std::get<0>(p)<< ' ' << std::get<1>(p) << ' ' << (char)std::get<2>(p) << std::endl;
	}


	endTest = clock();
	std::string s;
	for (char& c : duqueTest)
		s += c;
	duration = double(endTest - beginTest) / CLK_TCK;
	std::cout << s;


	*/

	std::cout << "\ntime: " << duration << std::endl;
	std::cout << "验证:" << (test.getText() == test2.getText()) << std::endl;
	std::cout << "验证size:" << test.getText().size() << std::endl;
	std::cout << "验证size:" << test2.getText().size() << std::endl;
	system("pause");

	
	

	/*
	
	std::string s = "aaabbbcccddd";

	std::cout << "====start====" << std::endl;

	for (int i = 0; i < s.size(); i++)
	{
		test.localInsert(i, s[i]);
	}
	std::cout << test.getText() << std::endl;

	//system("pause");
	// test.localInsert(5, 'X');

	// std::cout << test.getText() << std::endl;

	//test.localDelete(5);

	for (int i = 0; i < 5; ++i) {
		test.localDelete(i);
	}

	std::cout << test.getText() << std::endl;

	test.localInsert(4, 'X');
	test.localInsert(4, 'Y');
	test.localInsert(4, 'Z');

	test.localDelete(2);
	test.localDelete(3);
	test.localDelete(4);




	std::cout << test.getText() << std::endl;
	system("pause");
	
	*/

	return 0;
}
