#include "OrdersPerUser.h"


//OrdersPerUser osztaly fuggvenyek/////////////////////////////////////////////////////////////////////////////////////////////////////////

OrdersPerUser::OrdersPerUser(const std::string customername) : orders(false), customername(customername) {}

Array<Order**>& OrdersPerUser::GetOrders()
{
	return orders;
}
std::string OrdersPerUser::GetCustomername() const
{
	return customername;
}
void OrdersPerUser::SetCustomername(const std::string customername)
{
	this->customername = customername;
}
void OrdersPerUser::AddOrder(Order* order)
{
	orders.Upload(order);
}

void OrdersPerUser::FormatInfo(Order* order, std::string* stringarray)
{
	stringarray[0] = customername;
	order->OrderEncode(stringarray[1], ", ");
		if (order->GetState() == Order::State::RecievedOrder)
			stringarray[2] = "Beerkezett rendeles";
		else if (order->GetState() == Order::State::Shipped)
			stringarray[2] = "Atvetelre var";
		else if (order->GetState() == Order::State::Successful)
			stringarray[2] = "Sikeres kezbesites";
}

size_t OrdersPerUser::GetNewId() const
{
	size_t newid = 0;
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (orders[i]->GetOrderId() == newid)
		{
			newid++;
			i = 0;
		}
	}
	return newid;
}