//
// Created by Omar Zamarrón on 06/03/24.
//

#include "MouseListener.hpp"
#include <iostream>
MouseListener* MouseListener::intancia = nullptr;
MouseListener::MouseListener()
{
	mouse_x=0;
	mouse_y=0;
	mouse_btnder= false;
	mouse_btnizq= false;
	mouse_btnmid = false;
};

MouseListener &MouseListener::Get()
{
	if(!intancia)
		intancia = new MouseListener();
	return *intancia;
}
void MouseListener::catchEvents(const sf::Event& evento)
{

	if(evento.type == sf::Event::EventType::MouseMoved)
	{
		Get().mouse_x = (float)evento.mouseMove.x;
		Get().mouse_y = (float)evento.mouseMove.y;
	}

	if(evento.type == sf::Event::EventType::MouseButtonPressed)
	{
		switch (evento.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
			Get().mouse_btnizq =true;
			break;
		case sf::Mouse::Button::Right:
			Get().mouse_btnder = true;
			break;
		case sf::Mouse::Button::Middle:
			Get().mouse_btnmid = true;
			break;
		default:
			break;
		}
	}
	else if(evento.type == sf::Event::EventType::MouseButtonReleased)
	{
		switch (evento.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
			Get().mouse_btnizq = false;
			break;
		case sf::Mouse::Button::Right:
			Get().mouse_btnder = false;
			break;
		case sf::Mouse::Button::Middle:
			Get().mouse_btnmid = false;
			break;
		default:
			break;
		}
	}

}
bool MouseListener::isPressed(const sf::Mouse::Button& boton)
{
	bool activo = false;
	switch (boton)
	{
	case sf::Mouse::Button::Left:
		activo= Get().mouse_btnizq;
		break;
	case sf::Mouse::Button::Right:
		activo= Get().mouse_btnder;
		break;
	case sf::Mouse::Button::Middle:
		activo= Get().mouse_btnmid;
		break;
	default:
		break;
	}

	return activo;
}
void MouseListener::Destruir()
{
	std::cout<<"BORRAR MOUSELISTENER"<<std::endl;
	delete intancia;
}
