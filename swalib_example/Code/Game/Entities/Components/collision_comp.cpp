#include "../../../../../common/stdafx.h"
#include "collision_comp.h"
#include <assert.h>
#include "../entity.h"
#include "../../Managers/world.h"
#include ".././../../../../common/sys.h"
#include "../Messages/collision_msg.h"
#include "../Messages/new_pos_msg.h"
#include "../Player.h"
#include "../Messages/damage_msg.h"
#include "../Bullet.h"
#include "../Boss.h"
#include "../Messages/render_msg.h"
#include "../Upgrade.h"
#include "../Messages/entity_msg.h"
#include "../../Managers/Level.h"

cCollisionComp::cCollisionComp(float fRadius) : m_fRadius(fRadius)
	, m_vPos(vmake(0.0f, 0.0f))
{}

void cCollisionComp::Slot(float fTimeDiff)
{
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	const Enemy* enemy = dynamic_cast<const Enemy*>(pOwnEnt);
	//Se obtiene el componente de colisión del jugador para comprobar si colisiona con él
	cCollisionComp *pCollCompEnt = Player::GetPlayer()->FindComponent<cCollisionComp>();
	float flimit2 = (m_fRadius + pCollCompEnt->GetRadius());
	//Comprobación de colisión con el jugador
	if (enemy!=nullptr && vlen2(vsub(m_vPos, pCollCompEnt->GetPos())) <= flimit2) {
		cDamageMsg damagePlayer(1);
		Player::GetPlayer()->ReceiveMessage(damagePlayer);
	}
	//Comprobación de que los enemigos salen del mapa (serán eliminados) World::GetWorld()->GetWorldSize().x 
	if (enemy != nullptr && (m_vPos.x < 0.0f || m_vPos.x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x||
		m_vPos.y < 0.0f || m_vPos.y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
		GetOwner()->SetDead();
	}

	//Si estamos en la fase de boss (no quedan enemigos de nivel restantes y solo queda el boss y sus enemigos)
	if (Level::GetLevels().at(World::GetWorld()->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() <= 0 && 
		!Level::GetLevels().at(World::GetWorld()->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty()) {
		Boss* boss = Level::GetLevels().at(World::GetWorld()->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0];
		cCollisionComp *pCollCompEnt2 = boss->FindComponent<cCollisionComp>();
		float flimit3 = (m_fRadius + pCollCompEnt2->GetRadius());
		const Bullet* bullet = dynamic_cast<const Bullet*>(pOwnEnt);
		//Si el owner es una bala y colisiona con el boss se realiza el daño de la bala al boss y se elimina la bala
		if (bullet != nullptr && vlen2(vsub(m_vPos, pCollCompEnt2->GetPos())) <= flimit3) {
			cDamageMsg damageBoss(bullet->GetBulletDamage());
			boss->ReceiveMessage(damageBoss); 
			cChangeRGBA rgbaMsg({ 255, 255, 0, 0 });
			boss->ReceiveMessage(rgbaMsg);
			GetOwner()->SetDead();
		}
	}

	const Upgrade* upgrade = dynamic_cast<const Upgrade*>(pOwnEnt);
	//Si es una mejora y colisiona con el jugador, se añade la mejora al jugador y se elimina dicha mejora
	if (upgrade != nullptr && vlen2(vsub(m_vPos, pCollCompEnt->GetPos())) <= flimit2) {
		cUpgradeMsg upMsg(upgrade->GetUpgradeType(), upgrade->GetUpgradeAmount());
		Player::GetPlayer()->ReceiveMessage(upMsg);
		GetOwner()->SetDead();
	}

}

void cCollisionComp::ReceiveMessage(cMessage &message)
{
	const cNewPosMsg *pMsg = dynamic_cast<const cNewPosMsg *>(&message);
	//En caso de actualización de posición
	if (pMsg != nullptr){
		const Player* player = dynamic_cast<const Player*>(GetOwner());
		//Si el propietario es el jugador se le mantendrá en los márgenes del mapa
		if (player != nullptr && ((pMsg->GetPos().x < 0.0f || pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x) &&
			(pMsg->GetPos().y < 0.0f || pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y))) {
			return;
		}else if (player != nullptr) {
			if (pMsg->GetPos().x < 0.0f) {
				if (!(pMsg->GetPos().y < 0.0f || pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
					m_vPos = { 0.0f,pMsg->GetPos().y };
				}
				return;
			}else if (pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x) {
				if (!(pMsg->GetPos().y < 0.0f || pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
					m_vPos = { Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x,pMsg->GetPos().y };
				}
				return;
			}else if (pMsg->GetPos().y < 0.0f) {
				if (!(pMsg->GetPos().x < 0.0f || pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x)) {
					m_vPos = { pMsg->GetPos().x,0.0f };
				}
				return;
			}else if (pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y) {
				if (!(pMsg->GetPos().x < 0.0f || pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x)) {
					m_vPos = { pMsg->GetPos().x, Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y };
				}
				return;
			}else {
				m_vPos = pMsg->GetPos();
				return;
			}
		//Si no es el jugador simplemente se seguirá con su lógica
		}else {
			m_vPos = pMsg->GetPos();
			return;
		}
	}
}
