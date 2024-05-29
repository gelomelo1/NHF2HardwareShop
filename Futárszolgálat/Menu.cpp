#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <cstdio>
#include "Menu.h"
#include "memtrace.h"
#include "DescendantMenuItems.h"
#include "MenuSetters.h"

#include <Windows.h>

class CentralStorage;


//MenuContainer ososztály fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string MenuContainer::GetMenuname() const
{
	return menuname;
}

void MenuContainer::Loop()
{
	while (!proceed)
	{
		ClearScreen();
		if (!submenu) //ha submenu hamis akkor megyunk bele a Fomenube
			MainMenu();
		else //kulonben az almenube megyunk at, es atadjuk az iranyitast az almenunek
		{
			try
			{
				items[selected]->Task(this);
			}
			catch (InvalidProcess e)
			{
				error.ErrorDevOutput(e.what());
			}
		}
	}
}

void MenuContainer::MainMenu()
{
	std::string* menupoints = new std::string[maxitemcount];
	for (size_t i = 0; i < (size_t)maxitemcount; i++)
		menupoints[i] = items[i]->Print();

	menuname = originalmenuname;

	MenuItemPrint(maxitemcount, menupoints);

	delete[] menupoints;

	std::cout << "Valassz egy opciot!";

	MenuExtraDisplay();

	selected = -1;

	while (selected == -1)
	{
		selected = MenuSelectInput();
	}

	items[selected]->ChangeToSubmenu(this);
}

void MenuContainer::SetSubmenu(const bool submenu)
{
	this->submenu = submenu;
}

 MenuContainer::~MenuContainer()
{
	 for (int i = 0; i < maxitemcount; i++)
		 delete items[i];
	 delete[] items;
}

 void MenuContainer::AddItem(MenuItem* item)
 {
	 items[itemcount] = item;
	 item->SetSerial(itemcount);
	 itemcount++;
 }

 void MenuContainer::AddSubItem(MenuItem* item)
 {
	 submenuitems[submenuitemcount] = item;
	 submenuitemcount++;
	 item->SetSerial(submenuitemcount);
 }

 void MenuContainer::MenuItemPrint(const int count, std::string* menupoints, const bool displaysubmenu) const
 {

	 if (displaysubmenu)
	 {
		 std::cout << menuname;

		 std::cout << "\n";

		 for (size_t i = 0; i < menuname.length(); i++)
			 std::cout << "=";

		 std::cout << "\n";
	 }

	 for (int i = 0; i < count; i++)
		 std::cout << menupoints[i] << "\n";
 }

#ifdef CPORTA
 void MenuContainer::Table(std::string** content, const int rows, const int columns, const int columswidth, const int startheight, const int selected) const
 {
	 int x = 0;
	 for (int i = 0; i < rows; i++)
	 {
		 for (int j = 0; j < columns; j++)
		 {
			 std::cout << content[i][j];
			 x += content[i][j].length();
			 while (x < columswidth)
			 {
				 std::cout << " ";
				 x++;
			 }
			 std::cout << "  |";
			 x = 0;
		 }
		 if (i == selected && selected > 0)
			 std::cout << "<-";
		 else
			 std::cout << "  ";
		 std::cout << "\n";
	 }
	 if (selected != -1)
		 ClearScreen();
 }
#endif //CPORTA

#ifndef CPORTA
 void MenuContainer::Table(std::string** content, const int rows, const int columns, const int columswidth, const int startheight, const int selected) const
 {
	 int modifiedcolumnswidth = columswidth;
	 if (columns * columswidth + columns * 3 > width)
		 modifiedcolumnswidth = (width - columns * 3) / columns;

	 error.MovePos(0, startheight);
	 int x = 0;
	 for (int i = 0; i < rows; i++)
	 {
		 if (i == selected && selected > 0)
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
		 else
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		 for (int j = 0; j < columns; j++)
		 {
			 std::cout << content[i][j];
			 x += content[i][j].length();
			 while (x < modifiedcolumnswidth)
			 {
				 std::cout << " ";
				 x++;
			 }
			 std::cout << "  |";
			 x = 0;
		 }
		 std::cout << "\n";
	 }
 }
#endif // !CPORTA

#ifdef CPORTA
 void MenuContainer::TableControl(std::string** content, const int maxrowindex, const int columnindex, const int columswidth, const int startheight, int& selectedrow, bool& outsidecontrol)
 {
	 char key = 0;
	 if (selectedrow == maxrowindex - 1)
		 selectedrow--;
	 while (key != '0' && !outsidecontrol)
	 {
		 Table(content, maxrowindex, columnindex, columswidth, startheight, selectedrow + 1);
		 std::cin >> key;
		 switch (key)
		 {
		 case 102: //felfele gomb
		 {
			 if (selectedrow != 0)
				 selectedrow--;
			 break;
		 }

		 case 108: //lefele gomb 
		 {
			 if (selectedrow != maxrowindex - 2)
				 selectedrow++;
			 break;
		 }
		 case '0': //nulla akkor kilepes
			 break;
		 default: // egyebkent feladat kovetkezik
		 {
			 int index = CharToInt(key, true, 1);
			 if (index != -1 && maxrowindex > 1) //Megfelelo billetnyu akkor megy tovabb
			 {
				 outsidecontrol = true;  //Feladat kovetkezik, majd kulso beavatkozasra van szukseg
				 try
				 {
					 submenuitems[index - 1]->Task(this);
				 }
				 catch (InvalidProcess e)
				 {
					 error.ErrorDevOutput(e.what());
				 }
			 }
			 break;
		 }
		 }
	 }
 }
#endif // CPORTA

#ifndef CPORTA
 void MenuContainer::TableControl(std::string** content, const int maxrowindex, const int columnindex, const int columswidth, const int startheight, int& selectedrow, bool& outsidecontrol)
 {
	 char key = 0;
	 if (selectedrow == maxrowindex - 1)
		 selectedrow--;
	 while (key != '0' && !outsidecontrol)
	 {
		 Table(content, maxrowindex, columnindex, columswidth, startheight, selectedrow + 1);
		 key = _getch();
		 switch (key)
		 {
		 case 72: //felfele gomb
		 {
			 if (selectedrow != 0)
				 selectedrow--;
			 break;
		 }

		 case 80: //lefele gomb 
		 {
			 if (selectedrow != maxrowindex - 2)
				 selectedrow++;
			 break;
		 }
		 case '0': //nulla akkor kilepes
			 break;
		 default: // egyebkent feladat kovetkezik
		 {
			 int index = CharToInt(key, true, 1);
			 if (index != -1 && maxrowindex > 1) //Megfelelo billetnyu akkor megy tovabb
			 {
				 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				 outsidecontrol = true;  //Feladat kovetkezik, majd kulso beavatkozasra van szukseg
				 try
				 {
					 submenuitems[index - 1]->Task(this);
				 }
				 catch (InvalidProcess e)
				 {
					 error.ErrorDevOutput(e.what());
				 }
			 }
			 break;
		 }
		 }
	 }
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
 }
#endif // !CPORTA


 MenuContainer* MenuContainer::getNextmenu() const
 {
	 return nextmenu;
 }

 int MenuContainer::CharToInt(const char& value, const bool submenumode, int offset) const
 {
	 bool key = false;
	 int selectedindex = 0;
	 int count = 0;
	 if (submenumode)
		 count = submenuitemcount;
	 else
		 count = itemcount;
	 if (count < 11)
	 {
		 if (((value - '0') > -1 + offset && (value - '0') < count + offset))
		 {
			 selectedindex = value - '0';
			 key = true;
		 }
	 }
	 else
	 {
	     if ((value - '0') > -1 + offset && (value - '0') < 10 + offset)
		 {
		 selectedindex = value - '0';
		 key = true;
		 }
		else if ((value - 'a') > -1 + offset && (value - 'a') < count - 10 + offset)
		 {
		selectedindex = 10 + (value - 'a');
		 key = true;
		 }
	 }
		 if (key)
			 return selectedindex;
		 return -1;
 }

#ifdef CPORTA
 int MenuContainer::MenuSelectInput() const
 {
	 char c;
	 std::cin >> c;
	 int selected = CharToInt(c);
	 return selected;
 }
#endif // CPORTA

#ifndef CPORTA
 int MenuContainer::MenuSelectInput() const
 {
	 int selected = CharToInt(_getch());
	 return selected;
 }
#endif // !CPORTA

#ifdef CPORTA
 void MenuContainer::WaitForEnter(const std::string display) const
 {
	 std::cout << display;
	 std::cout << "\nNyomj p-t a folytatashoz";
	 char c = ' ';
	 do
	 {
		 std::cin >> c;
	 } while (c != 'p');
 }
#endif // CPORTA

#ifndef CPORTA
 void MenuContainer::WaitForEnter(const std::string display) const
 {
	 std::cout << display;
	 std::cout << "\nNyomj entert a folytatashoz";
	 int selected = 0;
	 do
	 {
		 selected = _getch();
	 } while (selected != 13);
 }
#endif // !CPORTA

#ifdef CPORTA
 bool MenuContainer::Decide(const std::string display) const
 {
	 std::cout << display;
	 std::cout << "\n" << "1.Igen";
	 std::cout << "\n" << "2.Nem";
	 char c = ' ';
	 do
	 {
		 std::cin >> c;
	 } while (c != '1' && c != '2');
	 if (c == '1') //1 -es nyomott, igazat adunk vissza
		 return true;
	 return false;//2 -es nyomott, hamisat adunk vissza
 }
#endif // CPORTA

#ifndef CPORTA
 bool MenuContainer::Decide(const std::string display) const
 {
	 std::cout << display;
	 std::cout << "\n" << "1.Igen";
	 std::cout << "\n" << "2.Nem";
	 int selected = 0;
	 do
	 {
		 selected = _getch();
	 } while (selected != 49 && selected != 50);
	 if (selected == 49) //1 -es nyomott, igazat adunk vissza
		 return true;
	 return false;//2 -es nyomott, hamisat adunk vissza
 }
#endif // !CPORTA

#ifdef CPORTA
 void MenuContainer::ClearScreen() const
 {
	 for (size_t i = 0; i <= 10; i++)
		 std::cout << "\n";
 }
#endif // CPORTA

#ifndef CPORTA
 void MenuContainer::ClearScreen() const
 {
	 system("cls");
 }
#endif // !CPORTA


 template<class T>
 void MenuContainer::FreeClassArray(T** t, int& count, bool dynamicarray) const
 {
	 for (int i = 0; i < count; i++)
		 delete t[i];
	 if (dynamicarray)
		 delete[] t;
	 count = 0;
 }


 //AccountMenu Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 AccountMenu::AccountMenu() : MenuContainer(3, "FelhasznaloMenu"), setter(false)
 {
	 setter.CreateArray(1);
	 setter.Upload(new PincodeSetter(this));
	 items = new MenuItem * [maxitemcount];
	 AddItem(new ExitItem());
	 AddItem(new LoginItem(getType()));
	 AddItem(new RegisterItem(getType()));
 }

 Array<Setters**>& AccountMenu::GetSetters()
 {
	 return setter;
 }

 std::string AccountMenu::getStatType()
 {
	 return "FelhasznaloMenu";
}

 std::string AccountMenu::getType() const
 {
	 return AccountMenu::getStatType();
 }

 void AccountMenu::SetPincode(const int pincode)
 {
	 if (pincode == BaseCentralStorage::getPin() || pincode == 0)
		 this->pincode = pincode;
	 else
		 throw InvalidFormatException("Helytelen pin kod");
 }

 void AccountMenu::RegistrationProcess()
 {
	 menuname = menuname + "->Regisztracio";//Menu nevenek megvaltoztatasa
	 //Pinkod
	 std::string quitinfo = "Vissza a menube = 'Kilepes'";
	 std::string pindesciption = "Amennyiben vasarlokent szeretnel regisztralni hagyd uresen a mezot, es lepj tovabb, admin regisztracio eseten ird be a megadott pin kodot!\n";
	 pindesciption += quitinfo;
	 MenuItemPrint(1, &pindesciption); //Pin kod informacio kiiras
	 std::string pinmenupoint = "Pin:";
	 MenuItemPrint(1, &pinmenupoint, false); //Pin kiiras
	 int size = 1;

#ifdef CPORTA
	 TextInput(*this, size, &pinmenupoint, true, 2, true);  //Adat bevitel
#endif // CPORTA

#ifndef CPORTA
	 TextInput(*this, size, &pinmenupoint, 2, true);  //Adat bevitel
#endif // !CPORTA


	 ClearScreen();

	 if (!submenu)
		 return;

	 User* user;
	 if (pincode == 0)
	 {
		 Customer* customer = new Customer();
		 user = customer;
	 }
	 else
	 {
		 Admin* admin = new Admin();
		 user = admin;
	 }
	 for (size_t i = 0; i < user->GetSetters().getSize(); i++)
		 user->GetSetters()[i]->SetState(Setters::State::Registration);
	 Array<std::string>menupoints;
	 user->GetMenuPoints(&menupoints);
	 MenuItemPrint(user->getCountForFunctions(), menupoints.getArray());
	 TextInput(*user, user->getCountForFunctions(), menupoints.getArray(), false);

	 if (!submenu)
	 {
		 delete user;
		 return;
	 }
	 user->AddUser();
	 WaitForEnter("\nSikeres regisztracio!");
	 delete user;
	 SetSubmenu(false);
 }

 void AccountMenu::LoginProcess()
 {
	 menuname = menuname + "->Belepes";
	 std::string quitinfo = "Vissza a menube = 'Kilepes'";
	 MenuItemPrint(1, &quitinfo);
	 User user;
	 Array<std::string>menupoints;
	 user.GetMenuPoints(&menupoints);
	 MenuItemPrint(user.getCountForFunctions(), menupoints.getArray(), false);
	 for (size_t i = 0; i < user.GetSetters().getSize(); i++)
		 user.GetSetters()[i]->SetState(Setters::State::Login);
#ifdef CPORTA
	 TextInput(user, user.getCountForFunctions(), menupoints.getArray(), true, 1);
#endif // CPORTA

#ifndef CPORTA
	 TextInput(user, user.getCountForFunctions(), menupoints.getArray(), 1);
#endif // !CPORTA

	 if (!submenu)
		 return;
	 std::string password;
	 std::string usertype;
	 user.EqualUsers(password, usertype, user.GetUsername());
	 if (usertype == "admin")
	 {
		 Admin* admin = new Admin();
		 admin->SetUsername(user.GetUsername());
		 admin->SetPassword(user.GetPassword());
		 nextmenu = new AdminMenu(admin);
	 }
	 else if (usertype == "customer")
	 {
		 Customer* customer = new Customer();
		 std::string* values = new std::string[Customer::GetInformationcount()];
		 customer->SetUsername(user.GetUsername());
		 Customer* basecustomer = customer->GetCentralStorage()->SearchForCustomer(customer);
		 basecustomer->FormatInfo(values);
		 for (size_t i = 0; i < customer->GetSetters().getSize(); i++)
		 {
			 customer->GetSetters()[i]->SetState(Setters::State::None);
			 customer->GetSetters()[i]->SetInput(values[i]);
			 customer->GetSetters()[i]->Set();
		 }
		 delete[] values;
		 nextmenu = new CustomerMenu(customer);
	 }
	 WaitForEnter("\nSikeres belepes!");
	 proceed = true;
 }

 void AccountMenu::ExitMenu()
 {
	 nextmenu = nullptr;
	 proceed = true;
 }


 //AdminMenu Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 AdminMenu::AdminMenu(Admin* admin) : MenuContainer(6, "AdminMenu"), admin(admin), userindex(nullptr), orderindex(nullptr), selectedIndex(0)
 {
	 items = new MenuItem * [maxitemcount];
	 AddItem(new ExitItem());
	 AddItem(new AccountList());
	 AddItem(new OrderListAdmin());
	 AddItem(new StorageList());
	 AddItem(new NewHardware());
	 AddItem(new AdminSelfDelete());
 }

 AdminMenu::~AdminMenu()
 
 {
	 if (userindex != nullptr)
		 delete[] userindex;
	 if (orderindex != nullptr)
		 delete[] orderindex;
	 delete admin;
 }

 std::string AdminMenu::getStatType()
 {
	 return "AdminMenu";
}

 std::string AdminMenu::getType() const
 {
	 return AdminMenu::getStatType();
 }

 void AdminMenu::ListAccounts()
 {
	 menuname = menuname + "->Vasarlok";
	 selectedIndex = 0;
	 submenuitems = new MenuItem*[1];
	 AddSubItem(new CustomerDelete());
	 Array<std::string> control;
	 control.CreateArray(submenuitemcount + 1);
	 control.Upload(items[0]->Print());
	 for (size_t i = 0; i < (size_t)submenuitemcount; i++)
		 control.Upload(submenuitems[i]->Print());
	 bool refresh = false;


	 do
	 {
		 refresh = false;
		 ClearScreen();
		 MenuItemPrint(submenuitemcount + 1, control.getArray());
		 Array<std::string**> menupoints(true);
		 menupoints.CreateArray(admin->GetCustomerArray().getSize() + 1);
		 std::string* labels = new std::string[Customer::GetInformationcount()];
		 Customer::GetStatMenuPoints(labels);
		 menupoints.Upload(labels);
		 for (size_t i = 0; i < admin->GetCustomerArray().getSize(); i++)
		 {
			 std::string* infos = new std::string[Customer::GetInformationcount()];
			 admin->GetCustomerArray()[i]->FormatInfo(infos);
			 menupoints.Upload(infos);
		 }
		 TableControl(menupoints.getArray(), admin->GetCustomerArray().getSize() + 1, Customer::GetInformationcount(), 22, submenuitemcount + 3, selectedIndex, refresh);
	 } while (refresh);
	 FreeClassArray(submenuitems, submenuitemcount, true);
	 SetSubmenu(false);
 }

 void AdminMenu::DeleteCustomer()
 {
	 if (Decide("Biztos, hogy torolni akarod ezt a vasarlot?"))
	 {
		 admin->DeleteCustomer(selectedIndex);
		 WaitForEnter("\nA vasarlo sikeresen torolve");
	 }
 }

 void AdminMenu::ListOrders()
 {
	 menuname = menuname + "->Rendelesek";
	 selectedIndex = 0;
	 submenuitems = new MenuItem * [2];
	 AddSubItem(new OrderDeleteAdmin());
	 AddSubItem(new OrderShip());
	 Array<std::string> control;
	 control.CreateArray(submenuitemcount + 1);
	 control.Upload(items[0]->Print());
	 for (size_t i = 0; i < (size_t)submenuitemcount; i++)
		 control.Upload(submenuitems[i]->Print());
	 bool refresh = false;


	 do
	 {
		 if (userindex != nullptr)
		 {
			 delete[] userindex;
			 delete[] orderindex;
			 orderindex = nullptr;
			 userindex = nullptr;
		 }
		 refresh = false;
		 ClearScreen();
		 MenuItemPrint(submenuitemcount + 1, control.getArray());
		 size_t ordercount = admin->GetCentralStorage()->GetCountOfOrdersInAState(Order::State::RecievedOrder);
		 userindex = new size_t[ordercount];
		 orderindex = new size_t[ordercount];
		 Array<std::string**> menupoints(true);
		 menupoints.CreateArray(ordercount + 1);
		 std::string* labels = new std::string[Order::GetInformationcount()];
		 Order::GetStatMenuPoints(labels);
		 menupoints.Upload(labels);
		 size_t ordersindex = 0;
		 for (size_t i = 0; i < admin->GetCentralStorage()->GetOrdersPerUser().getSize(); i++)
		 {
			 for (size_t j = 0; j < admin->GetCentralStorage()->GetOrdersPerUser()[i]->GetOrders().getSize(); j++)
			 {
				 if (admin->GetCentralStorage()->GetOrdersPerUser()[i]->GetOrders()[j]->GetState() == Order::State::RecievedOrder)
				 {
					 userindex[ordersindex] = i;
					 orderindex[ordersindex] = j;
					 ordersindex++;
					 std::string* infos = new std::string[Order::GetInformationcount()];
					 admin->GetCentralStorage()->GetOrdersPerUser()[i]->FormatInfo(admin->GetCentralStorage()->GetOrdersPerUser()[i]->GetOrders()[j], infos);
					 menupoints.Upload(infos);
				 }
			 }
		 }
		 TableControl(menupoints.getArray(), ordercount + 1, Order::GetInformationcount(), 74, submenuitemcount + 3, selectedIndex, refresh);
	 } while (refresh);
	 FreeClassArray(submenuitems, submenuitemcount, true);
	 SetSubmenu(false);
 }

 void AdminMenu::DeleteOrder()
 {
	 if (Decide("Biztos, hogy torolni akarod ezt a rendelest?"))
	 {
		 admin->DeleteOrder(userindex[selectedIndex], orderindex[selectedIndex]);
		 WaitForEnter("\nA rendeles sikeresen torolve, a tetelek visszakerultek a raktarba");
	 }
 }

 void AdminMenu::ShipOrder()
 {
	 if (Decide("Biztos, hogy kiszallitod ezt a rendelest?"))
	 {
		 admin->ShipOrder(userindex[selectedIndex], orderindex[selectedIndex]);
		 WaitForEnter("\nA rendeles sikeresen kiszallitva, atvetelre var");
	 }
 }

 void AdminMenu::ExitMenu()
 {
	 nextmenu = new AccountMenu();
	 proceed = true;
 }

#ifdef CPORTA
 void AdminMenu::MenuExtraDisplay()
 {
	 for (int i = 0; i < -(itemcount + 3) + height - 5; i++)
		 std::cout << "\n";
	 for (size_t i = 0; i < width; i++)
		 std::cout << "=";
	 std::cout << "\n";
	 std::cout << "Admin: " << admin->GetUsername() << "          " << "Vasarlok darabszama: " << admin->GetCustomerArray().getSize() << "          " << "Beerkezett rendelesek: " << admin->GetCentralStorage()->GetCountOfOrdersInAState(Order::State::RecievedOrder) << "          " << "Hardverek lista: " << admin->GetCentralStorage()->GetHardwareStorage().GetTotalHardwareCount();
	 std::cout << "\n";
 }
#endif // CPORTA

#ifndef CPORTA
 void AdminMenu::MenuExtraDisplay()
 {
	 int x = 0;
	 int y = 0;
	 error.MovePos(0, height - 5, true);
	 for (size_t i = 0; i < width; i++)
		 std::cout << "=";
	 std::cout << "\n";
	 std::cout << "Admin: " << admin->GetUsername();
	 error.GetCurPos(x, y);
	 error.MovePos(x + 5, y);
	 std::cout << "Vasarlok darabszama: " << admin->GetCustomerArray().getSize();
	 error.GetCurPos(x, y);
	 error.MovePos(x + 5, y);
	 std::cout << "Beerkezett rendelesek: " << admin->GetCentralStorage()->GetCountOfOrdersInAState(Order::State::RecievedOrder);
	 error.GetCurPos(x, y);
	 error.MovePos(x + 5, y);
	 std::cout << "Hardverek lista: " << admin->GetCentralStorage()->GetHardwareStorage().GetTotalHardwareCount();
	 error.MovePos(0, height - 5, true);
 }
#endif // !CPORTA


 void AdminMenu::DeleteSelf()
 {
	 menuname = menuname + "->Felhasznalo torles";
	 MenuItemPrint(0, nullptr);
	 if (Decide("Biztos, hogy torolni akarod a felhasznalod?")) //Biztos e a dontes
	 {
		 admin->DeleteSelf(); //Admin torli magat a Kozponti Tarolobol
		 WaitForEnter("\nA felhasznalod sikeresen torolve"); //Enterre var
		 items[0]->Task(this); //Meghivjuk az ExitItem class Taskjat ami kileptet az AdminMenubol es felszabaditja az Admin pointert
	 }
	 else
		 SetSubmenu(false); //Ha nem akarunk torolni akkor kilepunk az almenubol
 }

 void AdminMenu::AddHardwareProcess()
 {
	 HardwareProcessSubMenu submenu(admin, menuname + "->Uj hardver");
	 submenu.Loop();
	 SetSubmenu(false);
 }

 void AdminMenu::AddStorageProcess()
 {
	 StorageProcessSubMenu submenu(admin, menuname + "->Raktar");
	 submenu.Loop();
	 SetSubmenu(false);
 }


 //HardwareProcessSubMenu leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 HardwareProcessSubMenu::HardwareProcessSubMenu(Admin* admin, const std::string menuname) : MenuContainer(9, menuname), admin(admin)
 {
	 items = new MenuItem * [maxitemcount];
	 AddItem(new ExitItem());
	 AddItem(new NewCPU());
	 AddItem(new NewGPU());
	 AddItem(new NewMemory());
	 AddItem(new NewMotherboard());
	 AddItem(new NewPowerSupply());
	 AddItem(new NewHDD());
	 AddItem(new NewSSD());
	 AddItem(new NewComputerCase());
 }


 std::string HardwareProcessSubMenu::getStatType()
 {
	 return "AdminMenu->Uj hardver";
 }

 std::string HardwareProcessSubMenu::getType() const
 {
	 return getStatType();
 }

 void HardwareProcessSubMenu::ExitMenu()
 {
	 proceed = true;
 }


 //StorageProcessSubMenu leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 StorageProcessSubMenu::StorageProcessSubMenu(Admin* admin, const std::string menuname) : MenuContainer(9, menuname), admin(admin), selectedIndex(0), informationsize(0), menupoints(true), hardwares(nullptr), hardwarecount(0), manipulated(true)
 {
	 items = new MenuItem * [maxitemcount];
	 AddItem(new ExitItem());
	 AddItem(new CPUList());
	 AddItem(new GPUList());
	 AddItem(new MemoryList());
	 AddItem(new MotherboardList());
	 AddItem(new PowerSupplyList());
	 AddItem(new HDDList());
	 AddItem(new SSDList());
	 AddItem(new ComputerCaseList());
 }

 std::string StorageProcessSubMenu::getStatType()
 {
	 return "AdminMenu->Raktar";
}

 std::string StorageProcessSubMenu::getType() const
 {
	 return getStatType();
 }

 void StorageProcessSubMenu::ExitMenu()
 {
	 proceed = true;
 }

 void StorageProcessSubMenu::IncreaseHardware()
 {
	 hardwaredb[selectedIndex]++;
	 menupoints[selectedIndex + 1][informationsize - 1] = std::to_string(originalhardwaredb[selectedIndex]) + " + (" + std::to_string(hardwaredb[selectedIndex] -  originalhardwaredb[selectedIndex]) + ")";
 }

 void StorageProcessSubMenu::DecreaseHardware()
 {
	 if (hardwaredb[selectedIndex] > 0)
	 {
		 hardwaredb[selectedIndex]--;
		 menupoints[selectedIndex + 1][informationsize - 1] = std::to_string(originalhardwaredb[selectedIndex]) + " + (" + std::to_string(hardwaredb[selectedIndex] - originalhardwaredb[selectedIndex]) + ")";
	 }
 }

 void StorageProcessSubMenu::LoadStorage()
 {
	 if (Decide("Biztos, hogy vegre akarod hajtani a valtoztatasokat?"))
	 {
		 admin->LoadStorage(hardwares, hardwarecount, hardwaredb.getArray());
		 manipulated = true;
		 WaitForEnter("\nA raktar sikeresen rendezve");
	 }
 }



 template void StorageProcessSubMenu::ListHardware<CPU>();
 template void StorageProcessSubMenu::ListHardware<GPU>();
 template void StorageProcessSubMenu::ListHardware<Memory>();
 template void StorageProcessSubMenu::ListHardware<Motherboard>();
 template void StorageProcessSubMenu::ListHardware<PowerSupply>();
 template void StorageProcessSubMenu::ListHardware<HDD>();
 template void StorageProcessSubMenu::ListHardware<SSD>();
 template void StorageProcessSubMenu::ListHardware<ComputerCase>();
 template<typename Tclass>
 void StorageProcessSubMenu::ListHardware()
 {
	 if (hardwares != nullptr)
	 {
		 delete[] hardwares;
		 hardwares = nullptr;
	 }
	 manipulated = true;
	 selectedIndex = 0;
	 menuname = menuname + "->" + Tclass::getStatType();
	 submenuitems = new MenuItem * [3];
	 AddSubItem(new HardwareIncrease());
	 AddSubItem(new HardwareDecrease());
	 AddSubItem(new StorageLoad());
	 Array<std::string> control;
	 control.CreateArray(submenuitemcount + 1);
	 control.Upload(items[0]->Print());
	 for (size_t i = 0; i < (size_t)submenuitemcount; i++)
		 control.Upload(submenuitems[i]->Print());
	 bool refresh = false;

	 informationsize = Hardware::GetBaseinformationcount() + Tclass::GetInformationcount();
	 hardwarecount = Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage())).getSize();
	 hardwares = new Hardware*[hardwarecount];
	 for (size_t i = 0; i < hardwarecount; i++)
		 hardwares[i] = Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage()))[i];
	 do
	 {
		 if (manipulated)
		 {
			 hardwaredb.Clear();
			 originalhardwaredb.Clear();
			 menupoints.Clear();
			 hardwaredb.CreateArray(hardwarecount);
			 for (size_t i = 0; i < hardwarecount; i++)
				 hardwaredb.Upload(Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage()))[i]->GetDb());

			 originalhardwaredb.CreateArray(hardwarecount);
			 for (size_t i = 0; i < hardwarecount; i++)
				 originalhardwaredb.Upload(Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage()))[i]->GetDb());
			 menupoints.CreateArray(hardwarecount + 1);
			 std::string* labels = new std::string[informationsize];
			 Tclass::GetStatMenuPoints(labels);
			 labels[informationsize - 2] = "Id:";
			 labels[informationsize - 1] = "Db:";
			 menupoints.Upload(labels);
			 for (size_t i = 0; i < hardwarecount; i++)
			 {
				 std::string* infos = new std::string[informationsize];
				 Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage()))[i]->SetState(Hardware::State::Print);
				 Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage()))[i]->FormatInfo(infos);
				 Tclass::GetOwnArray(&(admin->GetCentralStorage()->GetHardwareStorage()))[i]->SetState(Hardware::State::Load);
				 menupoints.Upload(infos);
			 }
			 manipulated = false;
		 }


		 refresh = false;
		 ClearScreen();
		 MenuItemPrint(submenuitemcount + 1, control.getArray());
		 TableControl(menupoints.getArray(), hardwarecount + 1, informationsize, 22, submenuitemcount + 3, selectedIndex, refresh);
	 } while (refresh);
	 FreeClassArray(submenuitems, submenuitemcount, true);
	 hardwaredb.Clear();
	 originalhardwaredb.Clear();
	 menupoints.Clear();
	 SetSubmenu(false);
 }

 //CustomerMenu leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 CustomerMenu::CustomerMenu(Customer* customer) : MenuContainer(4, "VasarloMenu"), customer(customer), customerindex(0), selectedIndex(0)
 {
	 items = new MenuItem * [maxitemcount];
	 AddItem(new ExitItem());
	 AddItem(new OrderListCustomer());
	 AddItem(new WebshopOpen());
	 AddItem(new CustomerSelfDelete());
 }

 std::string CustomerMenu::getStatType()
 {
	 return "VasarloMenu";
}

 std::string CustomerMenu::getType() const
 {
	 return getStatType();
	}

 void CustomerMenu::ExitMenu()
 {
	 nextmenu = new AccountMenu();
	 proceed = true;
	}

 CustomerMenu::~CustomerMenu()
 {
	 delete customer;
 }

#ifdef CPORTA
 void CustomerMenu::MenuExtraDisplay()
 {
	 for (int i = 0; i < -(itemcount + 3) + height - 5; i++)
		 std::cout << "\n";
	 for (size_t i = 0; i < width; i++)
		 std::cout << "=";
	 std::cout << "\n";
	 size_t index = 0;
	 std::cout << "Vasarlo: " << customer->GetUsername() << "          " << "Osszes rendeles: " << customer->GetCentralStorage()->GetCountOfOrdersForACustomer(customer, index);
	 std::cout << "\n";
 }
#endif // CPORTA

#ifndef CPORTA
 void CustomerMenu::MenuExtraDisplay()
 {
	 int x = 0;
	 int y = 0;
	 error.MovePos(0, height - 5, true);
	 for (size_t i = 0; i < width; i++)
		 std::cout << "=";
	 std::cout << "\n";
	 std::cout << "Vasarlo: " << customer->GetUsername();
	 error.GetCurPos(x, y);
	 error.MovePos(x + 5, y);
	 size_t index = 0;
	 std::cout << "Osszes rendeles: " << customer->GetCentralStorage()->GetCountOfOrdersForACustomer(customer, index);
	 error.MovePos(0, height - 5, true);
 }
#endif // !CPORTA


 void CustomerMenu::DeleteSelf()
 {
	 menuname = menuname + "->Felhasznalo torles";
	 MenuItemPrint(0, nullptr);
	 if (Decide("Biztos, hogy torolni akarod a felhasznalod?")) //Biztos e a dontes
	 {
		 customer->DeleteSelf(); //Customer torli magat a Kozponti Tarolobol
		 WaitForEnter("\nA felhasznalod sikeresen torolve"); //Enterre var
		 items[0]->Task(this); //Meghivjuk az ExitItem class Taskjat ami kileptet a CustomerMenubol es felszabaditja a Customer pointert
	 }
	 else
		 SetSubmenu(false); //Ha nem akarunk torolni akkor kilepunk az almenubol
 }

 void CustomerMenu::ListOrders()
 {
	 menuname = menuname + "->Rendelesek";
	 selectedIndex = 0;
	 submenuitems = new MenuItem * [2];
	 AddSubItem(new OrderDeleteCustomer());
	 AddSubItem(new OrderRecieve());
	 Array<std::string> control;
	 control.CreateArray(submenuitemcount + 1);
	 control.Upload(items[0]->Print());
	 for (size_t i = 0; i < (size_t)submenuitemcount; i++)
		 control.Upload(submenuitems[i]->Print());
	 bool refresh = false;


	 do
	 {
		 refresh = false;
		 ClearScreen();
		 MenuItemPrint(submenuitemcount + 1, control.getArray());
		 size_t ordercount = customer->GetCentralStorage()->GetCountOfOrdersForACustomer(customer, customerindex);
		 Array<std::string**> menupoints(true);
		 menupoints.CreateArray(ordercount + 1);
		 std::string* labels = new std::string[Order::GetInformationcount()];
		 Order::GetStatMenuPoints(labels);
		 menupoints.Upload(labels);
			 for (size_t j = 0; j < ordercount; j++)
			 {
					 std::string* infos = new std::string[Order::GetInformationcount()];
					 customer->GetCentralStorage()->GetOrdersPerUser()[customerindex]->FormatInfo(customer->GetCentralStorage()->GetOrdersPerUser()[customerindex]->GetOrders()[j], infos);
					 menupoints.Upload(infos);
			 }
		 TableControl(menupoints.getArray(), ordercount + 1, Order::GetInformationcount(), 74, submenuitemcount + 3, selectedIndex, refresh);
	 } while (refresh);
	 FreeClassArray(submenuitems, submenuitemcount, true);
	 SetSubmenu(false);
 }

 void CustomerMenu::DeleteOrder()
 {
	 if (Decide("Biztos, hogy torolni akarod ezt a rendelest?"))
	 {
		 size_t selectedindex = selectedIndex;
		 customer->DeleteOrder(customerindex, selectedindex);
		 WaitForEnter("\nA rendeles sikeresen torolve");
	 }
 }

 void CustomerMenu::RecieveOrder()
 {
	 Order::State state = customer->GetCentralStorage()->GetOrdersPerUser()[customerindex]->GetOrders()[selectedIndex]->GetState();
	 if (state == Order::State::Shipped)
	 {
		 if (Decide("Biztos, hogy atakaord venni a rendelest?"))
		 {
			 size_t selectedindex = selectedIndex;
			 customer->RecieveOrder(customerindex, selectedindex);
			 WaitForEnter("\nA rendeles sikeresen atveve");
		 }
	 }
	 else
		 WaitForEnter("\nNem lehet mar megerkezett, vagy aktiv rendelest atvenni");
 }

 void CustomerMenu::AddWebshopProcess()
 {
	 WebshopProcessSubMenu submenu(customer, menuname + "->Online Bolt");
	 submenu.Loop();
	 SetSubmenu(false);
 }


 //WebshopProcessSubMenu leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

 WebshopProcessSubMenu::WebshopProcessSubMenu(Customer* customer, const std::string menuname) : MenuContainer(11, menuname), customer(customer), selectedIndex(0), informationsize(0), menupoints(true), box(true), boxrow(0), boxcolumn(0), hardwares(nullptr), selectedhardware(nullptr), hardwarecount(0), hardwareitemcount(0), manipulated(false)
 {
	 items = new MenuItem * [maxitemcount];
	 AddItem(new ExitItem());
	 AddItem(new WebshopCPU());
	 AddItem(new WebshopGPU());
	 AddItem(new WebshopMemory());
	 AddItem(new WebshopMotherboard());
	 AddItem(new WebshopPowerSupply());
	 AddItem(new WebshopHDD());
	 AddItem(new WebshopSSD());
	 AddItem(new WebshopComputerCase());
	 AddItem(new OrderFinish());
	 AddItem(new OrderEmpty());
	 EmptyOrder(true);
 }

 std::string WebshopProcessSubMenu::getStatType()
 {
	 return "VasarloMenu->Webshop";
}

 std::string WebshopProcessSubMenu::getType() const
 {
	 return getStatType();
 }

 void WebshopProcessSubMenu::ExitMenu()
 {
	 proceed = true;
 }

#ifdef CPORTA
 void WebshopProcessSubMenu::MenuExtraDisplay()
 {
	 for (int i = 0; i < -(itemcount + 3) + height - 17; i++)
		 std::cout << "\n";
	 for (size_t i = 0; i < width; i++)
		 std::cout << "=";
	 std::cout << "\n";
	 std::cout << "Kosar tartalma:";
	 std::cout << "\n";
	 Table(box.getArray(), 15, 8, 26, height + 17, -1);
 }
#endif // CPORTA

#ifndef CPORTA
 void WebshopProcessSubMenu::MenuExtraDisplay()
 {
	 error.MovePos(0, height - 20, true);
	 for (size_t i = 0; i < width; i++)
		 std::cout << "=";
	 std::cout << "\n";
	 std::cout << "Kosar tartalma:";
	 Table(box.getArray(), 15, 8, 26, height - 17, -1);
 }
#endif // !CPORTA


 template void WebshopProcessSubMenu::ListWebshop<CPU>();
 template void WebshopProcessSubMenu::ListWebshop<GPU>();
 template void WebshopProcessSubMenu::ListWebshop<Memory>();
 template void WebshopProcessSubMenu::ListWebshop<Motherboard>();
 template void WebshopProcessSubMenu::ListWebshop<PowerSupply>();
 template void WebshopProcessSubMenu::ListWebshop<HDD>();
 template void WebshopProcessSubMenu::ListWebshop<SSD>();
 template void WebshopProcessSubMenu::ListWebshop<ComputerCase>();
 template<typename Tclass>
 void WebshopProcessSubMenu::ListWebshop()
 {
	 selectedIndex = 0;
	 manipulated = false;
	 menuname = menuname + "->" + Tclass::getStatType();
	 submenuitems = new MenuItem * [1];
	 AddSubItem(new AddHardwareToOrder());
	 Array<std::string> control;
	 control.CreateArray(submenuitemcount + 1);
	 control.Upload(items[0]->Print());
	 for (size_t i = 0; i < (size_t)submenuitemcount; i++)
		 control.Upload(submenuitems[i]->Print());
	 bool refresh = false;

	 informationsize = Hardware::GetBaseinformationcount() + Tclass::GetInformationcount();
	 size_t hardwareitemcount = Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage())).getSize();
	 menupoints.Clear();

	 originalhardwaredb.CreateArray(hardwareitemcount);
	 for (size_t i = 0; i < hardwareitemcount; i++)
		 originalhardwaredb.Upload(Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage()))[i]->GetDb());
	 menupoints.CreateArray(hardwareitemcount + 1);
	 std::string* labels = new std::string[informationsize];
	 Tclass::GetStatMenuPoints(labels);
	 labels[informationsize - 2] = "Id:";
	 labels[informationsize - 1] = "Db:";
	 menupoints.Upload(labels);
	 for (size_t i = 0; i < hardwareitemcount; i++)
	 {
		 std::string* infos = new std::string[informationsize];
		 Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage()))[i]->SetState(Hardware::State::Print);
		 Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage()))[i]->FormatInfo(infos);
		 Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage()))[i]->SetState(Hardware::State::Load);
		 menupoints.Upload(infos);
	 }

	 do
	 {
		 if (manipulated)
		 {
			 selectedhardware = Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage()))[selectedIndex];
			 AddToOrder();
		 }
		 for (size_t i = 0; i < hardwarecount; i++)
		 {
			 for (size_t j = 0; j < hardwareitemcount; j++)
			 {
				 if (*(hardwares[i]) == *(Tclass::GetOwnArray(&(customer->GetCentralStorage()->GetHardwareStorage()))[j]))
						 menupoints[j + 1][informationsize - 1] = std::to_string(originalhardwaredb[j]) + " - (" + std::to_string(hardwaredb[i]) + ")";
			 }
		 }
		 manipulated = true;
		 refresh = false;
		 ClearScreen();
		 MenuItemPrint(submenuitemcount + 1, control.getArray());
		 TableControl(menupoints.getArray(), hardwareitemcount + 1, informationsize, 22, submenuitemcount + 3, selectedIndex, refresh);
	 } while (refresh);
	 FreeClassArray(submenuitems, submenuitemcount, true);
	 originalhardwaredb.Clear();
	 menupoints.Clear();
	 SetSubmenu(false);
 }

 void WebshopProcessSubMenu::AddToOrder()
 {
	 bool containhardware = false;
	 if (originalhardwaredb[selectedIndex] > 0)
	 {
		 for (size_t i = 0; i < hardwarecount; i++)
		 {
			 if (*(hardwares[i]) == *(selectedhardware))
			 {
				 if (originalhardwaredb[selectedIndex] - (int)hardwaredb[i] - 1 >= 0)
				 {
					 hardwaredb[i]++;
					 for (size_t s = 0; s < maxboxrow; s++)
					 {
						 for (size_t j = 0; j < maxboxcolumn; j++)
						 {
							 size_t found = box.getArray()[s][j].find(hardwares[i]->GetName());
							 if (found != std::string::npos)
								 box.getArray()[s][j] = std::to_string(hardwaredb[i]) + " X " + hardwares[i]->GetName();
						 }
					 }
				 }
				 containhardware = true;
				 break;
			 }
		 }
		 if (!containhardware && (boxcolumn + 1) * (boxrow + 1) < (maxboxcolumn * maxboxrow))
		 {
			 hardwares[hardwarecount] = selectedhardware;
			 hardwaredb[hardwarecount]++;
			 box.getArray()[boxrow][boxcolumn] = std::to_string(hardwaredb[hardwarecount]) + " X " + hardwares[hardwarecount]->GetName();
			 if (boxcolumn != 7)
				 boxcolumn++;
			 else
			 {
				 boxcolumn = 0;
				 boxrow++;
			 }
			 hardwarecount++;
		 }
	 }
 }

 void WebshopProcessSubMenu::EmptyOrder(bool start)
 {
	 if (!start)
	 {
		 if (Decide("Biztos, hogy torolni akarod a kosarad?"))
		 {
			 if (hardwares != nullptr)
			 {
				 delete[] hardwares;
				 hardwares = nullptr;
			 }
			 box.Clear();
			 box.CreateArray(maxboxrow);
			 for (size_t i = 0; i < maxboxrow; i++)
				 box.Upload(new std::string[maxboxcolumn]);
			 hardwarecount = customer->GetCentralStorage()->GetHardwareStorage().GetTotalHardwareCount();
			 hardwares = new Hardware * [hardwarecount];
			 hardwaredb.Clear();
			 hardwaredb.CreateArray(hardwarecount);
			 for (size_t i = 0; i < hardwarecount; i++)
				 hardwaredb.Upload(0);
			 boxrow = 0;
			 boxcolumn = 0;
			 hardwarecount = 0;
			 WaitForEnter("\nA kosar sikeresen torolve");
		 }
	 }
	 else
	 {
		 if (hardwares != nullptr)
		 {
			 delete[] hardwares;
			 hardwares = nullptr;
		 }
		 box.Clear();
		 box.CreateArray(maxboxrow);
		 for (size_t i = 0; i < maxboxrow; i++)
			 box.Upload(new std::string[maxboxcolumn]);
		 hardwarecount = customer->GetCentralStorage()->GetHardwareStorage().GetTotalHardwareCount();
		 hardwares = new Hardware * [hardwarecount];
		 hardwaredb.Clear();
		 hardwaredb.CreateArray(hardwarecount);
		 for (size_t i = 0; i < hardwarecount; i++)
			 hardwaredb.Upload(0);
		 boxrow = 0;
		 boxcolumn = 0;
		 hardwarecount = 0;
	 }
	 SetSubmenu(false);
 }

 void WebshopProcessSubMenu::FinishOrder()
 {
	 if (hardwarecount > 0)
	 {
		 if (Decide("Biztos, hogy le akarod adni a rendelest?"))
		 {
			 customer->FinishOrder(hardwares, hardwarecount, hardwaredb.getArray());
			 WaitForEnter("\nA rendeles sikeresen leadva");
			 EmptyOrder(true);
		 }
	 }
	 else
		 WaitForEnter("\nUres a kosar");
	 SetSubmenu(false);
 }

