#pragma once

#include "src/include/namespace.h"

namespace YJS_NAMESPACE{
	typedef unsigned int Clock;
	typedef unsigned int ClientId;
	class Id
		{
		public:
			// Id() {};
			~Id() {};

			Id(int client, int clock)
				:client(client), clock(clock){};

			ClientId client = 0;
			Clock clock = 0;


		};

}
