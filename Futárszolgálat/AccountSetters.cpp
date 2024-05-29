#include "memtrace.h"
#include "AccountSetters.h"


//UsernameSetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void UsernameSetter::Set()
{
	std::string password;
	std::string usertype;
	bool notunique = user->EqualUsers(password, usertype, input);
	if (notunique && state == Setters::State::Registration)
		throw InvalidFormatException("A felhasznalonev mar letezik");
	else if (!notunique && state == Setters::State::Login)
		throw InvalidFormatException("A felhasznalonev helytelen");
	else
	{
		passwordsetter->SetPassword(password);
		user->SetUsername(input);
	}
}


//PasswordSetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void PasswordSetter::SetPassword(const std::string password)
{
	this->password = password;
}

void PasswordSetter::Set()
{
	if (this->password != input && state == Setters::State::Login)
		throw InvalidFormatException("A jelszo helytelen");
	else
		user->SetPassword(input);
}


//NameSetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void NameSetter::Set()
{
	customer->SetName(input);
}


//EmailSetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void EmailSetter::Set()
{
	customer->SetEmail(input);
}


//PhoneSetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void PhoneSetter::Set()
{
	customer->SetPhonenumber(input);
}


//CitySetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void CitySetter::Set()
{
	customer->SetCity(input);
}


//AddressSetter leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

void AddressSetter::Set()
{
	customer->SetAddress(input);
}