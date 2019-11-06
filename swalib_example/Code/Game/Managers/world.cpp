#include "../../../../common/stdafx.h"
#include <string>
#include "World.h"
#include "../Entities/Player.h"
#include "../Entities/Boss.h"
#include "../Entities/Components/level_comp.h"
#include "../Entities/Messages/reset_msg.h"
#include "../Entities/Components/life_comp.h"
#include "../Entities//Messages/new_pos_msg.h"
#include "../Entities/Messages/render_msg.h"
#include "InputController.h"
#include "InterfaceController.h"
#include "graphics_engine.h"
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
//Necesario para el funcionamiento de la librería de música
#pragma comment(lib, "winmm.lib")
#include "../Entities/Bullet.h"
#include "../Entities/Messages/entity_msg.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Components/bullet_comp.h"
#include "../Entities/Messages/input_msg.h"
#include "../Entities/Messages/sound_msg.h"
#include "../Entities/Messages/menu_msg.h"
#include "events.h"

using namespace std;

World* World::m_world = nullptr;

World* World::GetWorld() {
	return m_world;
}

World* World::create(cBackground* victory, cBackground* defeat, cBackground* menu, vec2 worldSize) {
	DEL(m_world);
	World* world = NEW(World,(victory, defeat, menu, worldSize));
	World::m_world = world;
	return world;
}

World::World(cBackground* victory, cBackground* defeat, cBackground* menu, vec2 worldSize)
{
	SetActualLevel(0);
	SetState(State::PLAYING);
	m_worldSize = worldSize;
	vector<Level*> levels = Level::GetLevels();
	SetVictory(victory);
	SetDefeat(defeat);
	SetMenu(menu);
	SetInitCount(Level::GetLevels().at(0)->FindComponent<cLevelComp>()->GetInitWait());
}

World::~World() {
	DEL(GetVictory());
	DEL(GetDefeat());
	DEL(GetMenu());
	Level::DeleteLevels();
}

World::State World::GetState() {
	return m_state;
}

void World::ManageEvent(TEvent* pEvent, float fTimeDiff)
{
	if (m_state == World::State::MENU) {
		if (pEvent->GetType() == TEvent::TType::EMouseDownLeft) {
			TEventMouseDownLeft* event = dynamic_cast<TEventMouseDownLeft*>(pEvent);
			vec2 mousePos = { static_cast<float>(event->Getx()), static_cast<float>(event->Gety())};
			cClickMsg clickMsg(mousePos);
			ReceiveMessage(clickMsg);
		}
	}
		//Gestión del input en derrota y victoria
	else if (m_state == World::State::PLAYING) {
		
		//Gestión del input en el caso de los diálogos
		if (pEvent->GetType() == TEvent::TType::EKeyboardDown) {
			TEventKeyboardDown* eventSpace = dynamic_cast<TEventKeyboardDown*>(pEvent);
			if (eventSpace->Getkey() == (int)cInputController::Key::SPACE) {
				cPassDialogMsg passLogPly;
				ReceiveMessage(passLogPly);
			}
		}

		//Gestión del input en el caso del juego (jugador)
		if (Player::GetPlayer() != nullptr && Player::GetPlayer()->FindComponent<cLifeComp>()->GetLifes() > 0) {
			TEventMouseMove* eventMove = dynamic_cast<TEventMouseMove*>(pEvent);
			if (eventMove) {
				vec2 mousePos = { static_cast<float>(eventMove->Getx()), static_cast<float>(eventMove->Gety()) };
				cMovePlayerMsg newPosPly(mousePos);
				ReceiveMessage(newPosPly);
			}
			if (pEvent->GetType() == TEvent::TType::EMouseDownLeft) {
				cShootPlayerMsg shootMsg;
				ReceiveMessage(shootMsg);
			}
		}
	}
		//Gestión del input en derrota y victoria
	else if (m_state == World::State::GAMEOVER) {
		if (pEvent->GetType() == TEvent::TType::EMouseDownRight) {
			cResetWorldMsg resetMsg;
			ReceiveMessage(resetMsg);
		}
	}

	else if (m_state == World::State::VICTORY) {
		if (pEvent->GetType() == TEvent::TType::EMouseDownRight) {
			cResetWorldMsg resetMsg;
			ReceiveMessage(resetMsg);
		}
	}
}

void World::InitMenu()
{
	cPlaySoundMsg playSoundMsg(GetMenu()->GetAudio());
	ReceiveMessage(playSoundMsg);
	SetState(State::MENU);
}

//Inicializa el mundo (ya sea al principio o si termina el juego (victoria/derrota))
void World::Init() {
	SetActualLevel(0);
	//Ejecuta una música
	cPlaySoundMsg playSoundMsg(Level::GetLevels().at(GetActualLevel())->FindComponent<cLevelComp>()->GetBackgrounds()[0]->GetAudio());
	ReceiveMessage(playSoundMsg);
	SetInitCount(Level::GetLevels().at(0)->FindComponent<cLevelComp>()->GetInitWait());
	//Reinicia tanto el jugador como los niveles
	cResetMsg resetMsg;
	Player::GetPlayer()->ReceiveMessage(resetMsg);
	for (unsigned int i = 0; i < Level::GetLevels().size(); i++) {
		Level::GetLevels().at(i)->ReceiveMessage(resetMsg);
	}
	//El estado actual es jugando
	SetState(State::PLAYING);
	//Inicializa el estado de la interfaz
	vec2 pos = { m_worldSize.x - 32.0f, 8.0f };
	cInterfaceController::GetInstance().UpdatePlayerHealth(true, &pos);
	vec2 posB = { m_worldSize.x /2.0f - 5.0f, m_worldSize.y - 24.0f };
	cInterfaceController::GetInstance().UpdateBossHealth(false, &posB);
	//Si el primer nivel es horizontal o no establecerá dicha información para las balas del jugador
	if (Level::GetLevels().at(GetActualLevel())->FindComponent<cLevelComp>()->GetHorizontal()) {
		Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->SetBulletData({ Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().loc, Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().size, DEG2RAD(0.0f) });
	}
	else {
		Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->SetBulletData({ Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().loc, Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().size, DEG2RAD(90.0f) });
	}
}

//Actualización del mundo
void World::Update(float timeDiff) {
	switch (GetState()) {
	case State::PLAYING:
		//
		cDialogLogicMsg dialogLogPly(timeDiff);
		ReceiveMessage(dialogLogPly);

		if (Player::GetPlayer() == nullptr || Player::GetPlayer()->FindComponent<cLifeComp>()->GetLifes() <= 0) {
			cDeleteEntitiesMsg deleteMsg;
			Level::GetLevels().at(GetActualLevel())->ReceiveMessage(deleteMsg);
			cInterfaceController::GetInstance().UpdateBossHealth(false);
			cPlaySoundMsg playSoundMsg(GetDefeat()->GetAudio());
			ReceiveMessage(playSoundMsg);
			//Music(GetDefeat()->GetAudio());
			SetState(State::GAMEOVER);
		}
		//En caso contrario actualiza el jugador y el nivel
		else {
			Player::GetPlayer()->Slot(timeDiff);
		}
		break;
	}
}

//Dibuja el mundo (interfaz, gráficos y nivel)
void World::Draw() {
	cDrawDialogMsg drawDialogMsg;
	ReceiveMessage(drawDialogMsg);
	switch (GetState()) {
	case State::MENU:
		cGraphicsEngine::GetInstance().Slot(GetMenu());
		break;
	case State::VICTORY:
		cGraphicsEngine::GetInstance().Slot(GetVictory());
		break;
	case State::GAMEOVER:
		cGraphicsEngine::GetInstance().Slot(GetDefeat());
		break;
	}
}

vec2 World::GetWorldSize() {
	return m_worldSize;
}

void World::SetWorldSize(vec2 world) {
	m_worldSize = world;
}

//Obtiene las entidades spawneadas en el nivel actual
vector<cEntity*> World::GetEntities() {
	vector<Level*> levels = Level::GetLevels();
	Level* actLevel = levels.at(GetActualLevel());
	cLevelComp* levelComp = actLevel->FindComponent<cLevelComp>();
	vector<cEntity*> entities = levelComp->GetEntities();
	return entities;
}