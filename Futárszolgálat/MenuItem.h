#pragma once
#include "memtrace.h"
#include "Menu.h"

class MenuContainer;

class MenuItem
{
protected:
	std::string name; //Menupont neve
	const std::string castname;
	int serial;

public:
	MenuItem(const std::string castname) : castname(castname), serial(0) {}
	std::string getName() const; //Nev getter
	std::string Print() const;
	void SetSerial(const int serial);
	int getSerial() const;
	void ChangeToSubmenu(MenuContainer* container) const; //A menucontainer almenüjet bool valtozojat atallitjuk
	virtual void Task(MenuContainer* container) = 0;
	virtual ~MenuItem() {}
};