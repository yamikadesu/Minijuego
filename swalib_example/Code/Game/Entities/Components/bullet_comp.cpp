#include "../../../../../common/stdafx.h"
#include "bullet_comp.h"
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
#include "linear_vel_comp.h"
#include "collision_comp.h"
#include "life_comp.h"

cBulletComp::cBulletComp(Bullet* bullet) : m_bullet(bullet), m_delayShootTime(0.0f)
{}

cBulletComp::~cBulletComp() {
	DEL(m_bullet);
}

void cBulletComp::Slot(float fTimeDiff)
{
	//Se actualiza el cooldown restante para el siguiente disparo
	if (m_delayShootTime > 0.0f) {
		m_delayShootTime -= fTimeDiff;
	}
}

void cBulletComp::ReceiveMessage(cMessage &message)
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	const cUpgradeMsg *upMsg = dynamic_cast<const cUpgradeMsg *>(&message);
	if (upMsg != nullptr && player != nullptr) {
		//Dependiendo de la mejora añadirá una u otra al proyectil
		if (upMsg->GetType() == Upgrade::Type::BULLET_THREE) {
			m_bullet->AddUpgradeType(Bullet::UpgradeType::THREE);
		}
		else if (upMsg->GetType() == Upgrade::Type::BULLET_DAMAGE_UP) {
			m_bullet->AddUpgradeType(Bullet::UpgradeType::DAMAGE);
			m_bullet->SetBulletDamage(static_cast<int>(m_bullet->GetBulletDamage()*upMsg->GetAmount()));
			m_bullet->SetBulletData({ m_bullet->GetBulletData().loc, m_bullet->GetBulletData().size, m_bullet->GetBulletData().angle,{ 255, 0, 0, 255 } });
		}
		return;
	}
	const cShoot *shootMsg = dynamic_cast<const cShoot *>(&message);
	//Solo disparará cuando el cooldown restante sea 0
	if (shootMsg != nullptr && m_delayShootTime <= 0.0f) {
		//Para disparar creará una copia de esta bala y le informará al nivel para añadirla a la lista de entidades (proyectiles)
		vec2 pos = vmake(Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().x, Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().y);
		vec2 vel;
		if (Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetHorizontal()) {
			vel = vmake(CORE_FRand(shootMsg->GetBullet()->GetBulletSpeed() - 5.0f, shootMsg->GetBullet()->GetBulletSpeed() + 5.0f), 0.0f);
		}
		else {
			vel = vmake(0.0f, CORE_FRand(shootMsg->GetBullet()->GetBulletSpeed() - 5.0f, shootMsg->GetBullet()->GetBulletSpeed() + 5.0f));
		}
		Bullet* entity = NEW(Bullet,(m_bullet));
		cLinearVelComp* linearcomp = NEW(cLinearVelComp,(pos, vel));
		entity->AddComponent(linearcomp);
		cRenderComp* rendercomp = NEW(cRenderComp,(shootMsg->GetBullet()->GetBulletData().loc, shootMsg->GetBullet()->GetBulletData().size, true));
		entity->AddComponent(rendercomp);
		rendercomp->GetSprite()->SetRGBA(shootMsg->GetBullet()->GetBulletData().rgba);
		cCollisionComp* enemCollision = NEW(cCollisionComp,(shootMsg->GetBullet()->GetBulletData().size.x));
		entity->AddComponent(enemCollision);
		cRotate rotMsg(shootMsg->GetBullet()->GetBulletData().angle);
		entity->ReceiveMessage(rotMsg);
		cAddBullet bulletMsg(entity);
		Level::GetLevels()[World::GetWorld()->GetActualLevel()]->ReceiveMessage(bulletMsg);
		for (unsigned int i = 0; i < entity->GetUpgradeType().size(); i++) {
			//Si tiene la mejora de tres balas se crearán 2 más adicionales con rotación alterada(diferente en el caso de que el nivel sea horizontal o vertical)
			if (entity->GetUpgradeType()[i] == Bullet::UpgradeType::THREE) {
				float speed = CORE_FRand(shootMsg->GetBullet()->GetBulletSpeed() - 5.0f, shootMsg->GetBullet()->GetBulletSpeed() + 5.0f);
				float baseRot = 5.0f;
				float theta = 0.0f;
				vec2 vel2;
				if (Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetHorizontal()) {
					theta = DEG2RAD(baseRot);
					float cs = cos(theta);
					float sn = sin(theta);
					vec2 dir = { cs, sn };
					dir = { dir.x / vlen(dir), dir.y / vlen(dir) };
					vel2 = { speed* dir.x, speed * dir.y };
				}
				else {
					theta = DEG2RAD(90.0f + baseRot);
					float cs = cos(theta);
					float sn = sin(theta);
					vec2 dir = { cs, sn };
					dir = { dir.x / vlen(dir), dir.y / vlen(dir) };
					vel2 = { speed * dir.x, speed * dir.y };
				}
				Bullet* entity2 = NEW(Bullet,(m_bullet));
				cLinearVelComp* linearcomp2 = NEW(cLinearVelComp,(pos, vel2));
				entity2->AddComponent(linearcomp2);
				cRenderComp* rendercomp2 = NEW(cRenderComp,(shootMsg->GetBullet()->GetBulletData().loc, shootMsg->GetBullet()->GetBulletData().size, true));
				entity2->AddComponent(rendercomp2);
				rendercomp2->GetSprite()->SetRGBA(shootMsg->GetBullet()->GetBulletData().rgba);
				cCollisionComp* enemCollision2 = NEW(cCollisionComp,(shootMsg->GetBullet()->GetBulletData().size.x));
				entity2->AddComponent(enemCollision2);
				if (!Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetHorizontal()) {
					theta = DEG2RAD(baseRot);
				}
				cRotate rotMsg2(shootMsg->GetBullet()->GetBulletData().angle + theta);
				entity2->ReceiveMessage(rotMsg2);
				cAddBullet bulletMsg2(entity2);
				Level::GetLevels()[World::GetWorld()->GetActualLevel()]->ReceiveMessage(bulletMsg2);
				float theta2 = 0.0f;
				vec2 vel3;
				if (Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetHorizontal()) {
					theta2 = DEG2RAD(-baseRot);
					float cs2 = cos(theta2);
					float sn2 = sin(theta2);
					vec2 dir2 = { cs2, sn2 };
					dir2 = { dir2.x / vlen(dir2), dir2.y / vlen(dir2) };
					vel3 = { speed* dir2.x, speed * dir2.y };
				}
				else {
					theta2 = DEG2RAD(90.0f - baseRot);
					float cs2 = cos(theta2);
					float sn2 = sin(theta2);
					vec2 dir2 = { cs2, sn2 };
					dir2 = { dir2.x / vlen(dir2), dir2.y / vlen(dir2) };
					vel3 = { speed* dir2.x, speed * dir2.y };
				}
				Bullet* entity3 = NEW(Bullet,(m_bullet));
				cLinearVelComp* linearcomp3 = NEW(cLinearVelComp,(pos, vel3));
				entity3->AddComponent(linearcomp3);
				cRenderComp* rendercomp3 = NEW(cRenderComp,(shootMsg->GetBullet()->GetBulletData().loc, shootMsg->GetBullet()->GetBulletData().size, true));
				rendercomp3->GetSprite()->SetRGBA(shootMsg->GetBullet()->GetBulletData().rgba);
				entity3->AddComponent(rendercomp3);
				cCollisionComp* enemCollision3 = NEW(cCollisionComp,(shootMsg->GetBullet()->GetBulletData().size.x));
				entity3->AddComponent(enemCollision3);
				if (!Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetHorizontal()) {
					theta2 = DEG2RAD(-baseRot);
				}
				cRotate rotMsg3(shootMsg->GetBullet()->GetBulletData().angle + theta2);
				entity3->ReceiveMessage(rotMsg3);
				cAddBullet bulletMsg3(entity3);
				Level::GetLevels()[World::GetWorld()->GetActualLevel()]->ReceiveMessage(bulletMsg3);
			}
		}
		m_delayShootTime = entity->GetDelayTime();
		return;
	}
}


cEnemyComp::cEnemyComp(Enemy* enemy) : m_enemy(enemy)
{}

cEnemyComp::~cEnemyComp() {
	DEL(m_enemy);
}

void cEnemyComp::Slot(float fTimeDiff)
{
}

void cEnemyComp::ReceiveMessage(cMessage &message)
{
	Boss* boss = dynamic_cast<Boss*>(GetOwner());
	const cCreateEnemy *upMsg = dynamic_cast<const cCreateEnemy *>(&message);
	if (upMsg != nullptr && boss!=nullptr) {
		//Se aplica la misma lógica del proyectil (bala) de arriba pero con los enemigos que genera el boss
		vec2 pos;
		vec2 vel;
		Enemy* entity;
		cRenderComp* rendercomp;
		cCollisionComp* enemCollision;
		pos = vmake(boss->FindComponent<cLinearVelComp>()->GetPos().x, boss->FindComponent<cLinearVelComp>()->GetPos().y);
		if (boss->FindComponent<cBossLogicComp>()->GetData().rotateEnemy) {
			vec2 dir = { Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().x - boss->FindComponent<cLinearVelComp>()->GetPos().x,Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().y - boss->FindComponent<cLinearVelComp>()->GetPos().y };
			dir = {CORE_FRand(dir.x - boss->FindComponent<cBossLogicComp>()->GetData().error, dir.x + boss->FindComponent<cBossLogicComp>()->GetData().error),
				CORE_FRand(dir.y - boss->FindComponent<cBossLogicComp>()->GetData().error, dir.y + boss->FindComponent<cBossLogicComp>()->GetData().error) };
			dir = { dir.x / vlen(dir), dir.y / vlen(dir) };
			vec2 y = { 0.0f, -1.0f };
			float dot = vdot(dir, y);
			float mag = vlen(dir)*vlen(y);
			float angle = acos(dot/mag);
			if (Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().x <= boss->FindComponent<cLinearVelComp>()->GetPos().x) {
				angle = -angle;
			}
			cRotate rotMsg(angle);
			boss->ReceiveMessage(rotMsg);
			vel = vmake(boss->FindComponent<cBossLogicComp>()->GetData().maxSpeedEnemy,boss->FindComponent<cBossLogicComp>()->GetData().maxSpeedEnemy);
			vel = { vel.x * dir.x, vel.y * dir.y };
			rendercomp = NEW(cRenderComp,(m_enemy->GetEnemyData().loc, m_enemy->GetEnemyData().size, true));
 			enemCollision = NEW(cCollisionComp,(m_enemy->GetEnemyData().size.x));
			entity = NEW(Enemy,(m_enemy));
			cLinearVelComp* linearcomp = NEW(cLinearVelComp,(pos, vel));
			entity->AddComponent(linearcomp);
			entity->AddComponent(rendercomp);
			entity->AddComponent(enemCollision);
			entity->ReceiveMessage(rotMsg);
		}else {
			vec2 dir = { Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().x - boss->FindComponent<cLinearVelComp>()->GetPos().x,Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos().y - boss->FindComponent<cLinearVelComp>()->GetPos().y };
			dir = { dir.x / vlen(dir), dir.y / vlen(dir) };
			vel = vmake(CORE_FRand(-boss->FindComponent<cBossLogicComp>()->GetData().maxSpeedEnemy, +boss->FindComponent<cBossLogicComp>()->GetData().maxSpeedEnemy),
				CORE_FRand(+boss->FindComponent<cBossLogicComp>()->GetData().minSpeedEnemy, +boss->FindComponent<cBossLogicComp>()->GetData().maxSpeedEnemy));
			vel = { vel.x * dir.x, vel.y * dir.y };
			rendercomp = NEW(cRenderComp,(m_enemy->GetEnemyData().loc, m_enemy->GetEnemyData().size, true));
			enemCollision = NEW(cCollisionComp,(m_enemy->GetEnemyData().size.x));
			entity = NEW(Enemy,(m_enemy));
			cLinearVelComp* linearcomp = NEW(cLinearVelComp,(pos, vel));
			entity->AddComponent(linearcomp);
			entity->AddComponent(rendercomp);
			entity->AddComponent(enemCollision);
		}
		cAddEnemy enemMsg(entity);
		Level::GetLevels()[World::GetWorld()->GetActualLevel()]->ReceiveMessage(enemMsg);
	}
}