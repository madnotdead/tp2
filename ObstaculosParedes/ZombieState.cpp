#include "ZombieState.h"


State_Zombie_Deambular*  State_Zombie_Deambular::Instance(){
	static State_Zombie_Deambular instance;
	return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Deambular
/////////////////////////////////////////////////////////////////////////////

void  State_Zombie_Deambular::Entrar(EntidadBase* zombie){


	//((Zombie)zombie)->GetSteeringBehaviors().EvadirParedesOn();
	//zombie->GetSteeringBehaviors().m_PesoEvadirParedes = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
	//zombie->GetSteeringBehaviors().EvadirObstaculosOn();		 // de la fuerza de EvadirParedes
	//zombie->GetSteeringBehaviors().m_PesoEvadirObstaculos = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
	//zombie->GetSteeringBehaviors().DeambularOn();
}

void State_Zombie_Deambular::Salir(EntidadBase* zombie){

	////Calculamos si hay que cambiar de estado
	//Tablero* t = matador->GetTablero();

	////vemos si hay una hormiga cerca 
	//Hormiga* g = t->GetClosestHormiga(matador);
	//if (g != NULL){
	//	float dist = Utils::GetVecDistance(g->GetPosition(), matador->GetPosition());
	//	if (dist< DISTANCIAVISTA)//cambiamos al estado perseguir
	//		matador->GetFSM()->ChangeState(State_Matador_Perseguir::Instance());
	//}

	////calculamos si vamos a cambiar de dirección
	//if (Utils::GetRandomIntValue(0, 100) == 0){
	//	matador->ChangeDirection();
	//}

	//matador->Move();


}

void State_Zombie_Deambular::Ejecutar(EntidadBase* zombie){

	Zombie* o = (Zombie*)zombie;

	////Calculamos si hay que cambiar de estado
	//Tablero* t = matador->GetTablero();

	////vemos si hay una hormiga cerca 
	//Hormiga* g = t->GetClosestHormiga(matador);
	//if (g != NULL){
	//	float dist = Utils::GetVecDistance(g->GetPosition(), matador->GetPosition());
	//	if (dist< DISTANCIAVISTA)//cambiamos al estado perseguir
	//		matador->GetFSM()->ChangeState(State_Matador_Perseguir::Instance());
	//}

	////calculamos si vamos a cambiar de dirección
	//if (Utils::GetRandomIntValue(0, 100) == 0){
	//	matador->ChangeDirection();
	//}

	//matador->Move();


}

char* State_Zombie_Deambular::GetNombre(){
	return "Deambular";
}

bool State_Zombie_Deambular::OnMensaje(EntidadBase* pEntidad, const Mensaje& msg){
	return true;
}

//State_Zombie_Perseguir*  State_Zombie_Perseguir::Instance(){
//	static State_Zombie_Perseguir instance;
//	return &instance;
//}

///////////////////////////////////////////////////////////////////////////////
////Perseguir
///////////////////////////////////////////////////////////////////////////////
//
//void State_Zombie_Perseguir::Enter(Zombie* zombie){
//
//	zombie->GetSteeringBehaviors().EvadirParedesOn();
//	zombie->GetSteeringBehaviors().m_PesoEvadirParedes = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
//	zombie->GetSteeringBehaviors().EvadirObstaculosOn();		 // de la fuerza de EvadirParedes
//	zombie->GetSteeringBehaviors().m_PesoEvadirObstaculos = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
//	
//	//este vehiculo persigue(intercepta)
//	zombie->GetSteeringBehaviors().InterceptarOn();
//	//zombie->GetSteeringBehaviors().m_pPresa = m_pAutoPresa;//le decimos a quien intercepta(puntero)
//
//}
//
//void State_Zombie_Perseguir::Execute(Zombie* zombie){
//
//
//	////buscamos la hormiga mas cercana
//	//Tablero* t = matador->GetTablero();
//	//Hormiga* g = t->GetClosestHormiga(matador);
//	////guardamos el objetivo en el objeto matador
//	//if (g != NULL)
//	//	matador->SetTarget(g);
//	//else
//	//	matador->GetFSM()->ChangeState(State_Matador_Deambular::Instance());
//
//	////si estamos muy cerca lo comemos
//
//	//float dist = Utils::GetVecDistance(matador->GetPosition(), matador->GetTarget()->GetPosition());
//	//if (dist<EATDIST){
//
//	//	matador->GetTablero()->KillHormiga(matador->GetTarget());
//
//	//	/*if (g->HasPower())
//	//	{
//	//	t->KillMatador(matador);
//	//	return;
//	//	}*/
//
//
//	//	matador->GetFSM()->ChangeState(State_Matador_Deambular::Instance());
//	//}
//	////lo pierde de vista
//	//if (dist>DISTANCIAVISTA){
//	//	matador->GetFSM()->ChangeState(State_Matador_Deambular::Instance());
//	//}
//
//
//	////Update chase direction
//	//matador->Chase();
//	////move
//	//matador->Move();
//
//
//}
//
//void State_Zombie_Perseguir::Exit(Zombie* zombie){
//
//
//}
//
//char* State_Zombie_Perseguir::GetStateName(){
//	return "Perseguir";
//}
