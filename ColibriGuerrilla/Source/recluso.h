#ifndef __RECLUSO_H__
#define __RECLUSO_H__

#include "pickUp.h"
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
	void OnCollision(Collider* c1, Collider* c2);
	bool AddRecluso(int x, int y);

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation normalAnim;
	Animation rescuedAnim;
	Animation deathAnim;

	ReclusoSpawnpoint spawnQueueR[MAX_RECLUSOS];

};

#endif // __RECLUSO_H__