#pragma once

#include "src/struct/YList.h"

#include "src/server/transaction.h"

#include <string>


namespace YJS_NAMESPACE {

	enum YAlloc
	{
		LIST,

	};

	class Doc{
	public:
		Doc(YAlloc);
		~Doc();

		Id localId = {1, 0};

	public:
		
		YInterface* yStruct;

		void localInsert(Index index, char context);

		void localDelete(Index index);

		void testF(int index, int flag, char c) {
			if (flag)
				localDelete(index);
			else
				localInsert(index, c);
		}

		std::string getText();

	};
	

};