#pragma once
#include "memtrace.h"
#include "Setters.h"
#include "Hardware.h"

//HARDWARE SETTEREK



class HardwareIdSetter : public Setters
{
	Hardware* hardware;

public:
	HardwareIdSetter(Hardware* hardware) : hardware(hardware) {}

	void Set();
};

class HardwareDbSetter : public Setters
{
	Hardware* hardware;

public:
	HardwareDbSetter(Hardware* hardware) : hardware(hardware) {}

	void Set();
};

class HardwareNameSetter : public Setters
{
	Hardware* hardware;

public:
	HardwareNameSetter(Hardware* hardware) : hardware(hardware) {}

	void Set();
};

class CPUcoresSetter : public Setters
{
	CPU* cpu;

public:
	CPUcoresSetter(CPU* cpu) : cpu(cpu) {}

	void Set();
};

class CPUclockSetter : public Setters
{
	CPU* cpu;

public:
	CPUclockSetter(CPU* cpu) : cpu(cpu) {}

	void Set();
};

class CPUCPUSocketSetter : public Setters
{
	CPU* cpu;

public:
	CPUCPUSocketSetter(CPU* cpu) : cpu(cpu) {}

	void Set();
};

class CPUTDPSetter : public Setters
{
	CPU* cpu;

public:
	CPUTDPSetter(CPU* cpu) : cpu(cpu) {}

	void Set();
};

class GPUGPUSocketSetter : public Setters
{
	GPU* gpu;

public:
	GPUGPUSocketSetter(GPU* gpu) : gpu(gpu) {}

	void Set();
};

class GPUchipclockSetter : public Setters
{
	GPU* gpu;

public:
	GPUchipclockSetter(GPU* gpu) : gpu(gpu) {}

	void Set();
};

class GPUmemoryclockSetter : public Setters
{
	GPU* gpu;

public:
	GPUmemoryclockSetter(GPU* gpu) : gpu(gpu) {}

	void Set();
};

class GPUvramSetter : public Setters
{
	GPU* gpu;

public:
	GPUvramSetter(GPU* gpu) : gpu(gpu) {}

	void Set();
};

class GPUventsnumberSetter : public Setters
{
	GPU* gpu;

public:
	GPUventsnumberSetter(GPU* gpu) : gpu(gpu) {}

	void Set();
};

class GPUTDPSetter : public Setters
{
	GPU* gpu;

public:
	GPUTDPSetter(GPU* gpu) : gpu(gpu) {}

	void Set();
};

class MemorycapacitySetter : public Setters
{
	Memory* memory;

public:
	MemorycapacitySetter(Memory* memory) : memory(memory) {}

	void Set();
};

class MemorykitSetter : public Setters
{
	Memory* memory;

public:
	MemorykitSetter(Memory* memory) : memory(memory) {}

	void Set();
};

class MemoryclockSetter : public Setters
{
	Memory* memory;

public:
	MemoryclockSetter(Memory* memory) : memory(memory) {}

	void Set();
};

class MemoryddrtypeSetter : public Setters
{
	Memory* memory;

public:
	MemoryddrtypeSetter(Memory* memory) : memory(memory) {}

	void Set();
};

class MotherboardCPUSocketSetter : public Setters
{
	Motherboard* motherboard;

public:
	MotherboardCPUSocketSetter(Motherboard* motherboard) : motherboard(motherboard) {}

	void Set();
};

class MotherboardGPUSocketSetter : public Setters
{
	Motherboard* motherboard;

public:
	MotherboardGPUSocketSetter(Motherboard* motherboard) : motherboard(motherboard) {}

	void Set();
};

class MotherboardddrtypeSetter : public Setters
{
	Motherboard* motherboard;

public:
	MotherboardddrtypeSetter(Motherboard* motherboard) : motherboard(motherboard) {}

	void Set();
};

class MotherboardmaxmemorySetter : public Setters
{
	Motherboard* motherboard;

public:
	MotherboardmaxmemorySetter(Motherboard* motherboard) : motherboard(motherboard) {}

	void Set();
};

class MotherboardFormfactorSetter : public Setters
{
	Motherboard* motherboard;

public:
	MotherboardFormfactorSetter(Motherboard* motherboard) : motherboard(motherboard) {}

	void Set();
};

class PowerSupplypowersupplytypeSetter : public Setters
{
	PowerSupply* powersupply;

public:
	PowerSupplypowersupplytypeSetter(PowerSupply* powersupply) : powersupply(powersupply) {}

	void Set();
};

class PowerSupplypowerSetter : public Setters
{
	PowerSupply* powersupply;

public:
	PowerSupplypowerSetter(PowerSupply* powersupply) : powersupply(powersupply) {}

	void Set();
};

class PowerSupplyefficiencySetter : public Setters
{
	PowerSupply* powersupply;

public:
	PowerSupplyefficiencySetter(PowerSupply* powersupply) : powersupply(powersupply) {}

	void Set();
};

class PowerSupplyPFCSetter : public Setters
{
	PowerSupply* powersupply;

public:
	PowerSupplyPFCSetter(PowerSupply* powersupply) : powersupply(powersupply) {}

	void Set();
};

class HDDcapacitySetter : public Setters
{
	HDD* hdd;

public:
	HDDcapacitySetter(HDD* hdd) : hdd(hdd) {}

	void Set();
};

class HDDRPMSetter : public Setters
{
	HDD* hdd;

public:
	HDDRPMSetter(HDD* hdd) : hdd(hdd) {}

	void Set();
};

class HDDdiameterSetter : public Setters
{
	HDD* hdd;

public:
	HDDdiameterSetter(HDD* hdd) : hdd(hdd) {}

	void Set();
};

class HDDconnectorSetter : public Setters
{
	HDD* hdd;

public:
	HDDconnectorSetter(HDD* hdd) : hdd(hdd) {}

	void Set();
};

class SSDcapacitySetter : public Setters
{
	SSD* ssd;

public:
	SSDcapacitySetter(SSD* ssd) : ssd(ssd) {}

	void Set();
};

class SSDNANDflashSetter : public Setters
{
	SSD* ssd;

public:
	SSDNANDflashSetter(SSD* ssd) : ssd(ssd) {}

	void Set();
};

class SSDconnectorSetter : public Setters
{
	SSD* ssd;

public:
	SSDconnectorSetter(SSD* ssd) : ssd(ssd) {}

	void Set();
};

class ComputerCaseweightSetter : public Setters
{
	ComputerCase* computercase;

public:
	ComputerCaseweightSetter(ComputerCase* computercase) : computercase(computercase) {}

	void Set();
};

class ComputerCaseFormfactorSetter : public Setters
{
	ComputerCase* computercase;

public:
	ComputerCaseFormfactorSetter(ComputerCase* computercase) : computercase(computercase) {}

	void Set();
};

class ComputerCaseventsSetter : public Setters
{
	ComputerCase* computercase;

public:
	ComputerCaseventsSetter(ComputerCase* computercase) : computercase(computercase) {}

	void Set();
};

class ComputerCaseDrive3dot5Setter : public Setters
{
	ComputerCase* computercase;

public:
	ComputerCaseDrive3dot5Setter(ComputerCase* computercase) : computercase(computercase) {}

	void Set();
};

class ComputerCaseDrive2dot5Setter : public Setters
{
	ComputerCase* computercase;

public:
	ComputerCaseDrive2dot5Setter(ComputerCase* computercase) : computercase(computercase) {}

	void Set();
};
