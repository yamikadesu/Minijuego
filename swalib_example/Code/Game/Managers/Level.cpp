#include "../../../../common/stdafx.h"
#include "Level.h"
#include "../Entities/Messages/reset_msg.h"

vector<Level*> Level::m_levels;

Level* Level::create(){
	Level* level = NEW(Level,());
	m_levels.push_back(level);
	return level;
}

Level::~Level() {
	cDeleteEntitiesMsg msg;
	ReceiveMessage(msg);
// 	if (cLevelComp* levelComp = FindComponent<cLevelComp>()) {
// 		levelComp
// 	}
}

//Se usa para eliminar todos los niveles
void Level::DeleteLevels() {
	for (unsigned int i = 0; i < m_levels.size(); i++) {
		DEL(m_levels[i]);
	}
	m_levels.clear();
}