#include "src/server/doc.h"

namespace YJS_NAMESPACE{
	Doc::Doc(YAlloc yAlloc)
	{
		switch (yAlloc)
		{
		case LIST:
			yStruct = new YList;
			break;
		case BTREE:
			yStruct = new BPlusTree;
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
		//ItemPtr _insertPtr = yStruct->getItemByPos(index);
		//ItemPtr _insertNextPtr = yStruct->successor(_insertPtr);

		ItemPtr _insertNextPtr =  yStruct->getItemByPos(index);
		ItemPtr _insertPtr = yStruct->predecessor(_insertNextPtr);

		ItemMessage _insertItemMsg(
			context,
			++localId,
			yStruct->getId(_insertPtr),
			yStruct->getId(_insertNextPtr)
			);

		// YJS_DEBUG("¿Í»§¶Ëid:%d Ê±ÖÓ:%d", _insertItemMsg.id.client, _insertItemMsg.id.clock);

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
			ans += _headTemp.first->context[_headTemp.second];
			_headTemp = yStruct->successor(_headTemp);
		}
		return ans;
	}
}


