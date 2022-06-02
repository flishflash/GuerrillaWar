#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void shootNormalBullet();
	void launchGranade();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	//Print Only the trees of the map
	SDL_Texture* trees = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation northAnim;
	Animation southAnim;
	Animation eastAnim;
	Animation westAnim;
	Animation northEastAnim;
	Animation northWestAnim;
	Animation southEastAnim;
	Animation southWestAnim;
	Animation downAnim;
	Animation WidleAnim;
	Animation WnorthAnim;
	Animation WsouthAnim;
	Animation WeastAnim;
	Animation WwestAnim;
	Animation WnorthEastAnim;
	Animation WnorthWestAnim;
	Animation WsouthEastAnim;
	Animation WsouthWestAnim;
	Animation WdownAnim;
	int direction;
	// The player's collider
	Collider* collider = nullptr;

	bool gana = false;
	bool agua = false;
	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	uint destroyedCountdown = 60;
	bool pendingToDelete = false;
	// Sound effects indices
	uint NormalBulFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	uint highscore = 000;
	char HighscoreText[10] = { "\0" };

	SDL_Rect cameraGameplay;
};

#endif //!__MODULE_PLAYER_H__