#include "Destroy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Destroy::Destroy(int x, int y) : positiondestroy(x, y)
{
	spawnPos = positiondestroy;
}

Destroy::~Destroy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Destroy::GetCollider() const
{
	return collider;
}

void Destroy::Update()
{

	if (collider != nullptr)
		collider->SetPos(positiondestroy.x, positiondestroy.y);
}

void Destroy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, positiondestroy.x, positiondestroy.y, &(currentAnim->GetCurrentFrame()));
}

void Destroy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, positiondestroy.x, positiondestroy.y);
	App->audio->PlayFx(destroyedFx);

	SetToDelete();
}

void Destroy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}