#include "BulletEntity.h"
#include "World.h"

BulletEntity::BulletEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide, Vector2 dir) 
	: Entity(spritename,  posx,  posy,  width,  height, world, name, collide)
{
	m_Direction = dir;
}

BulletEntity::~BulletEntity()
{
	Entity::~Entity();
}

// This function makes it so that if the bullet goes of the screen it dies.
void BulletEntity::Update(Graphics& graph, float deltatime)
{
	Entity::Update(graph, deltatime);

	m_PosY += m_Direction.m_Y * deltatime;

	Rectangle screenRect = Rectangle(0, graph.GetScreenWidth(), 0, graph.GetScreenHeight());

	if (rect.CompletelyOutside(screenRect))
	{
		m_Health = 0;
	}
}

void BulletEntity::Fire(Vector2 startPos, Vector2 direction, int health)
{
	m_Direction = direction;
	m_PosX = startPos.m_X;
	m_PosY = startPos.m_Y;
	m_Health = health;
}

void BulletEntity::CheckCollision(Entity& other)
{
	if (!rect.Collide(other.GetRect()))
	{
		return;
	}
	if (other.GetName() == "Enemy")
	{
		other.Hurt(1);
		Hurt(1);
		m_World->ScoreIncrease(50);
		m_World->GetAliveEnemies();
	}
}
