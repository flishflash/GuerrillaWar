#include "ModuleDestroy.h"

#include "Application.h"

#include "Destroy.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#define SPAWN_MARGIN 200


	ModuleDestroy::ModuleDestroy(bool startEnabled) : Module(startEnabled)
	{
		for (uint i = 0; i < MAX_DESTROY; ++i)
			destroy[i] = nullptr;
	}

	ModuleDestroy::~ModuleDestroy()
	{

	}

	bool ModuleDestroy::Start()
	{
		texture = App->textures->Load("Assets/Sprites/EnemiesGW.png");
		//enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

		return true;
	}


	Update_Status ModuleDestroy::PreUpdate()
	{
		// Remove all enemies scheduled for deletion
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] != nullptr && destroy[i]->pendingToDelete)
			{
				delete destroy[i];
				destroy[i] = nullptr;
			}
		}

		return Update_Status::UPDATE_CONTINUE;
	}

	Update_Status ModuleDestroy::Update()
	{
		HandleDestroySpawn();

		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] != nullptr)
				destroy[i]->Update();
		}

		HandleDestroyDespawn();

		return Update_Status::UPDATE_CONTINUE;
	}

	Update_Status ModuleDestroy::PostUpdate()
	{
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] != nullptr)
				destroy[i]->Draw();
		}

		return Update_Status::UPDATE_CONTINUE;
	}

	// Called before quitting
	bool ModuleDestroy::CleanUp()
	{
		LOG("Freeing all enemies");

		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] != nullptr)
			{
				delete destroy[i];
				destroy[i] = nullptr;
			}
		}

		return true;
	}

	bool ModuleDestroy::AddDestroy(Destroy_Type type, int x, int y)
	{
		bool ret = false;

		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (spawnQueue[i].type == Destroy_Type::NO_TYPE)
			{
				spawnQueue[i].type = type;
				spawnQueue[i].x = x;
				spawnQueue[i].y = y;
				ret = true;
				break;
			}
		}

		return ret;
	}

	void ModuleDestroy::HandleDestroySpawn()
	{
		// Iterate all the enemies queue
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (spawnQueue[i].type != Destroy_Type::NO_TYPE)
			{
				// Spawn a new enemy if the screen has reached a spawn position
				if (spawnQueue[i].x * SCREEN_SIZE < App->player->cameraGameplay.x + (App->player->cameraGameplay.w * SCREEN_SIZE) + SPAWN_MARGIN)
				{
					LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

					SpawnDestroy(spawnQueue[i]);
					spawnQueue[i].type = Destroy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
				}
			}
		}
	}

	void ModuleDestroy::HandleDestroyDespawn()
	{
		// Iterate existing enemies
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] != nullptr)
			{
				// Delete the enemy when it has reached the end of the screen
				if (destroy[i]->positiondestroy.x * SCREEN_SIZE < (App->player->cameraGameplay.x) - SPAWN_MARGIN)
				{
					LOG("DeSpawning enemy at %d", destroy[i]->positiondestroy.x * SCREEN_SIZE);

					destroy[i]->SetToDelete();
				}
			}
		}
	}

	void ModuleDestroy::SpawnDestroy(const DestroySpawnpoint& info)
	{
		// Find an empty slot in the enemies array
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] == nullptr)
			{
				switch (info.type)
				{
				case Destroy_Type::ROCK:
					//destroy[i] = new greenSoldier(info.x, info.y);
					break;
				case Destroy_Type::FENCE:
					//destroy[i] = new greenSoldiergranada(info.x, info.y);
					break;
				}
				destroy[i]->texture = texture;
				destroy[i]->destroyedFx = destroyDestroyedFx;
				break;
			}
		}
	}

	void ModuleDestroy::OnCollision(Collider* c1, Collider* c2)
	{
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroy[i] != nullptr && destroy[i]->GetCollider() == c1)
			{
				destroy[i]->OnCollision(c2); //Notify the enemy of a collision
				App->player->score += 100;
				break;
			}
		}
	}

