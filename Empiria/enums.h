#pragma once
enum Buildings
{
	MAIN = 0, //done
	EMBASSY, //pretty much
	CRANNY, //done
	MARKETPLACE, //done
	TOWNHALL, //done 
	RESIDENCE, //done
	PALACE, //done
	TREASURY,
	TRADEOFFICE, //done
	BREWERY,
	HORSEDRINKING , //done

	RALLYPOINT, //done
	ROMANWALL, //done
	GAULWALL, //done
	GERMANWALL, //done
	BARRACKS, //done
	ACADEMY, //done
	BLACKSMITH,
	STABLE, //done
	STONEMASON, //done
	WORKSHOP, //done
	HEROMANSION ,
	TOURNAMENTSQUARE, //done
	GREATBARRACKS,
	GREATSTABLE,

	WAREHOUSE, //done
	GRANARY, //done
	WOODBONUS, //done
	CLAYBONUS , //done
	IRONBONUS, //done
	MILL , //done
	BAKERY, //done

	WOOD, //done
	CLAY, //done
	IRON, //done
	WHEAT, //done


	FREE = 100,
};

enum Plot
{

	/*	if (_Type <= 50) { _Type = 1; } // 4-4-4-6
	else if (_Type <= 60) { _Type = 2; } // 4-3-5-6
	else if (_Type <= 70) { _Type = 3; } // 4-5-3-6
	else if (_Type <= 80) { _Type = 4; } // 3-4-5-6
	else if (_Type <= 90) { _Type = 5; } // 5-4-3-6
	else if (_Type <= 100) { _Type = 6; } // 3-5-4-6
	else if (_Type <= 110) { _Type = 7; } // 5-3-4-6
	else if (_Type <= 116) { _Type = 8; } // 3-4-4-7
	else if (_Type <= 122) { _Type = 9; } // 4-3-4-7
	else if (_Type <= 128) { _Type = 10; } // 4-4-3-7
	else if (_Type <= 130) { _Type = 11; } // 3-3-3-9
	else if (_Type <= 131) { _Type = 12; } // 1-1-1-15
	else if (_Type <= 160) { _Type = 500; } // raw
	else if (_Type <= 166) { _Type = 501; } // +25% wood
	else if (_Type <= 172) { _Type = 502; } // +25% clay
	else if (_Type <= 178) { _Type = 503; } // +25% iron
	else if (_Type <= 184) { _Type = 504; } // +25% crop
	else if (_Type <= 187) { _Type = 505; } // +50% crop
	*/
	PLOT_4446 = 1,
	PLOT_4356,
	PLOT_4536,
	PLOT_3456,
	PLOT_5436,
	PLOT_3546,
	PLOT_5346,
	PLOT_3447,
	PLOT_4347,
	PLOT_4437,
	PLOT_3339,
	PLOT_11115,
	PLOT_RAW = 500,
	PLOT_WOOD,
	PLOT_CLAY,
	PLOT_IRON,
	PLOT_CROP,
	PLOT_CROPEXTRA
};

enum Events
{
	_EVENT_BUILD_OUTER = 0,
	_EVENT_BUILD_INNER,
	_EVENT_DEMOLISH,
	_EVENT_ATTACK,
	_EVENT_RAID,
	_EVENT_SPY,
	_EVENT_SUPPORT,
	_EVENT_HOMECOMING,
	_EVENT_SUPPLY_TO,
	_EVENT_SUPPLY_BACK,
	_EVENT_NEW_VILLAGE,
	_EVENT_TRAIN_BARRACKS,
	_EVENT_TRAIN_STABLE,
	_EVENT_TRAIN_WORKSHOP,
	_EVENT_TRAIN_PALACE,
	_EVENT_DEVELOP,
	_EVENT_CELEBRATE
};

enum TRIBES
{
	ROMAN,
	GAUL,
	GERMAN,
	NATAR,
	ANIMAL
};

enum LOGTYPES
{
	_LOG_RAID,
	_LOG_ATTACK,
	_LOG_SPY,
	_LOG_DEFEND_RAID,
	_LOG_DEFEND_NORMAL,
	_LOG_SPY_CAUGHT,
	_LOG_SPY_HIDDEN,
	_LOG_LOST
};

enum TROOPSANIMALS
{
	RAT,
	SPIDER,
	SERPENT,
	BAT,
	WILDBOAR,
	WOLF,
	BEAR,
	CROCODILE,
	TIGER,
	ELEPHANT
};