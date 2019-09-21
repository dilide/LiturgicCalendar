#include "Calendar.h"

std::map<int,LiturgicYear*> CathAssist::Calendar::Calendar::mapLiturgicYear;


LiturgicDay CathAssist::Calendar::Calendar::getLiturgicDay(const Date& d)
{
    LiturgicYear* pYear = NULL;
    int year = d.year();
    std::map<int,LiturgicYear*>::iterator iter = mapLiturgicYear.find(year);
    if(iter==mapLiturgicYear.end())
    {
        pYear = new LiturgicYear(year);
        mapLiturgicYear[year] = pYear;
    }
    else
    {
        pYear = iter->second;
    }

    return pYear->getLiturgicDay(d);
}

LiturgicDay CathAssist::Calendar::Calendar::getLiturgicDay(const int& year, const int& month,const int& day)
{
    return getLiturgicDay(Date(year,month,day));
}

void CathAssist::Calendar::Calendar::initCalendar()
{
	//初始化硬性规定的节日
	LiturgicYear::initPropers();
}

void CathAssist::Calendar::Calendar::releaseCalendar()
{
    std::map<int,LiturgicYear*>::iterator iter = mapLiturgicYear.begin();
    while(iter!=mapLiturgicYear.end())
    {
        delete iter->second;
        
        ++iter;
    }
    
    mapLiturgicYear.clear();
}
