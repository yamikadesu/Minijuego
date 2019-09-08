#ifndef _NEW_POS_MSG_H_
#define _NEW_POS_MSG_H_

#include "message.h"

class cNewPosMsg : public cMessage
{
private:
	//Nueva posición
	vec2 m_vPos;

public:
	cNewPosMsg(const vec2 &vPos) : m_vPos(vPos)
	{}

	inline const vec2 &GetPos() const { return m_vPos; }
};

class cContinueBossLogicMsg : public cMessage
{};

#endif // !_NEW_POS_MSG_H_
