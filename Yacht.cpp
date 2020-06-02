#include "Yacht.h"

Yacht::Yacht(const Yacht& y) {
	this->m_startX = y.m_startX;
	this->m_startY = y.m_startY;
	this->m_Orientation = y.m_Orientation;
	this->m_isHid = y.m_isHid;
}

Yacht& Yacht::operator=(const Yacht& y) {
	if (&y == this)
		return *this;
	else
	{
		this->m_startX = y.m_startX;
		this->m_startY = y.m_startY;
		this->m_Orientation = y.m_Orientation;
		this->m_isHid = y.m_isHid;
		return *this;
	}
}

bool Yacht::operator==(const Yacht& y) {
	return this->m_startX == y.m_startX && this->m_startY == y.m_startY && this->m_Orientation == y.m_Orientation && this->m_isHid == y.m_isHid;
}

int Yacht::getFigID() {
	return this->m_figID;
}

int Yacht::getLength() {
	return this->m_Length;
}

IE* Yacht::clone() {
	return new Yacht(*this);
}

bool Yacht::equals(IE* e) {
	if (dynamic_cast<Yacht*>(e) != nullptr)
		return this->operator==(*dynamic_cast<Yacht*>(e));
	else
		return false;
}
