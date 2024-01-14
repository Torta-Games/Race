#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->Start();
	App->textures->Start();

	App->camera->Move(vec3(0.0f, 5.0f, -5.0f));
	App->camera->LookAt(vec3(0, 0, 15));
	
	winTex = App->textures->Load("Assets/YouWon.png");

	// Create sensor cube (will trigger with car)
	sensor_cube = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(0, 3, 0);

	coin = Cylinder(1.0f, 0.5f);
	coin.SetPos(0, 3, 30);
	coin.color = Yellow;

	//platform = Cube(100, 0.4, 100);
	//platform.SetPos(0, 1, -86.3288);
	//platform.SetRotation(45.0f,vec3(1.0f, 0.0f, 0.0f));
	//platform.color = White;

	physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;
	
	CreateCube(vec3(17.05f, 2.00f, 71.41f), vec3(182.33f, -0.45f, 13.25f), vec3(-0.00f, 0.00f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 250.44f), vec3(48.59f, -0.45f, 57.48f), vec3(-0.00f, 1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 102.50f), vec3(-85.15f, -0.45f, -2.30f), vec3(-0.00f, 0.00f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 92.22f), vec3(-30.52f, -0.45f, -62.07f), vec3(-0.00f, 1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 1.86f, 17.44f), vec3(17.38f, 1.89f, -62.07f), vec3(-0.38f, 1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 1.86f, 17.44f), vec3(61.47f, 1.89f, -62.07f), vec3(-0.38f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 65.11f), vec3(99.59f, -0.45f, -62.07f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 85.20f), vec3(89.53f, -0.45f, -99.70f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 20.58f), vec3(140.66f, -0.45f, -80.89f), vec3(-0.00f, 3.14f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 90.06f), vec3(38.41f, -0.45f, -46.15f), vec3(-0.00f, 3.14f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 98.24f), vec3(124.69f, -0.45f, -30.98f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.36f, 38.92f), vec3(69.14f, 3.27f, -30.98f), vec3(-0.38f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.36f, 38.92f), vec3(1.93f, 3.26f, -30.98f), vec3(-0.38f, 1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 33.01f), vec3(-19.92f, -0.45f, -30.97f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 49.27f), vec3(5.25f, -0.45f, 7.41f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 21.34f), vec3(-27.90f, -0.45f, -11.78f), vec3(-0.00f, 3.14f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.30f, 31.97f), vec3(35.53f, 10.45f, -30.98f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(182.33f, -0.45f, -30.98f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(182.33f, -0.45f, 57.48f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(-85.15f, -0.45f, 57.48f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(-85.15f, -0.45f, -62.07f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(140.66f, -0.45f, -62.07f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(140.66f, -0.45f, -99.70f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(38.41f, -0.45f, -99.70f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(38.41f, -0.45f, 7.41f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(17.05f, 2.00f, 17.05f), vec3(-27.90f, -0.45f, 7.41f), vec3(-0.00f, -1.57f, -0.00f), Color(0.19f, 0.18f, 0.19f));
	CreateCube(vec3(332.65f, 1.08f, 449.65f), vec3(37.22f, -1.99f, -21.03f), vec3(-0.00f, 1.57f, -0.00f), Color(0.02f, 0.80f, 0.00f));
	CreateCube(vec3(1.61f, 8.66f, 250.44f), vec3(48.59f, -3.00f, 66.80f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 71.42f), vec3(191.59f, -3.00f, 13.25f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(182.26f, -0.42f, 66.81f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(191.59f, -0.42f, 57.48f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(149.99f, -0.42f, -62.07f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(140.66f, -0.42f, -52.74f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(47.74f, -0.42f, 7.41f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(38.41f, -0.42f, 16.74f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(-37.23f, -0.42f, 7.41f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(-27.90f, -0.42f, 16.74f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(-85.15f, -0.42f, 66.81f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(-94.48f, -0.42f, 57.48f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(149.99f, -0.42f, -99.70f), vec3(-0.00f, 3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(140.66f, -0.42f, -109.03f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(182.33f, -0.42f, -40.31f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(191.66f, -0.42f, -30.98f), vec3(-0.00f, 3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(-85.15f, -0.42f, -71.40f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(-94.48f, -0.42f, -62.07f), vec3(-0.00f, -3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 21.58f), vec3(-37.23f, -0.42f, -28.72f), vec3(-0.00f, -3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 35.70f), vec3(-18.58f, -0.42f, -40.30f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(38.41f, -0.42f, -109.03f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.05f), vec3(29.08f, -0.42f, -99.70f), vec3(-0.00f, -3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 250.44f), vec3(48.59f, -3.00f, 66.80f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 85.20f), vec3(89.53f, -3.00f, -109.04f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 85.20f), vec3(89.53f, -3.00f, -90.32f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 98.24f), vec3(124.69f, -3.00f, -21.77f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 98.24f), vec3(124.69f, -3.00f, -40.31f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 250.44f), vec3(48.59f, -3.00f, 48.13f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 68.50f), vec3(173.00f, -3.00f, 13.25f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 102.50f), vec3(-94.48f, -3.00f, -2.30f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 102.50f), vec3(-75.83f, -3.00f, -2.30f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 92.22f), vec3(-30.52f, -3.00f, -71.41f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 92.22f), vec3(-30.52f, -3.00f, -52.74f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 67.78f), vec3(98.24f, -3.00f, -71.41f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 67.78f), vec3(98.24f, -3.00f, -52.75f), vec3(-0.00f, 1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 20.60f), vec3(149.99f, -3.00f, -80.89f), vec3(-0.00f, 3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.27f), vec3(131.33f, -3.00f, -80.86f), vec3(-0.00f, 3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 49.27f), vec3(5.25f, -3.00f, 16.67f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 49.27f), vec3(5.25f, -3.00f, -1.90f), vec3(-0.00f, -1.57f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 90.06f), vec3(47.74f, -3.00f, -46.15f), vec3(-0.00f, 3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 90.06f), vec3(29.08f, -3.00f, -46.15f), vec3(-0.00f, 3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(1.61f, 8.66f, 17.03f), vec3(-37.23f, -1.69f, -9.51f), vec3(-0.00f, -3.14f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(2.34f, 25.70f, 2.34f), vec3(-73.27f, 5.19f, -2.30f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(2.34f, 25.70f, 2.34f), vec3(-97.14f, 5.19f, -2.30f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 0.99f, 0.96f));
	CreateCube(vec3(21.52f, 7.35f, 2.34f), vec3(-85.20f, 13.55f, -2.30f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.01f, 0.00f));
	CreateCube(vec3(0.90f, 4.21f, 0.65f), vec3(-77.72f, 13.86f, -3.59f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 1.68f, 0.60f), vec3(-79.02f, 15.54f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 0.84f, 0.60f), vec3(-80.28f, 14.70f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 1.68f, 0.60f), vec3(-79.02f, 13.85f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 0.84f, 0.60f), vec3(-79.44f, 13.01f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 0.84f, 0.60f), vec3(-80.28f, 12.17f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.90f, 3.37f, 0.65f), vec3(-82.22f, 13.44f, -3.59f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(17.29f, 0.04f, 1.41f), vec3(-85.20f, 0.59f, -2.32f), vec3(-3.14f, 0.00f, -0.00f), Color(0.82f, 0.01f, 0.00f));
	CreateCube(vec3(0.90f, 3.37f, 0.65f), vec3(-84.81f, 13.44f, -3.59f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 1.68f, 0.60f), vec3(-83.52f, 15.54f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 1.68f, 0.60f), vec3(-83.51f, 13.85f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 2.52f, 0.60f), vec3(-88.27f, 15.54f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 2.52f, 0.60f), vec3(-88.27f, 12.17f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 2.52f, 0.60f), vec3(-86.59f, 13.85f, -3.59f), vec3(0.00f, -0.00f, 3.14f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.90f, 4.21f, 0.65f), vec3(-90.97f, 13.86f, -3.59f), vec3(-0.00f, 0.00f, -0.00f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 2.52f, 0.60f), vec3(-92.68f, 15.54f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 1.68f, 0.60f), vec3(-92.26f, 13.85f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));
	CreateCube(vec3(0.84f, 2.52f, 0.60f), vec3(-92.68f, 12.17f, -3.59f), vec3(0.00f, 0.00f, 1.57f), Color(0.82f, 0.81f, 0.79f));

	rotatingCube[0] = new Cube(1.61f, 2.66f, 45.05f);  
	rotatingCube[0]->SetPos(-94.48f, 1.33, 66.80f); 
	rotatingCube[0]->color = Red;  
	rotationAngle[0] = 0.0f;

	rotatingCube[1] = new Cube(1.61f, 2.66f, 45.05f);  
	rotatingCube[1]->SetPos(191.58f, 1.33, 66.80f); 
	rotatingCube[1]->color = Red;  
	rotationAngle[1] = 0.0f;

	sandCube = new Cube(17.05f, 2.00f, 164.83f);
	sandCube->SetPos(48.59f, +0.24f, 57.48f);
	sandCube->color = Color(0.878f, 0.75f, 0.576f);
	sandCube->SetRotation(90,vec3(0, 1, 0));
	sandBody = App->physics->AddBody(*sandCube, 0.0f);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

void ModuleSceneIntro::winF() {
	App->renderer->Blit(winTex, 0, 0, NULL);
	App->player->win = true;
	LOG("CHECK");
	//SDL_Quit();
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
	
	for (int i = 0; i < 2; i++)
	{
		rotationAngle[i] -= dt*100;  
		rotatingCube[i]->SetRotation(rotationAngle[i], vec3(0, 1, 0));  
		rotatingCube[i]->Render(); 
	}

	sandCube->Render();

	angle++;
	coin.SetRotation(angle, vec3(0, 1, 0));
	coin.Render();
	platform.Render();

	for ( auto& cube : cubes)
	{
		cube.Render();
	}

	if (App->input->GetKey(SDL_SCANCODE_K))
	{
		App->renderer->Blit(winTex, 0, 0, NULL);

	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCube(vec3 size, vec3 position, vec3 rotation, Color color)
{
	Cube platform(size.x, size.y, size.z);
	platform.SetPos(position.x, position.y, position.z);


	btQuaternion quat;
	quat.setEulerZYX(rotation.z, rotation.y, rotation.x);

	float angle = quat.getAngle() * RADTODEG;
	btVector3 axis = quat.getAxis();

	platform.SetRotation(angle, vec3(axis.getX(), axis.getY(), axis.getZ()));

	platform.color = color;

	auto physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;

	cubes.push_back(platform);
}