#pragma once
#include "memtrace.h"
#include "HardwareStorage.h"
#include "Setters.h"
#include "GeneralFunctions.h"

class HardwareStorage;

class Hardware
{
public:
	enum class State
	{
		Load, Input, Print
	};
	virtual Hardware* Clone() const = 0;
	virtual Array<Setters**>& GetSetters() = 0;
	virtual void AddItself(HardwareStorage* const hardwarestorage) = 0;
	virtual void FormatInfo(std::string* stringarray) = 0;
	void SetId(const size_t id);
	void SetDb(const size_t db);
	void SetName(const std::string name);
    size_t GetId() const;
	size_t GetDb() const;
	std::string GetName() const;
	void SetState(const State state);
	int GetCountForFunctions();
	static int GetBaseinformationcount();
	bool operator==(const Hardware& hardware);
	bool isStringEmpty(const std::string& text);
	bool isContainSplit(const std::string& text);
	virtual ~Hardware() {}
protected:
	static const int baseinformationcount = 3;
	Array<Setters**> setters;
	size_t id; //a hardver azonositoja
	size_t db; //darabszam ami vagy a raktarban levo mennyiseget, vagy a rendelt mennyiseget jeloli
	std::string name; //a hardver neve
	State state;
	State statebefore;
	const int countforfunctions;
	Hardware(const int countforfunctions);
};

class CPU : public Hardware
{
	static const int informationcount = 4;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
public:
	std::string cores; //CPU magok szama
	std::string clock; //CPU orajel
	std::string CPUSocket; //CPU foglalat
	std::string TDP; //Energiafogyasztas
	CPU();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<CPU**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetCores(const std::string cores);
	void SetClock(const std::string clock);
	void SetCPUSocket(const std::string CPUSocket);
	void SetTDP(const std::string TDP);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	CPU& operator=(const CPU& cpu);
	Hardware* Clone() const;
};

class GPU : public Hardware
{
	static const int informationcount = 6;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
public:
	std::string GPUSocket; //GPU foglalat
	std::string chipclock; //chipset orajel
	std::string memoryclock; 	//memoriaorajel
	std::string vram; //vram merete
	std::string ventsnumber; //ventilatorok szama
	std::string TDP; //Energiafogyasztas
	GPU();

	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<GPU**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetGPUSocket(const std::string GPUSocket);
	void SetChipclock(const std::string chipclock);
	void SetMemoryclock(const std::string memoryclock);
	void SetVram(const std::string vram);
	void SetVentsnumber(const std::string ventsnumber);
	void SetTDP(const std::string TDP);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	GPU& operator=(const GPU& cpu);
	Hardware* Clone() const;
};

class Memory : public Hardware
{
	static const int informationcount = 4;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
	std::string capacity; //kapacitas
	std::string kit; //kiszereles
	std::string clock; //orajel
	std::string ddrtype; //ddr tipus
public:
	Memory();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<Memory**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetCapacity(const std::string capacity);
	void SetKit(const std::string kit);
	void SetClock(const std::string clock);
	void SetDdrtype(const std::string ddrtype);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	Memory& operator=(const Memory& cpu);
	Hardware* Clone() const;
};

class Motherboard : public Hardware
{
	static const int informationcount = 5;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
	std::string CPUSocket; //CPU foglalat
	std::string GPUSocket; //GPU foglalat
	std::string ddrtype; //ddr tipus
	std::string maxmemory; //maximum memoria
	std::string Formfactor; //meret szabvany
public:
	Motherboard();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<Motherboard**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetCPUSocket(const std::string CPUSocket);
	void SetGPUSocket(const std::string GPUSocket);
	void SetDdrtype(const std::string ddrtype);
	void SetMaxmemory(const std::string maxmemory);
	void SetFormfactor(const std::string Formfactor);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	Motherboard& operator=(const Motherboard& cpu);
	Hardware* Clone() const;
};

class PowerSupply : public Hardware
{
	static const int informationcount = 4;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
	std::string powersupplytype; //tapegyseg fajtaja
	std::string power; //aramfelvetel
	std::string efficiency; //hatasfok
	std::string PFC; //pfc fajtaja
public:
	PowerSupply();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<PowerSupply**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetPowersupplytype(const std::string powersupplytype);
	void SetPower(const std::string power);
	void SetEfficiency(const std::string efficiency);
	void SetPFC(const std::string PFC);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	PowerSupply& operator=(const PowerSupply& cpu);
	Hardware* Clone() const;
};

class HDD : public Hardware
{
	static const int informationcount = 4;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
	std::string capacity; //kapacitas
	std::string RPM; //lemez fordulatszam
	std::string diameter; //meret szabvany
	std::string connector; //csatlakozo tipusa
public:
	HDD();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<HDD**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetCapacity(const std::string capacity);
	void SetRPM(const std::string RPM);
	void SetDiameter(const std::string diameter);
	void SetConnector(const std::string connector);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	HDD& operator=(const HDD& cpu);
	Hardware* Clone() const;
};

class SSD : public Hardware
{
	static const int informationcount = 3;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
	std::string capacity; //kapacitas
	std::string NANDflash; //nand flash fajtaja
	std::string connector; //csatlakozo tipusa
public:
	SSD();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<SSD**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetCapacity(const std::string capacity);
	void SetNANDflash(const std::string NANDflash);
	void SetConnector(const std::string connector);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	SSD& operator=(const SSD& cpu);
	Hardware* Clone() const;
};

class ComputerCase : public Hardware
{
	static const int informationcount = 5;
	static const std::string type;
	static const std::string menupoints[informationcount + 1];
	std::string weight; //tomeg
	std::string Formfactor; //alaplap meretszabvany
	std::string vents; //ventilatorok szama
	std::string Drive3dot5; //3.5 tarolok szama
	std::string Drive2dot5; //2.5 tarolok szama
public:
	ComputerCase();
	static int GetInformationcount();
	static std::string getStatType();
	static void GetStatMenuPoints(std::string* stringarray);
	static Array<ComputerCase**>& GetOwnArray(HardwareStorage* const hardwarestorage);
	Array<Setters**>& GetSetters();
	void SetWeight(const std::string weight);
	void SetFormfactor(const std::string Formfactor);
	void SetVents(const std::string vents);
	void SetDrive3dot5(const std::string Drive3dot5);
	void SetDrive2dot5(const std::string Drive2dot5);
	void AddItself(HardwareStorage* const hardwarestorage);
	void FormatInfo(std::string* stringarray);
	ComputerCase& operator=(const ComputerCase& cpu);
	Hardware* Clone() const;
};



