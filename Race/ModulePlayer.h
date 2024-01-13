#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define MAX_TURBO_SPEED 150.0f
#define MAX_SPEED 100.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;
	bool CleanUp();

	void CreateCar(int carIndex);

public:

	PhysVehicle3D* vehicle[2];
	float turn[2];
	float acceleration[2];
	float brake[2];

	int carCount = 0;

	bool up[2] = { false, false };
	bool down[2] = { false, false };
	bool left[2] = { false, false };
	bool right[2] = { false, false };
	bool reverse[2] = { false, false };
	bool impulseActivated[2] = { false, false};
	int myCar = 0;
	int engine0, engine1, engine2, engine3, engine4, engine5, engine6;
	int nitro;
	bool turboFxPlayed = false;
	float currentCarSpeed;
	bool touchingSand = false;
	Cube* detectionCube;
	PhysBody3D* detectionCubeBody;
	btVector3* position;

};