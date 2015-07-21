#include "Zombie.h"
#include "ZombieState.h"

Zombie::Zombie(b2BodyDef cuerpo, b2FixtureDef adorno, float escala, sf::Texture *image, MiGame *_mGame ) :Vehiculo(cuerpo, adorno, escala, image)
{
	this->m_FuerzaSteeringMax = 600;
	this->m_VelocidadMax = 100;
	mGame = _mGame;
	m_pStateMachine = new StateMachine<Zombie>(this);
	m_pStateMachine->SetCurrentState(State_Zombie_Deambular::Instance());
}

void Zombie::Actualizar(float dt)
{
	m_pStateMachine->Update();
	Actualizar(dt);
}
Zombie::~Zombie()
{
}
