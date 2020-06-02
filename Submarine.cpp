#include "Submarine.h"

Submarine::Submarine(const Submarine& s) {
	this->m_startX = s.m_startX;
	this->m_startY = s.m_startY;
	this->m_Orientation = s.m_Orientation;
	this->m_isHid = s.m_isHid;
}

Submarine& Submarine::operator=(const Submarine& s) {
	if (&s == this)
		return *this;
	else
	{
		this->m_startX = s.m_startX;
		this->m_startY = s.m_startY;
		this->m_Orientation = s.m_Orientation;
		this->m_isHid = s.m_isHid;
		return *this;
	}
}

bool Submarine::operator==(const Submarine& s) {
	return this->m_startX == s.m_startX && this->m_startY == s.m_startY && this->m_Orientation == s.m_Orientation && this->m_isHid == s.m_isHid;
}

int Submarine::getFigID() {
	return this->m_figID;
}

int Submarine::getLength() {
	return this->m_Length;
}

IE* Submarine::clone()
{
	return new Submarine(*this);
}

bool Submarine::equals(IE* e)
{
	if (dynamic_cast<Submarine*>(e) != nullptr)
		return this->operator==(*dynamic_cast<Submarine*>(e));
	else
		return false;
}
