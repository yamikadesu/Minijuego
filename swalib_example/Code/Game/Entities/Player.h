#pragma once
#include "Entity.h"
#include "../Graphics/Sprite.h"
#include "../Entities/Components/render_comp.h"
#include "Bullet.h"

class Player : public cEntity {
public:
	static Player* create();
	static Player* GetPlayer();
	static void DeletePlayer();
private:
	Player() {};
	static Player* m_player;
};