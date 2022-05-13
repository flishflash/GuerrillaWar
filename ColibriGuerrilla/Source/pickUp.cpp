#include "pickUp.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

pickUp::pickUp(int x, int y) : positionenemy(x, y)
{
	spawnPos = positionenemy;
}

pickUp::~pickUp()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* pickUp::GetCollider() const
{
	return collider;
}

void pickUp::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(positionenemy.x, positionenemy.y);
}

void pickUp::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, positionenemy.x, positionenemy.y, &(currentAnim->GetCurrentFrame()));
}

void pickUp::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, positionenemy.x, positionenemy.y);
	App->audio->PlayFx(destroyedFx);

	SetToDelete();
}

void pickUp::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}