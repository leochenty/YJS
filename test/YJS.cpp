// YJS.cpp: 定义应用程序的入口点。
//

#include "YJS.h"
#include <iostream>

using YJS_NAMESPACE::Doc;
using YJS_NAMESPACE::YAlloc;

int main()
{
	Doc test(YAlloc::LIST);
	

	std::string s = "hello world!";

	std::cout << "====start====" << std::endl;

	for (int i = 0; i < s.size(); i++)
	{
		test.localInsert(i, s[i]);
	}
	
	std::cout << test.getText() << std::endl;
	return 0;
}
