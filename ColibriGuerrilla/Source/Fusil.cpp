#include "Fusil.h"

#include "Application.h"
#include "ModuleCollisions.h"

Fusil::Fusil(int x, int y) : pickUp(x, y)
{

}

void Fusil::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	pickUp::Update();
}
