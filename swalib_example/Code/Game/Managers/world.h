#ifndef _WORLD_H_
#define _WORLD_H_
#include <stdint.h>
#include <algorithm>
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Enemy.h"
#include "../Entities/Boss.h"
#include "../Graphics/Background.h"
#include "../Managers/Level.h"
#include "../Managers/InputController.h"

using namespace std;

//Mundo (Conjunto de niveles)
class World :public cEntity, public cInputController::IListener{
public:
	//Estado actual del mundo
	enum State {
		PLAYING,
		VICTORY,
		GAMEOVER,
		MENU
	};

	static World* GetWorld();

	static World* create(cBackground* victory, cBackground* defeat, cBackground* menu, vec2 worldSize);

	virtual void ManageEvent(TEvent* pEvent, float fTimeDiff);

	~World();

	State GetState();

	void InitMenu();
	void Init();
	virtual void Update(float timeDiff) override;
	void Draw();

	//Entidades actuales del mundo
	vector<cEntity*> GetEntities();

	//Tamaño del mundo
	vec2 GetWorldSize();
	void SetWorldSize(vec2 world);

	World::State GetState() const { return m_state; }
	void SetState(World::State val) { m_state = val; }
	int GetActualLevel() const { return m_actualLevel; }
	void SetActualLevel(int val) { m_actualLevel = val; }
	float GetInitCount() const { return m_initCount; }
	void SetInitCount(float val) { m_initCount = val; }
	cBackground* GetVictory() const { return m_victory; }
	void SetVictory(cBackground* val) { m_victory = val; }
	cBackground* GetDefeat() const { return m_defeat; }
	void SetDefeat(cBackground* val) { m_defeat = val; }
	cBackground* GetMenu() const { return m_menu; }
	void SetMenu(cBackground* val) { m_menu = val; }
	//Do once del behaviour del boss
	static bool setBehaviour;
private:
	World(cBackground* victory, cBackground* defeat, cBackground* menu, vec2 worldSize);
	//Tamaño del mundo
	vec2 m_worldSize;
	//Índice del nivel actual
	int m_actualLevel;
	//Estado del juego
	State m_state;
	//Mundo actual
	static World* m_world;
	//Background de victoria (Se ha decidido no crear un nivel para esto ya que en principio no será necesario (nunca habrán bosses ni enemigos
	//en los niveles de victoria y derrota, si se quiere añadir alguna entidad adicional como botones simplemente se podría crear una estructura
	//o una clase nueva, pero no es necesario usar la estructura existente actualmente en la clase Nivel
	cBackground* m_victory;
	//Background de derrota (lo mismo que victoria)
	cBackground* m_defeat;
	//Background de menu (lo mismo que victoria)
	cBackground* m_menu;
	//Tiempo de espera inicial antes de realizar la lógica (no sucede nada)
	float m_initCount;
};


#endif // !_WORLD_H_
