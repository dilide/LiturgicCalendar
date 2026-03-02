/*
============================================================================
文件名称	:	LiturgicYear.cpp
公司		:	CathAssist
作者		:	李亚科
创建时间	:	2014-06-12 12:27
修改时间	:	2014-06-12 12:30
说明		:	用于计算礼仪年
============================================================================
*/

#include "LiturgicYear.h"
#include "MultiLang.h"
#include <sstream>

using namespace CathAssist::Calendar;

std::map<int, CellInfo> CathAssist::Calendar::LiturgicYear::mapPropers;

void CathAssist::Calendar::LiturgicYear::initPropers()
{
    std::list<int> disableLang = {};
    std::list<int> allLang = getAllLangCodes();
    std::list<int> chineseLang = {LANG_ZH_CN, LANG_ZH_TW};
    std::list<int> allLangWithoutChinese = allLang;
    for(auto iter = chineseLang.begin(); iter != chineseLang.end(); ++iter) {
        allLangWithoutChinese.remove(*iter);
    }

    if (mapPropers.size() > 0)
    {
        return;
    }
    langcode_t lang = CathAssist::Calendar::MultiLang::getLangCode();
    /*
    // 初始化常用节日（日期固定）
    // 规则：采用十进制（共7位）,最高位始终为1
    // 前面两位为：月份
    // 中间两位为：月内日期
    // 最后两位为：编号，从1开始（适用于某个日期中可能有多个纪念日的情况）
    */
    {
        /*******************1月**********************/
        // 1日
        mapPropers.insert(std::make_pair(1010101, CellInfo(SOLEMNITY, WHITE, "天主之母节(Solemnity Mary, Mother of God)")));
        // 2日
        mapPropers.insert(std::make_pair(1010201, CellInfo(MEMORIAL, WHITE, "圣巴西略及圣国瑞•纳祥(St. Basil the Great & Gregory Nazianxen)")));
        // 3日
        mapPropers.insert(std::make_pair(1010301, CellInfo(MEMORIAL, WHITE, "耶稣圣名")));
        mapPropers.insert(std::make_pair(1010302, CellInfo(OPTIONAL, NOCOLOR, "真福查瓦拉(Bd. Kuriakose Elias Chavara)", disableLang)));
        mapPropers.insert(std::make_pair(1010303, CellInfo(OPTIONAL, NOCOLOR, "圣女日南斐法(St. Genevieve)")));
        // 4日
        mapPropers.insert(std::make_pair(1010401, CellInfo(OPTIONAL, NOCOLOR, "圣安•贝兰•丝彤(St. Eizabeth Ann Bayley Seton)", disableLang)));
        mapPropers.insert(std::make_pair(1010402, CellInfo(OPTIONAL, NOCOLOR, "圣女法拉意弟(St. Pharaildis)")));
        // 5日
        mapPropers.insert(std::make_pair(1010501, CellInfo(OPTIONAL, NOCOLOR, "圣若望纽曼(St. John Nepornucene Neumann)")));
        mapPropers.insert(std::make_pair(1010502, CellInfo(OPTIONAL, NOCOLOR, "圣西默盎“石柱人”(St. Simeon the Stylite)")));
        // 6日
        mapPropers.insert(std::make_pair(1010602, CellInfo(OPTIONAL, NOCOLOR, "真福辣法厄尔•玛利亚(Bd. Raphaela Mary)")));
        // 7日
        mapPropers.insert(std::make_pair(1010701, CellInfo(OPTIONAL, NOCOLOR, "圣赖孟多(St. Raymond of Penyafort)")));
        // 8日
        mapPropers.insert(std::make_pair(1010801, CellInfo(OPTIONAL, NOCOLOR, "圣塞味利•诺利根(St. Severin of Noricun)",disableLang)));
        mapPropers.insert(std::make_pair(1010802, CellInfo(OPTIONAL, NOCOLOR, "圣亚玻理纳利(St. Apollinaris Claudius)")));
        // 9日
        mapPropers.insert(std::make_pair(1010901, CellInfo(OPTIONAL, NOCOLOR, "圣哈德良(St. Adrian)")));
        // 10日
        mapPropers.insert(std::make_pair(1011001, CellInfo(OPTIONAL, NOCOLOR, "圣亚加杜(St. Agatho)")));
        mapPropers.insert(std::make_pair(1011002, CellInfo(OPTIONAL, NOCOLOR, "真福额我略十世(Bd. Gregory X)")));
        // 11日
        mapPropers.insert(std::make_pair(1011101, CellInfo(OPTIONAL, NOCOLOR, "圣戴沃多塞(St. Theodosius the Cenobiarch)")));
        // 12日
        mapPropers.insert(std::make_pair(1011201, CellInfo(OPTIONAL, NOCOLOR, "圣本笃•皮斯哥(St. Benedict Biscop)")));
        // 13日
        mapPropers.insert(std::make_pair(1011301, CellInfo(OPTIONAL, NOCOLOR, "圣依拉略(St. Hilary)")));
        // 14日
        mapPropers.insert(std::make_pair(1011401, CellInfo(OPTIONAL, NOCOLOR, "真福和德理(Bd. Odoric of Pordenone)")));
        // 15日
        mapPropers.insert(std::make_pair(1011501, CellInfo(OPTIONAL, NOCOLOR, "圣保禄首位独修(St. Paul the Hermit)")));
        mapPropers.insert(std::make_pair(1011502, CellInfo(OPTIONAL, NOCOLOR, "圣毛禄院长(St. Maurus)", disableLang)));
        mapPropers.insert(std::make_pair(1011503, CellInfo(OPTIONAL, NOCOLOR, "圣刘方济(St. Franciscus de Capillas)", chineseLang)));
        // 16日
        mapPropers.insert(std::make_pair(1011601, CellInfo(OPTIONAL, NOCOLOR, "圣马策禄一世(St. Marcellus)")));
        // 17日
        mapPropers.insert(std::make_pair(1011701, CellInfo(MEMORIAL, WHITE, "圣安当院长(St. Antony the Great)")));

        // 18日
        mapPropers.insert(std::make_pair(1011801, CellInfo(OPTIONAL, NOCOLOR, "为基督徒合一祈祷周（18 - 25日）")));
        mapPropers.insert(std::make_pair(1011802, CellInfo(FEAST, WHITE, "圣伯多禄定圣座于罗马(St. Peter's Chair at Rome)")));
        mapPropers.insert(std::make_pair(1011803, CellInfo(OPTIONAL, NOCOLOR, "圣女普黎斯加(St. Prisca)", disableLang)));
        // 19日
        mapPropers.insert(std::make_pair(1011901, CellInfo(OPTIONAL, NOCOLOR, "圣加努多(St. Canute Denrnark)", disableLang)));
        mapPropers.insert(std::make_pair(1011902, CellInfo(OPTIONAL, NOCOLOR, "马略、玛尔大、奥地法和亚巴古(Ss. Marius, Maltha, Audifax & Abachum)")));
        mapPropers.insert(std::make_pair(1011903, CellInfo(OPTIONAL, NOCOLOR, "圣女玛加利大(St. Margaret Bourgeoys)")));
        // 20日
        mapPropers.insert(std::make_pair(1012001, CellInfo(OPTIONAL, NOCOLOR, "圣法比盎(St. Fabian)")));
        mapPropers.insert(std::make_pair(1012002, CellInfo(OPTIONAL, NOCOLOR, "圣巴斯弟盎(St. Sebasian)")));
        // 21日
        mapPropers.insert(std::make_pair(1012101, CellInfo(MEMORIAL, RED, "圣女依搦斯(St. Agnes)")));
        // 22日
        mapPropers.insert(std::make_pair(1012201, CellInfo(OPTIONAL, NOCOLOR, "圣味增爵(St. Vincent of Saragossa)")));
        mapPropers.insert(std::make_pair(1012202, CellInfo(OPTIONAL, NOCOLOR, "圣亚纳大削(St. Anastasius the Persian)")));
        mapPropers.insert(std::make_pair(1012203, CellInfo(OPTIONAL, NOCOLOR, "圣味增爵•柏乐天(St. Vincent Polloti)", disableLang)));
        // 23日
        mapPropers.insert(std::make_pair(1012301, CellInfo(OPTIONAL, NOCOLOR, "圣爱美兰霞(St. Emerentiana)", allLangWithoutChinese)));
        mapPropers.insert(std::make_pair(1012302, CellInfo(OPTIONAL, NOCOLOR, "圣白小满", chineseLang)));
        // 24日
        mapPropers.insert(std::make_pair(1012401, CellInfo(MEMORIAL, WHITE, "圣方济各•撒肋爵(St. Francis de Sales)")));
        mapPropers.insert(std::make_pair(1012501, CellInfo(FEAST, WHITE, "圣保禄宗徒归化(The Conversion of St. Paul)")));
        mapPropers.insert(std::make_pair(1012601, CellInfo(MEMORIAL, WHITE, "圣弟茂德及圣弟铎(St. Timothy & St. Titus)")));
        // 27日
        mapPropers.insert(std::make_pair(1012701, CellInfo(OPTIONAL, NOCOLOR, "圣女安琪拉(St. Angela Merici)")));
        mapPropers.insert(std::make_pair(1012702, CellInfo(OPTIONAL, NOCOLOR, "圣赵荣", chineseLang)));
        mapPropers.insert(std::make_pair(1012801, CellInfo(MEMORIAL, WHITE, "圣多玛斯•阿奎那(St. Thomas Aquinas)")));
        mapPropers.insert(std::make_pair(1012901, CellInfo(OPTIONAL, NOCOLOR, "圣亚波罗尼(St. Apoelonius the Apologist)", disableLang)));
        mapPropers.insert(std::make_pair(1012902, CellInfo(MEMORIAL, NOCOLOR, "圣福若瑟(St. Joseph Freinademetz)")));
        mapPropers.insert(std::make_pair(1012903, CellInfo(OPTIONAL, NOCOLOR, "圣王炳", chineseLang)));
        mapPropers.insert(std::make_pair(1013001, CellInfo(OPTIONAL, NOCOLOR, "圣女玛蒂娜(St. Martina)", disableLang)));
        mapPropers.insert(std::make_pair(1013002, CellInfo(OPTIONAL, NOCOLOR, "圣妇巴蒂弟(St. Bathildis)")));
        mapPropers.insert(std::make_pair(1013003, CellInfo(MEMORIAL, NOCOLOR, "真福雷永明(Bd. Gabriele Allegra)")));
        mapPropers.insert(std::make_pair(1013101, CellInfo(MEMORIAL, WHITE, "圣鲍思高(St. John Bosco)")));
        mapPropers.insert(std::make_pair(1013102, CellInfo(OPTIONAL, NOCOLOR, "圣方济各•沙勿略•白英奇(St. Francis Xavier Bianchi)", disableLang)));

        /**********************2月*********************/
        // 1日
        mapPropers.insert(std::make_pair(1020101, CellInfo(OPTIONAL, NOCOLOR, "圣亨利•莫斯(St. Herry Morse)", disableLang)));
        mapPropers.insert(std::make_pair(1020201, CellInfo(LORD, WHITE, "献耶稣于圣殿(Presentation of the Lord)")));
        mapPropers.insert(std::make_pair(1020301, CellInfo(OPTIONAL, NOCOLOR, "圣伯拉削(St. Blaise)")));
        mapPropers.insert(std::make_pair(1020302, CellInfo(OPTIONAL, NOCOLOR, "圣安加略(St. Ansgarius)")));
        // 4日
        mapPropers.insert(std::make_pair(1020401, CellInfo(OPTIONAL, NOCOLOR, "圣若望•波利多(St. John de Britto)")));
        mapPropers.insert(std::make_pair(1020402, CellInfo(OPTIONAL, NOCOLOR, "圣妇若翰纳(St. John of France)")));
        mapPropers.insert(std::make_pair(1020501, CellInfo(MEMORIAL, RED, "圣女亚加大(St. Agatha)")));
        // 6日
        mapPropers.insert(std::make_pair(1020601, CellInfo(MEMORIAL, RED, "圣郑安道及圣保禄弥基等(the Martyrs of Japan)")));
        mapPropers.insert(std::make_pair(1020602, CellInfo(OPTIONAL, NOCOLOR, "圣童郑安道", disableLang)));
        mapPropers.insert(std::make_pair(1020701, CellInfo(OPTIONAL, NOCOLOR, "圣女尤丽娜(St. Juliana Falconieri)")));
        mapPropers.insert(std::make_pair(1020801, CellInfo(OPTIONAL, NOCOLOR, "圣热罗莫•爱弥廉(St. Jierome Emiliani)")));
        mapPropers.insert(std::make_pair(1020802, CellInfo(OPTIONAL, NOCOLOR, "圣若望•玛达(St. John of Matha)")));
        // 9日
        mapPropers.insert(std::make_pair(1020901, CellInfo(OPTIONAL, NOCOLOR, "圣高德乐(St. Miguel Febres Cordero)", disableLang)));
        mapPropers.insert(std::make_pair(1020902, CellInfo(OPTIONAL, NOCOLOR, "圣撒比诺(St. Sabinus)")));
        // 10日
        mapPropers.insert(std::make_pair(1021001, CellInfo(MEMORIAL, WHITE, "圣女斯高拉蒂加(Scholastica)")));
        mapPropers.insert(std::make_pair(1021101, CellInfo(MEMORIAL, WHITE, "露德圣母显现(the Appearing of our Lady at Lourdes)")));
        // 12日
        mapPropers.insert(std::make_pair(1021201, CellInfo(OPTIONAL, NOCOLOR, "圣高登雪(主教 St. Gaudentius)", disableLang)));
        mapPropers.insert(std::make_pair(1021202, CellInfo(OPTIONAL, NOCOLOR, "圣路登(St. Ludan)")));
        mapPropers.insert(std::make_pair(1021301, CellInfo(OPTIONAL, NOCOLOR, "圣女加大利纳•利其(St. Catherine de Ricci)")));
        mapPropers.insert(std::make_pair(1021302, CellInfo(OPTIONAL, NOCOLOR, "圣玛蒂银“隐修士”(St. Martinian the Hermit)", disableLang)));
        mapPropers.insert(std::make_pair(1021303, CellInfo(OPTIONAL, NOCOLOR, "圣蓝月旺", chineseLang)));
        // 14日
        mapPropers.insert(std::make_pair(1021401, CellInfo(MEMORIAL, WHITE, "圣济利禄、圣美铎第(Ss. Cyril and Methodius)")));
        mapPropers.insert(std::make_pair(1021402, CellInfo(OPTIONAL, NOCOLOR, "圣华楞定(St. Valentine)")));
        mapPropers.insert(std::make_pair(1021501, CellInfo(OPTIONAL, NOCOLOR, "圣傅天定和圣约未达(Ss. Faustinus & Jovita)", disableLang)));
        mapPropers.insert(std::make_pair(1021502, CellInfo(OPTIONAL, NOCOLOR, "真福日安当(Bd. Jordan of Saxony)", disableLang)));
        mapPropers.insert(std::make_pair(1021503, CellInfo(OPTIONAL, NOCOLOR, "圣高隆汴(St. Claud La Colombiere)")));
        mapPropers.insert(std::make_pair(1021601, CellInfo(OPTIONAL, NOCOLOR, "圣奥乃西莫(St. Onesimus)")));
        // 17日
        mapPropers.insert(std::make_pair(1021701, CellInfo(OPTIONAL, NOCOLOR, "圣母忠仆会七位会祖(the Founders of the Servite Order)")));
        mapPropers.insert(std::make_pair(1021702, CellInfo(OPTIONAL, NOCOLOR, "圣刁杜禄与圣儒里安(殉道 Ss. Theodulus & Julian)", disableLang)));
        mapPropers.insert(std::make_pair(1021801, CellInfo(OPTIONAL, NOCOLOR, "圣西满(St. Simeon)")));
        mapPropers.insert(std::make_pair(1021901, CellInfo(OPTIONAL, NOCOLOR, "圣公拉(St. Conrad of Placenza)")));
        mapPropers.insert(std::make_pair(1021902, CellInfo(OPTIONAL, NOCOLOR, "圣易贞美", chineseLang)));
        mapPropers.insert(std::make_pair(1022001, CellInfo(OPTIONAL, NOCOLOR, "圣欧却琉(St. Eucherius)")));
        mapPropers.insert(std::make_pair(1022002, CellInfo(OPTIONAL, NOCOLOR, "圣弟拉诺、柴诺波等殉道(Ss. Tyrannio, Zenobius & other Martyrs)", disableLang)));
        // 21日
        mapPropers.insert(std::make_pair(1022101, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•达弥盎(St. Peter Damian)")));
        mapPropers.insert(std::make_pair(1022201, CellInfo(FEAST, WHITE, "建立圣伯多禄宗座(St. Peter’s Chair at Antioch)")));
        mapPropers.insert(std::make_pair(1022202, CellInfo(OPTIONAL, NOCOLOR, "圣女玛加利大•高多娜(St. Margaret Cortona)")));
        mapPropers.insert(std::make_pair(1022301, CellInfo(MEMORIAL, RED, "圣波利卡浦(St. Polycarp)")));
        // 24日
        mapPropers.insert(std::make_pair(1022401, CellInfo(OPTIONAL, NOCOLOR, "圣凯撒利乌•纳齐盎(St. Caesarius of Nazianzus)", disableLang)));
        mapPropers.insert(std::make_pair(1022402, CellInfo(OPTIONAL, NOCOLOR, "圣孟泰诺、圣路琪及其它烈士(Ss. Montantls, Lucius & their Companions)")));
        mapPropers.insert(std::make_pair(1022501, CellInfo(OPTIONAL, NOCOLOR, "圣女华波加(St. Walburga)", disableLang)));
        mapPropers.insert(std::make_pair(1022502, CellInfo(OPTIONAL, NOCOLOR, "圣泰拉修(St. Tarsius)")));
        mapPropers.insert(std::make_pair(1022601, CellInfo(OPTIONAL, NOCOLOR, "圣女美狄黛(St. Mechtilde)", disableLang)));
        mapPropers.insert(std::make_pair(1022602, CellInfo(OPTIONAL, NOCOLOR, "圣波菲利(St. Porphyry)")));
        mapPropers.insert(std::make_pair(1022701, CellInfo(OPTIONAL, NOCOLOR, "圣母痛苦圣嘉俾厄尔(St. Gabriel Possenti)")));
        mapPropers.insert(std::make_pair(1022702, CellInfo(OPTIONAL, NOCOLOR, "圣林达(St. Leander)", disableLang)));
        mapPropers.insert(std::make_pair(1022703, CellInfo(OPTIONAL, NOCOLOR, "圣额我略•纳雷科", disableLang)));
        mapPropers.insert(std::make_pair(1022801, CellInfo(OPTIONAL, NOCOLOR, "圣希拉利(St. Hilarius)")));
        mapPropers.insert(std::make_pair(1022802, CellInfo(OPTIONAL, NOCOLOR, "圣安日拉(St. Angela of Foligno)")));

        /******************3月*****************/
        // 1日
        mapPropers.insert(std::make_pair(1030101, CellInfo(OPTIONAL, NOCOLOR, "圣达味(St. David)")));
        mapPropers.insert(std::make_pair(1030102, CellInfo(OPTIONAL, NOCOLOR, "圣曹桂英", chineseLang)));
        mapPropers.insert(std::make_pair(1030201, CellInfo(OPTIONAL, NOCOLOR, "圣嘉德(St. Chad)")));
        mapPropers.insert(std::make_pair(1030202, CellInfo(OPTIONAL, NOCOLOR, "圣顾乃宫(St. Cunegund)", disableLang)));
        mapPropers.insert(std::make_pair(1030301, CellInfo(OPTIONAL, NOCOLOR, "圣加大利纳(St. Katharine Drexel)")));
        mapPropers.insert(std::make_pair(1030401, CellInfo(OPTIONAL, NOCOLOR, "圣加西弥禄(St. Casimir of Poland)")));
        mapPropers.insert(std::make_pair(1030501, CellInfo(OPTIONAL, NOCOLOR, "圣十字架若望若瑟(St. John Joseph of the Cross)")));
        // 6日
        mapPropers.insert(std::make_pair(1030601, CellInfo(OPTIONAL, NOCOLOR, "圣高莱德(St. Colette)")));
        mapPropers.insert(std::make_pair(1030602, CellInfo(OPTIONAL, NOCOLOR, "真福若尔当(Bd. Jordan of Pisa)", disableLang)));
        mapPropers.insert(std::make_pair(1030701, CellInfo(MEMORIAL, RED, "圣伯尔都亚、圣斐利谦等殉道(Ss. Perpertua Felicity and their Companions)")));
        mapPropers.insert(std::make_pair(1030702, CellInfo(OPTIONAL, NOCOLOR, "圣保禄“诚朴者”(St. Paul the Simple)", disableLang)));
        mapPropers.insert(std::make_pair(1030801, CellInfo(OPTIONAL, NOCOLOR, "天赐圣若望(St. John of God)")));
        mapPropers.insert(std::make_pair(1030901, CellInfo(OPTIONAL, NOCOLOR, "圣芳济加(St. Frances of Rome)")));
        mapPropers.insert(std::make_pair(1031001, CellInfo(MEMORIAL, RED, "色巴德等四十位圣人殉道(the Forty Martyrs of Sebastea)")));
        mapPropers.insert(std::make_pair(1031002, CellInfo(OPTIONAL, NOCOLOR, "圣若望•安其味(St. John Ogilve)", disableLang)));
        // 11日
        mapPropers.insert(std::make_pair(1031101, CellInfo(OPTIONAL, NOCOLOR, "圣欧乐日(St. Eulogius of Cordova)")));
        mapPropers.insert(std::make_pair(1031102, CellInfo(OPTIONAL, NOCOLOR, "圣君士坦丁(St. Constantine)", disableLang)));
        mapPropers.insert(std::make_pair(1031201, CellInfo(OPTIONAL, NOCOLOR, "圣戴法纳(St. Theophanes the Chronicler)")));
        mapPropers.insert(std::make_pair(1031202, CellInfo(OPTIONAL, NOCOLOR, "圣张大鹏", chineseLang)));
        mapPropers.insert(std::make_pair(1031301, CellInfo(OPTIONAL, NOCOLOR, "圣欧弗来西亚(St. Euphrasia)")));
        mapPropers.insert(std::make_pair(1031302, CellInfo(OPTIONAL, NOCOLOR, "圣尼赛福禄(St. Niceohorus)")));
        mapPropers.insert(std::make_pair(1031401, CellInfo(OPTIONAL, NOCOLOR, "圣玛蒂达(St. Matilda)")));
        mapPropers.insert(std::make_pair(1031501, CellInfo(OPTIONAL, NOCOLOR, "圣露易丝(St. Louisa De Marillac)")));
        mapPropers.insert(std::make_pair(1031502, CellInfo(OPTIONAL, NOCOLOR, "圣格肋孟•浩卜(St. Clemlent Hofbauer)")));
        // 16日
        mapPropers.insert(std::make_pair(1031601, CellInfo(OPTIONAL, NOCOLOR, "圣赫利巴(St. Heribert)")));
        mapPropers.insert(std::make_pair(1031701, CellInfo(OPTIONAL, NOCOLOR, "圣巴特里爵(St. Patrick)")));
        mapPropers.insert(std::make_pair(1031702, CellInfo(OPTIONAL, NOCOLOR, "圣日多达•尼凡拉(St. Gertrude of Nivelles)")));
        mapPropers.insert(std::make_pair(1031801, CellInfo(OPTIONAL, NOCOLOR, "耶路撒冷•圣济利禄(St. Cyril)")));
        mapPropers.insert(std::make_pair(1031802, CellInfo(OPTIONAL, NOCOLOR, "圣安色莫(St. Anselm)", disableLang)));
        mapPropers.insert(std::make_pair(1031901, CellInfo(FEAST, WHITE, "圣母净配圣若瑟(St. Joseph)")));
        mapPropers.insert(std::make_pair(1032001, CellInfo(OPTIONAL, NOCOLOR, "圣格时白(St. Cuthbert)")));
        // 21日
        mapPropers.insert(std::make_pair(1032101, CellInfo(OPTIONAL, NOCOLOR, "圣尼格老•冯物洛(St. Nicholas de flue)", disableLang)));
        mapPropers.insert(std::make_pair(1032102, CellInfo(OPTIONAL, NOCOLOR, "圣恩达、圣女芳佳(St. Enda and St. Fanchea)")));
        mapPropers.insert(std::make_pair(1032201, CellInfo(OPTIONAL, NOCOLOR, "圣婴西满和圣童威廉(Ss. Simen of Trent and William of Norwich)")));
        mapPropers.insert(std::make_pair(1032301, CellInfo(OPTIONAL, NOCOLOR, "圣多利波(St. Turibius)", disableLang)));
        mapPropers.insert(std::make_pair(1032302, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•奥利沃(St. Joseph Oriol)")));
        mapPropers.insert(std::make_pair(1032401, CellInfo(OPTIONAL, NOCOLOR, "圣加大利纳•瑞典(St. Catherine of Sweden)")));
        mapPropers.insert(std::make_pair(1032402, CellInfo(OPTIONAL, NOCOLOR, "圣依勒内(St. Irenaeus)")));
        mapPropers.insert(std::make_pair(1032501, CellInfo(FEAST, WHITE, "圣母领报(the Annunciation of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1032502, CellInfo(OPTIONAL, NOCOLOR, "真福玛加大•格利塞罗(殉道 Bd. Margaret Clitherow)")));
        mapPropers.insert(std::make_pair(1032503, CellInfo(OPTIONAL, NOCOLOR, "善盗(the good thief)", disableLang)));
        // 26日
        mapPropers.insert(std::make_pair(1032601, CellInfo(OPTIONAL, NOCOLOR, "圣路基(St. Ludger)")));
        mapPropers.insert(std::make_pair(1032602, CellInfo(OPTIONAL, NOCOLOR, "圣加斯多罗(St. Castulus)")));
        mapPropers.insert(std::make_pair(1032701, CellInfo(OPTIONAL, NOCOLOR, "圣若望“埃及人”(St. John of Egypt)")));
        mapPropers.insert(std::make_pair(1032801, CellInfo(OPTIONAL, NOCOLOR, "圣西斯督三世(St. Sixrus III)")));
        mapPropers.insert(std::make_pair(1032901, CellInfo(OPTIONAL, NOCOLOR, "圣路伯(St. Rupert)", disableLang)));
        mapPropers.insert(std::make_pair(1032902, CellInfo(OPTIONAL, NOCOLOR, "圣约纳和巴拉古(Ss. Jonas and Barachisius)")));
        mapPropers.insert(std::make_pair(1033001, CellInfo(OPTIONAL, NOCOLOR, "圣若望•克利马古(St. John Climacus)")));
        mapPropers.insert(std::make_pair(1033101, CellInfo(OPTIONAL, NOCOLOR, "圣达尼尔隐修士(St. Daniel of Murano)")));

        /***************4月**************/
        // 1日
        mapPropers.insert(std::make_pair(1040101, CellInfo(OPTIONAL, NOCOLOR, "圣许格(St. Hugh of Grenoble)")));
        mapPropers.insert(std::make_pair(1040102, CellInfo(OPTIONAL, NOCOLOR, "真福路道味•巴华尼(Bd. Ludovic Pavoni)", disableLang)));
        mapPropers.insert(std::make_pair(1040201, CellInfo(OPTIONAL, NOCOLOR, "圣方济各保拉(St. Francis of Paola)")));
        mapPropers.insert(std::make_pair(1040301, CellInfo(OPTIONAL, NOCOLOR, "圣理查德(St. Richard)")));
        mapPropers.insert(std::make_pair(1040401, CellInfo(OPTIONAL, NOCOLOR, "圣依西多(St. Isidore)")));
        mapPropers.insert(std::make_pair(1040402, CellInfo(OPTIONAL, NOCOLOR, "圣“农民”依西多禄希道(St. Isidore the Husbandman)", disableLang)));
        mapPropers.insert(std::make_pair(1040501, CellInfo(OPTIONAL, NOCOLOR, "圣味增爵•斐勒洛(St. Vincent Ferrer)")));
        mapPropers.insert(std::make_pair(1040502, CellInfo(OPTIONAL, NOCOLOR, "真福儒利亚纳(Bd. Juliana of Mount Cornillon)", disableLang)));
        // 6日
        mapPropers.insert(std::make_pair(1040601, CellInfo(OPTIONAL, NOCOLOR, "圣塞来斯定一世(St. Celestinel)")));
        mapPropers.insert(std::make_pair(1040701, CellInfo(MEMORIAL, WHITE, "圣若翰•兰沙(St. John Baptist de la Salle)")));
        mapPropers.insert(std::make_pair(1040801, CellInfo(OPTIONAL, NOCOLOR, "真福尤丽•贝略(Bd. Julia Billiart)")));
        mapPropers.insert(std::make_pair(1040802, CellInfo(OPTIONAL, NOCOLOR, "真福亚松大(Bd. Maria Assunta)")));
        mapPropers.insert(std::make_pair(1040901, CellInfo(OPTIONAL, NOCOLOR, "圣华德托蒂(St. Waldetrudis)")));
        mapPropers.insert(std::make_pair(1040902, CellInfo(OPTIONAL, NOCOLOR, "真福欧伯(Bd. Ubald of Florence)", disableLang)));
        mapPropers.insert(std::make_pair(1041001, CellInfo(OPTIONAL, NOCOLOR, "圣傅培(St. Fulbert)")));
        // 11日
        mapPropers.insert(std::make_pair(1041101, CellInfo(MEMORIAL, RED, "圣达尼老(St. Stanislaus)")));
        mapPropers.insert(std::make_pair(1041102, CellInfo(OPTIONAL, NOCOLOR, "圣瑰玛•甘甘妮(St. Gemma Galgan)", disableLang)));
        mapPropers.insert(std::make_pair(1041201, CellInfo(OPTIONAL, NOCOLOR, "圣儒略一世(St. Julius I)")));
        mapPropers.insert(std::make_pair(1041202, CellInfo(OPTIONAL, NOCOLOR, "圣柴诺(St. Zeno)")));
        mapPropers.insert(std::make_pair(1041301, CellInfo(OPTIONAL, NOCOLOR, "圣玛尔定一世(St. Martin I)")));
        mapPropers.insert(std::make_pair(1041401, CellInfo(OPTIONAL, NOCOLOR, "圣谛步爵、圣华肋廉、圣玛息莫(Ss. Tiburtius, Valerius and Maxiuss)")));
        mapPropers.insert(std::make_pair(1041402, CellInfo(OPTIONAL, NOCOLOR, "真福李维娜(Bd. Lydwina of Schiedam)")));
        mapPropers.insert(std::make_pair(1041501, CellInfo(OPTIONAL, NOCOLOR, "圣本笃•若瑟•雷伯(St. Benedict Joseph Labre)")));
        // 16日
        mapPropers.insert(std::make_pair(1041601, CellInfo(OPTIONAL, NOCOLOR, "圣伯尔纳德(St. Bernadette or Mary Bernard Soubinous)")));
        mapPropers.insert(std::make_pair(1041701, CellInfo(OPTIONAL, NOCOLOR, "圣阿尼塞多(St. Anicetus)", disableLang)));
        mapPropers.insert(std::make_pair(1041702, CellInfo(OPTIONAL, NOCOLOR, "圣斯德望•哈定(St. Stephen Harding)")));
        mapPropers.insert(std::make_pair(1041801, CellInfo(OPTIONAL, NOCOLOR, "圣加帝诺(St. Caldinus)")));
        mapPropers.insert(std::make_pair(1041802, CellInfo(OPTIONAL, NOCOLOR, "真福玛利亚(Bd. Mary of the Incarnation)")));
        mapPropers.insert(std::make_pair(1041803, CellInfo(OPTIONAL, NOCOLOR, "圣马塞兰(St. Marcellin Chanmagnat)", disableLang)));
        mapPropers.insert(std::make_pair(1041901, CellInfo(OPTIONAL, NOCOLOR, "圣良九世(St. Leo IX. Bruno)")));
        mapPropers.insert(std::make_pair(1041902, CellInfo(OPTIONAL, NOCOLOR, "圣亚斐奇(St. Alphege)")));
        mapPropers.insert(std::make_pair(1042001, CellInfo(OPTIONAL, NOCOLOR, "圣女依搦斯•蒙德波(St. Agnes of Montepulciano)")));
        // 21日
        mapPropers.insert(std::make_pair(1042101, CellInfo(OPTIONAL, NOCOLOR, "圣安色莫(St. Anseln)")));
        mapPropers.insert(std::make_pair(1042201, CellInfo(OPTIONAL, NOCOLOR, "圣索台禄(教宗殉道 St. Soter)", disableLang)));
        mapPropers.insert(std::make_pair(1042202, CellInfo(OPTIONAL, NOCOLOR, "圣爱比巴巨、圣亚历山大(Ss. Epipodius and Alexander)")));
        mapPropers.insert(std::make_pair(1042301, CellInfo(OPTIONAL, NOCOLOR, "圣乔治(St. George)")));
        mapPropers.insert(std::make_pair(1042302, CellInfo(OPTIONAL, NOCOLOR, "真福吉利时(Bd. Giles of Assisi)")));
        mapPropers.insert(std::make_pair(1042401, CellInfo(OPTIONAL, NOCOLOR, "圣斐德(St. Fidelis of Sigmaringen)", disableLang)));
        mapPropers.insert(std::make_pair(1042402, CellInfo(OPTIONAL, NOCOLOR, "圣女贝莱蒂(St. Pelletier)")));
        mapPropers.insert(std::make_pair(1042501, CellInfo(FEAST, RED, "圣马尔谷(St. Mark)")));
        // 26日
        mapPropers.insert(std::make_pair(1042601, CellInfo(OPTIONAL, NOCOLOR, "圣格肋多(St. Cletus)")));
        mapPropers.insert(std::make_pair(1042602, CellInfo(OPTIONAL, NOCOLOR, "圣女方佳(St. Franca of Piacenza)")));
        mapPropers.insert(std::make_pair(1042701, CellInfo(OPTIONAL, NOCOLOR, "圣女纪达(St. Zita)")));
        mapPropers.insert(std::make_pair(1042801, CellInfo(OPTIONAL, NOCOLOR, "圣类思•葛利宁•蒙福(St. Louis Mary Grignion of Monffort)", disableLang)));
        mapPropers.insert(std::make_pair(1042802, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•尚耐(St. Peter Mary Chanel)")));
        mapPropers.insert(std::make_pair(1042901, CellInfo(MEMORIAL, WHITE, "圣女加大利纳•仙娜(St. Catherine of Siena)")));
        mapPropers.insert(std::make_pair(1042902, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•高登伦哥(St. Joseph Cottolengo)", disableLang)));
        mapPropers.insert(std::make_pair(1043001, CellInfo(OPTIONAL, NOCOLOR, "圣比约五世(Pius V Michele Ghislieril)")));

        /***************5月***************/
        // 1日
        mapPropers.insert(std::make_pair(1050101, CellInfo(MEMORIAL, WHITE, "大圣若瑟劳工主保(St. Joseph the Worker)")));
        mapPropers.insert(std::make_pair(1050102, CellInfo(OPTIONAL, NOCOLOR, "圣亚玛多(St. Amator)", disableLang)));
        mapPropers.insert(std::make_pair(1050201, CellInfo(MEMORIAL, WHITE, "圣亚大纳削(St. Athanasius)")));
        mapPropers.insert(std::make_pair(1050202, CellInfo(OPTIONAL, NOCOLOR, "圣女维芭达(St. Wibada)", disableLang)));
        mapPropers.insert(std::make_pair(1050301, CellInfo(FEAST, RED, "圣斐理伯、圣雅各伯宗徒(Ss. Philip and James)")));
        mapPropers.insert(std::make_pair(1050401, CellInfo(OPTIONAL, NOCOLOR, "圣福里安(St. Florian)", disableLang)));
        mapPropers.insert(std::make_pair(1050402, CellInfo(OPTIONAL, NOCOLOR, "英格兰和威尔士殉道烈士(the Martyrs of England and Wales)")));
        mapPropers.insert(std::make_pair(1050501, CellInfo(OPTIONAL, NOCOLOR, "圣安日洛(St. Angelo)")));
        // 6日
        mapPropers.insert(std::make_pair(1050601, CellInfo(OPTIONAL, NOCOLOR, "圣若望宗徒拉丁门前受鼎镬刑(St. John Before the Latin Gate)", disableLang)));
        mapPropers.insert(std::make_pair(1050602, CellInfo(OPTIONAL, NOCOLOR, "圣多明我•沙维豪(St. Donfinic Savio)")));
        mapPropers.insert(std::make_pair(1050701, CellInfo(OPTIONAL, NOCOLOR, "圣若望•比华力(St. John of Beverley)")));
        mapPropers.insert(std::make_pair(1050702, CellInfo(OPTIONAL, NOCOLOR, "真福罗撒•味内丽尼(Bd. Rose Venerini)")));
        mapPropers.insert(std::make_pair(1050801, CellInfo(OPTIONAL, NOCOLOR, "圣波尼法爵四世(St. Boniface IV)")));
        mapPropers.insert(std::make_pair(1050802, CellInfo(OPTIONAL, NOCOLOR, "圣女玛达肋纳•嘉诺撒(St. Magdalen Di Canossa)")));
        mapPropers.insert(std::make_pair(1050803, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄(St. Peter)", disableLang)));
        mapPropers.insert(std::make_pair(1050901, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•诺拉谷(St. Peter Nolasco)")));
        mapPropers.insert(std::make_pair(1051001, CellInfo(OPTIONAL, NOCOLOR, "圣安多宁(St. Antoninus)")));
        mapPropers.insert(std::make_pair(1051002, CellInfo(OPTIONAL, NOCOLOR, "圣若望•亚维拉(St. John of Avila)")));
        // 11日
        mapPropers.insert(std::make_pair(1051101, CellInfo(OPTIONAL, NOCOLOR, "圣依纳爵•雷可尼(St. Ignatius of Laconi)")));
        mapPropers.insert(std::make_pair(1051102, CellInfo(OPTIONAL, NOCOLOR, "圣方济各•基罗拉莫(St. Francis Di Girolamo)")));
        mapPropers.insert(std::make_pair(1051201, CellInfo(OPTIONAL, NOCOLOR, "圣聂略及圣亚基略(Ss. Nereus and Achilleus)")));
        mapPropers.insert(std::make_pair(1051202, CellInfo(OPTIONAL, NOCOLOR, "圣庞加爵(St. Pancras)")));
        mapPropers.insert(std::make_pair(1051301, CellInfo(MEMORIAL, WHITE, "法蒂玛圣母(Our Lady of Fatima)")));
        mapPropers.insert(std::make_pair(1051302, CellInfo(OPTIONAL, NOCOLOR, "圣玛利亚•玛萨利洛(St. Mary Mazzarello)")));
        mapPropers.insert(std::make_pair(1051401, CellInfo(FEAST, RED, "圣玛弟亚宗徒(St. Matthias)")));
        mapPropers.insert(std::make_pair(1051402, CellInfo(OPTIONAL, NOCOLOR, "圣弥额尔•加利古(St. Michael Garicoits)")));
        mapPropers.insert(std::make_pair(1051501, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄和圣刁尼霞(Ss. Peter and Dionysia)")));
        // 16日
        mapPropers.insert(std::make_pair(1051601, CellInfo(OPTIONAL, NOCOLOR, "圣西满•斯道克(St. Simon Stock)")));
        mapPropers.insert(std::make_pair(1051602, CellInfo(OPTIONAL, NOCOLOR, "圣吴巴多(St. Ubald)")));
        mapPropers.insert(std::make_pair(1051701, CellInfo(OPTIONAL, NOCOLOR, "圣巴斯卦(St. Paschal Baylon)")));
        mapPropers.insert(std::make_pair(1051702, CellInfo(OPTIONAL, NOCOLOR, "圣刘文元", chineseLang)));
        mapPropers.insert(std::make_pair(1051801, CellInfo(OPTIONAL, NOCOLOR, "圣若望一世(St. John I)")));
        mapPropers.insert(std::make_pair(1051802, CellInfo(OPTIONAL, NOCOLOR, "圣斐理斯(St. Felix Cantalice)")));
        mapPropers.insert(std::make_pair(1051901, CellInfo(OPTIONAL, NOCOLOR, "圣塞来斯定五世(St. Celestine V)")));
        mapPropers.insert(std::make_pair(1051902, CellInfo(OPTIONAL, NOCOLOR, "真福奥斯定•诺未洛(Bd. Augustine Novello)", disableLang)));
        mapPropers.insert(std::make_pair(1052001, CellInfo(OPTIONAL, NOCOLOR, "圣伯尔纳定•栖亚那(St. Bernardine of Siena)")));
        mapPropers.insert(std::make_pair(1052002, CellInfo(OPTIONAL, NOCOLOR, "真福高隆巴(Bd. Columba of Rieti)")));
        // 21日
        mapPropers.insert(std::make_pair(1052101, CellInfo(OPTIONAL, NOCOLOR, "圣维克多(St. Victor of Marseilles)")));
        mapPropers.insert(std::make_pair(1052102, CellInfo(OPTIONAL, NOCOLOR, "圣多福•麦哲伦司铎及同伴(St. Donatus Magellicanus and Companions)")));
        mapPropers.insert(std::make_pair(1052201, CellInfo(OPTIONAL, NOCOLOR, "圣丽达(St. Rita of Cascia)")));
        mapPropers.insert(std::make_pair(1052202, CellInfo(OPTIONAL, NOCOLOR, "真福若基玛(Bd. Joachima de Mas de Veruna)")));
        mapPropers.insert(std::make_pair(1052301, CellInfo(OPTIONAL, NOCOLOR, "圣若翰•路西(St. John Baptist Rossi)")));
        mapPropers.insert(std::make_pair(1052401, CellInfo(FEAST, WHITE, "圣母进教之佑(Our Lady Help of Christians)")));
        mapPropers.insert(std::make_pair(1052402, CellInfo(OPTIONAL, NOCOLOR, "圣味增爵•雷冷(St. Vincent of Lerins)")));
        mapPropers.insert(std::make_pair(1052501, CellInfo(OPTIONAL, NOCOLOR, "圣伯达(St. Bede the Venerable)")));
        mapPropers.insert(std::make_pair(1052502, CellInfo(OPTIONAL, NOCOLOR, "圣额我略七世(St. Gregory VII)")));
        mapPropers.insert(std::make_pair(1052503, CellInfo(OPTIONAL, NOCOLOR, "圣玛达肋纳•沙斐•亚巴拉(St. Madeleine Sophie Barat)", disableLang)));
        // 26日
        mapPropers.insert(std::make_pair(1052601, CellInfo(MEMORIAL, WHITE, "圣斐理伯•内利(St. Philip Neri)")));
        mapPropers.insert(std::make_pair(1052701, CellInfo(OPTIONAL, NOCOLOR, "圣奥斯定（坎特伯里总主教）(St. Augustine of Canterbury)")));
        mapPropers.insert(std::make_pair(1052801, CellInfo(OPTIONAL, NOCOLOR, "圣日曼诺斯(St. Gemanus of Paris)")));
        mapPropers.insert(std::make_pair(1052802, CellInfo(OPTIONAL, NOCOLOR, "真福多默•福特及其他殉道烈士(Bd. Thomas Ford and his Campanions)")));
        mapPropers.insert(std::make_pair(1052901, CellInfo(OPTIONAL, NOCOLOR, "圣济利禄•凯撒利亚(St. Cyril of Caesarea)", disableLang)));
        mapPropers.insert(std::make_pair(1052902, CellInfo(MEMORIAL, WHITE, "圣保禄六世(St. Paul VI)")));
        mapPropers.insert(std::make_pair(1052903, CellInfo(OPTIONAL, NOCOLOR, "圣何开枝", chineseLang)));
        mapPropers.insert(std::make_pair(1053001, CellInfo(OPTIONAL, NOCOLOR, "圣女贞德(St. Joan of Arc)")));
        mapPropers.insert(std::make_pair(1053101, CellInfo(FEAST, WHITE, "圣母访亲(the Vistation of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1053102, CellInfo(OPTIONAL, NOCOLOR, "圣母诸宠中保及中华圣母节(Our Lady of all Graces and Queen of China)", chineseLang)));

        /*************6月***************/
        // 1日
        mapPropers.insert(std::make_pair(1060101, CellInfo(MEMORIAL, RED, "圣犹思定殉道(St. Justin)")));
        mapPropers.insert(std::make_pair(1060102, CellInfo(OPTIONAL, NOCOLOR, "日本殉道烈士(The Martyrs of Japan, II)")));
        mapPropers.insert(std::make_pair(1060201, CellInfo(OPTIONAL, NOCOLOR, "圣玛策廉、圣伯多禄(Ss. Marcellinus and Peter)")));
        mapPropers.insert(std::make_pair(1060202, CellInfo(OPTIONAL, NOCOLOR, "里昂及维安殉道烈士(St. Pothinus and his Companions, the Martyrs of Lyons and Vienne)", disableLang)));
        mapPropers.insert(std::make_pair(1060301, CellInfo(MEMORIAL, RED, "圣嘉禄•卢安加及同伴(St. Charles Lwanga and Companions)")));
        mapPropers.insert(std::make_pair(1060302, CellInfo(OPTIONAL, NOCOLOR, "圣基文(St. Kevin)", disableLang)));
        mapPropers.insert(std::make_pair(1060401, CellInfo(OPTIONAL, NOCOLOR, "圣方济各•加辣巧洛(St. Francis Caracciolo)")));
        mapPropers.insert(std::make_pair(1060402, CellInfo(OPTIONAL, NOCOLOR, "圣达米盎(St. Damian)", disableLang)));
        mapPropers.insert(std::make_pair(1060501, CellInfo(MEMORIAL, RED, "圣波尼法爵(St. Boniface)")));
        // 6日
        mapPropers.insert(std::make_pair(1060601, CellInfo(OPTIONAL, NOCOLOR, "圣诺伯多(St. Norbert)")));
        mapPropers.insert(std::make_pair(1060701, CellInfo(OPTIONAL, NOCOLOR, "可敬多默•坎比斯(Ven. Thomas A Kenpis)", disableLang)));
        mapPropers.insert(std::make_pair(1060702, CellInfo(OPTIONAL, NOCOLOR, "真福巴蒂斯达•华拉妮(Bd. Baptista Varani)", disableLang)));
        mapPropers.insert(std::make_pair(1060703, CellInfo(OPTIONAL, NOCOLOR, "圣罗拔(St. Robert)")));
        mapPropers.insert(std::make_pair(1060801, CellInfo(OPTIONAL, NOCOLOR, "圣迈达(St. Medard)")));
        mapPropers.insert(std::make_pair(1060802, CellInfo(OPTIONAL, NOCOLOR, "圣克路多(St. Clodulf)")));
        mapPropers.insert(std::make_pair(1060901, CellInfo(OPTIONAL, NOCOLOR, "圣爱弗冷(St. Ephraem)")));
        mapPropers.insert(std::make_pair(1060902, CellInfo(OPTIONAL, NOCOLOR, "圣高隆巴(St. Columba)")));
        mapPropers.insert(std::make_pair(1060903, CellInfo(OPTIONAL, NOCOLOR, "真福亚纳•玛利亚•泰琪(Bd. Anne Mary Taigi)", disableLang)));
        mapPropers.insert(std::make_pair(1061001, CellInfo(OPTIONAL, NOCOLOR, "圣日多列和殉道烈士(Ss. Getulius and his Companions)")));
        // 11日
        mapPropers.insert(std::make_pair(1061101, CellInfo(FEAST, RED, "圣巴尔纳伯(St. Barnabas)")));
        mapPropers.insert(std::make_pair(1061102, CellInfo(OPTIONAL, NOCOLOR, "真福宝拉(Bd. Paula Frassinetti)", disableLang)));
        mapPropers.insert(std::make_pair(1061201, CellInfo(OPTIONAL, NOCOLOR, "圣若望•瑟哈公(St. John of Sahagun)")));
        mapPropers.insert(std::make_pair(1061202, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄(St. Peter of Mount Athos)", disableLang)));
        mapPropers.insert(std::make_pair(1061301, CellInfo(MEMORIAL, WHITE, "圣安多尼(St. Antony of Padua)")));
        mapPropers.insert(std::make_pair(1061401, CellInfo(OPTIONAL, NOCOLOR, "圣梅多田(St. Methodius I of Constantinople)")));
        mapPropers.insert(std::make_pair(1061501, CellInfo(OPTIONAL, NOCOLOR, "圣女任曼娜(St. Germaine Cousin)")));
        mapPropers.insert(std::make_pair(1061502, CellInfo(OPTIONAL, NOCOLOR, "圣女亚兰弟(St. Aleydis)")));
        // 16日
        mapPropers.insert(std::make_pair(1061601, CellInfo(OPTIONAL, NOCOLOR, "圣若望•方济各•雷奇(St. John Francis Regis)")));
        mapPropers.insert(std::make_pair(1061602, CellInfo(OPTIONAL, NOCOLOR, "圣女吕佳田(St. Lutgardis)")));
        mapPropers.insert(std::make_pair(1061701, CellInfo(OPTIONAL, NOCOLOR, "圣尼冈德、圣马星(Ss. Nicander and Marcian)")));
        mapPropers.insert(std::make_pair(1061702, CellInfo(OPTIONAL, NOCOLOR, "圣女爱弥丽(St. Emily de Vialar)")));
        mapPropers.insert(std::make_pair(1061801, CellInfo(OPTIONAL, NOCOLOR, "圣马尔谷、圣玛策廉(Ss. Mark and MareeUian)")));
        mapPropers.insert(std::make_pair(1061802, CellInfo(OPTIONAL, NOCOLOR, "圣女依撒伯尔•许诺(St. Elizabeth of Schonau)")));
        mapPropers.insert(std::make_pair(1061803, CellInfo(OPTIONAL, NOCOLOR, "圣额我略•巴巴里果(St. Gregory Barbarigo)", disableLang)));
        mapPropers.insert(std::make_pair(1061901, CellInfo(OPTIONAL, NOCOLOR, "圣罗慕铎(St. Romuald)")));
        mapPropers.insert(std::make_pair(1061902, CellInfo(OPTIONAL, NOCOLOR, "圣伯吕诺(St. Bruno)", disableLang)));
        mapPropers.insert(std::make_pair(1062001, CellInfo(OPTIONAL, NOCOLOR, "圣西尔物留(St. Silverius)")));
        mapPropers.insert(std::make_pair(1062002, CellInfo(OPTIONAL, NOCOLOR, "真福米凯琳(Bd. Michelina of Pesaro)")));
        // 21日
        mapPropers.insert(std::make_pair(1062101, CellInfo(MEMORIAL, WHITE, "圣类思•公撒格(St. Aloysius)")));
        mapPropers.insert(std::make_pair(1062102, CellInfo(OPTIONAL, NOCOLOR, "圣欧瑟伯(St. Eusebius of Samoasta)")));
        mapPropers.insert(std::make_pair(1062201, CellInfo(OPTIONAL, NOCOLOR, "圣保林(St. Paulinus of Nola)")));
        mapPropers.insert(std::make_pair(1062202, CellInfo(OPTIONAL, NOCOLOR, "圣若望•菲雪及圣多默•莫尔(Ss. John Fisher and Thomas More)")));
        mapPropers.insert(std::make_pair(1062203, CellInfo(OPTIONAL, NOCOLOR, "圣多默•莫尔(St. Thomas More)", disableLang)));
        mapPropers.insert(std::make_pair(1062301, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•嘉法沙(St. Joseph Cafasso)")));
        mapPropers.insert(std::make_pair(1062302, CellInfo(WEEKDAY, WHITE, "圣若翰洗者诞辰前夕")));
        mapPropers.insert(std::make_pair(1062303, CellInfo(OPTIONAL, NOCOLOR, "圣袁在德", chineseLang)));
        mapPropers.insert(std::make_pair(1062401, CellInfo(SOLEMNITY, WHITE, "圣若翰洗者诞辰(The Birthday of St. John the Baptist)")));
        mapPropers.insert(std::make_pair(1062501, CellInfo(OPTIONAL, NOCOLOR, "圣威廉•维吉尔(St. William of Monte Vergine)")));
        mapPropers.insert(std::make_pair(1062502, CellInfo(OPTIONAL, NOCOLOR, "圣女佛波罗尼(St. Febronia)")));
        // 26日
        mapPropers.insert(std::make_pair(1062601, CellInfo(OPTIONAL, NOCOLOR, "圣安德莫(St. Anthelm)")));
        mapPropers.insert(std::make_pair(1062602, CellInfo(MEMORIAL, WHITE, "圣施礼华(St. Josemaria)")));
        mapPropers.insert(std::make_pair(1062701, CellInfo(OPTIONAL, NOCOLOR, "圣济利禄(St. Cyril)")));
        mapPropers.insert(std::make_pair(1062801, CellInfo(MEMORIAL, RED, "圣依勒内(St. Irenaeus)")));
        mapPropers.insert(std::make_pair(1062802, CellInfo(OPTIONAL, NOCOLOR, "圣波罗德格、圣波太米诺及其他殉道烈士(Ss. Blutarch Potamiaena and their Companions)", disableLang)));
        mapPropers.insert(std::make_pair(1062803, CellInfo(WEEKDAY, RED, "圣伯多禄及圣保禄宗徒前夕")));
        mapPropers.insert(std::make_pair(1062901, CellInfo(SOLEMNITY, RED, "圣伯多禄及圣保禄宗徒(St. Peter Apostle & St. Paul Apostle)")));
        mapPropers.insert(std::make_pair(1063001, CellInfo(MEMORIAL, RED, "罗马第一批殉道烈士(Martyrs of Rome, I)")));

        /*************7月**************/
        // 1日
        mapPropers.insert(std::make_pair(1070101, CellInfo(OPTIONAL, NOCOLOR, "圣珈尔(St. Gall)")));
        mapPropers.insert(std::make_pair(1070102, CellInfo(OPTIONAL, NOCOLOR, "真福多默•李斯斐(Bd. Thomas Maxfield)", disableLang)));
        mapPropers.insert(std::make_pair(1070201, CellInfo(OPTIONAL, NOCOLOR, "圣博策稣、圣玛谛酿(殉道 Ss. Processus and Martinian)", disableLang)));
        mapPropers.insert(std::make_pair(1070202, CellInfo(OPTIONAL, NOCOLOR, "圣奥多(St. Otto)")));
        mapPropers.insert(std::make_pair(1070301, CellInfo(FEAST, RED, "圣多默(St. Thomas the Apostle)")));
        mapPropers.insert(std::make_pair(1070401, CellInfo(MEMORIAL, WHITE, "圣依撒伯尔(St. Elizabeth of Portuga)")));
        mapPropers.insert(std::make_pair(1070501, CellInfo(OPTIONAL, NOCOLOR, "圣安多尼•匝加利(St. Antony Zaccaria)")));
        // 6日
        mapPropers.insert(std::make_pair(1070601, CellInfo(OPTIONAL, NOCOLOR, "圣玛利亚•葛蕾蒂(St. Maria Goretti)")));
        mapPropers.insert(std::make_pair(1070701, CellInfo(OPTIONAL, NOCOLOR, "圣庞德诺(St. Pantaenus)")));
        mapPropers.insert(std::make_pair(1070801, CellInfo(OPTIONAL, NOCOLOR, "圣艾士波和卓娅(Ss. Hesperus and Zoa)")));
        mapPropers.insert(std::make_pair(1070802, CellInfo(OPTIONAL, NOCOLOR, "圣武文印", chineseLang)));
        if(checkContain(chineseLang, lang)) {
            mapPropers.insert(std::make_pair(1070901, CellInfo(FEAST, RED, "中华诸圣及真福(The Martyrs of China)", chineseLang)));
        } else {
            mapPropers.insert(std::make_pair(1070901, CellInfo(OPTIONAL, NOCOLOR, "中华诸圣及真福(The Martyrs of China)")));
        }
        mapPropers.insert(std::make_pair(1070902, CellInfo(OPTIONAL, NOCOLOR, "圣尼各老•比克及其它殉道烈士(Ss. Nicholas Pieck and his Companions)")));
        mapPropers.insert(std::make_pair(1070903, CellInfo(OPTIONAL, NOCOLOR, "圣万罗尼加•祁拉尼(St. Veronica Giuliani)", disableLang)));
        mapPropers.insert(std::make_pair(1071001, CellInfo(OPTIONAL, NOCOLOR, "七位圣昆仲(the Seven Brothers and St. Feheity)")));
        // 11日
        mapPropers.insert(std::make_pair(1071101, CellInfo(MEMORIAL, WHITE, "圣本笃(院长 St. Benedict)")));
        mapPropers.insert(std::make_pair(1071201, CellInfo(OPTIONAL, NOCOLOR, "越南殉道烈士(the Martyrs of Indo-China, I)")));
        mapPropers.insert(std::make_pair(1071301, CellInfo(OPTIONAL, NOCOLOR, "圣亨利二世(St. Henry II)")));
        mapPropers.insert(std::make_pair(1071302, CellInfo(OPTIONAL, NOCOLOR, "圣息拉(St. Silas)", disableLang)));
        mapPropers.insert(std::make_pair(1071303, CellInfo(OPTIONAL, NOCOLOR, "圣欧杰(St. Eugenius)", disableLang)));
        mapPropers.insert(std::make_pair(1071401, CellInfo(OPTIONAL, NOCOLOR, "圣加弥禄(St. Camillus De Lellis)")));
        mapPropers.insert(std::make_pair(1071501, CellInfo(MEMORIAL, WHITE, "圣文都辣(St. Bonaventure)")));
        mapPropers.insert(std::make_pair(1071502, CellInfo(OPTIONAL, NOCOLOR, "圣亚大纳削(St. Athanasius)")));
        // 16日
        mapPropers.insert(std::make_pair(1071601, CellInfo(MEMORIAL, WHITE, "加尔默罗圣母(The Commemoration of Our Lady of Mount Carmel)")));
        mapPropers.insert(std::make_pair(1071602, CellInfo(OPTIONAL, NOCOLOR, "圣女玛利亚•玛达肋纳•巴斯德(St. Mary Magdalem Postel)")));
        mapPropers.insert(std::make_pair(1071701, CellInfo(OPTIONAL, NOCOLOR, "圣亚肋叔(St. Alexius)")));
        mapPropers.insert(std::make_pair(1071702, CellInfo(OPTIONAL, NOCOLOR, "圣女玛珊利纳(St. Marcellina)")));
        mapPropers.insert(std::make_pair(1071801, CellInfo(OPTIONAL, NOCOLOR, "圣威德廉(St. Frederick)")));
        mapPropers.insert(std::make_pair(1071901, CellInfo(OPTIONAL, NOCOLOR, "圣女儒斯大、圣妇卢菲娜(Ss. Justa and Rufina)", disableLang)));
        mapPropers.insert(std::make_pair(1071902, CellInfo(OPTIONAL, NOCOLOR, "圣亚赛热(St. Arsenius the Great)")));
        mapPropers.insert(std::make_pair(1072001, CellInfo(OPTIONAL, NOCOLOR, "圣厄利亚和圣法来文(Ss. Elias and Flavian)", disableLang)));
        mapPropers.insert(std::make_pair(1072002, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•巴尔撒巴(St. Joseph Barsabas)")));
        mapPropers.insert(std::make_pair(1072003, CellInfo(OPTIONAL, NOCOLOR, "圣亚博那(St. Apollinaris)", disableLang)));
        mapPropers.insert(std::make_pair(1072004, CellInfo(OPTIONAL, NOCOLOR, "圣任德芬及同伴殉道(St. Leo Ignatius Mangin and Companions)", chineseLang)));
        // 21日
        mapPropers.insert(std::make_pair(1072101, CellInfo(OPTIONAL, NOCOLOR, "圣老楞佐•炳德西(St. Laurence of Brindisi)")));
        mapPropers.insert(std::make_pair(1072102, CellInfo(OPTIONAL, NOCOLOR, "圣郭西德", chineseLang)));
        mapPropers.insert(std::make_pair(1072201, CellInfo(FEAST, WHITE, "圣玛利亚•玛达肋纳(St. Mary Magdalen)")));
        mapPropers.insert(std::make_pair(1072202, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•巴勒斯坦(St. Joseph of Palestine)", disableLang)));
        mapPropers.insert(std::make_pair(1072301, CellInfo(OPTIONAL, NOCOLOR, "圣彼利日大(St. Bridget)")));
        mapPropers.insert(std::make_pair(1072401, CellInfo(OPTIONAL, NOCOLOR, "圣方济各•沙拉纳(St. Francis Salasno)", disableLang)));
        mapPropers.insert(std::make_pair(1072402, CellInfo(OPTIONAL, NOCOLOR, "圣克利斯蒂娜(St. Christina the Astonishing)")));
        mapPropers.insert(std::make_pair(1072403, CellInfo(OPTIONAL, NOCOLOR, "圣撒柏•麦禄福(St. Sharbel Makhluf)", disableLang)));
        mapPropers.insert(std::make_pair(1072501, CellInfo(FEAST, RED, "圣长雅各伯宗徒(St. James the Greater)")));
        mapPropers.insert(std::make_pair(1072502, CellInfo(OPTIONAL, NOCOLOR, "圣基多福(St. Christopher)")));
        // 26日
        mapPropers.insert(std::make_pair(1072601, CellInfo(MEMORIAL, WHITE, "圣妇亚纳及若亚敬(St. Anne & St. Joachim)")));
        mapPropers.insert(std::make_pair(1072602, CellInfo(OPTIONAL, NOCOLOR, "圣女亚加比大日(St. Bartholomea Capitanio)", disableLang)));
        mapPropers.insert(std::make_pair(1072701, CellInfo(OPTIONAL, NOCOLOR, "圣依诺增爵一世(St. Innocent I)")));
        mapPropers.insert(std::make_pair(1072702, CellInfo(OPTIONAL, NOCOLOR, "圣庞大良(St. Pantaleon)")));
        mapPropers.insert(std::make_pair(1072801, CellInfo(OPTIONAL, NOCOLOR, "真福亚尔丰索(Bd. Alphonsa Muttathupadathu)")));
        mapPropers.insert(std::make_pair(1072802, CellInfo(OPTIONAL, NOCOLOR, "圣陈昌品及同伴", chineseLang)));
        mapPropers.insert(std::make_pair(1072901, CellInfo(MEMORIAL, WHITE, "圣玛尔大、圣玛利亚及圣拉匝禄(St. Martha, Mary and Lazarus)")));
        mapPropers.insert(std::make_pair(1073001, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•金言(St. Peter Chrysologus)")));
        mapPropers.insert(std::make_pair(1073002, CellInfo(OPTIONAL, NOCOLOR, "真福伯多禄•玛格里诺(Bd. Peter of Mogliano)", disableLang)));
        mapPropers.insert(std::make_pair(1073101, CellInfo(MEMORIAL, WHITE, "圣依纳爵•罗耀拉(St. Ignatius of Loyola)")));
        mapPropers.insert(std::make_pair(1073102, CellInfo(OPTIONAL, NOCOLOR, "真福儒斯定(Bd. Justin de Jacobis)", disableLang)));

        /**************8月************/
        // 1日
        mapPropers.insert(std::make_pair(1080101, CellInfo(MEMORIAL, WHITE, "圣亚丰索(St. Alphonsus de Liguori)")));
        mapPropers.insert(std::make_pair(1080201, CellInfo(OPTIONAL, NOCOLOR, "圣欧瑟伯(St. Eusebius of Vencelli)")));
        mapPropers.insert(std::make_pair(1080301, CellInfo(OPTIONAL, NOCOLOR, "圣华旦(St. Waltheof)")));
        mapPropers.insert(std::make_pair(1080302, CellInfo(OPTIONAL, NOCOLOR, "真福伯多禄•儒里安•爱麦(Bd. Peter Julian Eymard)")));
        mapPropers.insert(std::make_pair(1080401, CellInfo(MEMORIAL, WHITE, "圣若翰•维雅纳(St. John Vianney)")));
        mapPropers.insert(std::make_pair(1080501, CellInfo(MEMORIAL, WHITE, "罗马圣母大殿奉献日(The Dedication of the Basilica of St. Mary Major)")));
        mapPropers.insert(std::make_pair(1080502, CellInfo(OPTIONAL, NOCOLOR, "圣亚勿拉(St. Afra)")));
        // 6日
        mapPropers.insert(std::make_pair(1080601, CellInfo(LORD, WHITE, "耶稣显圣容(The Transfiguration of Our Lord Jesus Christ)")));
        mapPropers.insert(std::make_pair(1080701, CellInfo(OPTIONAL, NOCOLOR, "圣西斯笃二世(St. Sixtus II)")));
        mapPropers.insert(std::make_pair(1080702, CellInfo(OPTIONAL, NOCOLOR, "圣加耶当(St. Cajetan)")));
        mapPropers.insert(std::make_pair(1080801, CellInfo(MEMORIAL, WHITE, "圣多明我(St. Dominic)")));
        mapPropers.insert(std::make_pair(1080901, CellInfo(OPTIONAL, NOCOLOR, "圣奥斯华(St. Oswald of Northumbria)")));
        mapPropers.insert(std::make_pair(1080902, CellInfo(OPTIONAL, NOCOLOR, "真福若望•沙肋诺(Bd. John of Salerno)", disableLang)));
        mapPropers.insert(std::make_pair(1081001, CellInfo(FEAST, RED, "圣老楞佐(St. Laurence)")));
        mapPropers.insert(std::make_pair(1081002, CellInfo(OPTIONAL, NOCOLOR, "圣女菲洛美娜(St. Philomena)")));
        // 11日
        mapPropers.insert(std::make_pair(1081101, CellInfo(MEMORIAL, WHITE, "圣女加辣(St. Clare)")));
        mapPropers.insert(std::make_pair(1081102, CellInfo(OPTIONAL, NOCOLOR, "真福伯多禄•法华(Bd. Peter Favre)")));
        mapPropers.insert(std::make_pair(1081201, CellInfo(OPTIONAL, NOCOLOR, "圣慕达(St. Murtagh)")));
        mapPropers.insert(std::make_pair(1081202, CellInfo(OPTIONAL, NOCOLOR, "圣方济加•尚达尔(St. Jane Frances de Chantal)")));
        mapPropers.insert(std::make_pair(1081301, CellInfo(OPTIONAL, NOCOLOR, "圣依玻里多和圣彭谦(Ss. Hippolytus and Ponlianus)")));
        mapPropers.insert(std::make_pair(1081302, CellInfo(OPTIONAL, NOCOLOR, "圣贝尼杜(St. Benildus)", disableLang)));
        mapPropers.insert(std::make_pair(1081401, CellInfo(OPTIONAL, NOCOLOR, "真福安多尼毕马田和伙伴(Bb. Antony Primaldi and other Martyrs)", disableLang)));
        mapPropers.insert(std::make_pair(1081402, CellInfo(MEMORIAL, RED, "圣国柏司铎(St. Maximilian Kolbe, Priest and Martyr)")));
        mapPropers.insert(std::make_pair(1081403, CellInfo(WEEKDAY, WHITE, "圣母升天节前夕")));
        mapPropers.insert(std::make_pair(1081501, CellInfo(SOLEMNITY, WHITE, "圣母升天节(The Assumption of the Blessed Virgin Mary)")));
        // 16日
        mapPropers.insert(std::make_pair(1081601, CellInfo(OPTIONAL, NOCOLOR, "圣斯德望（匈牙利）(St. Stephen of Hungary)")));
        mapPropers.insert(std::make_pair(1081602, CellInfo(OPTIONAL, NOCOLOR, "圣洛克(St. Rock)")));
        mapPropers.insert(std::make_pair(1081701, CellInfo(OPTIONAL, NOCOLOR, "圣雅钦多(St. Hyachinth)")));
        mapPropers.insert(std::make_pair(1081702, CellInfo(OPTIONAL, NOCOLOR, "真福若翰纳•德拉诺(Bd. Joan Delanoue)")));
        mapPropers.insert(std::make_pair(1081801, CellInfo(OPTIONAL, NOCOLOR, "圣海伦(St. Helen)")));
        mapPropers.insert(std::make_pair(1081802, CellInfo(OPTIONAL, NOCOLOR, "圣亚尔比(St. Alipius)")));
        mapPropers.insert(std::make_pair(1081803, CellInfo(OPTIONAL, NOCOLOR, "真福白亚蒂斯(Bd. Beatrice da Silva)", disableLang)));
        mapPropers.insert(std::make_pair(1081901, CellInfo(OPTIONAL, NOCOLOR, "圣若望•欧德(St. John Eudes)")));
        mapPropers.insert(std::make_pair(1081902, CellInfo(OPTIONAL, NOCOLOR, "圣路易•安日(St. Louis of Anjou)", disableLang)));
        mapPropers.insert(std::make_pair(1082001, CellInfo(MEMORIAL, WHITE, "圣伯尔纳铎(St. Bernard)")));
        mapPropers.insert(std::make_pair(1082002, CellInfo(OPTIONAL, NOCOLOR, "真福玛利亚•德玛帝亚(Bd. Mary of Mattias)", disableLang)));
        // 21日
        mapPropers.insert(std::make_pair(1082101, CellInfo(MEMORIAL, WHITE, "圣比约十世(教宗 St. Pius X)")));
        mapPropers.insert(std::make_pair(1082201, CellInfo(MEMORIAL, WHITE, "圣母元后(The Queenship of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1082202, CellInfo(OPTIONAL, NOCOLOR, "真福奥撒南(Bd. Ozanet)", disableLang)));
        mapPropers.insert(std::make_pair(1082301, CellInfo(OPTIONAL, NOCOLOR, "圣女罗撒（利马）(St. Rose of Lima)")));
        mapPropers.insert(std::make_pair(1082302, CellInfo(OPTIONAL, NOCOLOR, "圣斐理伯•贝尼谛(St. Philip Benizi)")));
        mapPropers.insert(std::make_pair(1082303, CellInfo(OPTIONAL, NOCOLOR, "圣高洛巨及其同班(Ss. Claudius, Asterius, Neon, Domnina and Theonilla)", disableLang)));
        mapPropers.insert(std::make_pair(1082401, CellInfo(FEAST, RED, "圣巴尔多禄茂(St. Bartholomew)")));
        mapPropers.insert(std::make_pair(1082501, CellInfo(OPTIONAL, NOCOLOR, "圣路易(St. Louis of France)")));
        mapPropers.insert(std::make_pair(1082502, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•加拉桑(St. Joseph Calasanz)")));
        mapPropers.insert(std::make_pair(1082503, CellInfo(OPTIONAL, NOCOLOR, "圣女玛利亚•弥额拉•谭马西(St. Mary Michaela Desmanisieres)", disableLang)));
        // 26日
        mapPropers.insert(std::make_pair(1082601, CellInfo(OPTIONAL, NOCOLOR, "圣女依撒伯尔•皮希亚(St. Elizabeth Bichier des Ages)")));
        mapPropers.insert(std::make_pair(1082701, CellInfo(MEMORIAL, WHITE, "圣莫尼加(St. Monica)")));
        mapPropers.insert(std::make_pair(1082801, CellInfo(MEMORIAL, WHITE, "圣奥斯定(St. Augustinei of Hippo)")));
        mapPropers.insert(std::make_pair(1082901, CellInfo(MEMORIAL, RED, "圣若翰洗者蒙难(The Beheading of St. John the Baptist)")));
        mapPropers.insert(std::make_pair(1083001, CellInfo(OPTIONAL, NOCOLOR, "圣斐理、圣亚祷多(Ss. Felix and Adauctus)")));
        mapPropers.insert(std::make_pair(1083101, CellInfo(OPTIONAL, NOCOLOR, "圣赖孟多•农纳都(St. Raymund Nonnatus)")));
        mapPropers.insert(std::make_pair(1083102, CellInfo(OPTIONAL, NOCOLOR, "真福儒万纳•安西诺(Bd. Juvenal Ancina)", disableLang)));

        /***************9月*****************/
        // 1日
        mapPropers.insert(std::make_pair(1090101, CellInfo(OPTIONAL, NOCOLOR, "圣祺肋(St. Giles)")));
        mapPropers.insert(std::make_pair(1090102, CellInfo(OPTIONAL, NOCOLOR, "圣旦利塞(St. Drithelm)", disableLang)));
        mapPropers.insert(std::make_pair(1090103, CellInfo(MEMORIAL, NOCOLOR, "照料受造界日")));
        mapPropers.insert(std::make_pair(1090201, CellInfo(OPTIONAL, NOCOLOR, "圣威廉(St. William of Rokide)")));
        mapPropers.insert(std::make_pair(1090202, CellInfo(OPTIONAL, NOCOLOR, "真福若望狄洛及其他殉道烈士(Bd. John du Lau and his Companions)")));
        mapPropers.insert(std::make_pair(1090301, CellInfo(MEMORIAL, WHITE, "圣额我略一世(St. Gregory the Great)")));
        mapPropers.insert(std::make_pair(1090302, CellInfo(OPTIONAL, NOCOLOR, "圣小西默盎“石柱人”(St. Simeon Stylite the Younger)", disableLang)));
        mapPropers.insert(std::make_pair(1090401, CellInfo(OPTIONAL, NOCOLOR, "圣女罗撒•薇台宝(St. Rose of Viterbo)")));
        mapPropers.insert(std::make_pair(1090402, CellInfo(OPTIONAL, NOCOLOR, "真福加大利纳•拉谷尼(Bd. Catherine of Racconigi)", disableLang)));
        mapPropers.insert(std::make_pair(1090501, CellInfo(OPTIONAL, NOCOLOR, "圣老楞佐•儒斯定(St. Laurence Giustiniani)", disableLang)));
        mapPropers.insert(std::make_pair(1090502, CellInfo(MEMORIAL, WHITE, "圣德肋撒（加尔各答）(St. Teresa of Calcutta)")));
        // 6日
        mapPropers.insert(std::make_pair(1090601, CellInfo(OPTIONAL, NOCOLOR, "圣爱琉德理(St. Eleutherius)")));
        mapPropers.insert(std::make_pair(1090602, CellInfo(OPTIONAL, NOCOLOR, "真福贝脱郎(Bd. Bertrand of Garrigues)", disableLang)));
        mapPropers.insert(std::make_pair(1090701, CellInfo(OPTIONAL, NOCOLOR, "圣克罗德(St. Cloud)")));
        mapPropers.insert(std::make_pair(1090702, CellInfo(OPTIONAL, NOCOLOR, "真福若望•德盖、赖夫•高比(Bb. John Duckett and Ralph Corby)")));
        mapPropers.insert(std::make_pair(1090801, CellInfo(FEAST, WHITE, "圣母诞辰(The Birthday of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1090802, CellInfo(OPTIONAL, NOCOLOR, "圣塞尔久一世(St. Sergius I)", disableLang)));
        mapPropers.insert(std::make_pair(1090901, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•格肋凡(St. Peter Claver)")));
        mapPropers.insert(std::make_pair(1090902, CellInfo(OPTIONAL, NOCOLOR, "圣依撒格(St. Isaac the Great)", disableLang)));
        mapPropers.insert(std::make_pair(1091001, CellInfo(OPTIONAL, NOCOLOR, "圣尼各老•多伦定(St. Nicholas of Tolentino)")));
        // 11日
        mapPropers.insert(std::make_pair(1091101, CellInfo(OPTIONAL, NOCOLOR, "圣普罗多、圣雅钦多(Ss. Prtcals & Hvacinth)", disableLang)));
        mapPropers.insert(std::make_pair(1091102, CellInfo(OPTIONAL, NOCOLOR, "圣彭诺许(St. Paphnutius)")));
        mapPropers.insert(std::make_pair(1091103, CellInfo(OPTIONAL, NOCOLOR, "圣董文学", chineseLang)));
        mapPropers.insert(std::make_pair(1091201, CellInfo(MEMORIAL, WHITE, "圣母圣名(The Holy Name of Mary)")));
        mapPropers.insert(std::make_pair(1091202, CellInfo(OPTIONAL, NOCOLOR, "圣祁•安德烈(St. Guy of Anderlecht)", disableLang)));
        mapPropers.insert(std::make_pair(1091301, CellInfo(MEMORIAL, WHITE, "金口圣若望(St. John Chrysostom)")));
        mapPropers.insert(std::make_pair(1091302, CellInfo(OPTIONAL, NOCOLOR, "圣欧洛日(St. Eulogius of Alexandlia)", disableLang)));
        mapPropers.insert(std::make_pair(1091401, CellInfo(LORD, RED, "光荣十字圣架(The Exaltation of the Holy Cross)")));
        mapPropers.insert(std::make_pair(1091402, CellInfo(OPTIONAL, NOCOLOR, "圣女诺波加(St. Notburga)", disableLang)));
        mapPropers.insert(std::make_pair(1091501, CellInfo(MEMORIAL, WHITE, "痛苦圣母(Our Lady of Sorrows)")));
        mapPropers.insert(std::make_pair(1091502, CellInfo(OPTIONAL, NOCOLOR, "圣加大利纳•热那亚(St. Catherine of Genoa)")));
        // 16日
        mapPropers.insert(std::make_pair(1091601, CellInfo(MEMORIAL, RED, "圣高尔内略及圣西彼廉主教(St. Cornelius & St. Cyprian)")));
        mapPropers.insert(std::make_pair(1091701, CellInfo(OPTIONAL, NOCOLOR, "圣罗伯多•贝辣民(St. Robert Bellarmine)")));
        mapPropers.insert(std::make_pair(1091702, CellInfo(OPTIONAL, NOCOLOR, "圣方济各受五伤痕(The Stigmata of St. Francis)")));
        mapPropers.insert(std::make_pair(1091703, CellInfo(OPTIONAL, NOCOLOR, "圣贺德佳•碧根(St. Robert Bellarmine)", disableLang)));
        mapPropers.insert(std::make_pair(1091801, CellInfo(OPTIONAL, NOCOLOR, "圣若瑟•古白定(St. Joseph of Cupertino)")));
        mapPropers.insert(std::make_pair(1091901, CellInfo(OPTIONAL, NOCOLOR, "圣雅纳略主教及其他殉道烈士(Ss. Januarius and his Companions)")));
        mapPropers.insert(std::make_pair(1092001, CellInfo(OPTIONAL, NOCOLOR, "圣刁多禄(St. Theodore)", disableLang)));
        mapPropers.insert(std::make_pair(1092002, CellInfo(OPTIONAL, NOCOLOR, "圣爱弥理(St. Emily de Rodat)")));
        mapPropers.insert(std::make_pair(1092003, CellInfo(MEMORIAL, RED, "圣金大建及同伴殉道(Ss. Andrew Kim Taegon and Companions)")));
        // 21日
        mapPropers.insert(std::make_pair(1092101, CellInfo(FEAST, RED, "圣玛窦(St. Matthew)")));
        mapPropers.insert(std::make_pair(1092201, CellInfo(OPTIONAL, NOCOLOR, "圣多默•威拉诺(St. Thomas of Villanova)")));
        mapPropers.insert(std::make_pair(1092301, CellInfo(OPTIONAL, NOCOLOR, "圣理诺(St. Linus)", disableLang)));
        mapPropers.insert(std::make_pair(1092302, CellInfo(OPTIONAL, NOCOLOR, "圣女德格拉(St. Thecla of Iconium)", disableLang)));
        mapPropers.insert(std::make_pair(1092303, CellInfo(MEMORIAL, WHITE, "圣比约•庇特來(St. Pio of Pietrelcina.)")));
        mapPropers.insert(std::make_pair(1092401, CellInfo(OPTIONAL, NOCOLOR, "圣母赎虏(Our Lady of Ransom)")));
        mapPropers.insert(std::make_pair(1092402, CellInfo(OPTIONAL, NOCOLOR, "圣吉拉(St. Gerard of Sagredo)")));
        mapPropers.insert(std::make_pair(1092501, CellInfo(OPTIONAL, NOCOLOR, "圣西弗里(St. Ceolfrid)", disableLang)));
        mapPropers.insert(std::make_pair(1092502, CellInfo(OPTIONAL, NOCOLOR, "圣亚尔伯(St. Albert of Jerusalem)")));
        // 26日
        mapPropers.insert(std::make_pair(1092601, CellInfo(OPTIONAL, NOCOLOR, "圣葛斯默、圣达弥盎(Ss. Cosmas and Damian)")));
        mapPropers.insert(std::make_pair(1092701, CellInfo(OPTIONAL, NOCOLOR, "圣爱徐亚(St. Eleazar de Sabran)", disableLang)));
        mapPropers.insert(std::make_pair(1092702, CellInfo(MEMORIAL, WHITE, "圣味增爵(St. Vincent De Paul)")));
        mapPropers.insert(std::make_pair(1092801, CellInfo(OPTIONAL, NOCOLOR, "圣文策老(St. Wenceslaus)")));
        mapPropers.insert(std::make_pair(1092802, CellInfo(OPTIONAL, NOCOLOR, "圣女欧多钦(St. Eustochium)", disableLang)));
        mapPropers.insert(std::make_pair(1092901, CellInfo(FEAST, WHITE, "诸圣天使")));
        mapPropers.insert(std::make_pair(1093001, CellInfo(MEMORIAL, WHITE, "圣热罗尼莫(St. Jerome)")));

        /***************10月**************/
        // 1日
        mapPropers.insert(std::make_pair(1100101, CellInfo(MEMORIAL, WHITE, "圣女婴孩耶稣德肋撒(St. Terese of Licieux)")));
        mapPropers.insert(std::make_pair(1100201, CellInfo(MEMORIAL, WHITE, "护守天使(The Guardian Angels)")));
        mapPropers.insert(std::make_pair(1100301, CellInfo(OPTIONAL, NOCOLOR, "依华昆仲(The Two Ewalds)")));
        mapPropers.insert(std::make_pair(1100401, CellInfo(MEMORIAL, WHITE, "圣五伤方济各(St. Francis Assisi)")));
        mapPropers.insert(std::make_pair(1100501, CellInfo(MEMORIAL, WHITE, "圣女傅天娜(St. Faustina)")));
        mapPropers.insert(std::make_pair(1100502, CellInfo(OPTIONAL, NOCOLOR, "圣布拉祺多(St. Placid)", disableLang)));
        mapPropers.insert(std::make_pair(1100503, CellInfo(OPTIONAL, NOCOLOR, "圣女福辣(St. Flora of Beaulien)", disableLang)));
        // 6日
        mapPropers.insert(std::make_pair(1100601, CellInfo(OPTIONAL, NOCOLOR, "圣勃路诺(St. Bruno)")));
        mapPropers.insert(std::make_pair(1100602, CellInfo(OPTIONAL, NOCOLOR, "圣女玛利亚•方济加(St. Mary Francesd Naples)")));
        mapPropers.insert(std::make_pair(1100701, CellInfo(MEMORIAL, WHITE, "玫瑰圣母(Our Lady's Rosary)")));
        mapPropers.insert(std::make_pair(1100801, CellInfo(OPTIONAL, NOCOLOR, "圣塞尔久、圣伯古斯(Ss. Sergius and Bacchus)", disableLang)));
        mapPropers.insert(std::make_pair(1100802, CellInfo(OPTIONAL, NOCOLOR, "圣女白兰佳(St. Pelagia the Penitent)")));
        mapPropers.insert(std::make_pair(1100901, CellInfo(OPTIONAL, NOCOLOR, "圣迪奥尼削及同伴(Ss. Denis, Rusticus & Eleutherius)")));
        mapPropers.insert(std::make_pair(1100902, CellInfo(OPTIONAL, NOCOLOR, "圣若望•良纳弟(St. John Leonardi)")));
        mapPropers.insert(std::make_pair(1100903, CellInfo(OPTIONAL, NOCOLOR, "圣若望•亨利•纽曼(St. John Henry Newman)")));
        mapPropers.insert(std::make_pair(1101001, CellInfo(OPTIONAL, NOCOLOR, "圣方济各•玻尔日亚(St. Francis Borgia)")));
        // 11日
        mapPropers.insert(std::make_pair(1101101, CellInfo(OPTIONAL, NOCOLOR, "圣加尼斯(St. Canice)", disableLang)));
        mapPropers.insert(std::make_pair(1101102, CellInfo(MEMORIAL, NOCOLOR, "圣若望二十三世(St. John XXIII)")));
        mapPropers.insert(std::make_pair(1101201, CellInfo(OPTIONAL, NOCOLOR, "圣威弗烈(St. Wilfrid)")));
        mapPropers.insert(std::make_pair(1101202, CellInfo(OPTIONAL, NOCOLOR, "圣卡洛·阿库蒂斯(St. Carlo Acutis)")));
        mapPropers.insert(std::make_pair(1101301, CellInfo(OPTIONAL, NOCOLOR, "圣爱德华(St. Edward Confessor)")));
        mapPropers.insert(std::make_pair(1101401, CellInfo(OPTIONAL, NOCOLOR, "圣加理多一世(St. Callistus I)")));
        mapPropers.insert(std::make_pair(1101501, CellInfo(MEMORIAL, WHITE, "圣女大德肋撒(St. Teresa of Avila)")));
        // 16日
        mapPropers.insert(std::make_pair(1101601, CellInfo(OPTIONAL, NOCOLOR, "圣赫德维(St. Hedwig)")));
        mapPropers.insert(std::make_pair(1101602, CellInfo(OPTIONAL, NOCOLOR, "圣玛加利大•亚拉高(St. Margaret Mary Alacoque)")));
        mapPropers.insert(std::make_pair(1101701, CellInfo(MEMORIAL, RED, "圣依纳爵•安提约基亚(St. Ignatius of Antioch)")));
        mapPropers.insert(std::make_pair(1101801, CellInfo(FEAST, RED, "圣史路加(St. Luke)")));
        mapPropers.insert(std::make_pair(1101901, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•亚刚大辣(St. Peter of Alcantara)", disableLang)));
        mapPropers.insert(std::make_pair(1101902, CellInfo(OPTIONAL, NOCOLOR, "北美洲殉道烈士(The Martyrs of North America)", disableLang)));
        mapPropers.insert(std::make_pair(1101903, CellInfo(OPTIONAL, NOCOLOR, "十字圣保禄(St. Paul of the Cross)")));
        mapPropers.insert(std::make_pair(1102001, CellInfo(OPTIONAL, NOCOLOR, "圣女贝蒂拉(St. Bertilla Boscardin)")));
        // 21日
        mapPropers.insert(std::make_pair(1102101, CellInfo(OPTIONAL, NOCOLOR, "圣依拉良(St. Hilarion)")));
        mapPropers.insert(std::make_pair(1102201, CellInfo(MEMORIAL, WHITE, "圣若望·保禄二世(St. John Paul II)")));
        mapPropers.insert(std::make_pair(1102202, CellInfo(OPTIONAL, NOCOLOR, "真福弟茂德•奇嘉多(Bd. Timothy Giocarde)", disableLang)));
        mapPropers.insert(std::make_pair(1102301, CellInfo(OPTIONAL, NOCOLOR, "圣若望•嘉庇当(St. John of Capistrano)")));
        mapPropers.insert(std::make_pair(1102401, CellInfo(OPTIONAL, NOCOLOR, "圣安多尼•加烈(St. Antony Claret)")));
        mapPropers.insert(std::make_pair(1102501, CellInfo(OPTIONAL, NOCOLOR, "圣克利斯品、圣克利斯毕(Ss. Crispin and Crispinian)")));
        // 26日
        mapPropers.insert(std::make_pair(1102601, CellInfo(OPTIONAL, NOCOLOR, "圣厄瓦理斯多(St. Evaristus)")));
        mapPropers.insert(std::make_pair(1102701, CellInfo(OPTIONAL, NOCOLOR, "圣福门舒(St. Frumentius)")));
        mapPropers.insert(std::make_pair(1102702, CellInfo(OPTIONAL, NOCOLOR, "真福费列尼(Bd. Contardo Ferrini)", disableLang)));
        mapPropers.insert(std::make_pair(1102703, CellInfo(OPTIONAL, NOCOLOR, "圣施方济及同伴", chineseLang)));
        mapPropers.insert(std::make_pair(1102801, CellInfo(FEAST, RED, "圣西满、圣达陡(Ss. Simon and Jude)")));
        mapPropers.insert(std::make_pair(1102901, CellInfo(OPTIONAL, NOCOLOR, "圣南西苏(St. Narcissus of Jerusalem)")));
        mapPropers.insert(std::make_pair(1103001, CellInfo(OPTIONAL, NOCOLOR, "圣玛塞洛(St. Marcellus the Cenlurion)", disableLang)));
        mapPropers.insert(std::make_pair(1103002, CellInfo(OPTIONAL, NOCOLOR, "真福安日洛(Bd. Angeto of Acri)")));
        mapPropers.insert(std::make_pair(1103101, CellInfo(OPTIONAL, NOCOLOR, "圣亚方沙•罗德利(St. Alphonsus Rodriguez)")));

        /**************11月**************/
        // 1日
        mapPropers.insert(std::make_pair(1110101, CellInfo(SOLEMNITY, WHITE, "诸圣节(All Saints)")));
        mapPropers.insert(std::make_pair(1110201, CellInfo(LORD, PURPLE, "追思亡者(All Souls)")));
        mapPropers.insert(std::make_pair(1110301, CellInfo(OPTIONAL, NOCOLOR, "圣玛尔定•包瑞斯(St. Martin de Porres)")));
        mapPropers.insert(std::make_pair(1110401, CellInfo(MEMORIAL, WHITE, "圣嘉禄(St. Charles Borromeo)")));
        mapPropers.insert(std::make_pair(1110501, CellInfo(OPTIONAL, NOCOLOR, "圣女伯蒂拉(St. Betrilla)")));
        // 6日
        mapPropers.insert(std::make_pair(1110601, CellInfo(MEMORIAL, RED, "越南第二批殉道烈士(The Martyrs of Indo-China, II)")));
        mapPropers.insert(std::make_pair(1110602, CellInfo(OPTIONAL, NOCOLOR, "圣良纳弟(St. Leonard of Noblac)", disableLang)));
        mapPropers.insert(std::make_pair(1110701, CellInfo(OPTIONAL, NOCOLOR, "圣威利巴(St. Willbrord)")));
        mapPropers.insert(std::make_pair(1110702, CellInfo(OPTIONAL, NOCOLOR, "真福安多尼•白田诺西(Bd. Antony Baldinucci)", disableLang)));
        mapPropers.insert(std::make_pair(1110801, CellInfo(OPTIONAL, NOCOLOR, "圣高弗烈(St. Godfrey)")));
        mapPropers.insert(std::make_pair(1110802, CellInfo(OPTIONAL, NOCOLOR, "真福若望·董思高(Bd. John Duns Scott)")));
        mapPropers.insert(std::make_pair(1110901, CellInfo(LORD, WHITE, "拉特朗大殿奉献日(The Dedication of the Lateran Basilica)")));
        mapPropers.insert(std::make_pair(1111001, CellInfo(MEMORIAL, WHITE, "圣良一世(教宗 St. Leo the Great)")));
        mapPropers.insert(std::make_pair(1111002, CellInfo(OPTIONAL, NOCOLOR, "圣安德肋•亚委琳(St. Andrew Avellino)", disableLang)));
        // 11日
        mapPropers.insert(std::make_pair(1111101, CellInfo(MEMORIAL, WHITE, "圣玛尔定(St. Martin of Tours)")));
        mapPropers.insert(std::make_pair(1111102, CellInfo(OPTIONAL, NOCOLOR, "圣刁多禄(St. Theodore the Studite)", disableLang)));
        mapPropers.insert(std::make_pair(1111201, CellInfo(MEMORIAL, RED, "圣若撒法(St. Joaphat of Polotsk)")));
        mapPropers.insert(std::make_pair(1111301, CellInfo(OPTIONAL, NOCOLOR, "圣达尼老•各斯加(St. Stanislaus Kostka)")));
        mapPropers.insert(std::make_pair(1111401, CellInfo(OPTIONAL, NOCOLOR, "圣老楞佐•奥多(St. Laurence O'Toole)")));
        mapPropers.insert(std::make_pair(1111501, CellInfo(OPTIONAL, NOCOLOR, "圣大亚尔伯(St. Albert the Great)")));
        mapPropers.insert(std::make_pair(1111502, CellInfo(OPTIONAL, NOCOLOR, "真福痛苦玛利亚修女(Bl. Mary of the Passion)", disableLang)));
        // 16日
        mapPropers.insert(std::make_pair(1111601, CellInfo(OPTIONAL, NOCOLOR, "圣玛加利大(St. Margaret of Scotland)")));
        mapPropers.insert(std::make_pair(1111602, CellInfo(OPTIONAL, NOCOLOR, "圣女日多达(St. Getrude)")));
        mapPropers.insert(std::make_pair(1111603, CellInfo(OPTIONAL, NOCOLOR, "圣爱德门(St. Edmund of Abingdon)", disableLang)));
        mapPropers.insert(std::make_pair(1111701, CellInfo(MEMORIAL, WHITE, "圣依撒伯尔(St. Elizabeth of Hungary)")));
        mapPropers.insert(std::make_pair(1111801, CellInfo(MEMORIAL, WHITE, "圣伯多禄圣保禄大殿奉献日(The Dedication of the Basilicas of St. Peter and of St. Paul)")));
        mapPropers.insert(std::make_pair(1111901, CellInfo(OPTIONAL, NOCOLOR, "圣额我略“显灵迹者”(St. Gregory the Wonderworker)", disableLang)));
        mapPropers.insert(std::make_pair(1111902, CellInfo(OPTIONAL, NOCOLOR, "圣狄尼削(St. Dionysius of Alexandria)")));
        mapPropers.insert(std::make_pair(1112001, CellInfo(OPTIONAL, NOCOLOR, "圣斐理斯•瓦洛亚(St. Felix of Valois)")));
        // 21日
        mapPropers.insert(std::make_pair(1112101, CellInfo(MEMORIAL, WHITE, "圣母奉献日(The Presentation of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1112201, CellInfo(MEMORIAL, RED, "圣女则济利亚(St. Cecilia)")));
        mapPropers.insert(std::make_pair(1112301, CellInfo(OPTIONAL, NOCOLOR, "圣格肋孟一世(St. Clement I)")));
        mapPropers.insert(std::make_pair(1112302, CellInfo(OPTIONAL, NOCOLOR, "圣高隆庞(St. Columban)")));
        mapPropers.insert(std::make_pair(1112401, CellInfo(MEMORIAL, RED, "圣陈安勇乐司铎及同伴")));
        mapPropers.insert(std::make_pair(1112402, CellInfo(OPTIONAL, NOCOLOR, "圣徐德新(St. Ioannes Dufresse)", chineseLang)));
        mapPropers.insert(std::make_pair(1112501, CellInfo(OPTIONAL, NOCOLOR, "圣加斯伯(St. Caspar Del Bufalo)", disableLang)));
        mapPropers.insert(std::make_pair(1112502, CellInfo(OPTIONAL, NOCOLOR, "圣若望•伯尔各满(St. John Berchmans)", disableLang)));
        mapPropers.insert(std::make_pair(1112503, CellInfo(OPTIONAL, NOCOLOR, "圣加大利纳•亚力山卓(St. Catherine of Alexandria)")));
        // 26日
        mapPropers.insert(std::make_pair(1112601, CellInfo(OPTIONAL, NOCOLOR, "圣良纳(St. Leonard of Port Mauriee)")));
        mapPropers.insert(std::make_pair(1112701, CellInfo(OPTIONAL, NOCOLOR, "圣维琪尔(St. Virgil of Salzburg)")));
        mapPropers.insert(std::make_pair(1112801, CellInfo(OPTIONAL, NOCOLOR, "圣女加大利纳•拉布莱(St. Catherine Laboure)")));
        mapPropers.insert(std::make_pair(1112901, CellInfo(OPTIONAL, NOCOLOR, "圣小斯德望(St. Stephen the Younger)")));
        mapPropers.insert(std::make_pair(1112902, CellInfo(OPTIONAL, NOCOLOR, "圣胡伯(St. Hubert)", disableLang)));
        mapPropers.insert(std::make_pair(1112903, CellInfo(OPTIONAL, NOCOLOR, "圣刘瑞廷", chineseLang)));
        mapPropers.insert(std::make_pair(1113001, CellInfo(FEAST, RED, "圣安德肋(St. Andrew the Apostle)")));

        /*******************12月*****************/
        // 1日
        mapPropers.insert(std::make_pair(1120101, CellInfo(OPTIONAL, NOCOLOR, "圣安利日(St. Eligius)")));
        mapPropers.insert(std::make_pair(1120102, CellInfo(OPTIONAL, NOCOLOR, "真福爱德门•江本(Bd. Edmund Campion)", disableLang)));
        mapPropers.insert(std::make_pair(1120201, CellInfo(OPTIONAL, NOCOLOR, "圣女彼彼亚纳(St. Bibiana)")));
        mapPropers.insert(std::make_pair(1120301, CellInfo(MEMORIAL, WHITE, "圣方济各•沙勿略(St. Francis Xavier)")));
        mapPropers.insert(std::make_pair(1120401, CellInfo(OPTIONAL, NOCOLOR, "圣若望•达玛森(St. John Damascene)")));
        mapPropers.insert(std::make_pair(1120501, CellInfo(OPTIONAL, NOCOLOR, "圣撒巴(St. Sabas)")));
        // 6日
        mapPropers.insert(std::make_pair(1120601, CellInfo(OPTIONAL, NOCOLOR, "圣尼各老(St. Nicholas of Myra)")));
        mapPropers.insert(std::make_pair(1120701, CellInfo(MEMORIAL, WHITE, "圣盎博罗削(St. Ambrose)")));
        mapPropers.insert(std::make_pair(1120702, CellInfo(OPTIONAL, NOCOLOR, "圣女若撒法•罗撒洛(St. Josepha ROssello)", disableLang)));
        mapPropers.insert(std::make_pair(1120801, CellInfo(FEAST, WHITE, "圣母无原罪始胎(The Immaculate Conception of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1120901, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•傅雷(St. Peter Fourier)")));
        mapPropers.insert(std::make_pair(1120902, CellInfo(OPTIONAL, NOCOLOR, "圣若望•迪达谷(St. Juan Diego Cuauhtlatoatzin)", disableLang)));
        mapPropers.insert(std::make_pair(1121001, CellInfo(MEMORIAL, WHITE, "洛雷托圣母"))); // 我灵赞颂主有
        mapPropers.insert(std::make_pair(1121002, CellInfo(OPTIONAL, NOCOLOR, "圣米济亚德(St. Miltiades)", disableLang)));
        // 11日
        mapPropers.insert(std::make_pair(1121101, CellInfo(OPTIONAL, NOCOLOR, "圣达玛稣一世(St. Damasus)")));
        mapPropers.insert(std::make_pair(1121201, CellInfo(FEAST, WHITE, "瓜达卢佩圣母(Our Lady of Guadalupe)")));
        mapPropers.insert(std::make_pair(1121202, CellInfo(OPTIONAL, NOCOLOR, "圣若翰纳•方济加•尚达尔(St. Jane Frances de Chantal)")));
        mapPropers.insert(std::make_pair(1121301, CellInfo(MEMORIAL, RED, "圣女路济亚(St. Lucy)")));
        mapPropers.insert(std::make_pair(1121401, CellInfo(MEMORIAL, WHITE, "圣若望“由十字架者”(St. John of the Cross)")));
        mapPropers.insert(std::make_pair(1121402, CellInfo(OPTIONAL, NOCOLOR, "圣史比利廷(St. Spiridion)", disableLang)));
        mapPropers.insert(std::make_pair(1121501, CellInfo(OPTIONAL, NOCOLOR, "圣万南修•福多诺(St. Venantius Fotunatus)", disableLang)));
        mapPropers.insert(std::make_pair(1121502, CellInfo(OPTIONAL, NOCOLOR, "圣女尼诺(St. Nino)")));
        mapPropers.insert(std::make_pair(1121503, CellInfo(OPTIONAL, NOCOLOR, "圣女玛利亚•罗撒(St. Mary di Rosa)")));
        // 16日
        mapPropers.insert(std::make_pair(1121601, CellInfo(OPTIONAL, NOCOLOR, "圣亚德莱(St. Adelaide)")));
        mapPropers.insert(std::make_pair(1121701, CellInfo(MEMORIAL, NOCOLOR, "圣拉匝禄(St. Lazarus)")));
        mapPropers.insert(std::make_pair(1121702, CellInfo(OPTIONAL, NOCOLOR, "圣妇奥林比亚(St. Olympias)")));
        mapPropers.insert(std::make_pair(1121703, CellInfo(MEMORIAL, PURPLE, "将临期 12月17日")));
        mapPropers.insert(std::make_pair(1121801, CellInfo(OPTIONAL, NOCOLOR, "圣威纳巴(St. Wunibald)")));
        mapPropers.insert(std::make_pair(1121802, CellInfo(OPTIONAL, NOCOLOR, "圣斯多米(St. Sturmi)", disableLang)));
        mapPropers.insert(std::make_pair(1121803, CellInfo(MEMORIAL, PURPLE, "将临期 12月18日")));
        mapPropers.insert(std::make_pair(1121901, CellInfo(OPTIONAL, NOCOLOR, "圣南米修及其他殉道烈士(Ss. Nemesius and other Martyrs)")));
        mapPropers.insert(std::make_pair(1121902, CellInfo(MEMORIAL, PURPLE, "将临期 12月19日")));
        mapPropers.insert(std::make_pair(1122001, CellInfo(OPTIONAL, NOCOLOR, "圣多明我•西洛(St. Dominic of Silos)")));
        mapPropers.insert(std::make_pair(1122002, CellInfo(MEMORIAL, PURPLE, "将临期 12月20日")));
        // 21日
        mapPropers.insert(std::make_pair(1122101, CellInfo(OPTIONAL, NOCOLOR, "圣伯多禄•加尼削(St. Peter Canisius)")));
        mapPropers.insert(std::make_pair(1122102, CellInfo(MEMORIAL, PURPLE, "将临期 12月21日")));
        mapPropers.insert(std::make_pair(1122201, CellInfo(OPTIONAL, NOCOLOR, "圣女方济加(St. Frances Xavier Cabrini)")));
        mapPropers.insert(std::make_pair(1122202, CellInfo(MEMORIAL, PURPLE, "将临期 12月22日")));
        mapPropers.insert(std::make_pair(1122301, CellInfo(OPTIONAL, NOCOLOR, "圣若望根地(St. John of Kanti)")));
        mapPropers.insert(std::make_pair(1122302, CellInfo(MEMORIAL, PURPLE, "将临期 12月23日")));
        mapPropers.insert(std::make_pair(1122401, CellInfo(SOLEMNITY, WHITE, "耶稣圣诞节望日")));
        mapPropers.insert(std::make_pair(1122501, CellInfo(SOLEMNITY, WHITE, "耶稣圣诞(The Birthday of Our Lord Jesus Christ)")));
        // 26日
        mapPropers.insert(std::make_pair(1122601, CellInfo(FEAST, RED, "圣斯德望(首位殉道 St. Stephen)")));
        mapPropers.insert(std::make_pair(1122602, CellInfo(OPTIONAL, NOCOLOR, "真福味增济亚(Bd. Vincentia)", disableLang)));
        mapPropers.insert(std::make_pair(1122701, CellInfo(FEAST, WHITE, "圣若望(St. John the Evangelist)")));
        mapPropers.insert(std::make_pair(1122801, CellInfo(FEAST, RED, "诸圣婴孩(The Holy Innocents)")));
        mapPropers.insert(std::make_pair(1122901, CellInfo(OPTIONAL, NOCOLOR, "圣多默•贝凯(St. Thomas Becket)")));
        mapPropers.insert(std::make_pair(1122902, CellInfo(LORD, WHITE, "圣诞节庆期第五日")));
        mapPropers.insert(std::make_pair(1123001, CellInfo(OPTIONAL, NOCOLOR, "圣撒比诺等殉道者(Ss. Sabinus and his Companions)")));
        mapPropers.insert(std::make_pair(1123002, CellInfo(LORD, WHITE, "圣诞节庆期第六日")));
        mapPropers.insert(std::make_pair(1123101, CellInfo(OPTIONAL, NOCOLOR, "圣西尔物斯德肋(St. Silvestes)")));
        mapPropers.insert(std::make_pair(1123102, CellInfo(OPTIONAL, NOCOLOR, "圣幼梅肋尼亚(St. Melania the Younger)", disableLang)));
        mapPropers.insert(std::make_pair(1123103, CellInfo(LORD, WHITE, "圣诞节庆期第七日")));
    }

    /*
    // 由礼仪年确定的特殊节日
    // 规则：采用十进制（共六位）
    // 前面两位为：Season
    // 中间两位为：主日编号
    // 最后两位为：星期几
    */
    {
        // 常年期
        mapPropers.insert(std::make_pair(ORDINARY * 10000 + 300 + 0, CellInfo(SUNDAY, GREEN, "常年期第三主日(圣言主日)")));
        // 四旬期第0主日星期三（圣灰礼仪）
        mapPropers.insert(std::make_pair(LENT * 10000 + 3, CellInfo(ASHWED, PURPLE, "圣灰礼仪")));
        // 四旬期第六主日（圣周）
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 0, CellInfo(HOLYWEEK, RED, "圣枝主日(基督苦难主日)")));
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 1, CellInfo(HOLYWEEK, PURPLE, "圣周一")));
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 2, CellInfo(HOLYWEEK, PURPLE, "圣周二")));
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 3, CellInfo(HOLYWEEK, PURPLE, "圣周三")));
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 4, CellInfo(TRIDUUM, WHITE, "主的晚餐")));
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 5, CellInfo(TRIDUUM, RED, "耶稣受难")));
        mapPropers.insert(std::make_pair(LENT * 10000 + 600 + 6, CellInfo(TRIDUUM, WHITE, "基督安眠墓中(复活节前夕)")));

        // 复活期第一主日（复活节）
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 0, CellInfo(SOLEMNITY, WHITE, "复活节")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 1, CellInfo(SOLEMNITY, WHITE, "复活节庆期第二日")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 2, CellInfo(SOLEMNITY, WHITE, "复活节庆期第三日")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 3, CellInfo(SOLEMNITY, WHITE, "复活节庆期第四日")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 4, CellInfo(SOLEMNITY, WHITE, "复活节庆期第五日")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 5, CellInfo(SOLEMNITY, WHITE, "复活节庆期第六日")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 100 + 6, CellInfo(SOLEMNITY, WHITE, "复活节庆期第七日")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 200 + 0, CellInfo(SOLEMNITY, WHITE, "复活节庆期第八日(慈悲主日)")));
        // 复活期第四主日
        mapPropers.insert(std::make_pair(EASTER * 10000 + 400 + 0, CellInfo(SUNDAY, WHITE, "复活期第四主日(善牧主日)")));

        // 圣神降临节（复活期第八主日）
        // mapPropers.insert(std::make_pair(EASTER*10000+700+6,CellInfo(FEAST,RED,"圣神降临节前夕")));
        mapPropers.insert(std::make_pair(EASTER * 10000 + 800 + 0, CellInfo(SOLEMNITY, RED, "圣神降临节")));

        // 常年期第三十三主日（世界穷人日）
        mapPropers.insert(std::make_pair(ORDINARY * 10000 + 3300 + 0, CellInfo(SUNDAY, WHITE, "常年期第三十三主日(世界穷人日)")));
        // 常年期第三十四主日（基督普世君王节）
        mapPropers.insert(std::make_pair(ORDINARY * 10000 + 3400 + 0, CellInfo(SOLEMNITY, WHITE, "基督普世君王节")));
    }

    /*
    // 特殊节日
    // 索引从1开始
    */
    {
        mapPropers.insert(std::make_pair(1, CellInfo(SOLEMNITY, WHITE, "主显节(Epiphany of the Lord)")));
        mapPropers.insert(std::make_pair(2, CellInfo(LORD, WHITE, "主受洗日(Baptism of the Lord)")));

        // 从复活节算起的节日
        mapPropers.insert(std::make_pair(3, CellInfo(LORD, WHITE, "我们的主耶稣基督—永恒的大司祭"))); // 复活节后53日
        mapPropers.insert(std::make_pair(4, CellInfo(SOLEMNITY, WHITE, "圣三主日")));                 // 复活节后56日（复活期后的主日）
        mapPropers.insert(std::make_pair(5, CellInfo(SOLEMNITY, WHITE, "基督圣体圣血节")));           // 复活节后60日
        mapPropers.insert(std::make_pair(6, CellInfo(SOLEMNITY, WHITE, "耶稣圣心节")));               // 复活节后68日
        mapPropers.insert(std::make_pair(7, CellInfo(MEMORIAL, WHITE, "圣母无玷圣心")));              // 复活节后69日

        // 圣诞期
        mapPropers.insert(std::make_pair(8, CellInfo(LORD, WHITE, "圣家节")));

        // 中华圣母（五月份的第二个星期六）
        mapPropers.insert(std::make_pair(9, CellInfo(FEAST, WHITE, "中华圣母")));
        // 教会之母节（圣神降临节后星期一）
        mapPropers.insert(std::make_pair(10, CellInfo(MEMORIAL, WHITE, "教会之母")));

        // 农历除夕
        mapPropers.insert(std::make_pair(11, CellInfo(FEAST, NOCOLOR, "农历除夕", chineseLang)));
        // 农历春节
        mapPropers.insert(std::make_pair(12, CellInfo(FEAST, NOCOLOR, "农历新春", chineseLang)));
        // 普世传教节
        mapPropers.insert(std::make_pair(13, CellInfo(LORD, GREEN, "普世传教节")));

        // 耶稣升天（固定在复活期第六主日星期四，但可能因牧灵需要调整到第七主日）
        mapPropers.insert(std::make_pair(14, CellInfo(SOLEMNITY, WHITE, "耶稣升天节")));

        // 圣诞期1月2日～1月8日
        mapPropers.insert(std::make_pair(15, CellInfo(WEEKDAY, WHITE, "圣诞期 1月2日")));
        mapPropers.insert(std::make_pair(16, CellInfo(WEEKDAY, WHITE, "圣诞期 1月3日")));
        mapPropers.insert(std::make_pair(17, CellInfo(WEEKDAY, WHITE, "圣诞期 1月4日")));
        mapPropers.insert(std::make_pair(18, CellInfo(WEEKDAY, WHITE, "圣诞期 1月5日")));
        mapPropers.insert(std::make_pair(19, CellInfo(WEEKDAY, WHITE, "圣诞期 1月6日")));
        mapPropers.insert(std::make_pair(20, CellInfo(WEEKDAY, WHITE, "圣诞期 1月7日")));
        mapPropers.insert(std::make_pair(21, CellInfo(WEEKDAY, WHITE, "圣诞期 1月8日")));

        // 主显节后的星期一至星期六
        mapPropers.insert(std::make_pair(31, CellInfo(WEEKDAY, WHITE, "主显节后 星期一")));
        mapPropers.insert(std::make_pair(32, CellInfo(WEEKDAY, WHITE, "主显节后 星期二")));
        mapPropers.insert(std::make_pair(33, CellInfo(WEEKDAY, WHITE, "主显节后 星期三")));
        mapPropers.insert(std::make_pair(34, CellInfo(WEEKDAY, WHITE, "主显节后 星期四")));
        mapPropers.insert(std::make_pair(35, CellInfo(WEEKDAY, WHITE, "主显节后 星期五")));
        mapPropers.insert(std::make_pair(36, CellInfo(WEEKDAY, WHITE, "主显节后 星期六")));
    }

    // 将节日编码插入到节日里
    auto iter = mapPropers.begin();
    while (iter != mapPropers.end())
    {
        iter->second.code = iter->first;
        CathAssist::Calendar::MultiLang::setString(iter->first, "zh_CN", iter->second.celebration);
        auto celebration = CathAssist::Calendar::MultiLang::getString(iter->first);
        if (celebration.size() > 0)
        {
            iter->second.celebration = celebration;
        }
        ++iter;
    }
}

void CathAssist::Calendar::LiturgicYear::releasePropers()
{
    mapPropers.clear();
}

CathAssist::Calendar::CellInfo CathAssist::Calendar::LiturgicYear::getCellInfo(const int &id)
{
    auto iter = mapPropers.find(id);
    if (iter != mapPropers.end())
        return iter->second;

    return CellInfo(CathAssist::Calendar::ErrorRank, CathAssist::Calendar::NOCOLOR, "");
}

LiturgicYear::LiturgicYear(const int &y)
    : year(y)
{
    init();
}

LiturgicYear::~LiturgicYear(void)
{
}

LiturgicDay LiturgicYear::getLiturgicDay(const Date &d)
{
    if (d.year() != year)
        return LiturgicDay();

    // 填充数据
    LiturgicDay ld = d;
    if (ld <= bl)
    {
        testChristmas1(ld);
    }
    else if (ld < aw)
    {
        testOrdinary1(ld);
    }
    else if (ld < easter)
    {
        testLent(ld);
    }
    else if (ld <= ps)
    {
        testEaster(ld);
    }
    else if (ld < av)
    {
        testOrdinary2(ld);
    }
    else if (ld < cm)
    {
        testAdvent(ld);
    }
    else
    {
        testChristmas2(ld);
    }

    testProper(ld);

    return ld;
}

std::string LiturgicYear::toString() const
{
    std::ostringstream ostr;
    ostr << "年份:" << year << std::endl;
    ostr << "主显节\t\t:\t" << ep.toString() << std::endl;
    ostr << "主受洗日\t\t:\t" << bl.toString() << std::endl;
    ostr << "圣灰礼仪\t\t:\t" << aw.toString() << std::endl;
    ostr << "复活节\t\t:\t" << easter.toString() << std::endl;
    ostr << "圣神降临\t\t:\t" << ps.toString() << std::endl;
    ostr << "将临期第一主日\t:\t" << av.toString() << std::endl;

    return ostr.str();
}

void LiturgicYear::init()
{
    LiturgicDay t(year, 1, 2);

    // 主显节
    langcode_t lang = CathAssist::Calendar::MultiLang::getLangCode();
    if (lang == LANG_IT_IT || lang == LANG_ES_ES)
    {
        // 意大利、西班牙等国家采用1月6日为主显节
        ep.setDate(year, 1, 6);

        // 主受洗日(主显节后的主日)
        bl = ep.addDays(7 - ep.dayOfWeek());
    }
    else
    {
        // 其他国家采用临近1月6日的主日为主显节
        ep = t.addDays((7 - t.dayOfWeek()) % 7);

        // 主受洗日
        if (ep.day() > 6)
        {
            // 主显节后的第二天（星期一）
            bl = ep.addDays(1);
        }
        else
        {
            // 主显节后的下一个主日
            bl = ep.addDays(7);
        }
    }

    // 复活节
    {
        int y, c, n, k, i, j, l, m, d;
        y = year;

        c = y / 100;
        n = y - 19 * (y / 19);
        k = (c - 17) / 25;
        i = c - c / 4 - (c - k) / 3 + 19 * n + 15;
        i = i - 30 * (i / 30);
        i = i - (i / 28) * (1 - (i / 28) * (29 / (i + 1)) * ((21 - n) / 11));
        j = y + y / 4 + i + 2 - c + c / 4;
        j = j - 7 * (j / 7);
        l = i - j;

        m = 3 + (l + 40) / 44;
        d = l + 28 - 31 * (m / 4);

        easter.setDate(year, m, d);
    }

    // 圣灰礼仪（周三 四旬期开始）
    aw = easter.addDays(-46);

    // 圣神降临节瞻礼
    ps = easter.addDays(49);

    t.setDate(year, 11, 30);
    // 将临期第一主日
    if (t.dayOfWeek() > Days::WED)
    {
        av = t.addDays(7 - t.dayOfWeek());
    }
    else
    {
        av = t.addDays(0 - t.dayOfWeek());
    }

    // 圣诞节
    cm.setDate(year, 12, 25);
}

void LiturgicYear::testChristmas1(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld < LiturgicDay(year, 1, 1) || ld > bl)
        return;

    ld.setSeason(CHRISTMAS);
    ld.setWeekOfSeason(-1);
    if (ld < ep)
    {
        if(ld.dayOfWeek() == SUN && ep.dayOfWeek() != SUN)
        {
            // 晚祷只用第二主日圣咏
            ld.setWeekOfSeason(2);
        } else {
            if (ep.day() == 8)
            {
                // 主显节在 1 月 8 日，主显节前是第二周（没有第一周）
                ld.setWeekOfSeason(2);
            }
            else
            {
                ld.setWeekOfSeason(1);
            }
        }

        // 弥撒特殊处理 主显节前(1月2日～1月8日)
        if (ld.day() == 2)
        {
            ld.appendCell(15);
        }
        else if (ld.day() == 3)
        {
            ld.appendCell(16);
        }
        else if (ld.day() == 4)
        {
            ld.appendCell(17);
        }
        else if (ld.day() == 5)
        {
            ld.appendCell(18);
        }
        else if (ld.day() == 6)
        {
            ld.appendCell(19);
        }
        else if (ld.day() == 7)
        {
            ld.appendCell(20);
        }
        else if (ld.day() == 8)
        {
            ld.appendCell(21);
        }
    }
    else if (ld == ep)
    {
        ld.appendCell(1); // 主显节（普世教会）
        if (ep.day() == 8)
        {
            ld.setWeekOfSeason(-1);
        }
        else
        {
            ld.setWeekOfSeason(2);
        }
    }
    else if (ld > ep && ld < bl)
    {
        // 主显节～主受洗日之间如果有平日，就一定是第二周
        ld.setWeekOfSeason(2);

        // 弥撒特殊处理 主显节后按礼仪年处理
        if (ld.dayOfWeek() == MON)
        {
            ld.appendCell(31);
        }
        else if (ld.dayOfWeek() == TUE)
        {
            ld.appendCell(32);
        }
        else if (ld.dayOfWeek() == WED)
        {
            ld.appendCell(33);
        }
        else if (ld.dayOfWeek() == THU)
        {
            ld.appendCell(34);
        }
        else if (ld.dayOfWeek() == FRI)
        {
            ld.appendCell(35);
        }
        else if (ld.dayOfWeek() == SAT)
        {
            ld.appendCell(36);
        }
    }
    else if (ld == bl)
    {
        ld.appendCell(2); // 主受洗日
        if (bl.dayOfWeek() == MON)
        {
            // 主受洗日不是主日
            ld.setSeason(ORDINARY);
            ld.setWeekOfSeason(1);
        }
    }

    if (ld.month() == 1 && ld.day() == 6)
    {
        // 移除 1 月 6 日的主显节
        //		ld.appendCell(1);	//主显节（大陆教会）
    }
}

void LiturgicYear::testOrdinary1(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld <= bl || ld >= aw)
        return;

    ld.setSeason(ORDINARY);
    //	int weekBegin = aw.weekNumber();
    ld.setWeekOfSeason(ld.weekNumber() - bl.weekNumber() + 1);
}

void LiturgicYear::testLent(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld < aw || ld >= easter)
        return;

    ld.setSeason(LENT);
    ld.setWeekOfSeason(ld.weekNumber() - aw.weekNumber());
}

void LiturgicYear::testEaster(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld < easter || ld > ps)
        return;

    ld.setSeason(EASTER);
    ld.setWeekOfSeason(ld.weekNumber() - easter.weekNumber() + 1);

    if (ld.getLiturgicId() == EASTER * 10000 + 600 + 4)
    {
        ld.appendCell(14); // 耶稣升天节（复活期第六主日星期四）
    }
    if (ld.getLiturgicId() == EASTER * 10000 + 700 + 0)
    {
        ld.appendCell(14); // 耶稣升天节（可挪到主日庆祝）
    }
}

void LiturgicYear::testOrdinary2(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld <= ps || ld >= av)
        return;

    int weekEnd = av.weekNumber() - 1; // 将临期第一主日为常年期的结束
    ld.setWeekOfSeason(34 - (weekEnd - ld.weekNumber()));

    int dayFromEaster = easter.daysTo(ld);

    if (dayFromEaster == 53)
    {
        ld.appendCell(3); // 我们的主耶稣基督—永恒的大司祭
    }
    else if (dayFromEaster == 56)
    {
        ld.appendCell(4); // 圣三主日
    }
    else if (dayFromEaster == 60 || dayFromEaster == 63)
    {
        // 圣三主日的星期四(+60)，可移至主日庆祝(+63)
        ld.appendCell(5); // 基督圣体圣血节
    }
    else if (dayFromEaster == 68)
    {
        ld.appendCell(6); // 耶稣圣心节
    }
    else if (dayFromEaster == 69)
    {
        ld.appendCell(7); // 圣母无玷圣心
    }

    if (SUN == ld.dayOfWeek() && 10 == ld.month() && ld.day() >= 18 && ld.day() <= 24)
    {
        // 普世传教节，10月倒数第二个主日
        ld.appendCell(13);
    }

    ld.setSeason(ORDINARY);
}

void LiturgicYear::testAdvent(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld < av || ld >= cm)
        return;

    ld.setSeason(ADVENT);
    ld.setWeekOfSeason(ld.weekNumber() - av.weekNumber() + 1);
}

void LiturgicYear::testChristmas2(LiturgicDay &ld)
{
    if ((!ld.isValid()) || ld < cm || ld > LiturgicDay(year, 12, 31))
        return;

    // 将临期第四主日的星期六之后的日期归为圣诞期第一周
    if (cm.dayOfWeek() != SUN && ld.dayOfWeek() >= cm.dayOfWeek())
    {
        ld.setSeason(ADVENT);
        ld.setWeekOfSeason(4);
    }
    else
    {
        ld.setSeason(CHRISTMAS);
        ld.setWeekOfSeason(1);
    }

    if (ld.dayOfWeek() == SUN)
    {
        // 省去圣诞期第一主日
        ld.setWeekOfSeason(-1);
    }

    // 圣家节
    if (cm.dayOfWeek() == SUN)
    {
        if (ld == Date(year, 12, 30))
            ld.appendCell(8);
    }
    else
    {
        if (ld.dayOfWeek() == SUN)
            ld.appendCell(8);
    }
}

void LiturgicYear::testProper(LiturgicDay &ld)
{
    {
        // 教会之母（圣神降临节后星期一）
        if (ld.daysTo(ps) == -1)
        {
            ld.appendCell(10);
        }
    }

    {
        // 中华圣母（5月的第二个周六）
        if (ld.month() == 5 && ld.dayOfWeek() == 6)
        {
            if (ld.day() >= 7 && ld.day() <= 13)
            {
                ld.appendCell(9);
            }
        }
    }

    {
        // 中国农历新年
        if (LiturgicDay::isSpringFestival(ld))
        {
            ld.appendCell(12);
        }
        // 中国农历除夕
        if (LiturgicDay::isNewYearEve(ld))
        {
            ld.appendCell(11);
        }
    }

    {
        // 礼仪年特殊节日
        int id = ld.getLiturgicId();
        auto iter = mapPropers.find(id);
        if (iter != mapPropers.end())
        {
            ld.appendCell(iter->first);
        }
    }
    {
        int v = 1000000 + ld.month() * 10000 + ld.day() * 100;

        auto iter = mapPropers.lower_bound(v);
        while (iter != mapPropers.end())
        {
            int key = iter->first;
            if (key / 100 != v / 100)
                break;
            ld.appendCell(key);

            ++iter;
        }
    }
}

std::list<CellInfo> LiturgicYear::getNormalDays()
{
    std::list<CellInfo> days;
    {
        // 将临期
        for (int i = 1; i <= 4; ++i)
        {
            for (int j = 0; j <= 6; ++j)
            {
                int code = ADVENT * 10000 + i * 100 + j;
                days.push_back(CellInfo(code, getRankByLiturgicId(code), getColorByLiturgicId(code), LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        // 圣诞期（12月25日至次年1月1日全部是特殊日期，1月2日～主显节为第二周，主显节后为第三周）
        for (int i = 1; i <= 2; ++i)
        {
            for (int j = 0; j <= 6; ++j)
            {
                if (i == 1 && j == 0)
                {
                    // 省去圣诞期第一主日
                    continue;
                }
                int code = CHRISTMAS * 10000 + i * 100 + j;
                days.push_back(CellInfo(code, getRankByLiturgicId(code), getColorByLiturgicId(code), LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        // 四旬期
        // 圣灰礼仪后三天（周四、周五、周六）
        int code = LENT * 10000 + 0 * 100 + 4;
        days.push_back(CellInfo(code, WEEKDAY, PURPLE, LiturgicDay::getWeekdayString(code)));
        code++;
        days.push_back(CellInfo(code, WEEKDAY, PURPLE, LiturgicDay::getWeekdayString(code)));
        code++;
        days.push_back(CellInfo(code, WEEKDAY, PURPLE, LiturgicDay::getWeekdayString(code)));
        for (int i = 1; i <= 6; ++i)
        {
            for (int j = 0; j <= 6; ++j)
            {
                int code = LENT * 10000 + i * 100 + j;
                days.push_back(CellInfo(code, getRankByLiturgicId(code), getColorByLiturgicId(code), LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        // 复活期
        for (int i = 1; i <= 7; ++i)
        {
            for (int j = 0; j <= 6; ++j)
            {
                int code = EASTER * 10000 + i * 100 + j;
                days.push_back(CellInfo(code, getRankByLiturgicId(code), getColorByLiturgicId(code), LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        // 常年期
        for (int i = 1; i <= 34; ++i)
        {
            for (int j = 0; j <= 6; ++j)
            {
                int code = ORDINARY * 10000 + i * 100 + j;
                days.push_back(CellInfo(code, getRankByLiturgicId(code), getColorByLiturgicId(code), LiturgicDay::getWeekdayString(code)));
            }
        }
    }

    return days;
}
