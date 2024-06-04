#include "Camara.hpp"
Camara::Camara(float x, float y, float width, float height) :camara_view_width((int)width), camara_view_height((int)height) {
	transformada = std::make_shared<CTransforme>(Vector2D(x, y), Vector2D(0.f, 0.f), 0.f);
	camara_area = std::make_shared<sf::View>(sf::FloatRect(x, y, (float)camara_view_width, (float)camara_view_height));
	lock = false;
	obj_lock = nullptr;
}
Camara::Camara(Vector2D centro, Vector2D dimensiones) :camara_view_width((int)dimensiones.x), camara_view_height((int)dimensiones.y) {
	transformada = std::make_shared<CTransforme>(centro, Vector2D(0.f, 0.f), 0.f);
	camara_area = std::make_shared<sf::View>(sf::Vector2f(centro.x, centro.y), sf::Vector2f(dimensiones.x, dimensiones.y));
	obj_lock = nullptr;
	lock = false;
}
void Camara::AddObjLock(const std::shared_ptr<Entidad>& ref) {
	lock = true;
	obj_lock = ref;
}

CamaraLock::CamaraLock(float x, float y, float width, float height) :Camara(x, y, width, height) {};
CamaraLock::CamaraLock(Vector2D centro, Vector2D dimensiones) : Camara(centro, dimensiones) {};

void CamaraLock::Update() {
	if (!obj_lock) {
		lock = false;
		return;
	}
	Vector2D pos = obj_lock->ctransform->posicion;
	transformada->posicion = pos;
	camara_area->setCenter(pos.x, pos.y);
}

CamaraSide::CamaraSide(float x, float y, float width, float height) :Camara(x, y, width, height) {};
CamaraSide::CamaraSide(Vector2D centro, Vector2D dimensiones) : Camara(centro, dimensiones) {};
void CamaraSide::Update() {
	if (!obj_lock) {
		lock = false;
		return;
	}
	Vector2D pos = obj_lock->ctransform->posicion;
	transformada->posicion = pos;
	camara_area->setCenter(pos.x, pos.y);
}
CamaraFollowLerp::CamaraFollowLerp(float x, float y, float width, float height)
	: Camara(x, y, width, height), total_frames{90}, current_frames{ 0 }, p0{ x, y } {}

CamaraFollowLerp::CamaraFollowLerp(Vector2D centro, Vector2D dimensiones)
	: Camara(centro, dimensiones), total_frames{ 90 }, current_frames{ 0 }, p0{ centro } {}
void CamaraFollowLerp::Update()
{
	if (!obj_lock)
	{
		current_frames = 0;
		p0 = transformada->posicion;
		return;
	}

	float dist = transformada->posicion.distancia(obj_lock->ctransform->posicion);
	if (dist <= 0.01 || current_frames == total_frames)
	{
		current_frames = 0;
		p0 = transformada->posicion;
	}

	float time = static_cast<float>(current_frames) / static_cast<float>(total_frames);
	transformada->posicion = p0.LERP(obj_lock->ctransform->posicion, time);
	camara_area->setCenter(transformada->posicion.x, transformada->posicion.y);
	current_frames++;
}
