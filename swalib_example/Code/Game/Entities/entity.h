#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>

class cComponent;
class cMessage;

class cEntity {
private:
	std::vector<cComponent*> m_Components;	// Component list.
	bool m_isAlive;
public:
	cEntity();
	virtual ~cEntity();

	void Activate();
	void Deactivate();
	void Slot(float fTimeDiff);
	virtual void Update(float timeDiff) {};
	void ReceiveMessage(cMessage &message) const;

	inline void SetDead() { m_isAlive = false; };
	inline bool GetIsAlive() { return m_isAlive; };

	template <class T>
	void AddComponent(T* component)
	{
		m_Components.push_back(component);
		component->SetOwner(*this);
	}

	template <class T>
	T *FindComponent() const
	{
		for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
			T* pComp = dynamic_cast<T*>(*compIt);
			if (pComp != nullptr) {
				return pComp;
			}
		}
		return nullptr;
	}
};

#endif // !_ENTITY_H_