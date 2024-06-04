//
// Created by Omar Zamarrón on 21/02/24.
//
#include "GameEngine.hpp"
#include <iostream>
#include <GLOBALS.hpp>
#include <Matematicas/Vector2D.hpp>
#include <Control/KeyListener.hpp>
#include <Control/MouseListener.hpp>
#include <Motor/Camara.hpp>
#define M_PI 3.1415
GameEngine::~GameEngine()
{
	std::cout<<"Borrando Ventana\n";
	MouseListener::Get().Destruir();
	KeyListener::Get().Destruir();
	delete ventana;
};
void GameEngine::OnInit()
{
	sf::ContextSettings videoSettings;
	videoSettings.antialiasingLevel = 10;
	ventana = new sf::RenderWindow(
		sf::VideoMode(1080u, 768u, 64u),
		"SFML Engine", sf::Style::Close, videoSettings);

	// Calculamos el centro de la ventana como punto inicial para las cámaras
	Vector2D center(0+1080/2,0+768/2);
	Vector2D dimensions(1080, 768);

	// Añadimos diferentes tipos de cámaras al manejador de cámaras
	manejador_camaras.AddCamara(std::make_shared<Camara>(center, dimensions));
	manejador_camaras.AddCamara(std::make_shared<CamaraLock>(center, dimensions));
	manejador_camaras.AddCamara(std::make_shared<CamaraFollowLerp>(center, dimensions));

	// Establecemos la cámara inicial
	manejador_camaras.SetCamara(0);
	// Configuración del límite de FPS
	ventana->setFramerateLimit(60);

	//jugador
	auto player = fabrica.AddEntidades(Tags::player);
	player->cnombre = std::make_shared<CNombre>("Player");
	player->ctransform =std::make_shared<CTransforme>(Vector2D{300,200},Vector2D{0,0},0);
	player->cfigura = std::make_shared<CCirculo>(40.f,3,sf::Color::Magenta,sf::Color::Yellow,3.f);
	player->cinput = std::make_shared<CInput>();
	
	player->SetPosicion(player->ctransform->posicion);

	player->avatar = std::make_shared<CSprite>(ROOT_DIR+ "/assets/sprites/heroe/gato_sheet.png", 0, 0, 400, 520, 0.25);

	player->cfirerate = std::make_shared<CTimer>(30);
	player->InitEntidad();
	jugador = player;
	max_enemigos = 10;
	m_running=true;
	m_enpausa = false;
	//curva bezier
	// Configurar puntos con sus posiciones y colores
	puntos[0].position = sf::Vector2f(50, 300);
	puntos[0].color = sf::Color::Blue;

	puntos[1].position = sf::Vector2f(200, 50);
	puntos[1].color = sf::Color::Blue;

	puntos[2].position = sf::Vector2f(200, 50); // Puede ser que este punto sea igual al anterior
	puntos[2].color = sf::Color::Red;

	puntos[3].position = sf::Vector2f(400, 300);
	puntos[3].color = sf::Color::Red;

	// Suponiendo que `curva` es un objeto de tipo sf::CircleShape
	sf::CircleShape curva;

	// Configurar el objeto curva
	curva.setPosition(puntos[0].position.x, puntos[0].position.y); // Establecer la posición de la curva
	curva_pos = { puntos[0].position.x, puntos[0].position.y }; // Guardar la posición de la curva
	curva.setRadius(10); // Establecer el radio del círculo
	curva.setOrigin(10.f, 10.f); // Establecer el origen del círculo
	curva.setFillColor(sf::Color::Cyan); // Establecer el color de relleno

};
int GameEngine::MainLoop()
{
	while(m_running && ventana->isOpen())
	{
		OnUpdate();
		OnInputs();
		OnRender();
		current_frame++;
	}
	return 0;
};
void GameEngine::OnInputs()
{
	// aqui no se implementa logica
	// solo las variables que se van usar (true o false)
	sf::Event eventos;
	while(ventana->pollEvent(eventos))
	{
		KeyListener::Get().catchEvents(eventos);
		MouseListener::Get().catchEvents(eventos);
		if (eventos.type == sf::Event::Closed)
			ventana->close();
		if(KeyListener::Get().isPressed(sf::Keyboard::Scancode::D))
		{
			jugador->cinput->DERECHA=true;
		}
		else if(KeyListener::Get().isReleased(sf::Keyboard::Scancode::D))
		{
			jugador->cinput->DERECHA = false;
		}
		if(KeyListener::Get().isPressed(sf::Keyboard::Scancode::A))
		{
			jugador->cinput->IZQUIERDA=true;
		}
		else if(KeyListener::Get().isReleased(sf::Keyboard::Scancode::A))
		{
			jugador->cinput->IZQUIERDA = false;
		}
		if(KeyListener::Get().isPressed(sf::Keyboard::Scancode::W))
		{
			jugador->cinput->ARRIBA=true;
		}
		else if(KeyListener::Get().isReleased(sf::Keyboard::Scancode::W))
		{
			jugador->cinput->ARRIBA = false;
		}
		if(KeyListener::Get().isPressed(sf::Keyboard::Scancode::S))
		{
			jugador->cinput->ABAJO=true;
		}
		else if(KeyListener::Get().isReleased(sf::Keyboard::Scancode::S))
		{
			jugador->cinput->ABAJO = false;
		}

		if(KeyListener::Get().isPressed(sf::Keyboard::Scancode::Space))
		{
			jugador->cinput->DISPARO = true;
		}
		else if(KeyListener::Get().isReleased(sf::Keyboard::Scancode::Space))
		{
			jugador->cinput->DISPARO = false;
			jugador->cfirerate->curr_frames=0;
		}
		if (KeyListener::Get().isPressed(sf::Keyboard::Scancode::K)) {
			//lock al jugador
			manejador_camaras.GetCamara(2).AddObjLock(jugador);
			manejador_camaras.SetCamara(2);
		}
		else if (KeyListener::Get().isPressed(sf::Keyboard::Scancode::L)) {
			manejador_camaras.SetCamara(0);
		}
		else if (KeyListener::Get().isPressed(sf::Keyboard::Scancode::J)) {
			//SideScroller
			manejador_camaras.GetCamara(3).AddObjLock(jugador);
			manejador_camaras.SetCamara(3);
		}
	}
};
void GameEngine::OnUpdate()
{
	fabrica.Update();
	if(!m_enpausa)
	{
		// sistema de respawn player
		// sistema de respawn enemigo
		SpawnEnemigo();
		// sistema movimiento
		SystemaMovimiento();
		// sistema de mouse tracking
		SystemaMouseTracking();
		SystemaDisparos();
		// sistema colision
		CheckColision();
		//Sistema movimienot
		SystemaMovimiento();
		//sistema colision
		CheckColision();
	}
	//actualizar el render de la camara
	manejador_camaras.Update(*ventana);
	//Curva Bézier
		if (frames_actuales > frames_totales) {
			frames_actuales = 0;
		}

	float t = static_cast<float>(frames_actuales) / static_cast<float>(frames_totales);
	Vector2D p1 = { puntos[2].position.x, puntos[2].position.y };
	Vector2D p2 = { puntos[3].position.x, puntos[3].position.y };
	Vector2D pr = curva_pos.LERPCuadrada(p1, p2, t);
	curva.setPosition(pr.x, pr.y);
	frames_actuales++;
};
void GameEngine::OnRender()
{
	//limpiar frame
	ventana->clear();
	//pintar en el frame
	for(const auto& e : fabrica.GetEntidades(Tags::enemigo))
	{
		e->OnRender(*ventana);
	}

	for(const auto& b: fabrica.GetEntidades(Tags::balas))
	{
		b->OnRender(*ventana);
	}


	//particulas
	for(const auto &p : fabrica.GetEntidades(Tags::particulas))
		p->OnRender(*ventana);

	jugador->OnRender(*ventana);

	sf::CircleShape mousepoint(10);
	mousepoint.setOrigin(10,10);
	mousepoint.setPosition(MouseListener::Get().GetX(),MouseListener::Get().GetY());
	// Dibujar el punto del mouse
	ventana->draw(mousepoint);
	// Curva Bézier
	ventana->draw(puntos, 4, sf::Lines); // Dibujar línea con 4 puntos
	ventana->draw(curva); // Dibujar curva circular
	//mostrar frame
	ventana->display();
}
void GameEngine::SystemaMovimiento()
{
	jugador->ctransform->velocidad ={0.f,0.f};

	if(jugador->cinput->ARRIBA)
		jugador->ctransform->velocidad.y=-5;
	else if(jugador->cinput->ABAJO)
		jugador->ctransform->velocidad.y=5;
	if(jugador->cinput->DERECHA)
		jugador->ctransform->velocidad.x=5;
	else if(jugador->cinput->IZQUIERDA)
		jugador->ctransform->velocidad.x=-5;

	//update de posición
	jugador->ctransform->posicion.x += jugador->ctransform->velocidad.x;
	jugador->ctransform->posicion.y += jugador->ctransform->velocidad.y;
	jugador->SetPosicion(jugador->ctransform->posicion);

	//enemigos
	for(const auto& e:fabrica.GetEntidades(Tags::enemigo))
	{
		if(e->ctransform->posicion.x <= 10)
			e->ctransform->velocidad.x = -e->ctransform->velocidad.x;
		if(e->ctransform->posicion.x >= manejador_camaras.GetCamara(0).camara_view_width)
			e->ctransform->velocidad.x = -e->ctransform->velocidad.x;

		if(e->ctransform->posicion.y <= 10)
			e->ctransform->velocidad.y = -e->ctransform->velocidad.y;
		if(e->ctransform->posicion.y >= manejador_camaras.GetCamara(0).camara_view_height)
			e->ctransform->velocidad.y = -e->ctransform->velocidad.y;


		//sin quebrarnos la cabeza al nacer el enemigo que se le asigne
		// al azar un valor de velocidad en x y/o en y
		e->ctransform->posicion.x += e->ctransform->velocidad.x;
		e->ctransform->posicion.y += e->ctransform->velocidad.y;
		e->SetPosicion(e->ctransform->posicion);
	}

	for(const auto&p :fabrica.GetEntidades(Tags::particulas))
	{
		p->ctransform->posicion.x += -p->ctransform->velocidad.x;
		p->ctransform->posicion.y += -p->ctransform->velocidad.y;
		p->SetPosicion(p->ctransform->posicion);
	}

	//balas
	for(const auto& b: fabrica.GetEntidades(Tags::balas))
	{
		b->ctransform->posicion.x += b->ctransform->velocidad.x;
		b->ctransform->posicion.y += b->ctransform->velocidad.y;
		b->SetPosicion(b->ctransform->posicion);
	}
}
void GameEngine::SystemaMouseTracking()
{
	//normalizar
	Vector2D mouseNorm = (
		Vector2D(MouseListener::Get().GetX(),MouseListener::Get().GetY()) - jugador->ctransform->posicion)
			.normalizacion();
	float angmouse = atan2(mouseNorm.y,mouseNorm.x);
	//compensamos 30 grados por el angulo del vertice con respecto al centro
	jugador->ctransform->angulo = angmouse*(180.f/M_PI) -30;

}
void GameEngine::SpawnBala(std::shared_ptr<Entidad> quien, const Vector2D& target)
{
	//spawniar la bala
	auto bala = fabrica.AddEntidades(Tags::balas);
	bala->ctransform = std::make_shared<CTransforme>(quien->CalcularPuntoCoor(1),Vector2D(5,5),0);
	bala->cfigura = std::make_shared<CCirculo>(10,8,sf::Color::Green,
		sf::Color::Red,2);
	bala->ctiempo = std::make_shared<CTimer>(60);
	//bala->InitEntidad();
	bala->SetPosicion(bala->ctransform->posicion);
	bala->cdestino = std::make_shared<CDestino>(target);

	//crear las velocidades
	Vector2D currpos = (bala->ctransform->posicion - target);
	float ang_bm = (float)(atan2(currpos.y,currpos.x));
	Vector2D fwb = Vector2D(-cos(ang_bm),-sin(ang_bm));

	bala->ctransform->velocidad.x *=fwb.x;
	bala->ctransform->velocidad.y *=fwb.y;

}
void GameEngine::SystemaDisparos()
{
	if (jugador->cinput->DISPARO)
	{
		if (jugador->cfirerate->curr_frames == 0)
			SpawnBala(jugador, Vector2D(MouseListener::Get().GetX(), MouseListener::Get().GetY()));
		jugador->cfirerate->curr_frames++;
	}
}

void GameEngine::SpawnEnemigo()
{

	if(fabrica.GetEntidades(Tags::enemigo).size() != max_enemigos)
	{
		float LIMX = manejador_camaras.GetCamara(0).camara_view_width;
		float LIMY = manejador_camaras.GetCamara(0).camara_view_height;
		float radio = NumeroRandom(20, 40);
		float ranx = NumeroRandom(radio / 2, LIMX);
		float rany = NumeroRandom(radio / 2, LIMY);
		float velx = NumeroRandom(-3, 3);
		float vely = NumeroRandom(-3, 3);
		int r = (int)NumeroRandom(0, 255);
		int g = (int)NumeroRandom(0, 255);
		int b = (int)NumeroRandom(0, 255);
		auto enemigo = fabrica.AddEntidades(Tags::enemigo);
		enemigo->ctransform = std::make_shared<CTransforme>(
			Vector2D(ranx, rany), Vector2D(velx, vely), 0);
		enemigo->cfigura = std::make_shared<CCirculo>(radio, 6,
			sf::Color(r, g, b), sf::Color::Red, 4);
		enemigo->SetPosicion(enemigo->ctransform->posicion);
		int numen = rand() % 9;
		enemigo->avatar = std::make_shared<CSprite>(ROOT_DIR + "/assets/sprites/Planets/planet0" + std::to_string(numen) + ".png", 0, 0, 1280, 1280, 0.1);
		enemigo->InitEntidad();
	}

/*#if DEBUG == 1
	std::cout<<"("<<ranx<<", "<<rany<<")"<<std::endl;
#endif*/

}
float GameEngine::NumeroRandom(float min, float max)
{
	return min + ((float)rand()/((float)RAND_MAX))*(max-min);;
}
void GameEngine::CheckColision()
{
	for(const auto &b: fabrica.GetEntidades(Tags::balas))
	{
		for(const auto &e:fabrica.GetEntidades(Tags::enemigo))
		{
			float dist = b->ctransform->posicion.distancia(e->ctransform->posicion);
			if(dist <= e->cfigura->fig.getRadius())
			{
				b->Destruir();
				e->Destruir();
				SpawnOnDeathParticulas(e);
			}
		}
	}
}
void GameEngine::SpawnOnDeathParticulas(const std::shared_ptr<Entidad>& enemigo)
{
	int lados = enemigo->cfigura->fig.getPointCount();
	sf::Color pcolor = enemigo->cfigura->fig.getFillColor();
	sf::Color pbcolor = enemigo->cfigura->fig.getOutlineColor();
	for(int i=0;i<lados;i++)
	{
		Vector2D partPos = enemigo->ctransform->posicion; //enemigo->CalcularPuntoCoor(i);
		Vector2D diffpos = partPos-enemigo->CalcularPuntoCoor(i);
		float ang_bm = (float)(atan2(diffpos.y,diffpos.x));
		Vector2D fwb = Vector2D(-cos(ang_bm),-sin(ang_bm));
		//calcular la velocidad dependiendo del angulo con respecto al centro para irse hacia fuera
		auto particula = fabrica.AddEntidades(Tags::particulas);
		particula->ctransform = std::make_shared<CTransforme>(partPos,fwb,0);
		particula->ctiempo = std::make_shared<CTimer>(40);
		particula->cfigura = std::make_shared<CCirculo>(10,lados,pcolor,pbcolor,4);
		particula->SetPosicion(partPos);
	}

};
