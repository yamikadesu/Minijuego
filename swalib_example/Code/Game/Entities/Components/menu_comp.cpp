#include "../../../../../common/stdafx.h"
#include "menu_comp.h"
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
#include "../Messages/input_msg.h"
#include "../Upgrade.h"
#include "../Messages/entity_msg.h"
#include "../../Managers/Level.h"
#include "../../Managers/InterfaceController.h"
#include "../Messages/reset_msg.h"
#include "life_comp.h"
#include "bullet_comp.h"
#include "../Messages/render_msg.h"
#include "../../Managers/graphics_engine.h"
#include "../Messages/menu_msg.h"
#include "linear_vel_comp.h"

cMenuComp::cMenuComp()
{
}

cMenuComp::~cMenuComp()
{
	RemoveEntities();
}

void cMenuComp::Slot(float fTimeDiff)
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->Slot(fTimeDiff);
	}
}

void cMenuComp::ReceiveMessage(cMessage &message)
{
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	World* world = dynamic_cast<World*>(pOwnEnt);
	const cClickMsg *pMsg6 = dynamic_cast<const cClickMsg *>(&message);
	if (pMsg6 != nullptr) {
		if (world->GetState() == World::MENU) {
			for (unsigned int i = 0; i < m_entities.size(); i++) {
				if (stopLogic) {
					RemoveEntities();
					break;
				}
				m_entities[i]->onClick(reinterpret_cast<void*>(world), pMsg6->GetPos());
			}
		}
		return;
	}
}

void cMenuComp::BeginDestroy() {
	stopLogic = true;
}

void cMenuComp::RemoveEntities()
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		DEL(m_entities[i]);
	}
	m_entities.clear();
}
