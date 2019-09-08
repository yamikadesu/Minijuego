#include "../../../../../common/stdafx.h"
#include "life_comp.h"
#include "render_comp.h"
#include "../Entity.h"
#include "../Enemy.h"
#include "../Player.h"
#include "../Boss.h"
#include <assert.h>
#include "../Messages/damage_msg.h"
#include "../Messages/reset_msg.h"
#include "../Messages/new_pos_msg.h"
#include "../../Managers/InterfaceController.h"
#include "../Messages/entity_msg.h"
#include "bullet_comp.h"
#include "linear_vel_comp.h"
#include "../Messages/render_msg.h"
#include "../../Managers/world.h"

cLifeComp::cLifeComp(int lifes, float invTime, float invTicksTime, float blankTime) : m_lifes(lifes)
, m_inv(false), m_invTime(invTime), m_waitTime(0.0f), m_initLifes(lifes), m_invTicksTime(invTicksTime), m_blankTime(blankTime)
{}

void cLifeComp::Slot(float fTimeDiff)
{
	//Si el jugador se encuentra invulnerable irá parpadeando de forma constante indicado por los parámetros de entrada
	if (m_inv) {
		m_waitTime += static_cast<float>(fTimeDiff);
		if (m_waitTime >= m_invTime) {
			m_waitTime = 0.0f;
			m_inv = false;
			cDrawMsg setRenderMsg;
			GetOwner()->ReceiveMessage(setRenderMsg);
		}else {
			cInvMsg invMsg(static_cast<float>(fTimeDiff));
			GetOwner()->ReceiveMessage(invMsg);
		}
	}
}

void cLifeComp::ReceiveMessage(cMessage &message)
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	const Boss* boss = dynamic_cast<const Boss*>(GetOwner());
	//Si recibe daño se actualiza la vida, la interfaz y se hace invulnerable al jugador
	const cDamageMsg *pMsg = dynamic_cast<const cDamageMsg *>(&message);
	if (pMsg != nullptr && player!=nullptr && !m_inv) {
		m_lifes -= pMsg->GetDamage();
		cInterfaceController::GetInstance().UpdatePlayerHealth(true);
		if (m_lifes > 0) {
			m_inv = true;
			cNotDrawMsg notmsg;
			player->ReceiveMessage(notmsg);
			return;
		}else {
			GetOwner()->SetDead();
			return;
		}
	}
	const cResetMsg *rMsg = dynamic_cast<const cResetMsg *>(&message);
	if (rMsg != nullptr && (player != nullptr || boss != nullptr)) {
		m_lifes = m_initLifes;
		player->FindComponent<cBulletComp>()->GetBullet()->ClearUpgrades();
		return;
	}
}

cBossLogicComp::cBossLogicComp(std::vector<vec3> poss, float roundWait, float initWait, bool random, int lifes, bossEnem enemyData)
	: m_index(random ? -1 : 0), m_poss(poss), m_roundWait(roundWait), m_time(initWait),
	m_timePos(random ? CORE_FRand(poss[0].z, poss[0].z + 0.02f) + initWait : poss[0].z + initWait),
	m_continue(true), m_enemyData(enemyData)
{
	m_lifes = lifes;
	m_initLifes = lifes;
}

void cBossLogicComp::Slot(float fTimeDiff) {
	//Realiza toda la lógica de cambiar de posición y con el m_continue informa al nivel que se puede crear una nueva entidad
	m_time -= static_cast<float>(fTimeDiff);
	if (!m_poss.empty()) {
		m_timePos -= static_cast<float>(fTimeDiff);
		if (m_timePos <= 0.0f) {
			const Boss* boss = dynamic_cast<const Boss*>(GetOwner());
			if (m_index != -1) {
				m_index = (m_index + 1) % m_poss.size();
				vec2 pos = { m_poss[m_index].x, m_poss[m_index].y };
				cNewPosMsg newpos(pos);
				boss->ReceiveMessage(newpos);
				m_timePos = m_poss[m_index].z;
			}
			else {
				int i = rand() % m_poss.size();
				vec2 pos = { m_poss[i].x, m_poss[i].y };
				cNewPosMsg newpos(pos);
				boss->ReceiveMessage(newpos);
				this->m_timePos = m_poss[i].z;
			}
		}
	}
	if (!m_continue && m_time <= 0 && m_lifes > 0) {
		m_continue = true;
	}
}

//Función que indica si el boss puede continuar con su lógica
bool cBossLogicComp::GetContinue(float fTimeDiff) {
	Slot(fTimeDiff);
	return m_continue;
}

void cBossLogicComp::ReceiveMessage(cMessage &message) {
	//Si recibe este mensaje volverá a esperar hasta poder disparar de nuevo
	const cContinueBossLogicMsg *pMsg = dynamic_cast<const cContinueBossLogicMsg *>(&message);
	if (pMsg != nullptr) {
		m_time = m_roundWait;
		m_continue = false;
		return;
	}
	//Una vez recibe daño actualiza su bossLogic así hacemos que solo reciba daño cuando termine el tiempo (una invulnerabilidad para el boss)
	const Boss* boss = dynamic_cast<const Boss*>(GetOwner());
	const cDamageMsg *pMsg1 = dynamic_cast<const cDamageMsg *>(&message);
	if (pMsg1 != nullptr && boss != nullptr && boss->FindComponent<cBossLogicComp>()->GetTime() <= 0) {
		m_lifes -= pMsg1->GetDamage();
		cInterfaceController::GetInstance().UpdateBossHealth(true);
		cContinueBossLogicMsg notmsg;
		boss->ReceiveMessage(notmsg);
		return;
	}
	const cResetMsg *rMsg = dynamic_cast<const cResetMsg *>(&message);
	if (rMsg != nullptr && boss != nullptr) {
		m_lifes = m_initLifes;
		vec2 pos = { m_poss[0].x, m_poss[0].y };
		cNewPosMsg newpos(pos);
		boss->ReceiveMessage(newpos);
		return;
	}
}