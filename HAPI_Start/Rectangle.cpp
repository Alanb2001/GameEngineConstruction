#include "Rectangle.h"

#pragma warning (disable : 26451)

Rectangle::Rectangle()
{
}

// Moves the rectangle to its correct position.
void Rectangle::Translate(int dx, int dy)
{
	m_Left += dx;
	m_Right += dx;
	m_Top += dy;
	m_Bottom += dy;
}

// Allows for the rectangles to clip through each other.
void Rectangle::ClipTo(const Rectangle& other)
{
	if (m_Right > other.m_Right)
	{
		m_Right = other.m_Right;
	}

	if (m_Bottom > other.m_Bottom)
	{
		m_Bottom = other.m_Bottom;
	}

	if (m_Left < other.m_Left)
	{
		m_Left = other.m_Left;
	}

	if (m_Top < other.m_Top)
	{
		m_Top = other.m_Top;
	}
}

// Checks to see if two rectangles are exactly in the same position.
bool Rectangle::CompletelyContains(const Rectangle& other) const
{
	if (m_Left == other.m_Right)
	{
		return true;
	}

	if (m_Bottom == other.m_Top)
	{
		return true;
	}

	if (m_Right == other.m_Left)
	{
		return true;
	}

	if (m_Top == other.m_Bottom)
	{
		return true;
	}

	return false;
}

// Checks to see if two rectangles are in a completely different position.
bool Rectangle::CompletelyOutside(const Rectangle& other) const
{
	if (m_Left > other.m_Right)
	{
	    return true;
	}

	if (m_Bottom < other.m_Top)
	{
		return true;
	}

	if (m_Right < other.m_Left)
	{
		return true;
	}

	if (m_Top > other.m_Bottom)
	{
		return true;
	}

	return false;
}

// Checks for collisions.
bool Rectangle::Collide(Rectangle other)
{
	return ((m_Right > other.m_Left && m_Left < other.m_Right) && (m_Bottom > other.m_Top && m_Top < other.m_Bottom));
}
