//
// Created by Omar Zamarrón on 06/03/24.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <Matematicas/Vector2D.hpp>


class CCirculo
{
 public:
	CCirculo(float radio);
	CCirculo(float radio, int vertices, const sf::Color &fill, const sf::Color &contorno, float thickness);
 public:
	sf::CircleShape fig;
	int vertices;
};

class CNombre
{
 public:
	CNombre(const std::string &nom);
 public:
	std::string nombre;
};

class CTransforme
{
 public:
	CTransforme()=default;
	CTransforme(const Vector2D &pos, const Vector2D &vel,const float ang);
 public:
	Vector2D posicion;
	Vector2D velocidad;
	float angulo;
};

class CInput
{
 public:
	bool ARRIBA,ABAJO,IZQUIERDA,DERECHA,DISPARO;
	CInput();
};

class CTimer
{
 public:
	CTimer(const int max);
 public:
	int max_frames;
	int curr_frames;

};
class CDestino
{
 public:
	explicit CDestino(const Vector2D &target);
 public:
	Vector2D destino;
};
class CSprite {
public:
	CSprite(const std::string& direccion_imagen);
	CSprite(const std::string& direccion_imagen,
		int x0, int y0, int w, int h, float scale = 1.0);
public:
	sf::Sprite sprite;
private:
	sf::Texture img;
};
