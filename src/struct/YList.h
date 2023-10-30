#pragma once

#include "src/struct/YStruct.h"

#include <list>

namespace YJS_NAMESPACE {
	class YList : public YInterface {
	public:
		typedef class ItemList : public ItemInterface {
		public:
			ItemList() :ItemInterface() {};

			ItemList(const ItemInterface& p)
				:ItemInterface(p)
			{};

			virtual ~ItemList() {};
			// 添加你需要的的变量, 这是一个例子
			ItemInterface* left;

			ItemInterface* right;
		}_ItemType_No_Use;

		typedef unsigned int Size;
		typedef ItemInterface ItemType;
		typedef ItemInterface* ItemTypePtr;

		YList() {
			head = new ItemType;
			head->left = head;
			head->right = head;
		};
		~YList() {
			delete head;
		};

		Size size = 0;

		ItemType* head;

		virtual ItemPtr begin() const override {
			return head->right;
		};

		virtual ItemPtr end() const override {
			return head;
		};

		virtual void insertItem(Index index, Item item) override;

		// virtual void insertItem(ItemPtr item) override;

		virtual void deleteItem(Index index) override;

		// virtual void deleteItem(ItemPtr item) override;

		virtual ItemPtr getItemByPos(Index index) const override;

		// virtual ItemPtr getItemByGid(Id_const id) override;

		// virtual Id_const idByIndex(Index index) override;

		// virtual Index posByGid(Id_const id) override;

		virtual ItemPtr predecessor(ItemPtr item) const override;

		virtual ItemPtr successor(ItemPtr item) const override;


	private:
		ItemTypePtr _getItemByIndex(int index) const;
	};
}