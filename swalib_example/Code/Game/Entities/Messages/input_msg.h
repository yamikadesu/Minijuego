#pragma once
#ifndef _NEW_INPUT_MSG_H_
#define _NEW_INPUT_MSG_H_

#include "message.h"


class cPassDialogMsg : public cMessage
{
};

class cResetWorldMsg : public cMessage
{
};

class cDialogLogicMsg : public cMessage
{
private:
	float m_time;

public:
	cDialogLogicMsg(const float &vPos) : m_time(vPos)
	{}

	inline const float &GetTime() const { return m_time; }
};

class cMovePlayerMsg : public cMessage
{
private:
	vec2 m_pos;

public:
	cMovePlayerMsg(const vec2 &vPos) : m_pos(vPos)
	{}

	inline const vec2 &GetPos() const { return m_pos; }
};

class cShootPlayerMsg : public cMessage
{
};

class cDrawDialogMsg : public cMessage
{
};

#endif // !_NEW_POS_MSG_H_
