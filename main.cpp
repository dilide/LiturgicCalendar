#define _CRT_SECURE_NO_DEPRECATE
#include "Calendar.h"
#include "sqlite/sqlite3.h"
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <iomanip>
#include <fstream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#ifdef __APPLE__
using namespace std;
using namespace rapidjson;
#define ansi2utf8(X) (X)
#else
#include <windows.h>
using namespace std;
using namespace rapidjson;
//UTF-8转Unicode
std::wstring Utf82Unicode(const std::string& utf8string)
{
    int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    
    std::vector<wchar_t> resultstring(widesize);
    
    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
    
    if (convresult != widesize)
    {
        throw std::exception("La falla!");
    }
    
    return std::wstring(&resultstring[0]);
}

//unicode 转为 ascii

string WideByte2Acsi(wstring& wstrcode)
{
    int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (asciisize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<char> resultstring(asciisize);
    int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
    
    if (convresult != asciisize)
    {
        throw std::exception("La falla!");
    }
    
    return std::string(&resultstring[0]);
}

//utf-8 转 ascii

string UTF_82ASCII(string& strUtf8Code)
{
    string strRet("");
    
    
    //先把 utf8 转为 unicode
    wstring wstr = Utf82Unicode(strUtf8Code);
    
    //最后把 unicode 转为 ascii
    strRet = WideByte2Acsi(wstr);
    
    
    return strRet;
}

///////////////////////////////////////////////////////////////////////

//ascii 转 Unicode

wstring Acsi2WideByte(string& strascii)
{
    int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<wchar_t> resultstring(widesize);
    int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
    
    if (convresult != widesize)
    {
        throw std::exception("La falla!");
    }
    
    return std::wstring(&resultstring[0]);
}

//Unicode 转 Utf8

std::string Unicode2Utf8(const std::wstring& widestring)
{
    int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8size == 0)
    {
        throw std::exception("Error in conversion.");
    }
    
    std::vector<char> resultstring(utf8size);
    
    int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
    
    if (convresult != utf8size)
    {
        throw std::exception("La falla!");
    }
    
    return std::string(&resultstring[0]);
}

//ascii 转 Utf8

string ASCII2UTF_8(string& strAsciiCode)
{
    string strRet("");
    
    
    //先把 ascii 转为 unicode
    wstring wstr = Acsi2WideByte(strAsciiCode);
    
    //最后把 unicode 转为 utf8
    
    strRet = Unicode2Utf8(wstr);
    
    
    return strRet;
}

std::string ansi2utf8(std::string& s)
{
    return ASCII2UTF_8(s);
}
#endif

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

//导出给数据库使用，返回值：0 成功；非0 失败
int exportSqlite() {
    std::string strDbName = "liturgic.db";
    
    //删除已存在的数据库文件
    remove(strDbName.c_str());
    
    sqlite3* db;
    
    if(sqlite3_open(strDbName.c_str(), &db))
    {
        std::cout<<"open liturgic.db error"<<std::endl;
        return -1;
    }
    
    if(create_tables(db)<1)
        return -1;
    
    
    Calendar::initCalendar();
    
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
                return -1;
            }
            else
            {
                std::cout<<"insert date "<<iter->second.celebration<<std::endl;
            }
            
            ++iter;
        }
        
        sqlite3_exec(db,"commit;",0,0,0);
    }
    
    sqlite3_exec(db,"begin;",0,0,0);
    for(int iYear=2000;iYear<2031;++iYear)
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
                return -1;
            }
            else
            {
                std::cout<<"insert date "<<dayInfo.toString()<<std::endl;
            }
            
            /*of<<dayInfo.toString()<<strSplit
             <<iLiturgicDay<<strSplit
             <<dayInfo.toLunarString()<<strSplit
             <<dayInfo.toWeekdayString()<<strSplit
             <<ostr.str()<<strSplit
             <<std::endl;
             */
            dtBegin = dtBegin.addDays(1);
        }
    }
    sqlite3_exec(db,"commit;",0,0,0);
    
    Calendar::releaseCalendar();
    
    sqlite3_close(db);
    return 0;
}

//导出为按月份的 JSON 文件，返回值：0 成功；非0 失败
int exportMonthJson() {
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
    for(int iYear=2000;iYear<2042;++iYear)
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
                    liturgic.AddMember("name", Value(iterCell->toString().c_str(), allocator), allocator);
                    liturgic.AddMember("rank", Value(iterCell->rank), allocator);
                    
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
    
    return 0;
}

int main(int argc, char* argv[])
{
//    exportSqlite();
    exportMonthJson();
    return 0;
}
