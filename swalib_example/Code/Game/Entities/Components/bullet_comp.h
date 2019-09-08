#ifndef _BULLET_COMP_H_
#define _BULLET_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"
#include "../Bullet.h"
#include "../Enemy.h"

//Componente encargado de los proyectiles aliados (del jugador)
class cBulletComp : public cComponent
{
private:
	//Proyectil (es una referencia de un proyectil no un proyectil spawneado)
	Bullet * m_bullet;
	//Cooldown actual
	float m_delayShootTime;

public:
	cBulletComp(Bullet* bullet);
	~cBulletComp();
	virtual void Slot(float fTimeDiff) override;
	inline Bullet* GetBullet() { return m_bullet; };
	inline void SetBullet(Bullet* bullet) { m_bullet = bullet; };
	virtual void ReceiveMessage(cMessage &message) override;

};

//Componente encargado de los proyectiles enemigos (del boss)
class cEnemyComp : public cComponent
{
private:
	//Proyectil enemigo
	Enemy * m_enemy;
public:
	cEnemyComp(Enemy* enemy);
	~cEnemyComp();
	virtual void Slot(float fTimeDiff) override;
	inline Enemy* GetEnemy() { return m_enemy; };
	inline void SetEnemy(Enemy* enemy) { m_enemy = enemy; };
	virtual void ReceiveMessage(cMessage &message) override;

};

#endif // !_COLLISION_COMP_H_
