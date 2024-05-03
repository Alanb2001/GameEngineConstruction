#include "Entity.h"
#include "Graphics.h"
#include "World.h"

Entity::Entity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide)
{
	m_Name = name;
	m_Collider = collide;
	m_SpriteName = spritename;
	m_PosX = posx;
	m_PosY = posy;
	m_Width = width;
	m_Height = height;
	m_World = world;

	rect = Rectangle(posx, posx + width, posy, posy + height);
}

Entity::~Entity()
{

}

void Entity::Render(Graphics& graph)
{
	graph.DrawTextureAlphaClip(m_SpriteName, m_PosX, m_PosY);
}

void Entity::Update(Graphics& graph, float deltatime)
{
	rect = Rectangle(m_PosX, m_PosX + m_Width, m_PosY, m_PosY + m_Height);
}

std::string Entity::GetName()
{
	return m_Name;
}

void Entity::CheckCollision(Entity& other)
{
	return;
}

// This function makes it so when a collision happens you lose health, once that reaches 0 that entity dies.
void Entity::Hurt(int amount)
{
	m_Health -= amount;

	if (m_Health < 0)
	{
		m_Health = 0;
	}
}

bool Entity::IsAlive()
{
	return m_Health > 0;
}

bool Entity::IsCollider()
{
	return m_Collider;
}

Rectangle Entity::GetRect()
{
	return rect;
}
