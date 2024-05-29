#include "FileHandler.h"
#include <stdio.h>
#include "memtrace.h"


//FileHandler osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FileHandler::FileExist(const std::string filename) const
{
	std::ifstream File(filename);
	File.close();
	return File.good();
}


void FileHandler::CreateFileCustom(const std::string filename) const
{
	std::ofstream File(filename);
	File.close();
}

void FileHandler::ReadFromFile(const std::string filename, std::string** text, size_t* count, const int searchline, const int block, const bool firstlines)
{
	if (!FileExist(filename))
		throw InvalidProcess("Nem letezik a megadott fajl");
	else
	{
		std::ifstream File(filename);
		std::string reader;
		int index = 0;
		int search = 0;
		if (!firstlines)
			search = searchline;
		int blockcount = -1;
		while (std::getline(File, reader))
		{
			index++;
		}
		*text = new std::string[index];
		index = 0;
		File.clear();
		File.seekg(0);
		while (getline(File, reader))
		{
			if (search == searchline)
			{
				blockcount++;
				if (blockcount < block)
				{
					(*text)[index] = reader;
					index++;
				}
				if(blockcount == block - 1)
				{
					blockcount = -1;
					search = 0;
				}
			}
			else
			{
				search++;
			}
		}
		File.close();
		*count = index;
	}
}

std::istream& FileHandler::getline(std::istream& is, std::string& str) { //Platformfuggetlen beolvaso
	std::getline(is, str);
	if (str.size() && *str.rbegin() == '\r')
		str.erase(str.size() - 1);
	return is;
}