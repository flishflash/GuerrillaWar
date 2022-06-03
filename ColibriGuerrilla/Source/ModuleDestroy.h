#ifndef __MODULE_DESTROY_H__
#define __MODULE_DESTROY_H__

#include "Module.h"
#include "Collider.h"
#include "Globals.h"
#include "Destroy.h"

#define MAX_DESTROY 200


struct Collider;
struct SDL_Texture;

class ModuleDestroy : public Module
{
public:
	// Constructor
	ModuleDestroy(bool startEnabled);

	// Destructor
	~ModuleDestroy();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	Destroy* AddDestroy(const Destroy& destroy, int x, int y, Collider::Type colliderType);

public:

	Destroy rock;
	Destroy rockL;
	Destroy fence;
	Destroy fence2;
	Destroy trinch;

private:

	// All spawned enemies in the scene
	Destroy* destroys[MAX_DESTROY] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

#endif // __MODULE_ENEMIES_H__