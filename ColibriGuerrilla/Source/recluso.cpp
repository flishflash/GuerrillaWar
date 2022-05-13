#include "recluso.h"

#include "Application.h"
#include "ModuleCollisions.h"

recluso::recluso(int x, int y) : pickUp(x, y)
{

}

void recluso::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	pickUp::Update();
}
