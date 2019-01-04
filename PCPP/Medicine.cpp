#include "pch.h"
#include "Medicine.h"

vector<Medicine> Medicine::medicines;

Medicine::Medicine() {
}
Medicine::Medicine(string name, string company, double price, string manuDate, string expDate) {
	Medicine::name = name;
	Medicine::company = company;
	Medicine::price = price;
	Medicine::manuDate = manuDate;
	Medicine::expDate = expDate;
	Medicine::id = (medicines.size() > 0) ? medicines.back().getID() + 1 : 1;
}

Medicine::Medicine(int id, string name, string company, double price, string manuDate, string expDate) {
	Medicine::id = id;
	Medicine::name = name;
	Medicine::company = company;
	Medicine::price = price;
	Medicine::manuDate = manuDate;
	Medicine::expDate = expDate;
}

int Medicine::getID() {
	return Medicine::id;
}

string Medicine::getName() {
	return Medicine::name;
}

void Medicine::setName(string name) {
	Medicine::name = name;
}

string Medicine::getCompany() {
	return Medicine::company;
}

void Medicine::setCompany(string company) {
	Medicine::company = company;
}

double Medicine::getPrice() {
	return Medicine::price;
}

void Medicine::setPrice(double price) {
	Medicine::price = price;
}

string Medicine::getManuDate() {
	return Medicine::manuDate;
}

void Medicine::setManuDate(string manuDate) {
	Medicine::manuDate = manuDate;
}


string Medicine::getExpDate() {
	return Medicine::expDate;
}

void Medicine::setExpDate(string expDate) {
	Medicine::expDate = expDate;
}

int Medicine::getIndex(int id) {
	for (int i = 0; i < medicines.size(); i++) {
		if (medicines[i].getID() == id) {
			return i;
		}
	}
	return -1;
}

int Medicine::checkIDisvalid(int id) {
	for (Medicine medicine : Medicine::medicines) {
		if (medicine.getID() == id){
			return 1;
		}
	}
	return -1;
}
void Medicine::delMedicine(int id) {
	for (int i = 0; i < medicines.size(); i++) {
		if (medicines[i].getID() == id) {
			medicines.erase(medicines.begin() + i);
		}
	}
}

vector<Medicine> Medicine::searchById(int id) {
	vector<Medicine> idMedicines;
	for (int i = 0; i < medicines.size(); i++) {
		if (to_string(medicines[i].getID()).find(to_string(id)) != string::npos) {
			idMedicines.push_back(Medicine(medicines[i].getID(), medicines[i].getName() , medicines[i].getCompany(), medicines[i].getPrice(), medicines[i].getManuDate(), medicines[i].getExpDate()));
		}
	}
	return idMedicines;
}

vector<Medicine> Medicine::searchByName(string name) {
	vector<Medicine> nameMedicines;
	for (int i = 0; i < medicines.size(); i++) {
		if (medicines[i].getName().find(name) != string::npos) {
			nameMedicines.push_back(Medicine(medicines[i].getID(), medicines[i].getName(), medicines[i].getCompany(), medicines[i].getPrice(), medicines[i].getManuDate(), medicines[i].getExpDate()));
		}
	}
	return nameMedicines;
}

vector<Medicine> Medicine::searchByYear(int year) {
	vector<Medicine> yMedicines;
	for (int i = 0; i < medicines.size(); i++) {
		if (Date::StringToDate(medicines[i].getExpDate()).year == year) {
			yMedicines.push_back(Medicine(medicines[i].getID(), medicines[i].getName(), medicines[i].getCompany(), medicines[i].getPrice(), medicines[i].getManuDate(), medicines[i].getExpDate()));
		}
	}
	return yMedicines;
}

vector<Medicine> Medicine::searchByMonth(int year, int month) {
	vector<Medicine> mMedicines;
	for (int i = 0; i < medicines.size(); i++) {
		if (Date::StringToDate(medicines[i].getExpDate()).year == year && Date::StringToDate(medicines[i].getExpDate()).month == month) {
			mMedicines.push_back(Medicine(medicines[i].getID(), medicines[i].getName(), medicines[i].getCompany(), medicines[i].getPrice(), medicines[i].getManuDate(), medicines[i].getExpDate()));
		}
	}
	return mMedicines;
}


void Medicine::save() {
	ofstream myFile("Medicine.txt");
	for (int i = 0; i < medicines.size(); i++) {
		myFile << medicines[i].getID() << "|";
		myFile << medicines[i].getName() << "|";
		myFile << medicines[i].getCompany() << "|";
		myFile << medicines[i].getPrice() << "|" ;
		myFile << medicines[i].getManuDate() << "|";
		myFile << medicines[i].getExpDate() << "\n";
	}
}

void Medicine::load() {
	ifstream myFile("Medicine.txt");
	string line;
	string data[6] = {};
	while (getline(myFile,line)) {
		stringstream ss(line);
		for (int i = 0; getline(ss, data[i], '|'); i++);
		medicines.push_back(Medicine(stoi(data[0]), data[1], data[2], stod(data[3]), data[4], data[5]));
	}
}