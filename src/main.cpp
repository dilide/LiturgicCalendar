//
// Created by Peter on 2022/1/11.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include "sqlite/sqlite3.h"
#include "CharConverter.h"
#include "Calendar.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using namespace std;
using namespace rapidjson;


std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

//创建数据库表
int create_tables(sqlite3* db)
{
    {
        std::string strSql = "create table saints("\
        "id integer primary key autoincrement,"\
        "key integer not null,"\
        "name text not null,"\
        "rank integer not null,"\
        "color integer not null"\
        ");";

        /* Execute SQL statement */
        if(sqlite3_exec(db, strSql.c_str(), NULL, 0, NULL))
        {
            std::cout<<"create table saints error!"<<std::endl;
            return -1;
        }
    }

    {
        std::string strSql = "create table calendar("\
        "id integer primary key autoincrement,"\
        "date date not null,"\
        "lunar text not null,"\
        "liturgic integer not null,"\
        "color integer not null,"\
        "cells text);";

        /* Execute SQL statement */
        if(sqlite3_exec(db, strSql.c_str(), NULL, 0, NULL))
        {
            std::cout<<"create table calendar error!"<<std::endl;
            return -1;
        }

        if(sqlite3_exec(db,"create index index_calendar_date on calendar (date);",0,0,0))
        {
            std::cout<<"create index error!"<<std::endl;
            return -1;
        }
    }



    return 1;
}

void export_month_json_test()
{
    std::string strRootPath = "month";

    //删除已存在的数据库文件
    remove(strRootPath.c_str());

    Calendar::initCalendar();

    system("rm -rf months");
    system("mkdir months");
    int lastYear = -1;
    int lastMonth = -1;
    std::string lastFileName = "";
    rapidjson::Document docMonth;
    docMonth.SetObject();
    rapidjson::Document::AllocatorType& allocator = docMonth.GetAllocator();
    rapidjson::Value* days = new rapidjson::Value(rapidjson::kArrayType);
    for(int iYear=2010;iYear<2051;++iYear)
    {
        CathAssist::Calendar::Date dtBegin(iYear,1,1);
        while (dtBegin.year()==iYear)
        {
            if(lastYear!= dtBegin.year() || lastMonth != dtBegin.month())
            {
                //save last month
                if(lastYear > 0)
                {
                    std::ostringstream tmp;
                    tmp<<lastYear<<setfill('0')<<setw(2)<<lastMonth;

                    docMonth.AddMember("month",Value(tmp.str().c_str(), allocator).Move(), allocator);
                    docMonth.AddMember("title",Value(getSpecialMonth(lastMonth).c_str(), allocator), allocator);
                    docMonth.AddMember("items", *days, allocator);
                    StringBuffer buffer;
                    PrettyWriter<StringBuffer> writer(buffer);
                    docMonth.Accept(writer);

                    std::ofstream of;
                    of.open(string("./months/") + tmp.str() + ".json");
                    of<<buffer.GetString();
                    of.close();

                    if(docMonth.IsObject()) {
                        docMonth.RemoveAllMembers();
                        delete days;
                        days = new rapidjson::Value(rapidjson::kArrayType);
                    }
                }

                lastYear = dtBegin.year();
                lastMonth = dtBegin.month();
                //docMonth.AddMember("items", days, allocator);
            }

            rapidjson::Value day(rapidjson::kObjectType);
            LiturgicDay dayInfo = Calendar::getLiturgicDay(dtBegin);

            day.AddMember("date", Value(dayInfo.toString().c_str(), allocator), allocator);
            day.AddMember("lunar", Value(dayInfo.toLunarString().c_str(), allocator), allocator);
            day.AddMember("color", Value(getColorValue(dayInfo.getColor()).c_str(), allocator), allocator);
            day.AddMember("colorStr", Value(getColorStr(dayInfo.getColor()).c_str(), allocator), allocator);

            rapidjson::Value liturgics(kArrayType);

            auto cells = dayInfo.getCellInfos();
            auto iterCell = cells.begin();
            while (iterCell!=cells.end())
            {
                if(iterCell->rank > ErrorRank)
                {
                    rapidjson::Value liturgic(rapidjson::kObjectType);
                    liturgic.AddMember("name", Value(iterCell->celebration.c_str(), allocator), allocator);
                    liturgic.AddMember("rank", Value(iterCell->rank), allocator);
                    liturgic.AddMember("code", Value(iterCell->code), allocator);

                    liturgics.PushBack(liturgic, allocator);
                }

                ++iterCell;
            }

            day.AddMember("liturgics", liturgics, allocator);

            days->PushBack(day, docMonth.GetAllocator());
            dtBegin = dtBegin.addDays(1);
        }
    }

    Calendar::releaseCalendar();
}

void export_to_sqlite()
{
    std::string strDbName = "liturgic.db";

    //删除已存在的数据库文件
    remove(strDbName.c_str());

    sqlite3* db;

    if(sqlite3_open(strDbName.c_str(), &db))
    {
        std::cout<<"open liturgic.db error"<<std::endl;
        return;
    }

    if(create_tables(db)<1)
        return;
    
    
    Calendar::initCalendar();

    std::ofstream of;
    of.open(string("./update.sql"));
    //导入圣人传记目录
    {
        sqlite3_exec(db,"begin;",0,0,0);
        auto saints = LiturgicYear::getPropers();
        auto iter = saints.begin();
        while (iter!=saints.end()) {

            //插入sqlite数据库
            std::ostringstream osql;
            osql<<"insert into saints(key,name,rank,color) values("
                <<iter->first<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"',"
                <<iter->second.rank<<","<<iter->second.color<<");";

            if(sqlite3_exec(db, osql.str().c_str(), NULL, 0, NULL))
            {
                std::cout<<osql.str()<<std::endl;
                return;
            }
            else
            {
                std::cout<<"insert date "<<iter->second.celebration<<std::endl;
            }
            
            //"INSERT INTO easter_saint (code, name, rank, color) SELECT 10300,'常年期第三主日(圣言主日)', 5, 4 WHERE NOT EXISTS (SELECT 1 FROM easter_saint WHERE code=10300);";

            of<<"insert into easter_saint(code, name, rank, color) select "<<iter->first<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"',"
                <<iter->second.rank<<","<<iter->second.color<<" where not exists (select 1 from easter_saint where code="<<iter->first<<");"<<std::endl;
            of<<"update easter_saint set name='"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"', rank="<<iter->second.rank<<", color="<<iter->second.color<<" where code="<<iter->first<<";"<<std::endl;

            ++iter;
        }

        sqlite3_exec(db,"commit;",0,0,0);
    }

    sqlite3_exec(db,"begin;",0,0,0);
    for(int iYear=2010;iYear<2051;++iYear)
    {
        CathAssist::Calendar::Date dtBegin(iYear,1,1);

        while (dtBegin.year()==iYear)
        {
            LiturgicDay dayInfo = Calendar::getLiturgicDay(dtBegin);

            unsigned int iLiturgicDay = dayInfo.getLiturgicId();

            std::ostringstream ostr;
            auto cells = dayInfo.getCellInfos();
            auto iterCell = cells.begin();
            while (iterCell!=cells.end())
            {
                ostr<<iterCell->toString()<<"|";

                ++iterCell;
            }

            //圣人传记的id，暂时不导出
            std::string strCellsId = "";
            {
                std::ostringstream ostrIds;
                auto ids = dayInfo.getCellsId();
                auto iii = ids.begin();
                while (iii != ids.end()) {
                    ostrIds<<*iii<<"|";

                    ++iii;
                }
                strCellsId = ostrIds.str();
            }
            //插入sqlite数据库
            std::ostringstream osql;
            osql<<"insert into calendar(date,lunar,liturgic,color,cells) values("
                <<"date('"<<ansi2utf8(dayInfo.toString())<<"'),'"<<ansi2utf8(dayInfo.toLunarString())<<"',"<<dayInfo.getLiturgicId()<<","<<dayInfo.getColor()<<",'"<<ansi2utf8(sqlite3_mprintf("%q",ostr.str().c_str()))<<"');";

            if(sqlite3_exec(db, osql.str().c_str(), NULL, 0, NULL))
            {
                std::cout<<osql.str()<<std::endl;
                return;
            }
            else
            {
                std::cout<<"insert date "<<dayInfo.toString()<<std::endl;
            }
            
            of<<"update easter_daily set cells='"<<ReplaceAll(ostr.str(), "'", "''").c_str()<<"', liturgic="<<dayInfo.getLiturgicId()<<", color="<<dayInfo.getColor()<<", lunar='"<<ansi2utf8(dayInfo.toLunarString())<<"' where date='"<<dayInfo.toString()<<"';"<<std::endl;
            //of<<"insert into easter_daily(date,lunar,liturgic,color,cells) values("
            //    <<"date('"<<ansi2utf8(dayInfo.toString())<<"'),'"<<ansi2utf8(dayInfo.toLunarString())<<"',"<<dayInfo.getLiturgicId()<<","<<dayInfo.getColor()<<",'"<<ansi2utf8(sqlite3_mprintf("%q",ostr.str().c_str()))<<"');"<<std::endl;
            
            dtBegin = dtBegin.addDays(1);
        }
    }
    sqlite3_exec(db,"commit;",0,0,0);
    of.close();

    Calendar::releaseCalendar();

    sqlite3_close(db);
}

void export_to_liturgy() {
    Calendar::initCalendar();

    std::ofstream of;
    of.open(string("./liturgy.sql"));
    {
        // 礼仪年
        {
            auto days = LiturgicYear::getNormalDays();
            auto iter = days.begin();
            while (iter != days.end()) {
                std::cout<<iter->celebration<<std::endl;

                of<<"insert into easter_mass(code, name) select "<<iter->code<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->celebration.c_str()))<<"'"
                        <<" where not exists (select 1 from easter_mass where code="<<iter->code<<");"<<std::endl;
                of<<"update easter_mass set name='"<<ansi2utf8(sqlite3_mprintf("%q",iter->celebration.c_str()))<<"'"<<" where code="<<iter->code<<";"<<std::endl;

                of<<"insert into easter_liturgy_hours(code, name) select "<<iter->code<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->celebration.c_str()))<<"'"
                        <<" where not exists (select 1 from easter_liturgy_hours where code="<<iter->code<<");"<<std::endl;
                of<<"update easter_liturgy_hours set name='"<<ansi2utf8(sqlite3_mprintf("%q",iter->celebration.c_str()))<<"'"<<" where code="<<iter->code<<";"<<std::endl;
                ++iter;
            }
        }        
        
        // 特殊节日
        {
            auto saints = LiturgicYear::getPropers();
            auto iter = saints.begin();
            while (iter!=saints.end()) {
                if(iter->second.rank >= MEMORIAL) {
                    std::cout<<iter->second.celebration<<std::endl;
//                    of<< "insert into easter_mass(code, name) values("<<iter->second.code<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"');"<<std::endl;
                    of<<"insert into easter_mass(code, name) select "<<iter->second.code<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"'"
                        <<" where not exists (select 1 from easter_mass where code="<<iter->second.code<<");"<<std::endl;
                    of<<"update easter_mass set name='"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"'"<<" where code="<<iter->second.code<<";"<<std::endl;

                    of<<"insert into easter_liturgy_hours(code, name) select "<<iter->second.code<<",'"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"'"
                        <<" where not exists (select 1 from easter_liturgy_hours where code="<<iter->second.code<<");"<<std::endl;
                    of<<"update easter_liturgy_hours set name='"<<ansi2utf8(sqlite3_mprintf("%q",iter->second.celebration.c_str()))<<"'"<<" where code="<<iter->second.code<<";"<<std::endl;
                }
                ++iter;
            }
        }
    }
    of.close();
    
    Calendar::releaseCalendar();
}

void calendar_test()
{  
    Calendar::initCalendar();
    
    CathAssist::Calendar::Date dtBegin(2022,1,1);

    while (dtBegin.year()==2022 && dtBegin.month()==1)
    {
       LiturgicDay dayInfo = Calendar::getLiturgicDay(dtBegin);

       unsigned int iLiturgicDay = dayInfo.getLiturgicId();
       std::cout<<dayInfo.toString()<<"\t";
       std::ostringstream ostr;
       auto cells = dayInfo.getCellInfos();
       auto iterCell = cells.begin();
       while (iterCell!=cells.end())
       {
           ostr<<iterCell->toString()<<"|";
            ++iterCell;
       }
       std::cout<<ostr.str()<<std::endl;
       dtBegin = dtBegin.addDays(1);
    }

    Calendar::releaseCalendar();
}

int main(int argc, char *argv[])
{
    export_month_json_test();
    export_to_sqlite();
    export_to_liturgy();
    
    calendar_test();
    return 0;
}
