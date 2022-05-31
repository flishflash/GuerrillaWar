#include "Fusil.h"

#include "Application.h"
#include "ModuleCollisions.h"


Fusil::Fusil(int x, int y) : pickUp(x, y)
{
	fusilaso.PushBack({13,196,22,22});
	fusilaso.PushBack({45,196,22,22});
	fusilaso.PushBack({77,196,22,22});
	fusilaso.loop = true;
	fusilaso.speed = 0.1f;
	currentAnim = &fusilaso;
	collider = App->collisions->AddCollider({ x, y, 22, 22 }, Collider::Type::PICK, (Module*)App->picks);

}

void Fusil::Update()
{
	path.Update();
	currentAnim = &fusilaso;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	pickUp::Update();
}
