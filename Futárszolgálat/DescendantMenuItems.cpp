#include "memtrace.h"
#include "DescendantMenuItems.h"


//ExitItem Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

ExitItem::ExitItem() : MenuItem("")
{
	name = "Kilepes";
}

void ExitItem::Task(MenuContainer* container)
{
	container->ExitMenu();
}


//LoginItem Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

LoginItem::LoginItem(const std::string castname) :MenuItem(castname)
{
	name = "Belepes";
}

void LoginItem::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AccountMenu* Amcontainer = static_cast<AccountMenu*>(container);
		Amcontainer->LoginProcess();
	}
	else
		throw InvalidProcess("Csak AccountMenuben hozhato letre ez a menupont");
}


//RegisterItem Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

RegisterItem::RegisterItem(const std::string castname) : MenuItem(castname)
{
	name = "Regisztracio";
}

void RegisterItem::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AccountMenu* Amcontainer = static_cast<AccountMenu*>(container);
		Amcontainer->RegistrationProcess();
	}
	else
		throw InvalidProcess("Csak AccountMenuben hozhato letre ez a menupont");
}


//AccountList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

AccountList::AccountList() : MenuItem(AdminMenu::getStatType())
{
	name = "Vasarlok listazasa";
}

void AccountList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->ListAccounts();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}


//OrderListAdmin Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderListAdmin::OrderListAdmin() : MenuItem(AdminMenu::getStatType())
{
	name = "Rendelesek listazasa";
}

void OrderListAdmin::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->ListOrders();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}

//StorageList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

StorageList::StorageList() : MenuItem(AdminMenu::getStatType())
{
	name = "Raktar listazasa";
}

void StorageList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->AddStorageProcess();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}

//NewHardware Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewHardware::NewHardware() : MenuItem(AdminMenu::getStatType())
{
	name = "Uj hardver hozzadasa";
}

void NewHardware::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->AddHardwareProcess();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}

//AdminSelfDelete Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

AdminSelfDelete::AdminSelfDelete() : MenuItem(AdminMenu::getStatType())
{
	name = "Felhasznalo torlese";
}

void AdminSelfDelete::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->DeleteSelf();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}


//CustomerDelete Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

CustomerDelete::CustomerDelete() : MenuItem(AdminMenu::getStatType())
{
	name = "Vasarlo torlese";
}

void CustomerDelete::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->DeleteCustomer();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}


//OrderDeleteAdmin Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderDeleteAdmin::OrderDeleteAdmin() : MenuItem(AdminMenu::getStatType())
{
	name = "Rendeles torlese";
}

void OrderDeleteAdmin::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->DeleteOrder();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}


//OrderShip Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderShip::OrderShip() : MenuItem(AdminMenu::getStatType())
{
	name = "Rendeles kezbesitese";
}

void OrderShip::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		AdminMenu* Adcontainer = static_cast<AdminMenu*>(container);
		Adcontainer->ShipOrder();
	}
	else
		throw InvalidProcess("Csak AdminMenuben hozhato letre ez a menupont");
}


//NewCPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewCPU::NewCPU() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Processzor";
}

void NewCPU::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<CPU>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewGPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewGPU::NewGPU() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Videokartya";
}

void NewGPU::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<GPU>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewMemory Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewMemory::NewMemory() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Memoria";
}

void NewMemory::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<Memory>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewMotherboard Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewMotherboard::NewMotherboard() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Alaplap";
}

void NewMotherboard::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<Motherboard>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewPowerSupply Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewPowerSupply::NewPowerSupply() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Tapegyseg";
}

void NewPowerSupply::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<PowerSupply>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewHDD Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewHDD::NewHDD() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Merevlemez";
}

void NewHDD::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<HDD>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewSSD Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewSSD::NewSSD() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "SSD";
}

void NewSSD::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<SSD>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//NewComputerCase Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

NewComputerCase::NewComputerCase() : MenuItem(HardwareProcessSubMenu::getStatType())
{
	name = "Gephaz";
}

void NewComputerCase::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		HardwareProcessSubMenu* Hardwarecontainer = static_cast<HardwareProcessSubMenu*>(container);
		Hardwarecontainer->AddHardware<ComputerCase>();
	}
	else
		throw InvalidProcess("Csak HardwareProcessSubMenuben hozhato letre ez a menupont");
}


//HardwareIncrease Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

HardwareIncrease::HardwareIncrease() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Hardver hozzadasa(+1)";
}

void HardwareIncrease::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->IncreaseHardware();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//HardwareDecrease Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

HardwareDecrease::HardwareDecrease() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Hardver elvetele(-1)";
}

void HardwareDecrease::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->DecreaseHardware();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//CPUList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

CPUList::CPUList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Processzor";
}

void CPUList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<CPU>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//GPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

GPUList::GPUList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Videokartya";
}

void GPUList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<GPU>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//MemoryList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

MemoryList::MemoryList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Memoria";
}

void MemoryList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<Memory>();

	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//MotherboardList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

MotherboardList::MotherboardList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Alaplap";
}

void MotherboardList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<Motherboard>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//PowerSupplyList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

PowerSupplyList::PowerSupplyList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Tapegyseg";
}

void PowerSupplyList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<PowerSupply>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//HDDList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

HDDList::HDDList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Merevlemez";
}

void HDDList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<HDD>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//SSDList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

SSDList::SSDList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "SSD";
}

void SSDList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<SSD>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//ComputerCaseList Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

ComputerCaseList::ComputerCaseList() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Gephaz";
}

void ComputerCaseList::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->ListHardware<ComputerCase>();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//StorageLoad Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

StorageLoad::StorageLoad() : MenuItem(StorageProcessSubMenu::getStatType())
{
	name = "Raktar feltoltese";
}

void StorageLoad::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		StorageProcessSubMenu* Storagecontainer = static_cast<StorageProcessSubMenu*>(container);
		Storagecontainer->LoadStorage();
	}
	else
		throw InvalidProcess("Csak StorageProcessSubMenuben hozhato letre ez a menupont");
}


//OrderListCustomer Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderListCustomer::OrderListCustomer() : MenuItem(CustomerMenu::getStatType())
{
	name = "Rendelesek listazasa";
}

void OrderListCustomer::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		CustomerMenu* Cucontainer = static_cast<CustomerMenu*>(container);
		Cucontainer->ListOrders();
	}
	else
		throw InvalidProcess("Csak CustomerMenuben hozhato letre ez a menupont");
}


//WebshopOpen Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopOpen::WebshopOpen() : MenuItem(CustomerMenu::getStatType())
{
	name = "Bolt megnyitasa";
}

void WebshopOpen::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		CustomerMenu* Cucontainer = static_cast<CustomerMenu*>(container);
		Cucontainer->AddWebshopProcess();
	}
	else
		throw InvalidProcess("Csak CustomerMenuben hozhato letre ez a menupont");
}


//CustomerSelfDelete Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

CustomerSelfDelete::CustomerSelfDelete() : MenuItem(CustomerMenu::getStatType())
{
	name = "Felhasznalo torlese";
}

void CustomerSelfDelete::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		CustomerMenu* Cucontainer = static_cast<CustomerMenu*>(container);
		Cucontainer->DeleteSelf();
	}
	else
		throw InvalidProcess("Csak CustomerMenuben hozhato letre ez a menupont");
}


//OrderDeleteCustomer Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderDeleteCustomer::OrderDeleteCustomer() : MenuItem(CustomerMenu::getStatType())
{
	name = "Rendeles torlese";
}

void OrderDeleteCustomer::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		CustomerMenu* Cucontainer = static_cast<CustomerMenu*>(container);
		Cucontainer->DeleteOrder();
	}
	else
		throw InvalidProcess("Csak CustomerMenuben hozhato letre ez a menupont");
}


//OrderRecieve Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderRecieve::OrderRecieve() : MenuItem(CustomerMenu::getStatType())
{
	name = "Rendeles atvetele";
}

void OrderRecieve::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		CustomerMenu* Cucontainer = static_cast<CustomerMenu*>(container);
		Cucontainer->RecieveOrder();
	}
	else
		throw InvalidProcess("Csak CustomerMenuben hozhato letre ez a menupont");
}


//WebshopCPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopCPU::WebshopCPU() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Processzor";
}

void  WebshopCPU::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<CPU>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopGPU Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopGPU::WebshopGPU() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Videokartya";
}

void  WebshopGPU::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<GPU>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopMemory Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopMemory::WebshopMemory() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Memoria";
}

void  WebshopMemory::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<Memory>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopMotherboard Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopMotherboard::WebshopMotherboard() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Alaplap";
}

void  WebshopMotherboard::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<Motherboard>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopPowerSupply Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopPowerSupply::WebshopPowerSupply() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Tapegyseg";
}

void  WebshopPowerSupply::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<PowerSupply>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopHDD Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopHDD::WebshopHDD() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Merevlemez";
}

void  WebshopHDD::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<HDD>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopSSD Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopSSD::WebshopSSD() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "SSD";
}

void  WebshopSSD::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<SSD>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//WebshopComputerCase Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

WebshopComputerCase::WebshopComputerCase() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Gephaz";
}

void  WebshopComputerCase::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->ListWebshop<ComputerCase>();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//OrderEmpty Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderEmpty::OrderEmpty() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Kosar uretese";
}

void  OrderEmpty::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->EmptyOrder(false);
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//OrderFinish Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrderFinish::OrderFinish() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Rendeles leadasa";
}

void  OrderFinish::Task(MenuContainer* container)
{
	if (container->getType() == castname)
	{
		WebshopProcessSubMenu* Wecontainer = static_cast<WebshopProcessSubMenu*>(container);
		Wecontainer->FinishOrder();
	}
	else
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}


//AddHardwareToOrder Leszarmazott osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

AddHardwareToOrder::AddHardwareToOrder() : MenuItem(WebshopProcessSubMenu::getStatType())
{
	name = "Hardver hozzadasa a kosarhoz(+1)";
}

void  AddHardwareToOrder::Task(MenuContainer* container)
{
	if (container->getType() != castname)
		throw InvalidProcess("Csak WebshopProcessSubMenuben hozhato letre ez a menupont");
}

