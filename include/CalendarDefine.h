#ifndef __CA_CALENDAR_DEFINE_H__
#define __CA_CALENDAR_DEFINE_H__
#include <string>
#include <sstream>

namespace CathAssist
{
	namespace Calendar
	{
        typedef enum LanguageCodes {
            LANG_EN = 1,
            LANG_ZH_CN,
            LANG_ZH_TW,
            LANG_ES_ES,
            LANG_IT_IT,
            LANG_PT_BR
        } langcode_t;

        static std::string getLangCodeStr(langcode_t lc) {
            switch (lc) {
                case LANG_EN:
                    return "en";
                case LANG_ZH_CN:
                    return "zh_CN";
                case LANG_ZH_TW:
                    return "zh_TW";
                case LANG_ES_ES:
                    return "es_ES";
                case LANG_IT_IT:
                    return "it_IT";
                case LANG_PT_BR:
                    return "pt_BR";
                default:
                    return "zh_CN";
            }
        }

        static langcode_t getLangCodeFromStr(const std::string& strLang) {
            if (strLang == "en") {
                return LANG_EN;
            } else if (strLang == "zh_CN") {
                return LANG_ZH_CN;
            } else if (strLang == "zh_TW") {
                return LANG_ZH_TW;
            } else if (strLang == "es_ES") {
                return LANG_ES_ES;
            } else if (strLang == "it_IT") {
                return LANG_IT_IT;
            } else if (strLang == "pt_BR") {
                return LANG_PT_BR;
            } else {
                return LANG_ZH_CN;
            }
        }

		/*
		 * Days of the Week
		 */
		typedef enum Days
		{
		   SUN = 0, MON, TUE, WED, THU, FRI, SAT
		} day_t;

		static std::string getDayStr(day_t d, const LanguageCodes& lang = LANG_ZH_CN)
		{
            if(lang == LANG_ZH_CN || lang == LANG_ZH_TW) {
                switch(d)
                {
                case SUN:
                    return "星期日";
                    break;
                case MON:
                    return "星期一";
                    break;
                case TUE:
                    return "星期二";
                    break;
                case WED:
                    return "星期三";
                    break;
                case THU:
                    return "星期四";
                    break;
                case FRI:
                    return "星期五";
                    break;
                case SAT:
                    return "星期六";
                    break;
                }
            } else if(lang == LANG_EN) {
                switch(d)
                {
                case SUN:
                    return "Sunday";
                    break;
                case MON:
                    return "Monday";
                    break;
                case TUE:
                    return "Tuesday";
                    break;
                case WED:
                    return "Wednesday";
                    break;
                case THU:
                    return "Thursday";
                    break;
                case FRI:
                    return "Friday";
                    break;
                case SAT:
                    return "Saturday";
                    break;
                }
            } else if (lang == LANG_ES_ES) {
                switch(d)
                {
                case SUN:
                    return "Domingo";
                    break;
                case MON:
                    return "Lunes";
                    break;
                case TUE:
                    return "Martes";
                    break;
                case WED:
                    return "Miércoles";
                    break;
                case THU:
                    return "Jueves";
                    break;
                case FRI:
                    return "Viernes";
                    break;
                case SAT:
                    return "Sábado";
                    break;
                }
            } else if (lang == LANG_IT_IT) {
                switch(d)
                {
                case SUN:
                    return "Domenica";
                    break;
                case MON:
                    return "Lunedì";
                    break;
                case TUE:
                    return "Martedì";
                    break;
                case WED:
                    return "Mercoledì";
                    break;
                case THU:
                    return "Giovedì";
                    break;
                case FRI:
                    return "Venerdì";
                    break;
                case SAT:
                    return "Sabato";
                    break;
                }
            } else if (lang == LANG_PT_BR) {
                switch(d)
                {
                case SUN:
                    return "Domingo";
                    break;
                case MON:
                    return "Segunda-feira";
                    break;
                case TUE:
                    return "Terça-feira";
                    break;
                case WED:
                    return "Quarta-feira";
                    break;
                case THU:
                    return "Quinta-feira";
                    break;
                case FRI:
                    return "Sexta-feira";
                    break;
                case SAT:
                    return "Sábado";
                    break;
                }
            }
			return "Not define";
		}

		/*
		 * Months of the Year
		 */
		typedef enum Months
        {
		   PREVDEC,  JANUARY,   FEBRUARY, MARCH,
		   APRIL,    MAY,       JUNE,     JULY,
		   AUGUST,   SEPTEMBER, OCTOBER, NOVEMBER,
		   DECEMBER, NEXTJAN
		} month_t;
		/*
		 * Liturgical Colors
		 */
		typedef enum Colors
        {
		   NOCOLOR, GREEN, WHITE, RED, PURPLE, ROSE, BLACK
		} color_t;
        
        static std::string getColorStr(color_t c, const LanguageCodes& lang = LANG_ZH_CN)
        {
            if(lang == LANG_ZH_CN) {
                switch(c)
                {
                    case NOCOLOR:
                        return "无";
                        break;
                    case GREEN:
                        return "绿";
                        break;
                    case WHITE:
                        return "白";
                        break;
                    case RED:
                        return "红";
                        break;
                    case PURPLE:
                        return "紫";
                        break;
                    case ROSE:
                        return "玫";
                        break;
                    case BLACK:
                        return "黑";
                        break;
                }
            } else if(lang == LANG_EN) {
                switch(c)
                {
                    case NOCOLOR:
                        return "Nocolor";
                        break;
                    case GREEN:
                        return "Green";
                        break;
                    case WHITE:
                        return "White";
                        break;
                    case RED:
                        return "Red";
                        break;
                    case PURPLE:
                        return "Purple";
                        break;
                    case ROSE:
                        return "Rose";
                        break;
                    case BLACK:
                        return "Black";
                        break;
                }
            } else if(lang == LANG_ZH_TW) {
                switch(c)
                {
                    case NOCOLOR:
                        return "無";
                        break;
                    case GREEN:
                        return "綠";
                        break;
                    case WHITE:
                        return "白";
                        break;
                    case RED:
                        return "紅";
                        break;
                    case PURPLE:
                        return "紫";
                        break;
                    case ROSE:
                        return "玫";
                        break;
                    case BLACK:
                        return "黑";
                        break;
                }
            } else if (lang == LANG_ES_ES) {
                switch(c)
                {
                    case NOCOLOR:
                        return "Sin color";
                        break;
                    case GREEN:
                        return "Verde";
                        break;
                    case WHITE:
                        return "Blanco";
                        break;
                    case RED:
                        return "Rojo";
                        break;
                    case PURPLE:
                        return "Morado";
                        break;
                    case ROSE:
                        return "Rosa";
                        break;
                    case BLACK:
                        return "Negro";
                        break;
                }
            } else if(lang == LANG_IT_IT) {
                switch(c)
                {
                    case NOCOLOR:
                        return "Senza colore";
                        break;
                    case GREEN:
                        return "Verde";
                        break;
                    case WHITE:
                        return "Bianco";
                        break;
                    case RED:
                        return "Rosso";
                        break;
                    case PURPLE:
                        return "Viola";
                        break;
                    case ROSE:
                        return "Rosa";
                        break;
                    case BLACK:
                        return "Nero";
                        break;
                }
            } else if (lang == LANG_PT_BR) {
                switch(c)
                {
                    case NOCOLOR:
                        return "Sem cor";
                        break;
                    case GREEN:
                        return "Verde";
                        break;
                    case WHITE:
                        return "Branco";
                        break;
                    case RED:
                        return "Vermelho";
                        break;
                    case PURPLE:
                        return "Roxo";
                        break;
                    case ROSE:
                        return "Rosa";
                        break;
                    case BLACK:
                        return "Preto";
                        break;
                }
            }
            return "Not define";
        }
        
        static std::string getColorValue(color_t c)
        {
            switch(c)
            {
                case NOCOLOR:
                    return "#FFFFFF";
                    break;
                case GREEN:
                    return "#00FF00";
                    break;
                case WHITE:
                    return "#DDDDDD";
                    break;
                case RED:
                    return "#FF0000";
                    break;
                case PURPLE:
                    return "#8B00FF";
                    break;
                case ROSE:
                    return "#FF0DA6";
                    break;
                case BLACK:
                    return "#000000";
                    break;
            }
            return "Not define";
        }
		/*
		 * Liturgical Ranks
		 */
		typedef enum Ranks
        {
		   ErrorRank = -1, //错误的优先级
		   WEEKDAY,		/* Plain, old weekdays			*/
		   COMMEMORATION,	/* Commemoration = Memorial in Lent 	*/
		   OPTIONAL,		/* Optional Memorials			*/
		   MEMORIAL,		/* Memorials				*/
		   FEAST,		/* Feasts (not of the Lord)		*/
		   SUNDAY,		/* Sundays 				*/
		   LORD,		/* Feasts of the Lord 			*/
		   ASHWED,		/* Ash Wednesday			*/
		   HOLYWEEK,		/* Mon, Tue, and Wed of Holy Week	*/
		   TRIDUUM,		/* The Triduum				*/
		   SOLEMNITY 		/* Solemnities 				*/
		} rank_t;
        
        static std::string getRankStr(rank_t r)
        {
            switch (r) {
                case ErrorRank:
                    return "Error";
                    break;
                case WEEKDAY:
                    return "Weekday";
                    break;
                case COMMEMORATION:
                    return "Commemoration";
                    break;
                case OPTIONAL:
                    return "Optional";
                    break;
                case MEMORIAL:
                    return "Memorial";
                    break;
                case FEAST:
                    return "Feast";
                    break;
                case SUNDAY:
                    return "Sunday";
                    break;
                case LORD:
                    return "Lord";
                    break;
                case ASHWED:
                    return "Ashwed";
                    break;
                case HOLYWEEK:
                    return "Holyweek";
                    break;
                case TRIDUUM:
                    return "Triduum";
                    break;
                case SOLEMNITY:
                    return "Solemnity";
                    break;
            }
            return "Not define";
        }
        
		/*
		 * Liturgical Seasons
		 */
		typedef enum Seasons
        {
		   ORDINARY = 1,
		   ADVENT,
		   CHRISTMAS,
		   LENT,
		   EASTER,
		   PASCHAL	/* Ash Wed., Holy Week & Easter Octave 	*/
		} season_t;
        
        static std::string getSeasonStr(season_t s, const LanguageCodes& lang = LANG_ZH_CN)
        {
            if(lang == LANG_ZH_CN) {
                switch(s)
                {
                    case ORDINARY:
                        return "常年期";
                        break;
                    case ADVENT:
                        return "将临期";
                        break;
                    case CHRISTMAS:
                        return "圣诞期";
                        break;
                    case LENT:
                        return "四旬期";
                        break;
                    case EASTER:
                        return "复活期";
                        break;
                    case PASCHAL:
                        return "逾越节";	//Ash Wed., Holy Week & Easter Octave
                        break;
                }
            } else if(lang == LANG_EN) {
                switch(s)
                {
                    case ORDINARY:
                        return "Ordinary Time";
                        break;
                    case ADVENT:
                        return "Advent";
                        break;
                    case CHRISTMAS:
                        return "Christmas";
                        break;
                    case LENT:
                        return "Lent";
                        break;
                    case EASTER:
                        return "Easter";
                        break;
                    case PASCHAL:
                        return "Paschal";	//Ash Wed., Holy Week & Easter Octave
                        break;
                }
            } else if(lang == LANG_ZH_TW) {
                switch(s)
                {
                    case ORDINARY:
                        return "常年期";
                        break;
                    case ADVENT:
                        return "將臨期";
                        break;
                    case CHRISTMAS:
                        return "聖誕期";
                        break;
                    case LENT:
                        return "四旬期";
                        break;
                    case EASTER:
                        return "復活期";
                        break;
                    case PASCHAL:
                        return "逾越節";	//Ash Wed., Holy Week & Easter Octave
                        break;
                }
            } else if (lang == LANG_ES_ES) {
                switch(s)
                {
                    case ORDINARY:
                        return "Tiempo Ordinario";
                        break;
                    case ADVENT:
                        return "Adviento";
                        break;
                    case CHRISTMAS:
                        return "Navidad";
                        break;
                    case LENT:
                        return "Cuaresma";
                        break;
                    case EASTER:
                        return "Pascua";
                        break;
                    case PASCHAL:
                        return "Pascual";	//Ash Wed., Holy Week & Easter Octave
                        break;
                }
            } else if(lang == LANG_IT_IT) {
                switch(s)
                {
                    case ORDINARY:
                        return "Tempo Ordinario";
                        break;
                    case ADVENT:
                        return "Avvento";
                        break;
                    case CHRISTMAS:
                        return "Natale";
                        break;
                    case LENT:
                        return "Quaresima";
                        break;
                    case EASTER:
                        return "Pasqua";
                        break;
                    case PASCHAL:
                        return "Pasquale";	//Ash Wed., Holy Week & Easter Octave
                        break;
                }
            } else if (lang == LANG_PT_BR) {
                switch(s)
                {
                    case ORDINARY:
                        return "Tempo Comum";
                        break;
                    case ADVENT:
                        return "Advento";
                        break;
                    case CHRISTMAS:
                        return "Natal";
                        break;
                    case LENT:
                        return "Quaresma";
                        break;
                    case EASTER:
                        return "Páscoa";
                        break;
                    case PASCHAL:
                        return "Pascal";	//Ash Wed., Holy Week & Easter Octave
                        break;
                }
            }
            return "Not define";
        }

        static std::string intToRoman(int num) {
            // 千位 (0, 1000, 2000, 3000)
            std::string thousands[] = {"", "M", "MM", "MMM"};
            // 百位 (0, 100, 200, ... 900)
            std::string hundreds[]  = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
            // 十位 (0, 10, 20, ... 90)
            std::string tens[]      = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
            // 个位 (0, 1, 2, ... 9)
            std::string ones[]      = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

            // 直接通过取模和除法计算每一位的索引并拼接
            return thousands[num / 1000] + 
                hundreds[(num % 1000) / 100] + 
                tens[(num % 100) / 10] + 
                ones[num % 10];
        }

        static std::string getOrdinalStr(const int& num, const langcode_t& lang = LANG_ZH_CN) {
            if(lang == LANG_EN) {
                if(num == 1) {
                    return "First";
                } else if(num == 2) {
                    return "Second";
                } else if(num == 3) {
                    return "Third";
                } else {
                    return std::to_string(num) + "th";
                }
            } else if(lang == LANG_ES_ES) {
                if(num == 1) {
                    return "Primero";
                } else if(num == 2) {
                    return "Segundo";
                } else if(num == 3) {
                    return "Tercero";
                } else {
                    return std::to_string(num) + "º";
                }
            } else if(lang == LANG_IT_IT) {
                return intToRoman(num);
            } else if(lang == LANG_PT_BR) {
                if(num == 1) {
                    return "Primeiro";
                } else if(num == 2) {
                    return "Segundo";
                } else if(num == 3) {
                    return "Terceiro";
                } else {
                    return std::to_string(num) + "º";
                }
            } else if(lang == LANG_ZH_CN || lang == LANG_ZH_TW) {
                static std::string numStr[] = 
                {
                    "零",
                    "一",
                    "二",
                    "三",
                    "四",
                    "五",
                    "六",
                    "七",
                    "八",
                    "九",
                    "十",
                };
                
                if(num<0||num>39)
                    return "Not define";
                if(num<=10)
                {
                    return numStr[num];
                }
                else if(num<20)
                {
                    return "十"+numStr[num%10];
                }
                else if(num<30)
                {
                    if(num==20)
                        return "二十";
                    else
                        return "二十"+numStr[num%10];
                }
                else if(num<40)
                {
                    if(num==30)
                        return "三十";
                    else
                        return "三十"+numStr[num%10];
                }
            }

            return "Not define";
        }

        static std::string getSpecialMonth(const int& iMonth)
        {
            switch (iMonth) {
                case 3:
                    return "圣若瑟月";
                case 5:
                    return "圣母月";
                case 6:
                    return "耶稣圣心月";
                case 10:
                    return "玫瑰月";
                case 11:
                    return "炼灵月";
                default:
                    break;
            }
            
            return "";
        }

        // 意大利语介词阴阳的问题
        static std::string getItPrepStr(const season_t& season) {
            if(season == ORDINARY) {
                return "del";
            } else {
                return "di";
            }
        }
	}
}

#endif	//__CA_CALENDAR_DEFINE_H__
