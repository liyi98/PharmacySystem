#include "pch.h"
#ifndef OrderItem_H
#define OrderItem_H

#include <iostream>
#include <vector>
#include "Medicine.h"
#include "string"

using namespace std;

class OrderItem {
	private:
		int med_id, quantity, orderID;
	public:
		OrderItem(int orderID, int med_id, int quantity);
		int getOrderID();
		int getMed_id();
		int getQuantity();
		double subTotal();
		void setMedicine(int med_id);
		void setQuantity(int quantity);
};


#endif