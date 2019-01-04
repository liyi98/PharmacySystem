#include "pch.h"
#ifndef Activities_H
#define Activities_H

#include <iostream>
#include "string"
#include "User.h"
#include "Medicine.h"
#include "Date.h"
#include <windows.h>

using namespace std;

class MainActivity {
public:
	MainActivity();
	void Login();
	void Register();
};

class CustomerActivity {
public:
	CustomerActivity(int cus_id);
	void ViewProfile(int cus_id);
	void EditProfile(int cus_id);
	void PurchaseMedicine(int cus_id);
	void SearchMeidicine();
	void OrderHistory(int cus_id);
};

class AdminPanel {
public:
	AdminPanel(int adm_id);
	void MedicineManage();
	void SearchMedicine();
	void SearchExpiredDate();
};


#endif

