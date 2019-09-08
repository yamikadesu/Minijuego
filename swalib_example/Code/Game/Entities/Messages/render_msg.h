#pragma once
#ifndef _NEW_RENDER_MSG_H_
#define _NEW_RENDER_MSG_H_

#include "message.h"
#include "../../../../../common/core.h"

class cDrawBossMsg : public cMessage
{};

class cDrawInitTextsMsg : public cMessage
{
private:
	//Variable que indica si se ha leido el texto inicial
	bool m_initTextRead;
	//Índice del diálogo por el que vamos
	int m_dialogueIndex;
public:
	cDrawInitTextsMsg(bool initTextRead, int dialogueIndex) : m_initTextRead(initTextRead), m_dialogueIndex(dialogueIndex){};
	inline const bool &GetInitTextRead() const { return m_initTextRead; }
	inline const int &GetDialogueIndex() const { return m_dialogueIndex; }
};

class cDrawBossTextsMsg : public cMessage
{
private:
	//Variable que indica si se ha leido el texto inicial
	bool m_initTextRead;
	//Variable que indica si se ha leido el texto del boss
	bool m_bossTextRead;
	//Índice del diálogo por el que vamos
	int m_dialogueIndex;
public:
	cDrawBossTextsMsg(bool initTextRead, bool bossTextRead, int dialogueIndex) : m_initTextRead(initTextRead), m_bossTextRead(bossTextRead), m_dialogueIndex(dialogueIndex) {};
	inline const bool &GetInitTextRead() const { return m_initTextRead; }
	inline const bool &GetBossTextRead() const { return m_bossTextRead; }
	inline const int &GetDialogueIndex() const { return m_dialogueIndex; }
};

class cDrawFinalTextsMsg : public cMessage
{
private:
	//Variable que indica si se ha leido el texto inicial
	bool m_initTextRead;
	//Variable que indica si se ha leido el texto del boss
	bool m_bossTextRead;
	//Variable que indica si se ha leido el texto final
	bool m_endTextRead;
	//Índice del diálogo por el que vamos
	int m_dialogueIndex;
public:
	cDrawFinalTextsMsg(bool initTextRead, bool bossTextRead, bool endTextRead, int dialogueIndex) : m_initTextRead(initTextRead), m_bossTextRead(bossTextRead), m_endTextRead(endTextRead), m_dialogueIndex(dialogueIndex) {};
	inline const bool &GetInitTextRead() const { return m_initTextRead; }
	inline const bool &GetBossTextRead() const { return m_bossTextRead; }
	inline const bool &GetEndTextRead() const { return m_endTextRead; }
	inline const int &GetDialogueIndex() const { return m_dialogueIndex; }
};

class cChangeRGBA : public cMessage
{
private:
	//Nuevo color
	rgba_t m_rgba;
public:
	cChangeRGBA(rgba_t rgba) : m_rgba(rgba) {};
	inline const rgba_t &GetRGBA() const { return m_rgba; }
};

class cRotate : public cMessage
{
private:
	//Nuevo ángulo 
	float m_rotation;
public:
	cRotate(float rotation) : m_rotation(rotation) {};
	inline const float &GetRotation() const { return m_rotation; }
};

class cAnimMsg : public cMessage
{
private:
	//Nueva uv
	vec4 m_uv;
public:
	cAnimMsg(vec4 uv) : m_uv(uv) {};
	inline const vec4 GetUV() const { return m_uv; }
};

#endif // !_NEW_POS_MSG_H_
