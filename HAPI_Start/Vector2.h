#pragma once

class Vector2
{
public:
	float m_X { 0 };
	float m_Y { 0 };

	Vector2();
	Vector2(float newX, float newY) : m_X(newX), m_Y(newY) {}
	Vector2 operator + (const Vector2& rhs) const;
	Vector2 operator - (const Vector2& rhs) const;
	Vector2 operator * (const Vector2& rhs) const;
	Vector2& operator *= (const Vector2& rhs);
	float Length() const;
	void NormaliseInPlace();
	float DotProduct(const Vector2& other) const;
	float CrossProduct(const Vector2& other) const;
};

