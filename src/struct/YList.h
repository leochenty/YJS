#pragma once

#include "src/struct/YStruct.h"

#include <deque>

namespace YJS_NAMESPACE {

	/*namespace yjs_list {

		ItemMessage itemMessage(
			'\0',
			Id(8, 0),
			Id(-1, 0),
			Id(-1, 0)
		);

		constexpr int cacheMax = 4;

		std::deque<ItemMessage> dequeTest;

		typedef deque<ItemMessage>::iterator dequePtr;

		int cacheNext = 0;
		int cachePos[cacheMax];
		dequePtr cachePtr[cacheMax];

		dequePtr temp;

		void localinsert(int index, char context) {
			itemMessage.character = context;
			++itemMessage.id.clock;
			for (int i = 0; i < cacheMax; ++i) {
				if (index == cachePos[i])
				{
					dequeTest.emplace(cachePtr[i], itemMessage);
					goto LOCALINSERT;
				}
			}
			{
				temp = dequeTest.begin() + index;
				auto p = dequeTest.emplace(temp, itemMessage);
				cachePos[cacheNext] = index;
				cachePtr[cacheNext] = temp;
				cacheNext = (cacheNext + 1) % cacheMax;
			}

			LOCALINSERT:
			for (int i = 0; i < cacheMax; ++i)
			{
				if (index <= cachePos[i])
				{
					++cachePos[i];
					++cachePtr[i];
				}
			}

		}

		void localDelete(int index) {
			for (int i = 0; i < cacheMax; ++i) {
				if (index == cachePos[i])
				{
					dequeTest.erase(cachePtr[i]);
				}
			}
			{
				temp = dequeTest.begin() + index;
				dequeTest.erase(temp);
				cachePos[cacheNext] = index;
				cachePtr[cacheNext] = temp;
				cacheNext = (cacheNext + 1) % cacheMax;
			}
		}
	};*/




};