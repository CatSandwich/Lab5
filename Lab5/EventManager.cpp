#include "EventManager.h"

namespace Events
{
	EventManagerType* EventManagerType::Instance = nullptr;

	EventManagerType::EventManagerType()
	{
		Instance = this;
	}

	void EventManagerType::InsertPair(EventList el, void* e)
	{
		insert(std::pair<EventList, void*>(el, e));
	}
}