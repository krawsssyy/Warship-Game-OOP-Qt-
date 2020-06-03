#pragma once
#include "Repo.h"
#include "Warship.h"
#include "Yacht.h"
#include "Submarine.h"

class Validator {
public:
	void validate(IE* e, bool& res) {
        if (e->getStartX() < 1 || e->getStartX() > N )
		{
			res = false;
			throw Exc("Invalid starting row!\n");
		}
        if (e->getStartY() < 1 || e->getStartY() > N )
		{
			res = false;
			throw Exc("Invalid starting column!\n");
		}
		if (e->getOrientation() != 0 && e->getOrientation() != 1)
		{
			res = false;
			throw Exc("Invalid orientation!\n");
		}
        if(dynamic_cast<Warship*>(e) != nullptr)
            if((e->getOrientation() == 1 && e->getStartX() + dynamic_cast<Warship*>(e)->getLength() > N + 1) ||
                 (e->getOrientation() == 0 && e->getStartY() + dynamic_cast<Warship*>(e)->getLength() > N + 1))
            {
                res = false;
                throw Exc("Your warship will fall out of the table bounds!\n");
            }
        if(dynamic_cast<Yacht*>(e) != nullptr)
            if((e->getOrientation() == 1 && e->getStartX() + dynamic_cast<Yacht*>(e)->getLength() > N + 1) ||
                 (e->getOrientation() == 0 && e->getStartY() + dynamic_cast<Yacht*>(e)->getLength() > N + 1))
            {
                res = false;
                throw Exc("Your yacht will fall out of the table bounds!\n");
            }
        if(dynamic_cast<Submarine*>(e) != nullptr)
            if((e->getOrientation() == 1 && e->getStartX() + dynamic_cast<Submarine*>(e)->getLength() > N + 1) ||
                 (e->getOrientation() == 0 && e->getStartY() + dynamic_cast<Submarine*>(e)->getLength() > N + 1))
            {
                res = false;
                throw Exc("Your s"
                          "ubmarine will fall out of the table bounds!\n");
            }
		res = true;

	}
};
