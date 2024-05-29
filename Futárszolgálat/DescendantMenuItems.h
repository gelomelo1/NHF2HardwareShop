#pragma once
#include "memtrace.h"
#include "Menu.h"
#include "MenuItem.h"

class LoginItem : public MenuItem
{

public:
	LoginItem(const std::string castname);

	void Task(MenuContainer* container);
};

class RegisterItem : public MenuItem
{

public:
	RegisterItem(const std::string castname);

	void Task(MenuContainer* container);
};

class AccountList : public MenuItem
{

public:
	AccountList();

	void Task(MenuContainer* container);
};

class OrderListAdmin : public MenuItem
{

public:
	OrderListAdmin();

	void Task(MenuContainer* container);
};

class StorageList : public MenuItem
{

public:
	StorageList();

	void Task(MenuContainer* container);
};

class NewHardware : public MenuItem
{

public:
	NewHardware();

	void Task(MenuContainer* container);
};

class ExitItem : public MenuItem
{

public:
	ExitItem();

	void Task(MenuContainer* container);
};

class CustomerDelete : public MenuItem
{

public:
	CustomerDelete();

	void Task(MenuContainer* container);
};

class OrderDeleteAdmin : public MenuItem
{
public:
	OrderDeleteAdmin();

	void Task(MenuContainer* container);
};

class OrderShip : public MenuItem
{
public:
	OrderShip();

	void Task(MenuContainer* container);
};

class AdminSelfDelete : public MenuItem
{

public:
	AdminSelfDelete();

	void Task(MenuContainer* container);
};

class NewCPU : public MenuItem
{
public:
	NewCPU();

	void Task(MenuContainer* container);
};

class NewGPU : public MenuItem
{
public:
	NewGPU();

	void Task(MenuContainer* container);
};

class NewMemory : public MenuItem
{
public:
	NewMemory();

	void Task(MenuContainer* container);
};

class NewMotherboard : public MenuItem
{
public:
	NewMotherboard();

	void Task(MenuContainer* container);
};

class NewPowerSupply : public MenuItem
{
public:
	NewPowerSupply();

	void Task(MenuContainer* container);
};

class NewHDD : public MenuItem
{
public:
	NewHDD();

	void Task(MenuContainer* container);
};

class NewSSD : public MenuItem
{
public:
	NewSSD();

	void Task(MenuContainer* container);
};

class NewComputerCase : public MenuItem
{
public:
	NewComputerCase();

	void Task(MenuContainer* container);
};

class HardwareIncrease : public MenuItem
{
public:
	HardwareIncrease();

	void Task(MenuContainer* container);
};

class HardwareDecrease : public MenuItem
{
public:
	HardwareDecrease();

	void Task(MenuContainer* container);
};

class CPUList : public MenuItem
{
public:
	CPUList();

	void Task(MenuContainer* container);
};

class GPUList : public MenuItem
{
public:
	GPUList();

	void Task(MenuContainer* container);
};

class MemoryList : public MenuItem
{
public:
	MemoryList();

	void Task(MenuContainer* container);
};

class MotherboardList : public MenuItem
{
public:
	MotherboardList();

	void Task(MenuContainer* container);
};

class PowerSupplyList : public MenuItem
{
public:
	PowerSupplyList();

	void Task(MenuContainer* container);
};

class HDDList : public MenuItem
{
public:
	HDDList();

	void Task(MenuContainer* container);
};

class SSDList  : public MenuItem
{
public:
	SSDList();

	void Task(MenuContainer* container);
};

class ComputerCaseList : public MenuItem
{
public:
	ComputerCaseList();

	void Task(MenuContainer* container);
};

class StorageLoad : public MenuItem
{
public:
	StorageLoad();

	void Task(MenuContainer* container);
};

class CustomerSelfDelete : public MenuItem
{
public:
	CustomerSelfDelete();

	void Task(MenuContainer* container);
};

class OrderListCustomer : public MenuItem
{
public:
	OrderListCustomer();

	void Task(MenuContainer* container);
};

class WebshopOpen : public MenuItem
{
public:
	WebshopOpen();

	void Task(MenuContainer* container);
};

class OrderDeleteCustomer : public MenuItem
{
public:
	OrderDeleteCustomer();

	void Task(MenuContainer* container);
};

class OrderRecieve : public MenuItem
{
public:
	OrderRecieve();

	void Task(MenuContainer* container);
};

class WebshopCPU : public MenuItem
{
public:
	WebshopCPU();

	void Task(MenuContainer* container);
};

class WebshopGPU : public MenuItem
{
public:
	WebshopGPU();

	void Task(MenuContainer* container);
};

class WebshopMemory : public MenuItem
{
public:
	WebshopMemory();

	void Task(MenuContainer* container);
};

class WebshopMotherboard : public MenuItem
{
public:
	WebshopMotherboard();

	void Task(MenuContainer* container);
};

class WebshopPowerSupply : public MenuItem
{
public:
	WebshopPowerSupply();

	void Task(MenuContainer* container);
};

class WebshopHDD : public MenuItem
{
public:
	WebshopHDD();

	void Task(MenuContainer* container);
};

class WebshopSSD : public MenuItem
{
public:
	WebshopSSD();

	void Task(MenuContainer* container);
};

class WebshopComputerCase : public MenuItem
{
public:
	WebshopComputerCase();

	void Task(MenuContainer* container);
};

class OrderEmpty : public MenuItem
{
public:
	OrderEmpty();

	void Task(MenuContainer* container);
};

class OrderFinish : public MenuItem
{
public:
	OrderFinish();

	void Task(MenuContainer* container);
};

class AddHardwareToOrder : public MenuItem
{
public:
	AddHardwareToOrder();

	void Task(MenuContainer* container);
};