#include "../../../../common/stdafx.h"
#include "entity.h"
#include "Components/component.h"

cEntity::cEntity() : m_isAlive(true)
{}

cEntity::~cEntity()
{
	for (unsigned int i = 0; i < m_Components.size(); i++) {
		DEL(m_Components[i]);
	}
	m_Components.clear();
}

void cEntity::Activate()
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Activate();
	}
}

void cEntity::Deactivate()
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Deactivate();
	}
}

void cEntity::Slot(float fTimeDiff)
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Slot(fTimeDiff);
	}
	Update(fTimeDiff);
}

void cEntity::ReceiveMessage(cMessage &message) const
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->ReceiveMessage(message);
	}
}
