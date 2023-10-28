#include "src/server/doc.h"

namespace YJS_NAMESPACE{
	Doc::Doc(YAlloc yAlloc)
	{
		this->clientId = 0;
		this->localClock = 0;

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

	void Doc::localInsert(Index index, Text context)
	{
		ItemPtr _insertPtr = yStruct->getItemByPos(index);
		Id _origin = _insertPtr->id;
		Id _rightOrigin = yStruct->successor(_insertPtr)->id;
		Id _insertId = Id(clientId, ++this->localClock);
		Item _insertItem(_insertId, context, _origin, _rightOrigin);
		yStruct->insertItem(index, _insertItem);
	}

	void Doc::localDelete(Index index)
	{
		yStruct->deleteItem(index);
	}



	std::string Doc::getText()
	{
		ItemPtr _head = this->yStruct->begin();
		std::string ans;
		while (_head!=this->yStruct->end()) {
			ans += _head->content;
			_head = yStruct->successor(_head);
		}
		return ans;
	}
}


