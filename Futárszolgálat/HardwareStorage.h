#pragma once
#include "memtrace.h"
#include "GeneralFunctions.h"
#include "Hardware.h"

class Hardware;
class CPU;
class GPU;
class Memory;
class Motherboard;
class PowerSupply;
class HDD;
class SSD;
class ComputerCase;

class HardwareStorage
{
	Array<CPU**> cpus;
	Array<GPU**> gpus;
	Array<Memory**> memories;
	Array<Motherboard**> motherboards;
	Array<PowerSupply**> powersupplies;
	Array<HDD**> hdds;
	Array<SSD**> ssds;
	Array<ComputerCase**> computercases;
 public:
	 HardwareStorage();
	Array<CPU**>& GetCPUArray();
	Array<GPU**>& GetGPUArray();
	Array<Memory**>& GetMemoryArray();
	Array<Motherboard**>& GetMotherboardArray();
	Array<PowerSupply**>& GetPowerSupplyArray();
	Array<HDD**>& GetHDDArray();
	Array<SSD**>& GetSSDArray();
	Array<ComputerCase**>& GetComputerCaseArray();
	void AddCPU(CPU* cpu);
	void AddGPU(GPU* gpu);
	void AddMemory(Memory* memory);
	void AddMotherboard(Motherboard* motherboard);
	void AddPowerSupply(PowerSupply* powersupply);
	void AddHDD(HDD* hdd);
	void AddSSD(SSD* ssd);
	void AddComputerCase(ComputerCase* computercase);
	int ValidId(const size_t min = 1) const;
	Hardware* SearchForId(const size_t id);
	Hardware** GetEveryHardareInStorage(size_t& count);
	size_t GetTotalHardwareCount() const;
};
