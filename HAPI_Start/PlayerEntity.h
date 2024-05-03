#pragma once
#include "Entity.h"
#include <string>

class PlayerEntity : public Entity
{
private:
	int m_Lives{ 3 };
	float m_TimeSinceShot{ 0.0f };
	float m_delayShot{ 0.5f };
	bool m_IsShootKeyPressed{ false };
public:
	PlayerEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide, int lives);
	~PlayerEntity();
	void Update(Graphics& graph, float deltatime) override;
	void PlayerEntity::CheckCollision(Entity& other) override;
};

