﻿/*
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

int LiturgicDay::getLiturgicId()
{
	return season*10000+weekOfSeason*100+dayOfWeek();
}

std::list<CellInfo> LiturgicDay::getCellInfos() const
{
    std::list<CellInfo> cells;

	for(int r = CathAssist::Calendar::SOLEMNITY; r>=WEEKDAY; --r)
	{
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
			//重新计算主日和平日信息
			if(r == CathAssist::Calendar::SUNDAY && dayOfWeek()==0)
			{
				//主日
				CellInfo c = getLiturgicCellInfo();
				if(c.rank != ErrorRank)
				{
					cells.push_back(c);
				}
			}
			else if(r == CathAssist::Calendar::WEEKDAY && dayOfWeek()!=0)
			{
				//平日
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
		if(getWeekOfSeason()==1 || getWeekOfSeason()==2&&dayOfWeek()==0)
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
		Date dayChristmas((month()<12 ? year()-1 : year()),12,25);
		int iAbsChristmas = abs(daysTo(dayChristmas));
		if(iAbsChristmas<8 && iAbsChristmas>0)
		{
			//圣诞庆期八日（第八日是天主之母节）
			std::ostringstream ostr;
			ostr<<"圣诞节庆期第"<<getChineseNumStr(iAbsChristmas+1)<<"日";
			return CellInfo(_rank,WHITE,ostr.str());
		}
		else
		{
			_clr = WHITE;
		}
	}

	return CellInfo(_rank,_clr,toWeekdayString());
}

std::string LiturgicDay::toWeekdayString() const
{
	std::ostringstream ostr;
	if(dayOfWeek()==SUN)
	{
		ostr<<CathAssist::Calendar::getSeasonStr(season)
			<<"第"<<getChineseNumStr(weekOfSeason)<<"主日";
	}
	else
	{
		ostr<<CathAssist::Calendar::getSeasonStr(season)
			<<"第"<<getChineseNumStr(weekOfSeason)<<"周("<<CathAssist::Calendar::getDayStr(dayOfWeek())<<")";
	}

	return ostr.str();
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
