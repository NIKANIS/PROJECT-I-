#ifndef _ModuleFightManager_H__
#define _ModuleFightManager_H__

#include "Globals.h"
#include "Module.h"

class ModuleFightManager : public Module
{
public:
	ModuleFightManager();
	~ModuleFightManager();

	bool Start();
	update_status Update();
	bool CleanUp();
	int Time();
private:
	int winner; // 0 = P1_win, 1 = P2_win, 2 = draw
	int pl_won_rounds;
	int en_won_rounds;
	int timer_num;
	int timer_counter;
	bool time_stop;
	void Reset();
};

#endif

