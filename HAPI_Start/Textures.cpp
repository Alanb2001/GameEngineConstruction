#include "Textures.h"

#pragma warning (disable : 26451)

// This gets all the information it needs about a texture.
bool Textures::Create(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &m_Data, m_Width, m_Height))
	{
		return false;
	}

	return true;
}

Textures::Textures()
{
}

// Deletes all data for the textures.
Textures::~Textures()
{
	delete[]m_Data;
}

// Renders textures onto the screen.
void Textures::FastBlit(BYTE* screen, int screenWidth, int screenHeight, int sx, int sy)
{
	auto* screen_offset = screen + (screenWidth * sy + sx) * 4;
	auto* texture_offset = m_Data + (m_Width) * 4;
	const auto screen_increment = (screenWidth - m_Width) * 4;
	// Go through each pixel.
	for (auto y = 0; y < m_Height; ++y)
	{
		for (auto x = 0; x < m_Width; ++x)
		{
			const auto pX = sx + x;
			const auto pY = sy + y;
			// Prevent wrap.
			if (pX >= 0 && pX < screenWidth &&
				pY >= 0 && pY < screenHeight)
			{
				memcpy(screen_offset, texture_offset, 4);
			}
			screen_offset += 4;
			texture_offset += 4;
		}
		screen_offset += screen_increment;
	}
}

// Renders textures onto the screen while also making sure that the alpha changes and also allow for efficient clipping.
void Textures::AlphaClipBlit(BYTE* dest, int destWidth, int desHeight, int posX, int posY)
{
	Rectangle screenRect(0, destWidth, 0, desHeight);

	Rectangle textureRect(0, m_Width, 0, m_Height);

	textureRect.Translate(posX, posY);

	if (textureRect.CompletelyOutside(screenRect))
	{
		return;
	}

	if (textureRect.CompletelyContains(screenRect))
	{
		return;
	}

	textureRect.ClipTo(screenRect);

	textureRect.Translate(-posX, -posY);

	if (posX < 0)
	{
		posX = 0;
	}

	if (posY < 0)
	{
		posY = 0;
	}

	BYTE* destPnter = dest + (posX + posY * destWidth) * 4;
	BYTE* sourcePnter = m_Data + (textureRect.m_Left + textureRect.m_Top * m_Width) * 4;

	int endOfLineDestIncrement = (destWidth - textureRect.Width()) * 4;
	int endOfLineSourceIncrement = (m_Width - textureRect.Width()) * 4;

	for (int y = 0; y < textureRect.Height(); y++)
	{
		for (int x = 0; x < textureRect.Width(); x++)
		{
			BYTE alpha = sourcePnter[3];

			if (alpha > 0)
			{

				BYTE blue = sourcePnter[0];
				BYTE green = sourcePnter[1];
				BYTE red = sourcePnter[2];

				if (alpha == 255)
				{
					memcpy(destPnter, sourcePnter, 4);
				}
				else
				{
					destPnter[0] = destPnter[0] + ((alpha * (blue - destPnter[0])) >> 8);
					destPnter[1] = destPnter[1] + ((alpha * (green - destPnter[1])) >> 8);
					destPnter[2] = destPnter[2] + ((alpha * (red - destPnter[2])) >> 8);
				}
			}

			sourcePnter += 4;
			destPnter += 4;
		}

		destPnter += endOfLineDestIncrement;
		sourcePnter += endOfLineSourceIncrement;
	}
}

int Textures::GetWidth()
{
	return m_Width;
}

int Textures::GetHeight()
{
	return m_Height;
}
