#include "pch.h"
#ifndef Order_H
#define Order_H

#include <iostream>
#include <vector>
#include "string"
#include "OrderItem.h"
#include <ctime>

using namespace std;

class Order {
	private:
		string date;
		int cus_id, orderid;
		
	public:
		vector<OrderItem> orderItems;
		static vector<Order> orders;
		Order(int cus_id, string date);
		Order(int orderid, int cus_id, string date);
		string getDate();
		int getCus_id();
		int getOrderID();
		static int findIndex(int orderid);
		static vector<Order> findCustomerOrder(int cus_id);
		static void save();
		static void load();
};



#endif
