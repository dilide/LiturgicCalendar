/*
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

bool Date::isSpringFestival(const Date& d) {
	int year = d.year();
	std::map<int, Date>::const_iterator found = gLunarSpringDays.find(year);
	if(found != gLunarSpringDays.end()) {
		return found->second == d;
	}
	return false;
}

bool Date::isNewYearEve(const Date& d) {
	int year = d.year();
	std::map<int, Date>::const_iterator found = gLunarSpringDays.find(year);
	if(found != gLunarSpringDays.end()) {
		return found->second.addDays(-1) == d;
	}
	return false;
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

const int Date::gStartYear = 1901;
const int Date::gEndYear = 2050;

const std::map<int, Date> Date::gLunarSpringDays = {
	{1901, Date(1901, 2, 19)},
	{1902, Date(1902, 2, 8)},
	{1903, Date(1903, 1, 29)},
	{1904, Date(1904, 2, 16)},
	{1905, Date(1905, 2, 4)},
	{1906, Date(1906, 1, 25)},
	{1907, Date(1907, 2, 13)},
	{1908, Date(1908, 2, 2)},
	{1909, Date(1909, 1, 22)},
	{1910, Date(1910, 2, 10)},
	{1911, Date(1911, 1, 30)},
	{1912, Date(1912, 2, 18)},
	{1913, Date(1913, 2, 6)},
	{1914, Date(1914, 1, 26)},
	{1915, Date(1915, 2, 14)},
	{1916, Date(1916, 2, 3)},
	{1917, Date(1917, 1, 23)},
	{1918, Date(1918, 2, 11)},
	{1919, Date(1919, 1, 31)},
	{1920, Date(1920, 2, 20)},
	{1921, Date(1921, 2, 8)},
	{1922, Date(1922, 1, 28)},
	{1923, Date(1923, 2, 16)},
	{1924, Date(1924, 2, 5)},
	{1925, Date(1925, 1, 24)},
	{1926, Date(1926, 2, 13)},
	{1927, Date(1927, 2, 2)},
	{1928, Date(1928, 1, 23)},
	{1929, Date(1929, 2, 10)},
	{1930, Date(1930, 1, 30)},
	{1931, Date(1931, 2, 17)},
	{1932, Date(1932, 2, 6)},
	{1933, Date(1933, 1, 26)},
	{1934, Date(1934, 2, 14)},
	{1935, Date(1935, 2, 4)},
	{1936, Date(1936, 1, 24)},
	{1937, Date(1937, 2, 11)},
	{1938, Date(1938, 1, 31)},
	{1939, Date(1939, 2, 19)},
	{1940, Date(1940, 2, 8)},
	{1941, Date(1941, 1, 27)},
	{1942, Date(1942, 2, 15)},
	{1943, Date(1943, 2, 5)},
	{1944, Date(1944, 1, 25)},
	{1945, Date(1945, 2, 13)},
	{1946, Date(1946, 2, 2)},
	{1947, Date(1947, 1, 22)},
	{1948, Date(1948, 2, 10)},
	{1949, Date(1949, 1, 29)},
	{1950, Date(1950, 2, 17)},
	{1951, Date(1951, 2, 6)},
	{1952, Date(1952, 1, 27)},
	{1953, Date(1953, 2, 14)},
	{1954, Date(1954, 2, 3)},
	{1955, Date(1955, 1, 24)},
	{1956, Date(1956, 2, 12)},
	{1957, Date(1957, 2, 1)},
	{1958, Date(1958, 1, 21)},
	{1959, Date(1959, 2, 9)},
	{1960, Date(1960, 1, 28)},
	{1961, Date(1961, 2, 15)},
	{1962, Date(1962, 2, 5)},
	{1963, Date(1963, 1, 25)},
	{1964, Date(1964, 2, 13)},
	{1965, Date(1965, 2, 2)},
	{1966, Date(1966, 1, 21)},
	{1967, Date(1967, 2, 9)},
	{1968, Date(1968, 1, 30)},
	{1969, Date(1969, 2, 17)},
	{1970, Date(1970, 2, 6)},
	{1971, Date(1971, 1, 27)},
	{1972, Date(1972, 2, 15)},
	{1973, Date(1973, 2, 3)},
	{1974, Date(1974, 1, 23)},
	{1975, Date(1975, 2, 11)},
	{1976, Date(1976, 1, 31)},
	{1977, Date(1977, 2, 18)},
	{1978, Date(1978, 2, 7)},
	{1979, Date(1979, 1, 28)},
	{1980, Date(1980, 2, 16)},
	{1981, Date(1981, 2, 5)},
	{1982, Date(1982, 1, 25)},
	{1983, Date(1983, 2, 13)},
	{1984, Date(1984, 2, 2)},
	{1985, Date(1985, 1, 21)},
	{1986, Date(1986, 2, 9)},
	{1987, Date(1987, 1, 29)},
	{1988, Date(1988, 2, 17)},
	{1989, Date(1989, 2, 6)},
	{1990, Date(1990, 1, 27)},
	{1991, Date(1991, 2, 15)},
	{1992, Date(1992, 2, 4)},
	{1993, Date(1993, 1, 23)},
	{1994, Date(1994, 2, 10)},
	{1995, Date(1995, 1, 31)},
	{1996, Date(1996, 2, 19)},
	{1997, Date(1997, 2, 7)},
	{1998, Date(1998, 1, 28)},
	{1999, Date(1999, 2, 16)},
	{2000, Date(2000, 2, 5)},
	{2001, Date(2001, 1, 24)},
	{2002, Date(2002, 2, 12)},
	{2003, Date(2003, 2, 1)},
	{2004, Date(2004, 1, 22)},
	{2005, Date(2005, 2, 9)},
	{2006, Date(2006, 1, 29)},
	{2007, Date(2007, 2, 18)},
	{2008, Date(2008, 2, 7)},
	{2009, Date(2009, 1, 26)},
	{2010, Date(2010, 2, 14)},
	{2011, Date(2011, 2, 3)},
	{2012, Date(2012, 1, 23)},
	{2013, Date(2013, 2, 10)},
	{2014, Date(2014, 1, 31)},
	{2015, Date(2015, 2, 19)},
	{2016, Date(2016, 2, 8)},
	{2017, Date(2017, 1, 28)},
	{2018, Date(2018, 2, 16)},
	{2019, Date(2019, 2, 5)},
	{2020, Date(2020, 1, 25)},
	{2021, Date(2021, 2, 12)},
	{2022, Date(2022, 2, 1)},
	{2023, Date(2023, 1, 22)},
	{2024, Date(2024, 2, 10)},
	{2025, Date(2025, 1, 29)},
	{2026, Date(2026, 2, 17)},
	{2027, Date(2027, 2, 6)},
	{2028, Date(2028, 1, 26)},
	{2029, Date(2029, 2, 13)},
	{2030, Date(2030, 2, 3)},
	{2031, Date(2031, 1, 23)},
	{2032, Date(2032, 2, 11)},
	{2033, Date(2033, 1, 31)},
	{2034, Date(2034, 2, 19)},
	{2035, Date(2035, 2, 8)},
	{2036, Date(2036, 1, 28)},
	{2037, Date(2037, 2, 15)},
	{2038, Date(2038, 2, 5)},
	{2039, Date(2039, 1, 24)},
	{2040, Date(2040, 2, 13)},
	{2041, Date(2041, 2, 2)},
	{2042, Date(2042, 1, 22)},
	{2043, Date(2043, 2, 10)},
	{2044, Date(2044, 1, 30)},
	{2045, Date(2045, 2, 17)},
	{2046, Date(2046, 2, 6)},
	{2047, Date(2047, 1, 26)},
	{2048, Date(2048, 2, 14)},
	{2049, Date(2049, 2, 3)},
	{2050, Date(2050, 1, 23)},
	{2051, Date(2051, 2, 11)},
	{2052, Date(2052, 1, 31)},
	{2053, Date(2053, 2, 18)},
	{2054, Date(2054, 2, 7)},
	{2055, Date(2055, 1, 27)},
	{2056, Date(2056, 2, 15)},
	{2057, Date(2057, 2, 4)},
	{2058, Date(2058, 1, 24)},
	{2059, Date(2059, 2, 12)},
	{2060, Date(2060, 2, 1)},
	{2061, Date(2061, 1, 21)},
	{2062, Date(2062, 2, 9)},
	{2063, Date(2063, 1, 29)},
	{2064, Date(2064, 2, 17)},
	{2065, Date(2065, 2, 6)},
	{2066, Date(2066, 1, 26)},
	{2067, Date(2067, 2, 14)},
	{2068, Date(2068, 2, 3)},
	{2069, Date(2069, 1, 23)},
	{2070, Date(2070, 2, 11)},
	{2071, Date(2071, 1, 31)},
	{2072, Date(2072, 2, 19)},
	{2073, Date(2073, 2, 8)},
	{2074, Date(2074, 1, 28)},
	{2075, Date(2075, 2, 15)},
	{2076, Date(2076, 2, 5)},
	{2077, Date(2077, 1, 24)},
	{2078, Date(2078, 2, 12)},
	{2079, Date(2079, 2, 1)},
	{2080, Date(2080, 1, 22)},
	{2081, Date(2081, 2, 9)},
	{2082, Date(2082, 1, 29)},
	{2083, Date(2083, 2, 17)},
	{2084, Date(2084, 2, 6)},
	{2085, Date(2085, 1, 26)},
	{2086, Date(2086, 2, 14)},
	{2087, Date(2087, 2, 3)},
	{2088, Date(2088, 1, 23)},
	{2089, Date(2089, 2, 10)},
	{2090, Date(2090, 1, 30)},
	{2091, Date(2091, 2, 18)},
	{2092, Date(2092, 2, 7)},
	{2093, Date(2093, 1, 27)},
	{2094, Date(2094, 2, 15)},
	{2095, Date(2095, 2, 4)},
	{2096, Date(2096, 1, 24)},
	{2097, Date(2097, 2, 11)},
	{2098, Date(2098, 1, 31)},
	{2099, Date(2099, 2, 19)},
	{2100, Date(2100, 2, 8)}};