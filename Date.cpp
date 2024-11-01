
#include "Date.h"

#include "sgUtil.h"
#include "Translations.h"
#include <ctime>

#include <sstream>

using namespace std;
using namespace FCInterface;


Date Date::now()
{
	
	time_t t = time(0);
	tm* ts = gmtime(&t);
	if (ts) {
		return Date((unsigned short)ts->tm_year + 1900, (unsigned char)ts->tm_mon, (unsigned char)ts->tm_mday - 1);
	}
	return Date();
}

Date::Date()
{
	year = 0;
	month = 0;
	day = 0;

}

bool Date::set(unsigned short _year, unsigned char _month, unsigned char _day)
{
	//todo - check for validity properly (eg. 30th Feb)
	if (month > 11 || day > 30)
		return false;

	year = _year;
	month = _month;
	day = _day;

	return true;
}

bool Date::set(const std::string& str)
{
	vector<string> parts;

	Util::split(str, '-', parts);
	if (parts.size() == 3) {
		try {
			year = (unsigned short)std::stoul(parts[0]);
			month = (unsigned char)std::stoul(parts[1]);
			day = (unsigned char)std::stoul(parts[2]);
			
			//make zero-based:
			month = month > 0 ? month - 1 : month;
			day = day > 0 ? day - 1 : day;

			
		}
		catch (...) {
			return false;
		}

	}
	return true;
}

Date& Date::operator=(const Date& d)
{
	year = d.year;
	month = d.month;
	day = d.day;
	
	return *this;
}



std::string Date::toString()
{
	stringstream ss;

	ss << to_string(year) << "-" << to_string(month) << "-" << to_string(day);

	return ss.str();

}

bool Date::operator<(const Date& b) const
{
	if (year < b.year)
		return true;
	if (year > b.year)
		return false;
	if (month < b.month)
		return true;
	if (month > b.month)
		return false;
	if (day < b.day)
		return true;
	if (day > b.day)
		return false;

	return false;
}

bool Date::operator>(const Date& b) const
{
	if (year < b.year)
		return false;
	if (year > b.year)
		return true;
	if (month < b.month)
		return false;
	if (month > b.month)
		return true;
	if (day < b.day)
		return false;
	if (day > b.day)
		return true;

	return false;
}

bool Date::operator==(const Date& b) const
{
	return year == b.year && month == b.month && day == b.day;
}

