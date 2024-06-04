//
// Created by Omar Zamarrón on 28/02/24.
//
#include "Entidad.hpp"
#define M_PI 3.1415
#include<iostream>

Entidad::Entidad(const Tags &tag,size_t id)
:e_id{id},esta_vivo{true},e_tag{tag}
{};
void Entidad::InitEntidad()
{
	/*Función que se llama despues de crear los componentes y antes de SetPosición*/
	if(cfigura)
	{
		linea = std::make_shared<sf::RectangleShape>(sf::Vector2(cfigura->fig.getRadius(),2.f));
		linea->setPosition(ctransform->posicion.x,ctransform->posicion.y);
	}
	if (avatar) {
		radio = cfigura->fig.getRadius();
		height = avatar->sprite.getTextureRect().height;
		width = avatar->sprite.getTextureRect().width;
		escala = avatar->sprite.getScale().x;
		avatar->sprite.setPosition(ctransform->posicion.x - (width / 2) * escala, ctransform->posicion.y - (height / 2) * escala);
		avatar->sprite.setOrigin(radio, radio);
	}

};
void Entidad::Destruir()
{
	esta_vivo= false;
}
void Entidad::SetPosicion(const Vector2D& pos)
{
	//si existe
	if(cfigura)
	{
		cfigura->fig.setPosition(pos.x, pos.y);
		if(linea)
		{
			linea->setPosition(pos.x, pos.y);
			Vector2D punto = CalcularPuntoCoor(1);
			float ang = atan2(punto.y - pos.y, punto.x - pos.x) * 180 / M_PI;
			linea->setRotation(ang);
		}
	}
	if (avatar) {
		avatar->sprite.setPosition(pos.x - (width / 2) * escala, pos.y - (height / 2) * escala);
	}
}
Vector2D Entidad::CalcularPuntoCoor(int index)
{
	sf::Vector2f p = cfigura->fig.getTransform().transformPoint(
		cfigura->fig.getPoint(index));
	return {p.x,p.y};
}
void Entidad::OnRender(sf::RenderWindow  &ventana)
{
	//talvez en otro método la rotacion
	cfigura->fig.setRotation(ctransform->angulo);
	if(cfigura)
		ventana.draw(cfigura->fig);
	if(linea)
		ventana.draw(*linea);
	if (avatar)
		ventana.draw(avatar->sprite);
}
void Entidad::OnUpdate()
{
	if(ctiempo)
	{
		if(ctiempo->curr_frames >=ctiempo->max_frames)
			Destruir();
		ctiempo->curr_frames++;
	}
	if(e_tag == Tags::particulas)
	{
		sf::Color c = cfigura->fig.getFillColor();
		sf::Color co = cfigura->fig.getOutlineColor();
		float  poralpha = 255-((ctiempo->curr_frames/(float)ctiempo->max_frames)*255.f);
		c.a= poralpha;
		co.a = poralpha;
		cfigura->fig.setFillColor(c);
		cfigura->fig.setOutlineColor(co);
		ctransform->angulo+=5;
	}

}
