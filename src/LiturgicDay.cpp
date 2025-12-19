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
#include "MultiLang.h"
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
		CellInfo normalCell(ErrorRank, NOCOLOR, "");
		if(r == CathAssist::Calendar::WEEKDAY && dayOfWeek()!=0) {
			//平日
			normalCell = getLiturgicCellInfo();
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

		if(normalCell.rank != ErrorRank)
		{
			cells.push_back(normalCell);
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
		/*
		if(dayOfWeek()==SUN) {
			// 圣诞期所有主日都是特殊的
			_rank = ErrorRank;
		}
		*/
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

	CathAssist::Calendar::LanguageCodes lang = CathAssist::Calendar::MultiLang::getLangCode();

	if(CathAssist::Calendar::LANG_ZH_CN == lang) {
		if(LENT == season && 0 == weekOfSeason) {
			if(dayOfWeek != 3) {
				ostr<<"圣灰礼仪后" + CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang);
				return ostr.str();
			}
		}

		if(dayOfWeek==SUN)
		{
			ostr<<CathAssist::Calendar::getSeasonStr(season, lang)
				<<"第"<<getOrdinalStr(weekOfSeason, lang)<<"主日";
		}
		else
		{
			ostr<<CathAssist::Calendar::getSeasonStr(season, lang)
				<<"第"<<getOrdinalStr(weekOfSeason, lang)<<"周("<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)<<")";
		}
	} else if(CathAssist::Calendar::LANG_ZH_TW == lang) {
		if(LENT == season && 0 == weekOfSeason) {
			if(dayOfWeek != 3) {
				ostr<<"聖灰禮儀後" + CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang);
				return ostr.str();
			}
		}

		if(dayOfWeek==SUN)
		{
			ostr<<CathAssist::Calendar::getSeasonStr(season, lang)
				<<"第"<<getOrdinalStr(weekOfSeason, lang)<<"主日";
		}
		else
		{
			ostr<<CathAssist::Calendar::getSeasonStr(season, lang)
				<<"第"<<getOrdinalStr(weekOfSeason, lang)<<"週("<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)<<")";
		}
	} else if(CathAssist::Calendar::LANG_EN == lang) {
		if(LENT == season && 0 == weekOfSeason) {
			if(dayOfWeek != 3) {
				ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)<<" after Ash Wednesday";
				return ostr.str();
			}
		}

		if(dayOfWeek==SUN)
		{
			ostr<<getOrdinalStr(weekOfSeason, lang)
				<<" "<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" in "<<CathAssist::Calendar::getSeasonStr(season, lang);
		}
		else
		{
			ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" of "<<getOrdinalStr(weekOfSeason, lang)
				<<" Week in " << CathAssist::Calendar::getSeasonStr(season, lang);
		}
	} else if(CathAssist::Calendar::LANG_ES_ES == lang) {
		if(LENT == season && 0 == weekOfSeason) {
			if(dayOfWeek != 3) {
				ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)<<" después de ceniza";
				return ostr.str();
			}
		}
		if(dayOfWeek==SUN)
		{
			ostr<<getOrdinalStr(weekOfSeason, lang)
				<<" "<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" de la "<<CathAssist::Calendar::getSeasonStr(season, lang);
		}
		else
		{
			ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" de la "<<getOrdinalStr(weekOfSeason, lang)
				<<" semana de " << CathAssist::Calendar::getSeasonStr(season, lang);
		}
	} else if(CathAssist::Calendar::LANG_IT_IT == lang) {
		if(LENT == season && 0 == weekOfSeason) {
			if(dayOfWeek != 3) {
				ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)<<" dopo le Ceneri";
				return ostr.str();
			}
		}

		if(dayOfWeek==SUN)
		{
			ostr<<getOrdinalStr(weekOfSeason, lang)
				<<" "<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" "<<getPrepGenderStr(season, lang)<<" "<<CathAssist::Calendar::getSeasonStr(season, lang);
		}
		else
		{
			ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" della "<<getOrdinalStr(weekOfSeason, lang)
				<<" settimana "<<getPrepGenderStr(season, lang)<<" " << CathAssist::Calendar::getSeasonStr(season, lang);
		}
	} else if(CathAssist::Calendar::LANG_PT_BR == lang) {
		if(LENT == season && 0 == weekOfSeason) {
			if(dayOfWeek != 3) {
				ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)<<" depois das Cinzas";
				return ostr.str();
			}
		}

		if(dayOfWeek==SUN)
		{
			ostr<<getOrdinalStr(weekOfSeason, lang)
				<<" "<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" da "<<CathAssist::Calendar::getSeasonStr(season, lang);
		}
		else
		{
			ostr<<CathAssist::Calendar::getDayStr((day_t)dayOfWeek, lang)
				<<" da "<<getOrdinalStr(weekOfSeason, lang)
				<<" semana " << CathAssist::Calendar::getSeasonStr(season, lang);
		}
	}

	return ostr.str();
}

