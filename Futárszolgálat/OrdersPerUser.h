#pragma once
#include "GeneralFunctions.h"
#include "Order.h"

class OrdersPerUser
{
	Array<Order**> orders;
	std::string customername;
public:
	OrdersPerUser(const std::string customername);
	void AddOrder(Order* order);
	Array<Order**>& GetOrders();
	std::string GetCustomername() const;
	void FormatInfo(Order* order, std::string* stringarray);
	void SetCustomername(const std::string customername);
	size_t GetNewId() const;
};