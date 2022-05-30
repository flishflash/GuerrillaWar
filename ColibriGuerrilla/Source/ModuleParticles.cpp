#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/shoots.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;


	//Normal bullet anims
	bulletN.anim.PushBack({ 7, 180, 7, 10 });
	bulletN.anim.PushBack({ 23, 179, 7, 11 });
	bulletN.speed.y = -5;
	bulletN.lifetime = 180;
	bulletN.anim.speed = 0.2f;

	bulletNE.anim.PushBack({ 36, 181, 8, 11 });
	bulletNE.anim.PushBack({ 52, 181, 8, 11 });
	bulletNE.speed.y = -3 ;
	bulletNE.speed.x = 3 ;
	bulletNE.lifetime = 180;
	bulletNE.anim.speed = 0.2f;

	bulletE.anim.PushBack({ 67, 183, 9, 9 });
	bulletE.anim.PushBack({ 84, 183, 9, 9 });
	bulletE.speed.x = 5;
	bulletE.lifetime = 180;
	bulletE.anim.speed = 0.2f;

	bulletSE.anim.PushBack({ 99, 180, 8, 12 });
	bulletSE.anim.PushBack({ 115, 180, 8, 12 });
	bulletSE.speed.x = 3 ;
	bulletSE.speed.y = 3 ;
	bulletSE.lifetime = 180;
	bulletSE.anim.speed = 0.2f;

	bulletS.anim.PushBack({ 134, 179, 7, 12 });
	bulletS.anim.PushBack({ 150, 180, 7, 11 });
	bulletS.speed.y = 5;
	bulletS.lifetime = 180;
	bulletS.anim.speed = 0.2f;

	bulletSW.anim.PushBack({ 165, 180, 7, 12 });
	bulletSW.anim.PushBack({ 181, 180, 7, 12 });
	bulletSW.speed.x = -3 ;
	bulletSW.speed.y = 3 ;
	bulletSW.lifetime = 180;
	bulletSW.anim.speed = 0.2f;

	bulletW.anim.PushBack({ 189, 182, 9, 8 });
	bulletW.anim.PushBack({ 195, 182, 10, 8 });
	bulletW.speed.x = -5;
	bulletW.lifetime = 180;
	bulletW.anim.speed = 0.2f;

	bulletNW.anim.PushBack({ 203, 181, 8, 11 });
	bulletNW.anim.PushBack({ 212, 181, 8, 11 });
	bulletNW.speed.x = -3 ;
	bulletNW.speed.y = -3 ;
	bulletNW.lifetime = 180;
	bulletNW.anim.speed = 0.2f;

	//Enemy bullets
	enemyBullet.anim.PushBack({194, 64, 12, 17});
	enemyBullet.anim.PushBack({212, 65, 11, 16});
	enemyBullet.speed.y = 5;
	enemyBullet.lifetime = 100;
	enemyBullet.anim.speed = 0.1f;	
	
	enemyBulletL.anim.PushBack({194, 64, 12, 17});
	enemyBulletL.anim.PushBack({212, 65, 11, 16});
	enemyBulletL.speed.x = -2;
	enemyBulletL.speed.y = 3;
	enemyBulletL.lifetime = 100;
	enemyBulletL.anim.speed = 0.1f;	
	
	enemyBulletR.anim.PushBack({194, 64, 12, 17});
	enemyBulletR.anim.PushBack({212, 65, 11, 16});
	enemyBulletR.speed.x = 2;
	enemyBulletR.speed.y = 3;
	enemyBulletR.lifetime = 100;
	enemyBulletR.anim.speed = 0.1f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}