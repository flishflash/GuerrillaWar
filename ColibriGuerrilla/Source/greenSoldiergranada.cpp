#include "greenSoldiergranada.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"


greenSoldiergranada::greenSoldiergranada(int x, int y) : Enemy(x, y)
{
	cooldown = 0;
	cooldown2 = 0;

	//walk forward
	granadeidle.PushBack({ 494, 934, 25, 47 });
	granadeidle.loop = true;
	granadeidle.speed = 0.1f;

	granadashot.PushBack({494, 934, 25, 47});
	granadashot.PushBack({494, 934, 25, 47});
	granadashot.PushBack({494, 934, 25, 47});
	granadashot.PushBack({494, 934, 25, 47});
	granadashot.PushBack({829, 853, 27, 54});
	granadashot.PushBack({737, 854, 28, 52});
	granadashot.PushBack({784, 859, 25, 44});
	granadashot.loop = true;
	granadashot.speed = 0.1f;

	//walk backward
	granadashotL.PushBack({ 532, 936, 28, 44 });
	granadashotL.PushBack({ 532, 936, 28, 44 });
	granadashotL.PushBack({ 532, 936, 28, 44 });
	granadashotL.PushBack({ 532, 936, 28, 44 });
	granadashotL.PushBack({ 687, 856, 31, 53 });
	granadashotL.PushBack({ 687, 856, 31, 53 });
	granadashotL.PushBack({ 874, 931, 28, 50 });
	granadashotL.loop = true;
	granadashotL.speed = 0.1f;

	granadashotR.PushBack({ 453, 935, 25, 44 });
	granadashotR.PushBack({ 453, 935, 25, 44 });
	granadashotR.PushBack({ 453, 935, 25, 44 });
	granadashotR.PushBack({ 453, 935, 25, 44 });
	granadashotR.PushBack({ 739, 926, 29, 47 });
	granadashotR.PushBack({ 793, 930, 25, 44 });
	granadashotR.PushBack({ 931, 933, 27, 38 });
	granadashotR.loop = true;
	granadashotR.speed = 0.1f;

	currentAnim = &granadeidle;
	LaunchG = App->audio->LoadFx("Assets/Fx/Throw_of_a_granade.wav");
	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}
void greenSoldiergranada::OnCollision(Collider* collider) {

		App->particles->AddParticle(App->particles->deathgreenAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);

		SetToDelete();

}
void greenSoldiergranada::Update()
{
	path.Update();


	if (cooldown > 0 && cooldown < 90)
	{

		if (cooldown < 33)
		{
				currentAnim = &granadashot;

			if (cooldown2 == 26)
			{
				App->particles->AddParticle(App->particles->granadeS, positionenemy.x, positionenemy.y + 25, Collider::Type::NONE, 20);
				App->particles->AddParticle(App->particles->explosionG, positionenemy.x-16, positionenemy.y + 65, Collider::Type::ENEMY_SHOT, 70);
				cooldown2 = 0;
			}
				cooldown2++;
		}
		else
		{
			currentAnim = &granadeidle;
		}
			
	}
	else
	{
		cooldown = 0;
		cooldown2 = 0;
	}

	cooldown++;

	Enemy::Update();
}
