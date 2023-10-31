#include "YList.h"
#include "src/struct/YList.h"


namespace YJS_NAMESPACE {

	// ItemPtr 指向迭代器的指针

	void YList::insertItem(Index index, ItemMessage itemMsg)
	{
		//ItemPtr _insertPtr = _getItemByIndex(index);
		//if (_insertPtr)
		//{

		//}

	}

	//void YList::insertItem(ItemPtr item)
	//{
	//	return;
	//}

	void YList::deleteItem(Index index)
	{
		ItemPtr _deletePtr = _getItemByIndex(index);

		if (_deletePtr == this->end())
			return;

		//--this->size;

		ItemList* p = (ItemList*)_deletePtr.first;

		
		p->isDelete[_deletePtr.second] = 1;
		--p->realSize;
	}

	ItemPtr YList::getItemByPos(Index index) const
	{
		return _getItemByIndex(index);
	}

	//void YList::deleteItem(ItemPtr item)
	//{
	//	return;
	//}

	//void YList::getItemByPos(Index index, ItemPtr itemPtr)
	//{
	//	*(YIterator*)itemPtr = _getItemByIndex(index);
	//}

	//ItemPtr YList::getItemByGid(Id_const id)
	//{
	//	return nullptr;
	//}

	//Id_const YList::idByIndex(Index index)
	//{
	//	return (*_getItemByIndex(index)).id;
	//}

	//Index YList::posByGid(Id_const id)
	//{
	//	return 0;
	//}



	ItemPtr YList::predecessor(ItemPtr item) const
	{
		int offset = item.second;
		ItemList* p = (ItemList*)item.first;
		do
		{
			while (offset > 0 && p->isDelete[--offset] == 1)
				return { p, offset };
			p = p->left;
			offset = p->size;
		} while (p);

		return this->end();
	}

	ItemPtr YList::successor(ItemPtr item) const
	{
		int offset = item.second;
		ItemList* p = (ItemList*)item.first;
		do
		{
			while (offset < p->size && p->isDelete[++offset] == 1)
				return { p, offset };
			offset = 0;
			p = p->right;
		} while (p);

		return this->end();
	}

	ItemPtr YList::_getItemByIndex(Index index) const {
		ItemPtr p = this->begin();
		while (p != this->end() && index--)
			p = this->successor(p);
		return p;
	}

	//ItemPtr YList::_getItemByIndex(Index index) const
	//{
	//	int offset = index;
	//	ItemList* p = this->head->right;

	//	while (offset > p->realSize) {
	//		offset -= p->realSize;
	//		p = p->right;
	//	}

	//	for (int i = 0; i < offset; ++i)
	//	{
	//		if (p->isDelete[i] == 0) {
	//			offset
	//		}

	//	}


	//	ItemPtr _yPtr = this->begin();
	//	while (index) {
	//		_yPtr = _yPtr->right;
	//		//if (_yPtr == this->head)
	//		//	return nullptr;
	//		if (!_yPtr->isDelete)
	//			--index;
	//	}
	//	return _yPtr;
	//};
}