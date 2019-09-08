#pragma once
#ifndef _NEW_SOUND_MSG_H_
#define _NEW_SOUND_MSG_H_

#include "message.h"

class cPlaySoundMsg : public cMessage
{
private:
	const char* m_song;

public:
	cPlaySoundMsg(const char* vPos) : m_song(vPos)
	{}

	inline const char* GetSong() const { return m_song; }
};

#endif // !_NEW_POS_MSG_H_
