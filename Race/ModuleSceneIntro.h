#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include <vector>
using namespace std;

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateCube(vec3 size, vec3 position, vec3 rotation, Color color);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;


	PhysBody3D* sensor_cube;
	PhysBody3D* sensor_cube2;
	PhysBody3D* sensor_cube3;

	Cylinder coin[10];
	PhysBody3D* coin_body[10];
	int coinCount = 0;

	Cube platform;

	PhysBody3D* physBody;

	vector<Cube> cubes;

	float angle = 0.0f;

	Cube* rotatingCube[2];
	PhysBody3D* rotatingCubeBody[2];
	float rotationAngle[2];

	Cube* sandCube;
	PhysBody3D* sandBody;
};
