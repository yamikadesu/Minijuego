#pragma once
#ifndef _NEW_SOUND_MSG_H_
#define _NEW_SOUND_MSG_H_

#include "message.h"
#include <string>

class cPlaySoundMsg : public cMessage
{
private:
	std::string m_song;

public:
	cPlaySoundMsg(std::string vPos) : m_song(vPos)
	{}

	inline std::string GetSong() const { return m_song; }
};

#endif // !_NEW_POS_MSG_H_
