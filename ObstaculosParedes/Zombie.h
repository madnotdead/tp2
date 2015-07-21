#pragma once
#include "C:\Users\Leandro\Desktop\Nueva carpeta (2)\Ejemplos_SteeringBehaviors_2014\Ejemplos_SteeringBehaviors\CodigoFuenteEjemplos\Libreria\includes\Vehiculo.h"
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "Utils.h"
#include "MiGame.h"
#include "StateMachine.h"

class ZombieState;

class Zombie :
	public Vehiculo
{
public:
	Zombie(b2BodyDef cuerpo,b2FixtureDef adorno,float escala, sf::Texture *img, MiGame* mGame) ;
	~Zombie();
	StateMachine<Zombie>* GetFSM() const;	
	void Actualizar(float dt);
	MiGame* getGame(){ return mGame; }
private:
	b2BodyDef cuerpo;
	b2FixtureDef adorno;
	sf::Texture* img;
	float escala;
	StateMachine<Zombie>* m_pStateMachine;
	b2BodyDef nCuerpo;
	b2FixtureDef nAdorno;
	MiGame* mGame;
};

