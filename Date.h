#ifndef DATE_H_
#define DATE_H_

#ifndef FCUI_DATE_H
#define FCUI_DATE_H

#include <string>

namespace FCInterface {

	class Date {
	public:
		Date();
		Date(unsigned short year, unsigned char month, unsigned char day) : Date() { set(year, month, day); }
		Date(const std::string& str) : Date() {
			set(str);
		}

		Date& operator=(const Date& d);


		bool operator==(const Date& d) const;
		bool set(const std::string& str);
		bool set(unsigned short year, unsigned char month, unsigned char day);
		std::string toString();

		bool operator<(const Date& b) const;
		bool operator>(const Date& b) const;



		static Date now();



		unsigned short year;
		unsigned char month;
		unsigned char day;

	};

}

#endif //!defined FCUI_DATE_H


#endif // DATE_H_
