//
// Created by Peter on 2017/7/28.
//
#include <fstream>
#include "gtest/gtest.h"
#include "sqlite/sqlite3.h"
#include "CharConverter.h"
#include "Calendar.h"
#include "MultiLang.h"
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

TEST(liturgy_calendar_test, export_month_json_test)
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

TEST(liturgy_calendar_test, export_to_sqlite)
{
    std::string strDbName = "liturgic.db";

    //删除已存在的数据库文件
    remove(strDbName.c_str());

    sqlite3* db;

    if(sqlite3_open(strDbName.c_str(), &db))
    {
        std::cout<<"open liturgic.db error"<<std::endl;
        FAIL();
    }

    if(create_tables(db)<1)
        FAIL();
    
    
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
                FAIL();
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
            osql<<"insert into calendar(date,liturgic,color,cells) values("
                <<"date('"<<ansi2utf8(dayInfo.toString())<<"'),"<<dayInfo.getLiturgicId()<<","<<dayInfo.getColor()<<",'"<<ansi2utf8(sqlite3_mprintf("%q",ostr.str().c_str()))<<"');";

            if(sqlite3_exec(db, osql.str().c_str(), NULL, 0, NULL))
            {
                std::cout<<osql.str()<<std::endl;
                FAIL();
            }
            else
            {
                std::cout<<"insert date "<<dayInfo.toString()<<std::endl;
            }
            
            of<<"update easter_daily set cells='"<<ReplaceAll(ostr.str(), "'", "''").c_str()<<"' where date='"<<dayInfo.toString()<<"';"<<std::endl;
            
            dtBegin = dtBegin.addDays(1);
        }
    }
    ASSERT_EQ(SQLITE_OK, sqlite3_exec(db, "commit;", nullptr, nullptr, nullptr))
        << sqlite3_errmsg(db);
    sqlite3_stmt* dates = nullptr;
    ASSERT_EQ(SQLITE_OK, sqlite3_prepare_v2(db,
        "SELECT count(*), count(DISTINCT date), min(date), max(date) FROM calendar",
        -1, &dates, nullptr)) << sqlite3_errmsg(db);
    ASSERT_EQ(SQLITE_ROW, sqlite3_step(dates));
    // 2000 through 2030 inclusive contains eight leap days.
    EXPECT_EQ(31 * 365 + 8, sqlite3_column_int(dates, 0));
    EXPECT_EQ(sqlite3_column_int(dates, 0), sqlite3_column_int(dates, 1));
    EXPECT_STREQ("2000-01-01", reinterpret_cast<const char*>(sqlite3_column_text(dates, 2)));
    EXPECT_STREQ("2030-12-31", reinterpret_cast<const char*>(sqlite3_column_text(dates, 3)));
    sqlite3_finalize(dates);
    of.close();

    Calendar::releaseCalendar();

    sqlite3_close(db);
}

TEST(DateTest, LeapDayFollowsGregorianCenturyRule)
{
    EXPECT_FALSE(Date::isValid(1900, 2, 29));
    EXPECT_TRUE(Date::isValid(2000, 2, 29));
    EXPECT_EQ(Date(1900, 3, 1), Date(1900, 2, 28).addDays(1));
    EXPECT_EQ(Date(2000, 2, 29), Date(2000, 3, 1).addDays(-1));
}

class CalendarSeasonTest : public ::testing::Test
{
protected:
    void SetUp() override { Calendar::initCalendar(); }
    void TearDown() override { Calendar::releaseCalendar(); }
};

TEST_F(CalendarSeasonTest, EasterStartsOnDifferentDatesInConsecutiveYears)
{
    for (const Date& easter : {Date(2024, 3, 31), Date(2025, 4, 20)})
    {
        SCOPED_TRACE(easter.toString());
        EXPECT_EQ(LENT, Calendar::getLiturgicDay(easter.addDays(-1)).getSeason());
        auto sunday = Calendar::getLiturgicDay(easter);
        EXPECT_EQ(EASTER, sunday.getSeason());
        EXPECT_EQ(1, sunday.getWeekOfSeason());
        EXPECT_EQ(WHITE, sunday.getColor());
    }
}

TEST_F(CalendarSeasonTest, PentecostIsTheLastDayOfEaster)
{
    auto pentecost = Calendar::getLiturgicDay(2024, 5, 19);
    EXPECT_EQ(EASTER, pentecost.getSeason());
    EXPECT_EQ(RED, pentecost.getColor());
    EXPECT_EQ(ORDINARY, Calendar::getLiturgicDay(2024, 5, 20).getSeason());
}

TEST_F(CalendarSeasonTest, AdventCanStartInNovember)
{
    EXPECT_EQ(ORDINARY, Calendar::getLiturgicDay(2025, 11, 29).getSeason());
    auto firstSunday = Calendar::getLiturgicDay(2025, 11, 30);
    EXPECT_EQ(ADVENT, firstSunday.getSeason());
    EXPECT_EQ(1, firstSunday.getWeekOfSeason());
    EXPECT_EQ(PURPLE, firstSunday.getColor());
}

TEST_F(CalendarSeasonTest, EasterAndAshWednesdayAcrossDatabaseExportYears)
{
    // Gregorian Easter dates from dateutil.easter (Western method).
    const Date easterSundays[] = {
        Date(2010, 4, 4), Date(2011, 4, 24), Date(2012, 4, 8), Date(2013, 3, 31),
        Date(2014, 4, 20), Date(2015, 4, 5), Date(2016, 3, 27), Date(2017, 4, 16),
        Date(2018, 4, 1), Date(2019, 4, 21), Date(2020, 4, 12), Date(2021, 4, 4),
        Date(2022, 4, 17), Date(2023, 4, 9), Date(2024, 3, 31), Date(2025, 4, 20),
        Date(2026, 4, 5), Date(2027, 3, 28), Date(2028, 4, 16), Date(2029, 4, 1),
        Date(2030, 4, 21), Date(2031, 4, 13), Date(2032, 3, 28), Date(2033, 4, 17),
        Date(2034, 4, 9), Date(2035, 3, 25), Date(2036, 4, 13), Date(2037, 4, 5),
        Date(2038, 4, 25), Date(2039, 4, 10), Date(2040, 4, 1), Date(2041, 4, 21),
        Date(2042, 4, 6), Date(2043, 3, 29), Date(2044, 4, 17), Date(2045, 4, 9),
        Date(2046, 3, 25), Date(2047, 4, 14), Date(2048, 4, 5), Date(2049, 4, 18),
        Date(2050, 4, 10),
    };
    for (const Date& easter : easterSundays)
    {
        SCOPED_TRACE(easter.toString());
        auto sunday = Calendar::getLiturgicDay(easter);
        EXPECT_EQ(EASTER, sunday.getSeason());
        EXPECT_EQ(1, sunday.getWeekOfSeason());
        EXPECT_EQ(SUN, sunday.dayOfWeek());
        EXPECT_EQ(LENT, Calendar::getLiturgicDay(easter.addDays(-1)).getSeason());

        auto ashWednesday = Calendar::getLiturgicDay(easter.addDays(-46));
        EXPECT_EQ(WED, ashWednesday.dayOfWeek());
        EXPECT_EQ(LENT, ashWednesday.getSeason());
        EXPECT_EQ(PURPLE, ashWednesday.getColor());
        const auto celebrations = ashWednesday.getCellInfos();
        ASSERT_FALSE(celebrations.empty());
        EXPECT_EQ(ASHWED, celebrations.front().rank);
        EXPECT_EQ(ORDINARY, Calendar::getLiturgicDay(easter.addDays(-47)).getSeason());
    }
}

TEST_F(CalendarSeasonTest, HolyWeekCelebrationsTakePrecedence)
{
    struct ExpectedDay {
        Date date;
        rank_t rank;
        color_t color;
    };
    const ExpectedDay days[] = {
        {Date(2024, 3, 24), HOLYWEEK, RED},  // Palm Sunday
        {Date(2024, 3, 28), TRIDUUM, WHITE}, // Holy Thursday
        {Date(2024, 3, 29), TRIDUUM, RED},   // Good Friday
    };
    for (const auto& expected : days)
    {
        SCOPED_TRACE(expected.date.toString());
        auto day = Calendar::getLiturgicDay(expected.date);
        EXPECT_EQ(LENT, day.getSeason());
        EXPECT_EQ(6, day.getWeekOfSeason());
        const auto celebrations = day.getCellInfos();
        ASSERT_FALSE(celebrations.empty());
        EXPECT_EQ(expected.rank, celebrations.front().rank);
        EXPECT_EQ(expected.color, day.getColor());
    }
}

class RegionalCalendarTest : public ::testing::Test
{
protected:
    const langcode_t originalLanguage = MultiLang::getLangCode();

    void TearDown() override
    {
        Calendar::releaseCalendar();
        MultiLang::setLangCode(originalLanguage);
    }

    void checkJanuary(langcode_t language, int year, int epiphany, int baptism)
    {
        MultiLang::setLangCode(language);
        Calendar::initCalendar();
        for (int date = 2; date <= 14; ++date)
        {
            auto day = Calendar::getLiturgicDay(year, 1, date);
            SCOPED_TRACE(day.toString());
            const auto celebrations = day.getCellInfos();
            EXPECT_EQ(date == epiphany, CellInfo::isContain(celebrations, 1));
            EXPECT_EQ(date == baptism, CellInfo::isContain(celebrations, 2));
        }
    }
};

TEST_F(RegionalCalendarTest, ItalyKeepsEpiphanyOnJanuarySixth)
{
    checkJanuary(LANG_IT_IT, 2024, 6, 7);
}

TEST_F(RegionalCalendarTest, SpainKeepsEpiphanyOnJanuarySixth)
{
    checkJanuary(LANG_ES_ES, 2024, 6, 7);
}

TEST_F(RegionalCalendarTest, LateSundayEpiphanyMovesBaptismToMonday)
{
    checkJanuary(LANG_EN, 2024, 7, 8);
}

TEST_F(RegionalCalendarTest, EarlySundayEpiphanyKeepsBaptismOnSunday)
{
    checkJanuary(LANG_EN, 2025, 5, 12);
}

TEST(DateTest, LunarHolidaysFallOnTheirKnownGregorianDates)
{
    for (const Date& newYear : {Date(2024, 2, 10), Date(2025, 1, 29)})
    {
        SCOPED_TRACE(newYear.toString());
        EXPECT_TRUE(Date::isNewYearEve(newYear.addDays(-1)));
        EXPECT_FALSE(Date::isSpringFestival(newYear.addDays(-1)));
        EXPECT_TRUE(Date::isSpringFestival(newYear));
        EXPECT_FALSE(Date::isNewYearEve(newYear));
        EXPECT_FALSE(Date::isSpringFestival(newYear.addDays(1)));
    }
    for (const Date& chuseok : {Date(2024, 9, 17), Date(2025, 10, 6)})
    {
        SCOPED_TRACE(chuseok.toString());
        EXPECT_FALSE(Date::isChuseok(chuseok.addDays(-1)));
        EXPECT_TRUE(Date::isChuseok(chuseok));
        EXPECT_FALSE(Date::isChuseok(chuseok.addDays(1)));
    }
}

TEST(DateTest, RegionalNewYearAndEveUseTheSameCalendar)
{
    const Date koreanNewYears[] = {
        {1916, 2, 4}, {1944, 1, 26}, {1954, 2, 4}, {1958, 2, 19},
        {1966, 1, 22}, {1988, 2, 18}, {1997, 2, 8}, {2027, 2, 7},
        {2028, 1, 27}, {2061, 1, 22}, {2089, 2, 11}, {2092, 2, 8},
    };
    for (const Date& koreanDate : koreanNewYears)
    {
        SCOPED_TRACE(koreanDate.toString());
        const Date chineseDate = koreanDate.addDays(-1);
        for (auto lang : {LANG_ZH_CN, LANG_ZH_TW})
        {
            EXPECT_TRUE(Date::isNewYearEve(chineseDate.addDays(-1), lang));
            EXPECT_TRUE(Date::isSpringFestival(chineseDate, lang));
            EXPECT_FALSE(Date::isNewYearEve(chineseDate, lang));
            EXPECT_FALSE(Date::isSpringFestival(koreanDate, lang));
        }
        EXPECT_TRUE(Date::isNewYearEve(chineseDate, LANG_KO_KR));
        EXPECT_FALSE(Date::isSpringFestival(chineseDate, LANG_KO_KR));
        EXPECT_TRUE(Date::isSpringFestival(koreanDate, LANG_KO_KR));
        EXPECT_FALSE(Date::isNewYearEve(koreanDate, LANG_KO_KR));
    }
    for (auto lang : {LANG_ZH_CN, LANG_ZH_TW, LANG_KO_KR})
        EXPECT_TRUE(Date::isSpringFestival(Date(2026, 2, 17), lang));
}

TEST(DateTest, ChuseokUsesTheKoreanDateOnly)
{
    const Date dates[] = {
        {1942, 9, 25}, {2040, 9, 21}, {2089, 9, 19}, {2096, 10, 1}, {2098, 9, 10},
    };
    for (const Date& chuseok : dates)
    {
        SCOPED_TRACE(chuseok.toString());
        EXPECT_TRUE(Date::isChuseok(chuseok, LANG_KO_KR));
        EXPECT_FALSE(Date::isChuseok(chuseok.addDays(-1), LANG_KO_KR));
        EXPECT_FALSE(Date::isChuseok(chuseok, LANG_ZH_CN));
        EXPECT_FALSE(Date::isChuseok(chuseok, LANG_ZH_TW));
    }
}

TEST_F(RegionalCalendarTest, DailyCelebrationsFollowTheSelectedLanguage)
{
    for (auto lang : {LANG_ZH_CN, LANG_ZH_TW, LANG_KO_KR, LANG_EN})
    {
        SCOPED_TRACE(getLangCodeStr(lang));
        MultiLang::setLangCode(lang);
        Calendar::initCalendar();
        const int newYear = lang == LANG_KO_KR ? 7 : 6;
        for (int day = 5; day <= 7; ++day)
        {
            SCOPED_TRACE(day);
            const auto cells = Calendar::getLiturgicDay(2027, 2, day).getCellInfos();
            EXPECT_EQ(lang != LANG_EN && day == newYear - 1, CellInfo::isContain(cells, 11));
            EXPECT_EQ(lang != LANG_EN && day == newYear, CellInfo::isContain(cells, 12));
        }
        const auto cells = Calendar::getLiturgicDay(2040, 9, 21).getCellInfos();
        EXPECT_EQ(lang == LANG_KO_KR, CellInfo::isContain(cells, 41));
        Calendar::releaseCalendar();
    }
}

TEST(DateTest, MidAutumnUsesItsOwnRegionalDates)
{
    // In 2089 both festivals differ. In 2040 only Mid-Autumn differs.
    for (const Date& chineseDate : {Date(2089, 9, 18), Date(2040, 9, 20)})
    {
        SCOPED_TRACE(chineseDate.toString());
        const Date koreanDate = chineseDate.addDays(1);
        for (auto lang : {LANG_ZH_CN, LANG_ZH_TW})
        {
            EXPECT_TRUE(Date::isMidAutumnFestival(chineseDate, lang));
            EXPECT_FALSE(Date::isMidAutumnFestival(koreanDate, lang));
            EXPECT_FALSE(Date::isChuseok(chineseDate, lang));
        }
        EXPECT_FALSE(Date::isMidAutumnFestival(chineseDate, LANG_KO_KR));
        EXPECT_TRUE(Date::isMidAutumnFestival(koreanDate, LANG_KO_KR));
    }

    // In 2027 only New Year differs. All three locales share Mid-Autumn.
    for (auto lang : {LANG_ZH_CN, LANG_ZH_TW, LANG_KO_KR})
        EXPECT_TRUE(Date::isMidAutumnFestival(Date(2027, 9, 15), lang));
}
