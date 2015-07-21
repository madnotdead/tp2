#include "MiGame.h"

#include <Box2D/Box2D.h>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MiGame::MiGame(): Game(sf::VideoMode(800,600,32), "Ejemplo: Escapar", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(24, 8, 0), 60)
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

	cuerpo.position = b2Vec2(100, 100);
	cuerpo.angle    = 0;

	m_pAutoFantastico = new Vehiculo(cuerpo, adorno, escala, img);

	m_pAutoFantastico->m_FuerzaSteeringMax = 600;
	m_pAutoFantastico->m_VelocidadMax = 40;


	//////////////////////////////////////////////////
	////// ACTIVANDO LOS STEERING BEHAVIORS //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->GetSteeringBehaviors().EscaparOn();
		//podriamos establecer m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo a la posicion
		//a escapar una vez, pero en vez de eso en este ejemplo le daremos cada frame la posicion a escapar
		//sea la posicion del mouse
}

void MiGame::Actualizar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	//////////////////////////////////////////////////
	//////     ACTUALIZANDO EL VEHICULO     //////////
	//////////////////////////////////////////////////

		//En este caso todas la posicion de la que huir sea la del mouse
		m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo = sf::Vector2f(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

		m_pAutoFantastico->Actualizar(dt);

	m_World.Step(m_dt, 10, 10);

	m_World.ClearForces();
}

void MiGame::Dibujar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	m_Window.clear();

	// coordenada objetivo
	sf::CircleShape Target(5.0f);
	Target.setOrigin(5.0f, 5.0f);
	Target.setFillColor(sf::Color(0, 0, 0, 0));
	Target.setOutlineColor(sf::Color::Yellow);
	Target.setOutlineThickness(2.0f);
	Target.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo);
	m_Window.draw(Target);

	//////////////////////////////////////////////////
	//////      DIBUJANDO EL VEHICULO       //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->Dibujar(m_Window);

	m_Window.display();
}

void MiGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticula].loadFromFile("Recursos\\Vehiculo2.png") )
			exit(0);
}