//
// Created by Omar Zamarrón on 05/03/24.
//

#include "KeyListener.hpp"
#include <iostream>

// inicializar el objeto en nulo
KeyListener* KeyListener::instancia = nullptr;
KeyListener::KeyListener()
{
	keys = new bool[sf::Keyboard::KeyCount]();
}
KeyListener& KeyListener::Get()
{
	if(!instancia)
		instancia = new KeyListener();
	return *instancia;
}

void KeyListener::catchEvents(const sf::Event& eventos)
{
	if(eventos.type == sf::Event::KeyPressed)
		Get().keys[eventos.key.scancode] = true;
	if(eventos.type == sf::Event::KeyReleased)
		Get().keys[eventos.key.scancode] = false;
}
bool KeyListener::isPressed(const sf::Keyboard::Scancode key)
{
	return Get().keys[key];
}
bool KeyListener::isReleased(const sf::Keyboard::Scancode key)
{
	return !Get().keys[key];
}
void KeyListener::Destruir()
{
	std::cout<<"BORRANDO KEYLISTENER"<<std::endl;
	delete[] Get().keys;
	delete Get().instancia;
}

