#include "EnemyEntity.h"
#include "World.h"

EnemyEntity::EnemyEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide) 
	: Entity(spritename, posx, posy, width, height, world, name, collide)
{
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update(Graphics& graph, float deltatime)
{
	Entity::Update(graph, deltatime);

	m_PosY += m_Speed * deltatime;

	Rectangle screenRect = Rectangle(0, graph.GetScreenWidth(), 0, graph.GetScreenHeight());

	if (rect.CompletelyOutside(screenRect))
	{
		m_Health = 0;
		m_World->GetAliveEnemies();
	}
}