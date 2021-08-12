#include "Interfaces.h"

void outer_t::Define(int type)
{
	static int list[12][18] =
	{ { WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, IRON, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, CLAY, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, WOOD, WOOD, CLAY, CLAY, CLAY, IRON, IRON, IRON, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT, WHEAT },
	{ WOOD, CLAY, IRON, WHEAT,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT ,WHEAT }
	};

	for (int i = 0; i < 18; i++)
	{
		buildings[i].defined = true;
		buildings[i].hi_level = 0;
		buildings[i].level = 0;
		buildings[i].type = list[type-1][i];
	}
}

void inner_t::Define(int tribe)
{
	for (int i = 0; i < 22; i++)
	{
		buildings[i].defined = false;
		buildings[i].level = 0;
	}
	buildings[0].type = MAIN;
	buildings[0].defined = true;
	buildings[0].level = 1;
	buildings[0].hi_level = 1;
	buildings[20].type = RALLYPOINT;
	buildings[20].defined = true;
	buildings[21].defined = true;
	buildings[21].type = ROMANWALL + tribe;
	if (tribe > 2)buildings[21].type = ROMANWALL;
}

void village_t::Initialize(field_t* fl, player_t* pl)
{
	if (fl->type > 500)
	{
		
	}
	else
	{
		inner.Define(pl->tribe);
		outer.Define(fl->type);

		this->field = fl;
		this->owner = pl;
		this->res.define(750, 750, 750, 750);
		
		for (int i = 0; i < 100; i++)
		{
			if (pl->villages[i] == nullptr)
			{
				pl->villages[i] = this;
				
				break;
			}
		}
		fl->village = this;
		
		//fl->village_id = pl->base->






	}







}