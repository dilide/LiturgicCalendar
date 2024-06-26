/*
============================================================================
文件名称	:	LiturgicYear.h
公司		:	CathAssist
作者		:	李亚科
创建时间	:	2014-06-12 12:27
修改时间	:	2014-06-12 12:30
说明		:	用于计算礼仪年
============================================================================
*/
#ifndef __CA_CALENDAR_LITURGIC_YEAR_H__
#define __CA_CALENDAR_LITURGIC_YEAR_H__
#include "LiturgicDay.h"

namespace CathAssist
{
	namespace Calendar
	{   
		class LiturgicYear
		{
		public:
			static void initPropers();
			static std::multimap<int,CellInfo> getPropers(){ return mapPropers; }
            static std::list<CellInfo> getNormalDays();
			static CellInfo getCellInfo(const int& id);

		public:
			LiturgicYear(const int& year);
			~LiturgicYear(void);

		public:
            LiturgicDay getLiturgicDay(const Date& d);
            std::string toString() const;

		private:
			void init();

			//测试1月1日以后的圣诞期
			void testChristmas1(LiturgicDay& ld);
			//测试四旬期
			void testLent(LiturgicDay& ld);
			//测试复活期
			void testEaster(LiturgicDay& ld);
			//测试将临期
			void testAdvent(LiturgicDay& ld);
			//测试12月25日以后的圣诞期
			void testChristmas2(LiturgicDay& ld);
			//测试常年期前半段
			void testOrdinary1(LiturgicDay& ld);
			//测试常年期后半段
			void testOrdinary2(LiturgicDay& ld);
			//测试正常情况下的节日
			void testProper(LiturgicDay& ld);

		private:
			//礼仪年中的关键日期
            Date ep;         // Epiphany of the Lord     主显节
			LiturgicDay bl;			// End of Christmas season	上一年圣诞期的结束日（主受洗日）
			LiturgicDay aw;			// Ash Wednesday			圣灰礼仪周三（四旬期开始）
            LiturgicDay easter;     // Easter sunday            复活节（主日）
			LiturgicDay ps;			// Pentecost Sunday			圣神降临节（复活期结束）
			LiturgicDay av;			// First Sunday of Advent	将临期第一主日，将临期的开始
			LiturgicDay cm;		// Christmas				圣诞节（圣诞期的开始）
            
            int year;           // Current year             当前年份

			static std::multimap<int,CellInfo> mapPropers;
		};
	}
}

#endif	//__CA_CALENDAR_LITURGIC_YEAR_H__
