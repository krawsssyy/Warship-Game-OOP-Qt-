#include "Repo.h"
Repository::Repository(){
    this->parseConfig();
    this->m_elems.reserve(k + p + q);
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
 
