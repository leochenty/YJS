#pragma once
#include "src/include/namespace.h"
#include <vector>
#include <tuple>
#include "src/item/id.h"
#include <string>

namespace YJS_NAMESPACE {
	typedef unsigned int Offset;
	typedef std::string Context;

	/*
		这是传输节点所需要的最小单位
	*/
	struct ItemMessage {
		char character;
		Id id;
		Id origin;
		Id rightOrigin;
	};

	/*
		这是一种特殊的叶子节点，任何实现底层算法的开发者需要以此类为基类，
		继承他并构造自己的叶子节点。
	*/
	class ItemListInterface {
	public:
		Context context;
		Id headId;
		Id headOrigin;
		Id endRightOrigin;

		// ItemListInterface():ItemListInterface('\0', Id(-1,-1) {}

		ItemListInterface(const ItemMessage& itemMessage)
				:context("" + itemMessage.character),
				headId(itemMessage.id),
				headOrigin(itemMessage.origin),
				endRightOrigin(itemMessage.rightOrigin){}



		virtual ~ItemListInterface() {};

	};






}