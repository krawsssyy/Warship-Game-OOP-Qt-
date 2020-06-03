#include "Logic.h"
#include <ctime>

void Logic::addElem(int startX, int startY, int orientation, std::string identifier) {
	if (identifier == "Warship") {
		IE* e = new Warship(startX, startY, orientation);
		bool res = false;
		this->m_valid->validate(e, res);
		if(res)
			this->m_userR->addElem(e);
		else
		{
			delete e;
			e = nullptr;
		}
	}
	else if (identifier == "Yacht") {
		IE* e = new Yacht(startX, startY, orientation);
		bool res = false;
		this->m_valid->validate(e, res);
		if (res)
			this->m_userR->addElem(e);
		else
		{
			delete e;
			e = nullptr;
		}
	}
	else if (identifier == "Submarine") {
		IE* e = new Submarine(startX, startY, orientation);
		bool res = false;
		this->m_valid->validate(e, res);
		if (res)
			this->m_userR->addElem(e);
		else
		{
			delete e;
			e = nullptr;
		}
	}
}

std::pair<int, int> Logic::guessDecoder(std::string guess) {
	this->verifyGuess(guess);
    if(guess.length() == 2)
        return std::pair<int, int>((guess[0] - '0'), (guess[1] - '0') % 48 );
    else if(guess.length() == 3)
    {
        std::string number(1, guess[0]);
        std::string number2(1, guess[1]);
        int no = std::stoi(number + number2);
        return std::pair<int, int>(no, (guess[2] - '0') % 48 );
    }
}

bool Logic::hitReg(std::string guess,char identifier) {
	bool hit = false;
	std::pair<int, int> g = this->guessDecoder(guess);
	if (identifier == 'u') {
		for (auto x : this->m_aiR->getAll()) {
			if (x->getOrientation() == 1) {
				if(g.second == x->getStartY()) {
					if (dynamic_cast<Warship*>(x) != nullptr) {
						if (x->getStartX() <= g.first && g.first < (x->getStartX() + ((Warship*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Yacht*>(x) != nullptr) {
						if (x->getStartX() <= g.first && g.first < (x->getStartX() + ((Yacht*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Submarine*>(x) != nullptr) {
						if (x->getStartX() <= g.first && g.first < (x->getStartX() + ((Submarine*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
				}
			}
			else {
				if (g.first == x->getStartX()) {
					if (dynamic_cast<Warship*>(x) != nullptr) {
						if (x->getStartY() <= g.second && g.second < (x->getStartY() + ((Warship*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Yacht*>(x) != nullptr) {
						if (x->getStartY() <= g.second && g.second < (x->getStartY() + ((Yacht*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Submarine*>(x) != nullptr) {
						if (x->getStartY() <= g.second && g.second < (x->getStartY() + ((Submarine*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
				}
			}
		}
	}
	else {
		for (auto x : this->m_userR->getAll()) {
			if (x->getOrientation() == 1) {
				if (g.second == x->getStartY()) {
					if (dynamic_cast<Warship*>(x) != nullptr) {
						if (x->getStartX() <= g.first && g.first < (x->getStartX() + (((Warship*)(x))->getLength())))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Yacht*>(x) != nullptr) {
						if (x->getStartX() <= g.first && g.first < (x->getStartX() + (((Yacht*)(x))->getLength())))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Submarine*>(x) != nullptr) {
						if (x->getStartX() <= g.first && g.first < (x->getStartX() + (((Submarine*)(x))->getLength())))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
				}
			}
			else {
				if (g.first == x->getStartX()) {
					if (dynamic_cast<Warship*>(x) != nullptr) {
						if (x->getStartY() <= g.second && g.second < (x->getStartY() + ((Warship*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Yacht*>(x) != nullptr) {
						if (x->getStartY() <= g.second && g.second < (x->getStartY() + ((Yacht*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
					if (dynamic_cast<Submarine*>(x) != nullptr) {
						if (x->getStartY() <= g.second && g.second < (x->getStartY() + ((Submarine*)(x))->getLength()))
						{
							hit = true;
							if (x->getHidden() == true)
								x->reveal();
							return hit;
						}
					}
				}
			}
		}
	}
	return hit;
}

std::string Logic::aiGuess() {
	srand((time_t)time(0));
    char col = 97 + rand() % (N + 1);
    int row = rand() % (N + 1);
	while(row == 0)
        row = rand() % (N + 1);
    while(col == 97 + N)
        col = 97 + rand() % (N + 1);
	std::string s = std::to_string(row) + col;
	auto inGuess = [this](std::string guess) {
		for (auto x : this->aiGuesses)
			if (guess == x)
				return true;
		return false;
	};
	while (inGuess(s)) {
        col = 97 + rand() % (N + 1);
        row = rand() % (N + 1);
        if (col == 97 + N || row == 0)
			continue;
		else
			s = std::to_string(row) + col;
	}
	this->aiGuesses.emplace_back(s);
	return s;
}

void Logic::aiStart(){
	srand((time_t)time(0));
	for (int i = 0; i < k; i++)
	{
        int startX = rand() % (N + 1), startY = rand() % (N + 1), orientation = rand() % 2;
        while (startX == 0 || (startX > N - 4 && orientation == 1))
            startX = rand() % (N + 1);
        while (startY == 0 || (startY > N - 4 && orientation == 0))
            startY = rand() % (N + 1);
		this->m_aiR->addElem(new Warship(startX, startY, orientation));
	}
	for (int i = 0; i < p; i++)
	{
        int startX = rand() % (N + 1), startY = rand() % (N + 1), orientation = rand() % 2;
        while (startX == 0 || (startX > N - 2 && orientation == 1))
            startX = rand() % (N + 1);
        while (startY == 0 || (startY > N - 2 && orientation == 0))
            startY = rand() % (N + 1);
		this->m_aiR->addElem(new Yacht(startX, startY, orientation));
	}
	for (int i = 0; i < q; i++)
	{

        int startX = rand() % (N + 1), startY = rand() % (N + 1), orientation = rand() % 2;
        while (startX == 0 || (startX > N - 1 && orientation == 1))
            startX = rand() % (N + 1);
        while (startY == 0 || (startY > N - 1 && orientation == 0))
            startY = rand() % (N + 1);
		this->m_aiR->addElem(new Submarine(startX, startY, orientation));
	}
}

int Logic::getGameStatus() {
	bool uOk = false, aOk = false;
	for (auto x : this->m_aiR->getAll())
		if (x->getHidden() == true)
		{
			aOk = true;
			break;
		}
	for (auto x : this->m_userR->getAll())
		if (x->getHidden() == true)
		{
			uOk = true;
			break;
		}
	if (uOk && aOk)
		return 0;
	else if (uOk && !aOk)
		return 1;
	else if (!uOk && aOk)
		return -1;
}

void Logic::verifyGuess(std::string guess) {
    if(N < 27)
    {
        if (guess.length() == 2)
        {
            if (guess[0] < '1' || guess[0] > '9')
                throw Exc("The row number is invalid!");
            if (guess[1] < 'a' || guess[1] > (97 + N - 1))
                throw Exc("The column number is invalid!");
        }
        else if(guess.length() == 3)
            {
                std::string number(1, guess[0]);
                if(N / 10 == 1 && guess[0] != '1')
                    throw Exc("The row number is invalid!");
                if(N / 10 == 2 && guess[0] != '1' && guess[0] != '2')
                    throw Exc("The row number is invalid!");
                if(N / 10 == 2 && guess[1] > *std::to_string(N%10).c_str())
                    throw Exc("The row number is invalid!");
                if(N / 10 == 1 && guess[1] > *std::to_string(N%10).c_str())
                    throw Exc("The row number is invalid!");
                std::string number2(1, guess[1]);
                number += number2;
                int no = std::stoi(number);
                if(no < 1 || no > N)
                    throw Exc("The row number is invalid!");
                if (guess[2] < 'a' || guess[2] > (97 + N - 1))
                    throw Exc("The column number is invalid!");
            }
            else
                throw Exc("Invalid guess format!");
    }

     else
          throw Exc("Invalid table size!");

}

std::vector<IE*> Logic::getAllUser()
{
	return this->m_userR->getAll();
}

std::vector<IE*> Logic::getAllAI()
{
	return this->m_aiR->getAll();
}

void Logic::resetGame(){
	this->m_userR->clearRepo();
	this->m_aiR->clearRepo();
}
