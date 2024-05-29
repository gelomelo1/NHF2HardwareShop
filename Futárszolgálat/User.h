#pragma once
#include "GeneralFunctions.h"
#include "memtrace.h"
#include "Hardware.h"
#include "Setters.h"
#include "CentralStorage.h"

class Customer;
class Admin;
class User;
class BaseCentralStorage;
class Hardware;

class User
{
private:
	static const int informationcount = 2;
	static const std::string menupoints[informationcount];
protected:
	const int countforfunctions;
	BaseCentralStorage* const centralstorage;
	Array<Setters**>setters;
	std::string username;
	std::string password;
	CheckError error;

	virtual void SetSetters();

public:
	
	bool isStringEmpty(const std::string& text);

	bool isContainSplit(const std::string& text);

	User(const int countforfunctions = informationcount, const bool independent = true);

	void SetUsername(const std::string username);

	std::string GetUsername() const;
	
	void SetPassword(const std::string password);

	std::string GetPassword() const;

	BaseCentralStorage* const GetCentralStorage();

	int getCountForFunctions() const;

	bool EqualUsers(std::string& password, std::string& usertype, const std::string username);

	bool operator==(const User& user) const;

	static int GetInformationcount();

	virtual void GetMenuPoints(Array<std::string>* strings, std::string* otherconnection = nullptr) const;

	Array<Setters**>& GetSetters();

	virtual void FormatInfo(std::string* text) const;

	virtual void AddUser() {}

	virtual ~User() {}
};

class Admin : public User
{

	static const int informationcount = 2;
	static const std::string menupoints[informationcount];
	void SetSetters();

public:

	Admin();

	void GetMenuPoints(Array<std::string>* strings, std::string* otherconnection = nullptr) const;

	void DeleteCustomer(const int index);

	void AddUser();

	void DeleteSelf();

	void DeleteOrder(size_t& userindex, size_t& orderindex);

	void ShipOrder(size_t& userindex, size_t& orderindex);

	void NewHardware(Hardware* hardware);

	void LoadStorage(Hardware** hardwares, const size_t count, int* db);

	const Array<Customer**>& GetCustomerArray() const;

	void operator=(const Admin& admin);

	static int GetInformationcount();
};

class Customer : public User
{
	static const int informationcount = 7;
	static const std::string menupoints[informationcount];
	std::string name;
	std::string email;
	std::string phonenumber;
	std::string city;
	std::string address;

	void SetSetters();

public:

	Customer();

	void operator=(const Customer& customer);

	void FormatInfo(std::string* text) const;

	void AddUser();

	void DeleteSelf();

	void DeleteOrder(size_t& userindex, size_t& orderindex);

	void RecieveOrder(size_t& userindex, size_t& orderindex);

	void GetMenuPoints(Array<std::string>* strings, std::string* otherconnection = nullptr) const;

	static void GetStatMenuPoints(std::string* stringarray);

	std::string GetName() const;

	std::string GetEmail() const;

	std::string GetPhonenumber() const;

	std::string GetCity() const;

	std::string GetAddress() const;

	void SetName(const std::string name);

	void SetEmail(const std::string email);

	void SetPhonenumber(const std::string phonenumber);

	void SetCity(const std::string city);

	void SetAddress(const std::string address);

	void FinishOrder(Hardware** hardwares, const size_t count, size_t* db);

	static int GetInformationcount();
};