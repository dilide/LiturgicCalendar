/*
============================================================================
文件名称	:	LiturgicDay.h
公司		:	CathAssist
作者		:	李亚科
创建时间	:	2014-06-12 21:27
修改时间	:	2014-06-12 22:30
说明		:	用于计算礼仪年
============================================================================
*/
#ifndef __CA_CALENDAR_LITURGIC_DAY_H__
#define __CA_CALENDAR_LITURGIC_DAY_H__
#include "Date.h"
#include <list>
#include <map>

namespace CathAssist
{
	namespace Calendar
	{
        typedef struct CellInfo
        {
            int code = -1;              //节日编码
            rank_t rank;                //优先级
            color_t color;              //祭衣颜色
            std::string celebration;    //节日
            int cycleOfReadings = 1;    //读经循环（如：主日读经三年一循环，平日读经两年一循环）
			CellInfo(int code, rank_t r, color_t c, const std::string& cel, int cycleOfReadings)
			{
                this->code = code;
				this->rank = r;
                this->color = c;
                celebration = cel;
                this->cycleOfReadings = cycleOfReadings;
			}
            
            CellInfo(rank_t r, color_t c, const std::string& cel)
                : CellInfo(-1, r, c, cel, 1)
            {
            }

			std::string toString()
			{
				std::ostringstream ostr;
				ostr<<celebration;
				/*
				if(rank == MEMORIAL)
				{
					ostr<<"(纪)";
				}
				else if(rank == FEAST)
				{
					ostr<<"(庆)";
				}
				else if(rank == LORD)
				{
					ostr<<"(庆)";
				}
                */
                if(code > 0) {
                    ostr<<"\\\\"<<code;
                }

				return ostr.str();
			}
        } CellInfo_t;
        
        typedef std::multimap<rank_t,CellInfo> CellMap;
        
        class LiturgicDay : public Date
        {
        public:
            static std::string getWeekdayString(int code);
            static std::string getWeekdayString(const season_t& season, const int& weekOfSeason, const int& dayOfWeek);
            
        public:
            LiturgicDay();
            LiturgicDay(const Date& d);
            LiturgicDay(const int& year, const int& month, const int& day);
            ~LiturgicDay();

        public:
            season_t getSeason(){ return season; }
            void setSeason(season_t s){ season = s; }

			//获取祭衣颜色（取优先级最高的节日颜色）
			color_t getColor() const;

			//获取礼仪年第N主日
			int getWeekOfSeason() const{ return weekOfSeason; }
			//设置礼仪年第N主日
			void setWeekOfSeason(const int& w){ weekOfSeason = w; }

			// 获取礼仪年的唯一标识
			// 规则：采用十进制（共六位）
			// 前面两位为：Season
			// 中间两位为：主日编号
			// 最后两位为：星期几
			int getLiturgicId() const;

			std::list<CellInfo> getCellInfos() const;
            std::list<int> getCellsId() const{ return listCell; }
			void appendCell(const int& id);

			CellInfo getLiturgicCellInfo() const;

//          rank_t getRank(){ return rank; }
//          void setRank(rank_t r){ rank = r; }
            
//          std::string getCelebration()const{ return celebration; }
//          void setCelebration(const std::string& c){ celebration = c; }
            
//          std::string getInvitatory()const{ return invitatory; }
//          void setInvitatory(const std::string& i){ invitatory = i; }
            
			std::string toWeekdayString() const;

            std::string toLiturgicString() const;
            
        private:
            season_t season;            // Advent, Lent, Ordinary, etc.
			int weekOfSeason;			// Week of season

			//节日数据列表
			std::list<int> listCell;
            
//            std::string invitatory;		// Invitatory of the day, 好像是当天选用的读经，暂时未使用
        };
    }
}

#endif	//__CA_CALENDAR_LITURGIC_YEAR_H__
