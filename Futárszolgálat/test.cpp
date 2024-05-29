#define _CRT_SECURE_NO_WARNINGS //KI KELL MAJD SZEDNI
#include "gtest_lite.h"
#include "FileHandler.h"
#include "Menu.h"
#include "DescendantMenuItems.h"
#include "User.h"
#include "CentralStorage.h"
#include "memtrace.h"
#include <iostream>

#include "CportaDefine.h"

// A CportaDefine.h HEADERBEN HA DEFINIALVA VAN A CPORTA MAKRO AKKOR A test.cpp TESZTESETES VERZIO FUT LE, HA NINCS DEFINIALVA AKKOR A main.cpp NORMAL VERZIO FUT LE
//A NORMAL VERZIO TARTALMAZ NEM SZABVANY KONYVTAR HEADEREKET IS, conio.h, Windows.h

#ifdef CPORTA

int main()
{
	//A tesztesetek a standard_input.txt fajlbol olvassak ra a standard bemenetre a szoveget, ennek segitsegevel jarjuk be a programot, minden teszteset egy teljes menut bejar, es a vegen azt ellenorzi, hogy jo menut jart e be

	BaseCentralStorage* storage = new BaseCentralStorage(); //Megnyitjuk a Kozponti Tarolot, ami beolvassa a txt fajlokat, ennek sikeresseget, az alabbi tesztek tamasztjak ala, hisz a program ezzel a Taroloval dolgozik a teljes futas soran
	MenuContainer* menu = nullptr; // Ezzel a pointerrel fogunk vegigmenni az osszes menun
	std::ifstream in("standard_input.txt");
	std::cin.rdbuf(in.rdbuf());
	//1. Teszteset: AccountMenu bejarasa
	
	//standard_input altal kiadott parancsok:
	//    2 -> belepunk a regisztracio almenube
	//    Kilepes -> beirjuk hogy kilepjunk az almenubol
	//    2 -> ismet belepunk a regisztracio almenube
	//    enter -> tovabbmegyunk a vasarloregisztraciohoz
	//    Kilepes -> beirjuk hogy kilepjunk az almenubol
	//    2 -> ismet belepunk a regisztracio almenube
	//    enter -> tovabbmegyunk a vasarloregisztraciohoz
	//    enter -> teszteljuk, hogy nem maradhat uresen a beviteli mezo
	//    | -> teszteljuk, hogy nem kerulhet | tiltott karakter a beviteli mezobe
	//    officemaster -> teszteljuk, hogy nem kerulhet mar letrehozott felhasznalonev a beviteli mezobe
	//    220 Volt -> teszteljuk, hogy nem kerulet space a felhasznalonevbe
	//    220Volt -> beirjuk helyesen a felhasznalonevet
	//    vol tage -> teszteljuk, hogy nem kerulhet space a jelszoba
	//    voltage -> beirjuk helyesen a jelszot
	//    Johnnie Walker8 -> teszteljuk, hogy nem kerulhet szam a nevbe
	//    Johnnie Walker -> beirjuk helyesen a nevet
	//    johnniewalker @ gmail.com -> teszteljuk, hogy nem kerulhet space az email cimbe
	//    johnniewalkergmail.com -> teszteljuk, hogy muszaj @ karaktert taralmaznia az email cimnek
	//    jw@gmail.com -> beirjuk helyesen az email cimet
	//    06704ABC863 -> teszteljuk, hogy nem kerulhet betu a telefonszamba
	//    106704539863 -> teszteljuk, hogy a megadott meret szerint, az elso karakter + kene hogy legyen
	//    067045398631234 -> teszteljuk, hogy nem ervenyes a telefonszam merete
	//    06704539863 -> beirjuk helyesen a telefonszamot
	//    Pecs1234 -> teszteljuk, hogy nem kerulhet szam a varos nevebe
	//    Pecs -> beirjuk helyesen a varos nevet
	//    Ret utca 8 -> beirjuk a cimet
	//    p -> oket nyomunk ra, hogy sikeres a regisztracio
	//    2 -> belepunk a regisztracio almenube
	//    1111 -> beirunk egy helytelen pin kodot
	//    ABCD -> beirunk betuket pin kod helyett
	//    4312 -> beirjuk a helyes pin kodot, tovabbmegyunk az adminregisztraciohoz
	//    geek -> beirjuk a helyes felhasznalonevet
	//    banner -> beirjuk a helyes jelszot
	//    p -> oket nyomunk ra, hogy sikeres a regisztracio
	//    1 -> belepunk a belepes almenube
	//    c# -> helytelen felhasznalonevet irunk be
	//    c++ -> helyes felhasznalonevet irunk be
	//    hardware5432 -> helytelen jelszot irunk be
	//    ilovec++ -> helyes jelszot irunk be
	//    p -> belepunk a vasarlo menube
	//    0 -> kilepunk a vasarlo menubol
	//    1 -> belepunk a belepes almenube
	//    officemaster -> beirjuk a helyes felhasznalonevet
	//    office21 -> beirjuk a helyes jelszot
	//    p -> belepunk az admin menube
	//    0 -> kilepunk az admin menubol
	//    0 -> kilepunk a felhasznalo menubol
	TEST(AccountMenu, Traverse)
	{
		menu = new AccountMenu();
		menu->Loop();
		MenuContainer* holder = menu; // atlepunk a customermenube
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop(); //customermenu loop, de 0 at nyomunk, egybol kilepunk belole
		holder = menu; // atlepunk az accountmenube
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop(); //accountmenu loop, de 0 at nyomunk, egybol kilepunk belole
		holder = menu; // atlepunk az adminmenube
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop(); // adminmenu loop, de 0 at nyomunk, egybol kilepunk belole
		holder = menu; // atlepunk az accountmenube
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop(); //accountmenu loop, de 0 at nyomunk, egybol kilepunk belole
		EXPECT_STREQ("FelhasznaloMenu", menu->getType().c_str()) << "A FelhasznaloMenu tesztje kell, hogy legyen";
		delete menu;
	}END

	//2. Teszteset CustomerMenu bejarasa

    //standard_input altal kiadott parancsok:
	//    1 -> belepunk a belepes almenube
	//    c++ -> beirjuk a felhasznalonevet
	//    ilovec++ -> beirjuk a jelszot
	//    p -> oket nyomunk ra, hogy sikeres a bejelentkezes
	//    2 -> megnyitjuk a boltot
	//    1 -> megnyijtuk a processzor alkategoria tablazatot
	//    f -> teszteljuk, hogy nem tudunk felfele lepni, ha nincs tobb sor
	//    l -> lefele lepunk egyet
	//    l -> teszteljuk, hogy nem tudunk lefele lepni, ha nincs tobb sor
	//    1 -> kosarba helyezunk egy AMD Ryzen 7 3700
	//    1 -> kosarba helyezunk +1 et
	//    0 -> visszalepunk a boltba
	//    a -> teszteljuk, hogy uritjuk e a kosarat
	//    2 -> elosszor nem uritjuk a kosarat
	//    a -> teszteljuk, hogy uritjuk e a kosarat
	//    1 -> masodjara elfogadjuk a kosar uriteset
	//    p -> oket nyomunk ra, hogy a kosar sikeresen kiurult
	//    3 -> megnyitjuk a memoria alkategoria tablazatot
    //    1 -> 5X nyomjuk meg, kosarhoz adjuk az osszes TUF Gaming T1 memoriat
	//    1 -> megnyomjuk megegyszer, teszteljuk, hogy tobbet nem lehet mar hozzaadni, ha nincs tobb raktaron
    //    0 -> visszalepunk a boltba
	//    7 -> megnyitjuk az ssd alkategoria tablazatot
	//    1 -> hozzadunk egy Samsung 980 ssd t
	//    0 -> visszalepunk a boltba
	//    9 -> leadjuk a rendelest
    //    2 -> elosszor elutassitjuk a rendeles leadasat
    //    9 -> leadjuk a rendelest
	//    1 -> masodjara elfogadjuk a rendeles leadasat
	//    p -> oket nyomunk ra, hogy a rendelest sikeresen leadtuk
	//    9 -> teszteljuk, hogy nem tudunk rendelest leadni ha ures a kosar
	//    p -> oket nyomunk ra, hogy ures kosarnal nincs rendeles
	//    2 -> megnyitjuk a videokartya alkategoria tablazatot
	//    0 -> visszalepunk a boltba
	//    4 -> megnyitjuk az alaplap alkategoria tablazatot
	//    0 -> visszalepunk a boltba
	//    5 -> megnyitjuk a tapegyseg alkategoria tablazatot
	//    0 -> visszalepunk a boltba
	//    6 -> megnyitjuk a merevlemez alkategoria tablazatot
	//    0 -> visszalepunk a boltba
	//    8 -> megnyitjuk a gephaz alkategoria tablazatot
	//    0 -> visszalepunk a boltba
	//    0 -> kilepunk a boltbol
	//    0 -> kilepunk a vasarlo menubol
	//    1 -> belepunk a belepes almenube
	//    hardwaremaster -> beirjuk a felhasznalonevet
	//    hardware5432 -> beirjuk a jelszot
	//    p -> oket nyomunk ra, hogy sikeres a bejelentkezes
	//    3 -> toroljuk a vasarlot
	//    2 -> eloszor nem toroljuk a vasarlot
	//    3 -> toroljuk a vasarlot
	//    1 -> masodjara toroljuk a vasarlot
	//    p -> oket nyomunk, hogy a vasarlo sikeresen torolve lett
	//    1 -> belepunk a belepes almenube
	//    tesztelek -> beirjuk a felhasznalonevet
	//    teszt1234 -> beirjuk a jelszot
	//    p -> oket nyomunk ra, hogy sikeres a bejelentkezes
	//    1 -> belepunk a rendelesek listazasa almenube
	//    f -> teszteljuk, hogy felfele nem lehet menni, mert nincs tobb sor
	//    2 -> teszteljuk, hogy nem lehet atvenni, nem kiszallitott rendelest
	//    p -> oket nyomunk, hogy nem lehet nem kiszallitott rendelest atvenni
	//    1 -> toroljuk a rendelest
	//    2 -> elosszor nem toroljuk a rendelest
	//    1 -> toroljuk a rendelest
	//    1 -> masodjara elfogadjuk a rendeles torleset
	//    p -> oket nyomunk, hogy a rendeles sikeresen torlodott
	//    1 -> toroljuk a rendelest
	//    1 -> elfogadjuk a rendeles torleset
	//    p -> oket nyomunk, hogy a rendeles sikeresen torlodott
	//    2 -> atvesszuk a rendelest
	//    2 -> elosszor nem veszzuk at a rendelest
	//    2 -> atvesszuk a rendelest
	//    1 -> elfogadjuk a rendeles atvetelet
	//    p -> oket nyomunk, hogy a rendelest sikeresen atvettuk
	//    l -> lefele lepunk egyet a sorban
	//    f -> felfele lepunk egyet a sorban
	//    1 -> toroljuk a rendelest
	//    1 -> elfogadjuk a rendeles torleset
	//    p -> oket nyomunk, hogy a rendeles sikeresen torlodott
	//    l -> teszteljuk, hogy lefele nem lehet menni mert nincs tobb sor
	//    1 -> toroljuk a rendelest
	//    1 -> elfogadjuk a rendeles torleset
	//    p -> oket nyomunk, hogy a rendeles sikeresen torlodott
	//    0 -> kilepunk a rendelesek listazasabol
	//    0 -> kilepunk a vasarlomenubol
	//    0 -> kilepunk a felhasznalomenubol
	TEST(CustomerMenu, Traverse)
	{
		menu = new AccountMenu(); //belepunk egy vasarloval a customermenube
		menu->Loop();
		MenuContainer* holder = menu; // atlepunk a customermenube, teszteljuk a Online Boltot
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("VasarloMenu", menu->getType().c_str()) << "A VasarloMenu tesztje kell, hogy legyen";
		holder = menu; // atlepunk az accountmenube, mert tesztelunk masik vasarloval is, teszteljuk a vasarlo torleset
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("FelhasznaloMenu", menu->getType().c_str()) << "Vissza kell menni a FelhasznaloMenube";
		holder = menu; // atlepunk a customermenube a masik vasaloval
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("VasarloMenu", menu->getType().c_str()) << "A VasarloMenu tesztje kell, hogy legyen";
		holder = menu; // atlepunk az accountmenube, mert tesztelunk masik vasarloval is, teszteljuk a rendelesek kilistazasat
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("FelhasznaloMenu", menu->getType().c_str()) << "Vissza kell menni a FelhasznaloMenube";
		holder = menu; // atlepunk a customermenube a masik vasarloval
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("VasarloMenu", menu->getType().c_str()) << "A VasarloMenu tesztje kell, hogy legyen";
		holder = menu; // atlepunk az accountmenube
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("FelhasznaloMenu", menu->getType().c_str()) << "Vissza kell menni a FelhasznaloMenube";
		delete menu;
	}END

	//3. Teszteset AdminMenu bejarasa

	//standard_input altal kiadott parancsok:
	//    1 -> belepunk a belepes almenube
	//    admin1 -> beirjuk a felhasznalonevet
	//    admin1234 -> beirjuk a jelszot
	//    p -> oket nyomunk ra, hogy sikeres a bejelentkezes
	//    5 -> toroljuk az admint
	//    2 -> eloszor nem toroljuk az admint
	//    5 -> toroljuk az admint
	//    1 -> masodjara elfogadjuk az admint torleset
	//    p -> oket nyomunk, hogy az admin sikeresen torlodott
	//    1 -> belepunk a belepes menube
	//    officemaster -> beirjuk a felhasznalonevet
	//    office21 -> beirjuk a jelszot
	//    p -> oket nyomunk ra, hogy sikeres a bejelentkezes
	//    1 -> belepunk a vasarlok listazasahoz
	//    l -> 2X nyomjuk meg, hogy lelepjunk a programmer12 felhasznalohoz
	//    1 -> toroljuk a vasarlot
	//    2 -> eloszor nem toroljuk a vasarlot
	//    1 -> toroljuk a felhasznalot
	//    1 -> masodjara elfogadjuk a vasarlo torleset
	//    p -> oket nyomunk, hogy a vasarlo sikeresen torlodott
	//    0 -> kilepunk a vasarlok listazasabol
	//    2 -> belepunk a rendelesek listazasa almenube
	//    2 -> kiszallitjuk a rendelest
	//    2 -> eloszor nem szallitjuk ki a rendelest
	//    2 -> kiszallitjuk a rendelest
	//    1 -> masodjara elfogadjuk, kiszallitjuk a rendelest
	//    p -> oket nyomunk ra, hogy sikeres a kiszallitas
	//    1 -> toroljuk a rendelest
	//    2 -> eloszor nem toroljuk a rendelest
	//    1 -> toroljuk a rendelest
	//    1 -> masodjara elfogadjuk, toroljuk a rendelest
	//    p -> oket nyomunk rá, hogy sikeres a torles
	//    0 -> kilepunk a rendelsek listazasabol
	//    3 -> belepunk a raktar listazasa almenube
	//    3 -> belepunk a memoria almenube
	//    l -> lelepunk egyet a Corsair memoriahoz
	//    2 -> teszteljuk, hogy nem lehet 0 db hardverbol elvenni
	//    1 -> 3X nyomjuk meg, hozzaadunk 3 db Corsair memoriat a raktarhoz
	//    2 -> egyet elveszunk a Corsair memoriabol
	//    1 -> ujra hozzaadjuk a memoriat
	//    3 -> feltoltjuk a raktarat memoriabol
	//    2 -> eloszor nem toltjuk fel a raktarat memoriabol
	//    3 -> feltoltjuk a raktarat memoriabol
	//    1 -> masodjara elfogadjuk a raktar feltolteset
	//    p -> oket nyomunk ra, hogy sikeres a feltoltes
	//    0 -> kilepunk a memoria raktarbol
	//    7 -> belepunk az SSD raktarba
	//    1 -> hozzaadunk 1 Samsung 980 SSD t a raktarhoz
	//    3 -> feltoltjuk a raktarat SSD bol
	//    1 -> elfogadjuk a raktar feltolteset
	//    p -> oket nyomunk ra, hogy sikeres a feltoltes
	//    0 -> kilepunk az SSD raktarbol
	//    1 -> belepunk a processzor raktarba
	//    0 -> kilepunk a processzor raktarbol
	//    2 -> belepunk a videokartya raktarba
	//    0 -> kilepunk a videokartya raktarbol
	//    4 -> belepunk az alaplap raktarba
	//    0 -> kilepunk az alaplap raktarbol
	//    5 -> belepunk a tapegyseg raktarba
	//    0 -> kilepunk a tapegyseg raktarbol
	//    6 -> belepunk a merevlemez raktarba
	//    0 -> kilepunk a merevlemez raktarbol
	//    8 -> belepunk a gephaz raktarba
	//    0 -> kilepunk a gephaz raktarbol
	//    0 -> kilepunk a raktarbol
	//    4 -> belepunk az uj hardver hozzadasa almenube
	//    1 -> belepunk a processzor felvetelbe
	//    Kilepes -> teszteljuk, hogy kilep a processzor felvetelbol
	//    1 -> belepunk a processzor felvetelbe
	//    enter -> teszteljuk, hogy nem maradhat uresen a beviteli mezo
	//    | -> teszteljuk, hogy nem kerulhet | tiltott karakter a beviteli mezobe
	//    Intel Core i9-13900K -> beirjuk a processzor nevet
	//    24 -> beirjuk a magok szamat
	//    3 -> beirjuk a processzor orajelet
	//    Intel Socket 1700 -> beirjuk a foglalat tipusat
	//    125 -> beirjuk a processzor fogyasztasat
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    2 -> belepunk a videokartya felvetelbe
	//    AMD Radeon RX6700 -> beirjuk a videokartya nevet
	//    PCIExpress -> beirjuk a foglalat tipusat
	//    2622 -> beirjuk a chip sebesseget
	//    16000 -> beirjuk a memoria sebesseget
	//    12 -> beirjuk a memoria meretet
	//    2 -> beirjuk a ventilatorok szamat
	//    260 -> beirjuk a videokartya fogyasztasat
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    3 -> belepunk a memoria felvetelbe
	//    Kingston Fury -> beirjuk a memoria nevet
	//    16 -> beirjuk a memoria meretet
	//    2X8 -> beirjuk a kiszerelest
	//    3200 -> beirjuk a memoria sebesseget
	//    ddr4 -> beirjuk a memoria tipusat
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    4 -> belepunk az alaplap felvetelbe
	//    Gigabyte B650M -> beirjuk az alaplap nevet
	//    AMD Socket AM5 -> beirjuk a processzor foglalatot
	//    PCIExpress -> beirjuk a videokartya foglalatot
	//    ddr5 -> beirjuk a ram tipust
	//    4 -> beirjuk a ram foglalatok szamat
	//    microATX -> beirjuk az alaplap foglalatat
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    5 -> belepunk a tapegyseg felvetelbe
	//    Cooler Master V3 -> beirjuk a tapegyseg nevet
	//    nem modularis -> beirjuk a tapegyseg tipusat
	//    600 -> beirjuk a tapegyseg teljesitmenyet
	//    80 -> beirjuk a tapegyseg hatasfokat
	//    aktiv -> beirjuk a PFC tipust
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    6 -> belepunk a merevlemez felvetelbe
	//    Seagate Barracuda -> beirjuk a merevlemez nevet
	//    2000 -> beirjuk a merevlemez kapacitasat
	//    7200 -> beirjuk a merevlemez fordulatszamat
	//    3.5 -> beirjuk a merevlemez meretet
	//    SATA3 -> beirjuk a csatlakozo tipusat
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    7 -> belepunk az SSD felvetelbe
	//    Adata Legend 710 -> beirjuk az SSD nevet
	//    1000 -> beirjuk az SSD kapacitasat
	//    TLC -> beirjuk a NAND Flash tipusat
	//    M.2 -> csatlakozo tipusa
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    8 -> belepunk a gephaz felvetelbe
	//    DeepCool Matrexx 55 -> beirjuk a gephaz nevet
	//    12 -> beirjuk a gephaz tomeget
	//    ATX -> beirjuk az alaplap tamogatasat
	//    6 -> beirjuk a ventilatorok szamat
	//    2 -> beirjuk a 3.5 csatlakozok szamat
	//    5 -> beirjuk a 2.5 csatlakozok szamat
	//    p -> oket nyomunk ra, hogy sikeres a hardver hozzaadas
	//    0 -> kilepunk az uj hardver hozzadasa menubol
	//    0 -> kilepunk az adminmenubol
	//    0 -> kilepunk a felhasznalomenubol
	TEST(AdminMenu, Traverse)
	{
		menu = new AccountMenu(); //belepunk egy adminnal az adminmenube
		menu->Loop();
		MenuContainer* holder = menu; // atlepunk az adminmenube, teszteljuk az admin torleset
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("AdminMenu", menu->getType().c_str()) << "Az AdminMenu tesztje kell, hogy legyen";
		holder = menu; // atlepunk az accountmenube, mert tesztelunk masik adminnal is, teszteljuk a vasarlok listazasat, rendelesek listazasat, raktar listazasat, hardver hozzadasat
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("FelhasznaloMenu", menu->getType().c_str()) << "Vissza kell menni a FelhasznaloMenube";
		holder = menu; // atlepunk az adminmenube a masik adminnal
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("AdminMenu", menu->getType().c_str()) << "Az AdminMenu tesztje kell, hogy legyen";
		holder = menu; // atlepunk az accountmenube
		menu = menu->getNextmenu();
		delete holder;
		menu->Loop();
		EXPECT_STREQ("FelhasznaloMenu", menu->getType().c_str()) << "Vissza kell menni a FelhasznaloMenube";
		delete menu;
	}END

	//Egyeb tesztek

	//4. Teszteset Fajlba iras, olvasas nincs ilyen fajl exception elkapasa, valamint kezeles a hibakezelo classal

	TEST(FileHandler, Write to file exception)
	{
		FileHandler handler;
		CheckError error;
		try
		{
			int number = 10;
			EXPECT_THROW_THROW(handler.WriteToFile("teszt.txt", &number, 1), InvalidProcess);
		}
		catch (InvalidProcess e)
		{
			std::string excp = e.what();
			error.ErrorOutput(excp);
			std::cout << "\n";
			error.ErrorDevOutput(e.what());
			std::cout << "\n";
			error.ErrorDevOutput(excp);
			std::cout << "\n";
		}
		try
		{
			std::string* content = nullptr;
			size_t count = 0;
			EXPECT_THROW_THROW(handler.ReadFromFile("teszt.txt", &content, &count), InvalidProcess);
		}
		catch (InvalidProcess e)
		{
			error.ErrorDevOutput(e.what());
		}
	}END

		//5. Fajl letrehozast teszteljuk ugy, hogy letrehozzuk a fajlt, es utanna nem varunk exceptiont a ReadFromFile fuggvenytol

		TEST(FileHandler, Create file exception)
	{
		FileHandler handler;
		handler.CreateFileCustom("testfile.txt");
		std::string* content = nullptr;
		size_t count = 0;
		EXPECT_NO_THROW(handler.ReadFromFile("testfile.txt", &content, &count));
		delete[] content;
	}END

	//6. Teszteset a template heterogen kollekcio helycsinalo algoritmusanak tesztelese, a kollekcio 5 elemenkent ujrameretezi magat
		TEST(Array, Resize)
	{
		Array<int> numbers;
		numbers.CreateArray(5);
		int series[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		numbers.Upload(series, 10);
		EXPECT_EQ(10, numbers.getMaxSizeForTest()) << "Nem teljesul az elvart mukodes"; //Azert 10, mert minden iteracio elejen ellenoriz, es az iteracio vegen emel a mereten, vagyis az utolso iteracioban meg nem meretez ujra
		Array<int**> numberptr(true); // Tesztelunk a 2D s tomb verzioval is
		numberptr.CreateArray(5);
		int* ptrseries[10] = { new int[2], new int[2], new int[2], new int[2], new int[2], new int[2], new int[2], new int[2], new int[2], new int[2] };
		numberptr.Upload(ptrseries, 10);
		EXPECT_EQ(10, numberptr.getMaxSizeForTest()) << "Nem teljesul az elvart mukodes"; //Azert 10, mert minden iteracio elejen ellenoriz, es az iteracio vegen emel a mereten, vagyis az utolso iteracioban meg nem meretez ujra
		numberptr.DeleteItem(6); // Tesztelunk torlest is a 2D s tombbol
		EXPECT_EQ(9, numberptr.getSize()) << "Nem teljesul az elvart mukodes";
	}END

		//7. Teszteset helytelen castolas exception teszt, MenuItem, es MenuContainer getter tesztek
		TEST(MenuItem, Cast)
	{
		Admin* admin = new Admin();
		admin->SetUsername("test");
		admin->SetPassword("test1234");
		CheckError error;
		LoginItem item(AccountMenu::getStatType());
		AdminMenu menu(admin);
		try
		{
			EXPECT_THROW_THROW(item.Task(&menu), InvalidProcess);
		}
		catch (InvalidProcess e)
		{
			error.ErrorDevOutput(e.what());
		}
		EXPECT_STREQ("AdminMenu", menu.GetMenuname().c_str()) << "Nem jo a menu neve";
		EXPECT_STREQ("Belepes", item.getName().c_str());
		EXPECT_EQ(0, item.getSerial());
	}END

		//8. Teszteset OrderId kiosztas algoritmus helyessegenek ellenorzese
		TEST(OrdersPerUser, OrderId)
	{
		OrdersPerUser orderperuser("220Volt");
		orderperuser.SetCustomername("computerexpert");
		Order* order = new Order(0);
		orderperuser.AddOrder(order);
		Order* nextorder = new Order(orderperuser.GetNewId());
		orderperuser.AddOrder(nextorder);
		EXPECT_EQ(1, nextorder->GetOrderId());
	}END

		//9. Teszteset Customer getterek, es a menupontok 
		TEST(Customer, Getters)
	{
		Customer customer;
		customer.SetUsername("computerexpert");
		customer.SetPassword("comp1234");
		customer.SetName("Jack Daniels");
		customer.SetEmail("jacky@gmail.com");
		customer.SetPhonenumber("+36205439821");
		customer.SetCity("Budapest");
		customer.SetAddress("Vereb utca 78");
		EXPECT_STREQ("computerexpert", customer.GetUsername().c_str()) << "Nem jo a felhasznalonev";
		EXPECT_STREQ("comp1234", customer.GetPassword().c_str()) << "Nem jo a jelszo";
		EXPECT_STREQ("Jack Daniels", customer.GetName().c_str()) << "Nem jo a nev";
		EXPECT_STREQ("jacky@gmail.com", customer.GetEmail().c_str()) << "Nem jo az email cim";
		EXPECT_STREQ("+36205439821", customer.GetPhonenumber().c_str()) << "Nem jo a telefonszam";
		EXPECT_STREQ("Budapest", customer.GetCity().c_str()) << "Nem jo a varos";
		EXPECT_STREQ("Vereb utca 78", customer.GetAddress().c_str()) << "Nem jo a cim";
		std::string* menupoints = new std::string[User::GetInformationcount()]; // Ennek a funkcionak alapesetben a program csak az egyik agat jarja be, ezert most bejarjuk a masikat is
		User user;
		user.GetMenuPoints(nullptr, menupoints);
		delete[] menupoints;
		menupoints = new std::string[Admin::GetInformationcount()];
		Admin admin;
		admin.GetMenuPoints(nullptr, menupoints);
		delete[] menupoints;
		menupoints = new std::string[Customer::GetInformationcount()];
		customer.GetMenuPoints(nullptr, menupoints);
		delete[] menupoints;
	}END
	delete storage;
	return 0;
}

#endif 