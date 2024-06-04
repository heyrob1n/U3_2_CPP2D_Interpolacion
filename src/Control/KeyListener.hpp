//
// Created by Omar Zamarrón on 05/03/24.
//

#pragma once

#include <SFML/Graphics.hpp>

class KeyListener
{
 private:
	KeyListener();

 public:
	//eliminar la copia y asignacion
	KeyListener(const KeyListener&) = delete;
	KeyListener& operator=(const KeyListener&) = delete;

	static void Destruir();
	static KeyListener &Get();
 public:


	static void catchEvents(const sf::Event &eventos);
	static bool isPressed(const sf::Keyboard::Scancode key);
	static bool isReleased(const sf::Keyboard::Scancode key);

 private:
	static KeyListener *instancia;
	bool *keys;

};
