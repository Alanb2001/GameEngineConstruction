#pragma once
#include "Entity.h"

class EnemyEntity : public Entity
{
public:
	EnemyEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide);
	~EnemyEntity();
	void Update(Graphics& graph, float deltatime) override;
};

