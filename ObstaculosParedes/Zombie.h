#pragma once
#include "Vehiculo.h"
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
	void Actualizar(float dt);
	MiGame* getGame(){ return mGame; }
private:
	b2BodyDef cuerpo;
	b2FixtureDef adorno;
	sf::Texture* img;
	float escala;
	b2BodyDef nCuerpo;
	b2FixtureDef nAdorno;
	MiGame* mGame;
};

