#include "../../../../common/stdafx.h"
#include "InterfaceController.h"
#include "graphics_engine.h"
#include "../../../../common/core.h"
#include "world.h"
#include "../Graphics/render_object.h"
#include <assert.h>
#include <vector>
#include <string>
#include "../../../../common/font.h"
#include "../Entities/Player.h"
#include "../Entities/Components/life_comp.h"

//Valores por defectos de los textos de la interfaz
string cInterfaceController::m_dialogue = "";
vec2 cInterfaceController::m_dialogue_pos = { 0.0f, 0.0f };
vector<string> cInterfaceController::m_staticFont;
vector<vec2> cInterfaceController::m_staticFont_pos;
string cInterfaceController::m_playerLifes = "";
vec2 cInterfaceController::m_playerLifes_pos = { 0.0f, 0.0f };
string cInterfaceController::m_bossLifes = "";
vec2 cInterfaceController::m_bossLifes_pos = { 0.0f, 0.0f };
float cInterfaceController::m_initSize = 0.0f;
cSprite* cInterfaceController::m_bossBar = nullptr;

cInterfaceController cInterfaceController::GetInstance() {
	static cInterfaceController inter;
	return inter;
}

void cInterfaceController::Init() {
	FONT_Init();
	//Inicializa el sprite de la vida del boss y el tamaño del mismo
	m_initSize = 800.0f;
	m_bossBar = NEW(cSprite,("data/bossbar.png", { m_initSize, 16.0f}));
}

void cInterfaceController::Slot() {
	//Renderiza cada parte de la interfaz si hay texto disponible
	if (m_dialogue != "") {
		FONT_DrawString(m_dialogue_pos, m_dialogue.c_str());
	}
	if (m_playerLifes != "") {
		FONT_DrawString(m_playerLifes_pos, m_playerLifes.c_str());
	}
	if (m_bossLifes != "") {
		FONT_DrawString(m_bossLifes_pos, m_bossLifes.c_str());
		m_bossBar->Render();
	}
	for (unsigned int i = 0; i < m_staticFont.size(); i++) {
		if (m_staticFont[i] != "") {
			FONT_DrawString(m_staticFont_pos[i], m_staticFont[i].c_str());
		}
	}
}

void cInterfaceController::Terminate() {
	FONT_End();
	DEL(m_bossBar);
}

//Introduce el texto estático indicado
void cInterfaceController::InsertStaticFont(const char* defaultText, vec2 pos) {
	m_staticFont.push_back(defaultText);
	m_staticFont_pos.push_back(pos);
}

//Indica que se quiere escribir el diálogo indicado una vez se actualice la interfaz
void cInterfaceController::WriteDialogue(const char* text, vec2* pos) {
	if (pos != nullptr) {
		m_dialogue_pos = *pos;
	}

	m_dialogue = text;
}

//Indica que se quiere mostrar la vida del jugador una vez se actualice la interfaz
void cInterfaceController::UpdatePlayerHealth(bool draw, vec2* pos) {
	if (pos != nullptr) {
		m_playerLifes_pos = *pos;
	}

	if (draw) {
		m_playerLifes = to_string(Player::GetPlayer()->FindComponent<cLifeComp>()->GetLifes());
	}else {
		m_playerLifes = "";
	}
}

//Indica que se quiere mostrar la vida del boss una vez se actualice la interfaz (se realiza la lógica necesaria para ir actualizando la barra de vida)
void cInterfaceController::UpdateBossHealth(bool draw, vec2* pos) {
	if (pos != nullptr) {
		m_bossLifes_pos = *pos;
		vec2 barPos = {pos->x +35.0f, pos->y - 16.0f };
		m_bossBar->SetPos(barPos);
	}

	if (draw) {
		int bossLifes = Level::GetLevels().at(World::GetWorld()->GetActualLevel())->FindComponent<cLevelComp>()
			->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetLifes();
		bossLifes = bossLifes < 0 ? 0 : bossLifes;
		int initBossLifes = Level::GetLevels().at(World::GetWorld()->GetActualLevel())->FindComponent<cLevelComp>()
			->GetBoss()[0]->FindComponent<cBossLogicComp>()->GetInitLifes();
		float percent = ((float)bossLifes / (float)initBossLifes);
		m_bossLifes = string("BOSS: ");
		m_bossBar->SetSize({ percent*m_initSize,m_bossBar->GetSize().y });
	}
	else {
		m_bossLifes = "";
	}
}

//Indica que se quiere mostrar el texto estático una vez se actualice la interfaz
void cInterfaceController::UpdateStaticFont(int index, const char* text) {
	m_staticFont[index] = text;
}