#include "Player.h"

Player::Player(const b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura) :
Vehiculo(CuerpoDef, AdornoDef, escala, pTextura)
{

}


Player::~Player()
{
}
