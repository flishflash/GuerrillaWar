#include "SceneLevel1.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include "ModulePickUp.h"
#include "ModuleDestroy.h"
#include "ModuleParticles.h"
#include "Boss_F1.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{
	 
}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Guerrilla_Map_Without_Objects.png");
	App->audio->PlayMusic("Assets/Music/04_Advance-_Area-1_-4_-5_.ogg", 1.0f);

	//player
	App->player->Enable();
	appear = 0;
	//Water colliders
	App->collisions->AddCollider({ 88, 4123, 302, 34 },	 Collider::Type::WATER);
	App->collisions->AddCollider({ 216, 3964, 81, 161 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 135, 4091, 32, 121 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 153, 4061, 205, 38 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 222, 4001, 104, 55 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 174, 4022, 162, 46 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 125, 4099, 242, 38 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 477, 633, 260, 403 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 798, 627, 191, 409 }, Collider::Type::WATER);

	//Ground colliders
	App->collisions->AddCollider({ 157, 3921, 147, 34 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 157, 3946, 45, 58 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 560, 2266, 40, 74 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 405, 2266, 40, 74 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 264, 3921, 163, 21 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 560, 3921, 163, 21 }, Collider::Type::GROUND);

	//Wall colliders
	App->collisions->AddCollider({ 452, 4015, 74, 200 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 4005, 54, 155 },	 Collider::Type::WALL);
	App->collisions->AddCollider({ 421, 4033, 54, 93 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 41, 4000, 52, 65 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 389, 3986, 60, 80 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 48, 3942, 71, 85 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 83, 3864, 73, 133 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 359, 3936, 40, 94 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 326, 3883, 50, 83 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 114, 3637, 72, 267 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 299, 3642, 54, 300 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 54, 4147, 423, 13 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 329, 3436, 50, 211 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 169, 3699, 44, 165 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 3614, 95, 32 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 3446, 40, 156 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 103, 3383, 49, 70 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 289, 3219, 67, 237 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 92, 3119, 88, 273 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 299, 3113, 125, 130 },Collider::Type::WALL);
	App->collisions->AddCollider({ 175, 3188, 40, 162 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 2975, 171, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 97, 3098, 53, 33 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 81, 2937, 32, 160 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 93, 2876, 60, 60 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 147, 2850, 253, 53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 401, 3090, 60, 30 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 429, 3072, 48, 21 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 447, 3051, 88, 21 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 526, 2908, 38, 148 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 405, 2588, 35, 285 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 436, 2682, 32, 151 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 557, 2621, 39, 286 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 377, 2483, 30, 91 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 575, 2603, 26, 23 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 585, 2552, 29, 61 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 555, 2348, 212, 202 },Collider::Type::WALL);
	App->collisions->AddCollider({ 261, 2349, 175, 138 },Collider::Type::WALL);
	App->collisions->AddCollider({ 240, 2109, 16, 252 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 768, 2118, 30, 238 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 255, 2081, 182, 23 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 557, 2080, 212, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 254, 1695, 29, 318 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 671, 1695, 32, 315 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 642, 1983, 124, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 254, 1950, 64, 64 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 642, 1953, 58, 29 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 256, 1696, 61, 62 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 256, 1600, 94, 30 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 670, 1600, 194, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 667, 1523, 265, 57 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 246, 1534, 148, 45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 312, 1450, 52, 65 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 737, 1489, 145, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340, 1150, 170, 270 },Collider::Type::WALL);
	App->collisions->AddCollider({ 483, 1146, 134, 193 },Collider::Type::WALL);
	App->collisions->AddCollider({ 606, 1245, 31, 95 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 828, 1454, 53, 35 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 856, 1150, 70, 313 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 883, 1123, 109, 159 },Collider::Type::WALL);
	App->collisions->AddCollider({ 930, 1070, 31, 64 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 511, 1070, 36, 67 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 479, 3, 153, 373 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 905, 3, 111, 401 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 887, 227, 34, 109 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 484, 363, 121, 116 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 890, 281, 126, 304 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 862, 415, 69, 32 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 481, 486, 112, 70 },  Collider::Type::WALL);
	App->collisions->AddCollider({ 481, 549, 80, 34 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 600, 0, 104, 189 },   Collider::Type::WALL);
	App->collisions->AddCollider({ 829, 0, 99, 189 },    Collider::Type::WALL);

	//Win collider
	App->collisions->AddCollider({ 729, 128, 71, 52 }, Collider::Type::WIN);

	//reclusos
	App->picks->AddPick(Pick_Type::RECLUSO, 151, 3370 );
	App->picks->AddPick(Pick_Type::RECLUSO, 175, 3370 );
	
	App->picks->AddPick(Pick_Type::RECLUSO, 247, 2920 );
	App->picks->AddPick(Pick_Type::RECLUSO, 271, 2920 );

	App->picks->AddPick(Pick_Type::RECLUSO, 548, 2522 );
	App->picks->AddPick(Pick_Type::RECLUSO, 538, 2332 );

	App->picks->AddPick(Pick_Type::RECLUSO, 423, 1929 );

	App->picks->AddPick(Pick_Type::RECLUSO, 647, 1325);
	App->picks->AddPick(Pick_Type::RECLUSO, 671, 1325);	
	
	App->picks->AddPick(Pick_Type::RECLUSO, 744, 1025);
	App->picks->AddPick(Pick_Type::RECLUSO, 786, 1025);

	//destrible
	App->destroys->AddDestroy(App->destroys->rock, 127, 3494, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 161, 3494, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 256, 3494, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 290, 3494, Collider::Type::DESTROY);
	
	App->destroys->AddDestroy(App->destroys->rock, 288, 3078, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 322, 3078, Collider::Type::DESTROY);
	
	App->destroys->AddDestroy(App->destroys->rock, 128, 2998, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 162, 3078, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 196, 3078, Collider::Type::DESTROY);	
	
	App->destroys->AddDestroy(App->destroys->rock, 416, 2501, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 450, 2501, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rockL, 487, 2462, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rockL, 552, 1471, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 256, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 290, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 324, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 358, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 392, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 426, 2104, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 544, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 578, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 612, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 646, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 680, 2104, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 714, 2104, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->fence, 256, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 285, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 310, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 339, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 365, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 394, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 419, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 448, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 473, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 502, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 527, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 556, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 581, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 610, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 635, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 664, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 689, 2018,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 718, 2033, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 743, 2033,  Collider::Type::DESTROY);
		
	App->destroys->AddDestroy(App->destroys->rock, 415, 1495, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 512, 1495, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 512, 1399, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 546, 1399, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 580, 1399, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 614, 1399, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 648, 1399, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 682, 1399, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 703, 1175, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 737, 1175, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 771, 1175, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 805, 1175, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 640, 1063, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 674, 1063, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 708, 1063, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 800, 1063, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 834, 1063, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 868, 1063, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 639, 551, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 673, 551, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 707, 551, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 800, 551, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 834, 551, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rock, 673, 503, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 707, 503, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 741, 503, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 775, 503, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rock, 809, 503, Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->rockL, 614, 511, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->rockL, 614, 544, Collider::Type::DESTROY);


	App->destroys->AddDestroy(App->destroys->fence, 256, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 285, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 310, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 339, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 365, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 394, 1630,  Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->fence, 521, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 550, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 575, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 604, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 629, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 659, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 683, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 712, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 737, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 766, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 791, 1630,  Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence2, 820, 1645, Collider::Type::DESTROY);
	App->destroys->AddDestroy(App->destroys->fence, 845, 1630,  Collider::Type::DESTROY);

	App->destroys->AddDestroy(App->destroys->trinch, 445, 1672,  Collider::Type::DESTROY);

	//camara
	App->player->cameraGameplay.x = 135;
	App->player->cameraGameplay.y = 3800;

	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//enemies
	//if (App->player->position.y == 341 && appear == 0)
	//{
	//	App->enemies->AddEnemy(Enemy_Type::BOSSF2, 737, 40); //bossf1 65
	//	appear++;
	//}

	if (App->player->position.y == 341 && appear == 17)
	{
		App->enemies->AddEnemy(Enemy_Type::BOSSF2, 737, 65); 
		appear++;
	}

	if (App->player->position.y == 3800 && appear == 0)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 215, 3600);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 241, 3600);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 267, 3600);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 215, 3530);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 241, 3530);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 267, 3530);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 215, 3460);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 241, 3460);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 267, 3460);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 215, 3390);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 241, 3390);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 267, 3390);

		appear=1;
		LOG("spawn 1");
	}
	if (App->player->position.y == 3710 && appear == 1)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 187, 3510);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 227, 3510);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 267, 3510);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 152, 3440);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 280, 3440);
		appear++;
		LOG("spawn 2");
	}
	if (App->player->position.y == 3594 && appear ==2)
	{
		App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 216, 3394);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 114, 3330);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 140, 3330);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 310, 3345);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 340, 3345);
		appear++;
		LOG("spawn 3");
	}
	if (App->player->position.y == 3500 && appear == 3)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 215, 3238);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 241, 3238);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 267, 3238);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 215, 3168);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 241, 3168);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 267, 3168);
		appear++;
		LOG("spawn 4");
	}
	if (App->player->cameraGameplay.y == 3162 && appear == 4)
	{
		App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 236, 3118);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 265, 3087);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 291, 3087);
		appear++;
	}
	if (App->player->cameraGameplay.y == 3046 && appear == 5)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 236, 3014);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 134, 3032);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 160, 3032);
		appear++;
	}
	if (App->player->cameraGameplay.y == 2797 && appear == 6)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 463, 2796);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 489, 2796);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 512, 2796);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 512, 2751);
		appear++;
	}
	if (App->player->cameraGameplay.y == 2702 && appear == 7)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 485, 2591);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 511, 2591);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 537, 2591);

		appear++;
	}
	if (App->player->cameraGameplay.y == 2538 && appear == 8)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 461, 2460);

		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 485, 2504);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 511, 2504);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 537, 2504);

		appear++;
	}
	if (App->player->cameraGameplay.y == 2239 && appear == 9)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 403, 2196);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 429, 2196);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 459, 2196);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 481, 2196);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 507, 2196);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 533, 2196);

		appear++;
	}
	if (App->player->cameraGameplay.y == 2125 && appear == 10)
	{
		App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 404, 2070);

		appear++;
	}
	if (App->player->cameraGameplay.y == 1866 && appear == 11)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 445, 1833);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 490, 1833);

		appear++;
	}
	if (App->player->cameraGameplay.y == 1771 && appear == 12)
	{
		App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 438, 1707);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 482, 1707);

		appear++;
	}
	if (App->player->cameraGameplay.y == 1553 && appear == 13)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 449, 1525);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 475, 1525);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIERGRAN, 501, 1525);

		appear++;
	}
	if (App->player->cameraGameplay.y == 1454 && appear == 14)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 627, 1425);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 653, 1425);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 679, 1425);

		appear++;
	}
	if (App->player->cameraGameplay.y == 1121 && appear == 15)
	{
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 707, 1091);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 733, 1091);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 759, 1091);
		App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 785, 1091);

		appear++;
	}
	if (App->player->cameraGameplay.y == 854 && appear == 16)
	{
		App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 780, 789);

		appear++;
	}


	//imputs
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A])
	{
		App->player->shootNormalBullet();
	}
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
	{
		App->player->launchGranade();
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->CleanUp();
	App->picks->CleanUp();
	App->destroys->CleanUp();
	App->particles->CleanUp();

	return true;
}