#pragma once
#include <vector>
#include "../../../../common/core.h"
#include "../Graphics/sprite.h"
#include <string>

#ifndef _INTERFACE_ENGINE_H_
#define _INTERFACE_ENGINE_H_

using namespace std;

class cInterfaceController
{
private:
	//Texto que almacena el dialogo actual
	static string m_dialogue;
	//Posición del diálogo actual
	static vec2 m_dialogue_pos;
	//Textos estáticos (se usa para cosas como los FPS)
	static vector<string> m_staticFont;
	//Posiciones de los textos estáticos
	static vector<vec2> m_staticFont_pos;
	//Texto que indica la vida actual del jugador
	static string m_playerLifes;
	//Posición actual de la vida del jugador
	static vec2 m_playerLifes_pos;
	//Texto que indica la vida del boss (es el texto de Boss:)
	static string m_bossLifes;
	//Posición del texto del boss
	static vec2 m_bossLifes_pos;
	//Tamaño inicial de la barra de vida del boss (no es la vida de boss sino cuando ocupa la barra)
	static float m_initSize;
	//Sprite de la barra de vida del boss
	static cSprite* m_bossBar;
public:
	static cInterfaceController GetInstance();
	void operator = (cInterfaceController const&) = delete;

	void Init();
	void Slot();
	void Terminate();

	void InsertStaticFont(const char* defaultText, vec2 pos);
	void WriteDialogue(const char* text, vec2* pos = nullptr);
	void UpdatePlayerHealth(bool draw = true, vec2* pos = nullptr);
	void UpdateBossHealth(bool draw = true, vec2* pos = nullptr);
	void UpdateStaticFont(int index, const char* text);

	inline string GetDialogue() const { return m_dialogue; }
	inline vector<string> GetStaticFonts() const { return m_staticFont; }
	inline string GetPlayerLifes() const { return m_playerLifes; }
private:
	cInterfaceController() {};
};

#endif // !_GRAPHICS_ENGINE_H_

