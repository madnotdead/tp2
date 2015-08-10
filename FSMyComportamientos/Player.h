#pragma once
#include "Vehiculo.h"
class Player : public Vehiculo
{
public:
	Player(const b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura);
	~Player();
};

