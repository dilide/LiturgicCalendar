#ifndef _MULTILANG_H_
#define _MULTILANG_H_
#include "ini/inicpp.hpp"
#include <map>

namespace CathAssist {
    namespace Calendar {
        class MultiLang
        {
        public:
            static void read(const std::string& strLangFile);
            static void write(const std::string& strLangFile);

            static void setDefaultLang(const std::string& langCode) {
                defaultLang = langCode;
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