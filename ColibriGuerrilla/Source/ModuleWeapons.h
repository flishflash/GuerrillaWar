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
	iPoint spritep;
	int speed = 1;

	int options;
	// The weapon spritesheet loaded into an SDL_Texture
	SDL_Texture* textureW = nullptr;


	Animation* WcurrentAnimation = nullptr;

	//Animations of the weapon for each direction
	Animation idleAnim;
	Animation northAnim;
	Animation southAnim;
	Animation eastAnim;
	Animation westAnim;
	Animation northEastAnim;
	Animation northWestAnim;
	Animation southEastAnim;
	Animation southWestAnim;
	Animation downAnim;
	Animation WidleAnim;
	Animation WnorthAnim;
	Animation WsouthAnim;
	Animation WeastAnim;
	Animation WwestAnim;
	Animation WnorthEastAnim;
	Animation WnorthWestAnim;
	Animation WsouthEastAnim;
	Animation WsouthWestAnim;
	Animation WdownAnim;

	Animation TidleAnim;
	Animation TnorthAnim;
	Animation TsouthAnim;
	Animation TeastAnim;
	Animation TwestAnim;
	Animation TnorthEastAnim;
	Animation TnorthWestAnim;
	Animation TsouthEastAnim;
	Animation TsouthWestAnim;
	Animation TdownAnim;
	Animation TWidleAnim;
	Animation TWnorthAnim;
	Animation TWsouthAnim;
	Animation TWeastAnim;
	Animation TWwestAnim;
	Animation TWnorthEastAnim;
	Animation TWnorthWestAnim;
	Animation TWsouthEastAnim;
	Animation TWsouthWestAnim;
	Animation TWdownAnim;
	int direction;

	bool destroyed = false;
};

