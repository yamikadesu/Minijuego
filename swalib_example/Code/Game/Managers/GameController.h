#pragma once
#include "World.h"
#include "../Global/timer.h"
#include "InputController.h"

//Controla la gestión del juego
class GameController {
public:
	static GameController* Init();
	~GameController();
	void Update();
	void Draw();
	bool Finished();
private:
	GameController(World * world, cInputController *pInput_manager);
	//Juego actual
	static GameController* m_game;
	//Mundo actual
	World* m_world;
	//Input controller
	cInputController* m_input;
	//Gestión del tiempo
	cTimer m_timer;
};