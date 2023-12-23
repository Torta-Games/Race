#include "Globals.h"
#include "Application.h"
#include "ModuleNetwork.h"

ModuleNetwork::ModuleNetwork(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleNetwork::~ModuleNetwork()
{}

bool ModuleNetwork::Start()
{
	LOG("Loading Network");

	SDLNet_Init();

	return true;
}

bool ModuleNetwork::CleanUp()
{
	LOG("Unloading Network");

	return true;
}

update_status ModuleNetwork::Update(float dt)
{
	
	if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
		CreateServer();
	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) {
		printf("Enter the host IP: ");
		scanf("%s", host);
		CreateClient();
	}

	return UPDATE_CONTINUE;
}

void ModuleNetwork::CreateServer()
{
	SDLNet_ResolveHost(&ip, NULL, 1234);

	server = SDLNet_TCP_Open(&ip);

	if (server != nullptr) host = SDLNet_ResolveIP(&ip);

	printf("Server created at %s\n", host);
	
}

void ModuleNetwork::CreateClient()
{
	SDLNet_ResolveHost(&ip, host, 1234);

	client = SDLNet_TCP_Open(&ip);

	if (SDLNet_ResolveHost(&ip, host, 0) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	}
	else {
		char ipString[16];
		const char* ipStringResult = SDLNet_ResolveIP(&ip);
		if (ipStringResult) {
			printf("IP: %s\n", ipStringResult);
		}
	}
}
