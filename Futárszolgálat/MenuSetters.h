#pragma once
#include "memtrace.h"
#include "Setters.h"
#include "Menu.h"
class PincodeSetter : public Setters
{
	AccountMenu* menu;

public:
	PincodeSetter(AccountMenu* menu) : menu(menu) {}

	void Set();
};