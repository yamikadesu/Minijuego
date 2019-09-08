#include "../../../../common/stdafx.h"
#include "Boss.h"
#include "../Managers/graphics_engine.h"

Boss* Boss::create() {
	Boss* boss = NEW(Boss,());
	return boss;
}
