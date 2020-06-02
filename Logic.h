#pragma once
#include "Repo.h"
#include "Yacht.h"
#include "Submarine.h"
#include "Warship.h"
#include "IValidator.h"
#include <string>

class Logic {
private:
	Repository* m_userR;
	Repository* m_aiR;
	Validator* m_valid;
	std::vector<std::string> aiGuesses;
public:
	Logic() : m_userR(nullptr), m_aiR(nullptr) , m_valid(nullptr) {}
	Logic(Repository* userR, Repository* aiR, Validator* valid) : m_userR(userR), m_aiR(aiR), m_valid(valid) {}
	~Logic() {
		if (this->m_userR){
			delete this->m_userR;
			this->m_userR = nullptr;
		}
		if (this->m_aiR) {
			delete this->m_aiR;
			this->m_aiR = nullptr;
		}
		if (this->m_valid) {
			delete this->m_valid;
			this->m_valid = nullptr;
		}
	}
	void addElem(int startX, int startY, int orientation, std::string identifier);
	std::pair<int, int> guessDecoder(std::string guess);
	bool hitReg(std::string guess, char identifier);
	std::string aiGuess();
	void aiStart();
	int getGameStatus();
	void verifyGuess(std::string guess);
	std::vector<IE*> getAllUser();
	std::vector<IE*> getAllAI();
	void resetGame();

};
