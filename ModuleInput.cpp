#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		controll[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		P2_controll[i] = KEY_IDLE;
}

ModuleInput::~ModuleInput()
{
}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	SDL_Init(SDL_INIT_JOYSTICK);
	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No joysticks connected!\n");
	}
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
			{
				if (i == 0)
				{
					controller = SDL_GameControllerOpen(i);
				}

				if (i == 1)
				{
					P2_controller = SDL_GameControllerOpen(i);
					break;
				}
			}
			else
			{
				LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{

	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Uint8 buttons[MAX_BUTTONS];
	Uint8 P2_buttons[MAX_BUTTONS];

	buttons[0] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	buttons[1] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	buttons[2] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	buttons[3] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	buttons[4] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A);
	buttons[5] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_B);
	buttons[6] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_X);
	buttons[7] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_BACK);


	P2_buttons[0] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	P2_buttons[1] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	P2_buttons[2] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	P2_buttons[3] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	P2_buttons[4] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_A);
	P2_buttons[5] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_B);
	P2_buttons[6] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_X);
	P2_buttons[7] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_BACK);
	

	



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

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (buttons[i] == 1)
		{
			if (controll[i] == KEY_IDLE)
				controll[i] = KEY_DOWN;
			else
				controll[i] = KEY_REPEAT;
		}
		else
		{
			if (controll[i] == KEY_REPEAT || controll[i] == KEY_DOWN)
				controll[i] = KEY_UP;
			else
				controll[i] = KEY_IDLE;
		}
	}
	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (P2_buttons[i] == 1)
		{
			if (P2_controll[i] == KEY_IDLE)
				P2_controll[i] = KEY_DOWN;
			else
				P2_controll[i] = KEY_REPEAT;
		}
		else
		{
			if (P2_controll[i] == KEY_REPEAT || P2_controll[i] == KEY_DOWN)
				P2_controll[i] = KEY_UP;
			else
				P2_controll[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;
	if (App->input->controll[BUTTON_BACK] == KEY_STATE::KEY_DOWN || App->input->P2_controll[BUTTON_BACK] == KEY_STATE::KEY_DOWN)
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_GameControllerClose(controller);
	controller = NULL;
	SDL_GameControllerClose(P2_controller);
	P2_controller = NULL;

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

bool ModuleInput::JoystickGetPos(SDL_GameController * gamepad, AXIS axis) 
{

	bool ret = false;
	if (gamepad != nullptr)
	{
		int deadzone_x = 7849;
		int deadzone_y = 15698;

		int xAxis = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX);
		int yAxis = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY);

		if (xAxis > deadzone_x && axis == RIGHT) ret = true;
		if (xAxis < -deadzone_x && axis == LEFT) ret = true;
		if (yAxis < -deadzone_y && axis == UP) ret = true;
		if (yAxis > deadzone_y && axis == DOWN) ret = true;

		if (yAxis < -deadzone_x && xAxis > deadzone_x && axis == UPRIGHT)		ret = true;
		if (yAxis > deadzone_x && xAxis > -deadzone_x && axis == DOWNLEFT)		ret = true;
		if (yAxis > deadzone_x && xAxis > deadzone_x && axis == LEFTUP)		ret = true;
		if (yAxis < -deadzone_x && xAxis > -deadzone_x && axis == RIGHTDOWN)	ret = true;

	}
	
	return ret;

}

