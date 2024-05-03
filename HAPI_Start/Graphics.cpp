#include "Graphics.h"
#include "Textures.h"

#pragma warning (disable : 26451)

Graphics::Graphics()
{
}

// Deletes all the data thats inside the map.
Graphics::~Graphics()
{
	for (auto i : m_TextureMap)
	{
		delete i.second;
	}
}

// Sets the screen height and width as will as initialising it.
bool Graphics::Initialise(int sw, int sh)
{
	m_ScreenWidth = sw;

	m_ScreenHeight = sh;

	if (!HAPI.Initialise(m_ScreenWidth, m_ScreenHeight, "HAPI Engine"))
	{
		return false;
	}

	HAPI.SetShowFPS(true);

	m_Screen = HAPI.GetScreenPointer();

	return true;
}

// This function changes the colour of the screen by setting each pixel to a colour. 
void Graphics::ClearToColour(HAPI_TColour col)
{
	for (int i = 0; i < m_ScreenWidth * m_ScreenHeight; i++)
	{
		memcpy(m_Screen + i * 4, &col, 4);
	}
}

// This searches for a texture and gives it a name.
bool Graphics::LoadTexture(const std::string& filename, const std::string& name)
{
	Textures* newTexture = new Textures;

	if (!newTexture->Create(filename))
	{
		delete newTexture;

		return false;
	}

	m_TextureMap[name] = newTexture;

	return true;

}

// Both of this functions draw the textures onto the screen.
void Graphics::DrawTextureFast(const std::string& name, int sx, int sy)
{
	if (m_TextureMap.find(name) == m_TextureMap.end())
	{
		std::cout << "Cound not find texture to render: " << name <<std::endl;
		return;
	}

	m_TextureMap[name]->FastBlit(m_Screen, m_ScreenWidth, m_ScreenHeight, sx, sy);
}

void Graphics::DrawTextureAlphaClip(const std::string& name, int sx, int sy)
{
	if (m_TextureMap.find(name) == m_TextureMap.end())
	{
		std::cout << "Cound not find texture to render: " << name << std::endl;
		return;
	}

	m_TextureMap[name]->AlphaClipBlit(m_Screen, m_ScreenWidth, m_ScreenHeight, sx, sy);
}

// These 4 functions let me get access to 4 different variables and use them in different classes.
int Graphics::GetTextureWidth(const std::string& name)
{
	return m_TextureMap[name]->GetWidth();
}

int Graphics::GetTextureHeight(const std::string& name)
{
	return m_TextureMap[name]->GetHeight();
}

int Graphics::GetScreenWidth()
{
	return m_ScreenWidth;
}

int Graphics::GetScreenHeight()
{
	return m_ScreenHeight;
}
