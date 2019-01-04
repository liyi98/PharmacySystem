#include "pch.h"
#include "Order.h"

vector<Order> Order::orders;


Order::Order(int cus_id, string date) {
	Order::cus_id = cus_id;
	Order::date = date;
	Order ::orderid= (orders.size() > 0) ? orders.back().getOrderID() + 1 : 1;
}

Order::Order(int orderid, int cus_id, string date) {
	Order::cus_id = cus_id;
	Order::orderid = orderid;
	Order::date = date;
	
}
string Order::getDate() {
	return Order::date;
}

int Order::getCus_id() {
	return Order::cus_id;
}

int Order::getOrderID() {
	return Order::orderid;
}

int Order::findIndex(int orderid) {
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i].getOrderID() == orderid) {
			return i;
		}
	}
	return -1;
}



vector<Order> Order::findCustomerOrder(int cus_id) {
	vector<Order> idOrder;
	int i = 0;
	for (Order order : orders) {
		if (order.getCus_id() == cus_id) {
			idOrder.push_back(Order(order.orderid, order.cus_id, order.date));
			for (OrderItem item : order.orderItems) {
				idOrder[i].orderItems.push_back(item);
			}
			i++;
		}
	}
	return idOrder;
}

void Order::save() {
	ofstream myfile("Order.txt");
	ofstream myOrderItem("OrderItem.txt");
	for (int i = 0; i < orders.size(); i++) {
		myfile << orders[i].getOrderID() << "|";
		myfile << orders[i].getCus_id() << "|";
		myfile << orders[i].getDate() << endl;
		for (OrderItem orderitem : orders[i].orderItems) {
			myOrderItem << orderitem.getOrderID() << "|";
			myOrderItem << orderitem.getMed_id() << "|";
			myOrderItem << orderitem.getQuantity() << endl;
		}
	}
}

void Order::load() {
	ifstream myfile("Order.txt");
	ifstream myOrderItem("OrderItem.txt");
	string line;
	string data[3] = {};
	while (getline(myfile, line))
	{
		stringstream ss(line);
		for (int i = 0; getline(ss, data[i], '|'); i++);
		Order o(stoi(data[0]), stoi(data[1]), data[2]);
		orders.push_back(o);
	}
	while (getline(myOrderItem, line)) {
		stringstream ss(line);
		for (int i = 0; getline(ss, data[i], '|'); i++);
		Order::orders[Order::findIndex(stoi(data[0]))].orderItems.push_back(OrderItem(stoi(data[0]), stoi(data[1]), stoi(data[2])));
	}
}
