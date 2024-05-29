#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "memtrace.h"
#include "GeneralFunctions.h"

class FileHandler
{

	CheckError error;

public:

	FileHandler() {}

	bool FileExist(const std::string filename) const;

	void CreateFileCustom(const std::string filename) const;

	void ReadFromFile(const std::string filename, std::string** text, size_t* count, const int searchline = 0, const int block = 1, const bool firstlines = false);

	std::istream& getline(std::istream& is, std::string& str);

	template<typename T>
	void WriteToFile(const std::string filename, const T* type, const int count, const bool addnewline = false, const bool overwrite = false) const
	{
		if (!FileExist(filename))
			throw InvalidProcess("Nem letezik a megadott fajl");
		else
		{
			std::ofstream File;
			if (overwrite)
				File.open(filename, std::ofstream::out | std::ofstream::trunc);
			else
				File.open(filename, std::ofstream::app);
			for (int i = 0; i < count; i++)
				File << type[i] << "\n";
			if (addnewline)
				File << "\n";
			File.close();
		}

	}
};
