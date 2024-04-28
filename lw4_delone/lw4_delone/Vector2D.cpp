#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) : m_x(x), m_y(y) {}

Vector2D Vector2D::operator+(const Vector2D& p) const
{
	return { m_x + p.m_x, m_y + p.m_y };
}

Vector2D Vector2D::operator-(const Vector2D& p) const
{
	return { m_x - p.m_x, m_y - p.m_y };
}

Vector2D Vector2D::operator-() const
{
	return { -m_x, -m_y };
}

bool Vector2D::operator==(const Vector2D& p) const
{
	return (m_x == p.m_x) && (m_y == p.m_y);
}
