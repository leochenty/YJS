#include "YList.h"
#include "src/struct/YList.h"


namespace YJS_NAMESPACE {

	// ItemPtr 指向迭代器的指针

	void YList::insertItem(Index index, Item item)
	{
		ItemTypePtr _insertPtr = _getItemByIndex(index);

		if (!_insertPtr)
			return;

		++this->size;

		ItemTypePtr _insertItem = new ItemType(item);

		_insertItem->left = _insertPtr;
		_insertItem->right = _insertPtr->right;
		_insertPtr->right = _insertItem;
		_insertItem->right->left = _insertPtr;

	}

	//void YList::insertItem(ItemPtr item)
	//{
	//	return;
	//}

	void YList::deleteItem(Index index)
	{
		ItemTypePtr _deletePtr = _getItemByIndex(index+1);

		if (!_deletePtr)
			return;

		--this->size;

		_deletePtr->isDelete = true;
	}

	ItemPtr YList::getItemByPos(Index index) const
	{
		ItemTypePtr _ptr = _getItemByIndex(index + 1);
		return (ItemPtr)_ptr;
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
		while (item->left->isDelete)
			item = item->left;
		return item->left;
	}

	ItemPtr YList::successor(ItemPtr item) const
	{
		while (item->right->isDelete)
			item = item->right;
		return item->right;
	}


	YList::ItemTypePtr YList::_getItemByIndex(int index) const
	{
		ItemTypePtr _yPtr = this->head;
		while (index) {
			_yPtr = _yPtr->right;
			//if (_yPtr == this->head)
			//	return nullptr;
			if (!_yPtr->isDelete)
				--index;
		}
		return _yPtr;
	};
}