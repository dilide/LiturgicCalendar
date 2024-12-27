/*
============================================================================
文件名称	:	Date.h
公司		:	CathAssist
作者		:	李亚科
创建时间	:	2014-06-12 12:27
修改时间	:	2014-06-12 12:30
说明		:	日期类，参考自QDate
============================================================================
*/

#ifndef __CA_CALENDAR_DATE_H__
#define __CA_CALENDAR_DATE_H__

#include <string>
#include <map>
#include "CalendarDefine.h"

namespace CathAssist
{
	namespace Calendar
	{
		class Date
		{
		public:
			static bool isValid(const int& year,const int& month,const int& day); 
			static bool isLeapYear(const int& year);
			// 判断是否为春节
			static bool isSpringFestival(const Date& d);
			// 判断是否为除夕
			static bool isNewYearEve(const Date& d);

		public:
			Date(void);
			Date(const int& year, const int& month, const int& day);
			~Date(void);

		public:
			bool isNull() const { return jd == 0; }
			bool isValid() const;

			int year() const;
			int month() const;
			int day() const;
			day_t dayOfWeek() const;
			int dayOfYear() const;
			int daysInMonth() const;
			int daysInYear() const;
			int weekNumber(int* yearNumber = 0) const;

			bool setYMD(const int& year, const int& month, const int& day);
			bool setDate(const int& year,const int& month,const int& day);
			void getDate(int& year, int& month, int& day);

			Date addDays(int days) const;
			Date addMonths(int months) const;
			Date addYears(int years) const;
			int daysTo(const Date &) const;
			std::string toString() const;

		public:
			bool operator==(const Date &other) const { return jd == other.jd; }
			bool operator!=(const Date &other) const { return jd != other.jd; }
			bool operator<(const Date &other) const { return jd < other.jd; }
			bool operator<=(const Date &other) const { return jd <= other.jd; }
			bool operator>(const Date &other) const { return jd > other.jd; }
			bool operator>=(const Date &other) const { return jd >= other.jd; }

		private:
			unsigned int jd;	//JulianDay
            
        private:
            static const int gStartYear;
            static const int gEndYear;
			static const std::map<int, Date> gLunarSpringDays;
		};
	}
}


#endif	//__CA_CALENDAR_DATE_H__