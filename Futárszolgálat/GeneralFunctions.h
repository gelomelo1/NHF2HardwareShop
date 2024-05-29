#pragma once
#include "memtrace.h"
#include "CportaDefine.h"

class InvalidFormatException : public std::runtime_error
{
public:
	InvalidFormatException(const char* const message);
};

class InvalidProcess : public std::logic_error
{
public:
	InvalidProcess(const char* const message);
};

#ifdef CPORTA
class CheckError
{
	static int X;
	static int Y;
	static int errorlenght;
	static bool cleariferror;

public:

	CheckError() {}

	bool GetClearIFerror() const;

	void SetClearIfError(const bool cleariferror) const;

	void ErrorOutput(const std::string error) const;

	void ErrorOutput(const char* error) const;

	void ErrorDevOutput(const std::string error) const;

	void ErrorDevOutput(const char* error) const;

};
#endif // CPORTA

#ifndef CPORTA
class CheckError
{
	static int X;
	static int Y;
	static int errorlenght;
	static bool cleariferror;

public:

	CheckError() {}

	bool GetClearIFerror() const;

	void SetClearIfError(const bool cleariferror) const;

	void ErrorOutput(const std::string error) const;

	void ErrorOutput(const char* error) const;

	void ErrorDevOutput(const std::string error) const;

	void ErrorDevOutput(const char* error) const;

	void ClearError() const;

	void ClearText(const int startX, const int StartY, const int lenght) const;

	void GetCurPos(int& x, int& y) const;

	void MovePos(const int x, const int y, const bool temporary = false) const;

	void MovePosBack() const;
};
#endif // !CPORTA


template<typename T>
class Array
{
	CheckError error;
	size_t maxSize;
	size_t size;
	T* arr;
	void MakeSpace()
	{
		maxSize += 5;
		T* space = new T[maxSize];
		for (size_t i = 0; i < size; i++)
			space[i] = arr[i];
		delete[] arr;
		arr = space;
	}
public:
	Array() : maxSize(0),  size(0), arr(nullptr) {}

	size_t getMaxSizeForTest() const
	{
		return maxSize;
	}

	void CreateArray(const size_t size)
	{
		maxSize = size;
		arr = new T[maxSize];
	}

	void Upload(const T* items, const size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (size == maxSize)
				MakeSpace();
			arr[i] = items[i];
			size++;
		}
	}

	void Upload(T item)
	{
		if (size == maxSize)
			MakeSpace();
		arr[size] = item;
		size++;
	}

	T* getArray()
	{
		return arr;
	}

	T& operator[](size_t index)
	{
			return arr[index];
	}

	const  T& operator[](size_t index) const
	{
		return arr[index];
	}

	size_t getSize() const
	{
		return size;
	}

	void Clear()
	{
		if (arr != nullptr)
		{
			delete[] arr;
			arr = nullptr;
			size = 0;
		}
	}

	~Array()
	{
		Clear();
	}
};

template<typename T>
class Array<T**>
{
	const bool twodimensionalarray;
	CheckError error;
	size_t maxSize;
	size_t size;
	T** arr;

	void MakeSpace()
	{
		maxSize += 5;
		T** space = new T * [maxSize];
		for (size_t i = 0; i < size; i++)
			space[i] = arr[i];
			delete[] arr;
		arr = space;
	}

public:
	Array(const bool twodimensionalarray) : twodimensionalarray(twodimensionalarray), maxSize(0), size(0), arr(nullptr) {}

	size_t getMaxSizeForTest() const
	{
		return maxSize;
	}

	void CreateArray(const size_t size)
	{
		maxSize = size;
		arr = new T * [maxSize];
	}

	void Upload(T** items, const size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (size == maxSize)
				MakeSpace();
			arr[i] = items[i];
			size++;
		}
	}

	void Upload(T* item)
	{
		if (size == maxSize)
			MakeSpace();
		arr[size] = item;
		size++;
	}

	void DeleteItem(const size_t index)
	{
			if (twodimensionalarray)
				delete[] arr[index];
			else
				delete arr[index];
			for (size_t i = index; i < size; i++)
				arr[i] = arr[i + 1];
			size--;
	}

	T** getArray()
	{
		return arr;
	}

	size_t getSize() const
	{
		return size;
	}

 	T* operator[](size_t index)
	{
			return arr[index];
	}

  const  T* operator[](size_t index) const
	{
			return arr[index];
	}

  void Clear()
  {
	  if (arr != nullptr)
	  {
		  for (size_t i = 0; i < size; i++)
		  {
			  if (arr[i] != nullptr)
			  {
				  if (twodimensionalarray)
					  delete[] arr[i];
				  else
					  delete arr[i];
				  arr[i] = nullptr;
			  }
		  }
		  delete[] arr;
		  arr = nullptr;
		  size = 0;
	  }
  }

	~Array()
	{
		Clear();
	}
};
