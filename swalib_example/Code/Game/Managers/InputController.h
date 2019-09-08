#pragma once
#include <vector>
#include "../../../../common/core.h"
#include "../Entities/Components/component.h"

#ifndef _INPUT_ENGINE_H_
#define _INPUT_ENGINE_H_

using namespace std;

class cGraphicsEngine;
class TEvent;

class cInputController
{
public:

	class IListener
	{
	public:
		virtual void ManageEvent(TEvent* pEvent, float fTimeDiff) = 0;
	};

	//Tipos de botones
	enum Key{
		SPACE,
		LCLICK,
		RCLICK
	};
	cInputController();
	~cInputController();
	
	void ProcessInputs();

	void Activate();
	void Init();
	void Update(float fTimeDiff);
	void RegisterToEvent(IListener * pObserver);

	void Terminate();

	bool isPress(Key key);
	bool isRelease(Key key);

	vec2 GetMousePos();
private:
	std::vector<IListener*>m_listeners;
	std::vector<TEvent*>m_events;
};

#endif // !_GRAPHICS_ENGINE_H_

