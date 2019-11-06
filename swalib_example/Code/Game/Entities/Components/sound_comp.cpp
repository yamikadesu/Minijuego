#include "../../../../../common/stdafx.h"
#include "sound_comp.h"
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
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
//Necesario para el funcionamiento de la librería de música
#pragma comment(lib, "winmm.lib")
#include "../Messages/sound_msg.h"

cSoundComp::cSoundComp()
{
}

void cSoundComp::Slot(float fTimeDiff)
{
}

void cSoundComp::ReceiveMessage(cMessage &message)
{
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	const cPlaySoundMsg *pMsg6 = dynamic_cast<const cPlaySoundMsg *>(&message);
	if (pMsg6 != nullptr) {
		PlaySound(pMsg6->GetSong().c_str(), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
		return;
	}
}
