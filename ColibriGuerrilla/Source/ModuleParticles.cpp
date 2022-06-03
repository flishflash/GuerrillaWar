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
	texture = App->textures->Load("Assets/Sprites/particles.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	//

	rescuedAnim.anim.PushBack({ 10, 258, 28, 56 });
	rescuedAnim.anim.PushBack({ 44, 258, 28, 56 });
	rescuedAnim.anim.PushBack({ 70, 258, 33, 58 });
	rescuedAnim.anim.loop = false;
	rescuedAnim.anim.speed = 0.1f;


	deathAnim.anim.PushBack({ 10, 322, 27, 58 });
	deathAnim.anim.PushBack({ 44, 322, 24, 55 });
	deathAnim.anim.PushBack({ 75, 322, 25, 54 });
	deathAnim.anim.PushBack({ 108, 322, 24, 46 });
	deathAnim.anim.loop = false;
	deathAnim.anim.speed = 0.1f;

	//soldier death
	deathgreenAnim.anim.PushBack({ 177, 326, 29, 49 });
	deathgreenAnim.anim.PushBack({ 211, 326, 29, 49 });
	deathgreenAnim.anim.PushBack({ 244, 326, 25, 46 });
	deathgreenAnim.anim.PushBack({ 276, 326, 25, 48 });
	deathgreenAnim.anim.PushBack({ 307, 326, 26, 48 });
	deathgreenAnim.anim.loop = false;
	deathgreenAnim.anim.speed = 0.1f;


	deathredAnim.anim.PushBack({ 177, 266, 29, 49 });
	deathredAnim.anim.PushBack({ 211, 266, 29, 49 });
	deathredAnim.anim.PushBack({ 244, 266, 25, 46 });
	deathredAnim.anim.PushBack({ 276, 267, 25, 48 });
	deathredAnim.anim.PushBack({ 307, 267, 26, 48 });
	deathredAnim.anim.loop = false;
	deathredAnim.anim.speed = 0.1f;

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
	enemyBullet.speed.y = 3;
	enemyBullet.lifetime = 40;
	enemyBullet.anim.speed = 0.1f;	
	
	enemyBulletL.anim.PushBack({194, 64, 12, 17});
	enemyBulletL.anim.PushBack({212, 65, 11, 16});
	enemyBulletL.speed.x = -1;
	enemyBulletL.speed.y = 2;
	enemyBulletL.lifetime = 40;
	enemyBulletL.anim.speed = 0.1f;	
	
	enemyBulletR.anim.PushBack({194, 64, 12, 17});
	enemyBulletR.anim.PushBack({212, 65, 11, 16});
	enemyBulletR.speed.x = 1;
	enemyBulletR.speed.y = 2;
	enemyBulletR.lifetime = 40;
	enemyBulletR.anim.speed = 0.1f;

	granadeN.anim.PushBack({ 0, 160, 15, 16 });
	granadeN.anim.PushBack({ 18, 160, 13, 16 });
	granadeN.anim.PushBack({ 35, 160, 11, 16 });
	granadeN.anim.PushBack({ 50, 160, 11, 16 });
	granadeN.anim.PushBack({ 66, 160, 11, 16 });
	granadeN.anim.PushBack({ 82, 160, 13, 16 });
	granadeN.anim.PushBack({ 96, 160, 15, 16 });
	granadeN.anim.PushBack({ 114, 160, 14, 16 });
	granadeN.anim.PushBack({ 131, 160, 12, 16 });
	granadeN.anim.PushBack({ 146, 160, 12, 16 });
	granadeN.anim.PushBack({ 161, 160, 13, 16 });
	granadeN.anim.PushBack({ 177, 160, 14, 16 });
	granadeN.speed.y = -1;
	granadeN.lifetime = 50;
	granadeN.anim.speed = 0.1f;

	granadeNE.anim.PushBack({ 0, 160, 15, 16 });
	granadeNE.anim.PushBack({ 18, 160, 13, 16 });
	granadeNE.anim.PushBack({ 35, 160, 11, 16 });
	granadeNE.anim.PushBack({ 50, 160, 11, 16 });
	granadeNE.anim.PushBack({ 66, 160, 11, 16 });
	granadeNE.anim.PushBack({ 82, 160, 13, 16 });
	granadeNE.anim.PushBack({ 96, 160, 15, 16 });
	granadeNE.anim.PushBack({ 114, 160, 14, 16 });
	granadeNE.anim.PushBack({ 131, 160, 12, 16 });
	granadeNE.anim.PushBack({ 146, 160, 12, 16 });
	granadeNE.anim.PushBack({ 161, 160, 13, 16 });
	granadeNE.anim.PushBack({ 177, 160, 14, 16 });
	granadeNE.speed.y = -1;
	granadeNE.speed.x = 1;
	granadeNE.lifetime = 50;
	granadeNE.anim.speed = 0.1f;

	granadeE.anim.PushBack({ 0, 160, 15, 16 });
	granadeE.anim.PushBack({ 18, 160, 13, 16 });
	granadeE.anim.PushBack({ 35, 160, 11, 16 });
	granadeE.anim.PushBack({ 50, 160, 11, 16 });
	granadeE.anim.PushBack({ 66, 160, 11, 16 });
	granadeE.anim.PushBack({ 82, 160, 13, 16 });
	granadeE.anim.PushBack({ 96, 160, 15, 16 });
	granadeE.anim.PushBack({ 114, 160, 14, 16 });
	granadeE.anim.PushBack({ 131, 160, 12, 16 });
	granadeE.anim.PushBack({ 146, 160, 12, 16 });
	granadeE.anim.PushBack({ 161, 160, 13, 16 });
	granadeE.anim.PushBack({ 177, 160, 14, 16 });
	granadeE.speed.x = 1;
	granadeE.lifetime = 50;
	granadeE.anim.speed = 0.1f;

	granadeSE.anim.PushBack({ 0, 160, 15, 16 });
	granadeSE.anim.PushBack({ 18, 160, 13, 16 });
	granadeSE.anim.PushBack({ 35, 160, 11, 16 });
	granadeSE.anim.PushBack({ 50, 160, 11, 16 });
	granadeSE.anim.PushBack({ 66, 160, 11, 16 });
	granadeSE.anim.PushBack({ 82, 160, 13, 16 });
	granadeSE.anim.PushBack({ 96, 160, 15, 16 });
	granadeSE.anim.PushBack({ 114, 160, 14, 16 });
	granadeSE.anim.PushBack({ 131, 160, 12, 16 });
	granadeSE.anim.PushBack({ 146, 160, 12, 16 });
	granadeSE.anim.PushBack({ 161, 160, 13, 16 });
	granadeSE.anim.PushBack({ 177, 160, 14, 16 });
	granadeSE.speed.y = 1;
	granadeSE.speed.x = 1;
	granadeSE.lifetime = 50;
	granadeSE.anim.speed = 0.1f;

	granadeS.anim.PushBack({ 0, 160, 15, 16 });
	granadeS.anim.PushBack({ 18, 160, 13, 16 });
	granadeS.anim.PushBack({ 35, 160, 11, 16 });
	granadeS.anim.PushBack({ 50, 160, 11, 16 });
	granadeS.anim.PushBack({ 66, 160, 11, 16 });
	granadeS.anim.PushBack({ 82, 160, 13, 16 });
	granadeS.anim.PushBack({ 96, 160, 15, 16 });
	granadeS.anim.PushBack({ 114, 160, 14, 16 });
	granadeS.anim.PushBack({ 131, 160, 12, 16 });
	granadeS.anim.PushBack({ 146, 160, 12, 16 });
	granadeS.anim.PushBack({ 161, 160, 13, 16 });
	granadeS.anim.PushBack({ 177, 160, 14, 16 });
	granadeS.speed.y = 1;
	granadeS.lifetime = 50;
	granadeS.anim.speed = 0.1f;

	granadeSW.anim.PushBack({ 0, 160, 15, 16 });
	granadeSW.anim.PushBack({ 18, 160, 13, 16 });
	granadeSW.anim.PushBack({ 35, 160, 11, 16 });
	granadeSW.anim.PushBack({ 50, 160, 11, 16 });
	granadeSW.anim.PushBack({ 66, 160, 11, 16 });
	granadeSW.anim.PushBack({ 82, 160, 13, 16 });
	granadeSW.anim.PushBack({ 96, 160, 15, 16 });
	granadeSW.anim.PushBack({ 114, 160, 14, 16 });
	granadeSW.anim.PushBack({ 131, 160, 12, 16 });
	granadeSW.anim.PushBack({ 146, 160, 12, 16 });
	granadeSW.anim.PushBack({ 161, 160, 13, 16 });
	granadeSW.anim.PushBack({ 177, 160, 14, 16 });
	granadeSW.speed.y = 1;
	granadeSW.speed.x = - 1;
	granadeSW.lifetime = 50;
	granadeSW.anim.speed = 0.1f;

	granadeW.anim.PushBack({ 0, 160, 15, 16 });
	granadeW.anim.PushBack({ 18, 160, 13, 16 });
	granadeW.anim.PushBack({ 35, 160, 11, 16 });
	granadeW.anim.PushBack({ 50, 160, 11, 16 });
	granadeW.anim.PushBack({ 66, 160, 11, 16 });
	granadeW.anim.PushBack({ 82, 160, 13, 16 });
	granadeW.anim.PushBack({ 96, 160, 15, 16 });
	granadeW.anim.PushBack({ 114, 160, 14, 16 });
	granadeW.anim.PushBack({ 131, 160, 12, 16 });
	granadeW.anim.PushBack({ 146, 160, 12, 16 });
	granadeW.anim.PushBack({ 161, 160, 13, 16 });
	granadeW.anim.PushBack({ 177, 160, 14, 16 });
	granadeW.speed.x = - 1;
	granadeW.lifetime = 50;
	granadeW.anim.speed = 0.1f;

	granadeNW.anim.PushBack({ 0, 160, 15, 16 });
	granadeNW.anim.PushBack({ 18, 160, 13, 16 });
	granadeNW.anim.PushBack({ 35, 160, 11, 16 });
	granadeNW.anim.PushBack({ 50, 160, 11, 16 });
	granadeNW.anim.PushBack({ 66, 160, 11, 16 });
	granadeNW.anim.PushBack({ 82, 160, 13, 16 });
	granadeNW.anim.PushBack({ 96, 160, 15, 16 });
	granadeNW.anim.PushBack({ 114, 160, 14, 16 });
	granadeNW.anim.PushBack({ 131, 160, 12, 16 });
	granadeNW.anim.PushBack({ 146, 160, 12, 16 });
	granadeNW.anim.PushBack({ 161, 160, 13, 16 });
	granadeNW.anim.PushBack({ 177, 160, 14, 16 });
	granadeNW.speed.y = - 1;
	granadeNW.speed.x = - 1;
	granadeNW.lifetime = 50;
	granadeNW.anim.speed = 0.1f;

	BulletBoss.anim.PushBack({0, 382, 12, 17});
	BulletBoss.anim.PushBack({18, 382, 8, 17 });
	BulletBoss.anim.loop = true;
	BulletBoss.speed.y = 3;
	BulletBoss.lifetime = 40;
	BulletBoss.anim.speed = 0.1f;

	BulletBossL.anim.PushBack({222, 382, 16, 16});
	BulletBossL.anim.PushBack({238, 382, 15, 16});
	BulletBossL.anim.loop = true;
	BulletBossL.speed.y = 3;
	BulletBossL.speed.x = -3;
	BulletBossL.lifetime = 40;
	BulletBossL.anim.speed = 0.1f;

	BulletBossR.anim.PushBack({31, 382, 15, 17});
	BulletBossR.anim.PushBack({47, 382, 15, 16 });
	BulletBossR.anim.loop = true;
	BulletBossR.speed.y = 3;
	BulletBossR.speed.x = 3;
	BulletBossR.lifetime = 40;
	BulletBossR.anim.speed = 0.1f;


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