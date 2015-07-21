#pragma once
#include "Zombie.h"

class State_Zombie_Deambular : public State <Zombie>
{
private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Zombie_Deambular(){}
	State_Zombie_Deambular(const State_Zombie_Deambular * &other){}
	State_Zombie_Deambular & operator=(const State_Zombie_Deambular&){}

public:
	static State_Zombie_Deambular * Instance();
	void Execute(Zombie* zombie);
	void Enter(Zombie* zombie);
	void Exit(Zombie* zombie);
	char* GetStateName();
};

class State_Zombie_Perseguir : public State<Zombie>{

private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Zombie_Perseguir(){}
	State_Zombie_Perseguir(const State_Zombie_Perseguir * &other){}
	State_Zombie_Perseguir & operator=(const State_Zombie_Perseguir&){}

public:
	static State_Zombie_Perseguir * Instance();
	void Execute(Zombie* matador);
	void Enter(Zombie* matador);
	void Exit(Zombie* matador);
	char* GetStateName();


};