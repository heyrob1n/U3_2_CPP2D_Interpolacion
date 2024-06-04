//
// Created by Omar Zamarrón on 06/03/24.
//

#pragma once
#include <SFML/Graphics.hpp>

class MouseListener
{
 public:
	static MouseListener& Get();
	static float GetX() {return Get().mouse_x;};
	static float GetY() {return Get().mouse_y;};
	static bool isPressed(const sf::Mouse::Button &boton);
	static void catchEvents(const sf::Event &evento);
	static void Destruir();

 private:
	MouseListener();
 private:
	static MouseListener *intancia;
	float mouse_x;
	float mouse_y;
	bool mouse_btnmid;
	bool mouse_btnizq;
	bool mouse_btnder;

};
