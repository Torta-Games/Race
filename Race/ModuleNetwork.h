#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL2_net/include/SDL_net.h"
#pragma comment(lib, "SDL2_net/lib/x86/SDL2_net.lib")

class ModuleNetwork : public Module
{
public:
	ModuleNetwork(Application* app, bool start_enabled = true);
	virtual ~ModuleNetwork();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateServer();
	void CreateClient();

public:
	TCPsocket server;
	TCPsocket client;
	IPaddress ip;
	const char* host;
};