#ifndef _MULTILANG_H_
#define _MULTILANG_H_
#include "ini/inicpp.hpp"
#include <map>

namespace CathAssist {
    namespace Calendar {
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

        class MultiLang
        {
        public:
            static void read(const std::string& strLangFile);
            static void write(const std::string& strLangFile);

            static langcode_t getLangCode() {
                return getLangCodeFromStr(defaultLang);
            }
            static void setLangCode(const langcode_t& langCode) {
                defaultLang = CathAssist::Calendar::getLangCodeStr(langCode);
            }
            
            static std::string getString(const int& code, const std::string& langCode);
            static std::string getString(const int& code) {
                return getString(code, defaultLang);
            }

            static void setString(const int& code, const std::string& langCode, const std::string& strValue) {
                mapLangs[code][langCode] = strValue;
            }
            
        private:
            static std::map<int, std::map<std::string, std::string>> mapLangs;
            static std::string defaultLang;
        };
    }
}

#endif