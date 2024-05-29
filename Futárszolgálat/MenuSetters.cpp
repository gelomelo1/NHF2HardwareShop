#include "memtrace.h"
#include "MenuSetters.h"


//PincodeSetter Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void PincodeSetter::Set()
{
	bool containletter = false;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] < 48 || input[i] > 57)
		{
			containletter = true;
			break;
		}
	}
	if (!containletter)
	{
		int pin = atoi(input.c_str());
		menu->SetPincode(pin);
	}
	else
	{
		throw InvalidFormatException("A pin kod csak szamot tartalmaz");
	}
}