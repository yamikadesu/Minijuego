#pragma once
#ifndef _NEW_DAMAGE_MSG_H_
#define _NEW_DAMAGE_MSG_H_

#include "message.h"

class cDamageMsg : public cMessage
{
private:
	//Daño causado
	int	m_damage;

public:
	cDamageMsg(int damage) : m_damage(damage)
	{}

	inline const int &GetDamage() const { return m_damage; }
};

class cInvMsg : public cMessage
{
private:
	//Tiempo de invulnerabilidad
	float m_time;
public:
	cInvMsg(float time) : m_time(time)
	{}

	inline const float &GetTime() const { return m_time; }
};

class cNotDrawMsg : public cMessage
{
};

class cDrawMsg : public cMessage
{
};

#endif // !_NEW_POS_MSG_H_
