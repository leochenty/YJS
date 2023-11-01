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
		ItemPtr _insertPtr = yStruct->getItemByPos(index - 1);
		ItemPtr _insertNextPtr = yStruct->successor(_insertPtr);

		ItemMessage _insertItemMsg(
			context,
			++localId,
			yStruct->getId(_insertPtr),
			yStruct->getId(_insertNextPtr)
			);

		// YJS_DEBUG("¿Í»§¶Ëid:%d Ê±ÖÓ:%d", _insertItemMsg.id.client, _insertItemMsg.id.clock);

		yStruct->insertItem(index - 1, _insertItemMsg);
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
			ans += _headTemp.first->context[_headTemp.second];
			_headTemp = yStruct->successor(_headTemp);
		}
		return ans;
	}
}


