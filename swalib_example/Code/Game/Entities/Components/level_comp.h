#pragma once
#ifndef _NEW_LEVEL_COMP_H_
#define _NEW_LEVEL_COMP_H_

#include "../../../../../common/core.h"
#include "../../Graphics/Background.h"
#include "../Boss.h"
#include "component.h"
#include "../Enemy.h"
#include "../Bullet.h"
#include <vector>
#include <string>
#include "../Upgrade.h"

using namespace std;

//Este es el componente que gestionará toda la lógica del nivel actual
class cLevelComp : public cComponent
{
public:
	cLevelComp(vector<string> initTexts, vector<string> bossTexts, vector<string> finalTexts, float initWait, float waitTime, SpriteData enemySprite, vector<Boss*> boss,
		float maxEnemySpeed, float minEnemySpeed, vector<cBackground*> backgrounds, bool horizontal, int enemyAmount, vec2 size, vector<Upgrade*> upgrades);
	~cLevelComp();

	virtual void Slot(float fTimeDiff) override;

	virtual void ReceiveMessage(cMessage &message) override;

	inline const vector<string> &GetInitTexts() const { return m_initTexts; }
	inline void SetInitTexts(vector<string> initTexts) { m_initTexts = initTexts; }
	inline const vector<string> &GetBossTexts() const { return m_bossTexts; }
	inline void SetBossTexts(vector<string> bossTexts) { m_bossTexts = bossTexts; }
	inline const vector<string> &GetFinalTexts() const { return m_finalTexts; }
	inline void SetFinalTexts(vector<string> finalTexts) { m_finalTexts = finalTexts; }
	inline const float &GetInitWait() const { return m_initWait; }
	inline void SetInitWait(float initWait) { m_initWait = initWait; }
	inline const float &GetWaitTime() const { return m_waitTime; }
	inline void SetWaitTime(float waitTime) { m_waitTime = waitTime; }
	inline const SpriteData &GetEnemySprite() const { return m_enemySprite; }
	inline void SetEnemySprite(SpriteData enemySprite) { m_enemySprite = enemySprite; }
	//El primer boss del vector se considera el boss principal del nivel (su barra de vida etc)
	inline vector<Boss*> GetBoss() { return m_boss; }
	inline const float &GetMaxSpeed() const { return m_maxEnemySpeed; }
	inline void SetMaxSpeed(float maxspeed) { m_maxEnemySpeed = maxspeed; }
	inline const float &GetMinSpeed() const { return m_minEnemySpeed; }
	inline void SetMinSpeed(float minspeed) { m_minEnemySpeed = minspeed; }
	inline const vector<cBackground*> &GetBackgrounds() const { return m_backgrounds; }
	inline void SetBackgrounds(vector<cBackground*> backgrounds) { m_backgrounds = backgrounds; }
	inline const bool &GetHorizontal() const { return m_horizontal; }
	inline void SetHorizontal(bool horizontal) { m_horizontal = horizontal; }
	inline const int &GetEnemyAmount() const { return m_enemyAmount; }
	inline void SetEnemyAmount(int amount) { m_enemyAmount = amount; }
	inline const vector<cEntity*> &GetEntities() const { return m_entities; }
	inline void SetEntities(vector<cEntity*> entities) { m_entities = entities; }
	inline const vec2 &GetLevelSize() const { return m_size; }
	inline void SetLevelSize(vec2 size) { m_size = size; }
	inline const vector<Upgrade*> &GetUpgrades() const { return m_upgrades; }
	inline void SetUpgrades(vector<Upgrade*> upgrades) { m_upgrades = upgrades; }

protected:
	//Variable que acumula el tiempo que ha pasado
	float m_time;
	//Variables de los dialogos iniciales, al iniciar el boss y al final del nivel
	vector<string> m_initTexts;
	vector<string> m_bossTexts;
	vector<string> m_finalTexts;
	//Tiempo de espera inicial antes de empezar el nivel
	float m_initWait;
	//Tiempo de espera entre enemigo y enemigo (sirve para ajustar el nivel de dificultad junto con la velocidad de los enemigos)
	float m_waitTime;
	//Información del sprite de dichos enemigos
	SpriteData m_enemySprite;
	//Bosses del nivel
	vector<Boss*> m_boss;
	//Velocidad máxima y mínima de los enemigos del nivel (no incluye los del boss)
	float m_maxEnemySpeed;
	float m_minEnemySpeed;
	//Fondos del nivel
	vector<cBackground*> m_backgrounds;
	//Indica si el nivel es horizontal o vertical
	bool m_horizontal;
	//Cantidad de enemigos restantes del nivel (no incluye los del boss)
	int m_enemyAmount;
	//Cantidad inicial de enemigos (para poder reiniciar el nivel correctamente)
	int m_initEnemyAmount;
	//Entidades actuales del nivel
	vector<cEntity*> m_entities;
	//Tamaño del nivel actual
	vec2 m_size;
	//Mejoras disponibles (que pueden spawnear) del nivel
	vector<Upgrade*> m_upgrades;
	//Tiempo de cooldown entre spawn de mejora
	float m_upgradeTime;
	void deleteEntities();
	void SpawnUpgrade(Upgrade* upgrade);
	void UpdateUpgrade(Upgrade* upgrade, Bullet::UpgradeType bulletUpgrade);
	void Update(float fTimeDiff, Boss* boss = nullptr);
};

#endif // !_LINEAR_VEL_COMP_H_
