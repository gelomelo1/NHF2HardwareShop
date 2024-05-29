#include "memtrace.h"
#include "Order.h"

const std::string Order::menupoints[informationcount] = { "rendelo neve:", "rendeles tetelei(mennyisegX#id):", "statusz:"};


//Order osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

Order::Order(const size_t id) : id(id), state(Order::State::RecievedOrder) {}
int Order::GetInformationcount()
{
	return informationcount;
}
void Order::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount; i++)
		stringarray[i] = menupoints[i];
}
void Order::SetState(State state)
{
	this->state = state;
}
HardwareStorage& Order::GetHardwareStorage()
{
	return hardwarestorage;
}
Order::State Order::GetState() const
{
	return state;
}
size_t Order::GetOrderId() const
{
	return id;
}

void Order::Split(const std::string& source, char delimeter, std::string** destination, size_t& arraysize)
{
	size_t size = 0;
	for (size_t i = 0; i < source.length(); i++)
	{
		if (source[i] == delimeter)
			size++;
	}
	*destination = new std::string[size + 1];
	size_t start = 0;
	size = 0;
	for (size_t i = 0; i < source.length(); i++)
	{
		if (source[i] == delimeter)
		{
			(*destination)[size++] = source.substr(start, i - start);
			start = i + 1;
		}
	}
	(*destination)[size++] = source.substr(start);
	arraysize = size;
}

void Order::OrderDecode(std::string& decoderow, size_t** counts, size_t** ids, size_t& itemnumber)
{
	std::string* ordersplit;
	Split(decoderow, '|', &ordersplit, itemnumber);
	*counts = new size_t[itemnumber];
	*ids = new size_t[itemnumber];
	for (size_t i = 0; i < itemnumber; i++)
	{
		std::string* item;
		size_t itemcount = 0;
		Split(ordersplit[i], 'X', &item, itemcount);
		(*counts)[i] = atoi(item[0].c_str());
		item[1][0] = '0';
		(*ids)[i] = atoi(item[1].c_str());
		delete[] item;
	}
	delete[] ordersplit;
}

void Order::OrderEncode(std::string& encodedmessage, std::string delimeter)
{
	size_t count = 0;
	Hardware** orderedhardwares = hardwarestorage.GetEveryHardareInStorage(count);
	std::string currentencode;
	for (size_t i = 0; i < count; i++)
	{
		currentencode = std::to_string(orderedhardwares[i]->GetDb()) + "X#" + std::to_string(orderedhardwares[i]->GetId());
		if (count != i + 1)
			encodedmessage += currentencode + delimeter;
		else
			encodedmessage += currentencode;
	}
	delete[] orderedhardwares;
}