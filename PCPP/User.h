#include "pch.h"
#ifndef User_H
#define User_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Order.h"
using namespace std;

class User {
	private:
		string username, password, name, address, tel;
		int id, roles;
	public:
		static vector<User> users;
		User();
		User(string username, string password, string name, string address, string tel, int roles);
		User(int id, string username, string password, string name, string address, string tel, int roles);
		int getID();
		string getUsername();
		string getPassword();
		string getName();
		string getAddress();
		string getTel();
		int getRole();
		static int findIndex(int cus_id);
		void setUsername(string username);
		void setPassword(string password);
		void setName(string name);
		void setAddress(string address);
		void setTel(string tel);
		void setRoles(int roles);
		void addUser(User user);
		void delUser(int id);
		static void save();
		static void load();
};


#endif // !Header_H
#pragma once
