#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	App->audio->Init();
	engine0 = App->audio->LoadFx("Assets/engine0_fx.wav");
	engine1 = App->audio->LoadFx("Assets/engine1_fx.wav");
	engine2 = App->audio->LoadFx("Assets/engine2_fx.wav");
	engine3 = App->audio->LoadFx("Assets/engine3_fx.wav");
	engine4 = App->audio->LoadFx("Assets/engine4_fx.wav");
	engine5 = App->audio->LoadFx("Assets/engine5_fx.wav");
	engine6 = App->audio->LoadFx("Assets/engine6_fx.wav");
	nitro = App->audio->LoadFx("Assets/nitro_fx.wav");
	coinFx = App->audio->LoadFx("Assets/collectcoin_fx.wav");
	
	detectionCube = new Cube();
	detectionCube->size = {4, 2, 4};
	detectionCubeBody = App->physics->AddBody(*detectionCube, 0.0f);
	detectionCube->color = Color(1,0,0,0.1f);
	detectionCubeBody->SetAsSensor(true);

	killercountdown = 60.0f;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->audio->CleanUp();
	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{

	btVector3 position = vehicle[myCar]->vehicle->getRigidBody()->getWorldTransform().getOrigin();
	detectionCube->SetPos(position.x(), position.y()+0.3f, position.z());
	detectionCubeBody->SetPos(position.x(), position.y() + 0.3f, position.z());
	static int lastSpeedRange = -1;

	myCar = App->network->clientIndex;
	currentCarSpeed = vehicle[myCar]->GetKmh();

	if (position.x() > -92 && position.x() < -78 && position.z() > -2 && checkpoint3 == true && win == false) {
		App->scene_intro->winF();
	}

	if (position.x() > 175 && position.x() < 189 && position.x() > 20) {
		checkpoint1 = true;
		LOG("CHECK")
	}


	if (position.z() > 0 && position.z() < 14 && position.z() > -7 && checkpoint1 == true) {
		checkpoint2 = true;
		LOG("CHECK")
	}

	if (position.z() > -69 && position.z() < -55 && position.x() < 0 && checkpoint2 == true) {
		checkpoint3 = true;
		LOG("CHECK")
	}

// timer 
	if (killercountdown > -1 && App->scene_intro->gameStarted) {
		killercountdown -= dt;
	}
	else if (killercountdown < 0)
	{
		SDL_Quit();
	}

// Car engine dinamic sound
    if (currentCarSpeed < 5)
    {
        currentSpeedRange = 0;
    }
    else if (currentCarSpeed < 10)
    {
        currentSpeedRange = 1;
    }
    else if (currentCarSpeed < 20)
    {
        currentSpeedRange = 2;
    }
    else if (currentCarSpeed < 40)
    {
        currentSpeedRange = 3;
    }
    else if (currentCarSpeed < 60)
    {
        currentSpeedRange = 4;
    }
    else if (currentCarSpeed < 80)
    {
        currentSpeedRange = 5;
    }
    else
    {
        currentSpeedRange = 6;
    }

// Car engine dinamic sound
    if (currentSpeedRange != lastSpeedRange)
    {
        Mix_HaltChannel(-1);

        switch (currentSpeedRange)
        {
            case 0:
                App->audio->PlayFx(engine0, -1, 0);
                break;
            case 1:
                App->audio->PlayFx(engine1, -1, 1);
                break;
            case 2:
                App->audio->PlayFx(engine2, -1, 2);
                break;
            case 3:
                App->audio->PlayFx(engine3, -1, 3);
                break;
            case 4:
                App->audio->PlayFx(engine4, -1, 4);
                break;
            case 5:
                App->audio->PlayFx(engine5, -1, 5);
                break;
            case 6:
                App->audio->PlayFx(engine6, -1, 6);
                break;
        }

        lastSpeedRange = currentSpeedRange;
    }
//Create car
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && carCount < 2)
	{
		CreateCar(carCount);
	}
	
	if (App->network->gameStarted)
	{
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				turn[currentCar] = acceleration[currentCar] = brake[currentCar] = 0.0f;

				if (up[currentCar])
				{
					acceleration[currentCar] = MAX_ACCELERATION;
				}

				if (left[currentCar])
				{
					if (turn[currentCar] < TURN_DEGREES)
						turn[currentCar] += TURN_DEGREES;
				}

				if (right[currentCar])
				{
					if (turn[currentCar] > -TURN_DEGREES)
						turn[currentCar] -= TURN_DEGREES;
				}

				if (reverse[currentCar])
				{
					acceleration[currentCar] = -MAX_ACCELERATION;
				}

				if (down[currentCar])
				{
					brake[currentCar] = BRAKE_POWER;
				}

				if (impulseActivated[currentCar])
				{
					vehicle[currentCar]->ApplyEngineForce(3000.0f);
					impulseActivated[currentCar] = false;
				}
				else vehicle[currentCar]->ApplyEngineForce(acceleration[currentCar]);
				vehicle[currentCar]->Turn(turn[currentCar]);
				vehicle[currentCar]->Brake(brake[currentCar]);

				vehicle[currentCar]->Render();
			}
		}

		turn[myCar] = acceleration[myCar] = brake[myCar] = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_W) != KEY_REPEAT && currentCarSpeed > 0)
		{
			acceleration[myCar] = - (currentCarSpeed* vehicle[myCar]->info.frictionSlip);
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			if (touchingSand) {
				maxSpeed = 40;
			}
			else
			{
				maxSpeed = MAX_SPEED;
			}


			if(vehicle[myCar]->GetKmh() < maxSpeed)	acceleration[myCar] = MAX_ACCELERATION;
			up[myCar] = true;
			if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && !touchingSand) {
				if (currentCarSpeed < MAX_TURBO_SPEED) {
					acceleration[myCar] = MAX_ACCELERATION * 6;
					if (turboFxPlayed == false) {
						App->audio->PlayFx(nitro);
						turboFxPlayed = true;
					}
					else
					{
						turboFxPlayed = false;
					}
				}
			}

		}
		else up[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (turn[myCar] < TURN_DEGREES)
				turn[myCar] += TURN_DEGREES;
			left[myCar] = true;
		}
		else left[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (turn[myCar] > -TURN_DEGREES)
				turn[myCar] -= TURN_DEGREES;
			right[myCar] = true;
		}
		else right[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			acceleration[myCar] = -MAX_ACCELERATION;
			reverse[myCar] = true;
		}
		else up[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			brake[myCar] = BRAKE_POWER;
			down[myCar] = true;
		}
		else down[myCar] = false;

		if (impulseActivated[myCar])
		{
			vehicle[myCar]->ApplyEngineForce(3000.0f);
			impulseActivated[myCar] = false;
		}
		else vehicle[myCar]->ApplyEngineForce(acceleration[myCar]);
		vehicle[myCar]->Turn(turn[myCar]);
		vehicle[myCar]->Brake(brake[myCar]);
// Car mass change
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
		{
			vehicle[myCar]->info.mass -= 1;
		}
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
		{
			vehicle[myCar]->info.mass += 1;
		}
// Car friction change
		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
		{
			vehicle[myCar]->info.frictionSlip = 100;
			for (int i = 0; i < vehicle[myCar]->vehicle->getNumWheels(); i++)
       	 	{
            vehicle[myCar]->vehicle->getWheelInfo(i).m_frictionSlip = 5000;
        	}
		}
		else
		{
			vehicle[myCar]->info.frictionSlip = 5;
			for (int i = 0; i < vehicle[myCar]->vehicle->getNumWheels(); i++)
       	 	{
            vehicle[myCar]->vehicle->getWheelInfo(i).m_frictionSlip = 50.5;
        	}
		}
//Gravity modifier
		if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
		{
			App->physics->ModifyGravity({ 0, -5, 0 });
		}
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		{
			App->physics->ModifyGravity({ 0, +5, 0 });
		}


		if (touchingSand) {
			vehicle[myCar]->info.frictionSlip = 100;
			if (currentCarSpeed >= 39) vehicle[myCar]->ApplyEngineForce(-1000.0f);
		}
		else vehicle[myCar]->info.frictionSlip = 10;

		vehicle[myCar]->Render();
		//detectionCube->Render();

		char title[120];
		sprintf_s(title, "%.1f Km/h | %.1f Mass | %.1f Friction | %i TouchingSand | %.1f Gravity | %i Coins | %.2f Cronometro | %i GS %i CK %i GF", vehicle[myCar]->GetKmh(), vehicle[myCar]->info.mass, vehicle[myCar]->info.frictionSlip, touchingSand, App->physics->GetGravity().y,App->scene_intro->coinCount, killercountdown, App->scene_intro->gameStarted, App->scene_intro->firstCheckpoint, App->scene_intro->gameFinished);
		App->window->SetTitle(title);
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == App->scene_intro->sensor_cube2 || body2 == App->scene_intro->sensor_cube2) {
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar]) touchingSand = true;
			}
			else touchingSand = true;
		}
	}
	//Collisión para fixear la arena + checkpoint
	if (body1 == App->scene_intro->sensor_cube3 || body2 == App->scene_intro->sensor_cube3) {
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar])
				{
					touchingSand = false;
					App->scene_intro->firstCheckpoint = true;
				}
			}
			else {
				touchingSand = false;
				App->scene_intro->firstCheckpoint = true;
			}
		}
	}

	//colision monedas
	for (int i = 0; i < 10; i++) {
		if (!coinCollected[i] && (body1 == App->scene_intro->coin_body[i] || body2 == App->scene_intro->coin_body[i])) {
			for (int currentCar = 0; currentCar < carCount; currentCar++)
			{
				if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar]) {
					App->scene_intro->coin_body[i]->SetPos(0, -100, 0);
					App->scene_intro->coin[i].SetPos(0, -100, 0);
					App->scene_intro->coinCount+=1;
					coinCollected[i] = true;
					App->audio->PlayFx(coinFx);
					killercountdown += 10.0f;
				}
			}
		}
	}
	//Colisión si te caes del mapa pierdes
	if (body1 == App->scene_intro->loseBody || body2 == App->scene_intro->loseBody) {
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar]) {
				SDL_Quit();
			}
		}
	}
	//Colisión empezar partida
	if (body1 == App->scene_intro->sensor_meta_cube || body2 == App->scene_intro->sensor_meta_cube) {
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar])
				{
					if (!App->scene_intro->gameStarted) {
						App->scene_intro->gameStarted = true;
					}
					else if (App->scene_intro->gameStarted) {
						App->scene_intro->gameFinished = true;
					}
				}
			}
			else {
				if (!App->scene_intro->gameStarted) {
					App->scene_intro->gameStarted = true;
				}
				else if (App->scene_intro->gameStarted && App->scene_intro->firstCheckpoint) {
					App->scene_intro->gameFinished = true;
				}
			}
		}
	}


	if (body1 == App->scene_intro->sensor_cube || body2 == App->scene_intro->sensor_cube)
	{
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar]) impulseActivated[currentCar] = true;
			}
			else impulseActivated[myCar] = true;
		}
	}
}

void ModulePlayer::CreateCar(int carIndex)
{
	carCount++;

	turn[carIndex] = acceleration[carIndex] = brake[carIndex] = 0.0f;

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1.5, 4);
	car.chassis_offset.Set(0, 1, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;
	if (carIndex == 0) car.wheelColor = Blue;
	else car.wheelColor = Red;


	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.7f;
	float half_length = car.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle[carIndex] = App->physics->AddVehicle(car);
	vehicle[carIndex]->collision_listeners.add(this); // Add this module as listener to callbacks from vehicle
	vehicle[carIndex]->SetPos((carIndex * 5) - 86, 1, -10);
}