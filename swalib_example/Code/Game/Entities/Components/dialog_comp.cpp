#include "../../../../../common/stdafx.h"
#include "dialog_comp.h"
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
#include "../Messages/sound_msg.h"

cDialogComp::cDialogComp(float waitText) : m_waitText(waitText), m_dialogueIndex(0), m_timeText(waitText), m_initTextRead(false), m_bossTextRead(false), m_endTextRead(false)
{}

void cDialogComp::Slot(float fTimeDiff)
{
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	World* world = dynamic_cast<World*>(pOwnEnt);
	if (world->GetState() == World::PLAYING && !(Player::GetPlayer() == nullptr || Player::GetPlayer()->FindComponent<cLifeComp>()->GetLifes() <= 0)) {
		if (GetInitTextRead() && !(!GetBossTextRead() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() <= 0) &&
			!GetEndTextRead() && GetDialogueIndex() <= 0 && ((!Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() &&
				Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() > 0) ||
				(Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() > 0))) {
			Level::GetLevels().at(world->GetActualLevel())->Slot(fTimeDiff);
		}
		//Si acaba el nivel se pasa al siguiente nivel o se considera victoria si se ha terminado
		else if (((!Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() <= 0) || (Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() <= 0)) && GetEndTextRead()) {
			cDeleteEntitiesMsg deleteMsg;
			Level::GetLevels().at(world->GetActualLevel())->ReceiveMessage(deleteMsg);
			SetInitTextRead(false);
			SetBossTextRead(false);
			SetEndTextRead(false);
			world->SetActualLevel(world->GetActualLevel() + 1);
			if (static_cast<unsigned int>(world->GetActualLevel()) < Level::GetLevels().size()) {
				cPlaySoundMsg playSoundMsg(Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBackgrounds()[0]->GetAudio());
				world->ReceiveMessage(playSoundMsg);
				//world->Music(Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBackgrounds()[0]->GetAudio());
				cInterfaceController::GetInstance().UpdateBossHealth(false);
				if (Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetHorizontal()) {
					Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->SetBulletData({ Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().loc, Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().size, DEG2RAD(0.0f) });
				}
				else {
					Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->SetBulletData({ Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().loc, Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet()->GetBulletData().size, DEG2RAD(90.0f) });
				}
			}
			else {
				cPlaySoundMsg playSoundMsg(world->GetVictory()->GetAudio());
				world->ReceiveMessage(playSoundMsg);
				//world->Music(world->GetVictory()->GetAudio());
				world->SetActualLevel(0);
				cInterfaceController::GetInstance().UpdateBossHealth(false);
				world->SetState(World::State::VICTORY);
			}
		}
		else if (world->GetInitCount() > 0) {
			world->SetInitCount(world->GetInitCount() - fTimeDiff);
		}
	}
}

void cDialogComp::ReceiveMessage(cMessage &message)
{
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	World* world = dynamic_cast<World*>(pOwnEnt);
	const cDrawDialogMsg *pMsg6 = dynamic_cast<const cDrawDialogMsg *>(&message);
	if (pMsg6 != nullptr) {
		if (world->GetState() == World::PLAYING) {
			cDrawBossMsg bossMsg;
			cDrawInitTextsMsg initTextMsg(GetInitTextRead(), GetDialogueIndex());
			cDrawBossTextsMsg bossTextMsg(GetInitTextRead(), GetBossTextRead(), GetDialogueIndex());
			cDrawFinalTextsMsg endTextMsg(GetInitTextRead(), GetBossTextRead(), GetEndTextRead(), GetDialogueIndex());
			cDrawInitTextsMsg* initMsgPtr = !GetInitTextRead() ? &initTextMsg : nullptr;
			cDrawBossTextsMsg* bossMsgPtr = GetInitTextRead() && !GetBossTextRead() ? &bossTextMsg : nullptr;
			cDrawFinalTextsMsg* endMsgPtr = Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() <= 0 && !GetEndTextRead() ? &endTextMsg : nullptr;
			cGraphicsEngine::GetInstance().Slot(nullptr, world->GetActualLevel(), world->GetInitCount() <= 0, GetInitTextRead(), &bossMsg, initMsgPtr, bossMsgPtr, endMsgPtr);
		}
		return;
	}
	const cDialogLogicMsg *pMsg3 = dynamic_cast<const cDialogLogicMsg *>(&message);
	if (pMsg3 != nullptr) {
		if (world->GetInitCount() <= 0 && !GetInitTextRead() && static_cast<unsigned int>(GetDialogueIndex()) < Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetInitTexts().size()) {
			SetTimeText(GetTimeText() + pMsg3->GetTime());
		}
		else if (world->GetInitCount() <= 0 && !GetInitTextRead()) {
			SetDialogueIndex(0);
			SetTimeText(0.0f);
			SetInitTextRead(true);
			cResetDialogue resetDialog;
			Level::GetLevels().at(world->GetActualLevel())->ReceiveMessage(resetDialog);
		}
		if (world->GetInitCount() <= 0 && GetInitTextRead() && !GetBossTextRead() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() <= 0 && static_cast<unsigned int>(GetDialogueIndex()) < Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBossTexts().size()) {
			SetTimeText(GetTimeText() + pMsg3->GetTime());
		}
		else if (world->GetInitCount() <= 0 && GetInitTextRead() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() <= 0 && !GetBossTextRead()) {
			SetDialogueIndex(0);
			SetTimeText(0.0f);
			SetBossTextRead(true);
			cInterfaceController::GetInstance().UpdateBossHealth(true);
			cResetDialogue resetDialog;
			Level::GetLevels().at(world->GetActualLevel())->ReceiveMessage(resetDialog);
		}
		if (Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() <= 0 && world->GetInitCount() <= 0 && !GetEndTextRead() && static_cast<unsigned int>(GetDialogueIndex()) < Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetFinalTexts().size()) {
			SetTimeText(GetTimeText() + pMsg3->GetTime());
		}
		else if (world->GetInitCount() <= 0 && !GetEndTextRead() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() <= 0) {
			SetDialogueIndex(0);
			SetTimeText(0.0f);
			SetEndTextRead(true);
			cResetDialogue resetDialog;
			Level::GetLevels().at(world->GetActualLevel())->ReceiveMessage(resetDialog);
		}
		return;
	}
	const cPassDialogMsg *pMsg = dynamic_cast<const cPassDialogMsg *>(&message);
	if (pMsg != nullptr) {
		if (GetTimeText() >= GetWaitText()) {
			SetDialogueIndex(GetDialogueIndex() + 1);
			SetTimeText(0.0f);
		}
		return;
	}
	const cResetWorldMsg *pMsg4 = dynamic_cast<const cResetWorldMsg *>(&message);
	if (pMsg4 != nullptr) {
		SetInitTextRead(false);
		SetBossTextRead(false);
		SetEndTextRead(false);
		world->Init();
		return;
	}
	const cMovePlayerMsg *pMsg2 = dynamic_cast<const cMovePlayerMsg *>(&message);
	if (pMsg2 != nullptr) {
		if (GetInitTextRead() && !(!GetBossTextRead() && GetDialogueIndex() > 0) && !GetEndTextRead() && ((!Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() > 0) || (Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() > 0))) {
			cNewPosMsg newPosMsg(pMsg2->GetPos());
			Player::GetPlayer()->ReceiveMessage(newPosMsg);
		}
		return;
	}
	const cShootPlayerMsg *pMsg5 = dynamic_cast<const cShootPlayerMsg *>(&message);
	if (pMsg5 != nullptr) {
		if (GetInitTextRead() && !(!GetBossTextRead() && GetDialogueIndex() > 0) && !GetEndTextRead() && ((!Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes() > 0) || (Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetBoss().empty() && Level::GetLevels().at(world->GetActualLevel())->FindComponent<cLevelComp>()->GetEnemyAmount() > 0))) {
			if ((GetInitTextRead() && !(!GetBossTextRead() && GetDialogueIndex() > 0) && !GetEndTextRead()) || (GetInitTextRead() && GetBossTextRead() && !GetEndTextRead())) {
				cShoot shootMsg(Player::GetPlayer()->FindComponent<cBulletComp>()->GetBullet());
				Player::GetPlayer()->ReceiveMessage(shootMsg);
			}
		}
		return;
	}
}
