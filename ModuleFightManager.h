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
private:
	int winner;
	int pl_won_rounds;
	int en_won_rounds;
};

#endif

