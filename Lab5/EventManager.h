#pragma once

#include "EventList.h"
#include <unordered_map>

namespace Events
{
	class EventManagerType : public std::unordered_map<EventList, void*>
	{
		public:

		static EventManagerType* Instance;

		void InsertPair(EventList, void*);

		EventManagerType();
	};
}

