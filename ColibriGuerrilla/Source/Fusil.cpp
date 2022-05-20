#include "Fusil.h"

#include "Application.h"
#include "ModuleCollisions.h"

Fusil::Fusil(int x, int y) : pickUp(x, y)
{
	fusilaso.PushBack({0,152,22,22});
	fusilaso.PushBack({32,152,22,22});
	fusilaso.PushBack({64,152,22,22});

	currentAnim = &fusilaso;
}

void Fusil::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	pickUp::Update();
}
