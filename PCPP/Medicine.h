#include "pch.h"
#ifndef Medicine_H
#define Medicine_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "string"
#include "Date.h"
using namespace std;

class Medicine {
private:
	string name, company, manuDate, expDate;
	int id;
	double price;
public:
	static vector<Medicine> medicines;
	Medicine();
	Medicine(string name, string company, double price, string manuDate, string expDate);
	Medicine(int id, string name, string company, double price, string manuDate, string expDate);
	int getID();
	string getName();
	string getCompany();
	double getPrice();
	string getManuDate();
	string getExpDate();
	static int getIndex(int id);
	static int checkIDisvalid(int id);
	static vector<Medicine> searchById(int id);
	static vector<Medicine> searchByName(string name);
	static vector<Medicine> searchByYear(int year);
	static vector<Medicine> searchByMonth(int year, int month);
	void setName(string name);
	void setCompany(string company);
	void setPrice(double price);
	void setManuDate(string ManuDate);
	void setExpDate(string ExpDate);
	static void delMedicine(int id);
	static void save();
	static void load();
};

#endif
