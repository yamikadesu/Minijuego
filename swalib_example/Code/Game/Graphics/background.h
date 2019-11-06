#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../../../../common/core.h"
#include "../Graphics/sprite.h"
#include "render_object.h"

class cBackground : public cRenderObject
{
private:
	//Sprite del background
	cSprite	m_Sprite;
	//Canción del background
	std::string m_song;
	//Variables que indican el reescalado según el tamaño del nivel
	vec2 m_resize;
	//Posicion que va a ir multiplicado por el índice del for del render del background de donde se va a ir posicionando el siguiente background
	vec2 m_resizePos;
	//Offset de posicionamiento del background (de cada uno de los backgrounds al colocarse en cada índice del for del render del background)
	vec2 m_resizeSum;
public:
	cBackground(std::string sFileName, const vec2 &fSize, vec2 resize, vec2 resizePos, vec2 resizeSum);

	virtual void Render() override;

	inline std::string  GetAudio() { return m_song; };
	inline void SetAudio(std::string sz_song) { m_song = sz_song; };
};


#endif // !_BACKGROUND_H_

