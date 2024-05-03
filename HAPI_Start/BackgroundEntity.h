#pragma once
#include "Entity.h"

class BackgroundEntity : public Entity
{
public:
	BackgroundEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide);
	~BackgroundEntity();
	void Render(Graphics& graph) override;
	void Update(Graphics& graph, float deltatime) override;
};

