#include "MiGame.h"
#include "Utils.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "Zombie.h"
//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MiGame::MiGame(): Game(sf::VideoMode(800,600,32), "Ejemplo: Obstaculos y paredes", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(24, 8, 0), 60)
{}

MiGame::~MiGame()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

MiGame* MiGame::Singleton()
{
	static MiGame instancia;
	return &instancia;
}

void MiGame::CrearEscena()
{
	sf::Texture* img = &m_ManagerDeImagenes[IDImagen::VehiculoParticula];
	sf::Texture* imgWanderer = &m_ManagerDeImagenes[IDImagen::Wanderer];
	sf::Texture* imgObstaculoCircular = &m_ManagerDeImagenes[IDImagen::ObstaculoCircular];
	sf::Texture* imgObstaculoPared = &m_ManagerDeImagenes[IDImagen::ObstaculoPared];
	float escala = 0.2f;

	b2BodyDef cuerpo;
	cuerpo.type = b2BodyType::b2_dynamicBody;
	b2FixtureDef adorno;
	adorno.restitution = 0.0;
	adorno.isSensor = false;
	adorno.friction = 0.3f;
	adorno.density = 0.01f;//Masa de 26.214399
	b2PolygonShape* pRectangulo = new b2PolygonShape();
	pRectangulo->SetAsBox(img->getSize().x / 2 * escala, img->getSize().y / 2 * escala, b2Vec2(0, 0), 0);
	adorno.shape = pRectangulo;

	cuerpo.position = b2Vec2(100, 100);
	cuerpo.angle = 0;

	m_pAutoFantastico = new Vehiculo(cuerpo, adorno, escala, img);

	m_pAutoFantastico->m_FuerzaSteeringMax = 600;
	m_pAutoFantastico->m_VelocidadMax = 250;


	//////////////////////////////////////////////////
	////// ACTIVANDO LOS STEERING BEHAVIORS //////////
	//////////////////////////////////////////////////

	//m_pAutoFantastico->GetSteeringBehaviors().EvadirParedesOn();
	//m_pAutoFantastico->GetSteeringBehaviors().m_PesoEvadirParedes = 0.5f;// El valor por defecto es 1.0f, este escala el resultado
	//m_pAutoFantastico->GetSteeringBehaviors().EvadirObstaculosOn();		 // de la fuerza de EvadirParedes
	//m_pAutoFantastico->GetSteeringBehaviors().m_PesoEvadirObstaculos = 0.5f;// El valor por defecto es 1.0f, este escala el resultado
	//m_pAutoFantastico->GetSteeringBehaviors().DeambularOn();				// de la fuerza de EvadirParedes

	cuerpo.position = b2Vec2(100, 400);
	m_pWanderer = new Zombie(cuerpo, adorno, escala, imgWanderer,this);
	//new Vehiculo(cuerpo, adorno, escala, imgWanderer);
	//m_pWanderer->m_FuerzaSteeringMax = 600;
	//m_pWanderer->m_VelocidadMax = 100;

	//m_pWanderer->GetSteeringBehaviors().EvadirParedesOn();
	//m_pWanderer->GetSteeringBehaviors().m_PesoEvadirParedes = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
	//m_pWanderer->GetSteeringBehaviors().EvadirObstaculosOn();		 // de la fuerza de EvadirParedes
	//m_pWanderer->GetSteeringBehaviors().m_PesoEvadirObstaculos = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
	//m_pWanderer->GetSteeringBehaviors().DeambularOn();
	//// Descripcion de las paredes y asignacion a SteeringBehaviors: Paredes
	// SE VE MUCHO CODIGO PORQUE DEFINIMOS 4 PAREDES, PERO ES REPETITIVO LO QUE HACE

		//Pared de arriba
		cuerpo.type        = b2BodyType::b2_staticBody;
		adorno.restitution = 0.2f;
		adorno.isSensor    = false;
		adorno.friction    = 0.3f;
		adorno.density     = 0.01f;
		pRectangulo->SetAsBox(400, 10, b2Vec2(0.0f, 0.0f), 0);
		adorno.shape       = pRectangulo;

		cuerpo.position = b2Vec2(400, 0);
		cuerpo.angle    = 0;
		//sf::Shape rectangulo = sf::Shape::Rectangle(sf::Vector2f(-400,  10.0f),
		//											sf::Vector2f( 400, -10.0f),
		//											sf::Color::Green);

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

		//Pared de abajo
		cuerpo.position = b2Vec2(400, 600);

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared) );

		//Pared de izquierda
		cuerpo.position = b2Vec2(0, 300);
		cuerpo.angle = 3.1415f/2.0f;

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(1.0f,0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared) );

		//Pared de derecha
		cuerpo.position = b2Vec2(800, 300);
		cuerpo.angle = 3.1415f/2.0f;

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(-1.0f,0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

		m_pAutoFantastico->GetSteeringBehaviors().m_pParedes = &Paredes;
		m_pWanderer->GetSteeringBehaviors().m_pParedes = &Paredes;
		// Obstaculos
		for(int i=0; i < 4 ; ++i)
		{
			cuerpo.type        = b2BodyType::b2_staticBody;
			adorno.restitution = 0.2;
			adorno.isSensor    = false;
			adorno.friction    = 0.3f;
			adorno.density     = 0.01f;//Masa de 45.32
			b2CircleShape* pCirculo = new b2CircleShape();
			pCirculo->m_radius = imgObstaculoCircular->getSize().x / 2 * escala;
			adorno.shape       = pCirculo;

			cuerpo.position = b2Vec2((rand()/(float)RAND_MAX)*400+200, (rand()/(float)RAND_MAX)*400+100);
			cuerpo.angle    = 0;

			//sf::Shape circulo = sf::Shape::Circle(sf::Vector2f(0.0f, 0.0f),
			//										pCirculo->m_radius, sf::Color::Green);
			//Obstaculos.push_back( new EntidadEscena(cuerpo, adorno, &circulo) );
			Obstaculos.push_back(new EntidadEscena(cuerpo, adorno, escala, imgObstaculoCircular));
		}
		m_pAutoFantastico->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;
		m_pWanderer->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;
}

std::vector<EntidadEscena*>	 MiGame::GetWalls()
{
	return ParedesEscena;
}
void MiGame::Actualizar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	//////////////////////////////////////////////////
	//////     ACTUALIZANDO EL VEHICULO     //////////
	//////////////////////////////////////////////////

		
	m_pAutoFantastico->Actualizar(dt);

	m_pWanderer->Actualizar(dt);

	for(int i=0; i < Obstaculos.size() ; ++i)
		Obstaculos[i]->Actualizar(dt);
	
	for(int i=0; i < ParedesEscena.size() ; ++i)
		ParedesEscena[i]->Actualizar(dt);

	

	/*float distance = Utils::GetVecDistance(m_pAutoFantastico->GetPosicion() , m_pWanderer->GetPosicion());
	std::cout << "Distance: " << distance << std::endl;
	if (distance < 100)
	{
		m_pWanderer->GetSteeringBehaviors().DeambularOff();
		m_pWanderer->GetSteeringBehaviors().EvadirObstaculosOn();
		m_pWanderer->GetSteeringBehaviors().EvadirParedesOn();
		m_pWanderer->GetSteeringBehaviors().InterceptarOn();
		m_pWanderer->GetSteeringBehaviors().m_PosObjetivo = m_pAutoFantastico->GetPosicion();
	}*/
	/*else
	{
		m_pWanderer->GetSteeringBehaviors().DeambularOn();
		m_pWanderer->GetSteeringBehaviors().EvadirObstaculosOff();
		m_pWanderer->GetSteeringBehaviors().EvadirParedesOff();
		m_pWanderer->GetSteeringBehaviors().InterceptarOff();
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pAutoFantastico->AplicarFuerzaMundo(sf::Vector2f(-500, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pAutoFantastico->AplicarFuerzaMundo(sf::Vector2f(500, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pAutoFantastico->AplicarFuerzaMundo(sf::Vector2f(0, -500));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pAutoFantastico->AplicarFuerzaMundo(sf::Vector2f(0, 500));

	m_World.Step(m_dt, 10, 10);

	m_World.ClearForces();
}

void MiGame::Dibujar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	m_Window.clear();

	//////////////////////////////////////////////////
	//////      DIBUJANDO EL VEHICULO       //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->Dibujar(m_Window);
		m_pWanderer->Dibujar(m_Window);
		for(int i=0; i < Obstaculos.size() ; ++i)
			Obstaculos[i]->Dibujar(m_Window);

		for(int i=0; i < ParedesEscena.size() ; ++i)
			ParedesEscena[i]->Dibujar(m_Window);

	m_Window.display();
}

void MiGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticula].loadFromFile("Recursos\\Vehiculo2.png") )
		exit(0);
	if (!m_ManagerDeImagenes[IDImagen::ObstaculoPared].loadFromFile("Recursos\\ObstaculoPared.png"))
		exit(0);
	if (!m_ManagerDeImagenes[IDImagen::ObstaculoCircular].loadFromFile("Recursos\\Obstaculo.png"))
		exit(0);
	if (!m_ManagerDeImagenes[IDImagen::Wanderer].loadFromFile("Recursos\\Wanderer.png"))
		exit(0);
}