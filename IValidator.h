#pragma once
#include "IElem.h"
#include "MyException.h"
#define N 10
class Validator {
public:
	void validate(IE* e, bool& res) {
		if (e->getStartX() < 1 || e->getStartX() > N - 1)
		{
			res = false;
			throw Exc("Invalid starting row!\n");
		}
		if (e->getStartY() < 1 || e->getStartY() > N - 1)
		{
			res = false;
			throw Exc("Invalid starting column!\n");
		}
		if (e->getOrientation() != 0 && e->getOrientation() != 1)
		{
			res = false;
			throw Exc("Invalid orientation!\n");
		}
		res = true;

	}
};