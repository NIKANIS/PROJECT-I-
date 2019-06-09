#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum AXIS
{
	AXIS_UP,
	AXIS_UPRIGHT,
	AXIS_RIGHT,
	AXIS_RIGHTDOWN,
	AXIS_DOWN,
	AXIS_DOWNLEFT,
	AXIS_LEFT,
	AXIS_LEFTUP,
	MAX
};


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	//bool JoystickGetPos(SDL_GameController * gamepad, AXIS axisDir);
	//bool ButtonTrigger(SDL_GameController * gamepad, SDL_GameControllerButton button);

public:
	KEY_STATE keyboard[MAX_KEYS];
	bool New_A[16] = { true };
	bool New_B[16] = { true };
	bool New_Direction[8] = { true };

	SDL_GameController* controller[2];
};

#endif // __ModuleInput_H__