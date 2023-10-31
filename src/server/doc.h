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

		int clientId;
		int localClock;


	public:
		
		YInterface* yStruct;

		void localInsert(Index index, char context);

		void localDelete(Index index);

		std::string getText();

	};
	

};