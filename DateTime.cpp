
#include "DateTime.h"

#include "sgUtil.h"

#include <sstream>

#define SECSPERDAY 86400
#define SECSPERHOUR 3600
#define SECSPERMIN 60



using namespace std;
using namespace FCInterface;


DateTime::DateTime()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
}

bool DateTime::set(const std::string& str)
{
	vector<string> parts, parts2;
	Util::split(str, ' ', parts);



	if (parts.size() == 2) {

		bool valid = true;

		unsigned short yearPrev = year;
		unsigned char monthPrev = month;
		unsigned char dayPrev = day;

		unsigned char hourPrev = hour;
		unsigned char minutePrev = minute;
		unsigned char secondPrev = second;

		Util::split(parts[0], '-', parts2);
		if (parts2.size() == 3) {
			try {
				year = (unsigned short)std::stoul(parts2[0]);
				month = (unsigned char)std::stoul(parts2[1]);
				day = (unsigned char)std::stoul(parts2[2]);
			}
			catch (...) {
				valid = false;
			}
			month = month > 0 ? month - 1 : month;
			day = day > 0 ? day - 1 : day;
		}
		else {
			valid = false;
		}
		
		if (parts[1].size() == 6) {
			try {
				hour = (unsigned char)std::stoul(parts[1].substr(0, 2));
				minute = (unsigned char)std::stoul(parts[1].substr(2, 2));
				second = (unsigned char)std::stoul(parts[1].substr(4, 2));
			}
			catch (...) {
				valid = false;
			}
		}
		else if (parts[1].size() == 8) {
			try {
				hour = (unsigned char)std::stoul(parts[1].substr(0, 2));
				minute = (unsigned char)std::stoul(parts[1].substr(3, 2));
				second = (unsigned char)std::stoul(parts[1].substr(6, 2));
			}
			catch (...) {
				valid = false;
			}
		}

		if (!valid) {

			year = yearPrev;
			month = monthPrev;
			day = dayPrev;
			hour = hourPrev;
			minute = minutePrev;
			second = secondPrev;
			return false;
		}
	}
	else {
		return false;
	}
	
	return true;
}

void DateTime::set(const Timestamp& ts)
{

	unsigned int timeIn	 = ts.ts();

	static const int mon_lengths[2][12] = {
	  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};


	static const int year_lengths[2] = {365, 366};


	int days = ((long)timeIn) / SECSPERDAY;
	int rem = ((long)timeIn) % SECSPERDAY;

	while (rem < 0)
	{
		rem += SECSPERDAY;
		--days;
	}
	while (rem >= SECSPERDAY)
	{
		rem -= SECSPERDAY;
		++days;
	}

	this->hour = (int)(rem / SECSPERHOUR);
	rem %= SECSPERHOUR;
	this->minute = (int)(rem / SECSPERMIN);
	this->second = (int)(rem % SECSPERMIN);


	int y = FCUI_TS_EPOCH_YEAR;
	int yleap;
	const int* ip;

	if (days >= 0)
	{
		for (;;)
		{
			yleap = myIsLeap(y);
			if (days < year_lengths[yleap])
				break;
			y++;
			days -= year_lengths[yleap];
		}
	}
	else
	{
		do
		{
			--y;
			yleap = myIsLeap(y);
			days += year_lengths[yleap];
		} while (days < 0);
	}

	this->year = y;

	ip = mon_lengths[yleap];
	for (this->month = 0; days >= ip[this->month]; ++this->month)
		days -= ip[this->month];
	this->day = days; // + 1  //we use 0-30 
}

void DateTime::set(unsigned short _year, unsigned char _month, unsigned char _day, 
	unsigned char _hour, unsigned char _minute, unsigned char _second)
{
	year = _year;
	month = _month;
	day = _day;

	hour = _hour;
	minute = _minute;
	second = _second;
}

DateTime DateTime::now()
{

	time_t t = time(0);
	tm* ts = gmtime(&t);
	if (ts) {
		return DateTime((unsigned short)ts->tm_year + 1900, (unsigned char)ts->tm_mon, (unsigned char)ts->tm_mday - 1,
			ts->tm_hour, ts->tm_min, ts->tm_sec);
	}
	return DateTime();
}



Timestamp DateTime::timestamp()
{
	Timestamp ts;
	ts.create(year, month, day, hour, minute, second);
	return ts;
}

std::string DateTime::toString()
{
	stringstream ss;

	ss << Util::padZeros(to_string(year),4) << "-" << Util::padZeros(to_string(month + 1), 2) << "-" << Util::padZeros(to_string(day + 1), 2) << " "
		<< Util::padZeros(to_string(hour), 2) << Util::padZeros(to_string(minute), 2) << Util::padZeros(to_string(second), 2);

	return ss.str();

}


bool DateTime::operator>=(const DateTime& b) const
{
	
	if (year > b.year)
		return true;
	if (year < b.year)
		return false;
	if (month > b.month)
		return true;
	if (month < b.month)
		return false;
	if (day > b.day)
		return true;
	if (day < b.day)
		return false;
	if (hour > b.hour)
		return true;
	if (hour < b.hour)
		return false;
	if (minute > b.minute)
		return true;
	if (minute < b.minute)
		return false;
	if (second > b.second)
		return true;
	if (second < b.second)
		return false;

	return true;

}

bool DateTime::operator<=(const DateTime& b) const
{
	if (year > b.year)
		return false;
	if (year < b.year)
		return true;
	if (month > b.month)
		return false;
	if (month < b.month)
		return true;
	if (day > b.day)
		return false;
	if (day < b.day)
		return true;
	if (hour > b.hour)
		return false;
	if (hour < b.hour)
		return true;
	if (minute > b.minute)
		return false;
	if (minute < b.minute)
		return true;
	if (second > b.second)
		return false;
	if (second < b.second)
		return true;

	return true;
}

bool DateTime::operator<(const DateTime& b) const
{
	if (year > b.year)
		return false;
	if (year < b.year)
		return true;
	if (month > b.month)
		return false;
	if (month < b.month)
		return true;
	if (day > b.day)
		return false;
	if (day < b.day)
		return true;
	if (hour > b.hour)
		return false;
	if (hour < b.hour)
		return true;
	if (minute > b.minute)
		return false;
	if (minute < b.minute)
		return true;
	if (second > b.second)
		return false;
	if (second < b.second)
		return true;

	return false;
}


bool DateTime::operator>(const DateTime& b) const
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
	if (hour < b.hour)
		return false;
	if (hour > b.hour)
		return true;
	if (minute < b.minute)
		return false;
	if (minute > b.minute)
		return true;
	if (second < b.second)
		return false;
	if (second > b.second)
		return true;

	return false;
}


bool DateTime::operator>=(Date& b)
{
	if (year > b.year)
		return true;
	if (year < b.year)
		return false;
	if (month > b.month)
		return true;
	if (month < b.month)
		return false;
	if (day > b.day)
		return true;
	if (day < b.day)
		return false;

	return true;
}

bool DateTime::operator<=(Date& b)
{
	if (year > b.year)
		return false;
	if (year < b.year)
		return true;
	if (month > b.month)
		return false;
	if (month < b.month)
		return true;
	if (day > b.day)
		return false;
	if (day < b.day)
		return true;

	return true;
}