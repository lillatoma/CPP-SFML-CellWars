#include "Interfaces.h"

void player_t::Initialize(float range, int _tribe)
{
	for (int i = 0; i < 100; i++)villages[i] = nullptr;

	while (true)
	{
		int r = range;
		int cx = Random(-r, r);
		int cy = Random(-r, r);

		if (cx*cx + cy*cy > range*range)continue;
		if (base->Map.fields[cx + 400][cy + 400].type != PLOT_4446)continue;
		if (base->Map.fields[cx + 400][cy + 400].village != nullptr)continue;

		auto pvil = &base->villages;
		int id = 0;
		while (pvil->next)
		{
			pvil = pvil->next;
			id++;
		}
		pvil->next = new village_t;

		pvil->Initialize(&base->Map.fields[cx + 400][cy + 400], this);
		pvil->id = id + 1;
		printf("\n%d | %d", cx, cy);

		break;
	}

	tribe = _tribe;
}

void player_t::BuildOuter(int id)
{
	resource_t* res = &this->villages[this->selected_village]->res;
	resource_t cost = IBuildings::GetCost(this->villages[this->selected_village]->outer.buildings[id].type, this->villages[this->selected_village]->outer.buildings[id].hi_level);

	if (*res < cost)return;

	res->subtract(cost);

	this->villages[this->selected_village]->outer.buildings[id].hi_level++;
	IEvents::CreateOuterBuildCall(&base->events, villages[selected_village], id);



}

void player_t::BuildInner(int id)
{
	resource_t* res = &this->villages[this->selected_village]->res;
	resource_t cost = IBuildings::GetCost(this->villages[this->selected_village]->inner.buildings[id].type, this->villages[this->selected_village]->inner.buildings[id].hi_level);

	if (*res < cost)return;

	res->subtract(cost);

	this->villages[this->selected_village]->inner.buildings[id].hi_level++;
	IEvents::CreateInnerBuildCall(&base->events, villages[selected_village], id);



}