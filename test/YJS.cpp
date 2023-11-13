// YJS.cpp: 定义应用程序的入口点。
//

#include "YJS.h"


using YJS_NAMESPACE::Doc;
using YJS_NAMESPACE::YAlloc;

// 259778

// 26355 26356
// 125287 125300
constexpr int MAX = 259778;

void testF(Doc& test, std::vector<std::tuple<int, int, char>> data);



int main()
{	

	Doc test(YAlloc::BTREE);
	
	Doc test2(YAlloc::LISTNEW);

	Doc test3(YAlloc::AVLTREE);

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

	std::cout << "数据量：" << MAX << '/' << n << std::endl;
	std::cout << std::endl;
	//system("pause");

	testF(test, data);

	testF(test2, data);

	testF(test3, data);



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

	bool _flag = true;
	if (!(test.getText() == test2.getText()))
		_flag = false;

	//std::cout << test3.getText() << std::endl;


	if(_flag)
		std::cout << "数据正确" << std::endl;
	else
		std::cout << "数据错误" << std::endl;
	//system("pause");

	return 0;
}

void testF(Doc& test, std::vector<std::tuple<int, int, char>> data) {
	PROCESS_MEMORY_COUNTERS pmcBegin, pmcEnd;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmcBegin, sizeof(pmcBegin));
	clock_t beginTest = clock();

	for (int i = 0; i < MAX; i++) {
		// std::cout << ((double)i / MAX) << std::endl;
		std::apply([&test](int a, int b, char c) {
			if (b == 0)
				test.localInsert(a, c);
			else
				test.localDelete(a);
			}, data[i]);
	}
	string _type;
	if (typeid(*test.yStruct) == typeid(BPlusTree)) {
		_type = "B+树";
		((YJS_NAMESPACE::BPlusTree*)test.yStruct)->checkPool();
	}

	if (typeid(*test.yStruct) == typeid(YListNew)) {
		_type = "双链表";
	}

	if (typeid(*test.yStruct) == typeid(AVLTree)) {
		_type = "AVL树";
	}

	clock_t endTest = clock();
	GetProcessMemoryInfo(GetCurrentProcess(), &pmcEnd, sizeof(pmcEnd));

	//std::cout << test.getText() << std::endl;
	double duration = double(endTest - beginTest) / CLK_TCK;
	double memory = double(pmcEnd.WorkingSetSize - pmcBegin.WorkingSetSize) / (1024 * 1024);
	std::cout << _type << std::endl;
	std::cout << "时间: " << duration << "秒" << std::endl;
	std::cout << "内存: " << memory << "MB" << std::endl;
	std::cout << std::endl;
	//system("pause");
}