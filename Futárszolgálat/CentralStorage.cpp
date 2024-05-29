#include "memtrace.h"
#include "CentralStorage.h"
#include "CportaDefine.h"

BaseCentralStorage* BaseCentralStorage::itself = nullptr;
int BaseCentralStorage::pin = 0;


//BaseCentralStorage leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseCentralStorage::BaseCentralStorage() : admins(false), customers(false), ordersperuser(false)
{
	itself = this;
	StartUp();
}

void BaseCentralStorage::StartUp()
{
	pin = CheckPin();
	ReadFile<Admin>(admins, "admins.txt");
	ReadFile<Customer>(customers, "customers.txt");
	ReadHardwareFile("hardwares.txt");
	ReadOrderFile("orders.txt");
}

#ifdef CPORTA
int BaseCentralStorage::CheckPin()
{
	bool exist = handler.FileExist("pin.txt");
	int pin = 0;
	if (exist)
	{
		std::string* value;
		size_t valuecount;
		handler.ReadFromFile("pin.txt", &value, &valuecount);
		pin = atoi(value->c_str());
		delete[] value;
		if (pin < 1000 || pin > 9999)
			exist = false;
	}
	if (!exist)
	{
		const std::string instruction = "Adjon meg egy 4 jegyu pin kodot amivel admin felhasznalok tudnak regisztralni:";
		std::string input;
		std::cout << instruction;
		do
		{
			try
			{
				error.SetClearIfError(false);
				std::getline(std::cin, input);
				pin = atoi(input.c_str());
				if (pin < 1000 || pin > 9999)
					throw InvalidFormatException("A pin kodnak 4 jegyunek kell lennie");
			}
			catch (InvalidFormatException e)
			{
				error.ErrorOutput(e.what());
				std::cout << "\n";
			}

		} while (error.GetClearIFerror());
		handler.CreateFileCustom("pin.txt");
		try
		{
			handler.WriteToFile("pin.txt", &pin, 1);
		}
		catch (InvalidProcess e)
		{
			error.ErrorOutput(e.what());
		}
	}
	return pin;
}
#endif // CPORTA

#ifndef CPORTA
#include <Windows.h>
#include <conio.h>
int BaseCentralStorage::CheckPin()
{
	bool exist = handler.FileExist("pin.txt");
	int pin = 0;
	if (exist)
	{
		std::string* value;
		size_t valuecount;
		handler.ReadFromFile("pin.txt", &value, &valuecount);
		pin = atoi(value->c_str());
		delete[] value;
		if (pin < 1000 || pin > 9999)
			exist = false;
	}
	if (!exist)
	{
		const std::string instruction = "Adjon meg egy 4 jegyu pin kodot amivel admin felhasznalok tudnak regisztralni:";
		std::string input;
		std::cout << instruction;
		do
		{
			try
			{
				error.SetClearIfError(false);
				error.MovePos(instruction.length() + 1, 0);
				std::getline(std::cin, input);
				pin = atoi(input.c_str());
				if (pin < 1000 || pin > 9999)
					throw InvalidFormatException("A pin kodnak 4 jegyunek kell lennie");
			}
			catch (InvalidFormatException e)
			{
				error.ErrorOutput(e.what());
				error.ClearText(instruction.length() + 1, 0, input.length());
			}

		} while (error.GetClearIFerror());
		handler.CreateFileCustom("pin.txt");
		try
		{
			handler.WriteToFile("pin.txt", &pin, 1);
		}
		catch (InvalidProcess e)
		{
			error.ErrorOutput(e.what());
		}
	}
	return pin;
}
#endif // !CPORTA


void BaseCentralStorage::ReadOrderFile(std::string filename)
{
	if (!handler.FileExist(filename))
		handler.CreateFileCustom(filename);
	ordersperuser.CreateArray(1);
	std::string* filerows = nullptr;
	size_t count = 0;
	handler.ReadFromFile(filename, &filerows, &count, 0, 1, true);
	enum class State
	{
		RecievedOrder, Shipped, Successful
	};
	State state = State::RecievedOrder;
	Array<std::string> blocks;
	bool nextlinename = true;
	OrdersPerUser* orders = nullptr;
	size_t orderid = 0;
	size_t* counts;
	size_t* ids;
	size_t itemnumber = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (nextlinename)
		{
			orders = new OrdersPerUser(filerows[i]);
			orderid = 0;
			state = State::RecievedOrder;
			nextlinename = false;
		}
		else if (filerows[i] == "-")
		{
			if (state == State::RecievedOrder)
				state = State::Shipped;
			else if (state == State::Shipped)
				state = State::Successful;
		}
		else if (filerows[i] != "")
		{
			Order* order = new Order(orderid);
			orderid++;
			order->OrderDecode(filerows[i], &counts, &ids, itemnumber);
			for (size_t i = 0; i < itemnumber; i++)
			{
				Hardware* hardware = hardwares.SearchForId(ids[i]);
				Hardware* orderhardware = hardware->Clone();
				orderhardware->SetDb(counts[i]);
				orderhardware->AddItself(&(order->GetHardwareStorage()));
			}
		if (state == State::RecievedOrder)
			order->SetState(Order::State::RecievedOrder); //Elöször beerkezett rendeles
		else if (state == State::Shipped)
			order->SetState(Order::State::Shipped); //Aztan postazott rendeles
		else if (state == State::Successful)
			order->SetState(Order::State::Successful); //Aztan teljesitett rendeles
		orders->AddOrder(order);
		delete[] counts;
		delete[] ids;
		}
		else
		{
			ordersperuser.Upload(orders);
			nextlinename = true;
		}
	}
	delete[] filerows;
}

void BaseCentralStorage::ReadHardwareFile(std::string filename)
{
	if (!handler.FileExist(filename))
		handler.CreateFileCustom(filename);
	std::string* filerows = nullptr;
	size_t count = 0;
	handler.ReadFromFile(filename, &filerows, &count, 0, 1, true);
	Array<std::string> blocks;
	bool nextlinetype = true;
	Hardware* hardware = nullptr;
	for (size_t i = 0; i < count; i++)
	{
		if (nextlinetype)
		{
			if (filerows[i] == CPU::getStatType())
			{
				CPU* cpu = new CPU;
				hardwares.AddCPU(cpu);
				hardware = cpu;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == GPU::getStatType())
			{
				GPU* gpu = new GPU;
				hardwares.AddGPU(gpu);
				hardware = gpu;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == Memory::getStatType())
			{
				Memory* memory = new Memory;
				hardwares.AddMemory(memory);
				hardware = memory;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == Motherboard::getStatType())
			{
				Motherboard* motherboard = new Motherboard;
				hardwares.AddMotherboard(motherboard);
				hardware = motherboard;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == PowerSupply::getStatType())
			{
				PowerSupply* powersupply = new PowerSupply;
				hardwares.AddPowerSupply(powersupply);
				hardware = powersupply;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == HDD::getStatType())
			{
				HDD* hdd = new HDD;
				hardwares.AddHDD(hdd);
				hardware = hdd;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == SSD::getStatType())
			{
				SSD* ssd = new SSD;
				hardwares.AddSSD(ssd);
				hardware = ssd;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			if (filerows[i] == ComputerCase::getStatType())
			{
				ComputerCase* computercase = new ComputerCase;
				hardwares.AddComputerCase(computercase);
				hardware = computercase;
				blocks.CreateArray(hardware->GetCountForFunctions());
			}
			nextlinetype = false;
		}
		else if(filerows[i] != "")
		{
			blocks.Upload(filerows[i]);
		}
		else
		{
			int index = 0;
			SetValues(hardware, hardware->GetCountForFunctions() + Hardware::GetBaseinformationcount(), index, blocks.getArray());
			blocks.Clear();
			nextlinetype = true;
		}
	}
	delete[] filerows;
}

void BaseCentralStorage::SaveHardwares()
{
	SaveHardwareToFile<CPU>(hardwares.GetCPUArray(), "hardwares.txt", true);
	SaveHardwareToFile<GPU>(hardwares.GetGPUArray(), "hardwares.txt", false);
	SaveHardwareToFile<Memory>(hardwares.GetMemoryArray(), "hardwares.txt", false);
	SaveHardwareToFile<Motherboard>(hardwares.GetMotherboardArray(), "hardwares.txt", false);
	SaveHardwareToFile<PowerSupply>(hardwares.GetPowerSupplyArray(), "hardwares.txt", false);
	SaveHardwareToFile<HDD>(hardwares.GetHDDArray(), "hardwares.txt", false);
	SaveHardwareToFile<SSD>(hardwares.GetSSDArray(), "hardwares.txt", false);
	SaveHardwareToFile<ComputerCase>(hardwares.GetComputerCaseArray(), "hardwares.txt", false);
}

void BaseCentralStorage::SaveOrdersToFile(const std::string filename)
{
	Array<std::string> rows;
	rows.CreateArray(ordersperuser.getSize() * 8);
	Order::State searchstate;
	searchstate = Order::State::RecievedOrder;
	size_t iterationcount = 0;
	for (size_t i = 0; i < ordersperuser.getSize(); i++)
	{
		rows.Upload(ordersperuser[i]->GetCustomername());
		searchstate = Order::State::RecievedOrder;
		iterationcount = 0;
		while (iterationcount != 3)
		{
			for (size_t j = 0; j < ordersperuser[i]->GetOrders().getSize(); j++)
			{
				if (searchstate == ordersperuser[i]->GetOrders()[j]->GetState())
				{
					std::string encodedmessage;
					ordersperuser[i]->GetOrders()[j]->OrderEncode(encodedmessage, "|");
					rows.Upload(encodedmessage);
				}
			}
			if (iterationcount != 2)
			{
				rows.Upload("-");
			}
			if (iterationcount == 0)
				searchstate = Order::State::Shipped;
			else if (iterationcount == 1)
				searchstate = Order::State::Successful;
			iterationcount++;
		}
		rows.Upload("");
	}
	try
	{
		handler.WriteToFile(filename, rows.getArray(), rows.getSize(), false, true);
	}
	catch (InvalidProcess e)
	{
		error.ErrorOutput(e.what());
	}
}

int BaseCentralStorage::getPin()
{
	return pin;
}

const Array<Admin**>& BaseCentralStorage::GetAdminArray() const
{
	return admins;
}
void BaseCentralStorage::AddAdmin(Admin* admin)
{
	admins.Upload(admin);
}

void BaseCentralStorage::DeleteAdmin(Admin* admin)
{
	for (size_t i = 0; i < admins.getSize(); i++)
	{
		if (*admins[i] == *admin)
			admins.DeleteItem(i);
	}
}

const Array<Customer**>& BaseCentralStorage::GetCustomerArray() const
{
	return customers;
}
void BaseCentralStorage::AddCustomer(Customer* customer)
{
	customers.Upload(customer);
}

void BaseCentralStorage::DeleteCustomer(Customer* customer)
{
	size_t userindex = 0;
	size_t ordercount = 0;
	for (size_t i = 0; i < ordersperuser.getSize(); i++)
	{
		if (customer->GetUsername() == ordersperuser[i]->GetCustomername())
		{
			userindex = i;
			ordercount = ordersperuser[i]->GetOrders().getSize();
			break;
		}
	}

	size_t orderindex = 0;
	for (size_t i = 0; i < ordercount; i++)
	{
		DeleteOrder(userindex, orderindex);
	}

	for (size_t i = 0; i < customers.getSize(); i++)
	{
		if (*customers[i] == *customer)
		{
			customers.DeleteItem(i);
			break;
		}
	}
}

void BaseCentralStorage::DeleteCustomer(const int index)
{
	size_t userindex = 0;
	size_t ordercount = 0;
	for (size_t i = 0; i < ordersperuser.getSize(); i++)
	{
		if (customers[index]->GetUsername() == ordersperuser[i]->GetCustomername())
		{
			userindex = i;
			ordercount = ordersperuser[i]->GetOrders().getSize();
			break;
		}
	}

	size_t orderindex = 0;
	for (size_t i = 0; i < ordercount; i++)
	{
		DeleteOrder(userindex, orderindex);
	}

	customers.DeleteItem(index);
}

void BaseCentralStorage::DeleteOrder(size_t& userindex, size_t& orderindex)
{
	if (ordersperuser[userindex]->GetOrders()[orderindex]->GetState() == Order::State::RecievedOrder || ordersperuser[userindex]->GetOrders()[orderindex]->GetState() == Order::State::Shipped)
	{
		size_t orderedhardwarescount = 0;
		Hardware** orderedhardwares = ordersperuser[userindex]->GetOrders()[orderindex]->GetHardwareStorage().GetEveryHardareInStorage(orderedhardwarescount);
		size_t originalhardwarescount = 0;
		Hardware** originalhardwares = hardwares.GetEveryHardareInStorage(originalhardwarescount);
		for (size_t i = 0; i < orderedhardwarescount; i++)
		{
			for (size_t j = 0; j < originalhardwarescount; j++)
			{
				if (*(orderedhardwares[i]) == *(originalhardwares[j]))
				{
					originalhardwares[j]->SetDb(originalhardwares[j]->GetDb() + orderedhardwares[i]->GetDb());
					break;
				}
			}
		}
		delete[] orderedhardwares;
		delete[] originalhardwares;
	}
	ordersperuser[userindex]->GetOrders().DeleteItem(orderindex);
	if (ordersperuser[userindex]->GetOrders().getSize() == 0)
		ordersperuser.DeleteItem(userindex);
}

void BaseCentralStorage::ChangeOrderState(size_t& userindex, size_t& orderindex, Order::State state)
{
	ordersperuser[userindex]->GetOrders()[orderindex]->SetState(state);
}

size_t BaseCentralStorage::GetCountOfOrdersInAState(Order::State state)
{
	size_t count = 0;
	for (size_t i = 0; i < ordersperuser.getSize(); i++)
	{
		for (size_t j = 0; j < ordersperuser[i]->GetOrders().getSize(); j++)
		{
			if (ordersperuser[i]->GetOrders()[j]->GetState() == state)
				count++;
		}
	}
	return count;
}

size_t BaseCentralStorage::GetCountOfOrdersForACustomer(Customer* customer, size_t& index)
{
	size_t count = 0;
	for (size_t i = 0; i < ordersperuser.getSize(); i++)
	{
		if (ordersperuser[i]->GetCustomername() == customer->GetUsername())
		{
			index = i;
			for (size_t j = 0; j < ordersperuser[i]->GetOrders().getSize(); j++)
			{
				count++;
			}
			break;
		}
	}
	return count;
}

HardwareStorage& BaseCentralStorage::GetHardwareStorage()
{
	return hardwares;
}

Array<OrdersPerUser**>& BaseCentralStorage::GetOrdersPerUser()
{
	return ordersperuser;
}

Customer* BaseCentralStorage::SearchForCustomer(Customer* customer)
{
	for (size_t i = 0; i < customers.getSize(); i++)
	{
		if (*(customers[i]) == *customer)
			return customers[i];
	}
	return nullptr;
}

void BaseCentralStorage::AddCustomerOrder(Customer* customer, Hardware** hardwares, size_t* db, const size_t count)
{
	bool hasorder = false;
	size_t index = 0;
	for (size_t i = 0; i < ordersperuser.getSize(); i++)
	{
		if (ordersperuser[i]->GetCustomername() == customer->GetUsername())
		{
			hasorder = true;
			index = i;
			break;
		}
	}
	if (!hasorder)
	{
		OrdersPerUser* newordersperuser = new OrdersPerUser(customer->GetUsername());
		ordersperuser.Upload(newordersperuser);
		index = ordersperuser.getSize() - 1;
	}
	Order* order = new Order(ordersperuser[index]->GetNewId());
	order->SetState(Order::State::RecievedOrder);
	for (size_t i = 0; i < count; i++)
	{
		Hardware* orderhardware = hardwares[i]->Clone();
		orderhardware->SetDb(db[i]);
		orderhardware->AddItself(&(order->GetHardwareStorage()));
	}
	ordersperuser[index]->AddOrder(order);
}

BaseCentralStorage* BaseCentralStorage::GetCentralStorage()
{
	return itself;
}