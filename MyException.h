#pragma once
#include <stdexcept>

class MyException : public std::runtime_error {
private:
	const char* m_Message;
public:
	MyException(const char* message) : runtime_error(message), m_Message(message) {}
	const char* what() {
		return this->m_Message;
	}
};

typedef MyException Exc;