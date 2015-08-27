#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Vehiculo.h"
//Identificadores para las imagenes(sf::Texture) almacenadas
//en el mapa m_ManagerDeImagenes
enum IDImagen{ VehiculoParticula, ObstaculoPared, ObstaculoCircular, Wanderer };

//Clase principal del juego, contiene toda la estructura de juego
//Este objeto sera el responsable de:
//	-Crear la escena
//	-Dibujar la pantalla
//	-Actualizar el juego

class Zombie;

class MiGame: public Game
{
private:

	MiGame();

	MiGame(const MiGame& cpy);

	MiGame& operator=(const MiGame& cpy);

	Vehiculo* m_pAutoFantastico;
	Zombie* m_pWanderer;
	std::vector<EntidadEscena*>				Obstaculos;//Necesitamos estos para decirle cuales son los obstaculos
	std::vector<SteeringBehaviors::Pared*>	Paredes;   //Necesitamos estos para definir como son las paredes obstaculos
	std::vector<EntidadEscena*>				ParedesEscena;//Necesitamos estos para tener las paredes como objetos de Box2D y que se grafiquen
	sf::Text timeCounter;
	sf::Text noActivityTimeCounter;
	sf::Font textFont;
public:
	//Nos devuelve la unica instancia de la clase
	static MiGame* Singleton();

	~MiGame();

	//================================================
	/////////	Game Propiedades publicas	 /////////
	//================================================

	std::map<IDImagen,sf::Texture> m_ManagerDeImagenes;

	sf::Text timeCounter;
	sf::Text noActivityTimeCounter;
	sf::Font textFont;

	//================================================
	/////////////	 Game Metodos		 /////////////
	//================================================

	//Crea la escena
	virtual void CrearEscena();

	//Actualiza la escena
	virtual void Actualizar(sf::Time frameTime);

	//Dibuja la escena
	virtual void Dibujar(sf::Time frameTime);

	//Carga los recursos a usar
	virtual void LoadRecursos();

	std::vector<EntidadEscena*>	 GetWalls();

	Vehiculo* GetPlayer() { return m_pAutoFantastico; }

	
};