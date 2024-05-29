#pragma once
#include "memtrace.h"
#include "Setters.h"
#include "User.h"

//ACCOUNT SETTEREK



class PasswordSetter : public Setters
{
	User* user;
	std::string password;

public:
	PasswordSetter(User* user) : user(user) {}

	void SetPassword(const std::string password);

	void Set();
};

class UsernameSetter : public Setters
{
	User* user;
	PasswordSetter* passwordsetter;

public:
	UsernameSetter(User* user, PasswordSetter* passwordsetter = nullptr) : user(user), passwordsetter(passwordsetter) {}

	void Set();
};

class NameSetter : public Setters
{
	Customer* customer;

public:
	NameSetter(Customer* customer) : customer(customer) {}

	void Set();
};

class EmailSetter : public Setters
{

	Customer* customer;
public:
	EmailSetter(Customer* customer) : customer(customer) {}

	void Set();
};

class PhoneSetter : public Setters
{
	Customer* customer;
public:
	PhoneSetter(Customer* customer) : customer(customer) {}

	void Set();
};

class CitySetter : public Setters
{
	Customer* customer;
public:
	CitySetter(Customer* customer) : customer(customer) {}

	void Set();
};

class AddressSetter : public Setters
{
	Customer* customer;
public:
	AddressSetter(Customer* customer) : customer(customer) {}

	void Set();
};
