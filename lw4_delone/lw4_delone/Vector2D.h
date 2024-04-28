#pragma once

class Vector2D
{
public:
	Vector2D(double x = -1, double y = -1);
	double m_x;
	double m_y;
	Vector2D operator+(const Vector2D& p) const;
	Vector2D operator-(const Vector2D& p) const;
	Vector2D operator-() const;
	bool operator==(const Vector2D& p) const;
};
