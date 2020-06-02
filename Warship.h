#pragma once
#include "IElem.h"
class Warship : public IE {
private:
	static const int m_figID = 1, m_Length = 5;
public :
	Warship() : IE() {};
	Warship(int startX, int startY, int orientation) : IE(startX, startY, orientation) {};
	Warship(const Warship& w);
	~Warship() {};
	Warship& operator=(const Warship& w);
	bool operator==(const Warship& w);
	int getFigID();
	int getLength();
	IE* clone();
	bool equals(IE* e);
};