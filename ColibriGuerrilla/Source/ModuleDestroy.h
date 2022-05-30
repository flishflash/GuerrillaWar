#ifndef __MODULE_DESTROY_H__
#define __MODULE_DESTROY_H__

#include "Module.h"

#define MAX_DESTROY 200

enum class Destroy_Type
{
	NO_TYPE,
	ROCK,
	FENCE,
};

struct DestroySpawnpoint
{
	Destroy_Type type = Destroy_Type::NO_TYPE;
	int x, y;
};

class Destroy;
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
	bool AddDestroy(Destroy_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleDestroySpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleDestroyDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnDestroy(const DestroySpawnpoint& info);

private:
	// A queue with all spawn points information
	DestroySpawnpoint spawnQueue[MAX_DESTROY];

	// All spawned enemies in the scene
	Destroy* destroy[MAX_DESTROY] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	int destroyDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__