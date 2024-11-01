#ifndef DATETIME_H_
#define DATETIME_H_

#ifndef FCUI_TEST_TIME_H
#define FCUI_TEST_TIME_H

#include <string>

#include "Date.h"
#include "Timestamp.h"

namespace FCInterface {

	class DateTime {
	public:
		DateTime();
		DateTime(unsigned short _year, unsigned char _month, unsigned char _day, unsigned char _hour, unsigned char _minute, unsigned char _second)
			: DateTime() { set(_year, _month, _day, _hour, _minute, _second); }
		DateTime(const std::string& str) : DateTime() {
			set(str);
		}

		bool set(const std::string& str);
		void set(unsigned short _year, unsigned char _month, unsigned char _day, unsigned char _hour, unsigned char _minute, unsigned char _second);
		void set(const Timestamp& ts);

		static DateTime now();

		DateTime& operator=(const Timestamp& ts) { set(ts); return *this; }

		std::string toString();

		Timestamp timestamp();

		bool operator>=(const DateTime& b) const;
		bool operator<=(const DateTime& b) const;
		bool operator<(const DateTime& b) const;
		bool operator>(const DateTime& b) const;

		bool operator>=(Date& b);
		bool operator<=(Date& b);

		unsigned short year;
		unsigned char month;
		unsigned char day;

		unsigned char hour;
		unsigned char minute;
		unsigned char second;

	};

}

#endif //!defined FCUI_TEST_TIME_H


#endif // DATETIME_H_
