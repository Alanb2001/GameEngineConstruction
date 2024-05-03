#include "World.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "BackgroundEntity.h"
#include "BulletEntity.h"
#include "Graphics.h"
#include <string>
#include <time.h>

World::World()
{
}

World::~World()
{
	for (auto p : m_EntityVector)
	{
		delete p;
	}

	m_EntityVector.clear();

	delete m_Graph;
}

// This function creates a window.
bool World::Initialise()
{
	m_Graph = new Graphics();

	if (!m_Graph->Initialise(540, 756))
	{
		delete m_Graph;
		return false;
	}

	return true;
}

constexpr int numBullets = 20;
constexpr int numEnemies = 5;

/* This function holds the update loop which creates the colour of the screen and graphics, as well as checking for any collisions that may occur and
   also checking if any enitity is alive or dead. */
void World::run()
{
	DWORD lastTimeUpdated = HAPI.GetTime();

	const DWORD tickTime = 1000 / 50;

	while (HAPI.Update())
	{
		DWORD timeSinceLastUpdate = HAPI.GetTime() - lastTimeUpdated;

		lastTimeUpdated = HAPI.GetTime();

		float deltatime = (float)timeSinceLastUpdate / 1000.0f;

		if (lastTimeUpdated >= tickTime)
		{
			for (auto p : m_EntityVector)
			{
				if (!p->IsAlive())
				{
					continue;
				}
				p->Update(*m_Graph, deltatime);
			}
		}

		for (size_t entity1 = 0; entity1 < m_EntityVector.size(); entity1++)
		{
			if (!m_EntityVector[entity1]->IsAlive() || !m_EntityVector[entity1]->IsCollider())
			{
				continue;
			}

			for (size_t entity2 = 0; entity2 < m_EntityVector.size(); entity2++)
			{
				if (entity1 == entity2)
				{
					continue;
				}
				else if (!m_EntityVector[entity2]->IsAlive() || !m_EntityVector[entity2]->IsCollider())
				{
					continue;
				}

				m_EntityVector[entity1]->CheckCollision(*m_EntityVector[entity2]);
			}
		}

		if (m_AliveEnemies == 0)
		{
			for (int i = 0; i < numEnemies; i++)
			{
				srand(time(NULL));

				EnemyEntity* enemy = new EnemyEntity("Enemy", 0 + i * m_Graph->GetScreenWidth() / 5, 0, m_Graph->GetTextureWidth("Enemy"), m_Graph->GetTextureHeight("Enemy"), this, "Enemy", true);

				m_EntityVector.push_back(enemy);

				m_AliveEnemies += 1;

			}
		}

		for (auto p : m_EntityVector)
		{
			if (!p->IsAlive())
			{
				continue;
			}

			p->Render(*m_Graph);
		}

		if (m_GameOver)
		{
			HAPI.RenderText(200, 350, HAPI_TColour::WHITE, "GameOver", 26, eRegular);
		}

		HAPI.RenderText(210, 0, HAPI_TColour::WHITE, "Score:", 20, eRegular);
		HAPI.RenderText(270, 0, HAPI_TColour::WHITE, std::to_string(m_Score), 20, eRegular);
	}
}

// This function finds the filepath for the textures and also puts each entity into the entity vector.
bool World::LoadLevel()
{
	if (!m_Graph->LoadTexture("Data\\laserBlue12.png", "Bullet"))
	{
		HAPI.UserMessage("Could not load file", "Error");
		return false;
	}

	if (!m_Graph->LoadTexture("Data\\purple.png", "Background"))
	{
		HAPI.UserMessage("Could not load file", "Error");
		return false;
	}

	if (!m_Graph->LoadTexture("Data\\enemyBlack4.png", "Enemy"))
	{
		HAPI.UserMessage("Could not load file", "Error");
		return false;
	}

	if (!m_Graph->LoadTexture("Data\\playerShip2_red.png", "Player"))
	{
		HAPI.UserMessage("Could not load file", "Error");
		return false;
	}

	BackgroundEntity* background = new BackgroundEntity("Background", 0, 0, m_Graph->GetTextureWidth("Background"), m_Graph->GetTextureHeight("Background"), this, "Background", false);

	m_EntityVector.push_back(background);

	for (int i = 0; i < numEnemies; i++)
	{
		srand(time(NULL));

		EnemyEntity* enemy = new EnemyEntity("Enemy", 0 + i * m_Graph->GetScreenWidth() / 5, 0, m_Graph->GetTextureWidth("Enemy"), m_Graph->GetTextureHeight("Enemy"), this, "Enemy", true);

		m_EntityVector.push_back(enemy);

		m_AliveEnemies += 1;

	}

	PlayerEntity* player = new PlayerEntity("Player", 300, 400, m_Graph->GetTextureWidth("Player"), m_Graph->GetTextureHeight("Player"), this, "Player", true, 3);

	m_EntityVector.push_back(player);

	m_BulletStartIndex = m_EntityVector.size();

	for (int i = 0; i < numBullets; i++)
	{
		BulletEntity* newBullet = new BulletEntity("Bullet", 0, 0, m_Graph->GetTextureWidth("Bullet"), m_Graph->GetTextureHeight("Bullet"), this, "Bullet", true, Vector2(0, -1));

		newBullet->Hurt(1);

		m_EntityVector.push_back(newBullet);
	}

	return true;
}

// This function goes through each bullet and checks to see if it is alive and if not than it can fire that bullet.
void World::FireBullet(Vector2 startPos, Vector2 velocity)
{
	for (size_t i = m_BulletStartIndex; i < m_BulletStartIndex + numBullets; i++)
	{
		if (!m_EntityVector[i]->IsAlive())
		{
			((BulletEntity*)m_EntityVector[i])->Fire(startPos, velocity, 1);
			return;
		}
	}
}

void World::ScoreIncrease(int score)
{
	m_Score += score;
}

void World::GameOver()
{
	m_GameOver = true;
}

void World::GetAliveEnemies()
{
	m_AliveEnemies -= 1;
}
