#pragma once

#include "src/item/itemNew.h"

namespace YJS_NAMESPACE {
	typedef int Index;
	// typedef const ItemInterface& Item_const;
	// typedef ItemInterface ItemPtr;

	// typedef ItemInterface Item;
	// typedef ItemInterface* ItemPtr;
	//typedef void* Item;
	typedef const Id Id_const;


	/*
		这是一种变形指针，用于快速交换内存中的数据
	*/
	typedef std::pair<ItemListInterface*, Offset> ItemPtr;

	/*
		这是一种变形指针，用于快速交换内存中的数据
	*/
	//struct ItemPtr {
	//	ItemListInterface* itemHead;
	//	Offset offset;
	//};

	

	class YInterface {
		
	public:

		YInterface() {};
		virtual ~YInterface() {};

		virtual inline ItemPtr begin() const = 0;

		virtual inline ItemPtr end() const = 0;

		virtual void insertItem(Index index, ItemMessage itemMsg) = 0;

		//virtual void insertItem(ItemPtr item) = 0;

		virtual void deleteItem(Index index) = 0;

		//virtual void deleteItem(ItemPtr item) = 0;


		virtual ItemPtr getItemByPos(Index index) const = 0;

		//virtual ItemPtr getItemByGid(Id_const id) = 0;

		// virtual Id_const idByIndex(Index index) = 0;

		// virtual Index posByGid(Id_const id) = 0;

		virtual ItemPtr predecessor(ItemPtr itemPtr) const = 0;



		virtual ItemPtr successor(ItemPtr itemPtr) const = 0;
	};


}