//
// Created by Omar Zamarrón on 06/03/24.
//

#include "Componentes.hpp"
CCirculo::CCirculo(float radio)
:fig(radio)
{}
CCirculo::CCirculo(float radio, int vertices, const sf::Color& fill, const sf::Color& contorno, float thickness)
:fig(radio,vertices),vertices{vertices}
{
	this->fig.setFillColor(fill);
	this->fig.setOutlineColor(contorno);
	this->fig.setOutlineThickness(thickness);
	this->fig.setOrigin(radio,radio);
};
CNombre::CNombre(const std::string &nom)
:nombre{nom}{};
CTransforme::CTransforme(const Vector2D& pos, const Vector2D& vel,const float ang)
: posicion{pos},velocidad{vel},angulo{ang}
{};
CInput::CInput()
:ARRIBA{ false},ABAJO{ false},
IZQUIERDA{ false},DERECHA{ false},DISPARO{false}
{}
CTimer::CTimer(const int max)
:max_frames{max},curr_frames{0}
{}
CDestino::CDestino(const Vector2D& target)
:destino{target}
{}

CSprite::CSprite(const std::string& direccion_imagen) {
	if (!img.loadFromFile(direccion_imagen)) {
		std::cout << "no se pudo cargar la imagen\n";
	}
	else {
		img.setSmooth(true);
		sprite.setTexture(img);
	}
}
CSprite::CSprite(const std::string& direccion_imagen,
		int x0, int y0, int w, int h, float scale) {
	if (!img.loadFromFile(direccion_imagen)) {
		std::cout<<"no se pudo cargar la imagen\n";
	}
	else {
		img.setSmooth(true);
		sprite.setTexture(img);
		sprite.setTextureRect(sf::IntRect(x0, y0, w, h));
		sprite.setScale(scale, scale);
	}
}
