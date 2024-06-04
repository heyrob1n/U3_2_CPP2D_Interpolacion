#pragma once
#include <Matematicas/Vector2D.hpp>
#include <Componentes/Componentes.hpp>
#include <Entes/Entidad.hpp>
#include <memory>
#include <SFML/Graphics.hpp>

class Camara {
public:
	Camara(float x, float y, float width, float height);
	Camara(Vector2D centro, Vector2D dimensiones);
	std::shared_ptr<CTransforme> transformada;
	int camara_view_width;
	int camara_view_height;
	bool lock;
protected:
	std::shared_ptr<sf::View> camara_area;
	std::shared_ptr<Entidad> obj_lock;
public:
	sf::View& GetView()const { return *camara_area;};
	void AddObjLock(const std::shared_ptr<Entidad>& ref);
	virtual void Update() {};
};

class CamaraLock : public Camara {
public:
	CamaraLock(float x, float y, float width, float height);
	CamaraLock(Vector2D centro, Vector2D dimensiones);
	void Update() override;
};
class CamaraSide : public Camara {
public:
	CamaraSide(float x, float y, float width, float height);
	CamaraSide(Vector2D centro, Vector2D dimensiones);
	void Update() override;
};

class CamaraFollowLerp : public Camara {
public:
	CamaraFollowLerp(float x, float y, float width, float height);
	CamaraFollowLerp(Vector2D centro, Vector2D dimensiones);
	void Update() override;

private:
	int total_frames;
	int current_frames;
	Vector2D p0;
};
