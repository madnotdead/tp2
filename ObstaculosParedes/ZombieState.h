#pragma once
#include "Zombie.h"

class State_Zombie_Deambular : public Estado
{
private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Zombie_Deambular(){}
	State_Zombie_Deambular(const State_Zombie_Deambular * &other){}
	State_Zombie_Deambular & operator=(const State_Zombie_Deambular&){}

public:
	void Entrar(EntidadBase* pEntidad);
	void Ejecutar(EntidadBase* pEntidad);
	void Salir(EntidadBase* pEntidad);
	bool OnMensaje(EntidadBase* pEntidad, const Mensaje& msg);
	static State_Zombie_Deambular * Instance();
	char* GetNombre();
};
//
//class State_Zombie_Perseguir : public Estado{
//
//private:
//
//	//constructores vacios y por copia privados
//	//para que nadie pueda crear la instancia
//	State_Zombie_Perseguir(){}
//	State_Zombie_Perseguir(const State_Zombie_Perseguir * &other){}
//	State_Zombie_Perseguir & operator=(const State_Zombie_Perseguir&){}
//
//public:
//	static State_Zombie_Perseguir * Instance();
//	void Execute(Zombie* matador);
//	void Enter(Zombie* matador);
//	void Exit(Zombie* matador);
//	char* GetStateName();
//
//
//};