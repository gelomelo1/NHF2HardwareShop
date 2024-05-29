#include "memtrace.h"
#include "HardwareStorage.h"


//HardwareStorage osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

HardwareStorage::HardwareStorage() : cpus(false), gpus(false), memories(false), motherboards(false), powersupplies(false), hdds(false), ssds(false), computercases(false)
{
	cpus.CreateArray(1);
	gpus.CreateArray(1);
	memories.CreateArray(1);
	motherboards.CreateArray(1);
	powersupplies.CreateArray(1);
	hdds.CreateArray(1);
	ssds.CreateArray(1);
	computercases.CreateArray(1);
}

Array<CPU**>& HardwareStorage::GetCPUArray()
{
	return cpus;
}
Array<GPU**>& HardwareStorage::GetGPUArray()
{
	return gpus;
}
Array<Memory**>& HardwareStorage::GetMemoryArray()
{
	return memories;
}
Array<Motherboard**>& HardwareStorage::GetMotherboardArray()
{
	return motherboards;
}
Array<PowerSupply**>& HardwareStorage::GetPowerSupplyArray()
{
	return powersupplies;
}
Array<HDD**>& HardwareStorage::GetHDDArray()
{
	return hdds;
}
Array<SSD**>& HardwareStorage::GetSSDArray()
{
	return ssds;
}
Array<ComputerCase**>& HardwareStorage::GetComputerCaseArray()
{
	return computercases;
}

void HardwareStorage::AddCPU(CPU* cpu)
{
	cpus.Upload(cpu);
}

void HardwareStorage::AddGPU(GPU* gpu)
{
	gpus.Upload(gpu);
}

void HardwareStorage::AddMemory(Memory* memory)
{
	memories.Upload(memory);
}

void HardwareStorage::AddMotherboard(Motherboard* motherboard)
{
	motherboards.Upload(motherboard);
}

void HardwareStorage::AddPowerSupply(PowerSupply* powersupply)
{
	powersupplies.Upload(powersupply);
}

void HardwareStorage::AddHDD(HDD* hdd)
{
	hdds.Upload(hdd);
}

void HardwareStorage::AddSSD(SSD* ssd)
{
	ssds.Upload(ssd);
}

void HardwareStorage::AddComputerCase(ComputerCase* computercase)
{
	computercases.Upload(computercase);
}

int HardwareStorage::ValidId(const size_t min) const
{
		for (size_t i = 0; i < cpus.getSize(); i++)
		{
			if (cpus[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < gpus.getSize(); i++)
		{
			if (gpus[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < memories.getSize(); i++)
		{
			if (memories[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < motherboards.getSize(); i++)
		{
			if (motherboards[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < powersupplies.getSize(); i++)
		{
			if (powersupplies[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < hdds.getSize(); i++)
		{
			if (hdds[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < ssds.getSize(); i++)
		{
			if (ssds[i]->GetId() == min)
				return ValidId(min + 1);
		}
		for (size_t i = 0; i < computercases.getSize(); i++)
		{
			if (computercases[i]->GetId() == min)
				return ValidId(min + 1);
		}
		return min;
}

Hardware* HardwareStorage::SearchForId(const size_t id)
{
	for (size_t i = 0; i < cpus.getSize(); i++)
	{
		if (cpus[i]->GetId() == id)
			return cpus[i];
	}
	for (size_t i = 0; i < gpus.getSize(); i++)
	{
		if (gpus[i]->GetId() == id)
			return gpus[i];
	}
	for (size_t i = 0; i < memories.getSize(); i++)
	{
		if (memories[i]->GetId() == id)
			return memories[i];
	}
	for (size_t i = 0; i < motherboards.getSize(); i++)
	{
		if (motherboards[i]->GetId() == id)
			return motherboards[i];
	}
	for (size_t i = 0; i < powersupplies.getSize(); i++)
	{
		if (powersupplies[i]->GetId() == id)
			return powersupplies[i];
	}
	for (size_t i = 0; i < hdds.getSize(); i++)
	{
		if (hdds[i]->GetId() == id)
			return hdds[i];
	}
	for (size_t i = 0; i < ssds.getSize(); i++)
	{
		if (ssds[i]->GetId() == id)
			return ssds[i];
	}
	for (size_t i = 0; i < computercases.getSize(); i++)
	{
		if (computercases[i]->GetId() == id)
			return computercases[i];
	}
	return nullptr;
}

Hardware** HardwareStorage::GetEveryHardareInStorage(size_t& count)
{
	count = cpus.getSize() + gpus.getSize() + memories.getSize() + motherboards.getSize() + powersupplies.getSize() + hdds.getSize() + ssds.getSize() + computercases.getSize();
	size_t index = 0;
	if (count > 0)
	{
		Hardware** hardwares = new Hardware * [count];
		for (size_t i = 0; i < cpus.getSize(); i++)
		{
			hardwares[index++] = cpus[i];
		}
		for (size_t i = 0; i < gpus.getSize(); i++)
		{
			hardwares[index++] = gpus[i];
		}
		for (size_t i = 0; i < memories.getSize(); i++)
		{
			hardwares[index++] = memories[i];
		}
		for (size_t i = 0; i < motherboards.getSize(); i++)
		{
			hardwares[index++] = motherboards[i];
		}
		for (size_t i = 0; i < powersupplies.getSize(); i++)
		{
			hardwares[index++] = powersupplies[i];
		}
		for (size_t i = 0; i < hdds.getSize(); i++)
		{
			hardwares[index++] = hdds[i];
		}
		for (size_t i = 0; i < ssds.getSize(); i++)
		{
			hardwares[index++] = ssds[i];
		}
		for (size_t i = 0; i < computercases.getSize(); i++)
		{
			hardwares[index++] = computercases[i];
		}
		return hardwares;
	}
	else
		return nullptr;
}

size_t HardwareStorage::GetTotalHardwareCount() const
{
	return  cpus.getSize() + gpus.getSize() + memories.getSize() + motherboards.getSize() + powersupplies.getSize() + hdds.getSize() + ssds.getSize() + computercases.getSize();
}