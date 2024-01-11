#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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

	App->camera->Move(vec3(0.0f, 5.0f, -5.0f));
	App->camera->LookAt(vec3(0, 0, 15));

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

	CreateCube(vec3(-10.76f, 0.42f, 100.00f), vec3(-0.00f, 0.00f, 0.00f), vec3(0.00f, 3.14f, -0.00f), Color(0.80f, 0.80f, 0.80f));

	CreateCube(vec3(-10.76f, 0.42f, 100.00f), vec3(-0.00f, 21.50f, 196.63f), vec3(0.22f, 3.14f, -0.00f), Color(0.80f, 0.80f, 0.80f));


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	angle++;
	coin.SetRotation(angle, vec3(0, 1, 0));
	coin.Render();

	platform.Render();

	for ( auto& cube : cubes)
	{
		cube.Render();
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
	platform.SetRotation(rotation.x, vec3(1, 0, 0));
	platform.SetRotation(rotation.y, vec3(0, 1, 0));
	platform.SetRotation(rotation.z, vec3(0, 0, 1));
	platform.color = color;

	auto physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;

	cubes.push_back(platform);
}