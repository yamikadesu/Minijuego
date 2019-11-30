#include "stdafx.h"
#include "BehaviourTree.h"
#include "../swalib_example/Code/Game/Entities/Components/render_comp.h"
#include "../swalib_example/Code/Game/Entities/Components/life_comp.h"
#include "../swalib_example/Code/Game/Entities/Components/linear_vel_comp.h"
#include "../swalib_example/Code/Game/Entities/Player.h"
#include "../swalib_example/Code/Game/Entities/Messages/new_pos_msg.h"
#include "../swalib_example/Code/Game/Entities/Messages/damage_msg.h"
#include "../swalib_example/Code/Game/Entities/Messages/render_msg.h"
#include "../swalib_example/Code/Game/Managers/world.h"
#include <algorithm>

Status Behaviour::tick(float time, const Boss* boss)
{
	//if (m_Status == eInvalid) {
		onEnter(boss);
	//}
	m_Status = update(time, boss);
	if (m_Status != eRunning) {
		onExit(boss);
	} 
	return m_Status;
}

Status Sequence::update(float time, const Boss* boss)
{
	while (true) {
		Status s = m_Children[m_CurrentChild]->tick(time, boss);
		if (s != eSuccess) { 
			return s;
		} 
		++m_CurrentChild;
		if (m_CurrentChild == m_Children.size()) {
			m_CurrentChild = 0;
			return eSuccess;
		}
	} 
	return eInvalid;
}

void Sequence::onEnter(const Boss* boss)
{
	m_CurrentChild = 0;
}

Status Selector::update(float time, const Boss* boss)
{
	while (true) {
		Status s = m_Children[m_CurrentChild]->tick(time, boss);
		if (s != eFail) {
			m_CurrentChild = 0;
			return s;
		} 
		++m_CurrentChild; 
		if (m_CurrentChild == m_Children.size()) {
			m_CurrentChild = 0;
			return eFail;
		}
	} 
	return eInvalid;
}

void Selector::onEnter(const Boss* boss)
{
	m_CurrentChild = 0;
}

Status BucleSequence::update(float time, const Boss* boss)
{
	while (true) {
		Status s = m_Children[m_CurrentChild]->tick(time, boss);
		if (s != eSuccess) {
			m_CurrentChild = 0;
			break;
		}
		++m_CurrentChild;
		if (m_CurrentChild == m_Children.size()) {
			m_CurrentChild = 0;
			return eSuccess;
		}
	}
	return eInvalid;
}

void BucleSequence::onEnter(const Boss* boss)
{
	m_CurrentChild = 0;
}


Status Bucle::update(float time, const Boss* boss)
{
	while (true) {
		Status s = m_Children[m_CurrentChild]->tick(time, boss);
		if (s != eSuccess) {
			return s;
		}
		++m_CurrentChild;
		if (m_CurrentChild == m_Children.size()) {
			m_CurrentChild = 0;
			return eRunning;
		}
	}
	return eInvalid;
}

void Bucle::onEnter(const Boss* boss)
{
	m_CurrentChild = 0;
}


void ChangeSprite::onEnter(const Boss* boss){
	cRenderComp* rendComp = boss->FindComponent<cRenderComp>();
	if (rendComp) {
		const vec2 bossPos = boss->FindComponent<cLinearVelComp>()->GetPos();
		if (rendComp->GetSprite()->GetFileName() == "data/sans.png") {
			cChangeSprite newMessage("data/sans2.png", rendComp->GetSprite()->GetSize());
			boss->ReceiveMessage(newMessage);
			//rendComp->SetSprite("data/sans2.png", rendComp->GetSprite()->GetSize());
		}
		else {
			cChangeSprite newMessage("data/sans.png", rendComp->GetSprite()->GetSize());
			boss->ReceiveMessage(newMessage);
			//rendComp->SetSprite("data/sans.png", rendComp->GetSprite()->GetSize());
		}
		cNewPosMsg msg(bossPos);
		boss->ReceiveMessage(msg);
	}
}


Status Flee::update(float time, const Boss* boss)
{
	const vec2 playerPos = Player::GetPlayer()->FindComponent<cLinearVelComp>()->GetPos();
	const vec2 bossPos = boss->FindComponent<cLinearVelComp>()->GetPos();
	vec2 resDir = { bossPos.x - playerPos.x + ((rand() % 2) ? 200.f : -200.f), bossPos.y - playerPos.y + ((rand() % 2) ? 200.f : -200.f) };
	//if (vlen(resDir) <= 800.f) {
	vec2 newPos = { ((rand() % 2) ? resDir.x : -resDir.x) , ((rand() % 2) ? resDir.y : -resDir.y) };
	newPos = { clampf(newPos.x + bossPos.x, 100.f, World::GetWorld()->GetWorldSize().x-100.f), clampf(newPos.y + bossPos.y, 100.f, World::GetWorld()->GetWorldSize().y-100.f) };
// 	if (World::GetWorld()) {
// 		if (newPos.x >= World::GetWorld()->GetWorldSize().x) {
// 			newPos.x = -resDir.x + bossPos.x;
// 		}
// 		else if (newPos.x <= 0.f) {
// 			newPos.x = -resDir.x + bossPos.x;
// 		}
// 		if (newPos.y >= World::GetWorld()->GetWorldSize().y) {
// 			newPos.y = -resDir.y + bossPos.y;
// 		}
// 		else if (newPos.y <= 0.f) {
// 			newPos.y = -resDir.y + bossPos.y;
// 		}
// 	}
	cNewPosMsg newpos(newPos);
	boss->ReceiveMessage(newpos);
	//}
	return eSuccess;
}


Status CheckHealth::update(float time, const Boss* boss)
{
	const int bossHealth = boss->FindComponent<cBossLogicComp>()->GetLifes();
	if (bossHealth <= m_health) {
		return eSuccess;
	}
	else {
		return eFail;
	}
}

std::vector<std::string> BehaviourTree::spritesList;

//bool BehaviourTree::b_isDead = false;

void BehaviourTree::start(const Boss* boss)
{
	if (m_Behaviours.size() > 0) {
		m_boss = boss;
		m_currentBehaviour = m_Behaviours[0];
		index = 0;
		m_currentBehaviour->onEnter(boss);
	}
}

void BehaviourTree::update(float time)
{
	if (index < m_Behaviours.size() && m_boss->FindComponent<cBossLogicComp>()->GetLifes()>0) {
		Status actStatus = m_currentBehaviour->update(time, m_boss);
		//std::vector<Behaviour*> behs = m_currentState->getTransitions();
		//for (int i = 0; i < behs.size(); i++) {
		if (actStatus!=eInvalid && actStatus!=eRunning) {
			m_currentBehaviour->onExit(m_boss);
			index++;
			if (index < m_Behaviours.size()) {
				Behaviour* nextBehaviour = m_Behaviours[index];
				nextBehaviour->onEnter(m_boss);
				m_currentBehaviour = nextBehaviour;
			}
			return;
		}
		//}
	}
}

Status WaitBehaviour::update(float time, const Boss* boss)
{
	m_time -= time;
	return m_time <= 0.f ? Status::eSuccess : Status::eRunning;
}
