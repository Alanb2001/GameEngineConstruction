#include "Vector2.h"
#include <cmath>
	
Vector2::Vector2()
{
}

// These functions allow you to calculate a vector 2. 
Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(m_X + rhs.m_X, m_Y + rhs.m_Y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(m_X - rhs.m_X, m_Y - rhs.m_Y);
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(rhs.m_X * m_X, rhs.m_Y * m_Y);
}

Vector2& Vector2::operator*=(const Vector2& rhs) 
{
	m_X *= rhs.m_X;
	m_Y *= rhs.m_Y;

	return Vector2(m_X, m_Y);
}

float Vector2::Length() const
{
	return sqrt(m_X * m_X + m_Y * m_Y);
}

void Vector2::NormaliseInPlace()
{
	float len = Length();

	if (len == 0)
	{
		return;
	}

	m_X /= len;
	m_Y /= len;
}

float Vector2::DotProduct(const Vector2& other) const
{
	return m_X * other.m_X + m_Y * other.m_Y;
}

float Vector2::CrossProduct(const Vector2& other) const
{
	return m_X * other.m_Y - m_Y * other.m_X;
}
