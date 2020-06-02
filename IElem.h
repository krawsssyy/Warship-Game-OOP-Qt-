#pragma once
#include "MyException.h"
class IElement {
protected:
	int m_startX, m_startY, m_Orientation;
	bool m_isHid;
public:
	IElement() {
		this->m_startX = -1;
		this->m_startY = -1;
		this->m_Orientation = 0;
		this->m_isHid = false;
	}

	IElement(int startX, int startY, int orientation) {
		this->m_startX = startX;
		this->m_startY = startY;
		this->m_Orientation = orientation;
		this->m_isHid = true;
	}

	void setStartX(int startX) {
		this->m_startX = startX;
	}

	void setStartY(int startY) {
		this->m_startY = startY;
	}

	void changeOrientation() {
		this->m_Orientation = m_Orientation == 1 ? 0 : 1;
	}

	int getStartX() {
		return this->m_startX;
	}

	int getStartY() {
		return this->m_startY;
	}

	int getOrientation() {
		return this->m_Orientation;
	}

	bool getHidden() {
		return this->m_isHid;
	}

	void reveal() {
		if (this->m_isHid == true)
			this->m_isHid = false;
		else
			throw Exc("It has already been identified");
	}

	virtual IElement* clone() = 0;
	virtual bool equals(IElement*) = 0;
	virtual ~IElement() {}

};

typedef IElement IE;
