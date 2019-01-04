#include "pch.h"
#include "Activities.h"


string option;
bool logout = false;


MainActivity::MainActivity() {
	option = "";
	while(true) {
		if (option == "1") {
			Login();
		}else if (option == "2") {
			Register();
		}
		else if (option == "0") {
			break;
		}else {
			cout << "Welcome To Pharmacy System" << endl;
			cout << "Please Select An Option" << endl;
			cout << "1. Login \n2. Register\n0. Exit" << endl;
			cout << "Your Option: ";
			getline(cin, option);
		}
	}
}

void MainActivity::Login() {
	option = "";
	logout = false;
	for (int i = 0; i < 3; i++) {
		string username;
		string password;
		cout << "Username: ";
		getline(cin, username);
		cout << "Password: ";
		getline(cin, password);
		cout << endl;
		for (int i = 0; i < User::users.size(); i++) {
			if (User::users[i].getUsername() == username && User::users[i].getPassword() == password) {
				if (User::users[i].getRole() == 0) {
					CustomerActivity::CustomerActivity(User::findIndex(User::users[i].getID()));
				}else {
					AdminPanel::AdminPanel(i);
				}
			}
		}
		if (logout) break;
		cout << "Username or Password wrong!Please try again!\n";
	}
}

void MainActivity::Register() {
	while (true) {
		string name, address, username, password, tel;
		cout << "--Registration--\nUsername: ";
		getline(cin, username);
		cout << "Password: ";
		getline(cin, password);
		cout << "Name: ";
		getline(cin, name);
		cout << "Address: ";
		getline(cin, address);
		cout << "Telephone: ";
		getline(cin, tel);
		bool isExist = false;
		for (int i = 0; i < User::users.size(); i++) {
			if (User::users[i].getUsername() == username) {
				cout << "Register Failed! Username";
				isExist = true;
			}
		}
		if (username == "" || password == "" || name == "" || address == "" || tel == "") {
			cout << "All field required!";
			isExist = true;
		}
		if (isExist) continue;
		User::users.push_back(User(username, password, name, address, tel, 0));
		cout << "Register Sucessfully!!\n";
		MainActivity::MainActivity();
		break;
	}
}


CustomerActivity::CustomerActivity(int cus_id) {
	option = "";
	while (true) {
		if (option == "1") {
			ViewProfile(cus_id);
		}else if (option == "2") {
			EditProfile(cus_id);
		}else if (option == "3") {
			PurchaseMedicine(cus_id);
		}else if (option == "4") {
			SearchMeidicine();
		}else if (option == "5") {
			OrderHistory(cus_id);
		}else if (option == "00") {
			logout = true;
			break;
		}else {
			system("cls");
			cout << "Hi! " << User::users[cus_id].getName();
			cout << "\nYou can do: \n1. View Profile\n2. Edit Profile\n3. Purchase Medicine\n4. Search Medicine\n5. Order History\n00. Logout" << endl;
			cout << "\nYour option: ";
			getline(cin, option);
		}
	}
}


void CustomerActivity::ViewProfile(int cus_id) {
	cout << "Your Username: " << User::users[cus_id].getUsername() << endl;
	cout << "Your Name: " << User::users[cus_id].getName() << endl;
	cout << "Your Address: " << User::users[cus_id].getAddress() << endl;
	cout << "Your Telephone: " << User::users[cus_id].getTel() << endl;
	cout << "Press Any Key to Back";
	getline(cin, option);
}

void CustomerActivity::EditProfile(int cus_id) {
	option = "100";
	while (true) {
		if (option == "1") {
			string name;
			cout << "Your Name: " << User::users[cus_id].getName() << endl;
			cout << "Change To: ";
			getline(cin, name);
			(name!="")?User::users[cus_id].setName(name): User::users[cus_id].setName(User::users[cus_id].getName());
			cout << "Press Any Key to Back";
			getline(cin, option);
		}else if (option == "2") {
			string oldp, newp, newp2;
			for (int i = 0; i < 3; i++) {
				cout << "Old Password: ";
				getline(cin, oldp);
				cout << "New Password: ";
				getline(cin, newp);
				cout << "Reenter Password: ";
				getline(cin, newp2);
				if (newp != newp2) {
					cout << "Fail!!\n";
					continue;
				}
				if (User::users[cus_id].getPassword() == oldp) {
					option = "";
					cout << "Sucess Change!!" << endl;
					User::users[cus_id].setPassword(newp);
					cout << User::users[cus_id].getPassword();
					break;
				}
				cout << "Old Password Wrong!\n";
				option = "";
			}
		}else if (option == "3") {
			string address;
			cout << "Your Address: " << User::users[cus_id].getAddress() << endl;
			cout << "Change To: ";
			getline(cin, address);
			(address!="")?User::users[cus_id].setAddress(address): User::users[cus_id].setAddress(User::users[cus_id].getAddress());
			cout << "Press Any Key to Back";
			getline(cin, option);
		}else if (option == "4") {
			string phone;
			cout << "Your phone: " << User::users[cus_id].getTel() << endl;
			cout << "Change To: ";
			getline(cin, phone);
			(phone!="")?User::users[cus_id].setTel(phone): User::users[cus_id].setTel(User::users[cus_id].getTel());
			cout << "Press Any Key to Back";
			getline(cin, option);
		}else if (option == "0") {
			break;
		}else{
			cout << "Hi!" << User::users[cus_id].getName();
			cout << "\nEdit Profile: \n1. Edit Name\n2. Change Password\n3. Edit Address \n4. Edit Phone\n0. Back" << endl;
			cout << "\nYour option: ";
			getline(cin, option);
		}
	}
}

void CustomerActivity::PurchaseMedicine(int cus_id) {
	option = "100";
	Order o(User::users[cus_id].getID(), Date::Now());
	Order::orders.push_back(o);
	while (true){
		double total = 0;
		if(option == "0") {
			if (Order::orders[Order::findIndex(o.getOrderID())].orderItems.size() <= 0) {
				Order::orders.erase(Order::findIndex(o.getOrderID()) + Order::orders.begin());
				break;
			}
			cout << "Your order below: \n";
			cout << "OrdeID: " << o.getOrderID() << endl;
			cout << "Medicineid\tName\tPrice\tQuantity\tSubtotal" << endl;
			for (OrderItem orderitem: Order::orders[Order::findIndex(o.getOrderID())].orderItems) {
				Medicine m = Medicine::medicines[Medicine::getIndex(orderitem.getMed_id())];
				cout << orderitem.getMed_id() << "\t" <<m.getName() << "\t" << m.getPrice() << "\t" << orderitem.getQuantity() << "\t" << orderitem.subTotal() << endl;
				total += orderitem.subTotal();
			}
			cout << "Total: RM" << total << endl;
			char isConfirm;
			cout << "Do you want to confirm order? Y/N \n";
			cout << "Your option: ";
			cin >> isConfirm;
			if (isConfirm == 'Y' || isConfirm == 'y') { break; }
			if (isConfirm == 'N' || isConfirm == 'n') {
				Order::orders.erase(Order::findIndex(o.getOrderID()) + Order::orders.begin());
				break;
			}
		}else{
			string id = "0", quantity = "0";
			cout << "id\tName\tPrice\tCompany\tManuFactureDate\tExpiredDate" << endl;
			for (int i = 0; i < Medicine::medicines.size(); i++) {
				cout << Medicine::medicines[i].getID() << "\t" << Medicine::medicines[i].getName() << "\t" << Medicine::medicines[i].getPrice() << "\t" << Medicine::medicines[i].getCompany() << "\t" << Medicine::medicines[i].getManuDate() << "\t" << Medicine::medicines[i].getExpDate() << endl;
			}
			cout << "Enter the id of medicine: ";
			cin >> id;
			cout << "Enter the quantity: ";
			cin >> quantity;
			try {
				if (Medicine::checkIDisvalid(stoi(id)) > 0 && stoi(quantity) > 0)
				Order::orders[Order::findIndex(o.getOrderID())].orderItems.push_back(OrderItem(o.getOrderID(), stoi(id), stoi(quantity)));
				else cout << "ID Invalid or Quantity must be more than 0\n";
			}catch (exception e) {
				cout << "ID and Quantity Format wrong!\n";
			}
			cout << "Do you want to continue purchase? 1/0 \n";
			cout << "Your option : ";
			cin >> option;
		}
	}
}

void CustomerActivity::SearchMeidicine() {
	string name;
	cout << "\nSearch Medicine name: ";
	getline(cin, name);
	vector<Medicine> m = Medicine::searchByName(name);
	if (m.size() > 0) {
		for (int i = 0; i < m.size(); i++) {
			cout << m[i].getID() << "\t" << m[i].getName() << "\t" << m[i].getPrice() << endl;
		}
	}else {
		cout << "No result Found!" << endl;
	}
	option = "";
	getline(cin, option);
}

void CustomerActivity::OrderHistory(int cus_id) {
	double total = 0;
	vector<Order> orders = Order::findCustomerOrder(User::users[cus_id].getID());
	cout << "OrderID\tDate\t\t\tTotal" << endl;
	for (Order order : orders) {
		cout << order.getOrderID() << "\t" << order.getDate() << "\t";
		for (OrderItem item : order.orderItems) {
			total += item.subTotal();
		}
		cout << "RM " << total << endl;
	}
	cout << "Press Any Key to Back";
	getline(cin, option);
}

AdminPanel::AdminPanel(int adm_id) {
	option = "";
	while (true){
		if (option == "1") {
			MedicineManage();
		}else if (option == "2") {
			SearchMedicine();
		}else if (option == "3") {
			AdminPanel::SearchExpiredDate();
		}else if (option == "00") {
			logout = true;
			break;
		}else {
			system("cls");
			cout << "Hi!" << User::users[adm_id].getName();
			cout << "\nYou can: \n1. Manage Medicine\n2. Search Medicine\n3. Search by Expired Date\n00. Logout" << endl;
			cout << "\nYour option: ";
			getline(cin, option);
		}
	}
}

void AdminPanel::MedicineManage() {
	option = "";
	string name, price, company, manuDate, expDate;
	while (true) {
		if (option == "1") {
			while (true) {
				option = "";
				cout << "--- New Medicine ---\n";
				cout << "Medicine Name: ";
				getline(cin, name);
				cout << "Medicine Company: ";
				getline(cin, company);
				cout << "Medicine Price: ";
				getline(cin, price);
				cout << "Medicine ManuFacture Date(dd/mm/yy): ";
				getline(cin, manuDate);
				cout << "Medicine Expired Date(dd/mm/yy) : ";
				getline(cin, expDate);	
				Date manuD, expD;
				try {
					manuD = Date::StringToDate(manuDate);
					expD = Date::StringToDate(expDate);
				}
				catch (exception e) {
					cout << "Fail! Date Format Wrong (dd/mm/yy) Please Retry..\n";
					continue;
				}
				if (manuD.isValidate() == false || expD.isValidate() == false) {
					cout << "Invalid Date\n";
					continue;
				}
				try {
					Medicine::medicines.push_back(Medicine(name, company, stod(price), manuDate , expDate));
				}catch(exception e){
					cout << "Fail! Invalid price...\n";
					continue;
				}
				cout << "Sucess!!\n";
				cout << "Do you want to continue add? (Press 8 to back)\n";
				cout << "\nYour option: ";
				getline(cin, option);
				if (option == "8") { 
					break; 
				}	
			}
		}
		else if (option == "2") {
			for (int m = 0; m < 3; m++) {
				string id;
				cout << "Enter the medicine id to delete: ";
				getline(cin, id);
				int i = Medicine::getIndex(stoi(id));
				if (i >= 0) {
					cout << "Medicine Information: \n";
					cout << "Medicine ID: " << Medicine::medicines[i].getID() << endl;
					cout << "Medicine Name: " << Medicine::medicines[i].getName() << endl;
					cout << "Medicine Company: " << Medicine::medicines[i].getCompany() << endl;
					cout << "Medicine Price: " << Medicine::medicines[i].getPrice() << endl;
					cout << "Medicine Manufacture Date: " << Medicine::medicines[i].getManuDate()<< endl;
					cout << "Medicine Expired Date: " << Medicine::medicines[i].getExpDate() << endl;
				}else {
					cout << "Invalid Medicine id!\n";
					continue;
				}
				cout << "Do you want to delete? (Press 9 to confirm delete)";
				cout << "\nYour option: ";
				getline(cin, option);
				if (option == "9") {
					Medicine::delMedicine(stoi(id));
					cout << "Deleted! \n";
				}else {
					cout << "Delete Fail \n";
				}
				cout << "Do you want to continue delete medicine? (Press 9 to exit/ Press any key to continue)";
				cout << "\nYour option: ";
				getline(cin, option);
				if (option == "9") {
					break;
				}
			}
		}else if (option == "3") {
			while (true) {
				string mid, mname, mcompany, mprice, mmanudate, mexpdate;
				int mindex;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				cout << "Enter Medicine id: ";
				getline(cin, mid);
				try {
					mindex = Medicine::getIndex(stoi(mid));
					if (mindex < 0) { cout << "ID invalid"; continue; }
				}catch(exception e){
					cout << "Invalid ID\n";
					continue;
				}
				cout << "Medicine Information: \n";
				cout << "Medicine ID: " << Medicine::medicines[mindex].getID() << endl;
				cout << "Medicine Name: " << Medicine::medicines[mindex].getName() << endl;
				SetConsoleTextAttribute(hConsole, 3);
				cout << "New Name:"; getline(cin, mname);
				(mname != "")?Medicine::medicines[mindex].setName(mname): Medicine::medicines[mindex].setName(Medicine::medicines[mindex].getName());
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Medicine Company: " << Medicine::medicines[mindex].getCompany() << endl;
				SetConsoleTextAttribute(hConsole, 3);
				cout << "New Company:"; getline(cin, mcompany);
				(mcompany != "")?Medicine::medicines[mindex].setCompany(mcompany): Medicine::medicines[mindex].setCompany(Medicine::medicines[mindex].getCompany());
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Medicine Price: " << Medicine::medicines[mindex].getPrice() << endl;
				SetConsoleTextAttribute(hConsole, 3);
				cout << "New Price:"; getline(cin, mprice);
				if (mprice != "")
					try {
					Medicine::medicines[mindex].setPrice(stod(mprice));
					}catch(exception e){
						SetConsoleTextAttribute(hConsole, 4);
						cout << "UnSucess!Price Format Wrong!\n";
						Medicine::medicines[mindex].setPrice(Medicine::medicines[mindex].getPrice());
					}
				else
				Medicine::medicines[mindex].setPrice(Medicine::medicines[mindex].getPrice());
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Medicine Manufacture Date: " << Medicine::medicines[mindex].getManuDate() << endl;
				SetConsoleTextAttribute(hConsole, 3);
				cout << "New Manufacture Date:"; getline(cin, mmanudate);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Medicine Expired Date: " << Medicine::medicines[mindex].getExpDate() << endl;
				SetConsoleTextAttribute(hConsole, 3);
				cout << "New Expired Date:"; getline(cin, mexpdate);
				Date manuD, expD;
				try {
					manuD = Date::StringToDate(mmanudate);
					expD = Date::StringToDate(mexpdate);
					if (manuD.isValidate() == true && expD.isValidate() == true) {
						Medicine::medicines[mindex].setManuDate(mmanudate);
						Medicine::medicines[mindex].setExpDate(mexpdate);
					}else{
						SetConsoleTextAttribute(hConsole, 4);
						cout << "Fail! Date Format Wrong (dd/mm/yy) Please Try Again..\n";
						Medicine::medicines[mindex].setManuDate(Medicine::medicines[mindex].getManuDate());
						Medicine::medicines[mindex].setExpDate(Medicine::medicines[mindex].getExpDate());
					}
				}catch (exception e) {
					SetConsoleTextAttribute(hConsole, 4);
					cout << "Fail! Date Format Wrong (dd/mm/yy) Please Try Again..\n";
					Medicine::medicines[mindex].setManuDate(Medicine::medicines[mindex].getManuDate());
					Medicine::medicines[mindex].setExpDate(Medicine::medicines[mindex].getExpDate());
				}
				SetConsoleTextAttribute(hConsole, 15);
				getline(cin, option);
				option = "";
				break;
			}
		}else if (option == "0") {
			break;
		}else {
			system("cls");
			cout << "id\tName\tPrice\tCompany\tManuFactureDate\tExpiredDate" << endl;
			for (int i = 0; i < Medicine::medicines.size(); i++) {
				cout << Medicine::medicines[i].getID() << "\t" << Medicine::medicines[i].getName() << "\t" << Medicine::medicines[i].getPrice() << "\t" << Medicine::medicines[i].getCompany() << "\t" << Medicine::medicines[i].getManuDate() << "\t" << Medicine::medicines[i].getExpDate() << endl;
			}
			cout << "\nManage Medicine: \n1. Add Medicine\n2. Delete Medicine\n3. Edit Medicine\n0. Back" << endl;
			cout << "\nYour option: ";
			getline(cin, option);
		}
	}
}

void AdminPanel::SearchMedicine() {
	option = "";
	while (true) {
		if (option == "1") {
			string id;
			cout << "\nSearch id: ";
			getline(cin, id);
			vector<Medicine> m;
			try {
				m = Medicine::searchById(stoi(id));
			}catch(exception e){
				cout << "Id Format Wrong!";
			}
			cout << "ID\tName\tPrice" << endl;
			if (m.size() > 0) {
				for (int i = 0; i < m.size(); i++) {
					cout << m[i].getID() << "\t" << m[i].getName() << "\t" << m[i].getPrice() << endl;
				}
			}else{
				cout << "No result Found\n";
			}
			option = "";
			continue;
		}else if (option == "2") {
			string name;
			cout << "\nSearch name: ";
			getline(cin, name);
			vector<Medicine> m = Medicine::searchByName(name);
			if (m.size() > 0) {
				for (int i = 0; i < m.size(); i++) {
					cout << m[i].getID() << "\t" << m[i].getName() << "\t" << m[i].getPrice() << endl;
				}
			}else {
				cout << "No result Found\n" ;
			}
			option = "";
			continue;
		}else if (option == "0") {
			break;
		}else {
			cout << "\Search Medicine: \n1. Search Medicine by Id \n2. Search Medicine by Name\n0. Back" << endl;
			cout << "Your option: ";
			getline(cin, option);
		}
	}
}

void AdminPanel::SearchExpiredDate() {
	option = "";
	while (true) {
		if (option == "1") {
			string year;
			cout << "\nEnter year: ";
			getline(cin, year);
			vector<Medicine> m;
			try {
				m = Medicine::searchByYear(stoi(year));
			}catch (exception e) {
				cout << "Year Format Wrong!";
			}
			cout << "ID\tName\tPrice\tExpired Date" << endl;
			if (m.size() > 0) {
				for (int i = 0; i < m.size(); i++) {
					cout << m[i].getID() << "\t" << m[i].getName() << "\t" << m[i].getPrice() << "\t" << m[i].getExpDate() << endl;
				}
				option = "";
				continue;
			}else {
				cout << "No result Found\n";
			}
			option = "";
			continue;
		}else if (option == "2") {
			string year, month;
			cout << "\nEnter year: "; 
			getline(cin, year);
			cout << "Enter month: ";
			getline(cin, month);
			vector<Medicine> m;
			try {
				m = Medicine::searchByMonth(stoi(year), stoi(month));
			}catch (exception e) {
				cout << "Date Format Wrong!";
			}
			cout << "ID\tName\tPrice\tExpired Date" << endl;
			if (m.size() > 0) {
				for (int i = 0; i < m.size(); i++) {
					cout << m[i].getID() << "\t" << m[i].getName() << "\t" << m[i].getPrice() << "\t" << m[i].getExpDate() << endl;
				}
			}else {
				cout << "No result Found\n";
			}
			option = "";
			continue;
		}else if (option == "0") {
			break;
		}else {
			cout << "\nSearch Expired Date: \n1. by Year \n2. by Month \n0. Back" << endl;
			cout << "Your option: ";
			getline(cin, option);
		}
	}
}   