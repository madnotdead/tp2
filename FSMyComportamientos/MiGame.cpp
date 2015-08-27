#include "MiGame.h"
#include <Box2D/Box2D.h>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MiGame::MiGame(): Game(sf::VideoMode(800,600,32), "Ejemplo: FSM y Comportamientos", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(24, 8, 0), 60)
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
	//sf::Texture* img = &m_ManagerDeImagenes[IDImagen::VehiculoParticulaCobarde];

	sf::Texture* img = &m_ManagerDeImagenes[IDImagen::Jugador];
	sf::Texture* imgWanderer = &m_ManagerDeImagenes[IDImagen::Wanderer];
	sf::Texture* imgObstaculoCircular = &m_ManagerDeImagenes[IDImagen::ObstaculoCircular];
	sf::Texture* imgObstaculoPared = &m_ManagerDeImagenes[IDImagen::ObstaculoPared];

	float escala = 0.2f;

	b2BodyDef cuerpo;
	cuerpo.type        = b2BodyType::b2_dynamicBody;
	b2FixtureDef adorno;
	adorno.restitution = 0.0f;
	adorno.isSensor    = false;
	adorno.friction    = 0.3f;
	adorno.density     = 0.01f;//Masa de 26.214399
	b2PolygonShape* pRectangulo = new b2PolygonShape();
	pRectangulo->SetAsBox(img->getSize().x / 2 * escala, img->getSize().y / 2 * escala, b2Vec2(0, 0), 0);
	adorno.shape       = pRectangulo;

	cuerpo.position = b2Vec2(300, 300);
	cuerpo.angle    = 0;

	m_pPlayer = new Player(cuerpo, adorno, escala, img);//Creamos al vehiculo que deambula

	for (size_t i = 0; i < 3; i++)
	{
		cuerpo.position = b2Vec2(Utils::GetRandomIntValue(100, 200), Utils::GetRandomIntValue(100, 200));
		m_pPersecutores.push_back(new Persecutor(m_pPlayer, cuerpo, adorno, escala, imgWanderer));
	}
	
	/////////////////////////////////////////////////
	////// ACTIVANDO LOS STEERING BEHAVIORS //////////
	/////////////////////////////////////////////////
	//Pared de arriba
	cuerpo.type = b2BodyType::b2_staticBody;
	adorno.restitution = 0.2f;
	adorno.isSensor = false;
	adorno.friction = 0.3f;
	adorno.density = 0.01f;
	pRectangulo->SetAsBox(400, 10, b2Vec2(0.0f, 0.0f), 0);
	adorno.shape = pRectangulo;

	cuerpo.position = b2Vec2(400, 0);
	cuerpo.angle = 0;

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	//Pared de abajo
	cuerpo.position = b2Vec2(400, 600);

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	//Pared de izquierda
	cuerpo.position = b2Vec2(0, 300);
	cuerpo.angle = 3.1415f / 2.0f;

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(1.0f, 0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	//Pared de derecha
	cuerpo.position = b2Vec2(800, 300);
	cuerpo.angle = 3.1415f / 2.0f;

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	for (int i = 0; i < 4; ++i)
	{
		cuerpo.type = b2BodyType::b2_staticBody;
		adorno.restitution = 0.2;
		adorno.isSensor = false;
		adorno.friction = 0.3f;
		adorno.density = 0.01f;//Masa de 45.32
		b2CircleShape* pCirculo = new b2CircleShape();
		pCirculo->m_radius = imgObstaculoCircular->getSize().x / 2 * escala;
		adorno.shape = pCirculo;

		cuerpo.position = b2Vec2((rand() / (float)RAND_MAX) * 400 + 200, (rand() / (float)RAND_MAX) * 400 + 100);
		cuerpo.angle = 0;

		//sf::Shape circulo = sf::Shape::Circle(sf::Vector2f(0.0f, 0.0f),
		//										pCirculo->m_radius, sf::Color::Green);
		//Obstaculos.push_back( new EntidadEscena(cuerpo, adorno, &circulo) );
		Obstaculos.push_back(new EntidadEscena(cuerpo, adorno, escala, imgObstaculoCircular));
	}

	for (size_t i = 0; i < 3; i++)
	{
		m_pPersecutores[i]->GetSteeringBehaviors().m_pParedes = &Paredes;
		m_pPersecutores[i]->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;
		m_pPersecutores[i]->m_FuerzaSteeringMax = 600;
		m_pPersecutores[i]->m_VelocidadMax = 40;
	}
		
	
	m_pPlayer->GetSteeringBehaviors().m_pParedes = &Paredes;
	m_pPlayer->m_FuerzaSteeringMax = 600;
	m_pPlayer->m_VelocidadMax = 40;

	/////////////////////////////////////////////////////////////////////////////////////////////
	timeCounter.setFont(textFont);
	timeCounter.setColor(sf::Color::White);
	timeCounter.setCharacterSize(12);
	timeCounter.setString("time: 0");
	timeCounter.setPosition(sf::Vector2f(m_Window.getSize().x - 100, 100));
}

void MiGame::Actualizar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	//////////////////////////////////////////////////
	//////     ACTUALIZANDO EL VEHICULO     //////////
	//////////////////////////////////////////////////


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pPlayer->AplicarFuerzaMundo(sf::Vector2f(-500, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pPlayer->AplicarFuerzaMundo(sf::Vector2f(500, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pPlayer->AplicarFuerzaMundo(sf::Vector2f(0, -500));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pPlayer->AplicarFuerzaMundo(sf::Vector2f(0, 500));

	m_pPlayer->Actualizar(dt);
	
	for (size_t i = 0; i < 3; i++)
		m_pPersecutores[i]->Actualizar(dt);

	for (int i = 0; i < Obstaculos.size(); ++i)
		Obstaculos[i]->Actualizar(dt);

	for (int i = 0; i < ParedesEscena.size(); ++i)
		ParedesEscena[i]->Actualizar(dt);

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

	m_pPlayer->Dibujar(m_Window);

	for (size_t i = 0; i < 3; i++)
		m_pPersecutores[i]->Dibujar(m_Window);

	for (int i = 0; i < Obstaculos.size(); ++i)
		Obstaculos[i]->Dibujar(m_Window);

	for (int i = 0; i < ParedesEscena.size(); ++i)
		ParedesEscena[i]->Dibujar(m_Window);

	m_Window.draw(timeCounter);

	m_Window.display();
}

void MiGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::Jugador].loadFromFile("Recursos\\Player.png") )
			exit(0);
	if( !m_ManagerDeImagenes[IDImagen::Wanderer].loadFromFile("Recursos\\Wanderer.png") )
			exit(0);
	if (!m_ManagerDeImagenes[IDImagen::ObstaculoCircular].loadFromFile("Recursos\\Obstaculo.png"))
		exit(0);
	if (!m_ManagerDeImagenes[IDImagen::ObstaculoPared].loadFromFile("Recursos\\ObstaculoPared.png"))
		exit(0);
	if (!textFont.loadFromFile("Recursos\\Tango Regular.ttf"))
		exit(0);
	
}