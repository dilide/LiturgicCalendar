/*
============================================================================
文件名称	:	LiturgicDay.cpp
公司		:	CathAssist
作者		:	李亚科
创建时间	:	2014-06-12 20:27
修改时间	:	2014-06-12 22:30
说明		:	用于计算礼仪年
============================================================================
*/

#include "LiturgicDay.h"
#include "LiturgicYear.h"
#include <sstream>
#include <iomanip>

using namespace CathAssist::Calendar;

LiturgicDay::LiturgicDay()
    : Date()
    , season(ORDINARY)
{
}

LiturgicDay::LiturgicDay(const Date& d)
    : Date(d)
    , season(ORDINARY)
{
    
}

LiturgicDay::LiturgicDay(const int& year, const int& month, const int& day)
    : Date(year,month,day)
    , season(ORDINARY)
{
    
}

LiturgicDay::~LiturgicDay()
{
    
}

color_t LiturgicDay::getColor() const
{
	std::list<CellInfo> cells = getCellInfos();

	auto iter = cells.begin();
	while(iter != cells.end())
	{
		if(NOCOLOR != iter->color)
			return iter->color;
		++iter;
	}

	return NOCOLOR;
}

int LiturgicDay::getLiturgicId() const
{
	if(weekOfSeason > -1) {
		return season*10000+weekOfSeason*100+dayOfWeek();
	} else {
		return season*10000+0*100+dayOfWeek();
	}
}

std::list<CellInfo> LiturgicDay::getCellInfos() const
{
    std::list<CellInfo> cells;

	for(int r = CathAssist::Calendar::SOLEMNITY; r>=WEEKDAY; --r)
	{
		if(r == CathAssist::Calendar::WEEKDAY && dayOfWeek()!=0) {
			//平日
			CellInfo c = getLiturgicCellInfo();
			if(c.rank != ErrorRank)
			{
				cells.push_back(c);
			}
		}

		//特殊节日
		int iCount = 0;
		auto iter = listCell.begin();
		while (iter!=listCell.end())
		{
			CellInfo c = LiturgicYear::getCellInfo(*iter);
			if(c.rank == r)
			{
				cells.push_back(c);
				++iCount;
			}

			++iter;
		}

		if(iCount<1)
		{
			//计算特殊主日
			if(r == CathAssist::Calendar::SUNDAY && dayOfWeek()==0)
			{
				//主日
				CellInfo c = getLiturgicCellInfo();
				if(c.rank != ErrorRank)
				{
					cells.push_back(c);
				}
			}
		}
	}
    
    return cells;
}

void CathAssist::Calendar::LiturgicDay::appendCell(const int& id)
{
	listCell.push_back(id);
}

CellInfo LiturgicDay::getLiturgicCellInfo() const
{
	Colors _clr = NOCOLOR;
	rank_t _rank = WEEKDAY;

	if(dayOfWeek()==SUN)
	{
		_rank = SUNDAY;
	}

	if(ORDINARY == season)
	{
		_clr = GREEN;
	}
	else if(LENT == season)
	{
		if(dayOfWeek()==SUN && getWeekOfSeason() == 4)
		{
			_clr = ROSE;
		}
		else
		{
			_clr = PURPLE;
		}
	}
	else if(EASTER == season)
	{
		if((getWeekOfSeason()==1 || getWeekOfSeason()==2) && dayOfWeek()==0)
		{
			//复活节八日庆典（已特殊定义）
			_rank = ErrorRank;
		}
		else
		{
			_clr = WHITE;
		}
	}
	else if(ADVENT == season)
	{
		if(dayOfWeek() == SUN && getWeekOfSeason()==3)
		{
			_clr = ROSE;
		}
		else
		{
			_clr = PURPLE;
		}
	}
	else if(CHRISTMAS == season)
	{
		if(dayOfWeek()==SUN) {
			// 圣诞期所有主日都是特殊的
			_rank = ErrorRank;
		}
		
		_clr = WHITE;
	}

	if(getWeekOfSeason() < 0) {
		_rank = ErrorRank;
	}
    
	return CellInfo(_rank, _clr, toWeekdayString());
}

std::string LiturgicDay::toWeekdayString() const
{
    return LiturgicDay::getWeekdayString(season, weekOfSeason, dayOfWeek());
}

std::string LiturgicDay::toLiturgicString() const
{
    //返回礼仪年日期对应的字符串，格式化输出本身
	std::ostringstream ostr;
    ostr<<"日期\t:\t"<<toString()<<std::endl;
    ostr<<"颜色\t:\t"<<CathAssist::Calendar::getColorStr(getColor())<<std::endl;
    
    
	std::list<CellInfo> cells = getCellInfos();
	auto iter = cells.begin();
    ostr<<"节日:\t"<<std::endl;
    while (iter!=cells.end())
    {
        ostr<<"    "<<iter->celebration<<std::endl;
        ++iter;
    }
    
    
    //ostr<<"Invit\t:\t"<<invitatory<<std::endl;
    
    
    return ostr.str();
}

std::string LiturgicDay::getWeekdayString(int code) { 
    int season = code/10000;
    int weekNum = (code%10000)/100;
    int dayNum = code%100;

    return LiturgicDay::getWeekdayString((season_t)season, weekNum, dayNum);
}


std::string LiturgicDay::getWeekdayString(const season_t &season, const int &weekOfSeason, const int &dayOfWeek) {
    std::ostringstream ostr;

	if(LENT == season && 0 == weekOfSeason) {
		if(dayOfWeek != 3) {
			ostr<<"圣灰礼仪后" + CathAssist::Calendar::getDayStr((day_t)dayOfWeek);
			return ostr.str();
		}
	}
	else if(CHRISTMAS == season)
	{
		ostr<<"主显节后 "<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek);
		return ostr.str();
	}

    if(dayOfWeek==SUN)
    {
        ostr<<CathAssist::Calendar::getSeasonStr(season)
            <<"第"<<getChineseNumStr(weekOfSeason)<<"主日";
    }
    else
    {
        ostr<<CathAssist::Calendar::getSeasonStr(season)
            <<"第"<<getChineseNumStr(weekOfSeason)<<"周("<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek)<<")";
    }

    return ostr.str();
}

