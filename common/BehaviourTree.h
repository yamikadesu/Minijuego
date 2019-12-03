#pragma once
#include <vector>
#include "../swalib_example/Code/Game/Entities/Boss.h"
#include "../swalib_example/Code/Game/Managers/graphics_engine.h"
#include <iostream>

enum Status { 
	eInvalid,
	eSuccess,
	eFail,
	eRunning,
};

class Behaviour {
public:
	Behaviour() {};
	virtual ~Behaviour() {};
	virtual Status update(float time, const Boss* boss) = 0;
	virtual void onEnter(const Boss* boss) = 0;
	virtual void onExit(const Boss* boss) = 0;
	Status tick(float time, const Boss* boss);

	Status m_Status = eInvalid; 
};

class BehaviourTree {
public:
	static std::vector<std::string> spritesList;
	BehaviourTree() {};
	std::vector<Behaviour*> m_Behaviours;
	Behaviour* m_currentBehaviour;
	const Boss* m_boss;

	//static bool b_isDead;
	unsigned int index = 0;
	/*void load();*/
	void start(const Boss* boss);
	void update(float time);
	void finishLogic() {
		for (auto sprite : spritesList) {
			cGraphicsEngine::GetInstance().DeleteRenderObj(sprite);
		}
	}

	~BehaviourTree() {
		for (unsigned int i = 0; i < m_Behaviours.size(); i++) {
			DEL(m_Behaviours[i]);
		}
	};
};

class Group : public Behaviour {
public: 
	Group() {};
	virtual ~Group() {
		for (unsigned int i = 0; i < m_Children.size(); i++) {
			DEL(m_Children[i]);
		} 
	};
	Status update(float time, const Boss* boss) { return eSuccess; };
	void onEnter(const Boss* boss) {};
	void onExit(const Boss* boss) {};
 
	std::vector<Behaviour*> m_Children;
};

//Behaviour 0
class Sequence : public Group {
public:
	Sequence() {};
	Sequence(std::vector<Behaviour*> Children) { m_Children = Children; };
	Status update(float time, const Boss* boss);
	void onEnter(const Boss* boss);
	void onExit(const Boss* boss) {};

	unsigned int m_CurrentChild;
};

//Behaviour 1
class Selector : public Group {
public:
	Selector() {};
	Selector(std::vector<Behaviour*> Children) { m_Children = Children; };
	Status update(float time, const Boss* boss);
	void onEnter(const Boss* boss);
	void onExit(const Boss* boss) {};

	unsigned int m_CurrentChild;
};

//Behaviour 2
class BucleSequence : public Group {
public:
	BucleSequence() {};
	BucleSequence(std::vector<Behaviour*> Children) { m_Children = Children; };
	Status update(float time, const Boss* boss);
	void onEnter(const Boss* boss);
	void onExit(const Boss* boss) {};

	unsigned int m_CurrentChild;
};

//Behaviour 3
class Bucle : public Group {
public:
	Bucle() {};
	Bucle(std::vector<Behaviour*> Children) { m_Children = Children; };
	Status update(float time, const Boss* boss);
	void onEnter(const Boss* boss);
	void onExit(const Boss* boss) {};

	unsigned int m_CurrentChild;
};

//Behaviour 4
class Idle : public Behaviour {
public:
	Idle() {};
	void onEnter(const Boss* boss) {};
	Status update(float time, const Boss* boss) { return Status::eSuccess; };
	void onExit(const Boss* boss) {};
};

//Behaviour 5
class ChangeSprite : public Behaviour {
public:
	ChangeSprite() {
		BehaviourTree::spritesList.push_back("data/sans2.png");
		BehaviourTree::spritesList.push_back("data/sans.png");
	};
	void onEnter(const Boss* boss);
	Status update(float time, const Boss* boss) { return Status::eSuccess; };
	void onExit(const Boss* boss) {};
};

//Behaviour 6
class WaitBehaviour : public Behaviour {
public:
	float m_initTime;
	float m_time;
	WaitBehaviour() { m_initTime = 5.f; m_time = 5.f; };
	WaitBehaviour(float time) { m_initTime = time; m_time = time; };
	void onEnter(const Boss* boss) {};
	Status update(float time, const Boss* boss);
	void onExit(const Boss* boss) { m_time = m_initTime; };
};

//Behaviour 7
class CheckHealth : public Behaviour {
public:
	int m_health;
	CheckHealth() { m_health = 1000; };
	CheckHealth(int health) { m_health = health; };
	void onEnter(const Boss* boss) {};
	Status update(float time, const Boss* boss);
	void onExit(const Boss* boss) {};
};

//Behaviour 8
class Flee : public Behaviour {
public:
	Flee() {};
	void onEnter(const Boss* boss) {};
	Status update(float time, const Boss* boss);
	void onExit(const Boss* boss) {};
};

//data[0] is the id so from data[1] to the end would be data for initialization
inline void bindBehaviour(std::vector<Behaviour*>& children, std::string id, std::vector<std::string> data) {
	if (id == "4") {
		Idle* behaviour = NEW(Idle, ());
		children.push_back(behaviour);
	}
	else if (id == "5") {
		ChangeSprite* behaviour = NEW(ChangeSprite, ());
		children.push_back(behaviour);
	}
	else if (id == "6") {
		if (data.size() > 1) {
			float par = (float)std::atof(data[1].c_str());
			WaitBehaviour* behaviour = NEW(WaitBehaviour, (par));
			children.push_back(behaviour);
		}
		else {
			WaitBehaviour* behaviour = NEW(WaitBehaviour, ());
			children.push_back(behaviour);
		}
	}
	else if (id == "7") {
		if (data.size() > 1) {
			int par = std::atoi(data[1].c_str());
			CheckHealth* behaviour = NEW(CheckHealth, (par));
			children.push_back(behaviour);
		}
		else {
			CheckHealth* behaviour = NEW(CheckHealth, ());
			children.push_back(behaviour);
		}
	}
	else if (id == "8") {
		Flee* behaviour = NEW(Flee, ());
		children.push_back(behaviour);
	}
}