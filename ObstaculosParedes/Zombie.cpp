#include "Zombie.h"
#include "ZombieState.h"

Zombie::Zombie(b2BodyDef cuerpo, b2FixtureDef adorno, float escala, sf::Texture *image, MiGame *_mGame ) :Vehiculo(cuerpo, adorno, escala, image)
{
	this->m_FuerzaSteeringMax = 600;
	this->m_VelocidadMax = 100;
	mGame = _mGame;
	//m_MaquinaDeEstadoFinito.CambiarEstado(State_Zombie_Deambular::Instance());
}

void Zombie::Actualizar(float dt)
{
	Actualizar(dt);
	//m_MaquinaDeEstadoFinito.Actualizar(dt);

}
Zombie::~Zombie()
{
}
