#ifndef __CA_CALENDAR_H__
#define __CA_CALENDAR_H__
#include "CalendarDefine.h"
#include "LiturgicYear.h"
#include <map>

using namespace CathAssist::Calendar;

namespace CathAssist
{
	namespace Calendar
	{
		class Calendar
		{
        public:
            static void initCalendar();
            static void releaseCalendar();
            
		public:
            static LiturgicDay getLiturgicDay(const Date& d);
            static LiturgicDay getLiturgicDay(const int& year, const int& month,const int& day);
            
        private:
            static std::map<int,LiturgicYear*> mapLiturgicYear;
		};
	}
}

#endif	//__CA_CALENDAR_H__
