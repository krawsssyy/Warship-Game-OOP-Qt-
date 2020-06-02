#pragma once
#include "IElem.h"

class Submarine : public IE {
private:
	static const int m_figID = 3, m_Length = 2;
public:
	Submarine() : IE() {}
	Submarine(int startX, int startY, int orientation) : IE(startX, startY, orientation) {};
	Submarine(const Submarine& s);
	~Submarine() {}
	Submarine& operator=(const Submarine& s);
	bool operator==(const Submarine& s);
	int getFigID();
	int getLength();
	IE* clone();
	bool equals(IE* e);
};