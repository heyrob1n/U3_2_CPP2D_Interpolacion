//
// Created by Omar Zamarrón on 21/02/24.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <Entes/Entidad.hpp>
#include <Fabricas/FabricaEntidades.hpp>
#include <Motor/CamaraManager.hpp>
class GameEngine
{
 public:
	GameEngine() = default;
	~GameEngine();
	int MainLoop();
	void OnInit();
 private:
	void OnInputs();
	void OnUpdate();
	void OnRender();
	void SystemaMouseTracking();
	void SystemaMovimiento();
	void SystemaDisparos();
	void SpawnBala(std::shared_ptr<Entidad> quien, const Vector2D &target);
	void SpawnEnemigo();
	void CheckColision();
	void SpawnOnDeathParticulas(const std::shared_ptr<Entidad> &enemigo);
 private:
	float NumeroRandom(float min, float max);
	/*void SpawnJugador();

	*/
 public:
	std::vector<std::shared_ptr<Entidad>> lista_enemigos;
	FabricaEntidades fabrica;
 private:
	unsigned int current_frame{};
	bool m_running{};
	bool m_enpausa{};
	sf::RenderWindow *ventana= nullptr;
	//sf::View camara;
	CamaraManager manejador_camaras;
	std::shared_ptr<Entidad> jugador;
	int max_enemigos;
public:
	//curva bezier
	sf::Vertex puntos[4];
	sf::CircleShape curva;
	Vector2D curva_pos;
	int frames_actuales = 0;
	int frames_totales = 180;


};
