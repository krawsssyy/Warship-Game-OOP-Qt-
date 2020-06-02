#include "Repo.h"

Repository::Repository(){
    this->m_elems.reserve(k + p + q);
}

Repository::Repository(std::vector<IE*> elems)
{
	for (auto x : elems)
		this->m_elems.emplace_back(x->clone());
}

Repository::~Repository()
{
	this->m_elems.clear();
}

void Repository::addElem(IE* elem)
{
	for (auto x : this->m_elems)
		if (x->equals(elem))
			return;
	this->m_elems.emplace_back(elem);
}

int Repository::getElemPos(IE* elem)
{
	int len = this->m_elems.size();
	int i = 0;
	for (i = 0; i < len; i++)
		if (this->m_elems[i]->equals(elem))
			break;
	if (i == len)
		throw Exc("Given element was not found!");
	return i;
}


void Repository::deleteElem(IE* elem)
{
	this->m_elems.erase(this->m_elems.begin() + getElemPos(elem));
}

int Repository::getSize()
{
	return this->m_elems.size();
}

std::vector<IE*> Repository::getAll()
{
	return this->m_elems;
}

void Repository::clearRepo(){
	this->m_elems.clear();
}
 
