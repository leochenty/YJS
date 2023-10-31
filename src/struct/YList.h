#pragma once

#include "src/struct/YStruct.h"

#include <list>

namespace YJS_NAMESPACE {
	class YList : public YInterface {
	public:
		class ItemList : public ItemListInterface {
		public:
			ItemList(const ItemMessage& itemMessage)
				:ItemListInterface(itemMessage),
				size(1),
				realSize(1),
				isDelete(std::vector<char>(1,0)){};

			//ItemList(const ItemListInterface& p)
			//	:ItemListInterface(p)
			//{};

			virtual ~ItemList() {};
			// 添加你需要的的变量, 这是一个例子
			ItemList* left = nullptr;

			ItemList* right = nullptr;

			std::vector<char> isDelete;

			int size;
			int realSize;
		};

		typedef unsigned int Size;
		typedef ItemList* ItemListPtr;

		ItemListPtr head;

		YList() {
			head = new ItemList(
				ItemMessage{ '\0', Id(-1,-1) , Id(-1, -1), Id(-1, -1) });
			head->left = head;
			head->right = head;
		};
		virtual ~YList() {
			delete head;
		};

		//Size size = 0;


		virtual inline ItemPtr begin() const override {
			return ItemPtr(head->right, 0);
		};

		virtual inline ItemPtr end() const override {
			return ItemPtr(head, 0);
		};

		virtual void insertItem(Index index, ItemMessage itemMsg) override;

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
		ItemPtr _getItemByIndex(int index) const;
	};
}