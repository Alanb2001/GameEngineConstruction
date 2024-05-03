#pragma once
#include "Entity.h"
#include "Vector2.h"

class BulletEntity : public Entity
{
private:
	Vector2 m_Direction;
public: 
	BulletEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide, Vector2 dir);
	~BulletEntity();
	void Update(Graphics& graph, float deltatime) override;
	void Fire(Vector2 startPos, Vector2 direction, int health);
	void BulletEntity::CheckCollision(Entity& other) override;
};

