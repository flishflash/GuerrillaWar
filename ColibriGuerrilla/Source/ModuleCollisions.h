#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__
#define MAX_COLLIDERS 500
#include "Module.h"
#include "Collider.h"
class ModuleCollisions : public Module {
	public:
		ModuleCollisions();
		~ModuleCollisions();
		update_status PreUpdate();
		update_status Update();
		update_status PostUpdate();
		bool CleanUp();
		Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);
		void DebugDraw();
	private:
		Collider* colliders[MAX_COLLIDERS] = { nullptr };
		bool matrix[Collider::Type::MAX][Collider::Type::MAX];
};
#endif // __MODULE_COLLISIONS_H__