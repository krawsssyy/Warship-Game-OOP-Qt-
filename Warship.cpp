#include "Warship.h"

Warship::Warship(const Warship& w) {
	this->m_startX = w.m_startX;
	this->m_startY = w.m_startY;
	this->m_Orientation = w.m_Orientation;
	this->m_isHid = w.m_isHid;
}

Warship& Warship::operator=(const Warship& w) {
	if (&w == this)
		return *this;
	else
	{
		this->m_startX = w.m_startX;
		this->m_startY = w.m_startY;
		this->m_Orientation = w.m_Orientation;
		this->m_isHid = w.m_isHid;
		return *this;
	}
}

bool Warship::operator==(const Warship& w) {
	return this->m_startX == w.m_startX && this->m_startY == w.m_startY && this->m_Orientation == w.m_Orientation && this->m_isHid == w.m_isHid;
}

int Warship::getFigID() {
	return this->m_figID;
}

int Warship::getLength() {
	return this->m_Length;
}

IE* Warship::clone() {
	return new Warship(*this);
}

bool Warship::equals(IE* e) {
	if (dynamic_cast<Warship*>(e) != nullptr)
		return this->operator==(*dynamic_cast<Warship*>(e));
	else
		return false;
}
