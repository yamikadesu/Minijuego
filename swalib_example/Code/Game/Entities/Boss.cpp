#include "../../../../common/stdafx.h"
#include "Boss.h"
#include "../Managers/graphics_engine.h"
#include "Components/life_comp.h"

Boss* Boss::create() {
	Boss* boss = NEW(Boss,());
	return boss;
}

void Boss::finishLogic()
{
	FindComponent<cBossLogicComp>()->finishLogic();
}
