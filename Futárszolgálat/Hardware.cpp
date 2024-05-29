#include "memtrace.h"
#include "Hardware.h"
#include "HardwareSetters.h"
const std::string CPU::type = "Processzor";
const std::string GPU::type = "Videokartya";
const std::string Memory::type = "Memoria";
const std::string Motherboard::type = "Alaplap";
const std::string PowerSupply::type = "Tapegyseg";
const std::string HDD::type = "Merevlemez";
const std::string SSD::type = "SSD";
const std::string ComputerCase::type = "Gephaz";
const std::string CPU::menupoints[] = { "nev:", "magok szama:", "orajel(Ghz):", "foglalat:", "fogyasztas(Watt):" };
const std::string GPU::menupoints[] = { "nev:", "foglalat:", "chipset orajel(Mhz):", "memoria orajel(Mhz):", "vram meret(Gb):", "ventilatorok szama:", "fogyasztas(Watt):" };
const std::string Memory::menupoints[] = { "nev:" ,"ram meret(Gb):", "kiszereles(modul db)", "orajel(Mhz):", "ddr tipus:"};
const std::string Motherboard::menupoints[] = { "nev:", "processzor foglalat:", "videokartya foglalat:", "ddr tipus:", "ram foglalatok(db):", "szabvany meret:" };
const std::string PowerSupply::menupoints[] = { "nev:", "tapegyseg tipusa:", "teljesitmeny(Watt):", "hatasfok(%):", "PFC fajtaja:" };
const std::string HDD::menupoints[] = { "nev:", "kapacitas(Gb):", "lemez fordulatszama:", "szabvany meret:", "csatlakozo tipusa:" };
const std::string SSD::menupoints[] = { "nev:", "kapacitas(Gb):", "NAND flash tipusa:", "csatlakozo tipusa:" };
const std::string ComputerCase::menupoints[] = { "nev:", "tomeg(Kg):", "alaplap szabvany:", "ventilatorok szama:", "3.5-os tarolok szama:", "2.5-os tarolok szama:" };


//Hardware ososztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

Hardware::Hardware(const int countforfunctions) : setters(false), id(0), db(0), state(Hardware::State::Load), statebefore(Hardware::State::Input), countforfunctions(countforfunctions) { }

int Hardware::GetBaseinformationcount()
{
	return baseinformationcount;
}

int Hardware::GetCountForFunctions()
{
	return countforfunctions;
}

size_t Hardware::GetId() const
{
	return id;
}
size_t Hardware::GetDb() const
{
	return db;
}
std::string Hardware::GetName() const
{
	return name;
}

void Hardware::SetId(const size_t id)
{
	this->id = id;
}
void Hardware::SetDb(const size_t db)
{
	this->db = db;
}

void Hardware::SetName(const std::string name)
{
	if(!isStringEmpty(name) && !isContainSplit(name))
	this->name = name;
}

void Hardware::SetState(const State state)
{
	statebefore = this->state;
	this->state = state;
}

bool Hardware::operator==(const Hardware& hardware)
{
	if (id == hardware.id)
		return true;
	return false;
}

bool Hardware::isStringEmpty(const std::string& text)
{
	if (text.length() == 0)
	{
		throw InvalidFormatException("Nem hagyhatod uresen a mezot");
		return true;
	}
	return false;
}

bool Hardware::isContainSplit(const std::string& text)
{
	size_t search = text.find("|");
	if (search != text.npos)
	{
		throw InvalidFormatException("A mezo nem tartalmazhat | karaktert");
		return true;
	}
	return false;
}


//CPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

CPU::CPU() : Hardware(informationcount) {}


Array<CPU**>& CPU::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetCPUArray();
}

int CPU::GetInformationcount()
{
	return informationcount;
}

std::string CPU::getStatType()
{
	return type;
}

void CPU::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& CPU::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new CPUcoresSetter(this), new CPUclockSetter(this), new CPUCPUSocketSetter(this), new CPUTDPSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new CPUcoresSetter(this), new CPUclockSetter(this), new CPUCPUSocketSetter(this), new CPUTDPSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void CPU::SetCores(const std::string cores)
{
	if(!isStringEmpty(cores) && !isContainSplit(cores))
	this->cores = cores;
}

void CPU::SetClock(const std::string clock)
{
	if(!isStringEmpty(clock) && !isContainSplit(clock))
	this->clock = clock;
}

void CPU::SetCPUSocket(const std::string CPUSocket)
{
	if(!isStringEmpty(CPUSocket) && !isContainSplit(CPUSocket))
	this->CPUSocket = CPUSocket;
}

void CPU::SetTDP(const std::string TDP)
{
	if(!isStringEmpty(TDP) && !isContainSplit(TDP))
	this->TDP = TDP;
}

void CPU::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddCPU(this);
}

void CPU::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = cores;
		stringarray[5] = clock;
		stringarray[6] = CPUSocket;
		stringarray[7] = TDP;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = cores;
		stringarray[2] = clock;
		stringarray[3] = CPUSocket;
		stringarray[4] = TDP;
		stringarray[5] = "#" + std::to_string(id);
		stringarray[6] = std::to_string(db);
	}
}

CPU& CPU::operator=(const CPU& cpu) //ATALAKITAS, itt lehet kellenek majd a GetSetterek
{
	id = cpu.id;
	db = cpu.db;
	name = cpu.name;
	state = cpu.state;
	statebefore = cpu.statebefore;
	cores = cpu.cores;
	clock = cpu.clock;
	CPUSocket = cpu.CPUSocket;
	TDP = cpu.TDP;
	return *this;
}

Hardware* CPU::Clone() const
{
	CPU* cpu = new CPU;
	*cpu = *this;
	return cpu;
}


//GPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

GPU::GPU() : Hardware(informationcount) {}

Array<GPU**>& GPU::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetGPUArray();
}

int GPU::GetInformationcount()
{
	return informationcount;
}

std::string GPU::getStatType()
{
	return type;
}

void GPU::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& GPU::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new GPUGPUSocketSetter(this), new GPUchipclockSetter(this), new GPUmemoryclockSetter(this), new GPUvramSetter(this), new GPUventsnumberSetter(this), new GPUTDPSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new GPUGPUSocketSetter(this), new GPUchipclockSetter(this), new GPUmemoryclockSetter(this), new GPUvramSetter(this), new GPUventsnumberSetter(this), new GPUTDPSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void GPU::SetGPUSocket(const std::string GPUSocket)
{
	if(!isStringEmpty(GPUSocket) && !isContainSplit(GPUSocket))
	this->GPUSocket = GPUSocket;
}
void GPU::SetChipclock(const std::string chipclock)
{
	if(!isStringEmpty(chipclock) && !isContainSplit(chipclock))
	this->chipclock = chipclock;
}
void GPU::SetMemoryclock(const std::string memoryclock)
{
	if(!isStringEmpty(memoryclock) && !isContainSplit(memoryclock))
	this->memoryclock = memoryclock;
}
void GPU::SetVram(const std::string vram)
{
	if(!isStringEmpty(vram) && !isContainSplit(vram))
	this->vram = vram;
}
void GPU::SetVentsnumber(const std::string ventsnumber)
{
	if(!isStringEmpty(ventsnumber) && !isContainSplit(ventsnumber))
	this->ventsnumber = ventsnumber;
}
void GPU::SetTDP(const std::string TDP)
{
	if(!isStringEmpty(TDP) && !isContainSplit(TDP))
	this->TDP = TDP;
}

void GPU::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddGPU(this);
}

void GPU::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = GPUSocket;
		stringarray[5] = chipclock;
		stringarray[6] = memoryclock;
		stringarray[7] = vram;
		stringarray[8] = ventsnumber;
		stringarray[9] = TDP;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = GPUSocket;
		stringarray[2] = chipclock;
		stringarray[3] = memoryclock;
		stringarray[4] = vram;
		stringarray[5] = ventsnumber;
		stringarray[6] = TDP;
		stringarray[7] = "#" + std::to_string(id);
		stringarray[8] = std::to_string(db);
	}
}

GPU& GPU::operator=(const GPU& gpu)
{
	id = gpu.id;
	db = gpu.db;
	name = gpu.name;
	state = gpu.state;
	statebefore = gpu.statebefore;
	GPUSocket = gpu.GPUSocket;
	chipclock = gpu.chipclock;
	memoryclock = gpu.memoryclock;
	vram = gpu.vram;
	ventsnumber = gpu.ventsnumber;
	TDP = gpu.TDP;
	return *this;
}

Hardware* GPU::Clone() const
{
	GPU* gpu = new GPU;
	*gpu = *this;
	return gpu;
}


//Memory Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

Memory::Memory() : Hardware(informationcount) {}

Array<Memory**>& Memory::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetMemoryArray();
}

int Memory::GetInformationcount()
{
	return informationcount;
}

std::string Memory::getStatType()
{
	return type;
}

void Memory::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& Memory::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new MemorycapacitySetter(this), new MemorykitSetter(this), new MemoryclockSetter(this), new MemoryddrtypeSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new MemorycapacitySetter(this), new MemorykitSetter(this), new MemoryclockSetter(this), new MemoryddrtypeSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
		return setters;
}

void Memory::SetCapacity(const std::string capacity)
{
	if(!isStringEmpty(capacity) && !isContainSplit(capacity))
	this->capacity = capacity;
}
void Memory::SetKit(const std::string kit)
{
	if(!isStringEmpty(kit) && !isContainSplit(kit))
	this->kit = kit;
}
void Memory::SetClock(const std::string clock)
{
	if(!isStringEmpty(clock) && !isContainSplit(clock))
	this->clock = clock;
}
void Memory::SetDdrtype(const std::string ddrtype)
{
	if(!isStringEmpty(ddrtype) && !isContainSplit(ddrtype))
	this->ddrtype = ddrtype;
}

void Memory::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddMemory(this);
}

void Memory::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = capacity;
		stringarray[5] = kit;
		stringarray[6] = clock;
		stringarray[7] = ddrtype;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = capacity;
		stringarray[2] = kit;
		stringarray[3] = clock;
		stringarray[4] = ddrtype;
		stringarray[5] = "#" + std::to_string(id);
		stringarray[6] = std::to_string(db);
	}
}

Memory& Memory::operator=(const Memory& memory)
{
	id = memory.id;
	db = memory.db;
	name = memory.name;
	state = memory.state;
	statebefore = memory.statebefore;
	capacity = memory.capacity;
	kit = memory.kit;
	clock = memory.clock;
	ddrtype = memory.ddrtype;
	return *this;
}

Hardware* Memory::Clone() const
{
	Memory* memory = new Memory;
	*memory = *this;
	return memory;
}


//Motherboard Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

Motherboard::Motherboard() : Hardware(informationcount) {}

Array<Motherboard**>& Motherboard::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetMotherboardArray();
}

int Motherboard::GetInformationcount()
{
	return informationcount;
}

std::string Motherboard::getStatType()
{
	return type;
}

void Motherboard::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& Motherboard::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new MotherboardCPUSocketSetter(this), new MotherboardGPUSocketSetter(this), new MotherboardddrtypeSetter(this), new MotherboardmaxmemorySetter(this), new MotherboardFormfactorSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new MotherboardCPUSocketSetter(this), new MotherboardGPUSocketSetter(this), new MotherboardddrtypeSetter(this), new MotherboardmaxmemorySetter(this), new MotherboardFormfactorSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void Motherboard::SetCPUSocket(const std::string CPUSocket)
{
	if(!isStringEmpty(CPUSocket) && !isContainSplit(CPUSocket))
	this->CPUSocket = CPUSocket;
}
void Motherboard::SetGPUSocket(const std::string GPUSocket)
{
	if(!isStringEmpty(GPUSocket) && !isContainSplit(GPUSocket))
	this->GPUSocket = GPUSocket;
}
void Motherboard::SetDdrtype(const std::string ddrtype)
{
	if(!isStringEmpty(ddrtype) && !isContainSplit(ddrtype))
	this->ddrtype = ddrtype;
}
void Motherboard::SetMaxmemory(const std::string maxmemory)
{
	if(!isStringEmpty(maxmemory) && !isContainSplit(maxmemory))
	this->maxmemory = maxmemory;
}
void Motherboard::SetFormfactor(const std::string Formfactor)
{
	if(!isStringEmpty(Formfactor) && !isContainSplit(Formfactor))
	this->Formfactor = Formfactor;
}

void Motherboard::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddMotherboard(this);
}

void Motherboard::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = CPUSocket;
		stringarray[5] = GPUSocket;
		stringarray[6] = ddrtype;
		stringarray[7] = maxmemory;
		stringarray[8] = Formfactor;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = CPUSocket;
		stringarray[2] = GPUSocket;
		stringarray[3] = ddrtype;
		stringarray[4] = maxmemory;
		stringarray[5] = Formfactor;
		stringarray[6] = "#" + std::to_string(id);
		stringarray[7] = std::to_string(db);
	}
}

Motherboard& Motherboard::operator=(const Motherboard& motherboard)
{
	id = motherboard.id;
	db = motherboard.db;
	name = motherboard.name;
	state = motherboard.state;
	statebefore = motherboard.statebefore;
	CPUSocket = motherboard.CPUSocket;
	GPUSocket = motherboard.GPUSocket;
	ddrtype = motherboard.ddrtype;
	maxmemory = motherboard.maxmemory;
	Formfactor = motherboard.Formfactor;
	return *this;
}

Hardware* Motherboard::Clone() const
{
	Motherboard* motherboard = new Motherboard;
	*motherboard = *this;
	return motherboard;
}


//PowerSupply Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

PowerSupply::PowerSupply() : Hardware(informationcount) {}

Array<PowerSupply**>& PowerSupply::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetPowerSupplyArray();
}

int PowerSupply::GetInformationcount()
{
	return informationcount;
}

std::string PowerSupply::getStatType()
{
	return type;
}

void PowerSupply::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& PowerSupply::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new PowerSupplypowersupplytypeSetter(this), new PowerSupplypowerSetter(this), new PowerSupplyefficiencySetter(this), new PowerSupplyPFCSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new PowerSupplypowersupplytypeSetter(this), new PowerSupplypowerSetter(this), new PowerSupplyefficiencySetter(this), new PowerSupplyPFCSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void PowerSupply::SetPowersupplytype(const std::string powersupplytype)
{
	if(!isStringEmpty(powersupplytype) && !isContainSplit(powersupplytype))
	this->powersupplytype = powersupplytype;
}
void PowerSupply::SetPower(const std::string power)
{
	if(!isStringEmpty(power) && !isContainSplit(power))
	this->power = power;
}
void PowerSupply::SetEfficiency(const std::string efficiency)
{
	if(!isStringEmpty(efficiency) && !isContainSplit(efficiency))
	this->efficiency = efficiency;
}
void PowerSupply::SetPFC(const std::string PFC)
{
	if(!isStringEmpty(PFC) && !isContainSplit(PFC))
	this->PFC = PFC;
}

void PowerSupply::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddPowerSupply(this);
}

void PowerSupply::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = powersupplytype;
		stringarray[5] = power;
		stringarray[6] = efficiency;
		stringarray[7] = PFC;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = powersupplytype;
		stringarray[2] = power;
		stringarray[3] = efficiency;
		stringarray[4] = PFC;
		stringarray[5] = "#" + std::to_string(id);
		stringarray[6] = std::to_string(db);
	}
}

PowerSupply& PowerSupply::operator=(const PowerSupply& powersupply)
{
	id = powersupply.id;
	db = powersupply.db;
	name = powersupply.name;
	state = powersupply.state;
	statebefore = powersupply.statebefore;
	powersupplytype = powersupply.powersupplytype;
	power = powersupply.power;
	efficiency = powersupply.efficiency;
	PFC = powersupply.PFC;
	return *this;
}

Hardware* PowerSupply::Clone() const
{
	PowerSupply* powersupply = new PowerSupply;
	*powersupply = *this;
	return powersupply;
}


//HDD Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

HDD::HDD() : Hardware(informationcount) {}

Array<HDD**>& HDD::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetHDDArray();
}

int HDD::GetInformationcount()
{
	return informationcount;
}

std::string HDD::getStatType()
{
	return type;
}

void HDD::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& HDD::GetSetters()
{
	
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new HDDcapacitySetter(this), new HDDRPMSetter(this), new HDDdiameterSetter(this), new HDDconnectorSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new HDDcapacitySetter(this), new HDDRPMSetter(this), new HDDdiameterSetter(this), new HDDconnectorSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void HDD::SetCapacity(const std::string capacity)
{
	if(!isStringEmpty(capacity) && !isContainSplit(capacity))
	this->capacity = capacity;
}
void HDD::SetRPM(const std::string RPM)
{
	if(!isStringEmpty(RPM) && !isContainSplit(RPM))
	this->RPM = RPM;
}
void HDD::SetDiameter(const std::string diameter)
{
	if(!isStringEmpty(diameter) && !isContainSplit(diameter))
	this->diameter = diameter;
}
void HDD::SetConnector(const std::string connector)
{
	if(!isStringEmpty(connector) && !isContainSplit(connector))
	this->connector = connector;
}

void HDD::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddHDD(this);
}

void HDD::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = capacity;
		stringarray[5] = RPM;
		stringarray[6] = diameter;
		stringarray[7] = connector;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = capacity;
		stringarray[2] = RPM;
		stringarray[3] = diameter;
		stringarray[4] = connector;
		stringarray[5] = "#" + std::to_string(id);
		stringarray[6] = std::to_string(db);
	}
}

HDD& HDD::operator=(const HDD& hdd)
{
	id = hdd.id;
	db = hdd.db;
	name = hdd.name;
	state = hdd.state;
	statebefore = hdd.statebefore;
	capacity = hdd.capacity;
	RPM = hdd.RPM;
	diameter = hdd.diameter;
	connector = hdd.connector;
	return *this;
}

Hardware* HDD::Clone() const
{
	HDD* hdd = new HDD;
	*hdd = *this;
	return hdd;
}


//SSD Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

SSD::SSD() : Hardware(informationcount) {}

Array<SSD**>& SSD::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetSSDArray();
}

int SSD::GetInformationcount()
{
	return informationcount;
}

std::string SSD::getStatType()
{
	return type;
}

void SSD::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& SSD::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new SSDcapacitySetter(this), new SSDNANDflashSetter(this), new SSDconnectorSetter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new SSDcapacitySetter(this), new SSDNANDflashSetter(this), new SSDconnectorSetter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void SSD::SetCapacity(const std::string capacity)
{
	if(!isStringEmpty(capacity) && !isContainSplit(capacity))
	this->capacity = capacity;
}
void SSD::SetNANDflash(const std::string NANDflash)
{
	if(!isStringEmpty(NANDflash) && !isContainSplit(NANDflash))
	this->NANDflash = NANDflash;
}
void SSD::SetConnector(const std::string connector)
{
	if(!isStringEmpty(connector) && !isContainSplit(connector))
	this->connector = connector;
}

void SSD::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddSSD(this);
}

void SSD::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = capacity;
		stringarray[5] = NANDflash;
		stringarray[6] = connector;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = capacity;
		stringarray[2] = NANDflash;
		stringarray[3] = connector;
		stringarray[4] = "#" + std::to_string(id);
		stringarray[5] = std::to_string(db);
	}
}

SSD& SSD::operator=(const SSD& ssd)
{
	id = ssd.id;
	db = ssd.db;
	name = ssd.name;
	state = ssd.state;
	statebefore = ssd.statebefore;
	capacity = ssd.capacity;
	NANDflash = ssd.NANDflash;
	connector = ssd.connector;
	return *this;
}

Hardware* SSD::Clone() const
{
	SSD* ssd = new SSD;
	*ssd = *this;
	return ssd;
}


//ComputerCase Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

ComputerCase::ComputerCase() : Hardware(informationcount) {}

Array<ComputerCase**>& ComputerCase::GetOwnArray(HardwareStorage* const hardwarestorage)
{
	return hardwarestorage->GetComputerCaseArray();
}

int ComputerCase::GetInformationcount()
{
	return informationcount;
}

std::string ComputerCase::getStatType()
{
	return type;
}

void ComputerCase::GetStatMenuPoints(std::string* stringarray)
{
	for (size_t i = 0; i < informationcount + 1; i++)
		stringarray[i] = menupoints[i];
}

Array<Setters**>& ComputerCase::GetSetters()
{
	if (state != statebefore)
	{
		statebefore = state;
		setters.Clear();
		setters.CreateArray(informationcount + baseinformationcount);
		if (state == Hardware::State::Load)
		{
			Setters* setterarray[informationcount + baseinformationcount] = { new HardwareIdSetter(this), new HardwareDbSetter(this), new HardwareNameSetter(this), new ComputerCaseweightSetter(this), new ComputerCaseFormfactorSetter(this), new ComputerCaseventsSetter(this), new ComputerCaseDrive3dot5Setter(this), new ComputerCaseDrive2dot5Setter(this) };
			setters.Upload(setterarray, informationcount + baseinformationcount);
		}
		else if (state == Hardware::State::Input)
		{
			Setters* setterarray[informationcount + 1] = { new HardwareNameSetter(this), new ComputerCaseweightSetter(this), new ComputerCaseFormfactorSetter(this), new ComputerCaseventsSetter(this), new ComputerCaseDrive3dot5Setter(this), new ComputerCaseDrive2dot5Setter(this) };
			setters.Upload(setterarray, informationcount + 1);
		}
	}
	return setters;
}

void ComputerCase::SetWeight(const std::string weight)
{
	if(!isStringEmpty(weight) && !isContainSplit(weight))
	this->weight = weight;
}
void ComputerCase::SetFormfactor(const std::string Formfactor)
{
	if(!isStringEmpty(Formfactor) && !isContainSplit(Formfactor))
	this->Formfactor = Formfactor;
}
void ComputerCase::SetVents(const std::string vents)
{
	if(!isStringEmpty(vents) && !isContainSplit(vents))
	this->vents = vents;
}
void ComputerCase::SetDrive3dot5(const std::string Drive3dot5)
{
	if(!isStringEmpty(Drive3dot5) && !isContainSplit(Drive3dot5))
	this->Drive3dot5 = Drive3dot5;
}
void ComputerCase::SetDrive2dot5(const std::string Drive2dot5)
{
	if(!isStringEmpty(Drive2dot5) && !isContainSplit(Drive2dot5))
	this->Drive2dot5 = Drive2dot5;
}

void ComputerCase::AddItself(HardwareStorage* const hardwarestorage)
{
	hardwarestorage->AddComputerCase(this);
}

void ComputerCase::FormatInfo(std::string* stringarray)
{
	if (state == Hardware::State::Load)
	{
		stringarray[0] = type;
		stringarray[1] = "#" + std::to_string(id);
		stringarray[2] = std::to_string(db);
		stringarray[3] = name;
		stringarray[4] = weight;
		stringarray[5] = Formfactor;
		stringarray[6] = vents;
		stringarray[7] = Drive3dot5;
		stringarray[8] = Drive2dot5;
	}
	if (state == Hardware::State::Print)
	{
		stringarray[0] = name;
		stringarray[1] = weight;
		stringarray[2] = Formfactor;
		stringarray[3] = vents;
		stringarray[4] = Drive3dot5;
		stringarray[5] = Drive2dot5;
		stringarray[6] = "#" + std::to_string(id);
		stringarray[7] = std::to_string(db);
	}
}

ComputerCase& ComputerCase::operator=(const ComputerCase& computercase)
{
	id = computercase.id;
	db = computercase.db;
	name = computercase.name;
	state = computercase.state;
	statebefore = computercase.statebefore;
	weight = computercase.weight;
	Formfactor = computercase.Formfactor;
	vents = computercase.vents;
	Drive2dot5 = computercase.Drive2dot5;
	Drive3dot5 = computercase.Drive3dot5;
	return *this;
}

Hardware* ComputerCase::Clone() const
{
	ComputerCase* computercase = new ComputerCase;
	*computercase = *this;
	return computercase;
}