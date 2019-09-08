#include "../../../../../common/stdafx.h"
#include "render_comp.h"
#include "../../Managers/graphics_engine.h"
#include "../Messages/new_pos_msg.h"
#include "../Messages/damage_msg.h"
#include "../Components/linear_vel_comp.h"
#include "life_comp.h"
#include "../entity.h"
#include "../Player.h"
#include "../../Managers/world.h"

//Se indica el lugar, el tamaño y si es introducido en el vector de sprites que se renderizan automaticamente o lo renderizamos manualmente
cRenderComp::cRenderComp(const char *sFileName, const vec2 &vSize, bool intr, int framesNum, float frameTime)
{
	SetFrameTime(frameTime);
	m_time = 0.f;
	SetFrames(framesNum);
	SetActualFrame(0);
	m_Sprite = NEW(cSprite,(sFileName, vSize));
	m_ticksTime = 0.0f;
	if (intr) {
		cGraphicsEngine::GetInstance().InsertRenderObj(*m_Sprite);
	}
}

cRenderComp::~cRenderComp()
{
	cGraphicsEngine::GetInstance().DeleteRenderObj(*m_Sprite);
	DEL(m_Sprite);
}

void cRenderComp::SetSprite(cSprite* sprite)
{
	m_Sprite = sprite;
	if (sprite) {
		cGraphicsEngine::GetInstance().GetImgInfo(sprite->GetFileName())->ImgId;
	}
}

void cRenderComp::Slot(float fTimeDiff)
{
	if (GetFrames() > 1) {
		m_time += fTimeDiff;
		if (m_time >= GetFrameTime()) {
			vec4 uv = { GetActualFrame()*(1.f / GetFrames()),(GetActualFrame() + 1.f)*(1.f / GetFrames()),GetActualFrame()*(1.f / GetFrames()),(GetActualFrame() + 1.f)*(1.f / GetFrames()) };
			m_Sprite->SetUV(uv);
			m_time = 0.f;
			SetActualFrame((GetActualFrame() + 1) % GetFrames());
		}
	}
}

void cRenderComp::ReceiveMessage(cMessage &message)
{
	const cNewPosMsg *pMsg = dynamic_cast<const cNewPosMsg *>(&message);
	if (pMsg != nullptr) {
		const Player* player = dynamic_cast<const Player*>(GetOwner());
		//Hace la misma logica que en linear_vel_comp para que el player no salga
		if (player != nullptr && ((pMsg->GetPos().x < 0.0f || pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x) &&
			(pMsg->GetPos().y < 0.0f || pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y))) {
			return;
		}
		else if (player != nullptr) {
			if (pMsg->GetPos().x < 0.0f) {
				if(!(pMsg->GetPos().y < 0.0f || pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
					m_Sprite->SetPos({ 0.0f,pMsg->GetPos().y });
					GetOwner()->FindComponent<cLinearVelComp>()->SetPos({ 0.0f,pMsg->GetPos().y });
				}
				return;
			}
			else if (pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x) {
				if (!(pMsg->GetPos().y < 0.0f || pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y)) {
					m_Sprite->SetPos({ Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x,pMsg->GetPos().y });
					GetOwner()->FindComponent<cLinearVelComp>()->SetPos({ Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x,pMsg->GetPos().y });
				}
				return;
			}
			else if (pMsg->GetPos().y < 0.0f) {
				if (!(pMsg->GetPos().x < 0.0f || pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x)) {
					m_Sprite->SetPos({ pMsg->GetPos().x,0.0f });
					GetOwner()->FindComponent<cLinearVelComp>()->SetPos({ pMsg->GetPos().x,0.0f });
				}
				return;
			}
			else if (pMsg->GetPos().y > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y) {
				if (!(pMsg->GetPos().x < 0.0f || pMsg->GetPos().x > Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x)) {
					m_Sprite->SetPos({ pMsg->GetPos().x, Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y });
					GetOwner()->FindComponent<cLinearVelComp>()->SetPos({ pMsg->GetPos().x, Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y });
				}
				return;
			}
			else {
				m_Sprite->SetPos(pMsg->GetPos());
				GetOwner()->FindComponent<cLinearVelComp>()->SetPos(pMsg->GetPos());
				return;
			}
		}
		else {
 			m_Sprite->SetPos(pMsg->GetPos());
			GetOwner()->FindComponent<cLinearVelComp>()->SetPos(pMsg->GetPos());
			return;
		}
	}
	
	//Si es invulnerable va a asignar el tiempo y establecerá si se renderiza o no el sprite (en el caso del player parpadea si esta invulnerable)
	const cInvMsg * invMsg = dynamic_cast<const cInvMsg *>(&message);
	if (invMsg != nullptr) {
		cLifeComp* lifeComp = GetOwner()->FindComponent<cLifeComp>();
		if (lifeComp != nullptr) {

			m_ticksTime += invMsg->GetTime();
			if (lifeComp->GetInv()) {
				if (m_ticksTime < lifeComp->GetInvTicks()) {
					m_Sprite->SetNotRender(false);
				}
				else if (m_ticksTime >= lifeComp->GetInvTicks() + lifeComp->GetBlankTime()) {
					m_ticksTime = 0.0f;
				}
				else if (m_ticksTime >= lifeComp->GetInvTicks()) {
					m_Sprite->SetNotRender(true);
				}
			}
		}
		return;
	}
	
	const cNotDrawMsg * notMsg = dynamic_cast<const cNotDrawMsg *>(&message);
	if (notMsg != nullptr) {
		m_Sprite->SetNotRender(true);
		return;
	}

	const cDrawMsg * drwMsg = dynamic_cast<const cDrawMsg *>(&message);
	if (drwMsg != nullptr) {
		m_Sprite->SetNotRender(false);
		return;
	}

	const cChangeRGBA * rgbaMsg = dynamic_cast<const cChangeRGBA *>(&message);
	if (rgbaMsg != nullptr) {
		m_Sprite->SetRGBA(rgbaMsg->GetRGBA());
		return;
	}

	const cRotate * rotMsg = dynamic_cast<const cRotate *>(&message);
	if (rotMsg != nullptr) {
		m_Sprite->SetAngle(rotMsg->GetRotation());
		return;
	}
}
