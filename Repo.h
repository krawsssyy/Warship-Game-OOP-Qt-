#pragma once
#include "MyException.h"
#include "IElem.h"
#include <vector>
const int k = 1;
const int p = 1;
const int q = 1;


class Repository {
private:
	std::vector<IE*> m_elems;
public:
	Repository();
	Repository(std::vector<IE*> elems);
	~Repository();
	void addElem(IE* elem);
	int getElemPos(IE* elem);
	void deleteElem(IE* elem);
	int getSize();
	std::vector<IE*> getAll();
	void clearRepo();

};
