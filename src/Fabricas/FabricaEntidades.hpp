//
// Created by Omar Zamarrón on 28/02/24.
//

#pragma once
#include <Entes/Entidad.hpp>
#include <map> //tabla hash
#include <vector> //linked list
#include <memory> //shared_ptr

//resolver definicion circular
enum class Tags;
class Entidad;
//alias
typedef std::vector<std::shared_ptr<Entidad>> ListaEntidades;
typedef std::map<Tags,ListaEntidades> HashEntidades;

class FabricaEntidades
{
 public:
	FabricaEntidades()=default;

 public:
	std::shared_ptr<Entidad> AddEntidades(const Tags& tag);
	ListaEntidades &GetEntidades();
	ListaEntidades &GetEntidades(const Tags &tag);

	void Update();

 private:
	ListaEntidades todas_entidades;
	ListaEntidades cola_entidades;
	HashEntidades has_entidades;
	size_t num_entidades{0};

};
