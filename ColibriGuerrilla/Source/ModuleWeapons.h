#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleWeapons :public Module
{
public:
	// Constructor
	ModuleWeapons(bool startEnabled);

	// Destructor
	~ModuleWeapons();

	bool Start() override;

	// Called at the middle of the application loop
	Update_Status Update() override;

	// Called at the end of the application loop
	Update_Status PostUpdate() override;

public:
	// Position of the weapon in the map
	iPoint positionWeapon;

	// The weapon spritesheet loaded into an SDL_Texture
	SDL_Texture* textureW = nullptr;


	Animation* WcurrentAnimation = nullptr;

	//Animations of the weapon for each direction
	Animation northWeapon;
	Animation southWeapon;
	Animation eastWeapon;
	Animation westWeapon;
	Animation northEastWeapon;
	Animation northWestWeapon;
	Animation southEastWeapon;
	Animation southWestWeapon;
	int direction;

	bool destroyed = false;
};

