#ifndef __ModuleCombos_H__
#define __ModuleCombos_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"

#define SPLASHFOUNT 50
#define POWERGRADUATION 60

class ModuleCombos : public Module
{
public:
	ModuleCombos();
	~ModuleCombos();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool SpecialAttack3(int player);
	/*bool CheckPunchP2();

	bool CheckSplashFountP1();
	bool CheckSplashFountP2();

	bool CheckPowerGraduationP1();
	bool CheckPowerGraduationP2();*/

public:
	int actual_frameP1SF = 0;
	int actual_frameP2SF = 0;

	int actual_frameP1PG = 0;
	int actual_frameP2PG = 0;

	int SplashFountCount = 0;
	int SplashFountCount2 = 0;

	int PowerGraditionCount = 0;
	int PowerGraditionCount2 = 0;

	int HoldGP1 = 0;
	int HoldGP2 = 0;
};
#endif // __ModuleCombos_H__