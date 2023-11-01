#include "src/server/doc.h"

namespace YJS_NAMESPACE{
	Doc::Doc(YAlloc yAlloc)
	{
		switch (yAlloc)
		{
		case LIST:
			yStruct = new YList;
			break;
		default:
			break;
		}

		
	}
	Doc::~Doc()
	{
		delete yStruct;
	}

	void Doc::localInsert(Index index, char context)
	{
		ItemPtr _insertPtr = yStruct->getItemByPos(index);
		ItemPtr _insertNextPtr = yStruct->successor(_insertPtr);

		ItemMessage _insertItemMsg(
			context,
			++localId,
			yStruct->getId(_insertPtr),
			yStruct->getId(_insertNextPtr)
			);

		yStruct->insertItem(index, _insertItemMsg);
	}

	void Doc::localDelete(Index index)
	{
		yStruct->deleteItem(index);
	}



	std::string Doc::getText()
	{
		ItemPtr _headTemp = this->yStruct->begin();
		std::string ans;
		while (_headTemp!=this->yStruct->end()) {
			ans += _headTemp.first->context;

			YJS_DEBUG("%d %s", _headTemp.first->headId.clock, _headTemp.first->context.c_str());

			_headTemp = yStruct->successor(_headTemp);
		}
		return ans;
	}
}


