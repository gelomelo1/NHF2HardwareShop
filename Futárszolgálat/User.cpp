#include "memtrace.h"
#include "AccountSetters.h"

const std::string Customer::menupoints[] = { "felhasznalonev:", "jelszo:", "nev:", "email:", "telefonszam:", "varos:", "cim:" };
const std::string User::menupoints[] = { "felhasznalonev:", "jelszo:" };
const std::string Admin::menupoints[] = { "felhasznalonev:", "jelszo:" };


//User ososztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

User::User(const int countforfunctions, const bool independent) : countforfunctions(countforfunctions), centralstorage(BaseCentralStorage::GetCentralStorage()), setters(false)
{
	if (independent)
		SetSetters();
}

bool User::operator==(const User& user) const //Akkor szamit egy user egyenlonek a masikkal ha megegyezik a felhasznalonevuk, mivel ez szolgal egyedi azonositoul
{
	if (username == user.username)
		return true;
	return false;
}

bool User::EqualUsers (std::string& password, std::string& usertype ,const std::string username)
{
	for (size_t i = 0; i < centralstorage->GetAdminArray().getSize(); i++)
	{
		if (username == centralstorage->GetAdminArray()[i]->GetUsername())
		{
			password = centralstorage->GetAdminArray()[i]->GetPassword();
			usertype = "admin";
			return true;
		}
	}
	for (size_t i = 0; i < centralstorage->GetCustomerArray().getSize(); i++)
	{
		if (username == centralstorage->GetCustomerArray()[i]->GetUsername())
		{
			password = centralstorage->GetCustomerArray()[i]->GetPassword();
			usertype = "customer";
			return true;
		}
	}
	return false;
}

bool User::isStringEmpty(const std::string& text)
{
	if (text.length() == 0)
	{
		throw InvalidFormatException("Nem hagyhatod uresen a mezot");
		return true;
	}
	return false;
}

bool User::isContainSplit(const std::string& text)
{
	size_t search = text.find("|");
	if (search != text.npos)
	{
		throw InvalidFormatException("A mezo nem tartalmazhat | karaktert");
		return true;
	}
	return false;
}

void User::SetUsername(const std::string username)
{
	if (!isStringEmpty(username) && !isContainSplit(username))
	{
		size_t search = username.find(" ");
		if (search == username.npos)
			this->username = username;
		else
			throw InvalidFormatException("A felhasznalonev nem tartalmazhat space karaktert");
	}
}

BaseCentralStorage* const User::GetCentralStorage()
{
	return centralstorage;
}

std::string User::GetUsername() const
{
	return username;
}

void User::SetPassword(const std::string password)
{
	if (!isStringEmpty(password) && !isContainSplit(password))
	{
		size_t search = password.find(" ");
		if (search == password.npos)
			this->password = password;
		else
			throw InvalidFormatException("A jelszo nem tartalmazhat space karaktert");
	}
}

Array<Setters**>& User::GetSetters()
{
	return setters;
}

std::string User::GetPassword() const
{
	return password;
}

int User::GetInformationcount()
{
	return informationcount;
}

 void User::FormatInfo(std::string* text) const
{
	 text[0] = username;
	 text[1] = password;
}

 void User::GetMenuPoints(Array<std::string>* strings, std::string* otherconnection) const
 {
	 if (strings != nullptr)
	 {
		 strings->CreateArray(informationcount);
		 strings->Upload(menupoints, informationcount);
	 }
	 if (otherconnection != nullptr)
	 {
		 for (size_t i = 0; i < informationcount; i++)
			 otherconnection[i] = menupoints[i];
	 }
}


 void User::SetSetters()
 {
	setters.CreateArray(informationcount);
	 PasswordSetter* passwordsetter = new PasswordSetter(this);
	 Setters* setterarray[informationcount] = { new UsernameSetter(this, passwordsetter), passwordsetter};
	 setters.Upload(setterarray, informationcount);
 }

 int User::getCountForFunctions() const
 {
	 return countforfunctions;
 }

	 
 //Admin Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 Admin::Admin() : User(informationcount, false)
 {
	 SetSetters();
 }

 void Admin::GetMenuPoints(Array<std::string>* strings, std::string* otherconnection) const
 {
	 if (strings != nullptr)
	 {
		 strings->CreateArray(informationcount);
		 strings->Upload(menupoints, informationcount);
	 }
	 if (otherconnection != nullptr)
	 {
		 for (size_t i = 0; i < informationcount; i++)
			 otherconnection[i] = menupoints[i];
	 }
 }

 void Admin::operator=(const Admin& admin)
 {
	 username = admin.username;
	 password = admin.password;
 }

 void Admin::NewHardware(Hardware* hardware)
 {
	 hardware->SetId(centralstorage->GetHardwareStorage().ValidId());
	 hardware->SetDb(0);
	 hardware->AddItself(&(centralstorage->GetHardwareStorage()));
	 centralstorage->SaveOneHardwareToFile(*hardware, "hardwares.txt");
 }

 void Admin::LoadStorage(Hardware** hardwares, const size_t count, int* db)
 {
	 for (size_t i = 0; i < count; i++)
	 {
		 hardwares[i]->SetDb(db[i]);
	 }
	 centralstorage->SaveHardwares();
 }

 void Admin::AddUser()
 {
	 Admin* admin = new Admin();
	 *admin = *this;
	 centralstorage->AddAdmin(admin);
	 centralstorage->SaveOneToFile<Admin>(*admin, "admins.txt");
 }

 void Admin::DeleteSelf()
 {
	 centralstorage->DeleteAdmin(this);
	 centralstorage->SaveFile<Admin>(centralstorage->GetAdminArray(), "admins.txt");
 }

 void Admin::DeleteOrder(size_t& userindex, size_t& orderindex)
 {
	 centralstorage->DeleteOrder(userindex, orderindex);
	 centralstorage->SaveOrdersToFile("orders.txt");
	 centralstorage->SaveHardwares();
 }

 void Admin::ShipOrder(size_t& userindex, size_t& orderindex)
 {
	 centralstorage->ChangeOrderState(userindex, orderindex, Order::State::Shipped);
	 centralstorage->SaveOrdersToFile("orders.txt");
 }

 void Admin::SetSetters()
 {
	 setters.CreateArray(informationcount);
	 PasswordSetter* passwordsetter = new PasswordSetter(this);
	 Setters* setterarray[informationcount] = { new UsernameSetter(this, passwordsetter),  passwordsetter };
	 setters.Upload(setterarray, informationcount);
 }

 int Admin::GetInformationcount()
 {
	 return informationcount;
 }

 const Array<Customer**>& Admin::GetCustomerArray() const
 {
	 return centralstorage->GetCustomerArray();
 }

 void Admin::DeleteCustomer(const int index)
 {
	 centralstorage->DeleteCustomer(index);
	 centralstorage->SaveFile<Customer>(centralstorage->GetCustomerArray(), "customers.txt");
	 centralstorage->SaveOrdersToFile("orders.txt");
	 centralstorage->SaveHardwares();
 }


 //Customer Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 Customer::Customer() : User(informationcount, false)
 {
	 SetSetters();
 }

 void Customer::DeleteSelf()
 {
	 centralstorage->DeleteCustomer(this);
	 centralstorage->SaveFile<Customer>(centralstorage->GetCustomerArray(), "customers.txt");
	 centralstorage->SaveOrdersToFile("orders.txt");
	 centralstorage->SaveHardwares();
 }

 void Customer::DeleteOrder(size_t& userindex, size_t& orderindex)
 {
	 centralstorage->DeleteOrder(userindex, orderindex);
	 centralstorage->SaveOrdersToFile("orders.txt");
	 centralstorage->SaveHardwares();
 }

 void Customer::RecieveOrder(size_t& userindex, size_t& orderindex)
 {
	 centralstorage->ChangeOrderState(userindex, orderindex, Order::State::Successful);
	 centralstorage->SaveOrdersToFile("orders.txt");
 }

 void Customer::FinishOrder(Hardware** hardwares, const size_t count, size_t* db)
 {
	 for (size_t i = 0; i < count; i++)
		 hardwares[i]->SetDb(hardwares[i]->GetDb() - db[i]);
	 centralstorage->AddCustomerOrder(this, hardwares, db, count);
	 centralstorage->SaveOrdersToFile("orders.txt");
	 centralstorage->SaveHardwares();
 }

 void Customer::operator=(const Customer& customer)
 {
	 username = customer.username;
	 password = customer.password;
	 name = customer.name;
	 email = customer.email;
	 phonenumber = customer.phonenumber;
	 city = customer.city;
	 address = customer.address;
 }

void Customer::FormatInfo(std::string* text) const
{
	text[0] = username;
	text[1] = password;
	text[2] = name;
	text[3] = email;
	text[4] = phonenumber;
	text[5] = city;
	text[6] = address;
}

void Customer::AddUser()
{
	Customer* customer = new Customer();
	*customer = *this;
	centralstorage->AddCustomer(customer);
	centralstorage->SaveOneToFile<Customer>(*customer, "customers.txt");
}

void Customer::GetMenuPoints(Array<std::string>* strings, std::string* otherconnection) const
{
	if (strings != nullptr)
	{
		strings->CreateArray(informationcount);
		strings->Upload(menupoints, informationcount);
	}
	if (otherconnection != nullptr)
	{
		for (size_t i = 0; i < informationcount; i++)
			otherconnection[i] = menupoints[i];
	}
}

void Customer::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount; i++)
		stringarray[i] = menupoints[i];
}

void Customer::SetSetters()
{

		setters.CreateArray(informationcount);
		PasswordSetter* passwordsetter = new PasswordSetter(this);
		Setters* setterarray[informationcount] = { new UsernameSetter(this, passwordsetter),  passwordsetter, new NameSetter(this), new EmailSetter(this), new PhoneSetter(this), new CitySetter(this), new AddressSetter(this) };
		setters.Upload(setterarray, informationcount);
}

void Customer::SetName(const std::string name)
{
	if (!isStringEmpty(name) && !isContainSplit(name))
	{
		bool hasdigit = false;
		for (size_t i = 0; i < name.length(); i++)
		{
			if (std::isdigit(name[i]))
			{
				hasdigit = true;
				break;
			}
		}
		if (hasdigit)
			throw InvalidFormatException("Nem lehet szam a nevedben");
		else
			this->name = name;
	}
}

void Customer::SetEmail(const std::string email)
{
	if (!isStringEmpty(email) && !isContainSplit(email))
	{
		size_t search = email.find(" ");
		if (search == email.npos)
		{
			search = email.find("@");
			if (search == email.npos)
				throw InvalidFormatException("Az email cimnek tartalmaznia kell @ karaktert");
			else
				this->email = email;
		}
		else
		{
			throw InvalidFormatException("Az email cim nem tartalmazhat space karaktert");
		}
	}
}

void Customer::SetPhonenumber(const std::string phonenumber)
{
	size_t numbercount = 11;
	if (!isStringEmpty(phonenumber) && !isContainSplit(phonenumber))
	{
		if (phonenumber.length() >= numbercount && phonenumber.length() <= numbercount + 1)
		{
			bool hasletter = false;
				int index = 0;
				if (phonenumber.length() == numbercount + 1)
				{
					if (phonenumber[0] != '+')
					{
						throw InvalidFormatException("A megadott formatumban, a legelso karakter + kell, hogy legyen");
							index = phonenumber.length();
					}
					else
						index = 1;
				}
			for (size_t i = index; i < phonenumber.length(); i++)
			{
				if (std::isalpha(phonenumber[i]))
				{
					hasletter = true;
					break;
				}
			}
			if (hasletter)
				throw InvalidFormatException("Nem szerepelhet betu a telefonszamban");
			else
				this->phonenumber = phonenumber;
		}
		else
			throw InvalidFormatException("Nem ervenyes a telefonszam merete");
	}
}

void Customer::SetCity(const std::string city)
{
	if (!isStringEmpty(city) && !isContainSplit(city))
	{
		bool hasdigit = false;
		for (size_t i = 0; i < city.length(); i++)
		{
			if (std::isdigit(city[i]))
			{
				hasdigit = true;
				break;
			}
		}
		if (hasdigit)
			 throw InvalidFormatException("Nem lehet szam a varosban");
		else
			this->city = city;
	}
}

void Customer::SetAddress(const std::string address)
{
	if(!isStringEmpty(address) && !isContainSplit(address))
	this->address = address;
}

int Customer::GetInformationcount()
{
	return informationcount;
}

std::string Customer::GetName() const
{
	return name;
}

std::string Customer::GetEmail() const
{
	return email;
}

std::string Customer::GetPhonenumber() const
{
	return phonenumber;
}

std::string Customer::GetCity() const
{
	return city;
}

std::string Customer::GetAddress() const
{
	return address;
}