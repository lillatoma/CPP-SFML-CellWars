#include "Interfaces.h"

struct CompareEvents
{
	bool operator() (event_t & lhs, event_t & rhs)
	{
		return (lhs.Valid > rhs.Valid) || (lhs.Valid == rhs.Valid && lhs.event_force_time > rhs.event_force_time);
	}
};

void IEvents::SortEvents(eventtable_t* table)
{
	std::sort(table->events, table->events + table->active_events, CompareEvents());

}


void IEvents::CreateGlobalEvent(eventtable_t* table, event_t eve)
{
	SortEvents(table);

	int M = table->active_events;

	for (int i = 0; i < sizeof(event_t); i++)
	{
		*(((char*)&table->events[M]) + i) = *(((char*)&eve) + i);
	}


	table->active_events++;

	SortEvents(table);
}

void IEvents::TimeTravel(eventtable_t* et, int time)
{
	for (int i = 0; i < time; i++)
	{
		et->Time++;
		et->main->Produce();
		DoEvents(et);
	}
}

void IEvents::DoEvents(eventtable_t* et)
{
	while (et->events[et->active_events - 1].Valid && et->events[et->active_events - 1].event_force_time <= et->Time && et->active_events >= 0)
	{
		SortEvents(et);
		auto &event = et->events[et->active_events - 1];

		switch (event.eventtype)
		{
		case _EVENT_BUILD_OUTER:
			event.Valid = false;
			et->main->GetVillage(event.requesting_id)->outer.buildings[event.building_id].level++;
			et->active_events--;
			break;
		case _EVENT_BUILD_INNER:
			event.Valid = false;
			et->main->GetVillage(event.requesting_id)->inner.buildings[event.building_id].level++;
			et->active_events--;
			break;
		}
	}
}

void IEvents::CreateOuterBuildCall(eventtable_t* et, village_t* v, int building_id)
{
	event_t event;
	event.Valid = true;
	event.requesting_id = v->id;
	event.building_id = building_id;
	event.building_level = v->outer.buildings[building_id].hi_level;
	event.eventtype = _EVENT_BUILD_OUTER;
	//count with time
	event.event_force_time = max(et->Time, GetHighestTime(et, v, _EVENT_BUILD_OUTER)) + IBuildings::GetTime(v, v->outer.buildings[building_id].type, v->outer.buildings[building_id].hi_level - 1);

	CreateGlobalEvent(et, event);
}

void IEvents::CreateInnerBuildCall(eventtable_t* et, village_t* v, int building_id)
{
	event_t event;
	event.Valid = true;
	event.requesting_id = v->id;
	event.building_id = building_id;
	event.building_level = v->inner.buildings[building_id].hi_level;
	event.eventtype = _EVENT_BUILD_INNER;
	//count with time
	event.event_force_time = max(et->Time, GetHighestTime(et, v, _EVENT_BUILD_INNER)) + IBuildings::GetTime(v, v->inner.buildings[building_id].type, v->inner.buildings[building_id].hi_level - 1);

	CreateGlobalEvent(et, event);
}

int IEvents::GetHighestTime(eventtable_t* table, village_t* v, int EVENT)
{
	int highest_time = 0;
	for (int i = 0; i < table->active_events; i++)
	{
		if (table->events[i].eventtype != EVENT) continue;
		if (table->events[i].requesting_id != v->id)continue;
		if (highest_time < table->events[i].event_force_time)highest_time = table->events[i].event_force_time;
	}

	return highest_time;
}

int IEvents::CountEvents(eventtable_t* table, village_t* v, int EVENT)
{
	int event_sum = 0;
	for (int i = 0; i < table->active_events; i++)
	{
		if (table->events[i].eventtype != EVENT) continue;
		if (table->events[i].requesting_id != v->id)continue;
		event_sum++;
	}

	return event_sum;
}