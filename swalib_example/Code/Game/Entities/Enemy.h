#pragma once
#include "Entity.h"
#include "../Graphics/sprite.h"

class Enemy : public cEntity {
public:
	Enemy(SpriteData enemyData) : m_enemyData(enemyData) {};
	Enemy(Enemy* enemy) : m_enemyData(enemy->GetEnemyData()) {};
	inline SpriteData GetEnemyData() { return m_enemyData; };
	inline void SetEnemyData(SpriteData enemyData) { m_enemyData = enemyData; };
private:
	//Datos del sprite del enemigo
	SpriteData m_enemyData;
};