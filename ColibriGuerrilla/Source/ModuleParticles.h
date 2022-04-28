#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__
#include "Module.h"
struct SDL_Texture;
#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#define MAX_ACTIVE_PARTICLES 100
class ModuleParticles : public Module {
	public:
		ModuleParticles();
		~ModuleParticles();
		bool Start() override;
		update_status Update() override;
		update_status PostUpdate() override;
		bool CleanUp() override;
		void OnCollision(Collider* c1, Collider* c2) override;
		void AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);
		Particle explosion;
		Particle laser;
		Particle bulletN;
		Particle bulletNE;
		Particle bulletE;
		Particle bulletSE;
		Particle bulletS;
		Particle bulletSW;
		Particle bulletW;
		Particle bulletNW;
	private:
		SDL_Texture* texture = nullptr;
		Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };
};
#endif // !__MODULEPARTICLES_H__