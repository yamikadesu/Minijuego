#pragma once
#include <vector>
#include "Entity.h"
#include "../../../../common/core.h"
#include "../Entities/Components/render_comp.h"
#include "../Graphics/sprite.h"
#include "Enemy.h"

class Boss : public cEntity {
public:
	static Boss* create();
private:
	Boss() {};
};