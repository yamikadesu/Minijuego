#pragma once
#ifndef _NEW_MENU_MSG_H_
#define _NEW_MENU_MSG_H_

#include "message.h"

class cClickMsg : public cMessage
{
private:
	vec2 m_pos;

public:
	cClickMsg(const vec2 &vPos) : m_pos(vPos)
	{}

	inline const vec2 &GetPos() const { return m_pos; }
};

class cClickButtonMsg : public cMessage
{
private:
	void * m_data;

public:
	cClickButtonMsg(void * data) : m_data(data)
	{}

	inline void* GetData() const { return m_data; }
};


#endif // !_NEW_POS_MSG_H_
