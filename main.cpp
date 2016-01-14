#define _CRT_SECURE_NO_DEPRECATE
#include "Calendar.h"
#include "sqlite/sqlite3.h"
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>

#ifdef __APPLE__
using namespace std;
#define ansi2utf8(X) (X)
#else
#include <windows.h>
using namespace std;
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
    
    return 1;
}


int main(int argc, char* argv[])
{
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
    std::string strSplit = "\t";
    
    std::ofstream of("LiturgicDay.txt",std::fstream::out|std::fstream::trunc);
    
    //导出特殊节日
    {
        auto propers = LiturgicYear::getPropers();
        auto iter = propers.begin();
        while (iter!=propers.end())
        {
            of<<iter->first<<strSplit<<iter->second.celebration<<std::endl;
            
            ++iter;
        }
        
        of<<std::endl<<std::endl;
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
            //插入sqlite数据库
            std::ostringstream osql;
            osql<<"insert into calendar(date,lunar,liturgic,color,cells) values("
            <<"date('"<<ansi2utf8(dayInfo.toString())<<"'),'"<<ansi2utf8(dayInfo.toLunarString())<<"',"<<dayInfo.getLiturgicId()<<","
            <<dayInfo.getColor()<<",'"<<ansi2utf8(ostr.str())<<"');";
            
            if(sqlite3_exec(db, osql.str().c_str(), NULL, 0, NULL))
            {
                std::cout<<osql.str()<<std::endl;
                return -1;
            }
            else
            {
                std::cout<<"inser date "<<dayInfo.toString()<<std::endl;
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
