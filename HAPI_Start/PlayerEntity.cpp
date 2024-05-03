#include "PlayerEntity.h"
#include "World.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

#pragma warning (disable : 4244)

PlayerEntity::PlayerEntity(const std::string& spritename, int posx, int posy, int width, int height, World* world, std::string name, bool collide, int lives)
	: Entity(spritename, posx, posy, width, height, world, name, collide)
{
	m_Lives = lives;
}

PlayerEntity::~PlayerEntity()
{
}

// This function allow the player to move and shoot bullets as well as updating the collison box.  
void PlayerEntity::Update(Graphics& graph, float deltatime)
{
	Entity::Update(graph, deltatime);

	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

	// Movement keys for the player.
	if (keyData.scanCode[HK_UP]) 
	{
		m_PosY -= m_Speed * deltatime;
	}

	if (keyData.scanCode[HK_DOWN])
	{
		m_PosY +=  m_Speed * deltatime;
	}

	if (keyData.scanCode[HK_LEFT])
	{
		m_PosX -= m_Speed * deltatime;
	}

	if (keyData.scanCode[HK_RIGHT])
	{
		m_PosX += m_Speed * deltatime;
	}

	if (m_PosX <= 0)
	{
		m_PosX = 0;
	}

	if (m_PosX + graph.GetTextureWidth("Player") >= graph.GetScreenWidth())
	{
		m_PosX = graph.GetScreenWidth() - graph.GetTextureWidth("Player");
	}

	if (m_PosY <= 0)
	{
		m_PosY = 0;
	}

	if (m_PosY + graph.GetTextureHeight("Player") >= graph.GetScreenHeight())
	{
		m_PosY = graph.GetScreenHeight() - graph.GetTextureHeight("Player");
	}

	m_IsShootKeyPressed = keyData.scanCode[HK_CONTROL];

	if (m_TimeSinceShot < m_delayShot)
	{
		m_TimeSinceShot += deltatime;
	}
	else if (m_IsShootKeyPressed)
	{
		m_World->FireBullet(Vector2(m_PosX, m_PosY), Vector2(0, -600));
		m_TimeSinceShot = 0;
	}

	rect = Rectangle(m_PosX, m_PosX + m_Width, m_PosY, m_PosY + m_Height);
}


// This function checks if the player has hit any enitiy with the name enemy and if so then it dies. 
void PlayerEntity::CheckCollision(Entity& other)
{
	if (!rect.Collide(other.GetRect()))
	{
		return;
	}

	if (other.GetName() == "Enemy")
	{
		other.Hurt(1);
		Hurt(1);
		m_World->GameOver();
	}
}
