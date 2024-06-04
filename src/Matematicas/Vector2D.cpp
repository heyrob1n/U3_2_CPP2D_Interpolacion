#include "Vector2D.hpp"
#include <cmath>
Vector2D::Vector2D(float x, float y)
:x{x},y{y}{};

float Vector2D::length()
{
	return sqrtf((x*x)+(y*y));
};
float Vector2D::magnitud()
{
	return this->length();
};
Vector2D& Vector2D::normalizacion()
{
	float mag = length();
	x /= mag;
	y /=mag;
	return *this;
};
Vector2D& Vector2D::scale(float s)
{
	x*=s;
	y*=s;
	return *this;
};
Vector2D& Vector2D::add(const Vector2D& v)
{
	x+=v.x;
	y+=v.y;
	return *this;
};
float Vector2D::distancia(const Vector2D& v)
{
	return sqrtf((v.x-x)*(v.x-x) + (v.y-y)*(v.y-y));
}
bool Vector2D::operator==(const Vector2D& rhs) const
{
	return (x==rhs.x) && (y==rhs.y);
};
Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	return Vector2D(x+rhs.x,y+rhs.y);
};
Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	return Vector2D(x-rhs.x,y-rhs.y);
};
void Vector2D::operator+=(const Vector2D& rhs)
{
	x+=rhs.x;
	y+=rhs.y;
}
void Vector2D::operator-=(const Vector2D& rhs)
{
	x-=rhs.x;
	y-=rhs.y;
}
std::ostream& operator<<(std::ostream& os, const Vector2D& vect)
{
	os <<"( "<<vect.x <<" , "<<vect.y<<" )"<<std::endl;
	return os;
}
Vector2D Vector2D::forward(float angulo_deg)
{
	return Vector2D(sin(angulo_deg),cos(angulo_deg));
};
Vector2D Vector2D::LERP(const Vector2D& p, float t) {
	float tm1 = (1 - t);
	return (Vector2D) { tm1* x + t * p.x, tm1* y + t * p.y };
};
Vector2D Vector2D::LERPCuadrada(const Vector2D& p1, const Vector2D& p2, float t) {
	//pr = p0 (1-t)(1-t)+2p1t(1-t)+p2t 2
	float tm1 = 1 - t;
	float tm12 = tm1 * tm1;
	float t2 = t * t;

	return Vector2D{
		tm12 * x + 2 * tm1 * t * p1.x + t2 * p2.x,
		tm12 * y + 2 * tm1 * t * p1.y + t2 * p2.y
	};
};

Vector2D Vector2D::LERPCubica(const Vector2D& p1, const Vector2D& p2, float t) {
	//pr = p0 (1-t)(1-t)+2p1t(1-t)+p2t 2
	float tm1 = 1 - t;
	float tm13 = tm1 * tm1;
	float t2 = t * t;

	return Vector2D{
		tm13 * x + 2 * tm1 * t * p1.x + t2 * p2.x,
		tm13 * y + 2 * tm1 * t * p1.y + t2 * p2.y
	};
};


