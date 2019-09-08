#ifndef _LINEAR_VEL_COMP_H_
#define _LINEAR_VEL_COMP_H_

#include "../../../../../common/core.h"
#include "component.h"

class cLinearVelComp : public cComponent
{
private:
	//Posición
	vec2	m_vPos;
	//Velocidad
	vec2	m_vVel;

public:
	cLinearVelComp(vec2 pos, vec2 vel);

	virtual void Slot(float fTimeDiff) override;
	inline const vec2 &GetPos() const { return m_vPos; }
	inline void SetPos(const vec2& vPos) { m_vPos = vPos; }
	inline const vec2 &GetVel() const { return m_vVel; }
	inline void SetVel(const vec2& vVel) { m_vVel = vVel; }

	virtual void ReceiveMessage(cMessage &message) override;
};

#endif // !_LINEAR_VEL_COMP_H_
