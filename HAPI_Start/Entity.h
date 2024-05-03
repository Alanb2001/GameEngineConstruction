#pragma once
#include <string>
#include "Rectangle.h"
#include "Graphics.h"

class World;

class Entity
{
protected:
	float m_PosX{ 0 };
	float m_PosY{ 0 };
	std::string m_SpriteName;
	std::string m_Name;
	int m_Health{ 1 };
	Rectangle rect;
	int m_Width{ 0 };
	int m_Height{ 0 };
	World* m_World{ nullptr };
	bool m_Collider = false;
	float m_Speed{ 200.0f };
public:
	Entity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide);
	~Entity();
	virtual void Render(Graphics& graph);
	virtual void Update(Graphics& graph, float deltatime);
	std::string GetName();
	virtual void CheckCollision(Entity& other);
	void Hurt(int amount);
	bool IsAlive();
	bool IsCollider();
	Rectangle GetRect();
};

