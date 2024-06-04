#include "CamaraManager.hpp"
void CamaraManager::SetCamara(int id) {
	if (id > lista_camaras.size() - 1)
		return;
	actual = lista_camaras[id];
}
void CamaraManager::AddCamara(const std::shared_ptr<Camara>& camara) {
	lista_camaras.push_back(camara);
}
void CamaraManager::Update(sf::RenderWindow& ven) {

	actual->Update();
	ven.setView(actual->GetView());
}