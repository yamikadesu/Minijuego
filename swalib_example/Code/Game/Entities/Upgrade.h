#pragma once
#include "Entity.h"
#include "../Graphics/sprite.h"

class Upgrade : public cEntity {
public:
	//Tipos de mejoras
	enum Type {
		BULLET_THREE, 
		BULLET_DAMAGE_UP
	};
	Upgrade(SpriteData upgradeData, Type upgradeType, float upgradeAmount, float upgradeDelay) : m_upgradeData(upgradeData), m_upgradeType(upgradeType), m_upgradeAmount(upgradeAmount), m_upgradeDelay(upgradeDelay), m_upgradeTime(0.0f) {};
	Upgrade(Upgrade* upgrade): m_upgradeData(upgrade->GetUpgradeData()), m_upgradeType(upgrade->GetUpgradeType()), m_upgradeAmount(upgrade->GetUpgradeAmount()), m_upgradeDelay(upgrade->GetUpgradeDelay()), m_upgradeTime(0.0f) {};
	inline const SpriteData GetUpgradeData() const { return m_upgradeData; };
	inline void SetUpgradeData(SpriteData upgradeData) { m_upgradeData = upgradeData; };
	inline const Type GetUpgradeType() const { return m_upgradeType; };
	inline void SetUpgradeType(Type upgradeType) { m_upgradeType = upgradeType; };
	inline float const GetUpgradeAmount() const { return m_upgradeAmount; };
	inline void SetUpgradeAmount(float upgradeAmount) { m_upgradeAmount = upgradeAmount; };
	inline float const GetUpgradeDelay() const { return m_upgradeDelay; };
	inline void SetUpgradeDelay(float upgradeDelay) { m_upgradeDelay = upgradeDelay; };
	inline float const GetUpgradeTime() const { return m_upgradeTime; };
	inline void SetUpgradeTime(float upgradeTime) { m_upgradeTime = upgradeTime; };
	inline void UpdateTime(float upgradeTime) { m_upgradeTime += upgradeTime; };
private:
	//Datos del sprite de la mejora
	SpriteData m_upgradeData;
	//Tipo de la mejora
	Type m_upgradeType;
	//Cantidad de la mejora (puede ser usado de diferentes formas, ya sea cantidad del daño, color, número de balas... cualquier cosa que pueda indicar un float)
	float m_upgradeAmount;
	//Delay de aparición de la mejora
	float m_upgradeDelay;
	//Variable que va acumulando el tiempo actual (para ver si hemos llegado al delay)
	float m_upgradeTime;
};