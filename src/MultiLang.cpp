#include <iostream>
#include "MultiLang.h"
#include "Calendar.h"
using namespace inicpp;

std::map<int, std::map<std::string, std::string>> CathAssist::Calendar::MultiLang::mapLangs;
std::string CathAssist::Calendar::MultiLang::defaultLang = "zh_CN";

void CathAssist::Calendar::MultiLang::read(const std::string &strLangFile)
{
    mapLangs.clear();
    IniManager ini(strLangFile);
    for (auto section : ini.sectionsList())
    {
        int code = std::stoi(section);
        if (code <= 0)
        {
            continue;
        }

        std::map<std::string, std::string> mapLang;
        mapLangs[code] = ini.sectionMap(section);
    }
}

void CathAssist::Calendar::MultiLang::write(const std::string &strLangFile)
{
    CathAssist::Calendar::MultiLang::setLangCode(CathAssist::Calendar::LANG_EN);
    Calendar::initCalendar();
    auto allSaints = LiturgicYear::getPropers();
    Calendar::releaseCalendar();

    IniManager ini(strLangFile);
    for (auto langItem : mapLangs)
    {
        std::string section = std::to_string(langItem.first);
        auto found = allSaints.find(langItem.first);
        if(found == allSaints.end()) {
            continue;
        }
        if(!found->second.isEnable()) {
            continue;
        }

        for(auto l : found->second.langs) {
            auto lang = CathAssist::Calendar::getLangCodeStr(static_cast<langcode_t>(l));
            if(ini[section].isKeyExist(lang)) {
                continue;
            }
            ini[section][lang] = found->second.celebration;
        }
        for (auto item : langItem.second) {
            ini[section][item.first] = item.second;
        }
    }
}

std::string CathAssist::Calendar::MultiLang::getString(const int &code, const std::string &langCode)
{
    /*
    std::cout<<"get lang string: code="<<code<<", langCode="<<langCode<<std::endl;
    if(mapLangs.find(code) == mapLangs.end()) {
        return "";
    }
    */
    return mapLangs[code][langCode];
}
