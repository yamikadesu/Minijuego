#ifndef _MENU_COMP_H_
#define _MENU_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"
#include <vector>
#include "../Button.h"

using namespace std;

class cWorld;

class cMenuComp : public cComponent
{
private:
	//Índice del diálogo por el que va ahora
	vector<Button*> m_entities;
	bool stopLogic = false;
public:
	cMenuComp();
	~cMenuComp();
	virtual void Slot(float fTimeDiff) override;
	virtual void ReceiveMessage(cMessage &message) override;

	std::vector<Button *> GetEntities() const { return m_entities; }
	void SetEntities(std::vector<Button *> val) { m_entities = val; }
	void AddEntity(Button * val) { m_entities.push_back(val); }
	void BeginDestroy();
	void RemoveEntities();
};

#endif // !_COLLISION_COMP_H_
