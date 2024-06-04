//
// Created by Omar Zamarrón on 28/02/24.
//

#include "FabricaEntidades.hpp"

std::shared_ptr<Entidad> FabricaEntidades::AddEntidades(const Tags& tag)
{
	//crear una objeto entidad con el constructor privado (se usa new como rawpointer)
	auto nuevo = std::shared_ptr<Entidad>(new Entidad(tag,num_entidades++));
	//meter el nuevo entidad en la cola de espera hasta que sea seguro guardar
	cola_entidades.push_back(nuevo);
	//regresar la entidad
	return nuevo;
}
ListaEntidades& FabricaEntidades::GetEntidades()
{
	return todas_entidades;
}
ListaEntidades& FabricaEntidades::GetEntidades(const Tags& tag)
{
	return has_entidades[tag];
}
void FabricaEntidades::Update()
{
	//agregar entidades disponibles en la cola
	for(auto &e: cola_entidades)
	{
		todas_entidades.push_back(e);
		has_entidades[e->GetTag()].push_back(e);
	}

	for(auto &e:todas_entidades)
		e->OnUpdate();
	//eliminar las entidades marcadas como muertos
	// de la tabla hash
	for(auto &e:todas_entidades)
	{
		has_entidades[e->GetTag()].erase(std::remove_if(
			has_entidades[e->GetTag()].begin(),
			has_entidades[e->GetTag()].end(),
			[](std::shared_ptr<Entidad>& x)
			{
				return !x->EstaVivo();
			}
		),has_entidades[e->GetTag()].end());
	}

	// eliminar de la lista de todos
	todas_entidades.erase(std::remove_if(
		todas_entidades.begin(),
		todas_entidades.end(),
		[](std::shared_ptr<Entidad>& x)
		{
			return !x->EstaVivo();
		}),todas_entidades.end());

	//limpiar la cola
	cola_entidades.clear();
}
