#ifndef _SOUND_COMP_H_
#define _SOUND_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"

class cWorld;

class cSoundComp : public cComponent
{
private:

public:
	cSoundComp();
	virtual void Slot(float fTimeDiff) override;
	virtual void ReceiveMessage(cMessage &message) override;
};

#endif // !_COLLISION_COMP_H_
