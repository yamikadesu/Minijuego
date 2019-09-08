#pragma once

#include "../../../../common/core.h"
#include "../Entities/Entity.h"
#include <vector>
#include "../Entities/Components/level_comp.h"

using namespace std;

class Level;

class Level : public cEntity{
private:
	//Vector de niveles
	static vector<Level*> m_levels;
	Level() {};
public:
	static Level* create();
	~Level();
	static inline vector<Level*> GetLevels() { return m_levels; }
	static void DeleteLevels();
};