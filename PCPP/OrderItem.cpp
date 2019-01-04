#include "pch.h"
#include "OrderItem.h"

OrderItem::OrderItem(int orderID, int med_id, int quantity) {
	OrderItem::orderID = orderID;
	OrderItem::med_id = med_id;
	OrderItem::quantity = quantity;
}

int OrderItem::getMed_id() {
	return OrderItem::med_id;
}

int OrderItem::getOrderID() {
	return OrderItem::orderID;
}

void OrderItem::setMedicine(int med_id) {
	OrderItem::med_id = med_id;
}

int OrderItem::getQuantity() {
	return OrderItem::quantity;
}

double OrderItem::subTotal() {
	int med_index = Medicine::getIndex(OrderItem::med_id);
	double subtotal = Medicine::medicines[med_index].getPrice() * OrderItem::getQuantity();
	return subtotal;
}
void OrderItem::setQuantity(int quantity) {
	OrderItem::quantity = quantity;
}