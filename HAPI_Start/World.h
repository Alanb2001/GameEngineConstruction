#pragma once
#include <vector>
#include "Vector2.h"

class Entity;
class Graphics;

class World
{
private:
	std::vector<Entity*> m_EntityVector{  };
	Graphics *m_Graph{ nullptr };
	size_t m_BulletStartIndex{ 0 };
	int m_Score{ 0 };
	int m_AliveEnemies{ 0 };
	bool m_GameOver{ false };
public:
	World();
	~World();
	bool Initialise();
	void run();
	bool LoadLevel();
	void FireBullet(Vector2 startPos, Vector2 velocity);
	void ScoreIncrease(int score);
	void GameOver();
	void GetAliveEnemies();
};

