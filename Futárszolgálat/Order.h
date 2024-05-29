#pragma once
#include <stdio.h>
#include "memtrace.h"
#include "HardwareStorage.h"

class Order
{
public:
	Order(const size_t id);
	enum class State
	{
		RecievedOrder, Shipped, Successful
	};
	void SetState(State state);
	static int GetInformationcount();
	static void GetStatMenuPoints(std::string* stringarray);
	HardwareStorage& GetHardwareStorage();
	State GetState() const;
	size_t GetOrderId() const;
	void OrderDecode(std::string& decoderow, size_t** counts, size_t** ids, size_t& itemnumber);
	void OrderEncode(std::string& encodedmessage, std::string delimeter);
	void Split(const std::string& source, char delimeter, std::string** destination, size_t& arraysize);
private:
	HardwareStorage hardwarestorage;
	const size_t id;
	State state;
	static const int informationcount = 3;
	static const std::string menupoints[informationcount];
};