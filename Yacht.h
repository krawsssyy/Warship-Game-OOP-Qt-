#pragma once
#include "IElem.h"

class Yacht : public IE {
private:
	static const int m_figID = 2, m_Length = 3;
public:
	Yacht() : IE() {};
	Yacht(int startX, int startY, int orientation) : IE(startX, startY, orientation) {};
	Yacht(const Yacht& y);
	~Yacht() {}
	Yacht& operator=(const Yacht& y);
	bool operator==(const Yacht& y);
	int getFigID();
	int getLength();
	IE* clone();
	bool equals(IE* e);
};