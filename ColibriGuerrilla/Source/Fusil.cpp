#include "Fusil.h"

#include "Application.h"
#include "ModuleCollisions.h"


Fusil::Fusil(int x, int y) : pickUp(x, y)
{
	fusilaso.PushBack({0,152,22,22});
	fusilaso.PushBack({32,152,22,22});
	fusilaso.PushBack({64,152,22,22});
	fusilaso.loop = true;
	fusilaso.speed = 0.1f;
	currentAnim = &fusilaso;
	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::PICK, (Module*)App->picks);

}

void Fusil::Update()
{
	path.Update();
	currentAnim = &fusilaso;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	pickUp::Update();
}
