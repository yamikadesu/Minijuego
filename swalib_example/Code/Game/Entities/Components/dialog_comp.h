#ifndef _DIALOG_COMP_H_
#define _DIALOG_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"

class cWorld;

class cDialogComp : public cComponent
{
private:
	//Índice del diálogo por el que va ahora
	int m_dialogueIndex;
	//¿Ha leido los textos iniciales?
	bool m_initTextRead;
	//¿Ha leido los textos del boss?
	bool m_bossTextRead;
	//¿Ha leido los textos finales?
	bool m_endTextRead;
	//Tiempo de espera para evitar que se spamee el input en los diálogos
	float m_waitText;
	//Variable que acumula el tiempo para los diálogos(waitText)
	float m_timeText;

public:
	cDialogComp(float waitText);
	virtual void Slot(float fTimeDiff) override;
	virtual void ReceiveMessage(cMessage &message) override;

	int GetDialogueIndex() const { return m_dialogueIndex; }
	void SetDialogueIndex(int val) { m_dialogueIndex = val; }
	bool GetInitTextRead() const { return m_initTextRead; }
	void SetInitTextRead(bool val) { m_initTextRead = val; }
	bool GetBossTextRead() const { return m_bossTextRead; }
	void SetBossTextRead(bool val) { m_bossTextRead = val; }
	bool GetEndTextRead() const { return m_endTextRead; }
	void SetEndTextRead(bool val) { m_endTextRead = val; }
	float GetWaitText() const { return m_waitText; }
	void SetWaitText(float val) { m_waitText = val; }
	float GetTimeText() const { return m_timeText; }
	void SetTimeText(float val) { m_timeText = val; }
};

#endif // !_COLLISION_COMP_H_
