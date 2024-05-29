#pragma once
#include "memtrace.h"
#include "FileHandler.h"

class Setters
{

public:

	Setters() : state(State::None) {}

	enum class State
	{
		None, Registration, Login
	};

	void SetInput(const std::string input);

	void SetState(const Setters::State state);

	virtual void Set() = 0;

	virtual ~Setters() {}

protected:
	std::string input;
	CheckError error;
	State state;
};