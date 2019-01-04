#include "pch.h"
#ifndef Customer_H
#define Customer_H

#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class Customer : public User {

	public:
		Customer();
		Customer(string username, string password, string name, string address, string tel);
};

#endif
