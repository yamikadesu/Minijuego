#pragma once
#ifndef _NEW_ENTITY_MSG_H_
#define _NEW_ENTITY_MSG_H_

#include "message.h"
#include "../../Graphics/sprite.h"
#include "../Bullet.h"
#include "../Upgrade.h"
#include "../Enemy.h"

class cShoot : public cMessage
{
private:
	//Proyectil (jugador)
	Bullet * m_bullet;
public:
	cShoot(Bullet* bullet) : m_bullet(bullet)
	{}

	inline const Bullet* GetBullet() const { return m_bullet; }
};

class cUpgradeMsg : public cMessage
{
private:
	//Tipo de mejora y cantidad de la mejora
	Upgrade::Type m_upgradeType;
	float m_amount;
public:
	cUpgradeMsg(Upgrade::Type type, float amount) : m_upgradeType(type), m_amount(amount)
	{}

	inline const Upgrade::Type GetType() const { return m_upgradeType; };
	inline const float GetAmount() const { return m_amount; };
};

class cAddBullet : public cMessage
{
private:
	//Añade esta bala al nivel
	Bullet * m_bullet;
public:
	cAddBullet(Bullet* bullet) : m_bullet(bullet)
	{}

	inline Bullet* GetBullet() { return m_bullet; }
};

class cCreateEnemy : public cMessage
{};

class cAddEnemy : public cMessage
{
private:
	//Añade este enemigo al nivel
	Enemy * m_enemy;
public:
	cAddEnemy(Enemy* enemy) : m_enemy(enemy)
	{}

	inline Enemy* GetEnemy() { return m_enemy; }
};

#endif // !_NEW_POS_MSG_H_