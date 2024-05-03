#include "BackgroundEntity.h"
#include "Graphics.h"

BackgroundEntity::BackgroundEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide)
	: Entity(spritename, posx, posy, width, height, world, name, collide)
{
}

BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::Render(Graphics& graph)
{
	graph.DrawTextureAlphaClip(m_SpriteName, m_PosX, m_PosY);
}

void BackgroundEntity::Update(Graphics& graph, float deltatime)
{

}
