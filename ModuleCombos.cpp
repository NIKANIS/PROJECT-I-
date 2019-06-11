#include "Globals.h"
#include "Application.h"
#include "ModuleCombos.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

ModuleCombos::ModuleCombos() : Module()
{}

// Destructor
ModuleCombos::~ModuleCombos()
{}

bool ModuleCombos::Init() {
	LOG("Init ModuleCOMBOS");

	return true;
}

bool ModuleCombos::CleanUp() {

	return true;
}

update_status ModuleCombos::Update() 
{



	return update_status::UPDATE_CONTINUE;
}

bool ModuleCombos::SpecialAttack3(int player) 
{
	if (player == 0)
	{
		actual_frameP1SF++;
		if (actual_frameP1SF <= 60)
		{
			switch (SplashFountCount)
			{
				case 0:
				{
					if (App->input->JoystickGetPos(App->input->controller, DOWN) == true)
						SplashFountCount++;
				}break;

				case 1:
				{
					if (App->input->JoystickGetPos(App->input->controller, LEFT) == true)
						SplashFountCount++;
				}break;
				
				case 2:
				{
					if (App->input->controll[BUTTON_A] == KEY_STATE::KEY_DOWN)
					{
						SplashFountCount = 0;
						return true;
					}
				}break;
			}
		}
		else
		{
			actual_frameP1SF = 0;
			SplashFountCount = 0;
			return false;
		}
	}
	else
	{
		actual_frameP1SF++;
		if (actual_frameP1SF <= 60)
		{
			switch (SplashFountCount)
			{
			case 0:
			{
				if (App->input->JoystickGetPos(App->input->P2_controller, DOWN) == true)
					SplashFountCount++;
			}break;
			case 1:
			{
				if (App->input->JoystickGetPos(App->input->P2_controller, LEFT) == true)
					SplashFountCount++;
			}break;
			case 2:
			{

				if (App->input->P2_controll[BUTTON_A] == KEY_DOWN)
				{
					SplashFountCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameP1SF = 0;
			SplashFountCount = 0;
			return false;
		}
	}
	return false;
}

bool ModuleCombos::SpecialAttack(int player)
{
	if (player == 0)
	{
		actual_frameSP++;
		if (actual_frameSP <= 30)
		{
			switch (SPCount)
			{
			case 0:
			{
				if (App->input->JoystickGetPos(App->input->controller, DOWN) == true)
					SPCount++;
			}break;
			case 1:
			{
				if (App->input->JoystickGetPos(App->input->controller, RIGHT) == true)
					SPCount++;
			}break;
			case 2:
			{

				if (App->input->controll[BUTTON_X] == KEY_DOWN)
				{
					SPCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameSP = 0;
			SPCount = 0;
			return false;
		}
	}
	else
	{
		actual_frameSP++;
		if (actual_frameSP <= 30)
		{
			switch (SPCount)
			{
			case 0:
			{
				if (App->input->JoystickGetPos(App->input->P2_controller, DOWN) == true)
					SPCount++;
			}break;
			case 1:
			{
				if (App->input->JoystickGetPos(App->input->P2_controller, RIGHT) == true)
					SPCount++;
			}break;
			case 2:
			{

				if (App->input->P2_controll[BUTTON_X] == KEY_DOWN)
				{
					SPCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameSP = 0;
			SPCount = 0;
			return false;
		}
	}
	return false;
}

bool ModuleCombos::SpT(int player)
{
	if (player == 0)
	{
		actual_frameSPT++;
		if (actual_frameSPT <= 120)
		{
			switch (SPTCount)
			{
			case 0:
			{
				if (App->input->JoystickGetPos(App->input->controller, LEFT) == true)
					SPTCount++;
			}break;
			case 1:
			{
				if (App->input->JoystickGetPos(App->input->controller, RIGHT) == true)
					SPTCount++;
			}break;
			case 2:
			{

				if (App->input->controll[BUTTON_A] == KEY_DOWN)
				{
					SPTCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameSPT = 0;
			SPTCount = 0;
			return false;
		}
	}
	else
	{
		actual_frameSPT++;
		if (actual_frameSPT <= 120)
		{
			switch (SPTCount)
			{
			case 0:
			{
				if (App->input->JoystickGetPos(App->input->P2_controller, LEFT) == true)
					SPTCount++;
			}break;
			case 1:
			{
				if (App->input->JoystickGetPos(App->input->P2_controller, RIGHT) == true)
					SPTCount++;
			}break;
			case 2:
			{

				if (App->input->P2_controll[BUTTON_A] == KEY_DOWN)
				{
					SPTCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameSPT = 0;
			SPTCount = 0;
			return false;
		}
	}
	return false;
}

bool ModuleCombos::SpJ(int player)
{
	if (player == 0)
	{
		actual_frameSPJ++;
		if (actual_frameSPJ <= 30)
		{
			switch (SPJCount)
			{
			case 0:
			{
				if (App->input->controll[BUTTON_X] == KEY_DOWN)
					SPJCount++;
			}break;
			case 1:
			{
				if (App->input->controll[BUTTON_X] == KEY_DOWN)
					SPJCount++;
			}break;
			case 2:
			{

				if (App->input->controll[BUTTON_X] == KEY_DOWN)
				{
					SPJCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameSPJ = 0;
			SPJCount = 0;
			return false;
		}
	}
	else
	{
		actual_frameSPJ++;
		if (actual_frameSPJ <= 30)
		{
			switch (SPJCount)
			{
			case 0:
			{
				if (App->input->P2_controll[BUTTON_X] == KEY_DOWN)
					SPJCount++;
			}break;
			case 1:
			{
				if (App->input->P2_controll[BUTTON_X] == KEY_DOWN)
					SPJCount++;
			}break;
			case 2:
			{

				if (App->input->P2_controll[BUTTON_X] == KEY_DOWN)
				{
					SPJCount = 0;
					return true;
				}
			}break;
			}
		}
		else
		{
			actual_frameSPJ = 0;
			SPJCount = 0;
			return false;
		}
	}
	return false;
}

/*bool ModuleCombos::CheckPunchP2() {
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		return true;
	}
	return false;
}

bool ModuleCombos::CheckSplashFountP1() {
	actual_frameP1SF++;
	if (actual_frameP1SF <= SPLASHFOUNT) {
		switch (SplashFountCount)
		{
		case 0:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN)  {
				SplashFountCount++;
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN)  {
				SplashFountCount++;
			}
			break;
		case 2:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN)  {
				SplashFountCount = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP1SF = 0;
		SplashFountCount = 0;
		return false;
	}
}

bool ModuleCombos::CheckSplashFountP2() {
	actual_frameP2SF++;
	if (actual_frameP2SF <= SPLASHFOUNT) {
		switch (SplashFountCount2)
		{
		case 0:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				SplashFountCount2++;
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				SplashFountCount2++;
			}
			break;
		case 2:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				SplashFountCount2 = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP2SF = 0;
		SplashFountCount2 = 0;
		return false;
	}
}

bool ModuleCombos::CheckPowerGraduationP1() {
	actual_frameP1PG++;
	if (actual_frameP1PG <= POWERGRADUATION) {
		switch (PowerGraditionCount)
		{
		case 0:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_IDLE) {
				HoldGP1++;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
				if (HoldGP1 > 10) {
					HoldGP1 = 0;
					PowerGraditionCount++;
				}
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
				if (HoldGP1 > 10) {
					HoldGP1 = 0;
					PowerGraditionCount++;
				}
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				PowerGraditionCount = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP1PG = 0;
		PowerGraditionCount = 0;
		return false;
	}
}

bool ModuleCombos::CheckPowerGraduationP2() {
	actual_frameP2PG++;
	if (actual_frameP2PG <= POWERGRADUATION) {
		switch (PowerGraditionCount2)
		{
		case 0:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_IDLE) {
				HoldGP2++;
			}
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
				if (HoldGP2 > 10) {
					HoldGP2 = 0;
					PowerGraditionCount2++;
				}
			}
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
				if (HoldGP2 > 10) {
					HoldGP2 = 0;
					PowerGraditionCount2++;
				}
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				PowerGraditionCount2 = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP2PG = 0;
		PowerGraditionCount2 = 0;
		return false;
	}
}*/