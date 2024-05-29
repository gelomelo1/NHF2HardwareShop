#define _CRT_SECURE_NO_WARNINGS
#include "CportaDefine.h"
#include "FileHandler.h"
#include "Menu.h"
#include "User.h"
#include "CentralStorage.h"
#include "memtrace.h"
// A CportaDefine.h HEADERBEN HA DEFINIALVA VAN A CPORTA MAKRO AKKOR A test.cpp TESZTESETES VERZIO FUT LE, HA NINCS DEFINIALVA AKKOR A main.cpp NORMAL VERZIO FUT LE
//A NORMAL VERZIO TARTALMAZ NEM SZABVANY KONYVTAR HEADEREKET IS, conio.h, Windows.h

#ifndef CPORTA
#include <Windows.h>
int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	BaseCentralStorage* storage = new BaseCentralStorage(); //Kozponti Tarolo letrehozasa
	MenuContainer* menu = new AccountMenu(); //Letrehozzuk az AccountMenut
	menu->Loop(); //Belepunk a Loopba
	while (menu->getNextmenu() != nullptr) //Ha kilepve a Loopbol nullptr a kovetkezo menu, akkor nincs kovetkezo menu, vege a program futasanak
	{
		MenuContainer* holder = menu; 
		menu = menu->getNextmenu();
		delete holder; //toroljuk a regi menut
		menu->ClearScreen();
		menu->Loop(); 
	}
	delete menu; //toroljuk a menut
	delete storage; //toroljuk a Kozponti Tarolot
	return 0;
}
#endif