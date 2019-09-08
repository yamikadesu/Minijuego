#pragma once
#include "Entity.h"
#include "../Graphics/sprite.h"
#include <vector>

using namespace std;

class Bullet : public cEntity {
public:
	//Tipo de mejora
	enum UpgradeType {
		NONE,
		THREE,
		DAMAGE
	};
	Bullet(SpriteData bulletData, float bulletSpeed, int bulletDamage, float delayTime) : m_bulletData(bulletData), m_bulletSpeed(bulletSpeed), m_bulletDamage(bulletDamage), m_delayTime(delayTime){};
	Bullet(Bullet* bullet) : m_bulletData(bullet->GetBulletData()), m_bulletSpeed(bullet->GetBulletSpeed()), m_bulletDamage(bullet->GetBulletDamage()), m_delayTime(bullet->GetDelayTime()), m_bulletUpgrade(bullet->GetUpgradeType()) {};
	inline const SpriteData GetBulletData() const { return m_bulletData; };
	inline void SetBulletData(SpriteData bulletData) { m_bulletData = bulletData; };
	inline float const GetBulletSpeed() const { return m_bulletSpeed; };
	inline void SetBulletSpeed(float bulletSpeed) { m_bulletSpeed = bulletSpeed; };
	inline int const GetBulletDamage() const { return m_bulletDamage; };
	inline void SetBulletDamage(int bulletDamage) { m_bulletDamage = bulletDamage; };
	inline float const GetDelayTime() const { return m_delayTime; };
	inline void SetDelayTime(float delayTime) { m_delayTime = delayTime; };
	inline const vector<UpgradeType> GetUpgradeType() const { return m_bulletUpgrade; };
	inline void AddUpgradeType(UpgradeType bulletUpgrade) { m_bulletUpgrade.push_back(bulletUpgrade); };
	void RemoveUpgradeType(UpgradeType bulletUpgrade);
	inline void ClearUpgrades() { m_bulletUpgrade.clear(); };
private:
	//Datos del Sprite de la bala
	SpriteData m_bulletData;
	//Velocidad de la bala
	float m_bulletSpeed;
	//Daño de la bala
	int m_bulletDamage;
	//Cooldown de disparo
	float m_delayTime;
	//Mejoras de la bala
	vector<UpgradeType> m_bulletUpgrade;
};