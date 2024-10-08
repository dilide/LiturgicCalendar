﻿/*
============================================================================
文件名称	:	Date.cpp
公司		:	CathAssist
作者		:	李亚科
创建时间	:	2014-06-12 12:27
修改时间	:	2014-06-12 12:30
说明		:	日期类，参考自QDate
============================================================================
*/

#include "Date.h"
#include <sstream>
#include <iomanip>

#define LOWORD(x) (x&0x0000FFFF)
#define HIWORD(x) ((x&0xFFFF0000)>>16)
#define MAKELONG(x,y) ((y<<16)|x)

using namespace CathAssist::Calendar;

template <typename T>
inline const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }

enum {
	FIRST_YEAR = -4713,
	FIRST_MONTH = 1,
	FIRST_DAY = 2,  // ### Qt 5: make FIRST_DAY = 1, by support jd == 0 as valid
	SECS_PER_DAY = 86400,
	MSECS_PER_DAY = 86400000,
	SECS_PER_HOUR = 3600,
	MSECS_PER_HOUR = 3600000,
	SECS_PER_MIN = 60,
	MSECS_PER_MIN = 60000,
	JULIAN_DAY_FOR_EPOCH = 2440588 // result of julianDayFromGregorianDate(1970, 1, 1)
};

static const char monthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static inline Date fixedDate(int y, int m, int d)
{
	Date result(y, m, 1);
	result.setDate(y, m, Min(d, result.daysInMonth()));
	return result;
}

static inline unsigned int julianDayFromGregorianDate(int year, int month, int day)
{
	// Gregorian calendar starting from October 15, 1582
	// Algorithm from Henry F. Fliegel and Thomas C. Van Flandern
	return (1461 * (year + 4800 + (month - 14) / 12)) / 4
		+ (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
		- (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4
		+ day - 32075;
}

static unsigned int julianDayFromDate(int year, int month, int day)
{
	if (year < 0)
		++year;

	if (year > 1582 || (year == 1582 && (month > 10 || (month == 10 && day >= 15))))
	{
		return julianDayFromGregorianDate(year, month, day);
	}
	else if (year < 1582 || (year == 1582 && (month < 10 || (month == 10 && day <= 4))))
	{
		// Julian calendar until October 4, 1582
		// Algorithm from Frequently Asked Questions about Calendars by Claus Toendering
		int a = (14 - month) / 12;
		return (153 * (month + (12 * a) - 3) + 2) / 5
			+ (1461 * (year + 4800 - a)) / 4
			+ day - 32083;
	}
	else
	{
		// the day following October 4, 1582 is October 15, 1582
		return 0;
	}
}

static void getDateFromJulianDay(unsigned int julianDay, int& year, int& month, int& day)
{
	int y, m, d;

	if (julianDay >= 2299161)
	{
		// Gregorian calendar starting from October 15, 1582
		// This algorithm is from Henry F. Fliegel and Thomas C. Van Flandern
		unsigned long long ell, n, i, j;
		ell = (unsigned long long)(julianDay) + 68569;
		n = (4 * ell) / 146097;
		ell = ell - (146097 * n + 3) / 4;
		i = (4000 * (ell + 1)) / 1461001;
		ell = ell - (1461 * i) / 4 + 31;
		j = (80 * ell) / 2447;
		d = (int)(ell - (2447 * j) / 80);
		ell = j / 11;
		m = (int)(j + 2 - (12 * ell));
		y = (int)(100 * (n - 49) + i + ell);
	}
	else
	{
		// Julian calendar until October 4, 1582
		// Algorithm from Frequently Asked Questions about Calendars by Claus Toendering
		julianDay += 32082;
		int dd = (4 * julianDay + 3) / 1461;
		int ee = julianDay - (1461 * dd) / 4;
		int mm = ((5 * ee) + 2) / 153;
		d = ee - (153 * mm + 2) / 5 + 1;
		m = mm + 3 - 12 * (mm / 10);
		y = dd - 4800 + (mm / 10);
		if (y <= 0)
			--y;
	}
	
    year = y;
	month = m;
	day = d;
}

bool Date::isValid(const int& year,const int& month,const int& day)
{
	if (year < FIRST_YEAR
		|| (year == FIRST_YEAR &&
		(month < FIRST_MONTH
		|| (month == FIRST_MONTH && day < FIRST_DAY)))
		|| year == 0) // there is no year 0 in the Julian calendar
		return false;

	// passage from Julian to Gregorian calendar
	if (year == 1582 && month == 10 && day > 4 && day < 15)
		return 0;

	return (day > 0 && month > 0 && month <= 12) &&
		(day <= monthDays[month] || (day == 29 && month == 2 && isLeapYear(year)));
}

bool Date::isLeapYear(const int& year)
{
	int y = year;
	if (y < 1582)
	{
		if ( y < 1)
		{  // No year 0 in Julian calendar, so -1, -5, -9 etc are leap years
			++y;
		}
		return y % 4 == 0;
	}
	else
	{
		return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
	}
}


Date::Date(void)
{
	 jd = 0;
}

Date::Date(const int& year, const int& month, const int& day)
{
	setDate(year, month, day);
}

Date::~Date(void)
{

}


bool CathAssist::Calendar::Date::isValid() const
{
	return !isNull();
}

int Date::year() const
{
	int y = 0,m = 0,d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return y;
}

int Date::month() const
{
	int y = 0,m = 0,d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return m;
}

int Date::day() const
{
	int y = 0,m = 0,d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return d;
}

day_t Date::dayOfWeek() const
{
	int w = (jd % 7) + 1;

	return static_cast<day_t>(w%7);
}

int Date::dayOfYear() const
{
	return jd - julianDayFromDate(year(), 1, 1) + 1;
}

int Date::daysInMonth() const
{
	int y = 0,m = 0,d = 0;
	getDateFromJulianDay(jd, y, m, d);
	if (m == 2 && isLeapYear(y))
		return 29;
	else
		return monthDays[m];
}

int Date::daysInYear() const
{
	int y = 0,m = 0,d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return isLeapYear(y) ? 366 : 365;
}

int Date::weekNumber(int* yearNumber /*= 0*/) const
{
    if (!isValid())
        return 0;

    int year = Date::year();
    int yday = dayOfYear() - 1;
    int wday = dayOfWeek();
    int w;

    for (;;)
	{
        int len;
        int bot;
        int top;

        len = isLeapYear(year) ? 366 : 365;
        /*
        ** What yday (-3 ... 3) does
        ** the ISO year begin on?
        */
        bot = ((yday + 11 - wday) % 7) - 3;
        /*
        ** What yday does the NEXT
        ** ISO year begin on?
        */
        top = bot - (len % 7);
        if (top < -3)
            top += 7;
        top += len;
        if (yday >= top) {
            ++year;
            w = 1;
            break;
        }
        if (yday >= bot) {
            w = 1 + ((yday - bot) / 7);
            break;
        }
        --year;
        yday += isLeapYear(year) ? 366 : 365;
    }
    if (yearNumber != 0)
        *yearNumber = year;

	if(wday == 0)
		w+=1;
    return w;
}


bool Date::setYMD(const int& year, const int& month, const int& day)
{
	int y = year;
	if ((unsigned int)(y) <= 99)
		y += 1900;
	return setDate(y, month, day);
}

bool Date::setDate(const int& year,const int& month,const int& day)
{
	if (!isValid(year, month, day))
	{
		jd = 0;
	}
	else
	{
		jd = julianDayFromDate(year, month, day);
	}
	return jd != 0;
}

void Date::getDate(int& year, int& month, int& day)
{
	getDateFromJulianDay(jd, year, month, day);
}

Date Date::addDays(int ndays) const
{
	Date d;
	// this is basically "d.jd = jd + ndays" with checks for integer overflow
	if (ndays >= 0)
		d.jd = (jd + ndays >= jd) ? jd + ndays : 0;
	else
		d.jd = (jd + ndays < jd) ? jd + ndays : 0;
	return d;
}

Date Date::addMonths(int nmonths) const
{
	if (!isValid())
		return Date();
	if (!nmonths)
		return *this;

	int old_y = 0, y = 0, m = 0, d = 0;
	getDateFromJulianDay(jd, y, m, d);
	old_y = y;

	bool increasing = nmonths > 0;

	while (nmonths != 0)
	{
		if (nmonths < 0 && nmonths + 12 <= 0)
		{
			y--;
			nmonths+=12;
		}
		else if (nmonths < 0)
		{
			m+= nmonths;
			nmonths = 0;
			if (m <= 0)
			{
				--y;
				m += 12;
			}
		}
		else if (nmonths - 12 >= 0)
		{
			y++;
			nmonths -= 12;
		}
		else if (m == 12)
		{
			y++;
			m = 0;
		}
		else
		{
			m += nmonths;
			nmonths = 0;
			if (m > 12)
			{
				++y;
				m -= 12;
			}
		}
	}

	// was there a sign change?
	if ((old_y > 0 && y <= 0) ||
		(old_y < 0 && y >= 0))
		// yes, adjust the date by +1 or -1 years
		y += increasing ? +1 : -1;

	// did we end up in the Gregorian/Julian conversion hole?
	if (y == 1582 && m == 10 && d > 4 && d < 15)
		d = increasing ? 15 : 4;

	return fixedDate(y, m, d);
}

Date Date::addYears(int nyears) const
{
	if (!isValid())
		return Date();
    
	int y = 0,m = 0,d = 0;
	getDateFromJulianDay(jd, y, m, d);

	int old_y = y;
	y += nyears;

	// was there a sign change?
	if ((old_y > 0 && y <= 0) ||
		(old_y < 0 && y >= 0))
		// yes, adjust the date by +1 or -1 years
		y += nyears > 0 ? +1 : -1;

	return fixedDate(y, m, d);
}

int Date::daysTo(const Date& d) const
{
	return d.jd - jd;
}

bool Date::getLunarDate(int& iLunarYear, int& iLunarMonth, int& iLunarDay) const
{
    static Date dtStart(gStartYear,1,1);
    static Date dtEnd(gEndYear,12,31);
    
    if ((*this < dtStart) || (*this > dtEnd))
    {
        return false;
    }
    
    int iSpanDays = dtStart.daysTo(*this);
    
    //阳历1901年2月19日为阴历1901年正月初一
    //阳历1901年1月1日到2月19日共有49天
    if(iSpanDays <49)
    {
        iLunarYear = gStartYear-1;
        if(iSpanDays <19)
        {
            iLunarMonth = 11;
            iLunarDay = 11+iSpanDays;
        }
        else
        {
            iLunarMonth = 12;
            iLunarDay = iSpanDays -18;
        }
        return true;
    }
    
    //下面从阴历1901年正月初一算起
    iSpanDays -=49;
    
    iLunarYear = gStartYear;
    iLunarMonth = 1;
    iLunarDay = 1;
    
    //计算年
    long tmp = getLunarYearDays(iLunarYear);
    while(iSpanDays >= tmp)
    {
        iSpanDays -= tmp;
        tmp = getLunarYearDays(++iLunarYear);
    }
    //计算月
    tmp = LOWORD(getLunarMonthDays(iLunarYear, iLunarMonth));
    while(iSpanDays >= tmp)
    {
        iSpanDays -= tmp;
        if(iLunarMonth == getLeapMonth(iLunarYear))
        {
            tmp  = HIWORD(getLunarMonthDays(iLunarYear, iLunarMonth));
            if(iSpanDays < tmp)
                break;
            iSpanDays -= tmp;
        }
        tmp = LOWORD(getLunarMonthDays(iLunarYear, ++iLunarMonth));
    }
    //计算日
    iLunarDay += iSpanDays;
    
    return true;
}

std::string Date::toString() const
{
	if (year() > 9999)
		return std::string();

	//格式化输出
	std::ostringstream ostr;
	ostr<<Date::year()<<"-"
        <<std::setfill('0')<<std::setw(2)<<Date::month()<<"-"
        <<std::setfill('0')<<std::setw(2)<<Date::day();

	return ostr.str();
}

std::string CathAssist::Calendar::Date::toLunarString() const
{
	int iLunarYear,iLunarMonth,iLunarDay;
	if(!getLunarDate(iLunarYear,iLunarMonth,iLunarDay))
	{
		return "农历超出范围";
	}

	//格式化输出
	std::ostringstream ostr;
	ostr<<getLunarYearStr(iLunarYear)<<getLunarMonthStr(iLunarMonth)<<getLunarDayStr(iLunarDay);

	return ostr.str();

}

unsigned short Date::getLeapMonth(int iLunarYear)
{
    unsigned char &flag = gLunarMonth[(iLunarYear - gStartYear)/2];
    return  (iLunarYear - gStartYear)%2 ? flag&0x0f : flag>>4;
}

int Date::getLunarMonthDays(int iLunarYear, int iLunarMonth)
{
    if(iLunarYear < gStartYear)
        return 30L;
    
    unsigned short high =0 ,low =29;
    int iBit = 16 - iLunarMonth;
    
    if(iLunarMonth > getLeapMonth(iLunarYear) && getLeapMonth(iLunarYear))
        iBit --;
    
    if(gLunarMonthDay[iLunarYear - gStartYear] & (1<<iBit))
        low ++;
    
    if(iLunarMonth == getLeapMonth(iLunarYear))
    {
        if(gLunarMonthDay[iLunarYear - gStartYear] & (1<< (iBit -1)))
        {
            high =30;
        }
        else
        {
            high =29;
        }
    }
    
    return MAKELONG(low, high);
}

int Date::getLunarYearDays(int iLunarYear)
{
    int days =0;
    for(int i=1; i<=12; i++)
    {
        long tmp = getLunarMonthDays(iLunarYear ,i);
        days += HIWORD(tmp);
        days += LOWORD(tmp);
    }
    return days;
}


const int Date::gStartYear = 1901;
const int Date::gEndYear = 2050;

/******************************************************************************
 下面为阴历计算所需的数据,为节省存储空间,所以采用下面比较变态的存储方法.
 *******************************************************************************/
//数组gLunarDay存入阴历1901年到2100年每年中的月天数信息，
//阴历每月只能是29或30天，一年用12（或13）个二进制位表示，对应位为1表30天，否则为29天
unsigned short Date::gLunarMonthDay[]=
{
    //测试数据只有1901.1.1 --2050.12.31
    0x4ae0, 0xa570, 0X5268, 0xd260, 0xD950, 0x6aa8, 0x56a0, 0x9ad0, 0x4ae8, 0x4ae0,   //1910
    0Xa4d8, 0Xa4d0, 0Xd250, 0Xd548, 0Xb550, 0X56a0, 0X96d0, 0X95b0, 0X49b8, 0X49b0,   //1920
    0Xa4b0, 0Xb258, 0X6a50, 0X6d40, 0Xada8, 0X2b60, 0X9570, 0X4978, 0X4970, 0X64b0,   //1930
    0Xd4a0, 0Xea50, 0X6d48, 0X5ad0, 0X2b60, 0X9370, 0X92e0, 0Xc968, 0Xc950, 0Xd4a0,   //1940
    0Xda50, 0Xb550, 0X56a0, 0Xaad8, 0X25d0, 0X92d0, 0Xc958, 0Xa950, 0Xb4a8, 0X6ca0,   //1950
    0Xb550, 0X55a8, 0X4da0, 0Xa5b0, 0X52b8, 0X52b0, 0Xa950, 0Xe950, 0X6aa0, 0Xad50,   //1960
    0Xab50, 0X4b60, 0Xa570, 0Xa570, 0X5260, 0Xe930, 0Xd950, 0X5aa8, 0X56a0, 0X96d0,   //1970
    0X4ae8, 0X4ad0, 0Xa4d0, 0Xd268, 0Xd250, 0Xd528, 0Xb540, 0Xb6a0, 0X96d0, 0X95b0,   //1980
    0X49b0, 0Xa4b8, 0Xa4b0, 0Xb258, 0X6a50, 0X6d40, 0Xada0, 0Xab60, 0X9370, 0X4978,   //1990
    0X4970, 0X64b0, 0X6a50, 0Xea50, 0X6b28, 0X5ac0, 0Xab60, 0X9368, 0X92e0, 0Xc960,   //2000
    0Xd4a8, 0Xd4a0, 0Xda50, 0X5aa8, 0X56a0, 0Xaad8, 0X25d0, 0X92d0, 0Xc958, 0Xa950,   //2010
    0Xb4a0, 0Xb550, 0Xb550, 0X55a8, 0X4ba0, 0Xa5b0, 0X52b8, 0X52b0, 0Xa930, 0X74a8,   //2020
    0X6aa0, 0Xad50, 0X4da8, 0X4b60, 0X9570, 0Xa4e0, 0Xd260, 0Xe930, 0Xd530, 0X5aa0,   //2030
    0X6b50, 0X96d0, 0X4ae8, 0X4ad0, 0Xa4d0, 0Xd258, 0Xd250, 0Xd520, 0Xdaa0, 0Xb5a0,   //2040
    0X56d0, 0X4ad8, 0X49b0, 0Xa4b8, 0Xa4b0, 0Xaa50, 0Xb528, 0X6d20, 0Xada0, 0X55b0,   //2050
};

//数组gLanarMonth存放阴历1901年到2050年闰月的月份，如没有则为0，每字节存两年
unsigned char Date::gLunarMonth[]=
{
    0X00, 0X50, 0X04, 0X00, 0X20,   //1910
    0X60, 0X05, 0X00, 0X20, 0X70,   //1920
    0X05, 0X00, 0X40, 0X02, 0X06,   //1930
    0X00, 0X50, 0X03, 0X07, 0X00,   //1940
    0X60, 0X04, 0X00, 0X20, 0X70,   //1950
    0X05, 0X00, 0X30, 0X80, 0X06,   //1960
    0X00, 0X40, 0X03, 0X07, 0X00,   //1970
    0X50, 0X04, 0X08, 0X00, 0X60,   //1980
    0X04, 0X0a, 0X00, 0X60, 0X05,   //1990
    0X00, 0X30, 0X80, 0X05, 0X00,   //2000
    0X40, 0X02, 0X07, 0X00, 0X50,   //2010
    0X04, 0X09, 0X00, 0X60, 0X04,   //2020
    0X00, 0X20, 0X60, 0X05, 0X00,   //2030
    0X30, 0Xb0, 0X06, 0X00, 0X50,   //2040
    0X02, 0X07, 0X00, 0X50, 0X03    //2050
};

