#include "../../../../common/stdafx.h"
#include <sstream>
#include <vector>
#include <time.h>
#include <string.h>

#include <fstream>     
#include <iterator>

#include <iostream>
#include "../../../../common/core.h"
#include "../Graphics/Sprite.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Entities/Boss.h"
#include "../Graphics/Background.h"
#include "GameController.h"
#include "graphics_engine.h"
#include "InterfaceController.h"
#include "../Entities/Components/render_comp.h"
#include "../Entities/Components/life_comp.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Messages/collision_msg.h"
#include "InputController.h"
#include "../../../../common/sys.h"
#include "../Entities/Components/collision_comp.h"
#include "../Entities/Components/level_comp.h"
#include "../Entities/Messages/new_pos_msg.h"
#include "Level.h"
#include "../Entities/Bullet.h"
#include "../Entities/Enemy.h"
#include <stdio.h>
#include "../Entities/Components/bullet_comp.h"
#include "../Entities/Components/component.h"
#include "../Entities/Components/dialog_comp.h"
#include "../Entities/Components/sound_comp.h"
#include "../Entities/Components/menu_comp.h"
#include "../Entities/Components/click_comp.h"
#include "../Entities/Button.h"
#include "../Entities/CheckBox.h"
#include <functional>

using namespace std;

GameController* GameController::m_game = nullptr;

void onClickPlay(Button* button, void* data) {
	World* world = reinterpret_cast<World*>(data);
	if (world) {
		world->Init();
		world->FindComponent<cMenuComp>()->BeginDestroy();
	}
}

void onClickCheck(Button* checkButton, void* data) {

}

GameController::GameController(World * world, cInputController *pInput_manager)
	: m_timer(1.0f / 60.0f)
	{
	m_world = world;
	m_input = pInput_manager;
	//this->g_fFPS = 0.0f;
}

GameController::~GameController() {
	DEL(Player::GetPlayer());
	DEL(m_world);
	DEL(m_input);
	//cInputController::GetInstance().Terminate();
	cInterfaceController::GetInstance().Terminate();
	cGraphicsEngine::GetInstance().Terminate();
}

//Dibuja el mundo
void GameController::Draw() {
	m_world->Draw();
}

//Inicializa el juego con los valores indicados en sys
GameController* GameController::Init() {
	DEL(m_game);
	//Establece una semilla aleatoria
	srand(static_cast<unsigned int>(time(NULL)));

	//Tamaño del mundo
	int width = SCR_WIDTH;
	int height = SCR_HEIGHT;

	//Inicialización de los controladores
	cGraphicsEngine::GetInstance().Init();
	cInterfaceController::GetInstance().Init();
	cInputController *pInput_manager = NEW(cInputController, ());
	//cInputController::GetInstance().Init();

	//Creación del jugador (y sus balas)
	Bullet* bullet = NEW(Bullet, ({ BLL_SPRITE,BLL_SIZE }, BLL_SPEED, BLL_DAMAGE, BLL_COOLDOWN));
	Player* player = Player::create();
	cRenderComp* playerRend = NEW(cRenderComp, (PLY_SPRITE, PLY_SIZE, false, PLY_FRAMES, PLY_FRAMES_TIME));
	player->AddComponent(playerRend);
	cLinearVelComp* playerPos = NEW(cLinearVelComp, ({ width / 2.0f, height - 20.0f }, { 0.0f, 0.0f }));
	player->AddComponent(playerPos);
	cLifeComp* playerLife = NEW(cLifeComp, (PLY_LIFES, PLY_INV_TIME, PLY_INV_TICKS, PLY_BLANK_TIME));
	player->AddComponent(playerLife);
	cCollisionComp* playerCollision = NEW(cCollisionComp, (PLY_COLL_RADIUS));
	player->AddComponent(playerCollision);
	cBulletComp* bulletComp = NEW(cBulletComp, (bullet));
	player->AddComponent(bulletComp);

	//Diálogos del nivel 1
	vector<string> initTexts2{ LVL_1_INIT_TEXT };
	vector<string> bossTexts2{ LVL_1_BOSS_TEXT };
	vector<string> finalTexts2{ LVL_1_END_TEXT };

	//Background del nivel 1
	vector<cBackground*> backgrounds2;
	cBackground* back2 = NEW(cBackground, (BCK_1_LVL_1_SPRITE, BCK_1_LVL_1_SIZE, BCK_1_LVL_1_RESIZE, BCK_1_LVL_1_RESIZEPOS, BCK_1_LVL_1_OFFSET));
	back2->SetAudio(BCK_1_LVL_1_MUSIC);
	backgrounds2.push_back(back2);

	vector<Boss*> bosses;
	//Creación del boss principal del nivel 1 junto con sus esbirros (el primer boss del vector se considera el boss principal del nivel
	vector<vec3> posboss2{ BSS_1_LVL_1_POSS };
	Enemy* enemy2 = NEW(Enemy, ({ ENE_BSS_1_LVL_1_SPRITE ,ENE_BSS_1_LVL_1_SIZE }));
	Boss* boss2 = Boss::create();
	cRenderComp* bossRend2 = NEW(cRenderComp, (BSS_1_LVL_1_SPRITE, BSS_1_LVL_1_SIZE, false, BSS_1_LVL_1_FRAMES, BSS_1_LVL_1_FRAMES_TIME));
	boss2->AddComponent(bossRend2);
	cBossLogicComp* bossLogic2 = NEW(cBossLogicComp, (posboss2, BSS_1_LVL_1_ROUNDWAIT, BSS_1_LVL_1_INITWAIT, BSS_1_LVL_1_RANDOM, BSS_1_LVL_1_LIFES, { ENE_BSS_1_LVL_1_MAXSPEED, ENE_BSS_1_LVL_1_MINSPEED, ENE_BSS_1_LVL_1_ROTATE, ENE_BSS_1_LVL_1_ERROR }));
	boss2->AddComponent(bossLogic2);
	cLinearVelComp* bossPos2 = NEW(cLinearVelComp, ({ posboss2.at(0).x, posboss2.at(0).y }, { 0.0f, 0.0f }));
	boss2->AddComponent(bossPos2);
	cCollisionComp* bossCollision2 = NEW(cCollisionComp, (BSS_1_LVL_1_RADIUS));
	boss2->AddComponent(bossCollision2);
	cNewPosMsg updatePos2({ posboss2.at(0).x, posboss2.at(0).y });
	boss2->ReceiveMessage(updatePos2);
	cEnemyComp* enemyComp2 = NEW(cEnemyComp, (enemy2));
	boss2->AddComponent(enemyComp2);

	//Creación del boss secundario del nivel 1 (acompaña al primer boss)
	vector<vec3> posboss1{ BSS_2_LVL_1_POSS };
	Enemy* enemy = NEW(Enemy, ({ ENE_BSS_2_LVL_1_SPRITE,ENE_BSS_2_LVL_1_SIZE }));
	Boss* boss = Boss::create();
	cRenderComp* bossRend = NEW(cRenderComp, (BSS_2_LVL_1_SPRITE, BSS_2_LVL_1_SIZE, false, BSS_2_LVL_1_FRAMES, BSS_2_LVL_1_FRAMES_TIME));
	boss->AddComponent(bossRend);
	cBossLogicComp* bossLogic = NEW(cBossLogicComp, (posboss1, BSS_2_LVL_1_ROUNDWAIT, BSS_2_LVL_1_INITWAIT, BSS_2_LVL_1_RANDOM, BSS_2_LVL_1_LIFES, { ENE_BSS_2_LVL_1_MAXSPEED, ENE_BSS_2_LVL_1_MINSPEED, ENE_BSS_2_LVL_1_ROTATE, ENE_BSS_2_LVL_1_ERROR }));
	boss->AddComponent(bossLogic);
	cLinearVelComp* bossPos = NEW(cLinearVelComp, ({ posboss1.at(0).x, posboss1.at(0).y }, { 0.0f, 0.0f }));
	boss->AddComponent(bossPos);
	cCollisionComp* bossCollision = NEW(cCollisionComp, (BSS_2_LVL_1_RADIUS));
	boss->AddComponent(bossCollision);
	cNewPosMsg updatePos({ posboss1.at(0).x, posboss1.at(0).y });
	boss->ReceiveMessage(updatePos);
	cEnemyComp* enemyComp = NEW(cEnemyComp, (enemy));
	boss->AddComponent(enemyComp);

	bosses.push_back(boss2);
	bosses.push_back(boss);

	//Mejoras del nivel
	vector<Upgrade*> upgrades;
	Upgrade* upgrade = NEW(Upgrade, ({ UPG_1_LVL_1_SPRITE, UPG_1_LVL_1_SIZE }, Upgrade::Type::UPG_1_LVL_1_TYPE, UPG_1_LVL_1_AMOUNT, UPG_1_LVL_1_DELAY));
	upgrades.push_back(upgrade);

	//Creación del nivel 1
	cLevelComp* levelComp1 = NEW(cLevelComp, (initTexts2, bossTexts2, finalTexts2, LVL_1_INITWAIT, LVL_1_WAITTIME, { ENE_LVL_1_SPRITE ,ENE_LVL_1_SIZE }, bosses, ENE_LVL_1_MAXSPEED, ENE_LVL_1_MINSPEED, backgrounds2, LVL_1_HORIZONTAL, LVL_1_ENEMYAMOUNT, { static_cast<float>(LVL_1_WIDTH), static_cast<float>(LVL_1_HEIGHT) }, upgrades));
	Level* level1 = Level::create();
	level1->AddComponent(levelComp1);

	//Diálogos del nivel 2
	vector<string> initTexts{ LVL_2_INIT_TEXT };
	vector<string> bossTexts{ LVL_2_BOSS_TEXT };
	vector<string> finalTexts{ LVL_2_END_TEXT };

	//Background del nivel 2
	vector<cBackground*> backgrounds;
	cBackground* back1 = NEW(cBackground, (BCK_1_LVL_2_SPRITE, BCK_1_LVL_2_SIZE, BCK_1_LVL_2_RESIZE, BCK_1_LVL_2_RESIZEPOS, BCK_1_LVL_2_OFFSET));
	back1->SetAudio(BCK_1_LVL_2_MUSIC);
	backgrounds.push_back(back1);

	vector<Boss*> bosses2;
	//Creación del boss del nivel 2 y sus esbirros
	vector<vec3> posboss3{ BSS_1_LVL_2_POSS };
	Enemy* enemy3 = NEW(Enemy, ({ ENE_BSS_1_LVL_2_SPRITE,ENE_BSS_1_LVL_2_SIZE }));
	Boss* boss3 = Boss::create();
	cRenderComp* bossRend3 = NEW(cRenderComp, (BSS_1_LVL_2_SPRITE, BSS_1_LVL_2_SIZE, false, BSS_1_LVL_2_FRAMES, BSS_1_LVL_2_FRAMES_TIME));
	boss3->AddComponent(bossRend3);
	cBossLogicComp* bossLogic3 = NEW(cBossLogicComp, (posboss3, BSS_1_LVL_2_ROUNDWAIT, BSS_1_LVL_2_INITWAIT, BSS_1_LVL_2_RANDOM, BSS_1_LVL_2_LIFES, { ENE_BSS_1_LVL_2_MAXSPEED, ENE_BSS_1_LVL_2_MINSPEED, ENE_BSS_1_LVL_2_ROTATE, ENE_BSS_1_LVL_2_ERROR }));
	boss3->AddComponent(bossLogic3);
	cLinearVelComp* bossPos3 = NEW(cLinearVelComp, ({ posboss3.at(0).x, posboss3.at(0).y }, { 0.0f, 0.0f }));
	boss3->AddComponent(bossPos3);
	cCollisionComp* bossCollision3 = NEW(cCollisionComp, (BSS_1_LVL_2_RADIUS));
	boss3->AddComponent(bossCollision3);
	cNewPosMsg updatePos3({ posboss3.at(0).x, posboss3.at(0).y });
	boss3->ReceiveMessage(updatePos3);
	cEnemyComp* enemyComp3 = NEW(cEnemyComp, (enemy3));
	boss3->AddComponent(enemyComp3);

	bosses2.push_back(boss3);

	//Mejoras del nivel 2
	vector<Upgrade*> upgrades1;
	Upgrade* upgrade1 = NEW(Upgrade, ({ UPG_2_LVL_2_SPRITE,UPG_2_LVL_2_SIZE }, Upgrade::Type::UPG_2_LVL_2_TYPE, UPG_2_LVL_2_AMOUNT, UPG_2_LVL_2_DELAY));
	Upgrade* upgrade2 = NEW(Upgrade, ({ UPG_1_LVL_2_SPRITE,UPG_1_LVL_2_SIZE }, Upgrade::Type::UPG_1_LVL_2_TYPE, UPG_1_LVL_2_AMOUNT, UPG_1_LVL_2_DELAY));
	upgrades1.push_back(upgrade1);
	upgrades1.push_back(upgrade2);

	//Creación del nivel 2
	cLevelComp* levelComp = NEW(cLevelComp, (initTexts, bossTexts, finalTexts, LVL_2_INITWAIT, LVL_2_WAITTIME, { ENE_LVL_2_SPRITE ,ENE_LVL_2_SIZE }, bosses2, ENE_LVL_2_MAXSPEED, ENE_LVL_2_MINSPEED, backgrounds, LVL_2_HORIZONTAL, LVL_2_ENEMYAMOUNT, { static_cast<float>(LVL_2_WIDTH), static_cast<float>(LVL_2_HEIGHT) }, upgrades1));
	Level* level = Level::create();
	level->AddComponent(levelComp);

	//Creación del Background de victoria
	cBackground* victory = NEW(cBackground, (BCK_VCT_SPRITE, BCK_VCT_SIZE, BCK_VCT_RESIZE, BCK_VCT_RESIZEPOS, BCK_VCT_OFFSET));
	victory->SetAudio(BCK_VCT_MUSIC);
	//Creación del Background de derrota
	cBackground* defeat = NEW(cBackground, (BCK_DFT_SPRITE, BCK_DFT_SIZE, BCK_DFT_RESIZE, BCK_DFT_RESIZEPOS, BCK_DFT_OFFSET));
	defeat->SetAudio(BCK_DFT_MUSIC);
	//Creación del Background de menu
	cBackground* menu = NEW(cBackground, (BCK_MENU_SPRITE, BCK_MENU_SIZE, BCK_MENU_RESIZE, BCK_MENU_RESIZEPOS, BCK_MENU_OFFSET));
	menu->SetAudio(BCK_MENU_MUSIC);

	//Creación del mundo
	World* world = World::create(victory, defeat, menu, { static_cast<float>(width), static_cast<float>(height) });
	cSoundComp* soundContr = NEW(cSoundComp, ());
	world->AddComponent(soundContr);
	cDialogComp* dialogContr = NEW(cDialogComp, (WRL_TEXTTIME));
	world->AddComponent(dialogContr);
	cMenuComp* menuContr = NEW(cMenuComp, ());
	pInput_manager->RegisterToEvent(world);

	Button* button = NEW(Button, (BUTTON_SIZE));
	button->SetCallback(onClickPlay);
	cClickComp* buttonClick = NEW(cClickComp, ());
	button->AddComponent(buttonClick);
	cRenderComp* buttonRend = NEW(cRenderComp, (BUTTON_SPRITE, BUTTON_SIZE, true, BUTTON_FRAMES, BUTTON_FRAMES_TIME));
	button->AddComponent(buttonRend);
	cLinearVelComp* buttonPos = NEW(cLinearVelComp, (BUTTON_POS, BUTTON_SPEED));
	button->AddComponent(buttonPos);
	menuContr->AddEntity(button);

	bool checkedState = CHECKED_STATE;
	CheckBox* checkB = NEW(CheckBox, (CHECKED_SIZE, CHECKED_SPRITE, UNCHECKED_SPRITE, checkedState));
	checkB->SetCallback(onClickCheck);
	cClickComp* checkBClick = NEW(cClickComp, ());
	checkB->AddComponent(checkBClick);
	cRenderComp* checkBRend = nullptr;
	if (checkedState) {
		checkBRend = NEW(cRenderComp, (CHECKED_SPRITE, CHECKED_SIZE, true, CHECKED_FRAMES, CHECKED_FRAMES_TIME));
		cGraphicsEngine::GetInstance().InsertImg(UNCHECKED_SPRITE);
	}
	else {
		checkBRend = NEW(cRenderComp, (UNCHECKED_SPRITE, CHECKED_SIZE, true, CHECKED_FRAMES, CHECKED_FRAMES_TIME));
		cGraphicsEngine::GetInstance().InsertImg(CHECKED_SPRITE);
	}
	checkB->AddComponent(checkBRend);
	cLinearVelComp* checkBPos = NEW(cLinearVelComp, (CHECKED_POS, CHECKED_SPEED));
	checkB->AddComponent(checkBPos);
	menuContr->AddEntity(checkB);

	world->AddComponent(menuContr);
	world->InitMenu();
	//cInputController::GetInstance().
	return m_game = NEW(GameController,(world, pInput_manager));
}

//Actualización lógica del mundo
void GameController::Update() {
	m_timer.InitSlotsToProcess();
	//g_fFPS = 1.0f / timer.GetElapsedTime();
	while (m_timer.ProcessSlots()) {
		m_input->Update(m_timer.GetFixedTick());
		//m_world->Input(m_timer.GetFixedTick());
		m_world->Slot(m_timer.GetFixedTick());
		m_world->Update(m_timer.GetFixedTick());
	}
}

bool GameController::Finished() {
	return SYS_GottaQuit();
}