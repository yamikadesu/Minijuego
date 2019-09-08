#ifndef _COLLISION_MSG_H_
#define _COLLISION_MSG_H_

#include "message.h"

class cEntity;

class cCollisionMsg : public cMessage
{
};

class cEntCollisionMsg : public cCollisionMsg
{
private:
	// Entidad a colisionar
	cEntity	*m_EntToColl;	

public:
	cEntCollisionMsg(cEntity &ent) : m_EntToColl(&ent)
	{}

	inline const cEntity *GetEntToColl() const { return m_EntToColl; }
};

#endif // !_COLLISION_MSG_H_

