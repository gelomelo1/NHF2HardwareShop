#include <cstdio>
#include "memtrace.h"
#include "GeneralFunctions.h"


//CheckError osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CPORTA
int CheckError::X = 0;
int CheckError::Y = 0;
int CheckError::errorlenght = 0;
bool CheckError::cleariferror = false;


bool CheckError::GetClearIFerror() const
{
	return cleariferror;
}

void CheckError::SetClearIfError(const bool cleariferror) const
{
	this->cleariferror = cleariferror;
}

void CheckError::ErrorOutput(const std::string error) const
{
	std::cout << error;
	cleariferror = true;
}

void CheckError::ErrorOutput(const char* error) const
{
	std::cout << error;
	cleariferror = true;
}

void CheckError::ErrorDevOutput(const std::string error) const
{
	std::cout << error;
	std::cout << "          to procceed, write 'ok'";
	cleariferror = true;
	std::string decision;
	do
	{
		std::cin >> decision;
	} while (decision != "ok");
}

void CheckError::ErrorDevOutput(const char* error) const
{
	std::cout << error;
	std::cout << "          to procceed, write 'ok'";
	cleariferror = true;
	std::string decision;
	do
	{
		std::cin >> decision;
	} while (decision != "ok");
}
#endif // CPORTA

#ifndef CPORTA
#include<Windows.h>
#include<conio.h>
int CheckError::X = 0;
int CheckError::Y = 0;
int CheckError::errorlenght = 0;
bool CheckError::cleariferror = false;

void CheckError::MovePos(const int x, const int y, const bool temporary) const
{
	GetCurPos(X, Y);

	COORD c;
	c.X = x;
	c.Y = y;


	if (!temporary)
	{
		X = x;
		Y = y;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void CheckError::MovePosBack() const
{
	COORD c;
	c.X = X;
	c.Y = Y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void CheckError::GetCurPos(int& x, int& y) const
{
	CONSOLE_SCREEN_BUFFER_INFO screenbuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenbuffer);
	COORD curpos = screenbuffer.dwCursorPosition;
	x = curpos.X;
	y = curpos.Y;
}

bool CheckError::GetClearIFerror() const
{
	return cleariferror;
}

void CheckError::SetClearIfError(const bool cleariferror) const
{
	this->cleariferror = cleariferror;
}

void CheckError::ErrorOutput(const std::string error) const
{
	MovePos(100, Y, true);
	std::cout << error;
	MovePos(X, Y);
	errorlenght = error.length();
	cleariferror = true;
}

void CheckError::ErrorOutput(const char* error) const
{
	MovePos(100, Y, true);
	std::cout << error;
	MovePos(X, Y);
	errorlenght = strlen(error);
	cleariferror = true;
}

void CheckError::ErrorDevOutput(const std::string error) const
{
	MovePos(100, Y, true);
	std::cout << error;
	MovePos(X, Y);
	errorlenght = error.length();
	cleariferror = true;
	char c = _getch();
}

void CheckError::ErrorDevOutput(const char* error) const
{
	MovePos(100, Y, true);
	std::cout << error;
	MovePos(X, Y);
	errorlenght = strlen(error);
	cleariferror = true;
	char c = _getch();
}

void CheckError::ClearError() const
{
	MovePos(100, Y);
	for (int i = 0; i < errorlenght; i++)
		std::cout << " ";
	MovePos(X, Y);
	cleariferror = false;
}

void CheckError::ClearText(const int startX, const int StartY, const int lenght) const
{
	MovePos(startX, StartY, true);
	for (int i = 0; i < lenght; i++)
		std::cout << " ";
	MovePos(X, Y);
}
#endif // !CPORTA


//EXCEPTION CLASSOK

InvalidFormatException::InvalidFormatException(const char* const message) : std::runtime_error(message)
{

}

InvalidProcess::InvalidProcess(const char* const message) : std::logic_error(message)
{

}