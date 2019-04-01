#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

class ModuleAudio : public Module
{
public:

	ModuleAudio();

	// Destructor
	~ModuleAudio();

	// Called before starting
	bool Init();
	update_status Update();
	// Called before quitting
	bool CleanUp();

public:

};

#endif // __ModuleAudio_H__