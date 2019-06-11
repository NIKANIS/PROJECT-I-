
#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL_events.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 15

#define GAME_PAD_1 0
#define GAME_PAD_2 1
#define MAX_GAME_PAD 2

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
public:
	KEY_STATE keyboard[MAX_KEYS];
	SDL_Event Events;
	Uint8 game_pad[MAX_BUTTONS][MAX_GAME_PAD];

	SDL_GameController* controller_player_1 = nullptr;
	SDL_GameController* controller_player_2 = nullptr;

private:
	int controller_1_index;
};

#endif // __ModuleInput_H__