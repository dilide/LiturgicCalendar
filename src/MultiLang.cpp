#include <iostream>
#include "MultiLang.h"
using namespace inicpp;

std::map<int, std::map<std::string, std::string>> CathAssist::Calendar::MultiLang::mapLangs;
std::string CathAssist::Calendar::MultiLang::defaultLang = "zh_CN";

void CathAssist::Calendar::MultiLang::read(const std::string& strLangFile)
{
    mapLangs.clear();
    IniManager ini(strLangFile);
    for(auto section : ini.sectionsList()) {
        int code = std::stoi(section);
        if(code <= 0) {
            continue;
        }

        std::map<std::string, std::string> mapLang;
        mapLangs[code] = ini.sectionMap(section);
    }
}

void CathAssist::Calendar::MultiLang::write(const std::string& strLangFile)
{
    IniManager ini(strLangFile);
    for(auto langItem : mapLangs) {
        std::string section = std::to_string(langItem.first);
        for(auto item : langItem.second) {
            ini[section][item.first] = item.second;
        }
    }
}

std::string CathAssist::Calendar::MultiLang::getString(const int& code, const std::string& langCode)
{
    /*
    std::cout<<"get lang string: code="<<code<<", langCode="<<langCode<<std::endl;
    if(mapLangs.find(code) == mapLangs.end()) {
        return "";
    }
    */
    return mapLangs[code][langCode];
}
