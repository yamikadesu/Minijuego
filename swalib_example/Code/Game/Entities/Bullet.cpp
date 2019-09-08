#include "../../../../common/stdafx.h"
#include "Bullet.h"

//Se elimina de todas las mejoras el tipo de mejora especificada
void Bullet::RemoveUpgradeType(UpgradeType bulletUpgrade) {
	for (unsigned int i = 0; i < m_bulletUpgrade.size(); i++) {
		if (bulletUpgrade == m_bulletUpgrade[i]) {
			m_bulletUpgrade.erase(m_bulletUpgrade.begin() + i);
		}
	}
}