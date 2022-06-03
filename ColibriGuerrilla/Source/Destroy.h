#pragma once

#ifndef __DESTROY_H__
#define __DESTROY_H__

#include "Animation.h"
#include "p2Point.h"


struct Collider;

class Destroy
{
	public:
		// Constructor
		Destroy();

		// Copy constructor
		Destroy(const Destroy& d);

		// Destructor
		~Destroy();

		// Called in ModuleParticles' Update
		// Handles the logic of the particle
		// Returns false when the particle reaches its lifetime
		bool Update();

		// Sets flag for deletion and for the collider aswell
		void SetToDelete();

		void OnCollision(Collider* collider);

	public:
		// Defines the position in the screen
		iPoint position;

		// Defines wether the particle is alive or not
		// Particles will be set to not alive until "spawnTime" is reached
		bool isAlive = false;

		// The particle's collider
		Collider* collider = nullptr;

		Animation anim;

		// A flag for the particle removal. Important! We do not delete objects instantly
		bool pendingToDelete = false;
	};


#endif // __DESTRY_H__
