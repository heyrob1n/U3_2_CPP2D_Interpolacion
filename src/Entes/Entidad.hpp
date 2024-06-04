//
// Created by Omar Zamarrón on 28/02/24.
//

#pragma once
#include <Componentes/Componentes.hpp>
#include <SFML/Graphics.hpp>
#include <Fabricas/FabricaEntidades.hpp>
#include <memory>
enum class Tags
{
	player=0xAAA,
	enemigo,
	balas,
	particulas,
	Default
};
class Entidad
{
 private:
	Entidad(const Tags &tag,size_t id);
	friend class FabricaEntidades;
 public:
	std::shared_ptr<CNombre> cnombre;
	std::shared_ptr<CCirculo> cfigura;
	std::shared_ptr<CTransforme> ctransform;
	std::shared_ptr<CInput> cinput;
	std::shared_ptr<CTimer> ctiempo;
	std::shared_ptr<CTimer> cfirerate;
	std::shared_ptr<CDestino> cdestino;
	std::shared_ptr<sf::RectangleShape> linea;
	std::shared_ptr<CSprite> avatar;

	//Dimensiones
	float radio;
	float width;
	float height;
	float escala;

 public:
	void Destruir();
	[[nodiscard]] bool EstaVivo() const {return esta_vivo;};
	[[nodiscard]] Tags GetTag() const {return e_tag;};
	void InitEntidad();
	void SetPosicion(const Vector2D &pos);
	void OnRender(sf::RenderWindow &ventana);
	void OnUpdate();
	Vector2D CalcularPuntoCoor(int index);
 private:
	size_t e_id;
	Vector2D centro;
	bool esta_vivo;
	Tags e_tag=Tags::Default;
};
