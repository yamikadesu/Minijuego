#include "../../../../common/stdafx.h"
#include "background.h"
#include "../../../../common/sys.h"
#include "../Managers/world.h"
#include "../Managers/Level.h"
#include "../Entities/Components/level_comp.h"

cBackground::cBackground(std::string sFileName, const vec2 &fSize, vec2 resize, vec2 resizePos, vec2 resizeSum) : m_Sprite(sFileName, fSize), m_resize(resize), m_resizePos(resizePos), m_resizeSum(resizeSum)
{
}

void cBackground::Render()
{
	// Render background
	for (int i = 0; i <= Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().x / m_resize.x; i++) {
		for (int j = 0; j <= Level::GetLevels()[World::GetWorld()->GetActualLevel()]->FindComponent<cLevelComp>()->GetLevelSize().y / m_resize.y; j++) {
			m_Sprite.SetPos(vmake(i * m_resizePos.x+ m_resizeSum.x, j * m_resizePos.y + m_resizeSum.y));
			m_Sprite.Render();
		}
	}
}