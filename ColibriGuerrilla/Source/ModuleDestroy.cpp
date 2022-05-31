#include "ModuleDestroy.h"

#include "Application.h"

#include "Destroy.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#define SPAWN_MARGIN 200


	ModuleDestroy::ModuleDestroy(bool startEnabled) : Module(startEnabled)
	{
		for (uint i = 0; i < MAX_DESTROY; ++i)
			destroys[i] = nullptr;
	}

	ModuleDestroy::~ModuleDestroy()
	{

	}

	bool ModuleDestroy::Start()
	{
		texture = App->textures->Load("Assets/Sprites/Guerrilla_Objects.png");
		//enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

		return true;
	}


	Update_Status ModuleDestroy::PreUpdate()
	{
		// Remove all enemies scheduled for deletion
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroys[i] != nullptr && destroys[i]->pendingToDelete)
			{
				delete destroys[i];
				destroys[i] = nullptr;
			}
		}

		return Update_Status::UPDATE_CONTINUE;
	}

	Update_Status ModuleDestroy::Update()
	{

		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroys[i] != nullptr)
				destroys[i]->Update();
		}

		return Update_Status::UPDATE_CONTINUE;
	}

	Update_Status ModuleDestroy::PostUpdate()
	{
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			Destroy* destroy = destroys[i];

			if (destroys[i] != nullptr)
				App->render->Blit(texture, destroy->position.x, destroy->position.y, &(destroy->anim.GetCurrentFrame()));
		}

		return Update_Status::UPDATE_CONTINUE;
	}

	// Called before quitting
	bool ModuleDestroy::CleanUp()
	{
		LOG("Freeing all enemies");

		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroys[i] != nullptr)
			{
				delete destroys[i];
				destroys[i] = nullptr;
			}
		}

		return true;
	}

	Destroy* ModuleDestroy::AddDestroy(const Destroy& destroy, int x, int y, Collider::Type colliderType)
	{
		Destroy* newDestroy = nullptr;

		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			if (destroys[i] == nullptr)
			{
				newDestroy = new Destroy(destroy);
				newDestroy->position.x = x;						// so when frameCount reaches 0 the particle will be activated
				newDestroy->position.y = y;

				//Adding the particle's collider
				if (colliderType != Collider::Type::NONE)
					newDestroy->collider = App->collisions->AddCollider(newDestroy->anim.GetCurrentFrame(), colliderType, this);

				destroys[i] = newDestroy;
				break;
			}
		}

		return newDestroy;
	}

	void ModuleDestroy::OnCollision(Collider* c1, Collider* c2)
	{
		for (uint i = 0; i < MAX_DESTROY; ++i)
		{
			// Always destroy particles that collide
			if (destroys[i] != nullptr && destroys[i]->collider == c1)
			{
				destroys[i]->pendingToDelete = true;
				destroys[i]->collider->pendingToDelete = true;
				break;
			}
		}
	}

