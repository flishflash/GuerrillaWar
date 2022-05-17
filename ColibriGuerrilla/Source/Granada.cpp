#include "Granada.h"

#include "Application.h"
#include "ModuleCollisions.h"

Granada::Granada(int x, int y) : pickUp(x, y)
{

}

void Granada::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	pickUp::Update();
}
