#include "pch.h"
#include "Customer.h"


Customer::Customer() {}

Customer::Customer(string username, string password, string name, string address, string tel) : User(username, password, name, address, tel, 0) {
}




