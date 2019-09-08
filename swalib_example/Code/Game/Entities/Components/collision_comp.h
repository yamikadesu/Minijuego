#ifndef _COLLISION_COMP_H_
#define _COLLISION_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"

class cLinearVelComp;

class cCollisionComp : public cComponent
{
private:
	//Radio de colisión
	float m_fRadius;
	//La posición de la colisión puede diferir de la posición lógica
	vec2 m_vPos;

public:
	cCollisionComp(float fRadius);
	virtual void Slot(float fTimeDiff) override;
	inline float GetRadius() const { return m_fRadius; }
	inline const vec2 &GetPos() const { return m_vPos; }
	virtual void ReceiveMessage(cMessage &message) override;

};

#endif // !_COLLISION_COMP_H_
