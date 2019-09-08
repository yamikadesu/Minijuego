#include "Button.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Messages/menu_msg.h"

void Button::onClick(void* data, vec2 pos) {
	vec2 bPos = FindComponent<cLinearVelComp>()->GetPos();
	vec2 bsize = GetSize();
	if (pos.x > (bPos.x - bsize.x / 2.f) && pos.x < (bPos.x + bsize.x / 2.f) && pos.y >(bPos.y - bsize.y / 2.f) && pos.y < (bPos.y + bsize.y / 2.f)) {
		cClickButtonMsg clickButton(data);
		ReceiveMessage(clickButton);
	}
}