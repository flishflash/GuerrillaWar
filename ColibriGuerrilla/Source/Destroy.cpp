#include "Destroy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Destroy::Destroy()
{
	position.SetToZero();
}

Destroy::Destroy(const Destroy& d) :  anim(d.anim), position(d.position)
{

}

Destroy::~Destroy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}


bool Destroy::Update()
{
	bool ret = true;

	anim.Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

void Destroy::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::EXPLOSION)
	{
		SetToDelete();
	}
}

void Destroy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}