#include "pch.h"
#ifndef Header_H
#define Header_H

#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class Admin: public User{

public:
	Admin();
	Admin(string username, string password, string name, string address, string tel);

};
#endif // !Header_H

