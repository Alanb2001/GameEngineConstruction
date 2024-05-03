#pragma once

#include <HAPI_lib.h>

#include "Rectangle.h"

using namespace HAPISPACE;

class Textures
{
private:
	int m_Width{0};
	int m_Height{0};
	BYTE* m_Data{ nullptr };
public:
	bool Create(const std::string& filename);
	Textures();
	~Textures();
	void FastBlit(BYTE* screen, int screenWidth, int screenHeight, int sx, int sy);
	void AlphaClipBlit(BYTE* dest, int destWidth, int desHeight, int posX, int posY);
	int GetWidth();
	int GetHeight();
};

