#include "memtrace.h"
#include "MenuItem.h"


//MenuItem ososztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuItem::ChangeToSubmenu(MenuContainer* container) const
{
	container->SetSubmenu(true);
}

std::string MenuItem::getName() const
{
	return name;
}

void MenuItem::SetSerial(const int serial)
{
	this->serial = serial;
}

int MenuItem::getSerial() const
{
	return serial;
}

std::string MenuItem::Print() const
{
	std::string value;
	char c = serial + 55;
	if (serial < 10)
		value = std::to_string(serial) + "." + name;
	else
	{
		value = c;
		value += "." + name;
	}
	return value;
}