#include "../../common/stdafx.h"
#include "../../common/sys.h"
#include "../../common/core.h"
#include "Game/Managers/GameController.h"

using namespace std;

//Bucle principal
int Main(void) {
	//Inicialización del juego
	GameController* game = GameController::Init();
	//Mientras no acabe
	while (!game->Finished()) {
		//Actualización lógica del nivel
		game->Update();
		//Dibujado del nivel
		game->Draw();
		SYS_Pump();
	}
	//Terminación del nivel
	DEL(game);
	//Fugas de memoria
	DUMP_LEAKS
	return 0;
}
