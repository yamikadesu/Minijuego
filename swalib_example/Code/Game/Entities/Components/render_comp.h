#ifndef _RENDER_COMP_H_
#define _RENDER_COMP_H_

#include "../../Graphics/sprite.h"
#include "component.h"

class cRenderComp : public cComponent
{
private:
	//Sprite
	cSprite* m_Sprite;
	//Variable que acumula el tiempo en caso de que la entidad parpadee
	float m_ticksTime;
	//Variable que indica el número de frames
	int m_frames;
	//Variable que indica el frame actual
	int m_actualFrame;
	//Valor que indica el tiempo entre frame y frame
	float m_frameTime;
	//Variable que va acumulando el tiempo
	float m_time;
public:
	cRenderComp(std::string sFileName, const vec2 &vSize, bool intr, int framesNum = 1, float frameTime = 0.f);
	~cRenderComp();

	inline cSprite* GetSprite() { return m_Sprite; };
	inline void SetSprite(cSprite* sprite);
	inline void SetSprite(std::string sFileName, const vec2 &vSize);
	int GetFrames() const { return m_frames; }
	void SetFrames(int val) { m_frames = val; }
	float GetFrameTime() const { return m_frameTime; }
	void SetFrameTime(float val) { m_frameTime = val; }
	//Si se quisiera modificar el frame actual para determinados usos
	int GetActualFrame() const { return m_actualFrame; }
	void SetActualFrame(int val) { m_actualFrame = val; }

	void Slot(float fTimeDiff);

	virtual void ReceiveMessage(cMessage &message) override;
};

#endif // !_RENDER_COMP_H_
