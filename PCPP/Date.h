#ifndef Date_H
#define Date_H
#pragma once
#include "pch.h"
#include <iostream>
#include "string"
#include "chrono"

using namespace std;

class Date {
public:
	int day, month, year;
	Date() {}

	Date(int day, int month, int year) {
		this->day = day;
		this->month = month;
		this->year = year;
	}
	
	string DateToString() {
		string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
		return date;
	}

	static Date StringToDate(string date) {
		string data[3] = {};
		stringstream dd(date);
		for (int i = 0; getline(dd, data[i], '/'); i++);
		Date d = Date(stoi(data[0]), stoi(data[1]), stoi(data[2]));
		return d;
	}
	static string Now() {
		time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
		tm tt;
		localtime_s(&tt, &t);
		string time = to_string(tt.tm_mday) + "/" + to_string(tt.tm_mon + 1) + "/" + to_string(tt.tm_year + 1900) + " " + to_string(tt.tm_hour) + ":" + to_string(tt.tm_min) + ":" + to_string(tt.tm_sec);
		return time;
	}
	bool isValidate() {
		if (day < 0 || day > 31) {
			return false;
		}
		else if (month < 0 || month> 12) {
			return false;
		}
		else if (year < 1970 || year> 2100) {
			return false;
		}
		return true;
	}
};

#endif