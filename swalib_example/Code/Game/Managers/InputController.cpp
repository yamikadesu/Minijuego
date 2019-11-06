#include "../../../../common/stdafx.h"
#include "InputController.h"
#include "graphics_engine.h"
#include "../../../../common/core.h"
#include "world.h"
#include "../Graphics/render_object.h"
#include <assert.h>
#include <vector>
#include <string>
#include "../../../../common/sys.h"
#include "../Entities/Messages/new_pos_msg.h"
#include "../Entities/Player.h"
#include "../Entities/Messages/entity_msg.h"
#include "../Entities/Components/bullet_comp.h"
#include "../Entities/Components/life_comp.h"
#include "../Entities/Components/level_comp.h"
#include "../Entities/Messages/reset_msg.h"
#include "InterfaceController.h"
#include "events.h"
#include "../Entities/Messages/input_msg.h"
#include "../Entities/Messages/menu_msg.h"

cInputController * g_pIM = nullptr;

void cInputController::ProcessInputs()
{
	vec2 mousePos = GetMousePos();
	if (isPress(Key::LCLICK)) {
		TEvent *pEventL = NEW(TEventMouseDownLeft, (static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)));
		m_events.push_back(pEventL);
	}

	if (isPress(Key::RCLICK)) {
		TEvent *pEventR = NEW(TEventMouseDownRight, (static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)));
		m_events.push_back(pEventR);
	}

	if (isPress(Key::SPACE)) {
		TEvent *pEventS = NEW(TEventKeyboardDown, (static_cast<unsigned int>((int)Key::SPACE)));
		m_events.push_back(pEventS);
	}

	TEvent *pEvent2 = NEW(TEventMouseMove, (static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)));
	m_events.push_back(pEvent2);
}

cInputController::cInputController()
{
	g_pIM = this;
}

cInputController::~cInputController()
{
	for (TEvent* event : m_events)
	{
		DEL(event);
	}
}

void cInputController::RegisterToEvent(cInputController::IListener * pObserver)
{
	m_listeners.push_back(pObserver);
}

void cInputController::Activate() {
	Init();
}

void cInputController::Init() {
}

void cInputController::Update(float fTimeDiff)
{
	ProcessInputs();
	for (TEvent* event : m_events)
	{
		for (IListener* listener : m_listeners)
			listener->ManageEvent(event, fTimeDiff);
		DEL(event);
	}
	m_events.clear();
}

void cInputController::Terminate() {
}

//Indica si ha sido presionada una tecla
bool cInputController::isPress(Key key) {
	switch (key) {
	case SPACE:
		return SYS_KeyPressed(SYS_KEY_SPACE);
		break;
	case LCLICK:
		return SYS_MouseButonPressed(SYS_MB_LEFT);
		break;
	case RCLICK:
		return SYS_MouseButonPressed(SYS_MB_RIGHT);
		break;
	default:
		return false;
	}
}

//Indica si ha dejado de ser presionada una tecla
bool cInputController::isRelease(Key key) {
	switch (key) {
	case SPACE:
		return !SYS_KeyPressed(SYS_KEY_SPACE);
		break;
	case LCLICK:
		return !SYS_MouseButonPressed(SYS_MB_LEFT);
		break;
	case RCLICK:
		return !SYS_MouseButonPressed(SYS_MB_RIGHT);
		break;
	default:
		return false;
	}
}

//Indica la posición del ratón
vec2 cInputController::GetMousePos() {
   	return { static_cast<float>(SYS_MousePos().x), static_cast<float>(SYS_MousePos().y) };
}