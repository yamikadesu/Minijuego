#include "../../../../../common/stdafx.h"
#include "click_comp.h"
#include <assert.h>
#include "../entity.h"
#include "../../Managers/world.h"
#include ".././../../../../common/sys.h"
#include "../Messages/collision_msg.h"
#include "../Messages/new_pos_msg.h"
#include "../Player.h"
#include "../Messages/damage_msg.h"
#include "../Bullet.h"
#include "../Boss.h"
#include "../Messages/render_msg.h"
#include "../Upgrade.h"
#include "../Messages/entity_msg.h"
#include "../../Managers/Level.h"
#include "../Button.h"
#include "../Messages/menu_msg.h"

cClickComp::cClickComp()
{}

void cClickComp::Slot(float fTimeDiff)
{}

void cClickComp::ReceiveMessage(cMessage &message)
{
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	Button* button = dynamic_cast<Button*>(pOwnEnt);
	cClickButtonMsg *pMsg = dynamic_cast<cClickButtonMsg *>(&message);
	if (button && pMsg != nullptr){
		button->onClick(pMsg->GetData());
	}
}