#include "../../../../../common/stdafx.h"
#include "level_comp.h"
#include "render_comp.h"
#include "../Entity.h"
#include "../Player.h"
#include "../Boss.h"
#include <assert.h>
#include "../Messages/damage_msg.h"
#include "../Messages/reset_msg.h"
#include "../Messages/collision_msg.h"
#include "../Messages/new_pos_msg.h"
#include "life_comp.h"
#include "linear_vel_comp.h"
#include "../Messages/render_msg.h"
#include "../../Managers/InterfaceController.h"
#include "../../Managers/graphics_engine.h"
#include "../Components/collision_comp.h"
#include "../Messages/entity_msg.h"
#include "../Bullet.h"
#include "../../Managers/world.h"
#include <vector>
#include "bullet_comp.h"

using namespace std;

cLevelComp::cLevelComp(vector<string> initTexts, vector<string> bossTexts, vector<string> finalTexts, float initWait, float waitTime, SpriteData enemySprite, vector<Boss*> boss,
	float maxEnemySpeed, float minEnemySpeed, vector<cBackground*> backgrounds, bool horizontal, int enemyAmount, vec2 size, vector<Upgrade*> upgrades)
	: m_initTexts(initTexts), m_bossTexts(bossTexts), m_finalTexts(finalTexts), m_initWait(initWait), m_waitTime(waitTime), m_enemySprite(enemySprite),
	m_boss(boss), m_maxEnemySpeed(maxEnemySpeed), m_minEnemySpeed(minEnemySpeed), m_backgrounds(backgrounds), m_horizontal(horizontal), m_enemyAmount(enemyAmount),
	m_size(size), m_initEnemyAmount(enemyAmount), m_upgrades(upgrades), m_upgradeTime(0.0f), m_time(0.0f)
{}

//Elimina todas las entidades del nivel (proyectiles, enemigos y mejoras)
void cLevelComp::deleteEntities() {
	int esize = m_entities.size();
	for (int i = 0; i < esize; i++) {
		cGraphicsEngine::GetInstance().DeleteRenderObj(*m_entities.at(i)->FindComponent<cRenderComp>()->GetSprite());
		DEL(m_entities.at(i));
	}
	m_entities.clear();
}

cLevelComp::~cLevelComp() {
	int bosssize = m_boss.size();
	for (int i = 0; i < bosssize; i++) {
		DEL(m_boss[i]);
	}
	m_boss.clear();
	int bsize = m_backgrounds.size();
	for (int i = 0; i < bsize; i++) {
		DEL(m_backgrounds[i]);
	}
	m_backgrounds.clear();
	deleteEntities();
	int usize = m_upgrades.size();
	for (int i = 0; i < usize; i++) {
		DEL(m_upgrades[i]);
	}
	m_upgrades.clear();
}

//Dada una de las mejoras de referencia spawnea una copia de la misma en una posición dentro del nivel
void cLevelComp::SpawnUpgrade(Upgrade* upgrade) {
	vec2 pos = vmake(CORE_FRand(32.0f, m_size.x +32.0f), CORE_FRand(32.0f, m_size.y + 32.0f));
	vec2 vel = { 0.0f, 0.0f };
	Upgrade* entity = NEW(Upgrade,(upgrade));
	cLinearVelComp* linearcomp = NEW(cLinearVelComp,(pos, vel));
	entity->AddComponent(linearcomp);
	cRenderComp* rendercomp = NEW(cRenderComp,(upgrade->GetUpgradeData().loc, upgrade->GetUpgradeData().size, true));
	entity->AddComponent(rendercomp);
	cCollisionComp* enemCollision = NEW(cCollisionComp,(upgrade->GetUpgradeData().size.x));
	entity->AddComponent(enemCollision);
	m_entities.push_back(entity);
}

//Actualiza toda la lógica de una determinada mejora (no se spawnea si ya el usuario la ha consumido
void cLevelComp::UpdateUpgrade(Upgrade* upgrade, Bullet::UpgradeType bulletUpgrade) {
	bool enter = true;
	for (unsigned int i = 0; i < Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetUpgradeType().size(); i++) {
		if (Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetUpgradeType()[i] == bulletUpgrade) {
			enter = false;
			break;
		}
	}
	if (enter) {
		if (upgrade->GetUpgradeTime() >= upgrade->GetUpgradeDelay()) {
			upgrade->SetUpgradeTime(0.0f);
			SpawnUpgrade(upgrade);
		}
	}
}

//Actualiza la lógica de enemigos y del boss
void cLevelComp::Update(float fTimeDiff, Boss* boss) {
	//Si no hay boss crea entidades del nivel
	if (m_enemyAmount > 0) {
		vec2 pos;
		vec2 vel;
		Enemy* entity;
		cRenderComp* rendercomp;
		cCollisionComp* enemCollision;
		if (m_horizontal) {
			pos = vmake(m_size.x - 16.0f, CORE_FRand(16.0f, m_size.y - 16.0f));
			vel = vmake(CORE_FRand(-m_maxEnemySpeed, -m_minEnemySpeed),
				-CORE_FRand(-m_maxEnemySpeed, +m_maxEnemySpeed));
		}
		else {
			pos = vmake(CORE_FRand(16.0f, m_size.x - 16.0f), m_size.y - 16.0f);
			vel = vmake(CORE_FRand(-m_maxEnemySpeed, +m_maxEnemySpeed),
				-CORE_FRand(+m_maxEnemySpeed, +m_minEnemySpeed));
		}
		rendercomp = NEW(cRenderComp,(m_enemySprite.loc, m_enemySprite.size, true));
		enemCollision = NEW(cCollisionComp,(m_enemySprite.size.y));
		entity = NEW(Enemy,(m_enemySprite));
		cLinearVelComp* linearcomp = NEW(cLinearVelComp,(pos, vel));
		entity->AddComponent(linearcomp);
		entity->AddComponent(rendercomp);
		entity->AddComponent(enemCollision);
		m_entities.push_back(entity);

		m_enemyAmount--;
		if (m_enemyAmount <= 0) {
			deleteEntities();
		}
	}
	//En caso de que haya un boss hace toda su lógica y spawnea sus enemigos (proyectiles)
	else if (boss != nullptr && boss->FindComponent<cBossLogicComp>()->GetLifes() > 0) {
		cCreateEnemy crEnemMsg;
		boss->FindComponent<cEnemyComp>()->ReceiveMessage(crEnemMsg);
		boss->FindComponent<cBossLogicComp>()->Slot(fTimeDiff);
		cDamageMsg damage(1);
		boss->ReceiveMessage(damage);
		cChangeRGBA rgbaMsg({ 255, 255, 255, 255 });
		boss->ReceiveMessage(rgbaMsg);
		if (boss->FindComponent<cBossLogicComp>()->GetLifes() <= 0) {
			deleteEntities();
		}
	}
}

void cLevelComp::Slot(float fTimeDiff)
{
	//Cuando pase el tiempo de espera de cada tick del juego se permite la realización de la lógica del nivel
	if (m_time <= 0.0f) {
		//Realiza la lógica de  mejoras
		for (unsigned int s = 0; s < m_upgrades.size(); s++) {
			m_upgrades[s]->UpdateTime(fTimeDiff);
			if (m_upgrades[s]->GetUpgradeType() == Upgrade::Type::BULLET_THREE) {
				UpdateUpgrade(m_upgrades[s], Bullet::UpgradeType::THREE);
			}
			else if (m_upgrades[s]->GetUpgradeType() == Upgrade::Type::BULLET_DAMAGE_UP) {
				UpdateUpgrade(m_upgrades[s], Bullet::UpgradeType::DAMAGE);
			}
		}

		//Realiza la lógica de enemigos
		if (m_enemyAmount > 0) {
			Update(fTimeDiff);
		}
		else if (!m_boss.empty()) {
			for (unsigned int i = 0; i < m_boss.size(); i++) {
				if (m_boss[i]->FindComponent<cBossLogicComp>()->GetContinue(fTimeDiff)) {
					Update(fTimeDiff, m_boss[i]);
				}
			}
		}

		//Elimina las entidades que estan marcadas para morir
		for (unsigned int i = 0; i < m_entities.size(); i++) {
			m_entities[i]->Slot(fTimeDiff);
			if (!m_entities[i]->GetIsAlive()) {
				cEntity* enem = dynamic_cast<cEntity*>(m_entities[i]);
				m_entities.erase(m_entities.begin() + i);
				cGraphicsEngine::GetInstance().DeleteRenderObj(*enem->FindComponent<cRenderComp>()->GetSprite());
				DEL(enem);
				i--;
			}
		}
		m_time = m_waitTime;
	}
	m_time -= fTimeDiff;
}

void cLevelComp::ReceiveMessage(cMessage &message)
{
	const cDeleteEntitiesMsg* pMsg = dynamic_cast<const cDeleteEntitiesMsg *>(&message);
	if (pMsg != nullptr) {
		deleteEntities();
		return;
	}
	const cDrawBossMsg* pMsg5 = dynamic_cast<const cDrawBossMsg *>(&message);
	if (pMsg5 != nullptr) {
		if (!m_boss.empty() && m_enemyAmount <= 0) {
			for (unsigned int i = 0; i < m_boss.size(); i++) {
				if (m_boss[i]->FindComponent<cLifeComp>()->GetLifes() > 0) {
					m_boss[i]->FindComponent<cRenderComp>()->GetSprite()->Render();
				}
			}
		}
		return;
	}
	const cResetMsg *rMsg = dynamic_cast<const cResetMsg *>(&message);
	if (rMsg != nullptr) {
		m_enemyAmount = m_initEnemyAmount;
		m_upgradeTime = 0.0f;
		for (unsigned int j = 0; j < GetBoss().size(); j++) {
			GetBoss()[j]->ReceiveMessage(message);
		}
		return;
	}
	//Si recibe el mensaje de añadir una bala o un enemigo al conjunto de entidades lo añadirá
	cAddBullet * bulletMsg = dynamic_cast<cAddBullet*>(&message);
	if (bulletMsg != nullptr) {
		m_entities.push_back(bulletMsg->GetBullet());
		return;
	}
	cAddEnemy * enemMsg = dynamic_cast<cAddEnemy*>(&message);
	if (enemMsg != nullptr) {
		m_entities.push_back(enemMsg->GetEnemy());
		return;
	}
	//En cuanto reciba del World que debe ser escrito el diálogo, el nivel enviará el texto a la interfaz para que sea escrito
	const cDrawInitTextsMsg* pMsg6 = dynamic_cast<const cDrawInitTextsMsg *>(&message);
	if (pMsg6 != nullptr) {
		if (!pMsg6->GetInitTextRead() && static_cast<unsigned int>(pMsg6->GetDialogueIndex()) < m_initTexts.size()) {
			const char * text = m_initTexts.at(pMsg6->GetDialogueIndex()).c_str();
			vec2 pos = { m_size.x / 2.0f - (m_initTexts.at(pMsg6->GetDialogueIndex()).length()*16.0f) / 2.0f, m_size.y / 2.0f };
			cInterfaceController::GetInstance().WriteDialogue(text, &pos);
		}
		return;
	}
	const cDrawBossTextsMsg* pMsg7 = dynamic_cast<const cDrawBossTextsMsg *>(&message);
	if (pMsg7 != nullptr) {
		if (pMsg7->GetInitTextRead() && !pMsg7->GetBossTextRead() && m_enemyAmount<=0 && static_cast<unsigned int>(pMsg7->GetDialogueIndex()) < m_bossTexts.size()) {
			const char * text = m_bossTexts.at(pMsg7->GetDialogueIndex()).c_str();
			vec2 pos = { m_size.x / 2.0f - (m_bossTexts.at(pMsg7->GetDialogueIndex()).length()*16.0f) / 2.0f, m_size.y / 2.0f };
			cInterfaceController::GetInstance().WriteDialogue(text, &pos);
		}
		return;
	}
	const cDrawFinalTextsMsg* pMsg8 = dynamic_cast<const cDrawFinalTextsMsg *>(&message);
	if (pMsg8 != nullptr) {
		if ( m_boss[0]->FindComponent<cBossLogicComp>()->GetLifes() <= 0 && pMsg8->GetInitTextRead() && pMsg8->GetBossTextRead() && !pMsg8->GetEndTextRead() && static_cast<unsigned int>(pMsg8->GetDialogueIndex()) < m_finalTexts.size()) {
			const char * text = m_finalTexts.at(pMsg8->GetDialogueIndex()).c_str();
			vec2 pos = { m_size.x / 2.0f - (m_finalTexts.at(pMsg8->GetDialogueIndex()).length()*16.0f) / 2.0f, m_size.y / 2.0f };
			cInterfaceController::GetInstance().WriteDialogue(text, &pos);
		}
		return;
	}
	const cResetDialogue* pMsg9 = dynamic_cast<const cResetDialogue *>(&message);
	if (pMsg9 != nullptr) {
		cInterfaceController::GetInstance().WriteDialogue("");
		return;
	}
}