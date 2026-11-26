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
#include <utility>
#include <iomanip>

#define LOWORD(x) (x & 0x0000FFFF)
#define HIWORD(x) ((x & 0xFFFF0000) >> 16)
#define MAKELONG(x, y) ((y << 16) | x)

using namespace CathAssist::Calendar;

template <typename T>
inline const T &Min(const T &a, const T &b) { return (a < b) ? a : b; }

enum
{
	FIRST_YEAR = -4713,
	FIRST_MONTH = 1,
	FIRST_DAY = 2, // ### Qt 5: make FIRST_DAY = 1, by support jd == 0 as valid
	SECS_PER_DAY = 86400,
	MSECS_PER_DAY = 86400000,
	SECS_PER_HOUR = 3600,
	MSECS_PER_HOUR = 3600000,
	SECS_PER_MIN = 60,
	MSECS_PER_MIN = 60000,
	JULIAN_DAY_FOR_EPOCH = 2440588 // result of julianDayFromGregorianDate(1970, 1, 1)
};

static const char monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
	return (1461 * (year + 4800 + (month - 14) / 12)) / 4 + (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12 - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075;
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
		return (153 * (month + (12 * a) - 3) + 2) / 5 + (1461 * (year + 4800 - a)) / 4 + day - 32083;
	}
	else
	{
		// the day following October 4, 1582 is October 15, 1582
		return 0;
	}
}

static void getDateFromJulianDay(unsigned int julianDay, int &year, int &month, int &day)
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

bool Date::isValid(const int &year, const int &month, const int &day)
{
	if (year < FIRST_YEAR || (year == FIRST_YEAR && (month < FIRST_MONTH || (month == FIRST_MONTH && day < FIRST_DAY))) || year == 0) // there is no year 0 in the Julian calendar
		return false;

	// passage from Julian to Gregorian calendar
	if (year == 1582 && month == 10 && day > 4 && day < 15)
		return 0;

	return (day > 0 && month > 0 && month <= 12) &&
		   (day <= monthDays[month] || (day == 29 && month == 2 && isLeapYear(year)));
}

bool Date::isLeapYear(const int &year)
{
	int y = year;
	if (y < 1582)
	{
		if (y < 1)
		{ // No year 0 in Julian calendar, so -1, -5, -9 etc are leap years
			++y;
		}
		return y % 4 == 0;
	}
	else
	{
		return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
	}
}

namespace
{
struct MonthDay
{
    int month;
    int day;

    bool matches(const Date &date) const
    {
        return month == date.month() && day == date.day();
    }
};

struct RegionalDate
{
    MonthDay china;
    std::map<langcode_t, MonthDay> overrides;

    RegionalDate(int month, int day, std::map<langcode_t, MonthDay> overrides = {})
        : china{month, day}, overrides(std::move(overrides)) {}

    bool matches(const Date &date, langcode_t lang) const
    {
        const auto it = overrides.find(lang);
        const MonthDay &local = it == overrides.end() ? china : it->second;
        return local.matches(date);
    }
};

struct LunarHolidays
{
    RegionalDate newYear;
    RegionalDate midAutumn;
};

// Each festival starts with the Chinese Gregorian month/day (Hong Kong Observatory).
// Record a language override only when its date differs. Korean dates use ICU Dangi and Time4J.
const std::map<int, LunarHolidays> lunarHolidays = {
	{1901, {{2, 19}, {9, 27}}},
	{1902, {{2, 8}, {9, 16}}},
	{1903, {{1, 29}, {10, 5}}},
	{1904, {{2, 16}, {9, 24}}},
	{1905, {{2, 4}, {9, 13}}},
	{1906, {{1, 25}, {10, 2}}},
	{1907, {{2, 13}, {9, 22}}},
	{1908, {{2, 2}, {9, 10}}},
	{1909, {{1, 22}, {9, 28}}},
	{1910, {{2, 10}, {9, 18}}},
	{1911, {{1, 30}, {10, 6}}},
	{1912, {{2, 18}, {9, 25}}},
	{1913, {{2, 6}, {9, 15}}},
	{1914, {{1, 26}, {10, 4}}},
	{1915, {{2, 14}, {9, 23}}},
	{1916, {{2, 3, {{LANG_KO_KR, {2, 4}}}}, {9, 12}}},
	{1917, {{1, 23}, {9, 30}}},
	{1918, {{2, 11}, {9, 19}}},
	{1919, {{2, 1}, {10, 8}}},
	{1920, {{2, 20}, {9, 26}}},
	{1921, {{2, 8}, {9, 16}}},
	{1922, {{1, 28}, {10, 5}}},
	{1923, {{2, 16}, {9, 25}}},
	{1924, {{2, 5}, {9, 13}}},
	{1925, {{1, 24}, {10, 2}}},
	{1926, {{2, 13}, {9, 21}}},
	{1927, {{2, 2}, {9, 10}}},
	{1928, {{1, 23}, {9, 28}}},
	{1929, {{2, 10}, {9, 17}}},
	{1930, {{1, 30}, {10, 6}}},
	{1931, {{2, 17}, {9, 26}}},
	{1932, {{2, 6}, {9, 15}}},
	{1933, {{1, 26}, {10, 4}}},
	{1934, {{2, 14}, {9, 23}}},
	{1935, {{2, 4}, {9, 12}}},
	{1936, {{1, 24}, {9, 30}}},
	{1937, {{2, 11}, {9, 19}}},
	{1938, {{1, 31}, {10, 8}}},
	{1939, {{2, 19}, {9, 27}}},
	{1940, {{2, 8}, {9, 16}}},
	{1941, {{1, 27}, {10, 5}}},
	{1942, {{2, 15}, {9, 24, {{LANG_KO_KR, {9, 25}}}}}},
	{1943, {{2, 5}, {9, 14}}},
	{1944, {{1, 25, {{LANG_KO_KR, {1, 26}}}}, {10, 1}}},
	{1945, {{2, 13}, {9, 20}}},
	{1946, {{2, 2}, {9, 10}}},
	{1947, {{1, 22}, {9, 29}}},
	{1948, {{2, 10}, {9, 17}}},
	{1949, {{1, 29}, {10, 6}}},
	{1950, {{2, 17}, {9, 26}}},
	{1951, {{2, 6}, {9, 15}}},
	{1952, {{1, 27}, {10, 3}}},
	{1953, {{2, 14}, {9, 22}}},
	{1954, {{2, 3, {{LANG_KO_KR, {2, 4}}}}, {9, 11}}},
	{1955, {{1, 24}, {9, 30}}},
	{1956, {{2, 12}, {9, 19}}},
	{1957, {{1, 31}, {9, 8}}},
	{1958, {{2, 18, {{LANG_KO_KR, {2, 19}}}}, {9, 27}}},
	{1959, {{2, 8}, {9, 17}}},
	{1960, {{1, 28}, {10, 5}}},
	{1961, {{2, 15}, {9, 24}}},
	{1962, {{2, 5}, {9, 13}}},
	{1963, {{1, 25}, {10, 2}}},
	{1964, {{2, 13}, {9, 20}}},
	{1965, {{2, 2}, {9, 10}}},
	{1966, {{1, 21, {{LANG_KO_KR, {1, 22}}}}, {9, 29}}},
	{1967, {{2, 9}, {9, 18}}},
	{1968, {{1, 30}, {10, 6}}},
	{1969, {{2, 17}, {9, 26}}},
	{1970, {{2, 6}, {9, 15}}},
	{1971, {{1, 27}, {10, 3}}},
	{1972, {{2, 15}, {9, 22}}},
	{1973, {{2, 3}, {9, 11}}},
	{1974, {{1, 23}, {9, 30}}},
	{1975, {{2, 11}, {9, 20}}},
	{1976, {{1, 31}, {9, 8}}},
	{1977, {{2, 18}, {9, 27}}},
	{1978, {{2, 7}, {9, 17}}},
	{1979, {{1, 28}, {10, 5}}},
	{1980, {{2, 16}, {9, 23}}},
	{1981, {{2, 5}, {9, 12}}},
	{1982, {{1, 25}, {10, 1}}},
	{1983, {{2, 13}, {9, 21}}},
	{1984, {{2, 2}, {9, 10}}},
	{1985, {{2, 20}, {9, 29}}},
	{1986, {{2, 9}, {9, 18}}},
	{1987, {{1, 29}, {10, 7}}},
	{1988, {{2, 17, {{LANG_KO_KR, {2, 18}}}}, {9, 25}}},
	{1989, {{2, 6}, {9, 14}}},
	{1990, {{1, 27}, {10, 3}}},
	{1991, {{2, 15}, {9, 22}}},
	{1992, {{2, 4}, {9, 11}}},
	{1993, {{1, 23}, {9, 30}}},
	{1994, {{2, 10}, {9, 20}}},
	{1995, {{1, 31}, {9, 9}}},
	{1996, {{2, 19}, {9, 27}}},
	{1997, {{2, 7, {{LANG_KO_KR, {2, 8}}}}, {9, 16}}},
	{1998, {{1, 28}, {10, 5}}},
	{1999, {{2, 16}, {9, 24}}},
	{2000, {{2, 5}, {9, 12}}},
	{2001, {{1, 24}, {10, 1}}},
	{2002, {{2, 12}, {9, 21}}},
	{2003, {{2, 1}, {9, 11}}},
	{2004, {{1, 22}, {9, 28}}},
	{2005, {{2, 9}, {9, 18}}},
	{2006, {{1, 29}, {10, 6}}},
	{2007, {{2, 18}, {9, 25}}},
	{2008, {{2, 7}, {9, 14}}},
	{2009, {{1, 26}, {10, 3}}},
	{2010, {{2, 14}, {9, 22}}},
	{2011, {{2, 3}, {9, 12}}},
	{2012, {{1, 23}, {9, 30}}},
	{2013, {{2, 10}, {9, 19}}},
	{2014, {{1, 31}, {9, 8}}},
	{2015, {{2, 19}, {9, 27}}},
	{2016, {{2, 8}, {9, 15}}},
	{2017, {{1, 28}, {10, 4}}},
	{2018, {{2, 16}, {9, 24}}},
	{2019, {{2, 5}, {9, 13}}},
	{2020, {{1, 25}, {10, 1}}},
	{2021, {{2, 12}, {9, 21}}},
	{2022, {{2, 1}, {9, 10}}},
	{2023, {{1, 22}, {9, 29}}},
	{2024, {{2, 10}, {9, 17}}},
	{2025, {{1, 29}, {10, 6}}},
	{2026, {{2, 17}, {9, 25}}},
	{2027, {{2, 6, {{LANG_KO_KR, {2, 7}}}}, {9, 15}}},
	{2028, {{1, 26, {{LANG_KO_KR, {1, 27}}}}, {10, 3}}},
	{2029, {{2, 13}, {9, 22}}},
	{2030, {{2, 3}, {9, 12}}},
	{2031, {{1, 23}, {10, 1}}},
	{2032, {{2, 11}, {9, 19}}},
	{2033, {{1, 31}, {9, 8}}},
	{2034, {{2, 19}, {9, 27}}},
	{2035, {{2, 8}, {9, 16}}},
	{2036, {{1, 28}, {10, 4}}},
	{2037, {{2, 15}, {9, 24}}},
	{2038, {{2, 4}, {9, 13}}},
	{2039, {{1, 24}, {10, 2}}},
	{2040, {{2, 12}, {9, 20, {{LANG_KO_KR, {9, 21}}}}}},
	{2041, {{2, 1}, {9, 10}}},
	{2042, {{1, 22}, {9, 28}}},
	{2043, {{2, 10}, {9, 17}}},
	{2044, {{1, 30}, {10, 5}}},
	{2045, {{2, 17}, {9, 25}}},
	{2046, {{2, 6}, {9, 15}}},
	{2047, {{1, 26}, {10, 4}}},
	{2048, {{2, 14}, {9, 22}}},
	{2049, {{2, 2}, {9, 11}}},
	{2050, {{1, 23}, {9, 30}}},
	{2051, {{2, 11}, {9, 19}}},
	{2052, {{2, 1}, {9, 7}}},
	{2053, {{2, 19}, {9, 26}}},
	{2054, {{2, 8}, {9, 16}}},
	{2055, {{1, 28}, {10, 5}}},
	{2056, {{2, 15}, {9, 24}}},
	{2057, {{2, 4}, {9, 13}}},
	{2058, {{1, 24}, {10, 2}}},
	{2059, {{2, 12}, {9, 21}}},
	{2060, {{2, 2}, {9, 9}}},
	{2061, {{1, 21, {{LANG_KO_KR, {1, 22}}}}, {9, 28}}},
	{2062, {{2, 9}, {9, 17}}},
	{2063, {{1, 29}, {10, 6}}},
	{2064, {{2, 17}, {9, 25}}},
	{2065, {{2, 5}, {9, 15}}},
	{2066, {{1, 26}, {10, 3}}},
	{2067, {{2, 14}, {9, 23}}},
	{2068, {{2, 3}, {9, 11}}},
	{2069, {{1, 23}, {9, 29}}},
	{2070, {{2, 11}, {9, 19}}},
	{2071, {{1, 31}, {9, 8}}},
	{2072, {{2, 19}, {9, 26}}},
	{2073, {{2, 7}, {9, 16}}},
	{2074, {{1, 27}, {10, 5}}},
	{2075, {{2, 15}, {9, 24}}},
	{2076, {{2, 5}, {9, 12}}},
	{2077, {{1, 24}, {10, 1}}},
	{2078, {{2, 12}, {9, 20}}},
	{2079, {{2, 2}, {9, 10}}},
	{2080, {{1, 22}, {9, 28}}},
	{2081, {{2, 9}, {9, 17}}},
	{2082, {{1, 29}, {10, 6}}},
	{2083, {{2, 17}, {9, 26}}},
	{2084, {{2, 6}, {9, 14}}},
	{2085, {{1, 26}, {10, 3}}},
	{2086, {{2, 14}, {9, 22}}},
	{2087, {{2, 3}, {9, 11}}},
	{2088, {{1, 24}, {9, 29}}},
	{2089, {{2, 10, {{LANG_KO_KR, {2, 11}}}}, {9, 18, {{LANG_KO_KR, {9, 19}}}}}},
	{2090, {{1, 30}, {9, 8}}},
	{2091, {{2, 18}, {9, 27}}},
	{2092, {{2, 7, {{LANG_KO_KR, {2, 8}}}}, {9, 16}}},
	{2093, {{1, 27}, {10, 5}}},
	{2094, {{2, 15}, {9, 24}}},
	{2095, {{2, 5}, {9, 13}}},
	{2096, {{1, 25}, {9, 30, {{LANG_KO_KR, {10, 1}}}}}},
	{2097, {{2, 12}, {9, 20}}},
	{2098, {{2, 1}, {9, 9, {{LANG_KO_KR, {9, 10}}}}}},
	{2099, {{1, 21}, {9, 29}}},
	{2100, {{2, 9}, {9, 18}}},
};
}

bool Date::isSpringFestival(const Date &d, langcode_t lang)
{
    if (lang != LANG_ZH_CN && lang != LANG_ZH_TW && lang != LANG_KO_KR)
        return false;
    const auto year = lunarHolidays.find(d.year());
    return year != lunarHolidays.end() && year->second.newYear.matches(d, lang);
}

bool Date::isNewYearEve(const Date &d, langcode_t lang)
{
    return isSpringFestival(d.addDays(1), lang);
}

bool Date::isMidAutumnFestival(const Date &d, langcode_t lang)
{
    const auto year = lunarHolidays.find(d.year());
    return year != lunarHolidays.end() && year->second.midAutumn.matches(d, lang);
}

bool Date::isChuseok(const Date &d, langcode_t lang)
{
    return lang == LANG_KO_KR && isMidAutumnFestival(d, lang);
}

Date Date::getCurrentDate(void)
{
	time_t now = time(0);
	struct tm *ltm = localtime(&now);
	return Date(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday);
}

Date::Date(void)
{
	jd = 0;
}

Date::Date(const int &year, const int &month, const int &day)
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
	int y = 0, m = 0, d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return y;
}

int Date::month() const
{
	int y = 0, m = 0, d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return m;
}

int Date::day() const
{
	int y = 0, m = 0, d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return d;
}

day_t Date::dayOfWeek() const
{
	int w = (jd % 7) + 1;

	return static_cast<day_t>(w % 7);
}

int Date::dayOfYear() const
{
	return jd - julianDayFromDate(year(), 1, 1) + 1;
}

int Date::daysInMonth() const
{
	int y = 0, m = 0, d = 0;
	getDateFromJulianDay(jd, y, m, d);
	if (m == 2 && isLeapYear(y))
		return 29;
	else
		return monthDays[m];
}

int Date::daysInYear() const
{
	int y = 0, m = 0, d = 0;
	getDateFromJulianDay(jd, y, m, d);
	return isLeapYear(y) ? 366 : 365;
}

int Date::weekNumber(int *yearNumber /*= 0*/) const
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
		if (yday >= top)
		{
			++year;
			w = 1;
			break;
		}
		if (yday >= bot)
		{
			w = 1 + ((yday - bot) / 7);
			break;
		}
		--year;
		yday += isLeapYear(year) ? 366 : 365;
	}
	if (yearNumber != 0)
		*yearNumber = year;

	if (wday == 0)
		w += 1;
	return w;
}

bool Date::setYMD(const int &year, const int &month, const int &day)
{
	int y = year;
	if ((unsigned int)(y) <= 99)
		y += 1900;
	return setDate(y, month, day);
}

bool Date::setDate(const int &year, const int &month, const int &day)
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

void Date::getDate(int &year, int &month, int &day)
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
			nmonths += 12;
		}
		else if (nmonths < 0)
		{
			m += nmonths;
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

	int y = 0, m = 0, d = 0;
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

int Date::daysTo(const Date &d) const
{
	return d.jd - jd;
}

std::string Date::toString() const
{
	if (year() > 9999)
		return std::string();

	// 格式化输出
	std::ostringstream ostr;
	ostr << Date::year() << "-"
		 << std::setfill('0') << std::setw(2) << Date::month() << "-"
		 << std::setfill('0') << std::setw(2) << Date::day();

	return ostr.str();
}
