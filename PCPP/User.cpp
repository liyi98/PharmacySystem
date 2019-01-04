#include "pch.h"
#include "User.h"

vector<User> User::users;

User::User() {}

User::User(string username, string password, string name, string address, string tel, int roles) {
	User::username = username;
	User::password = password;
	User::name = name; 
	User::address = address;
	User::tel = tel;
	User::roles = roles;
	User::id = users.back().getID() + 1;		
}

User::User(int id, string username, string password, string name, string address, string tel, int roles) {
	User::id = id;
	User::username = username;
	User::password = password;
	User::name = name;
	User::address = address;
	User::tel = tel;
	User::roles = roles;

}

int User::getID(){
	return User::id;
}

string User::getUsername() {
	return User::username;
}

void User::setUsername(string username) {
	User::username = username;
}

string User::getPassword() {
	return User::password;
}

void User::setPassword(string password) {
	User::password = password;
}

string User::getName() {
	return User::name;
}

void User::setName(string name) {
	User::name = name;
}

string User::getAddress() {
	return User::address;
}

void User::setAddress(string address) {
	User::address = address;
}

string User::getTel() {
	return User::tel;
}

void User::setTel(string tel) {
	User::tel = tel;
}
int User::getRole() {
	return User::roles;
}

int User::findIndex(int cus_id) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == cus_id) {
			return i;
		}
	}
	return -1;
}
void User::setRoles(int roles) {
	User::roles = roles;
}

void User::addUser(User user) {
	users.push_back(user);
}

void User::delUser(int id) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == id) {
			users.erase(users.begin() + i);
		}
	}
}

void User::save() {
	ofstream myfile ("User.txt");
	for (int i = 0; i < users.size(); i++) {
		myfile << users[i].getID() << "|";
		myfile << users[i].getUsername() << "|";
		myfile << users[i].getPassword() << "|";
		myfile << users[i].getName() << "|";
		myfile << users[i].getAddress() << "|";
		myfile << users[i].getTel() << "|";
		myfile << users[i].getRole() << "\n";
	}
}

void User::load() {
	ifstream myfile("User.txt");
	string line;
	string data[7] = {};
	while (getline(myfile, line))
	{
		stringstream ss(line);
		for (int i = 0; getline(ss, data[i], '|'); i++);
		users.push_back(User(stoi(data[0]), data[1], data[2], data[3], data[4], data[5], stoi(data[6])));	
	}
	
}