#pragma once
#include <ios>
#include <limits>
#include "CportaDefine.h"
#include "memtrace.h"
#include "GeneralFunctions.h"
#include "FileHandler.h"
#include "MenuItem.h"
#include "User.h"

#ifndef CPORTA
#include <Windows.h>
#include <conio.h>
#endif // !CPORTA

class MenuItem;
class Admin;
class Setters;

class MenuContainer
{
protected:
	MenuItem** items;        //Fomenu opciok valtozoi
	const int maxitemcount;
	int itemcount;
	int selected;

	MenuItem** submenuitems;  //Almenu opciok valtozoi
	int submenuitemcount;

	MenuContainer* nextmenu; //Menu folyamat valtozoi
	bool proceed;
	bool submenu;

	CheckError error;    //Hiba kezelo osztaly

	static const int height = 50; //Menu kinezet valtozoi
	static const int width = 211;
	const std::string originalmenuname;
	std::string menuname;
	const int startheight;

	void AddItem(MenuItem* item);
	void AddSubItem(MenuItem* item);
	void MainMenu();
	void TableControl(std::string** content, const int maxrowindex, const int columnindex, const int columswidth, const int startheight, int& selectedrow, bool& outsidecontrol);
#ifdef CPORTA
	template<class Tclass>
	void TextInput(Tclass& selectedclass, const int textsnumber, std::string* menupoints, const bool aftercin, const int offset = 0, const bool resetpos = false)
	{
		bool quit = false;
		std::string input;
		if (aftercin)
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (int i = 0; i < textsnumber; i++)
		{
			do
			{
				error.SetClearIfError(false);
				std::getline(std::cin, input);
				if (input == "Kilepes")
				{
					quit = true;
					SetSubmenu(false);
					break;
				}
				try
				{
					selectedclass.GetSetters()[i]->SetInput(input);
					selectedclass.GetSetters()[i]->Set();
				}
				catch (InvalidFormatException e)
				{
					error.ErrorOutput(e.what());
					std::cout << "\n";
				}
			} while (error.GetClearIFerror());
			if (quit)
				break;
		}
	}
#endif // CPORTA

#ifndef CPORTA
	template<class Tclass>
	void TextInput(Tclass& selectedclass, const int textsnumber, std::string* menupoints, const int offset = 0, const bool resetpos = false)
	{
		error.MovePos(0, startheight + offset);
		bool quit = false;
		int y = startheight + offset;
		int x = 0;
		std::string input;
		for (int i = 0; i < textsnumber; i++)
		{
			do
			{
				error.SetClearIfError(false);
				x = menupoints[i].length() + 1;
				error.MovePos(x, y);
				std::getline(std::cin, input);
				if (input == "Kilepes")
				{
					quit = true;
					SetSubmenu(false);
					break;
				}
				try
				{
					selectedclass.GetSetters()[i]->SetInput(input);
					selectedclass.GetSetters()[i]->Set();
				}
				catch (InvalidFormatException e)
				{
					error.ClearError();
					error.ErrorOutput(e.what());
				}
				if (error.GetClearIFerror())
					error.ClearText(x, y, input.length());
			} while (error.GetClearIFerror());
			error.ClearError();
			y++;
			if (quit)
				break;
		}
		if (resetpos)
			error.MovePos(0, 0);
	}
#endif // !CPORTA

	virtual void MenuExtraDisplay() {}
public:

	std::string GetMenuname() const;

	MenuContainer(const int maxitemcount, const std::string menuname) : items(nullptr), maxitemcount(maxitemcount), itemcount(0), selected(0), submenuitems(nullptr), submenuitemcount(0), nextmenu(nullptr), proceed(false), submenu(false), originalmenuname(menuname), menuname(menuname), startheight(2) {}

	void MenuItemPrint(const int count, std::string* menupoints, const bool displaysubmenu = true) const;

	int CharToInt(const char& value, const bool submenumode = false, int offset = 0) const;

	int MenuSelectInput() const;

	void WaitForEnter(const std::string display) const;

	bool Decide(const std::string display) const;

	void ClearScreen() const;

	void Loop();

	void SetSubmenu(const bool submenu);

	void Table(std::string** content, const int rows, const int columns, const int columswidth, const int startheight, const int selected) const;

	MenuContainer* getNextmenu() const;

	 virtual std::string getType() const = 0;

	 template<class T>
	 void FreeClassArray(T** t, int& count, bool dynamicarray = false) const;

	 virtual void ExitMenu() = 0;

	virtual ~MenuContainer();
};

class AccountMenu : public MenuContainer
{
	Array<Setters**> setter;
	int pincode;

public:

	AccountMenu();

	Array<Setters**>& GetSetters();

	void SetPincode(const int pincode);

	void RegistrationProcess();

	static std::string getStatType();

	std::string getType() const;

	void LoginProcess();

	void ExitMenu();
};


class AdminMenu : public MenuContainer
{
	Admin* admin;
	size_t* userindex;
	size_t* orderindex;
	int selectedIndex;

public:
	AdminMenu(Admin* admin);

	static std::string getStatType();

	std::string getType() const;

	void ListAccounts();

	void ListOrders();

	void DeleteOrder();

	void ShipOrder();

	void ExitMenu();

	void MenuExtraDisplay();

	void DeleteSelf();

	void AddHardwareProcess();

	void AddStorageProcess();

	void DeleteCustomer();

	~AdminMenu();
};

class HardwareProcessSubMenu : public MenuContainer
{
	Admin* admin;
public:
	HardwareProcessSubMenu(Admin* admin, const std::string menuname);

	template<class Tclass>
	void AddHardware()
	{
		menuname = menuname + "->" + Tclass::getStatType();
		std::string quitinfo = "Vissza a menube = 'Kilepes'";
		MenuItemPrint(1, &quitinfo);
		Tclass* newmember = new Tclass;
		newmember->SetState(Tclass::State::Input);
		std::string* labels = new std::string[Tclass::GetInformationcount() + 1];
		Tclass::GetStatMenuPoints(labels);
		MenuItemPrint(Tclass::GetInformationcount() + 1, labels, false);
#ifdef CPORTA
		TextInput(*newmember, Tclass::GetInformationcount() + 1, labels, true, 1);
#endif // CPORTA

#ifndef CPORTA
		TextInput(*newmember, Tclass::GetInformationcount() + 1, labels, 1);
#endif // !CPORTA


		if (!submenu)
		{
			delete[] labels;
			delete newmember;
			return;
		}
		newmember->SetState(Tclass::State::Load);
		admin->NewHardware(newmember);
		WaitForEnter("\nA hardver hozzadas sikeres");
		delete[] labels;
		SetSubmenu(false);
	}

	static std::string getStatType();

	std::string getType() const;

	void ExitMenu();
};

class HardwareIncrease;
class HardwareDecrease;

class StorageProcessSubMenu : public MenuContainer
{
	Admin* admin;
	int selectedIndex;
	int informationsize;
	Array<int> hardwaredb;
	Array<int> originalhardwaredb;
	Array<std::string**> menupoints;
	Hardware** hardwares;
	size_t hardwarecount;
	bool manipulated;
public:
	StorageProcessSubMenu(Admin* admin, const std::string menuname);

	template<typename Tclass>
	void ListHardware();

	void IncreaseHardware();

	void DecreaseHardware();

	void LoadStorage();

	static std::string getStatType();

	std::string getType() const;

	void ExitMenu();

	~StorageProcessSubMenu()
	{
		if (hardwares != nullptr)
			delete[] hardwares;
	}
};

class CustomerMenu : public MenuContainer
{
	Customer* customer;
	size_t customerindex;
	int selectedIndex;
public:
	CustomerMenu(Customer* customer);

	static std::string getStatType();

	std::string getType() const;

	void AddWebshopProcess();

	void ExitMenu();

	void MenuExtraDisplay();

	void DeleteSelf();

	void ListOrders();

	void DeleteOrder();

	void RecieveOrder();

	~CustomerMenu();
};

class WebshopProcessSubMenu : public MenuContainer
{
	const static size_t maxboxrow = 15;
	const static size_t maxboxcolumn = 8;
	Customer* customer;
	int selectedIndex;
	int informationsize;
	Array<size_t> hardwaredb;
	Array<int> originalhardwaredb;
	Array<std::string**> menupoints;
	Array<std::string**> box;
	size_t boxrow;
	size_t boxcolumn;
	Hardware** hardwares;
	Hardware* selectedhardware;
	size_t hardwarecount;
	size_t hardwareitemcount;
	bool manipulated;
public:
	WebshopProcessSubMenu(Customer* customer, const std::string menuname);

	template<typename Tclass>
	void ListWebshop();

	void AddToOrder();

	void EmptyOrder(bool start);

	void FinishOrder();

	void MenuExtraDisplay();

	static std::string getStatType();

	std::string getType() const;

	void ExitMenu();

	~WebshopProcessSubMenu()
	{
		if (hardwares != nullptr)
			delete[] hardwares;
	}
};