# Liturgic Calendar

LiturgicCalendar is a program that generates the General Roman Calendar of the Catholic Church.

## Purpose

This project is desgined for [CathAssist](http://www.cathassist.org).

## Architecture

### Date.h

- Use Julian Day store the date
- Provide lunar for Chinese (1901 ~ 2050)

### CalendarDefile.h

- Define week/month/color etc
- Liturgical ranks represent how important the day is.

## How to compile

This project used CMake to compile, for more information please visit: [CMake](https://cmake.org/).

```bash
# Use `cmake` to generate makefile
cmake .
# make the project
make
```

## How to use

Sample in test/liturgy_calendar_test.cpp

1. include "Calendar.h"
2. init the calendar by 'Calendar::initCalendar()'
3. just get the LiturgicDay by static method 'Calendar::getLiturgicDay(inputDate)'
4. after all, release the calendar by 'Calendar::releaseCalendar()'

## Thanks

- [Romcal](http://www.romcal.net/)
- [我灵赞颂主](http://www.mhchina.net/)