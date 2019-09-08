#ifndef __EVENTS2__
#define __EVENTS2__

//***************************************************************************************
//TEvent
//***************************************************************************************

class TEvent
{
public:

	enum TType
	{
		EMouseDownLeft,
		EMouseDownRight,
		EMouseMove,
		EKeyboardDown
	};
	TEvent(TType type) { m_type = type; }
	virtual ~TEvent() {}
    TType GetType() const { return m_type;}
private:
	TType m_type;
};




//***************************************************************************************
//TEventMouse
//***************************************************************************************


class TEventMouseDownLeft : public TEvent
{
public:
	TEventMouseDownLeft(int x, int y) : TEvent (EMouseDownLeft)
	{ 
		m_x = x; 
		m_y = y; 
	}

	int Getx() { return m_x; }
	int Gety() { return m_y; }
private:
	int m_x;
	int m_y;
};

class TEventMouseDownRight : public TEvent
{
public:
	TEventMouseDownRight(int x, int y) : TEvent(EMouseDownRight)
	{
		m_x = x;
		m_y = y;
	}

	int Getx() { return m_x; }
	int Gety() { return m_y; }
private:
	int m_x;
	int m_y;
};

class TEventMouseMove : public TEvent
{
public:
	TEventMouseMove(int x, int y) : TEvent(EMouseMove)
	{
		m_x = x;
		m_y = y;
	}

	int Getx() { return m_x; }
	int Gety() { return m_y; }
private:
	int m_x;
	int m_y;
};

//***************************************************************************************
//TEventKeyboard
//***************************************************************************************


class TEventKeyboardDown : public TEvent
{
public:
	TEventKeyboardDown(unsigned int key) : TEvent(EKeyboardDown)
	{
		m_key = key;
	}

	int Getkey() { return m_key; }
private:
	unsigned int m_key;
};

#endif