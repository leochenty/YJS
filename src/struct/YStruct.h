#pragma once

#include "src/item/Item.h"

namespace YJS_NAMESPACE {
	typedef int Index;
	// typedef const ItemInterface& Item_const;
	// typedef ItemInterface ItemPtr;

	typedef ItemInterface Item;
	typedef ItemInterface* ItemPtr;
	//typedef void* Item;
	typedef const Id Id_const;

	class YInterface {
		
	public:

		YInterface() {};
		virtual ~YInterface() {};

		virtual ItemPtr begin() const = 0;

		virtual ItemPtr end() const = 0;

		virtual void insertItem(Index index, ItemInterface item) = 0;

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