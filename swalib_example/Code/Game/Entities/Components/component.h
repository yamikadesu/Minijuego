#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class cEntity;
class cMessage;

class cComponent
{
private:
	cEntity* m_pOwner;

public:
	cComponent() : m_pOwner(nullptr)
	{}
	virtual ~cComponent();
	virtual void Slot(float fTimeDiff) = 0;
	inline void SetOwner(cEntity &ent) { m_pOwner = &ent; }
	inline cEntity *GetOwner() const { return m_pOwner; }
	virtual void ReceiveMessage(cMessage &message)
	{};
	virtual void Activate()
	{}
	virtual void Deactivate()
	{}
};

#endif // !_COMPONENT_H_
