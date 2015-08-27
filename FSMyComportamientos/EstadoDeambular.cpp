#include "EstadoQuieto.h"
#include "EstadoAtacar.h"
#include "EstadoDeambular.h"
#include "Persecutor.h"

#include <iostream>

#include "MiGame.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoDeambular::EstadoDeambular() : Estado("EstadoDeambular")
{}

EstadoDeambular::EstadoDeambular(const EstadoDeambular& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoDeambular& EstadoDeambular::operator=(const EstadoDeambular& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoDeambular::~EstadoDeambular()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoDeambular* EstadoDeambular::Singleton()
{
	static EstadoDeambular instancia;
	return &instancia;
}

void EstadoDeambular::Entrar(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
	std::cout << "Entro a EstadoDeambular" << std::endl;

	pPersecutor->GetSteeringBehaviors().DeambularOn();
	//pPersecutor->GetSteeringBehaviors().EvadirObstaculosOn();
	//pPersecutor->GetSteeringBehaviors().EvadirParedesOn();
}

void EstadoDeambular::Ejecutar(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
	FSM& vahiculoFSM = pEntidad->GetFSM();

	sf::Vector2f dist = pPersecutor->GetPosicion() - pPersecutor->m_pPresa->GetPosicion();
	if (sqrt(dist.x*dist.x + dist.y*dist.y) < 100)//Si el enemigo esta muy cerca cambia de estado para atacar
	{
		vahiculoFSM.CambiarEstado(EstadoAtacar::Singleton());
		return;
	}
}

void EstadoDeambular::Salir(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
	pPersecutor->GetSteeringBehaviors().DeambularOff();
}