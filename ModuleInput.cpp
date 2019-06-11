#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include <stdio.h>
#include <string.h>
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_EVENTS could not initialize Game Controller! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller[i] = SDL_GameControllerOpen(i);
			if (controller[i] == NULL) {
				LOG("Can't open controller %s", SDL_GetError());

			}
		}
	}

	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	//for (int i = 0; i < 8; i++) {
	//	if (App->input->JoystickGetPos(App->input->controller[0], (AXIS)i) == false)
	//		App->input->New_Direction[i] = true;
	//}


	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;


	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}

//bool ModuleInput::JoystickGetPos(SDL_GameController* gamepad, AXIS axisDir) {
//	bool ret = false;
//
//	int deadzone = 7849;
//	int xAxis = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX);
//	int yAxis = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY);
//
//	if (yAxis < -deadzone && axisDir == AXIS_UP)	ret = true;
//	if (yAxis > deadzone && axisDir == AXIS_DOWN)	ret = true;
//	if (xAxis > deadzone && axisDir == AXIS_RIGHT)	ret = true;
//	if (xAxis < -deadzone && axisDir == AXIS_LEFT)	ret = true;
//
//	if (yAxis < -deadzone && xAxis > deadzone && axisDir == AXIS_UPRIGHT)		ret = true;
//	if (yAxis > deadzone && xAxis > -deadzone && axisDir == AXIS_DOWNLEFT)		ret = true;
//	if (yAxis > deadzone && xAxis > deadzone && axisDir == AXIS_LEFTUP)			ret = true;
//	if (yAxis < -deadzone && xAxis > -deadzone && axisDir == AXIS_RIGHTDOWN)	ret = true;
//	return ret;
//}
///* estos son los valores que hay que ponerle al segundo parametro de la función, cada uno es un boton del mando
//SDL_CONTROLLER_BUTTON_INVALID
//SDL_CONTROLLER_BUTTON_A
//SDL_CONTROLLER_BUTTON_B
//SDL_CONTROLLER_BUTTON_X
//SDL_CONTROLLER_BUTTON_Y
//SDL_CONTROLLER_BUTTON_BACK
//SDL_CONTROLLER_BUTTON_GUIDE
//SDL_CONTROLLER_BUTTON_START
//SDL_CONTROLLER_BUTTON_LEFTSTICK
//SDL_CONTROLLER_BUTTON_RIGHTSTICK
//SDL_CONTROLLER_BUTTON_LEFTSHOULDER
//SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
//SDL_CONTROLLER_BUTTON_DPAD_UP
//SDL_CONTROLLER_BUTTON_DPAD_DOWN
//SDL_CONTROLLER_BUTTON_DPAD_LEFT
//SDL_CONTROLLER_BUTTON_DPAD_RIGHT
//SDL_CONTROLLER_BUTTON_MAX
//*/
//
//bool ModuleInput::ButtonTrigger(SDL_GameController* gamepad, SDL_GameControllerButton button) {
//	if (gamepad != nullptr)
//	{
//		if (gamepad == controller[0]) {
//			if (SDL_GameControllerGetButton(controller[0], button) == 1) {
//				if (New_A[button]) {
//					New_A[button] = false;
//					return true;
//				}
//			}
//			else if (SDL_GameControllerGetButton(controller[0], button) == 0) {
//				if (New_A[button] == false) {
//					New_A[button] = true;
//				}
//			}
//
//		}
//		else if (gamepad == controller[1])
//		{
//			if (SDL_GameControllerGetButton(controller[1], button) == 1) {
//				if (New_B[button]) {
//					New_B[button] = false;
//					return true;
//				}
//			}
//			else if (SDL_GameControllerGetButton(controller[1], button) == 0) {
//				if (New_B[button] == false) {
//					New_B[button] = true;
//				}
//			}
//		}
//	}
//	
//
//	return false;
//}