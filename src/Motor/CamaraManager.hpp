#pragma once
#include <Motor/Camara.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class CamaraManager {
public:
	explicit CamaraManager() = default;
private:
	std::vector<std::shared_ptr<Camara>> lista_camaras;
	std::shared_ptr<Camara> actual;
public:
	void AddCamara(const std::shared_ptr<Camara>& camara);
	void SetCamara(int id);
	void Update(sf::RenderWindow& ven);
	[[nodiscard]] Camara& GetCamara(const int id) const {
		return *lista_camaras[id];
	};
	[[nodiscard]] std::vector<std::shared_ptr<Camara>> GetCamaraLista() const {
		return lista_camaras;
	};
};