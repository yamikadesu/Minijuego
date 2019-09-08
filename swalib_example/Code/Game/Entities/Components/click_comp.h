#ifndef _CLICK_COMP_H_
#define _CLICK_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"

class cClickComp : public cComponent
{
private:

public:
	cClickComp();
	virtual void Slot(float fTimeDiff) override;
	virtual void ReceiveMessage(cMessage &message) override;

};

#endif // !_COLLISION_COMP_H_
