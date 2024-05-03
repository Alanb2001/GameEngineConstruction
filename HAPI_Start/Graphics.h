#pragma once

#include <HAPI_lib.h>
#include <unordered_map>

#include "Rectangle.h"

using namespace HAPISPACE;

class Textures;

class Graphics
{
private:
	int m_ScreenWidth{0};
	int m_ScreenHeight{0};
	BYTE* m_Screen{ nullptr };
	std::unordered_map<std::string, Textures*> m_TextureMap;
public:
	Graphics();
	~Graphics();
	bool Initialise(int sw, int sh);
	void ClearToColour(HAPI_TColour col);
	bool LoadTexture(const std::string& filename, const std::string& name);
	void DrawTextureFast(const std::string& name, int sx, int sy);
	void DrawTextureAlphaClip(const std::string& name, int sx, int sy);
	int GetTextureWidth(const std::string& name);
	int GetTextureHeight(const std::string& name);
	int GetScreenWidth();
	int GetScreenHeight();
};

