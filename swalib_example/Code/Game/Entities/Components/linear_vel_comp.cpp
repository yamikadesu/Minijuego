#include "../../../../../common/stdafx.h"
#include "linear_vel_comp.h"
#include "render_comp.h"
#include "../entity.h"
#include <assert.h>
#include "../Messages/new_pos_msg.h"
#include "../Messages/collision_msg.h"
#include "../../Managers/world.h"
#include "../Player.h"


cLinearVelComp::cLinearVelComp(vec2 pos, vec2 vel) : m_vPos(pos)
, m_vVel(vel)
{}

void cLinearVelComp::Slot(float fTimeDiff)
{
	cEntity *pEnt = GetOwner();
	assert(pEnt != nullptr);
	const Player* player = dynamic_cast<const Player*>(pEnt);
	vec2 vec2Vel = vscale(m_vVel, fTimeDiff);
	vec2 newPos = vadd(m_vPos, vec2Vel);

	//Evitamos que el jugador salga del mapa
	if (player != nullptr && ((newPos.x < 0.0f || newPos.x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x) &&
		(newPos.y < 0.0f || newPos.y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y))) {

	}
	else if (player != nullptr) {
		if (newPos.x < 0.0f) {
			if (!(newPos.y < 0.0f || newPos.y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
				m_vPos = { 0.0f,newPos.y };
			}
		}
		else if (newPos.x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x) {
			if (!(newPos.y < 0.0f || newPos.y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
				m_vPos = { Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x,newPos.y };
			}
		}
		else if (newPos.y < 0.0f) {
			if (!(newPos.x < 0.0f || newPos.x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x)) {
				m_vPos = { newPos.x,0.0f };
			}
		}
		else if (newPos.y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y) {
			if (!(newPos.x < 0.0f || newPos.x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x)) {
				m_vPos = { newPos.x, Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y };
			}
		}
		else {
			//En caso contrario permitimos el movimiento
			m_vPos = newPos;
		}
	}
	else {
		//En caso contrario permitimos el movimiento
 		m_vPos = newPos;
	}

	cNewPosMsg msg(m_vPos);
	pEnt->ReceiveMessage(msg);
}

void cLinearVelComp::ReceiveMessage(cMessage &message)
{}
