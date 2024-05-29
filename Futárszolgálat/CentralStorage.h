#pragma once
#include "memtrace.h"
#include "FileHandler.h"
#include "GeneralFunctions.h"
#include "HardwareStorage.h"
#include "OrdersPerUser.h"
#include "Order.h"
#include "User.h"

class Admin;
class Customer;
class User;

class BaseCentralStorage   //Ez a class kezel minden adatot, ide erkezik be, es innen jon ki adat
{
private:
	static int pin;
	Array<Admin**> admins;
	Array<Customer**> customers;
	HardwareStorage hardwares;
	FileHandler handler;
	Array<OrdersPerUser**> ordersperuser;
	CheckError error;

	template<class Tclass>
	void SetValues(Tclass* newmember, const size_t count, int& index, std::string* filerows)
	{
		for (size_t j = 0; j < count; j++)
		{   
			newmember->GetSetters()[j]->SetInput(filerows[index]);
			newmember->GetSetters()[j]->Set();
			index++;
		}
	}

	template<class Tclass, class StorageClass>
	void ReadFile(StorageClass& storageclass, const std::string filename)
	{
		if (!handler.FileExist(filename))
			handler.CreateFileCustom(filename);
		std::string* filerows = nullptr;
		size_t count = 0;
		handler.ReadFromFile(filename, &filerows, &count, 1, Tclass::GetInformationcount());
		storageclass.CreateArray(count / Tclass::GetInformationcount());
		int index = 0;
		for (size_t i = 0; i < count / Tclass::GetInformationcount(); i++)
		{
			Tclass* newmember = new Tclass();
			SetValues(newmember, Tclass::GetInformationcount(), index, filerows);
			storageclass.Upload(newmember);
		}
		delete[] filerows;
	}
	void ReadHardwareFile(std::string filename);
	void ReadOrderFile(std::string filename);

public:
	BaseCentralStorage();
	int CheckPin();
	void StartUp();
	template<class Tclass, class StorageClass>
	void SaveFile(StorageClass& storageclass, const std::string filename)
	{
		Array<std::string> infos;
		infos.CreateArray(storageclass.getSize() * (Tclass::GetInformationcount() + 1));
		size_t startindex = 0;
		size_t endindex = startindex + Tclass::GetInformationcount();
		for (size_t i = 0; i < storageclass.getSize(); i++)
		{
			Array<std::string> packages;
			packages.CreateArray(Tclass::GetInformationcount() + 1);
			storageclass[i]->FormatInfo(packages.getArray());
			packages[Tclass::GetInformationcount()] = "";
			size_t counter = 0;
			for (size_t j = startindex; j <= endindex; j++)
			{
				infos[j] = packages[counter++];
				if (j == endindex)
				{
					startindex = endindex + 1;
				}
			}
			endindex = startindex + Tclass::GetInformationcount();
		}
		handler.WriteToFile(filename, infos.getArray(), storageclass.getSize() * (Tclass::GetInformationcount() + 1), false, true);
	}
	template<class Tclass, class StorageClass>
	void SaveOneToFile(StorageClass& storageclass, const std::string filename)
	{
		Array<std::string>info;
		info.CreateArray(Tclass::GetInformationcount());
		storageclass.FormatInfo(info.getArray());
		handler.WriteToFile(filename, info.getArray(), Tclass::GetInformationcount(), true);
	}

	template<class StorageClass>
	void SaveOneHardwareToFile(StorageClass& storageclass, const std::string filename)
	{
		Array<std::string>info;
		info.CreateArray(Hardware::GetBaseinformationcount() + storageclass.GetCountForFunctions() + 1);
		storageclass.FormatInfo(info.getArray());
		handler.WriteToFile(filename, info.getArray(), Hardware::GetBaseinformationcount() + storageclass.GetCountForFunctions() + 1, true);

	}

	template<class Tclass, class StorageClass>
	void SaveHardwareToFile(StorageClass& storageclass, const std::string filename, const bool overwrite)
	{
		Array<std::string> infos;
		infos.CreateArray(storageclass.getSize() * (Hardware::GetBaseinformationcount() + Tclass::GetInformationcount() + 2));
		size_t startindex = 0;
		size_t endindex = startindex + Hardware::GetBaseinformationcount() + Tclass::GetInformationcount() + 1;
		for (size_t i = 0; i < storageclass.getSize(); i++)
		{
			Array<std::string> packages;
			packages.CreateArray(Hardware::GetBaseinformationcount() + Tclass::GetInformationcount() + 2);
			storageclass[i]->FormatInfo(packages.getArray());
			packages[Hardware::GetBaseinformationcount() + Tclass::GetInformationcount() + 1] = "";
			size_t counter = 0;
			for (size_t j = startindex; j <= endindex; j++)
			{
				infos[j] = packages[counter++];
				if (j == endindex)
				{
					startindex = endindex + 1;
				}
			}
			endindex = startindex + Hardware::GetBaseinformationcount() + Tclass::GetInformationcount() + 1;
		}
		handler.WriteToFile(filename, infos.getArray(), storageclass.getSize() * (Hardware::GetBaseinformationcount() + Tclass::GetInformationcount() + 2), false, overwrite);
	}

	void SaveHardwares();

	const Array<Admin**>& GetAdminArray() const;
	void AddAdmin(Admin* admin);
	void DeleteAdmin(Admin* admin);

	const Array<Customer**>& GetCustomerArray() const;
	void AddCustomer(Customer* customer);
	void DeleteCustomer(Customer* customer);
	void DeleteCustomer(const int index);

	Customer* SearchForCustomer(Customer* customer);
	void DeleteOrder(size_t& userindex, size_t& orderindex);
	void ChangeOrderState(size_t& userindex, size_t& orderindex, Order::State state);
	void SaveOrdersToFile(const std::string filename);
	size_t GetCountOfOrdersInAState(Order::State state);
	size_t GetCountOfOrdersForACustomer(Customer* customer, size_t& index);
	HardwareStorage& GetHardwareStorage();
	Array<OrdersPerUser**>& GetOrdersPerUser();
	void AddCustomerOrder(Customer* customer, Hardware** hardwares, size_t* db, const size_t count);
	static int getPin();
	static BaseCentralStorage* itself;
	static BaseCentralStorage* GetCentralStorage();
};
