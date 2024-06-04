#pragma once
#include <iostream>

class Vector2D
{
 public:
	Vector2D()=default;
	Vector2D(float x, float y);

	float length();
	float magnitud();
	Vector2D& normalizacion();
	float distancia(const Vector2D &v);

	Vector2D& scale(float s);
	Vector2D& add(const Vector2D &v);

	Vector2D forward(float angulo_deg);
	Vector2D LERP(const Vector2D& p, float t);

	// Realiza una interpolación lineal entre este vector y otro vector p dado un valor t
	Vector2D LERP(const Vector2D& p, float t);
	// Realiza una interpolación cuadrática entre este vector y dos vectores p1 y p2 dado un valor t
	Vector2D LERPCuadrada(const Vector2D& p1, const Vector2D& p2, float t);
	// Operador de comparación de igualdad
	bool operator== (const Vector2D &rhs) const;
	Vector2D LERPCubica(const Vector2D& p1, const Vector2D& p2, float t);
	// Operador de comparación de igualdad
	bool operator== (const Vector2D& rhs) const;


	Vector2D operator+(const Vector2D &rhs) const;
	Vector2D operator-(const Vector2D &rhs) const;
	void operator+=(const Vector2D &rhs);
	void operator-=(const Vector2D &rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vect);

 public:
	float x;
	float y;

};
