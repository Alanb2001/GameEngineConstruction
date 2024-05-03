#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Rectangle
{
public:
	int m_Left{ 0 };
	int m_Right{ 0 };
	int m_Top{ 0 };
	int m_Bottom{ 0 };

	Rectangle(int l, int r, int t, int b) : m_Left(l), m_Right(r), m_Top(t), m_Bottom(b) {}
	Rectangle();
	int Width() const { return m_Right - m_Left; }
	int Height() const { return m_Bottom - m_Top; }
	void Translate(int dx, int dy);
	void ClipTo(const Rectangle& other);
	bool CompletelyContains(const Rectangle& other) const;
	bool CompletelyOutside(const Rectangle& other) const;
	bool Collide(Rectangle other);
};

