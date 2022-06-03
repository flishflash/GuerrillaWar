#ifndef __RECLUSO_H__
#define __RECLUSO_H__

#include "pickUp.h"
#include "path.h"
#define MAX_RECLUSOS 100
struct ReclusoSpawnpoint
{
	int x, y;
};

class recluso : public pickUp
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	recluso(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;
	void OnCollision(Collider* c1);

private:
	// The original spawning position. The wave will be calculated from that
	Path path;
	// The enemy animation
	Animation normalAnim;
	Animation rescuedAnim;
	Animation deathAnim;

	ReclusoSpawnpoint spawnQueueR[MAX_RECLUSOS];
	int deletecooldown;
};

#endif // __RECLUSO_H__