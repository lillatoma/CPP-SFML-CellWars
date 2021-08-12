#include "structs.h"


bool cmatch_t::BotSafeThink(int id)
{
	if (GetEmptyCells() == 0)return BotFreeThink(id);
	if (id < 2 || id > 10)return false;
	if (profiles[id - 2].intelligence == 1)
	{

		int own_cells = GetOwnedCells(id + 2);

		if (own_cells < 3)
		{
			int own_found = 0;
			int owned_found[3];

			for (int i = 0; i < cell_count; i++)
			{
				if (cells[i].owner_id == id)
				{
					owned_found[own_found] = i;
					own_found++;
				}
			}

			int owned_id = -1;

			for (int i = 0; i < own_found; i++)
			{
				auto j = owned_found[i];
				if (cells[j].species >= cells[j].size + 2)
				{
					owned_id = j;
					break;
				}

				else if (cells[j].species > cells[owned_id].species)owned_id = j;
				else if (owned_id == -1)
					owned_id = j;
			}

			if (owned_id == -1)return false;

			int used_up = 0;
			bool* used = new bool[cell_count];
			for (int z = 0; z < cell_count; z++)used[z] = false;


			int _id = -1;
			float dist = 2000;
			while (used_up != cell_count)
			{
				int r = Random(0, cell_count - 1);

				if (used[r])continue;
				used[r] = true;
				used_up++;
				if (cells[r].owner_id != 0)continue;


				if (_id == -1) {
					_id = r;
					dist = GetDist(owned_id, r);
				}
				else if (GetDist(r, owned_id) < dist)
				{
					_id = r;
					dist = GetDist(r, owned_id);
				}
			}
			delete[] used;
			if (cells[owned_id].species / 2 - 1 > cells[_id].species)
			{
				MoveSpecies(owned_id, _id);
				return true;
			}
			else return false;

		}
		else
		{

			int own_found = 0;
			int owned_found[100];

			for (int i = 0; i < cell_count; i++)
			{
				if (cells[i].owner_id == id)
				{
					owned_found[own_found] = i;
					own_found++;
				}
			}

			int owned_id = -1;

			for (int i = 0; i < own_found; i++)
			{
				auto j = owned_found[i];
				if (cells[j].species > cells[owned_id].species)owned_id = j;
				else if (owned_id == -1)
					owned_id = j;
			}

			if (owned_id == -1)return false;

			int used_up = 0;
			bool* used = new bool[cell_count];
			for (int z = 0; z < cell_count; z++)used[z] = false;

			int _id = -1;
			float resistance = 10000;
			while (used_up != cell_count)
			{
				int r = Random(0, cell_count - 1);

				if (used[r])continue;
				used[r] = true;
				used_up++;
				if (cells[r].owner_id != 0)continue;


				if (_id == -1) {
					if (cells[r].species != 0)
					{
						_id = r;
						resistance = cells[r].production_speed * cells[r].production_speed / (cells[r].species);
					}
				}
				else if (cells[r].species != 0 && cells[r].production_speed*cells[r].production_speed / (cells[r].species) > resistance)
				{
					_id = r;
					resistance = cells[r].production_speed*cells[r].production_speed / (cells[r].species);
				}
			}
			delete[] used;
			if (cells[owned_id].species / 2 - 1 > cells[_id].species)
			{
				MoveSpecies(owned_id, _id);
				return true;
			}
			else return BotFreeThink(id);
		}

	}
	else
	{
		int own = Random(0, cell_count - 1);
		while (cells[own].owner_id != id)own = Random(0, cell_count - 1);

		int tries = 0;

		int tar = own - 1;
		if (tar < 0)tar = own + 1;

		for (int i = 0; i < cell_count; i++)
		{
			if (cells[i].owner_id != 0)continue;
			if (GetDist(own, i) < GetDist(own, tar))tar = i;
		}

		if (cells[own].species > cells[tar].species / 2 + 1)
		{
			if (cells[tar].owner_id == id)return false;
			MoveSpecies(own, tar);
			return true;
		}
		return false;
	}
}

bool cmatch_t::BotFreeThink(int id)
{
	if (id < 2 || id > 10)return false;
	if (profiles[id - 2].intelligence == 0)
	{

		int own = Random(0, cell_count - 1);
		while (cells[own].owner_id != id)own = Random(0, cell_count - 1);

		int tries = 0;

		int tar = Random(0, cell_count - 1);

		while (true)
		{
			if (tries > 2000)break;
			tar = Random(0, cell_count - 1);

			if (cells[tar].owner_id != id && cells[own].species - 3 >= cells[tar].species * 2)
			{
				break;
				tries = 0;
			}

			tries++;
		}


		if (tries < 2000)
		{
			MoveSpecies(own, tar);
			return true;
		}
		return false;
	}
	else
	{
		int own_found = 0;
		int owned_found[100];

		for (int i = 0; i < cell_count; i++)
		{
			if (cells[i].owner_id == id)
			{
				owned_found[own_found] = i;
				own_found++;
			}
		}

		int owned_id[3] = { -1,-1,-1 };

		for (int i = 0; i < own_found; i++)
		{
			auto j = owned_found[i];
			if (cells[j].species > cells[owned_id[0]].species)
			{
				owned_id[2] = owned_id[1];
				owned_id[1] = owned_id[0];
				owned_id[0] = j;


			}
			else if (owned_id[0] == -1)
				owned_id[0] = j;
		}

		int used_up = 0;
		bool* used = new bool[cell_count];
		for (int z = 0; z < cell_count; z++)used[z] = false;

		int _id = -1;
		float resistance = 1;

		while (used_up != cell_count)
		{
			int r = Random(0, cell_count - 1);

			if (used[r])continue;
			used[r] = true;
			used_up++;
			if (cells[r].owner_id == id)continue;


			if (_id == -1 && cells[r].species != 0) {

				_id = r;
				resistance = cells[r].production_speed * cells[r].production_speed / (cells[r].species);
			}
			else if (cells[r].species != 0 && cells[r].production_speed*cells[r].production_speed / (cells[r].species) > resistance)
			{
				_id = r;
				resistance = cells[r].production_speed*cells[r].production_speed / (cells[r].species);
			}
		}
		delete[] used;
		if (cells[owned_id[0]].species / 2 - 1 > cells[_id].size)
		{
			MoveSpecies(owned_id[0], _id);
			return true;
		}
		else if (owned_id[1] != -1 && (cells[owned_id[0]].species + cells[owned_id[1]].species) / 2 - 2 > cells[_id].size)
		{
			MoveSpecies(owned_id[0], _id);
			MoveSpecies(owned_id[1], _id);
			profiles[id - 2].decisions_made += 1;
			return true;
		}
		else if (owned_id[2] != -1 && owned_id[1] != -1 && (cells[owned_id[0]].species + cells[owned_id[1]].species + cells[owned_id[2]].species) / 2 - 2 > cells[_id].size)
		{
			MoveSpecies(owned_id[0], _id);
			MoveSpecies(owned_id[1], _id);
			MoveSpecies(owned_id[2], _id);
			profiles[id - 2].decisions_made += 2;
			return true;
		}
		else return false;

	}
}

bool cmatch_t::BotAggress(int id)
{
	if (id < 2 || id > 10)return false;
	if (profiles[id - 2].intelligence == 0)
	{
		int own = Random(0, cell_count - 1);
		while (cells[own].owner_id != id)own = Random(0, cell_count - 1);

		int tries = 0;

		int tar = Random(0, cell_count - 1);

		while (true)
		{
			if (tries > 2000)break;
			tar = Random(0, cell_count - 1);

			if (cells[tar].owner_id != id &&  cells[tar].owner_id != 0)
			{
				if (cells[own].species - 3 >= cells[tar].species * 2 || Random(0, 1000) < 250)
				{

					tries = 0;
					break;
				}
			}

			tries++;
		}


		if (tries < 2000)
		{
			MoveSpecies(own, tar);
			return true;
		}
		int decs_should_have_made = (profiles[id - 2].spent_time - profiles[id - 2].warmuptime) / profiles[id - 2].decisiontime + 1;

		if (profiles[id + 2].decisions_made > decs_should_have_made + 2)
			return BotFreeThink(id);
		return false;
	}
	else
	{

		int own_found = 0;
		int owned_found[100];

		for (int i = 0; i < cell_count; i++)
		{
			if (cells[i].owner_id == id)
			{
				owned_found[own_found] = i;
				own_found++;
			}
		}

		int owned_id[3] = { -1,-1,-1 };

		for (int i = 0; i < own_found; i++)
		{
			auto j = owned_found[i];
			if (cells[j].species > cells[owned_id[0]].species)
			{
				owned_id[2] = owned_id[1];
				owned_id[1] = owned_id[0];
				owned_id[0] = j;


			}
			else if (owned_id[0] == -1)
				owned_id[0] = j;
		}

		int used_up = 0;
		bool* used = new bool[cell_count];
		for (int z = 0; z < cell_count; z++)used[z] = false;

		int _id = -1;
		float resistance = 10000;

		while (used_up != cell_count)
		{
			int r = Random(0, cell_count - 1);

			if (used[r])continue;
			used[r] = true;
			used_up++;
			if (cells[r].owner_id == id || cells[r].owner_id == 0)continue;


			if (_id == -1 && cells[r].species != 0) {
				_id = r;
				resistance = cells[r].production_speed * cells[r].production_speed / (cells[r].species);
			}
			else if (cells[r].species != 0&& cells[r].production_speed*cells[r].production_speed / (cells[r].species) > resistance)
			{
				_id = r;
				resistance = cells[r].production_speed*cells[r].production_speed / (cells[r].species);
			}
		}
		delete[] used;
		if (cells[owned_id[0]].species / 2 - 1 > cells[_id].size)
		{
			MoveSpecies(owned_id[0], _id);
			return true;
		}
		else if (owned_id[1] != -1 && (cells[owned_id[0]].species + cells[owned_id[1]].species) / 2 - 2 > cells[_id].size)
		{
			MoveSpecies(owned_id[0], _id);
			MoveSpecies(owned_id[1], _id);
			profiles[id - 2].decisions_made += 1;
			return true;
		}
		else if (owned_id[2] != -1 && owned_id[1] != -1 && (cells[owned_id[0]].species + cells[owned_id[1]].species + cells[owned_id[2]].species) / 2 - 2 > cells[_id].size)
		{
			MoveSpecies(owned_id[0], _id);
			MoveSpecies(owned_id[1], _id);
			MoveSpecies(owned_id[2], _id);
			profiles[id - 2].decisions_made += 2;
			return true;
		}
		else return false;

	}



}

bool cmatch_t::BotFullThink(int id)
{
	if (id < 2 || id > 10)return false;
	if (profiles[id - 2].intelligence == 0)
	{
		int own = Random(0,cell_count-1);

		while (cells[own].owner_id != id)
		{
			own = Random(0, cell_count - 1);
		}

		int tar = Random(0, cell_count - 1);

		while (cells[tar].owner_id == id)
		{
			tar = Random(0, cell_count - 1);
		}

		MoveSpecies(own, tar);
		return true;
	}
	else
	{
		int own[3] = { Random(0,cell_count-1),Random(0,cell_count - 1),Random(0,cell_count - 1) };
		int max_owned_cells = GetOwnedCells(id + 2);
		
		while (cells[own[0]].owner_id != id)
		{
			own[0] = Random(0, cell_count - 1);
		}
		while (max_owned_cells > 1 && own[0] != own[1] && cells[own[1]].owner_id != id)
		{
			own[1] = Random(0, cell_count - 1);
		}
		while (max_owned_cells > 2 && own[0] != own[2] && own[1] != own[2] && cells[own[2]].owner_id != id)
		{
			own[2] = Random(0, cell_count - 1);
		}
		
		int tar = Random(0, cell_count - 1);
		while (cells[tar].owner_id == id)
		{
			tar = Random(0, cell_count - 1);
		}
		profiles[id - 2].decisions_made--;
		for (int i = 0; i < 3; i++)
		{
			if (cells[own[i]].owner_id == id)
			{
				MoveSpecies(own[i], tar);
				profiles[id - 2].decisions_made++;
			}
		}
		return true;
	}
}

void cmatch_t::BotThink()
{
	using namespace std::chrono;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	int diff = duration_cast<milliseconds>(now - last).count();
	if (reset_timer) {
		last = now;
		return;
	}
	last = now;
	if (pause)diff = 0;
	for (int i = 0; i < 8; i++)
	{
		profiles[i].spent_time += diff;

		if (profiles[i].spent_time > profiles[i].warmuptime)
		{
			int decs_should_have_made = (profiles[i].spent_time - profiles[i].warmuptime) / profiles[i].decisiontime + 1;
			if (decs_should_have_made > profiles[i].decisions_made)
			{
				auto perc = GetPercent(i + 2);
				if (perc < 0.1 || GetOwnedCells(i + 2) == 0 || GetOwnedCells(i+2) == cell_count)continue;
				else if (isFull(i + 2))BotFullThink(i + 2);
				else if ((perc < profiles[i].percent_to_freely_decide && GetEmptyCells() != 0) || Random(0, cell_count) > GetEmptyCells())profiles[i].decisions_made += BotSafeThink(i + 2);
				else if (perc < profiles[i].percent_to_aggress)profiles[i].decisions_made += BotFreeThink(i + 2);
				else profiles[i].decisions_made += BotAggress(i + 2);
			}
		}

	}
}