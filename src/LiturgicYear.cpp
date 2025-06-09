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
#include <sstream>

using namespace CathAssist::Calendar;

std::multimap<int,CellInfo> CathAssist::Calendar::LiturgicYear::mapPropers;

void CathAssist::Calendar::LiturgicYear::initPropers()
{
    if(mapPropers.size() > 0) {
        return;
    }
	/*
	// 初始化常用节日（日期固定）
	// 规则：采用十进制（共7位）,最高位始终为1
	// 前面两位为：月份
	// 中间两位为：月内日期
	// 最后两位为：编号，从1开始（适用于某个日期中可能有多个纪念日的情况）
	*/
	{
		/*******************1月**********************/
        //1日
		mapPropers.insert(std::make_pair(1010101,CellInfo(SOLEMNITY,WHITE,"天主之母节(Solemnity Mary,Monther of God)")));
        //2日
        mapPropers.insert(std::make_pair(1010201,CellInfo(MEMORIAL,WHITE,"圣西略及圣国瑞•纳祥(St. Basil the Great & Gregory Nazianxen)")));
        //3日
        mapPropers.insert(std::make_pair(1010301,CellInfo(MEMORIAL,WHITE,"耶稣圣名")));
        mapPropers.insert(std::make_pair(1010302,CellInfo(OPTIONAL,NOCOLOR,"真福查瓦拉(Bd. Kuriakose Elias Chavara)")));
        mapPropers.insert(std::make_pair(1010303,CellInfo(OPTIONAL,NOCOLOR,"圣女日南斐法(童贞 St. Genevieve)")));
        //4日
        mapPropers.insert(std::make_pair(1010401,CellInfo(OPTIONAL,NOCOLOR,"圣安•贝兰•丝彤(依丽莎白 St. Eizabeth Ann Bayley Seton)")));
        mapPropers.insert(std::make_pair(1010402,CellInfo(OPTIONAL,NOCOLOR,"圣女法拉意弟(St. Pharaildis)")));
        //5日
        mapPropers.insert(std::make_pair(1010501,CellInfo(OPTIONAL,NOCOLOR,"圣牛曼(St. John Nepornucene Neumann)")));
        mapPropers.insert(std::make_pair(1010502,CellInfo(OPTIONAL,NOCOLOR,"圣西默盎“石柱人”(St. Simeon the Stylite)")));
		//6日
        mapPropers.insert(std::make_pair(1010602,CellInfo(OPTIONAL,NOCOLOR,"真福辣法厄尔•玛利亚(童贞圣心婢女会会祖 Bd. Raphaela Mary)")));
        //7日
		mapPropers.insert(std::make_pair(1010701,CellInfo(OPTIONAL,NOCOLOR,"圣赖孟多(St. Raymond of Penyafort)")));
        //8日
        mapPropers.insert(std::make_pair(1010801,CellInfo(OPTIONAL,NOCOLOR,"圣塞味利•诺利根(St. Severin of Noricun)")));
        //9日
        mapPropers.insert(std::make_pair(1010901,CellInfo(OPTIONAL,NOCOLOR,"圣哈德良(坎特培里院长 St. Adrian)")));
        //10日
        mapPropers.insert(std::make_pair(1011001,CellInfo(OPTIONAL,NOCOLOR,"圣阿加道(教宗 St. Agatho)")));
        mapPropers.insert(std::make_pair(1011002,CellInfo(OPTIONAL,NOCOLOR,"真福额我略十世(教宗 Bd. Gregory X)")));
        //11日
        mapPropers.insert(std::make_pair(1011101,CellInfo(OPTIONAL,NOCOLOR,"圣戴沃多西(St. Theodosius the Cenobiarch)")));
        //12日
        mapPropers.insert(std::make_pair(1011201,CellInfo(OPTIONAL,NOCOLOR,"圣本笃•波斯哥(修院院长 St. Benedict Biscop)")));
        //13日
		mapPropers.insert(std::make_pair(1011301,CellInfo(OPTIONAL,NOCOLOR,"圣依拉略(主教圣师 St. Hilary)")));
        //14日
        mapPropers.insert(std::make_pair(1011401,CellInfo(OPTIONAL,NOCOLOR,"真福和德理精修(Bd. Odoric of Pordenone)")));
        //15日
        mapPropers.insert(std::make_pair(1011501,CellInfo(OPTIONAL,NOCOLOR,"圣保禄首位独修(St. Paul the Hermit)")));
        mapPropers.insert(std::make_pair(1011502,CellInfo(OPTIONAL,NOCOLOR,"圣毛禄院长(St. Maurus)")));
        //16日
        mapPropers.insert(std::make_pair(1011601,CellInfo(OPTIONAL,NOCOLOR,"圣马塞录一世(教宗殉道 St. Marcellus)")));
        //17日
        mapPropers.insert(std::make_pair(1011701,CellInfo(MEMORIAL,WHITE,"圣安当院长(St. Antony the Great)")));
        
        //18日
        mapPropers.insert(std::make_pair(1011801,CellInfo(OPTIONAL,NOCOLOR,"为基督徒合一祈祷周（18 - 25日）")));
        mapPropers.insert(std::make_pair(1011802,CellInfo(FEAST,WHITE,"圣伯多禄定圣座于罗马(St. Peter's Chair at Rome)")));
        mapPropers.insert(std::make_pair(1011803,CellInfo(OPTIONAL,NOCOLOR,"圣女普黎斯加(St. Prisca)")));
        //19日
        mapPropers.insert(std::make_pair(1011901,CellInfo(OPTIONAL,NOCOLOR,"圣加努多(St. Canute Denrnark)")));
        mapPropers.insert(std::make_pair(1011902,CellInfo(OPTIONAL,NOCOLOR,"马略、玛尔大、奥地法和亚巴古(殉道 Ss. Marius, Maltha, Audifax & Abachum)")));
        mapPropers.insert(std::make_pair(1011903,CellInfo(OPTIONAL,NOCOLOR,"圣女玛加利大(童贞蒙特利尔圣母会会祖 St. Margaret Bourgeoys 1620-1700)")));
        //20日
        mapPropers.insert(std::make_pair(1012001,CellInfo(OPTIONAL,NOCOLOR,"圣法比盎(法彬教宗殉道 St. Fabian)")));
        mapPropers.insert(std::make_pair(1012002,CellInfo(OPTIONAL,NOCOLOR,"圣巴斯弟盎(殉道 St. Sebasian)")));
        //21日
        mapPropers.insert(std::make_pair(1012101,CellInfo(MEMORIAL,RED,"圣女依搦斯(雅妮童贞殉道 St. Agnes)")));
        //22日
        mapPropers.insert(std::make_pair(1012201,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵(文生殉道 St. Vincent of Saragossa)")));
        mapPropers.insert(std::make_pair(1012202,CellInfo(OPTIONAL,NOCOLOR,"圣亚纳大削(殉道 St. Anastasius the Persian)")));
        mapPropers.insert(std::make_pair(1012203,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵•柏乐天(St. Vincent Polloti)")));
        //23日
        mapPropers.insert(std::make_pair(1012301,CellInfo(OPTIONAL,NOCOLOR,"圣爱美兰霞(童贞殉道 St. Emerentiana)")));
        mapPropers.insert(std::make_pair(1012401,CellInfo(MEMORIAL,WHITE,"圣方济各•撒肋爵(主教圣师 St. Francis de Sales)")));
        mapPropers.insert(std::make_pair(1012501,CellInfo(FEAST,WHITE,"圣保禄宗徒归化(The Conversion of St. Paul)")));
        mapPropers.insert(std::make_pair(1012601,CellInfo(MEMORIAL,WHITE,"圣弟茂德及圣弟铎(St. Timothy & St. Titus)")));
        //27日
        mapPropers.insert(std::make_pair(1012701,CellInfo(OPTIONAL,NOCOLOR,"圣女安琪拉(童贞圣乌苏拉女修会会祖 St. Angela Merici)")));
        mapPropers.insert(std::make_pair(1012801,CellInfo(MEMORIAL,WHITE,"圣多玛斯•阿奎那(圣师雅奎 St. Thomas Aquinas)")));
        mapPropers.insert(std::make_pair(1012901,CellInfo(OPTIONAL,NOCOLOR,"圣亚波罗尼(殉道 St. Apoelonius the Apologist)")));
        mapPropers.insert(std::make_pair(1012902,CellInfo(MEMORIAL,NOCOLOR,"圣福若瑟(司铎 St. Joseph Freinademetz)")));
        mapPropers.insert(std::make_pair(1013001,CellInfo(OPTIONAL,NOCOLOR,"圣女玛蒂娜(童贞致命 St. Martina)")));
        mapPropers.insert(std::make_pair(1013002,CellInfo(OPTIONAL,NOCOLOR,"圣妇巴蒂弟(St. Bathildis)")));
        mapPropers.insert(std::make_pair(1013003,CellInfo(MEMORIAL,NOCOLOR,"真福雷永明(司铎 Bd. Gabriele Allegra)")));
        mapPropers.insert(std::make_pair(1013101,CellInfo(MEMORIAL,WHITE,"圣鲍思高(慈幼会会祖 St. John Bosco)")));
        mapPropers.insert(std::make_pair(1013102,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•沙勿略•白英奇(St. Francis Xavier Bianchi)")));
        
        /**********************2月*********************/
        //1日
        mapPropers.insert(std::make_pair(1020101,CellInfo(OPTIONAL,NOCOLOR,"圣亨利•莫斯(殉道 St. Herry Morse)")));
        mapPropers.insert(std::make_pair(1020201,CellInfo(LORD,WHITE,"献耶稣于圣殿(Presentation of the Lord)")));
        mapPropers.insert(std::make_pair(1020301,CellInfo(OPTIONAL,NOCOLOR,"圣巴拉削(主教殉道 St. Blaise)")));
        mapPropers.insert(std::make_pair(1020302,CellInfo(OPTIONAL,NOCOLOR,"圣老楞佐(主教 St. Laurence)")));
        //4日
        mapPropers.insert(std::make_pair(1020401,CellInfo(OPTIONAL,NOCOLOR,"圣若望•波利多(殉道 St. John de Britto)")));
        mapPropers.insert(std::make_pair(1020402,CellInfo(OPTIONAL,NOCOLOR,"圣妇若翰纳(圣母领报会会祖 St. John of France)")));
        mapPropers.insert(std::make_pair(1020501,CellInfo(MEMORIAL,RED,"圣女亚加大(童贞殉道 St. Agatha)")));
        //6日
        mapPropers.insert(std::make_pair(1020601,CellInfo(MEMORIAL,RED,"圣保禄三木司铎及同伴(the Martyrs of Japan)")));
        mapPropers.insert(std::make_pair(1020602,CellInfo(OPTIONAL,NOCOLOR,"圣童郑安道")));
        mapPropers.insert(std::make_pair(1020701,CellInfo(OPTIONAL,NOCOLOR,"圣女尤丽娜(童贞 St. Juliana Falconieri)")));
        mapPropers.insert(std::make_pair(1020801,CellInfo(OPTIONAL,NOCOLOR,"圣热罗莫•爱弥廉(St. Jierome Emiliani)")));
        mapPropers.insert(std::make_pair(1020802,CellInfo(OPTIONAL,NOCOLOR,"圣若望•玛达(圣三赎虏会副会祖 St. John of Matha)")));
        //9日
        mapPropers.insert(std::make_pair(1020901,CellInfo(OPTIONAL,NOCOLOR,"圣高德乐(精修 St. Miguel Febres Cordero)")));
        mapPropers.insert(std::make_pair(1020902,CellInfo(OPTIONAL,NOCOLOR,"圣撒比诺(嘉诺沙主教 St. Sabinus)")));
        //10日
        mapPropers.insert(std::make_pair(1021001,CellInfo(MEMORIAL,WHITE,"圣女斯高拉蒂加(圣思嘉童贞 Scholastica)")));
        mapPropers.insert(std::make_pair(1021101,CellInfo(MEMORIAL,WHITE,"露德圣母显现(the Appearing of our Lady at Lourdes)")));
        //12日
        mapPropers.insert(std::make_pair(1021201,CellInfo(OPTIONAL,NOCOLOR,"圣高登雪(主教 St. Gaudentius)")));
        mapPropers.insert(std::make_pair(1021202,CellInfo(OPTIONAL,NOCOLOR,"圣路登(St. Ludan)")));
        mapPropers.insert(std::make_pair(1021301,CellInfo(OPTIONAL,NOCOLOR,"圣女加大利纳•利其(St. Catherine de Ricci)")));
        mapPropers.insert(std::make_pair(1021302,CellInfo(OPTIONAL,NOCOLOR,"圣玛蒂银“隐修士”(St. Martinian the Hermit)")));
        //14日
        mapPropers.insert(std::make_pair(1021401,CellInfo(MEMORIAL,WHITE,"圣济利禄、圣美铎第(主教 Ss. Cyril and Methodius)")));
        mapPropers.insert(std::make_pair(1021402,CellInfo(OPTIONAL,NOCOLOR,"圣华楞定(殉道 St. Valentine)")));
        mapPropers.insert(std::make_pair(1021501,CellInfo(OPTIONAL,NOCOLOR,"圣傅天定和圣约未达殉道(Ss. Faustinus & Jovita)")));
        mapPropers.insert(std::make_pair(1021502,CellInfo(OPTIONAL,NOCOLOR,"真福日安当(Bd. Jordan of Saxony)")));
        mapPropers.insert(std::make_pair(1021503,CellInfo(OPTIONAL,NOCOLOR,"圣高隆汴(St. Claud La Colombiere)")));
        mapPropers.insert(std::make_pair(1021601,CellInfo(OPTIONAL,NOCOLOR,"圣奥乃西(殉道 St. Onesimus)")));
        //17日
        mapPropers.insert(std::make_pair(1021701,CellInfo(OPTIONAL,NOCOLOR,"圣母忠仆会七位会祖(the Founders of the Servite Order)")));
        mapPropers.insert(std::make_pair(1021702,CellInfo(OPTIONAL,NOCOLOR,"圣刁杜禄与圣儒里安(殉道 Ss. Theodulus & Julian)")));
        mapPropers.insert(std::make_pair(1021801,CellInfo(OPTIONAL,NOCOLOR,"圣西满(主教殉道 St. Simeon)")));
        mapPropers.insert(std::make_pair(1021901,CellInfo(OPTIONAL,NOCOLOR,"圣公拉(St. Conrad of Placenza)")));
        mapPropers.insert(std::make_pair(1022001,CellInfo(OPTIONAL,NOCOLOR,"圣欧千流(奥尔良主教 St. Eucherius)")));
        mapPropers.insert(std::make_pair(1022002,CellInfo(OPTIONAL,NOCOLOR,"圣弟拉诺、柴诺波等殉道(Ss. Tyrannio, Zenobius & other Martyrs)")));
        //21日
        mapPropers.insert(std::make_pair(1022101,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•达弥盎(主教圣师 St. Peter Damian)")));
        mapPropers.insert(std::make_pair(1022201,CellInfo(FEAST,WHITE,"建立圣伯多禄宗座于安提约基(St. Peter’s Chair at Antioch)")));
        mapPropers.insert(std::make_pair(1022202,CellInfo(OPTIONAL,NOCOLOR,"圣女玛加利大•高多娜(St. Margaret Cortona)")));
        mapPropers.insert(std::make_pair(1022301,CellInfo(MEMORIAL,RED,"圣波利卡浦(主教殉道 St. Polycarp)")));
        //24日
        mapPropers.insert(std::make_pair(1022401,CellInfo(OPTIONAL,NOCOLOR,"圣凯撒利乌•纳齐盎(St. Caesarius of Nazianzus)")));
        mapPropers.insert(std::make_pair(1022402,CellInfo(OPTIONAL,NOCOLOR,"圣孟泰诺、圣路琪及其它烈士(殉道 Ss. Montantls, Lucius & their Companions)")));
        mapPropers.insert(std::make_pair(1022501,CellInfo(OPTIONAL,NOCOLOR,"圣女华波加(童贞 St. Walburga)")));
        mapPropers.insert(std::make_pair(1022502,CellInfo(OPTIONAL,NOCOLOR,"圣泰拉修(君士坦丁堡宗主教 St. Tarsius)")));
        mapPropers.insert(std::make_pair(1022601,CellInfo(OPTIONAL,NOCOLOR,"圣女美狄黛(童贞 St. Mechtilde)")));
        mapPropers.insert(std::make_pair(1022602,CellInfo(OPTIONAL,NOCOLOR,"圣波菲利(迦萨主教 St. Porphyry)")));
        mapPropers.insert(std::make_pair(1022701,CellInfo(OPTIONAL,NOCOLOR,"圣母痛苦圣嘉俾厄尔(St. Gabriel Possenti)")));
        mapPropers.insert(std::make_pair(1022702,CellInfo(OPTIONAL,NOCOLOR,"圣林达(赛维拉主教 St. Leander)")));
        mapPropers.insert(std::make_pair(1022801,CellInfo(OPTIONAL,NOCOLOR,"圣希拉利(教宗 St. Hilarius)")));
        mapPropers.insert(std::make_pair(1022802,CellInfo(OPTIONAL,NOCOLOR,"福女安日拉(Bd. Angela of Foligno)")));
    
        /******************3月*****************/
        //1日
        mapPropers.insert(std::make_pair(1030101,CellInfo(OPTIONAL,NOCOLOR,"圣达味(米尼主教 St. David 495-589)")));
        mapPropers.insert(std::make_pair(1030201,CellInfo(OPTIONAL,NOCOLOR,"圣嘉德(李非主教 St. Chad)")));
        mapPropers.insert(std::make_pair(1030202,CellInfo(OPTIONAL,NOCOLOR,"圣妇顾乃宫(St. Cunegund)")));
        mapPropers.insert(std::make_pair(1030301,CellInfo(OPTIONAL,NOCOLOR,"圣女加大利纳(St. Katharine Drexel 1858-1955)")));
        mapPropers.insert(std::make_pair(1030401,CellInfo(OPTIONAL,NOCOLOR,"圣加西弥禄(St. Casimir of Poland)")));
        mapPropers.insert(std::make_pair(1030501,CellInfo(OPTIONAL,NOCOLOR,"圣十字架若望若瑟(St. John Joseph of the Cross)")));
        //6日
        mapPropers.insert(std::make_pair(1030601,CellInfo(OPTIONAL,NOCOLOR,"圣女高莱德(童贞 St. Colette)")));
        mapPropers.insert(std::make_pair(1030602,CellInfo(OPTIONAL,NOCOLOR,"真福若尔当(Bd. Jordan of Pisa)")));
        mapPropers.insert(std::make_pair(1030701,CellInfo(MEMORIAL,RED,"圣妇伯尔都亚、圣妇斐利琪等殉道(Ss. Perpertua Felicity and their Companions)")));
        mapPropers.insert(std::make_pair(1030702,CellInfo(OPTIONAL,NOCOLOR,"圣保禄“诚朴者”(St. Paul the Simple)")));
        mapPropers.insert(std::make_pair(1030801,CellInfo(OPTIONAL,NOCOLOR,"天赐圣若望(St. John of God)")));
        mapPropers.insert(std::make_pair(1030901,CellInfo(OPTIONAL,NOCOLOR,"圣妇芳济加(St. Frances of Rome)")));
        mapPropers.insert(std::make_pair(1031001,CellInfo(MEMORIAL,RED,"色巴德等四十位圣人殉道(the Forty Martyrs of Sebastea)")));
        mapPropers.insert(std::make_pair(1031002,CellInfo(OPTIONAL,NOCOLOR,"圣若望•安其味(St. John Ogilve 1580-1615)")));
        //11日
        mapPropers.insert(std::make_pair(1031101,CellInfo(OPTIONAL,NOCOLOR,"圣欧乐日(殉道 St. Eulogius of Cordova)")));
        mapPropers.insert(std::make_pair(1031102,CellInfo(OPTIONAL,NOCOLOR,"圣君士坦丁(殉道 St. Constantine)")));
        mapPropers.insert(std::make_pair(1031201,CellInfo(OPTIONAL,NOCOLOR,"圣戴法纳(院长 St. Theophanes the Chronicler)")));
        mapPropers.insert(std::make_pair(1031301,CellInfo(OPTIONAL,NOCOLOR,"圣女欧弗来西亚(童贞 St. Euphrasia)")));
        mapPropers.insert(std::make_pair(1031302,CellInfo(OPTIONAL,NOCOLOR,"圣尼赛福禄(君士坦丁堡宗主教 St. Niceohorus)")));
        mapPropers.insert(std::make_pair(1031401,CellInfo(OPTIONAL,NOCOLOR,"圣妇玛蒂达(St. Matilda)")));
        mapPropers.insert(std::make_pair(1031501,CellInfo(OPTIONAL,NOCOLOR,"圣妇露易丝(仁爱女修会副会祖 St. Louisa De Marillac)")));
        mapPropers.insert(std::make_pair(1031502,CellInfo(OPTIONAL,NOCOLOR,"圣格肋孟•浩卜(St. Clemlent Hofbauer)")));
        //16日
        mapPropers.insert(std::make_pair(1031601,CellInfo(OPTIONAL,NOCOLOR,"圣赫利巴(高郎总主教 St. Heribert)")));
        mapPropers.insert(std::make_pair(1031701,CellInfo(OPTIONAL,NOCOLOR,"圣巴特利爵(St. Patrick)")));
        mapPropers.insert(std::make_pair(1031702,CellInfo(OPTIONAL,NOCOLOR,"圣女日多达•尼凡拉(童贞 St. Gertrude of Nivelles)")));
        mapPropers.insert(std::make_pair(1031801,CellInfo(OPTIONAL,NOCOLOR,"圣济利禄(St. Cyril)")));
        mapPropers.insert(std::make_pair(1031802,CellInfo(OPTIONAL,NOCOLOR,"圣安色莫(吕佳主教 St. Anselm)")));
        mapPropers.insert(std::make_pair(1031901,CellInfo(FEAST,WHITE,"圣若瑟(圣母净配中国主保 St. Joseph)")));
        mapPropers.insert(std::make_pair(1032001,CellInfo(OPTIONAL,NOCOLOR,"圣格时白(主教 St. Cuthbert)")));
        //21日
        mapPropers.insert(std::make_pair(1032101,CellInfo(OPTIONAL,NOCOLOR,"圣尼格老•冯物洛(St. Nicholas de flue)")));
        mapPropers.insert(std::make_pair(1032102,CellInfo(OPTIONAL,NOCOLOR,"圣恩达（院长）、圣女芳佳（童贞）(St. Enda and St. Fanchea)")));
        mapPropers.insert(std::make_pair(1032201,CellInfo(OPTIONAL,NOCOLOR,"圣婴西满和圣童威廉(殉道者 Ss. Simen of Trent and William of Norwich)")));
        mapPropers.insert(std::make_pair(1032301,CellInfo(OPTIONAL,NOCOLOR,"圣多利波(利马总主教 St. Turibius)")));
        mapPropers.insert(std::make_pair(1032302,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•奥利沃(St. Joseph Oriol)")));
        mapPropers.insert(std::make_pair(1032401,CellInfo(OPTIONAL,NOCOLOR,"圣女加大利纳•瑞典(童贞 St. Catherine of Sweden)")));
        mapPropers.insert(std::make_pair(1032402,CellInfo(OPTIONAL,NOCOLOR,"圣依勒内(殉道 St. Irenaeus)")));
        mapPropers.insert(std::make_pair(1032501,CellInfo(FEAST,WHITE,"圣母领报(the Annunciation of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1032502,CellInfo(OPTIONAL,NOCOLOR,"真福玛加大•格利塞罗(殉道 Bd. Margaret Clitherow)")));
        mapPropers.insert(std::make_pair(1032503,CellInfo(OPTIONAL,NOCOLOR,"善盗(the good thief)")));
        //26日
        mapPropers.insert(std::make_pair(1032601,CellInfo(OPTIONAL,NOCOLOR,"圣路基(孟斯脱主教 St. Ludger)")));
        mapPropers.insert(std::make_pair(1032602,CellInfo(OPTIONAL,NOCOLOR,"圣加斯多罗(殉道 St. Castulus)")));
        mapPropers.insert(std::make_pair(1032701,CellInfo(OPTIONAL,NOCOLOR,"圣若望“埃及人”(St. John of Egypt)")));
        mapPropers.insert(std::make_pair(1032801,CellInfo(OPTIONAL,NOCOLOR,"圣西斯督三世(教宗 St. Sixrus III)")));
        mapPropers.insert(std::make_pair(1032901,CellInfo(OPTIONAL,NOCOLOR,"圣路伯(沙伯主教 St. Rupert)")));
        mapPropers.insert(std::make_pair(1032902,CellInfo(OPTIONAL,NOCOLOR,"圣约纳和巴拉古(殉道 Ss. Jonas and Barachisius)")));
        mapPropers.insert(std::make_pair(1033001,CellInfo(OPTIONAL,NOCOLOR,"圣若望•克利马古(院长 St. John Climacus)")));
        mapPropers.insert(std::make_pair(1033101,CellInfo(OPTIONAL,NOCOLOR,"圣达尼尔隐修士(St. Daniel of Murano)")));
    
		/***************4月**************/
        //1日
        mapPropers.insert(std::make_pair(1040101,CellInfo(OPTIONAL,NOCOLOR,"圣许格(格肋诺主教 St. Hugh of Grenoble)")));
        mapPropers.insert(std::make_pair(1040102,CellInfo(OPTIONAL,NOCOLOR,"真福路道味•巴华尼(无玷圣母之子会会祖 Bd. Ludovic Pavoni)")));
        mapPropers.insert(std::make_pair(1040201,CellInfo(OPTIONAL,NOCOLOR,"圣方济各保拉(最小兄弟会会祖 St. Francis of Paola)")));
        mapPropers.insert(std::make_pair(1040301,CellInfo(OPTIONAL,NOCOLOR,"圣理查德(St. Richard)")));
        mapPropers.insert(std::make_pair(1040401,CellInfo(OPTIONAL,NOCOLOR,"圣依西多禄(St. Isidore)")));
        mapPropers.insert(std::make_pair(1040402,CellInfo(OPTIONAL,NOCOLOR,"圣“农民”依西多禄希道(St. Isidore the Husbandman)")));
        mapPropers.insert(std::make_pair(1040501,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵•斐勒略(St. Vincent Ferrer)")));
        mapPropers.insert(std::make_pair(1040502,CellInfo(OPTIONAL,NOCOLOR,"真福儒利亚纳(童贞 Bd. Juliana of Mount Cornillon)")));
        //6日
        mapPropers.insert(std::make_pair(1040601,CellInfo(OPTIONAL,NOCOLOR,"圣塞来斯定一世(教宗 St. Celestinel)")));
        mapPropers.insert(std::make_pair(1040701,CellInfo(MEMORIAL,WHITE,"圣若翰•兰沙(St. John Baptist de la Salle)")));
        mapPropers.insert(std::make_pair(1040801,CellInfo(OPTIONAL,NOCOLOR,"真福尤丽•贝略(童贞诺默圣母会副会祖 Bd. Julia Billiart)")));
        mapPropers.insert(std::make_pair(1040802,CellInfo(OPTIONAL,NOCOLOR,"真福亚松大(Bd. Maria Assunta)")));
        mapPropers.insert(std::make_pair(1040901,CellInfo(OPTIONAL,NOCOLOR,"圣妇华德托蒂(St. Waldetrudis)")));
        mapPropers.insert(std::make_pair(1040902,CellInfo(OPTIONAL,NOCOLOR,"真福欧伯(Bd. Ubald of Florence)")));
        mapPropers.insert(std::make_pair(1041001,CellInfo(OPTIONAL,NOCOLOR,"圣傅培(沙尔德主教 St. Fulbert)")));
        //11日
		mapPropers.insert(std::make_pair(1041101,CellInfo(MEMORIAL,RED,"圣达尼老(主教殉道 St. Stanislaus)")));
        mapPropers.insert(std::make_pair(1041102,CellInfo(OPTIONAL,NOCOLOR,"圣瑰玛•甘甘妮(St. Gemma Galgan)")));
        mapPropers.insert(std::make_pair(1041201,CellInfo(OPTIONAL,NOCOLOR,"圣儒略一世(教宗 St. Julius I)")));
        mapPropers.insert(std::make_pair(1041202,CellInfo(OPTIONAL,NOCOLOR,"圣柴诺(万罗纳主教 St. Zeno)")));
        mapPropers.insert(std::make_pair(1041301,CellInfo(OPTIONAL,NOCOLOR,"圣玛尔定一世(教宗殉道 St. Martin I)")));
        mapPropers.insert(std::make_pair(1041401,CellInfo(OPTIONAL,NOCOLOR,"圣谛步爵、圣华肋廉、圣玛息莫(殉道 Ss. Tiburtius, Valerius and Maxiuss)")));
        mapPropers.insert(std::make_pair(1041402,CellInfo(OPTIONAL,NOCOLOR,"真福李维娜(童贞 Bd. Lydwina of Schiedam)")));
        mapPropers.insert(std::make_pair(1041501,CellInfo(OPTIONAL,NOCOLOR,"圣本笃•若瑟•雷伯(St. Benedict Joseph Labre)")));
        //16日
        mapPropers.insert(std::make_pair(1041601,CellInfo(OPTIONAL,NOCOLOR,"圣女伯尔纳德(St. Bernadette or Mary Bernard Soubinous)")));
        mapPropers.insert(std::make_pair(1041701,CellInfo(OPTIONAL,NOCOLOR,"圣阿尼塞多(教宗殉道 St. Anicetus)")));
        mapPropers.insert(std::make_pair(1041702,CellInfo(OPTIONAL,NOCOLOR,"圣斯德望(西笃修院院长西斯德会副会长 St. Stephen Harding)")));
        mapPropers.insert(std::make_pair(1041801,CellInfo(OPTIONAL,NOCOLOR,"圣加帝诺(米兰总主教 St. Caldinus)")));
        mapPropers.insert(std::make_pair(1041802,CellInfo(OPTIONAL,NOCOLOR,"福女玛利亚(Bd. Mary of the Incarnation)")));
        mapPropers.insert(std::make_pair(1041803,CellInfo(OPTIONAL,NOCOLOR,"圣马塞兰(St. Marcellin Chanmagnat)")));
        mapPropers.insert(std::make_pair(1041901,CellInfo(OPTIONAL,NOCOLOR,"圣良九世(教宗 St. Leo IX. Bruno)")));
        mapPropers.insert(std::make_pair(1041902,CellInfo(OPTIONAL,NOCOLOR,"圣亚斐奇(坎特伯里总主教殉道 St. Alphege)")));
        mapPropers.insert(std::make_pair(1042001,CellInfo(OPTIONAL,NOCOLOR,"圣女依搦斯•蒙德波(童贞 St. Agnes of Montepulciano)")));
        //21日
        mapPropers.insert(std::make_pair(1042101,CellInfo(OPTIONAL,NOCOLOR,"圣安色莫(坎特伯里总主教圣师 St. Anseln)")));
        mapPropers.insert(std::make_pair(1042201,CellInfo(OPTIONAL,NOCOLOR,"圣索台禄(教宗殉道 St. Soter)")));
        mapPropers.insert(std::make_pair(1042202,CellInfo(OPTIONAL,NOCOLOR,"圣爱比巴巨、圣亚历山大(殉道 Ss. Epipodius and Alexander)")));
        mapPropers.insert(std::make_pair(1042301,CellInfo(OPTIONAL,NOCOLOR,"圣乔治(殉道 St. George)")));
        mapPropers.insert(std::make_pair(1042302,CellInfo(OPTIONAL,NOCOLOR,"真福吉利(Bd. Giles of Assisi)")));
        mapPropers.insert(std::make_pair(1042401,CellInfo(OPTIONAL,NOCOLOR,"圣斐德(圣斐德理 St. Fidelis of Sigmaringen)")));
        mapPropers.insert(std::make_pair(1042402,CellInfo(OPTIONAL,NOCOLOR,"圣女贝莱蒂(童贞善牧仁爱圣母会会祖 St. Pelletier)")));
		mapPropers.insert(std::make_pair(1042501,CellInfo(FEAST,RED,"圣马尔谷(St. Mark)")));
        //26日
        mapPropers.insert(std::make_pair(1042601,CellInfo(OPTIONAL,NOCOLOR,"圣格肋多(殉道 St. Cletus)")));
        mapPropers.insert(std::make_pair(1042602,CellInfo(OPTIONAL,NOCOLOR,"圣女方佳(童贞女修院院长 St. Franca of Piacenza)")));
        mapPropers.insert(std::make_pair(1042701,CellInfo(OPTIONAL,NOCOLOR,"圣女纪达(童贞 St. Zita)")));
        mapPropers.insert(std::make_pair(1042801,CellInfo(OPTIONAL,NOCOLOR,"圣葛利农(St. Louis Mary Grignion of Monffort)")));
        mapPropers.insert(std::make_pair(1042802,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•尚纳神父(殉道 St. Peter Mary Chanel)")));
        mapPropers.insert(std::make_pair(1042901,CellInfo(MEMORIAL,WHITE,"圣女加大利纳•仙娜(童贞圣师 St. Catherine of Siena)")));
        mapPropers.insert(std::make_pair(1042902,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•高登伦哥(St. Joseph Cottolengo)")));
		mapPropers.insert(std::make_pair(1043001,CellInfo(OPTIONAL,NOCOLOR,"圣比约五世(教宗 Pius V Michele Ghislieril)")));
        
		/***************5月***************/
        //1日
        mapPropers.insert(std::make_pair(1050101,CellInfo(MEMORIAL,WHITE,"大圣若瑟劳工主保(St. Joseph the Worker)")));
        mapPropers.insert(std::make_pair(1050102,CellInfo(OPTIONAL,NOCOLOR,"圣亚玛多(St. Amator)")));
        mapPropers.insert(std::make_pair(1050201,CellInfo(MEMORIAL,WHITE,"圣亚大纳削(St. Athanasius)")));
        mapPropers.insert(std::make_pair(1050202,CellInfo(OPTIONAL,NOCOLOR,"圣女维芭达(童贞殉道 St. Wibada)")));
        mapPropers.insert(std::make_pair(1050301,CellInfo(FEAST,RED,"圣斐理伯、圣雅各伯宗徒(Ss. Philip and James)")));
        mapPropers.insert(std::make_pair(1050401,CellInfo(OPTIONAL,NOCOLOR,"圣福里安(殉道 St. Florian)")));
        mapPropers.insert(std::make_pair(1050402,CellInfo(OPTIONAL,NOCOLOR,"英格兰和威尔士殉道烈士(the Martyrs of England and Wales)")));
        mapPropers.insert(std::make_pair(1050501,CellInfo(OPTIONAL,NOCOLOR,"圣安日洛(殉道 St. Angelo)")));
        //6日
        mapPropers.insert(std::make_pair(1050601,CellInfo(OPTIONAL,NOCOLOR,"圣若望宗徒拉丁门前受鼎镬刑(St. John Before the Latin Gate)")));
        mapPropers.insert(std::make_pair(1050602,CellInfo(OPTIONAL,NOCOLOR,"圣多明我•沙维豪(St. Donfinic Savio)")));
        mapPropers.insert(std::make_pair(1050701,CellInfo(OPTIONAL,NOCOLOR,"圣若望•比华力(St. John of Beverley)")));
        mapPropers.insert(std::make_pair(1050702,CellInfo(OPTIONAL,NOCOLOR,"真福罗撒(童贞 Bd. Rose Venerini)")));
        mapPropers.insert(std::make_pair(1050801,CellInfo(OPTIONAL,NOCOLOR,"圣波尼法爵四世(St. Boniface IV)")));
        mapPropers.insert(std::make_pair(1050802,CellInfo(OPTIONAL,NOCOLOR,"圣女玛达肋纳•嘉诺撒(St. Magdalen Di Canossa)")));
        mapPropers.insert(std::make_pair(1050803,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄(戴郎旦主教 St. Peter)")));
        mapPropers.insert(std::make_pair(1050901,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•诺拉谷(玛利亚赎虏会 St. Peter Nolasco)")));
        mapPropers.insert(std::make_pair(1051001,CellInfo(OPTIONAL,NOCOLOR,"圣安多宁(佛罗伦萨总主教 St. Antoninus)")));
        mapPropers.insert(std::make_pair(1051002,CellInfo(OPTIONAL,NOCOLOR,"圣若望•亚维拉(St. John of Avila)")));
        //11日
        mapPropers.insert(std::make_pair(1051101,CellInfo(OPTIONAL,NOCOLOR,"圣依纳爵•雷可尼(St. Ignatius of Laconi)")));
        mapPropers.insert(std::make_pair(1051102,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•基罗拉莫(St. Francis Di Girolamo)")));
        mapPropers.insert(std::make_pair(1051201,CellInfo(OPTIONAL,NOCOLOR,"圣乃仁、圣亚启略、圣女多弥谛拉(Ss. Nereus, Achilleus and Domitilla)")));
        mapPropers.insert(std::make_pair(1051202,CellInfo(OPTIONAL,NOCOLOR,"圣邦康(St. Pancras)")));
        mapPropers.insert(std::make_pair(1051301,CellInfo(MEMORIAL,WHITE,"法蒂玛圣母(Our Lady of Fatima)")));
        mapPropers.insert(std::make_pair(1051302,CellInfo(OPTIONAL,NOCOLOR,"圣玛利亚•玛萨利洛(母佑会副会祖 St. Mary Mazzarello)")));
        mapPropers.insert(std::make_pair(1051401,CellInfo(FEAST,RED,"圣玛弟亚宗徒(St. Matthias)")));
        mapPropers.insert(std::make_pair(1051402,CellInfo(OPTIONAL,NOCOLOR,"圣弥额尔•加利古(白太林圣心司铎会会祖 St. Michael Garicoits)")));
        mapPropers.insert(std::make_pair(1051501,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄和圣刁尼霞(殉道者 Ss. Peter and Dionysia)")));
        //16日
        mapPropers.insert(std::make_pair(1051601,CellInfo(OPTIONAL,NOCOLOR,"圣西满•斯道克(St. Simon Stock)")));
        mapPropers.insert(std::make_pair(1051602,CellInfo(OPTIONAL,NOCOLOR,"圣吴巴多(古比奥主教 St. Ubald)")));
        mapPropers.insert(std::make_pair(1051701,CellInfo(OPTIONAL,NOCOLOR,"圣巴斯卦(St. Paschal Baylon)")));
        mapPropers.insert(std::make_pair(1051801,CellInfo(OPTIONAL,NOCOLOR,"圣若望一世(教宗殉道 St. John I)")));
        mapPropers.insert(std::make_pair(1051802,CellInfo(OPTIONAL,NOCOLOR,"圣斐理斯(St. Felix Cantalice)")));
        mapPropers.insert(std::make_pair(1051901,CellInfo(OPTIONAL,NOCOLOR,"圣塞来斯定五世(教宗 St. Celestine V)")));
        mapPropers.insert(std::make_pair(1051902,CellInfo(OPTIONAL,NOCOLOR,"真福奥斯定•诺未洛(Bd. Augustine Novello)")));
        mapPropers.insert(std::make_pair(1052001,CellInfo(OPTIONAL,NOCOLOR,"圣伯尔纳定•栖亚那(St. Bernardine of Siena)")));
        mapPropers.insert(std::make_pair(1052002,CellInfo(OPTIONAL,NOCOLOR,"真福高隆巴(童贞 Bd. Columba of Rieti)")));
        //21日
        mapPropers.insert(std::make_pair(1052101,CellInfo(OPTIONAL,NOCOLOR,"圣维克多(殉道 St. Victor of Marseilles)")));
        mapPropers.insert(std::make_pair(1052201,CellInfo(OPTIONAL,NOCOLOR,"圣妇丽达(St. Rita of Cascia)")));
        mapPropers.insert(std::make_pair(1052202,CellInfo(OPTIONAL,NOCOLOR,"福女若基玛(加尔默罗会祖 Bd. Joachima de Mas de Veruna)")));
        mapPropers.insert(std::make_pair(1052301,CellInfo(OPTIONAL,NOCOLOR,"圣若翰•路西(St. John Baptist Rossi)")));
        mapPropers.insert(std::make_pair(1052401,CellInfo(FEAST,WHITE,"圣母进教之佑节(Our Lady Help of Christians)")));
        mapPropers.insert(std::make_pair(1052402,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵•雷冷(St. Vincent of Lerins)")));
        mapPropers.insert(std::make_pair(1052501,CellInfo(OPTIONAL,NOCOLOR,"圣伯达(圣师 St. Bede the Venerable)")));
        mapPropers.insert(std::make_pair(1052502,CellInfo(OPTIONAL,NOCOLOR,"圣额我略七世教宗(St. Gregory VII)")));
        mapPropers.insert(std::make_pair(1052503,CellInfo(OPTIONAL,NOCOLOR,"圣玛达肋纳•沙斐•亚巴拉(童贞圣心女修会会祖 St. Madeleine Sophie Barat)")));
        //26日
        mapPropers.insert(std::make_pair(1052601,CellInfo(MEMORIAL,WHITE,"圣斐理伯•内利(斐理•乃立 St. Philip Neri)")));
        mapPropers.insert(std::make_pair(1052701,CellInfo(OPTIONAL,NOCOLOR,"圣奥斯定(坎特伯里总主教 St. Augustine)")));
        mapPropers.insert(std::make_pair(1052801,CellInfo(OPTIONAL,NOCOLOR,"圣日曼诺斯(巴黎主教 St. Gemanus)")));
        mapPropers.insert(std::make_pair(1052802,CellInfo(OPTIONAL,NOCOLOR,"真福多默•福特及其他殉道烈士(Bd. Thomas Ford and his Campanions)")));
        mapPropers.insert(std::make_pair(1052901,CellInfo(OPTIONAL,NOCOLOR,"圣济利禄•凯撒利亚(殉道 St. Cyril of Caesarea)")));
        mapPropers.insert(std::make_pair(1052902,CellInfo(MEMORIAL,WHITE,"圣保禄六世(教宗 St. Paul VI)")));
        mapPropers.insert(std::make_pair(1053001,CellInfo(OPTIONAL,NOCOLOR,"圣女贞德(童贞 St. Joan of Arc)")));
        mapPropers.insert(std::make_pair(1053101,CellInfo(FEAST,WHITE,"圣母访亲(the Vistation of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1053102,CellInfo(OPTIONAL,NOCOLOR,"圣母诸宠中保及中华圣母节(Our Lady of all Graces and Queen of China)")));
        
        /*************6月***************/
		//1日
        mapPropers.insert(std::make_pair(1060101,CellInfo(MEMORIAL,RED,"圣犹思定殉道(St. Justin)")));
        mapPropers.insert(std::make_pair(1060102,CellInfo(OPTIONAL,NOCOLOR,"日本殉道烈士(The Martyrs of Japan, II)")));
        mapPropers.insert(std::make_pair(1060201,CellInfo(OPTIONAL,NOCOLOR,"圣玛策林、圣伯多禄(殉道 Ss. Marcellinus and Peter)")));
        mapPropers.insert(std::make_pair(1060202,CellInfo(OPTIONAL,NOCOLOR,"里昂及维安殉道烈士(St. Pothinus and his Companions, the Martyrs of Lyons and Vienne)")));
        mapPropers.insert(std::make_pair(1060301,CellInfo(MEMORIAL,RED,"圣嘉禄•卢安加及同伴(St. Charles Lwanga and Companions)")));
        mapPropers.insert(std::make_pair(1060302,CellInfo(OPTIONAL,NOCOLOR,"圣基文(根巴度院长 St. Kevin)")));
        mapPropers.insert(std::make_pair(1060401,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•加辣巧洛(末位神职界修会会祖 St. Francis Caracciolo)")));
        mapPropers.insert(std::make_pair(1060402,CellInfo(OPTIONAL,NOCOLOR,"圣达米盎(St. Damian)")));
        mapPropers.insert(std::make_pair(1060501,CellInfo(MEMORIAL,RED,"圣波尼法爵(圣博义总主教殉道 St. Boniface)")));
        //6日
        mapPropers.insert(std::make_pair(1060601,CellInfo(OPTIONAL,NOCOLOR,"圣诺贝特(诺博马德堡总主教 波利荣拉登修会会祖 St. Norbert)")));
        mapPropers.insert(std::make_pair(1060701,CellInfo(OPTIONAL,NOCOLOR,"可敬多默•坎比斯(Ven. Thomas A Kenpis)")));
        mapPropers.insert(std::make_pair(1060702,CellInfo(OPTIONAL,NOCOLOR,"真福巴蒂斯达•华拉妮(Bd. Baptista Varani)")));
        mapPropers.insert(std::make_pair(1060703,CellInfo(OPTIONAL,NOCOLOR,"圣罗拔(纽明特院长 St. Robert)")));
        mapPropers.insert(std::make_pair(1060801,CellInfo(OPTIONAL,NOCOLOR,"圣迈达(万孟杜主教 St. Medard)")));
        mapPropers.insert(std::make_pair(1060802,CellInfo(OPTIONAL,NOCOLOR,"圣克路多(梅兹主教 St. Clodulf)")));
        mapPropers.insert(std::make_pair(1060901,CellInfo(OPTIONAL,NOCOLOR,"圣爱弗冷(圣师 St. Ephraem)")));
        mapPropers.insert(std::make_pair(1060902,CellInfo(OPTIONAL,NOCOLOR,"圣高隆巴(约纳院长 St. Columba)")));
        mapPropers.insert(std::make_pair(1060903,CellInfo(OPTIONAL,NOCOLOR,"真福亚纳•玛利亚•泰琪(Bd. Anne Mary Taigi)")));
        mapPropers.insert(std::make_pair(1061001,CellInfo(OPTIONAL,NOCOLOR,"圣日多列和殉道烈士(Ss. Getulius and his Companions)")));
        //11日
        mapPropers.insert(std::make_pair(1061101,CellInfo(FEAST,RED,"圣巴尔纳伯(宗徒 St. Barnabas)")));
        mapPropers.insert(std::make_pair(1061102,CellInfo(OPTIONAL,NOCOLOR,"真福宝拉(童贞圣多罗珊女修会会祖 Bd. Paula Frassinetti)")));
        mapPropers.insert(std::make_pair(1061201,CellInfo(OPTIONAL,NOCOLOR,"圣若望•瑟哈公(St. John of Sahagun)")));
        mapPropers.insert(std::make_pair(1061202,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄(St. Peter of Mount Athos)")));
        mapPropers.insert(std::make_pair(1061301,CellInfo(MEMORIAL,WHITE,"圣安多尼(圣师 St. Antony of Padua)")));
        mapPropers.insert(std::make_pair(1061401,CellInfo(OPTIONAL,NOCOLOR,"圣梅多田(君士坦丁堡宗主教 St. Methodius I of Constantinople)")));
        mapPropers.insert(std::make_pair(1061501,CellInfo(OPTIONAL,NOCOLOR,"圣女任曼娜(童贞 St. Germaine Cousin)")));
        mapPropers.insert(std::make_pair(1061502,CellInfo(OPTIONAL,NOCOLOR,"圣女亚兰弟(童贞 St. Aleydis)")));
        //16日
        mapPropers.insert(std::make_pair(1061601,CellInfo(OPTIONAL,NOCOLOR,"圣若望•方济各•雷奇(St. John Francis Regis)")));
        mapPropers.insert(std::make_pair(1061602,CellInfo(OPTIONAL,NOCOLOR,"圣女吕佳田(童贞 St. Lutgardis)")));
        mapPropers.insert(std::make_pair(1061701,CellInfo(OPTIONAL,NOCOLOR,"圣尼冈德、圣马星(殉道 Ss. Nicander and Marcian)")));
        mapPropers.insert(std::make_pair(1061702,CellInfo(OPTIONAL,NOCOLOR,"圣女爱弥丽(童贞“天神显现”若瑟女修会会祖 St. Emily de Vialar)")));
        mapPropers.insert(std::make_pair(1061801,CellInfo(OPTIONAL,NOCOLOR,"圣马尔谷、圣玛策廉(殉道 Ss. Mark and MareeUian)")));
        mapPropers.insert(std::make_pair(1061802,CellInfo(OPTIONAL,NOCOLOR,"圣女依撒伯尔•许诺(童贞 St. Elizabeth of Schonau)")));
        mapPropers.insert(std::make_pair(1061803,CellInfo(OPTIONAL,NOCOLOR,"圣额我略•巴巴里果(枢机主教 St. Gregory Barbarigo)")));
        mapPropers.insert(std::make_pair(1061901,CellInfo(OPTIONAL,NOCOLOR,"圣罗慕铎(院长卡马尔修会会祖 St. Romuald)")));
        mapPropers.insert(std::make_pair(1061902,CellInfo(OPTIONAL,NOCOLOR,"圣伯吕诺(主教殉道 St. Bruno)")));
        mapPropers.insert(std::make_pair(1062001,CellInfo(OPTIONAL,NOCOLOR,"圣西尔物留(教宗殉道 St. Silverius)")));
        mapPropers.insert(std::make_pair(1062002,CellInfo(OPTIONAL,NOCOLOR,"真福米凯琳(Bd. Michelina of Pesaro)")));
        //21日
        mapPropers.insert(std::make_pair(1062101,CellInfo(MEMORIAL,WHITE,"圣类思•公撒格(St. Aloysius)")));
        mapPropers.insert(std::make_pair(1062102,CellInfo(OPTIONAL,NOCOLOR,"圣欧瑟伯(主教 St. Eusebius of Samoasta)")));
        mapPropers.insert(std::make_pair(1062201,CellInfo(OPTIONAL,NOCOLOR,"圣保林(诺拉主教 St. Paulinus of Nola)")));
        mapPropers.insert(std::make_pair(1062202,CellInfo(OPTIONAL,NOCOLOR,"圣若望•费生(主教枢机 St. John Fisher)")));
        mapPropers.insert(std::make_pair(1062203,CellInfo(OPTIONAL,NOCOLOR,"圣多默•莫尔(殉道 St. Thomas More)")));
        mapPropers.insert(std::make_pair(1062301,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•嘉法沙(St. Joseph Cafasso)")));
        mapPropers.insert(std::make_pair(1062401,CellInfo(LORD,WHITE,"圣若翰洗者诞辰(The Birthday of St. John the Baptist)")));
        mapPropers.insert(std::make_pair(1062501,CellInfo(OPTIONAL,NOCOLOR,"圣威廉•维吉尔(维吉尔修院院长 St. William of Monte Vergine)")));
        mapPropers.insert(std::make_pair(1062502,CellInfo(OPTIONAL,NOCOLOR,"圣女佛波罗尼(童贞殉道 St. Febronia)")));
        //26日
        mapPropers.insert(std::make_pair(1062601,CellInfo(OPTIONAL,NOCOLOR,"圣安德莫(比利主教 St. Anthelm)")));
        mapPropers.insert(std::make_pair(1062602,CellInfo(MEMORIAL,WHITE,"圣施礼华(司铎 St. Josemaria)")));
        mapPropers.insert(std::make_pair(1062701,CellInfo(OPTIONAL,NOCOLOR,"圣济利禄(亚历山大主教圣师 St. Cyril)")));
        mapPropers.insert(std::make_pair(1062801,CellInfo(MEMORIAL,RED,"圣依勒内(里昂主教殉道 St. Irenaeus)")));
        mapPropers.insert(std::make_pair(1062802,CellInfo(OPTIONAL,NOCOLOR,"圣波罗德格、圣波太米诺及其他殉道烈士(Ss. Blutarch Potamiaena and their Companions)")));
        mapPropers.insert(std::make_pair(1062901,CellInfo(SOLEMNITY,RED,"圣伯多禄及圣保禄宗徒(St. Peter Apostle & St. Paul Apostle)")));
		mapPropers.insert(std::make_pair(1063001,CellInfo(MEMORIAL,RED,"罗马第一批殉道烈士(Martyrs of Rome, I)")));
    
		/*************7月**************/
        //1日
        mapPropers.insert(std::make_pair(1070101,CellInfo(OPTIONAL,NOCOLOR,"圣珈尔(克来门主教 St. Gall)")));
        mapPropers.insert(std::make_pair(1070102,CellInfo(OPTIONAL,NOCOLOR,"真福多默•李斯斐(Bd. Thomas Maxfield)")));
        mapPropers.insert(std::make_pair(1070201,CellInfo(OPTIONAL,NOCOLOR,"圣博策稣、圣玛谛酿(殉道 Ss. Processus and Martinian)")));
        mapPropers.insert(std::make_pair(1070202,CellInfo(OPTIONAL,NOCOLOR,"圣奥多(彭伯主教 St. Otto)")));
        mapPropers.insert(std::make_pair(1070301,CellInfo(FEAST,RED,"圣多默(宗徒 St. Thomas the Apostle)")));
        mapPropers.insert(std::make_pair(1070401,CellInfo(MEMORIAL,WHITE,"圣妇依撒伯尔(St. Elizabeth of Portuga)")));
        mapPropers.insert(std::make_pair(1070501,CellInfo(OPTIONAL,NOCOLOR,"圣安多尼•匝加利(圣保禄神职修会创办人 St. Antony Zaccaria)")));
        //6日
        mapPropers.insert(std::make_pair(1070601,CellInfo(OPTIONAL,NOCOLOR,"高兰蒂•玛利亚(童贞殉道 St. Maria Goretti)")));
        mapPropers.insert(std::make_pair(1070701,CellInfo(OPTIONAL,NOCOLOR,"圣庞德诺(St. Pantaenus)")));
        mapPropers.insert(std::make_pair(1070801,CellInfo(OPTIONAL,NOCOLOR,"圣艾士波和卓娅(殉道 Ss. Hesperus and Zoa-135)")));
        mapPropers.insert(std::make_pair(1070901,CellInfo(FEAST,RED,"中华诸圣及真福(The Martyrs of China)")));
        mapPropers.insert(std::make_pair(1070902,CellInfo(OPTIONAL,NOCOLOR,"圣尼各老•比克及其它殉道烈士(Ss. Nicholas Pieck and his Companions)")));
        mapPropers.insert(std::make_pair(1070903,CellInfo(OPTIONAL,NOCOLOR,"圣女万罗尼加•祁拉尼(童贞 St. Veronica Giuliani)")));
        mapPropers.insert(std::make_pair(1071001,CellInfo(OPTIONAL,NOCOLOR,"七位圣昆仲(殉道 the Seven Brothers and St. Feheity)")));
        //11日
        mapPropers.insert(std::make_pair(1071101,CellInfo(MEMORIAL,WHITE,"圣本笃(院长 St. Benedict 480-547)")));
        mapPropers.insert(std::make_pair(1071201,CellInfo(OPTIONAL,NOCOLOR,"越南殉道烈士(the Martyrs of Indo-China, I)")));
        mapPropers.insert(std::make_pair(1071301,CellInfo(OPTIONAL,NOCOLOR,"圣亨利二世(St. Henry II)")));
        mapPropers.insert(std::make_pair(1071302,CellInfo(OPTIONAL,NOCOLOR,"圣息拉(St. Silas)")));
        mapPropers.insert(std::make_pair(1071303,CellInfo(OPTIONAL,NOCOLOR,"圣欧杰(迦太基主教 St. Eugenius-505)")));
        mapPropers.insert(std::make_pair(1071401,CellInfo(OPTIONAL,NOCOLOR,"圣加弥禄(灵医会创办人 St. Camillus De Lellis)")));
        mapPropers.insert(std::make_pair(1071501,CellInfo(MEMORIAL,WHITE,"圣文都辣(St. Bonaventure)")));
        mapPropers.insert(std::make_pair(1071502,CellInfo(OPTIONAL,NOCOLOR,"圣亚大纳削(那不勒斯主教 St. Athanasius)")));
        //16日
        mapPropers.insert(std::make_pair(1071601,CellInfo(MEMORIAL,WHITE,"加尔默罗圣母(The Commemoration of Our Lady of Mount Carmel)")));
        mapPropers.insert(std::make_pair(1071602,CellInfo(OPTIONAL,NOCOLOR,"圣女玛利亚•玛达肋纳•巴斯德(St. Mary Magdalem Postel)")));
        mapPropers.insert(std::make_pair(1071701,CellInfo(OPTIONAL,NOCOLOR,"圣亚肋叔(St. Alexius)")));
        mapPropers.insert(std::make_pair(1071702,CellInfo(OPTIONAL,NOCOLOR,"圣女玛珊利纳(St. Marcellina)")));
        mapPropers.insert(std::make_pair(1071801,CellInfo(OPTIONAL,NOCOLOR,"圣威德廉(乌德莱主教殉道 St. Frederick)")));
        mapPropers.insert(std::make_pair(1071901,CellInfo(OPTIONAL,NOCOLOR,"圣女儒斯大、圣妇卢菲娜(Ss. Justa and Rufina)")));
        mapPropers.insert(std::make_pair(1071902,CellInfo(OPTIONAL,NOCOLOR,"圣亚赛热(St. Arsenius the Great-450)")));
        mapPropers.insert(std::make_pair(1072001,CellInfo(OPTIONAL,NOCOLOR,"圣厄利亚(耶路撒冷宗主教)和圣法来文(Ss. Elias and Flavian)")));
        mapPropers.insert(std::make_pair(1072002,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•巴尔撒巴(St. Joseph Barsabas)")));
        //21日
        mapPropers.insert(std::make_pair(1072101,CellInfo(OPTIONAL,NOCOLOR,"圣炳德西(St. Laurence of Brindisi)")));
        mapPropers.insert(std::make_pair(1072201,CellInfo(FEAST,WHITE,"圣女玛利亚•玛达肋纳(圣徳莲 St. Mary Magdalen)")));
        mapPropers.insert(std::make_pair(1072202,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•巴勒斯坦(St. Joseph of Palestine)")));
        mapPropers.insert(std::make_pair(1072301,CellInfo(OPTIONAL,NOCOLOR,"圣妇彼利日大(救世主会创始人 St. Bridget)")));
        mapPropers.insert(std::make_pair(1072401,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•沙拉纳(St. Francis Salasno)")));
        mapPropers.insert(std::make_pair(1072402,CellInfo(OPTIONAL,NOCOLOR,"圣女克利斯蒂娜(童贞 St. Christina the Astonishing)")));
        mapPropers.insert(std::make_pair(1072501,CellInfo(FEAST,RED,"圣长雅各伯宗徒(St. James the Greater)")));
        mapPropers.insert(std::make_pair(1072502,CellInfo(OPTIONAL,NOCOLOR,"圣基多福(殉道 St. Christopher)")));
        //26日
        mapPropers.insert(std::make_pair(1072601,CellInfo(MEMORIAL,WHITE,"圣妇亚纳及若亚敬(St. Anne & St. Joachim)")));
        mapPropers.insert(std::make_pair(1072602,CellInfo(OPTIONAL,NOCOLOR,"圣女亚加比大日(童贞路物仁爱女修会副会祖 St. Bartholomea Capitanio-1833)")));
        mapPropers.insert(std::make_pair(1072701,CellInfo(OPTIONAL,NOCOLOR,"圣依诺增爵一世(教宗 St. Innocent I)")));
        mapPropers.insert(std::make_pair(1072702,CellInfo(OPTIONAL,NOCOLOR,"圣庞大良(殉道 St. Pantaleon)")));
        mapPropers.insert(std::make_pair(1072801,CellInfo(OPTIONAL,NOCOLOR,"真福亚尔丰索(童贞 Bd. Alphonsa Muttathupadathu 1910-1946)")));
        mapPropers.insert(std::make_pair(1072901,CellInfo(MEMORIAL,WHITE,"圣玛尔大、圣玛利亚及圣拉匝禄(St. Martha, Mary and Lazarus)")));
        mapPropers.insert(std::make_pair(1073001,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄金言(辣未纳总主教圣师 St. Peter Chrysologus)")));
        mapPropers.insert(std::make_pair(1073002,CellInfo(OPTIONAL,NOCOLOR,"真福伯多禄•玛格里诺(Bd. Peter of Mogliano)")));
        mapPropers.insert(std::make_pair(1073101,CellInfo(MEMORIAL,WHITE,"圣依纳爵•罗耀拉(耶稣会会祖圣纳爵 St. Ignatius of Loyola)")));
        mapPropers.insert(std::make_pair(1073102,CellInfo(OPTIONAL,NOCOLOR,"真福儒斯定(尼洛波利主教 Bd. Justin de Jacobis)")));
		/**************8月************/
        //1日
        mapPropers.insert(std::make_pair(1080101,CellInfo(MEMORIAL,WHITE,"圣亚尔丰索(主教圣师赎世主会会祖 St. Alphonsus de Liguori)")));
        mapPropers.insert(std::make_pair(1080201,CellInfo(OPTIONAL,NOCOLOR,"圣欧瑟伯(凡尔则里主教 St. Eusebius of Vencelli)")));
        mapPropers.insert(std::make_pair(1080301,CellInfo(OPTIONAL,NOCOLOR,"圣华旦(梅洛士院长 St. Waltheof -1160)")));
        mapPropers.insert(std::make_pair(1080302,CellInfo(OPTIONAL,NOCOLOR,"真福伯多禄•儒里安•爱麦(至圣圣体修会会祖 Bd. Peter Julian Eymard)")));
        mapPropers.insert(std::make_pair(1080401,CellInfo(MEMORIAL,WHITE,"圣若翰•维雅纳(St. John Vianney)")));
        mapPropers.insert(std::make_pair(1080501,CellInfo(MEMORIAL,WHITE,"罗马圣母大殿奉献日(The Dedication of the Basilica of St. Mary Major)")));
        mapPropers.insert(std::make_pair(1080502,CellInfo(OPTIONAL,NOCOLOR,"圣妇亚勿拉(殉道 St. Afra -304)")));
        //6日
		mapPropers.insert(std::make_pair(1080601,CellInfo(LORD,WHITE,"耶稣显圣容(The Transfiguration of Our Lord Jesus Christ)")));
        mapPropers.insert(std::make_pair(1080701,CellInfo(OPTIONAL,NOCOLOR,"圣西斯督二世(教宗殉道 St. Sixtus II)")));
        mapPropers.insert(std::make_pair(1080702,CellInfo(OPTIONAL,NOCOLOR,"圣加耶当(神职界修会副会祖 St. Cajetan)")));
        mapPropers.insert(std::make_pair(1080801,CellInfo(MEMORIAL,WHITE,"圣多明我(多明我会会祖 St. Dominic)")));
        mapPropers.insert(std::make_pair(1080901,CellInfo(OPTIONAL,NOCOLOR,"圣奥斯华(殉道 St. Oswald of Northumbria)")));
        mapPropers.insert(std::make_pair(1080902,CellInfo(OPTIONAL,NOCOLOR,"真福若望•沙肋诺(Bd. John of Salerno 1190-1242)")));
        mapPropers.insert(std::make_pair(1081001,CellInfo(FEAST,RED,"圣老楞佐(殉道 St. Laurence)")));
        mapPropers.insert(std::make_pair(1081002,CellInfo(OPTIONAL,NOCOLOR,"圣女菲洛美娜(St. Philomena)")));
        //11日
        mapPropers.insert(std::make_pair(1081101,CellInfo(MEMORIAL,WHITE,"圣女加辣(加辣会创办人 St. Clare)")));
        mapPropers.insert(std::make_pair(1081102,CellInfo(OPTIONAL,NOCOLOR,"真福伯多禄•法华(Bd. Peter Favre)")));
        mapPropers.insert(std::make_pair(1081201,CellInfo(OPTIONAL,NOCOLOR,"圣慕达(St. Murtagh)")));
        mapPropers.insert(std::make_pair(1081301,CellInfo(OPTIONAL,NOCOLOR,"圣依玻里多和圣彭谦(殉道 Ss. Hippolytus and Ponlianus)")));
        mapPropers.insert(std::make_pair(1081302,CellInfo(OPTIONAL,NOCOLOR,"圣贝尼杜(St. Benildus)")));
        mapPropers.insert(std::make_pair(1081401,CellInfo(OPTIONAL,NOCOLOR,"真福安多尼毕马田和伙伴(殉道 Bb. Antony Primaldi and other Martyrs)")));
        mapPropers.insert(std::make_pair(1081402,CellInfo(MEMORIAL,RED,"圣高比司铎(殉道 St. Maximilian Kolbe, Priest and Martyr)")));
        mapPropers.insert(std::make_pair(1081403,CellInfo(FEAST,WHITE,"圣母升天节前夕")));
        mapPropers.insert(std::make_pair(1081501,CellInfo(SOLEMNITY,WHITE,"圣母升天节(The Assumption of the Blessed Virgin Mary)")));
        //16日
        mapPropers.insert(std::make_pair(1081601,CellInfo(OPTIONAL,NOCOLOR,"圣斯德望国王(St. Stephen of Hungary)")));
        mapPropers.insert(std::make_pair(1081602,CellInfo(OPTIONAL,NOCOLOR,"圣洛克(St. Rock)")));
        mapPropers.insert(std::make_pair(1081701,CellInfo(OPTIONAL,NOCOLOR,"圣雅钦多(St. Hyachinth)")));
        mapPropers.insert(std::make_pair(1081702,CellInfo(OPTIONAL,NOCOLOR,"真福若翰纳•德拉诺(圣亚纳创办人 Bd. Joan Delanoue)")));
        mapPropers.insert(std::make_pair(1081801,CellInfo(OPTIONAL,NOCOLOR,"圣妇海伦(St. Helen -330)")));
        mapPropers.insert(std::make_pair(1081802,CellInfo(OPTIONAL,NOCOLOR,"圣亚尔比(St. Alipius)")));
        mapPropers.insert(std::make_pair(1081803,CellInfo(OPTIONAL,NOCOLOR,"真福白亚蒂斯(童贞圣母无原罪始胎会创办人 Bd. Beatrice da Silva)")));
        mapPropers.insert(std::make_pair(1081901,CellInfo(OPTIONAL,NOCOLOR,"圣若望•欧德(耶稣圣母会及仁爱圣母会创办人 St. John Eudes)")));
        mapPropers.insert(std::make_pair(1081902,CellInfo(OPTIONAL,NOCOLOR,"圣路易•安日(都鲁士主教 St. Louis of Anjou)")));
        mapPropers.insert(std::make_pair(1082001,CellInfo(MEMORIAL,WHITE,"圣伯尔纳铎(格来福院长圣师 St. Bernard)")));
        mapPropers.insert(std::make_pair(1082002,CellInfo(OPTIONAL,NOCOLOR,"真福玛利亚•德玛帝亚(童贞宝血会创办人 Bd. Mary of Mattias)")));
        //21日
        mapPropers.insert(std::make_pair(1082101,CellInfo(MEMORIAL,WHITE,"圣比约十世(教宗 St. Pius X)")));
        mapPropers.insert(std::make_pair(1082201,CellInfo(MEMORIAL,WHITE,"圣母元后(The Queenship of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1082202,CellInfo(OPTIONAL,NOCOLOR,"真福奥撒南(圣云先会创办人 Bd. Ozanet")));
        mapPropers.insert(std::make_pair(1082301,CellInfo(OPTIONAL,NOCOLOR,"圣女罗撒(童贞 St. Rose of Lima)")));
        mapPropers.insert(std::make_pair(1082302,CellInfo(OPTIONAL,NOCOLOR,"圣斐理伯•贝尼谛(St. Philip Benizi)")));
        mapPropers.insert(std::make_pair(1082303,CellInfo(OPTIONAL,NOCOLOR,"圣高洛巨及其同班(Ss. Claudius, Asterius, Neon, Domnina and Theonilla)")));
        mapPropers.insert(std::make_pair(1082401,CellInfo(FEAST,RED,"圣巴尔多禄茂(宗徒 St. Bartholomew)")));
        mapPropers.insert(std::make_pair(1082501,CellInfo(OPTIONAL,NOCOLOR,"圣路易(St. Louis of France)")));
        mapPropers.insert(std::make_pair(1082502,CellInfo(OPTIONAL,NOCOLOR,"圣加拉桑(公学司铎修会创办人 St. Joseph Calasanz)")));
        mapPropers.insert(std::make_pair(1082503,CellInfo(OPTIONAL,NOCOLOR,"圣女玛利亚•弥额拉•谭马西(童贞圣体孝女会创办人 St. Mary Michaela Desmanisieres 1809-1865)")));
        //26日
        mapPropers.insert(std::make_pair(1082601,CellInfo(OPTIONAL,NOCOLOR,"圣女依撒伯尔•皮希亚(童贞十字女修会副创办人 St. Elizabeth Bichier des Ages)")));
        mapPropers.insert(std::make_pair(1082701,CellInfo(MEMORIAL,WHITE,"圣妇莫尼加(St. Monica)")));
        mapPropers.insert(std::make_pair(1082801,CellInfo(MEMORIAL,WHITE,"圣奥斯定(希波主教圣师 St. Augustinei of Hippo)")));
        mapPropers.insert(std::make_pair(1082901,CellInfo(MEMORIAL,RED,"圣若翰洗者蒙难(The Beheading of St. John the Baptist)")));
        mapPropers.insert(std::make_pair(1083001,CellInfo(OPTIONAL,NOCOLOR,"圣斐理、圣亚祷多(殉道 Ss. Felix and Adauctus)")));
        mapPropers.insert(std::make_pair(1083101,CellInfo(OPTIONAL,NOCOLOR,"圣赖孟多•农纳都(枢机 St. Raymund Nonnatus)")));
        mapPropers.insert(std::make_pair(1083102,CellInfo(OPTIONAL,NOCOLOR,"真福儒万纳•安西诺(沙吕查主教 Bd. Juvenal Ancina)")));
		/***************9月*****************/
        //1日
        mapPropers.insert(std::make_pair(1090101,CellInfo(OPTIONAL,NOCOLOR,"圣祺肋(院长 St. Giles)")));
        mapPropers.insert(std::make_pair(1090102,CellInfo(OPTIONAL,NOCOLOR,"圣旦利塞(St. Drithelm)")));
        mapPropers.insert(std::make_pair(1090201,CellInfo(OPTIONAL,NOCOLOR,"圣威廉(洛斯奇主教 St. William of Rokide)")));
        mapPropers.insert(std::make_pair(1090202,CellInfo(OPTIONAL,NOCOLOR,"真福若望狄洛及其他殉道烈士(亚尔斯总主教 Bd. John du Lau and his Companions)")));
        mapPropers.insert(std::make_pair(1090301,CellInfo(MEMORIAL,WHITE,"圣额我略一世(教宗圣师 St. Gregory the Great)")));
        mapPropers.insert(std::make_pair(1090302,CellInfo(OPTIONAL,NOCOLOR,"圣小西默盎“石柱人”(St. Simeon Stylite the Younger)")));
        mapPropers.insert(std::make_pair(1090401,CellInfo(OPTIONAL,NOCOLOR,"圣女罗撒•薇台宝(童贞 St. Rose of Viterbo)")));
        mapPropers.insert(std::make_pair(1090402,CellInfo(OPTIONAL,NOCOLOR,"真福加大利纳•拉谷尼(童贞 Bd. Catherine of Racconigi 1486-1547)")));
        mapPropers.insert(std::make_pair(1090501,CellInfo(OPTIONAL,NOCOLOR,"圣老楞佐•儒斯定(威尼斯宗主教 St. Laurence Giustiniani)")));
        mapPropers.insert(std::make_pair(1090502,CellInfo(MEMORIAL,WHITE,"圣德肋撒·加尔各答(St. Teresa of Calcutta)")));
        //6日
        mapPropers.insert(std::make_pair(1090601,CellInfo(OPTIONAL,NOCOLOR,"圣爱琉德理(院长 St. Eleutherius)")));
        mapPropers.insert(std::make_pair(1090602,CellInfo(OPTIONAL,NOCOLOR,"真福贝脱郎(Bd. Bertrand of Garrigues)")));
        mapPropers.insert(std::make_pair(1090701,CellInfo(OPTIONAL,NOCOLOR,"圣克罗德(St. Cloud)")));
        mapPropers.insert(std::make_pair(1090702,CellInfo(OPTIONAL,NOCOLOR,"真福若望•德盖、赖夫•高比(殉道 Bb. John Duckett and Ralph Corby)")));
        mapPropers.insert(std::make_pair(1090801,CellInfo(FEAST,WHITE,"圣母诞辰(The Birthday of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1090802,CellInfo(OPTIONAL,NOCOLOR,"圣塞尔久一世(教宗 St. Sergius I)")));
        mapPropers.insert(std::make_pair(1090901,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•格肋凡(St. Peter Claver)")));
        mapPropers.insert(std::make_pair(1090902,CellInfo(OPTIONAL,NOCOLOR,"圣依撒格(St. Isaac the Great)")));
        mapPropers.insert(std::make_pair(1091001,CellInfo(OPTIONAL,NOCOLOR,"圣尼各老•多伦定(St. Nicholas of Tolentino)")));
        //11日
        mapPropers.insert(std::make_pair(1091101,CellInfo(OPTIONAL,NOCOLOR,"圣普罗多、圣雅钦多(殉道 Ss. Prtcals & Hvacinth)")));
        mapPropers.insert(std::make_pair(1091102,CellInfo(OPTIONAL,NOCOLOR,"圣彭诺许(主教 St. Paphnutius)")));
        mapPropers.insert(std::make_pair(1091201,CellInfo(MEMORIAL,WHITE,"圣母圣名节(The Holy Name of Mary)")));
        mapPropers.insert(std::make_pair(1091202,CellInfo(OPTIONAL,NOCOLOR,"圣祁•安德烈(St. Guy of Anderlecht)")));
        mapPropers.insert(std::make_pair(1091301,CellInfo(MEMORIAL,WHITE,"金口圣若望(主教圣师 St. John Chrysostom)")));
        mapPropers.insert(std::make_pair(1091302,CellInfo(OPTIONAL,NOCOLOR,"圣欧洛日(亚历山大宗主教 St. Eulogius of Alexandlia)")));
        mapPropers.insert(std::make_pair(1091401,CellInfo(LORD,RED,"光荣十字圣架(The Exaltation of the Holy Cross)")));
        mapPropers.insert(std::make_pair(1091402,CellInfo(OPTIONAL,NOCOLOR,"圣女诺波加(童贞 St. Notburga -1313)")));
        mapPropers.insert(std::make_pair(1091501,CellInfo(MEMORIAL,WHITE,"痛苦圣母(Our Lady of Sorrows)")));
        mapPropers.insert(std::make_pair(1091502,CellInfo(OPTIONAL,NOCOLOR,"圣妇加大利纳•热那亚(St. Catherine of Genoa)")));
        //16日
        mapPropers.insert(std::make_pair(1091601,CellInfo(MEMORIAL,RED,"圣高尔内略及圣西彼廉主教(殉道 St. Cornelius & St. Cyprian)")));
        mapPropers.insert(std::make_pair(1091701,CellInfo(OPTIONAL,NOCOLOR,"圣罗伯多•贝勒明(加菩亚主教枢机圣师 St. Robert Bellarmine)")));
        mapPropers.insert(std::make_pair(1091702,CellInfo(OPTIONAL,NOCOLOR,"圣方济各受五伤痕(The Stigmata of St. Francis)")));
        mapPropers.insert(std::make_pair(1091801,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•古白定(St. Joseph of Cupertino)")));
        mapPropers.insert(std::make_pair(1091901,CellInfo(OPTIONAL,NOCOLOR,"圣雅纳略主教及其他殉道烈士(Ss. Januarius and his Companions)")));
        mapPropers.insert(std::make_pair(1092001,CellInfo(OPTIONAL,NOCOLOR,"圣刁多禄(坎特布里总主教 St. Theodore -690)")));
        mapPropers.insert(std::make_pair(1092002,CellInfo(OPTIONAL,NOCOLOR,"圣爱弥理(童贞圣家女修会创办人 St. Emily de Rodat)")));
        mapPropers.insert(std::make_pair(1092003,CellInfo(MEMORIAL,RED,"圣金大建及同伴殉道(Ss. Andrew Kim Taegon and Companions)")));
        //21日
        mapPropers.insert(std::make_pair(1092101,CellInfo(FEAST,RED,"圣玛窦(宗徒兼圣史 St. Matthew)")));
        mapPropers.insert(std::make_pair(1092201,CellInfo(OPTIONAL,NOCOLOR,"圣多默•威拉诺(总主教 St. Thomas of Villanova)")));
        mapPropers.insert(std::make_pair(1092301,CellInfo(OPTIONAL,NOCOLOR,"圣理诺(教宗殉道 St. Linus)")));
        mapPropers.insert(std::make_pair(1092302,CellInfo(OPTIONAL,NOCOLOR,"圣女德格拉(童贞殉道 St. Thecla of Iconium)")));
        mapPropers.insert(std::make_pair(1092303,CellInfo(MEMORIAL,WHITE,"圣比约•庇特來(司铎 St. Pio of Pietrelcina.)")));
        mapPropers.insert(std::make_pair(1092401,CellInfo(OPTIONAL,NOCOLOR,"圣母赎虏(Our Lady of Ransom)")));
        mapPropers.insert(std::make_pair(1092402,CellInfo(OPTIONAL,NOCOLOR,"圣吉拉(塞纳主教殉道 St. Gerard of Sagredo)")));
        mapPropers.insert(std::make_pair(1092501,CellInfo(OPTIONAL,NOCOLOR,"圣西弗里(威马院长 St. Ceolfrid)")));
        mapPropers.insert(std::make_pair(1092502,CellInfo(OPTIONAL,NOCOLOR,"圣亚尔伯(耶路撒冷宗主教 St. Albert of Jerusalem)")));
        //26日
        mapPropers.insert(std::make_pair(1092601,CellInfo(OPTIONAL,NOCOLOR,"圣葛斯默、圣达弥盎(殉道 Ss. Cosmas and Damian)")));
        mapPropers.insert(std::make_pair(1092701,CellInfo(OPTIONAL,NOCOLOR,"圣爱徐亚(St. Eleazar de Sabran)")));
        mapPropers.insert(std::make_pair(1092702,CellInfo(MEMORIAL,WHITE,"圣味增爵(遣使会和仁爱会创始人 St. Vincent De Paul)")));
        mapPropers.insert(std::make_pair(1092801,CellInfo(OPTIONAL,NOCOLOR,"圣文策老(殉道 St. Wenceslaus of Bohemia)")));
        mapPropers.insert(std::make_pair(1092802,CellInfo(OPTIONAL,NOCOLOR,"圣女欧多钦(童贞 St. Eustochium)")));
        mapPropers.insert(std::make_pair(1092901,CellInfo(FEAST,WHITE,"诸圣天使(圣弥额尔、圣加俾额尔、圣拉法厄尔)")));
        mapPropers.insert(std::make_pair(1093001,CellInfo(MEMORIAL,WHITE,"圣热罗尼莫(圣师 St. Jerome)")));
        /***************10月**************/
        //1日
        mapPropers.insert(std::make_pair(1100101,CellInfo(MEMORIAL,WHITE,"圣女婴孩耶稣德肋撒(St. Terese of Licieux)")));
        mapPropers.insert(std::make_pair(1100201,CellInfo(MEMORIAL,WHITE,"护守天使(The Guardian Angels)")));
        mapPropers.insert(std::make_pair(1100301,CellInfo(OPTIONAL,NOCOLOR,"依华昆仲(殉道 The Two Ewalds -695)")));
        mapPropers.insert(std::make_pair(1100401,CellInfo(MEMORIAL,WHITE,"圣五伤方济各(St. Francis Assisi)")));
        mapPropers.insert(std::make_pair(1100501,CellInfo(MEMORIAL,WHITE,"圣女傅天娜(童贞 St. Faustina)")));
        mapPropers.insert(std::make_pair(1100502,CellInfo(OPTIONAL,NOCOLOR,"圣布拉祺多(殉道 St. Placid)")));
        mapPropers.insert(std::make_pair(1100503,CellInfo(OPTIONAL,NOCOLOR,"圣女福辣(St. Flora of Beaulien)")));
        //6日
        mapPropers.insert(std::make_pair(1100601,CellInfo(OPTIONAL,NOCOLOR,"圣勃路诺(加多森会创办人 St. Bruno)")));
        mapPropers.insert(std::make_pair(1100602,CellInfo(OPTIONAL,NOCOLOR,"圣女玛利亚•方济加(童贞 St. Mary Francesd Naples)")));
        mapPropers.insert(std::make_pair(1100701,CellInfo(MEMORIAL,WHITE,"玫瑰圣母节(Our Lady's Rosary)")));
        mapPropers.insert(std::make_pair(1100801,CellInfo(OPTIONAL,NOCOLOR,"圣塞尔久、圣伯古斯(殉道 Ss. Sergius and Bacchus)")));
        mapPropers.insert(std::make_pair(1100802,CellInfo(OPTIONAL,NOCOLOR,"圣女白兰佳(St. Pelagia the Penitent)")));
        mapPropers.insert(std::make_pair(1100901,CellInfo(OPTIONAL,NOCOLOR,"圣德尼斯(巴黎主教)、圣路帝古、圣爱留德路(殉道 Ss. Denis, Rusticus & Eleutherius)")));
        mapPropers.insert(std::make_pair(1100902,CellInfo(OPTIONAL,NOCOLOR,"圣若望•良纳弟(天主之母会会祖 St. John Leonardi 1543-1609)")));
        mapPropers.insert(std::make_pair(1101001,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•玻尔日亚(St. Francis Borgia)")));
        //11日
        mapPropers.insert(std::make_pair(1101101,CellInfo(OPTIONAL,NOCOLOR,"圣加尼斯(院长 St. Canice)")));
        mapPropers.insert(std::make_pair(1101102,CellInfo(MEMORIAL,NOCOLOR,"圣若望二十三世(教宗 St. John XXIII)")));
        mapPropers.insert(std::make_pair(1101201,CellInfo(OPTIONAL,NOCOLOR,"圣威弗烈(约克主教 St. Wilfrid 709)")));
        mapPropers.insert(std::make_pair(1101301,CellInfo(OPTIONAL,NOCOLOR,"圣爱德华(St. Edward Confessor 1004-1066)")));
        mapPropers.insert(std::make_pair(1101401,CellInfo(OPTIONAL,NOCOLOR,"圣加利斯督(教宗殉道 St. Callistus)")));
        mapPropers.insert(std::make_pair(1101501,CellInfo(MEMORIAL,WHITE,"圣女大德肋撒(童贞 加尔默罗修会改革者 St. Teresa of Avila)")));
        //16日
        mapPropers.insert(std::make_pair(1101601,CellInfo(OPTIONAL,NOCOLOR,"圣妇赫德维(St. Hedwig)")));
        mapPropers.insert(std::make_pair(1101602,CellInfo(OPTIONAL,NOCOLOR,"圣女玛加利大(童贞 St. Margaret Mary)")));
        mapPropers.insert(std::make_pair(1101701,CellInfo(MEMORIAL,RED,"圣依纳爵•安提约基亚(主教殉道 St. Ignatius of Antioch)")));
        mapPropers.insert(std::make_pair(1101801,CellInfo(FEAST,RED,"圣史路加(St. Luke)")));
        mapPropers.insert(std::make_pair(1101901,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•亚刚大辣(St. Peter of Alcantara)")));
        mapPropers.insert(std::make_pair(1101902,CellInfo(OPTIONAL,NOCOLOR,"北美洲殉道烈士(The Martyrs of North America)")));
        mapPropers.insert(std::make_pair(1101903,CellInfo(OPTIONAL,NOCOLOR,"圣十字保禄(苦难会会祖 St. Paul of the Cross 1694-1775)")));
        mapPropers.insert(std::make_pair(1102001,CellInfo(OPTIONAL,NOCOLOR,"圣女贝蒂拉(童贞 St. Bertilla Boscardin)")));
        //21日
        mapPropers.insert(std::make_pair(1102101,CellInfo(OPTIONAL,NOCOLOR,"圣依拉良(St. Hilarion)")));
        mapPropers.insert(std::make_pair(1102201,CellInfo(MEMORIAL,WHITE,"圣若望·保禄二世(教宗 St. John Paul II)")));
        mapPropers.insert(std::make_pair(1102202,CellInfo(OPTIONAL,NOCOLOR,"真福弟茂德•奇嘉多(Bd. Timothy Giocarde 1896-1948)")));
        mapPropers.insert(std::make_pair(1102301,CellInfo(OPTIONAL,NOCOLOR,"圣若望•贾必昌(St. John of Capistrano)")));
        mapPropers.insert(std::make_pair(1102401,CellInfo(OPTIONAL,NOCOLOR,"圣安多尼•加烈(古巴总主教圣母无玷圣心传教会创办人 St. Antony Claret)")));
        mapPropers.insert(std::make_pair(1102501,CellInfo(OPTIONAL,NOCOLOR,"圣克利斯品、圣克利斯毕(殉道 Ss. Crispin and Crispinian)")));
        //26日
        mapPropers.insert(std::make_pair(1102601,CellInfo(OPTIONAL,NOCOLOR,"圣厄瓦理斯多(教宗殉道 St. Evaristus)")));
        mapPropers.insert(std::make_pair(1102701,CellInfo(OPTIONAL,NOCOLOR,"圣福门舒(亚克松主教 St. Frumentius 330-380)")));
        mapPropers.insert(std::make_pair(1102702,CellInfo(OPTIONAL,NOCOLOR,"真福费列尼(Bd. Contardo Ferrini)")));
        mapPropers.insert(std::make_pair(1102801,CellInfo(FEAST,RED,"圣西满、圣达陡(宗徒 Ss. Simon and Jude)")));
        mapPropers.insert(std::make_pair(1102901,CellInfo(OPTIONAL,NOCOLOR,"圣南西苏(耶路撒冷主教 St. Narcissus of Jerusalem -215)")));
        mapPropers.insert(std::make_pair(1103001,CellInfo(OPTIONAL,NOCOLOR,"圣玛塞洛(殉道 St. Marcellus the Cenlurion)")));
        mapPropers.insert(std::make_pair(1103002,CellInfo(OPTIONAL,NOCOLOR,"真福安日洛(Bd. Angeto of Acri)")));
        mapPropers.insert(std::make_pair(1103101,CellInfo(OPTIONAL,NOCOLOR,"圣亚方沙•罗德利(St. Alphonsus Rodriguez)")));
		/**************11月**************/
        //1日
        mapPropers.insert(std::make_pair(1110101,CellInfo(SOLEMNITY,WHITE,"诸圣节(All Saints)")));
        mapPropers.insert(std::make_pair(1110201,CellInfo(LORD,PURPLE,"追思亡者(All Souls)")));
        mapPropers.insert(std::make_pair(1110301,CellInfo(OPTIONAL,NOCOLOR,"圣玛尔定(St. Martin de Porres 1579-1639)")));
        mapPropers.insert(std::make_pair(1110401,CellInfo(MEMORIAL,WHITE,"圣嘉禄(米兰枢机主教 St. Charles Borromeo)")));
        mapPropers.insert(std::make_pair(1110501,CellInfo(OPTIONAL,NOCOLOR,"圣女伯蒂拉(童贞 St. Betrilla -708)")));
        //6日
        mapPropers.insert(std::make_pair(1110601,CellInfo(MEMORIAL,RED,"越南第二批殉道烈士(The Martyrs of Indo-China, II)")));
        mapPropers.insert(std::make_pair(1110602,CellInfo(OPTIONAL,NOCOLOR,"圣良纳弟(St. Leonard of Noblac)")));
        mapPropers.insert(std::make_pair(1110701,CellInfo(OPTIONAL,NOCOLOR,"圣威利巴(欧德莱主教 St. Willbrord 658-739)")));
        mapPropers.insert(std::make_pair(1110702,CellInfo(OPTIONAL,NOCOLOR,"真福安多尼•白田诺西(Bd. Antony Baldinucci)")));
        mapPropers.insert(std::make_pair(1110801,CellInfo(OPTIONAL,NOCOLOR,"圣高弗烈(亚弥央斯主教 St. Godfrey -1115)")));
        mapPropers.insert(std::make_pair(1110802,CellInfo(OPTIONAL,NOCOLOR,"真福若望·董思高(司铎圣师 St. John Duns Scott 1266—1308)")));
        mapPropers.insert(std::make_pair(1110901,CellInfo(LORD,WHITE,"拉特朗大殿奉献日(The Dedication of the Lateran Basilica)")));
        mapPropers.insert(std::make_pair(1111001,CellInfo(MEMORIAL,WHITE,"圣良一世(主教 St. Leo the Great)")));
        mapPropers.insert(std::make_pair(1111002,CellInfo(OPTIONAL,NOCOLOR,"圣安德肋•亚委琳(St. Andrew Avellino)")));
        //11日
        mapPropers.insert(std::make_pair(1111101,CellInfo(MEMORIAL,WHITE,"圣玛尔定(都尔主教 St. Martin of Tours)")));
        mapPropers.insert(std::make_pair(1111102,CellInfo(OPTIONAL,NOCOLOR,"圣刁多禄(院长 St. Theodore the Studite)")));
        mapPropers.insert(std::make_pair(1111201,CellInfo(MEMORIAL,RED,"圣若撒法(波罗总主教殉道 St. Joaphat of Polotsk)")));
        mapPropers.insert(std::make_pair(1111301,CellInfo(OPTIONAL,NOCOLOR,"圣达尼老•各斯加(St. Stanislaus Kostka 1550-1568)")));
        mapPropers.insert(std::make_pair(1111401,CellInfo(OPTIONAL,NOCOLOR,"圣老楞佐•奥多(都柏林总主教 St. Laurence O'Toole)")));
        mapPropers.insert(std::make_pair(1111501,CellInfo(OPTIONAL,NOCOLOR,"圣大亚伯尔(勒根斯堡主教圣师 St. Albert the Great)")));
        mapPropers.insert(std::make_pair(1111502,CellInfo(OPTIONAL,NOCOLOR,"真福痛苦玛利亚修女(Bl. Mary of the Passion)")));
        //16日
        mapPropers.insert(std::make_pair(1111601,CellInfo(OPTIONAL,NOCOLOR,"圣妇玛加利大(St. Margaret of Scotland)")));
        mapPropers.insert(std::make_pair(1111602,CellInfo(OPTIONAL,NOCOLOR,"圣女日多达(St. Getrude)")));
        mapPropers.insert(std::make_pair(1111603,CellInfo(OPTIONAL,NOCOLOR,"圣爱德门(坎特布里总主教 St. Edmund of Abingdon)")));
        mapPropers.insert(std::make_pair(1111701,CellInfo(MEMORIAL,WHITE,"真福依撒伯尔(童贞 Bd. Elizabeth the Good)")));
        mapPropers.insert(std::make_pair(1111801,CellInfo(MEMORIAL,WHITE,"圣伯多禄圣保禄大殿奉献日(The Dedication of the Basilicas of St. Peter and of St. Paul)")));
        mapPropers.insert(std::make_pair(1111901,CellInfo(OPTIONAL,NOCOLOR,"圣额我略“显灵迹者”(新则撒肋主教 St. Gregory the Wonderworker 215-268)")));
        mapPropers.insert(std::make_pair(1111902,CellInfo(OPTIONAL,NOCOLOR,"圣狄尼削(亚历山大主教 St. Dionysius of Alexandria)")));
        mapPropers.insert(std::make_pair(1112001,CellInfo(OPTIONAL,NOCOLOR,"圣斐理斯•瓦洛亚(圣三赎虏会会祖 St. Felix of Valois)")));
        //21日
		mapPropers.insert(std::make_pair(1112101,CellInfo(MEMORIAL,WHITE,"圣母奉献日(The Presentation of the Blessed Virgin Mary)")));
		mapPropers.insert(std::make_pair(1112201,CellInfo(MEMORIAL,RED,"圣女则济利亚(童贞殉道 St. Cecilia -250)")));
        mapPropers.insert(std::make_pair(1112301,CellInfo(OPTIONAL,NOCOLOR,"圣格肋孟一世(教宗殉道 St. Clement I -100)")));
        mapPropers.insert(std::make_pair(1112302,CellInfo(OPTIONAL,NOCOLOR,"圣高隆庞(St. Columban -615)")));
        mapPropers.insert(std::make_pair(1112401,CellInfo(MEMORIAL,RED,"圣芬明(殉道 St. Finmin -303)、圣芬伯(主教 St. Finbar -633)")));
        mapPropers.insert(std::make_pair(1112501,CellInfo(OPTIONAL,NOCOLOR,"圣加斯伯(宝血会会祖 St. Caspar Del Bufalo)")));
        mapPropers.insert(std::make_pair(1112502,CellInfo(OPTIONAL,NOCOLOR,"圣若望•伯尔各满(St. John Berchmans)")));
        //26日
        mapPropers.insert(std::make_pair(1112601,CellInfo(OPTIONAL,NOCOLOR,"圣良纳(St. Leonard of Port Mauriee 1676-1751)")));
        mapPropers.insert(std::make_pair(1112701,CellInfo(OPTIONAL,NOCOLOR,"圣维琪尔(苏士堡主教 St. Virgil of Salzburg -784)")));
        mapPropers.insert(std::make_pair(1112801,CellInfo(OPTIONAL,NOCOLOR,"圣女加大利纳•拉布莱(童贞 St. Catherine Laboure 1806-1876)")));
        mapPropers.insert(std::make_pair(1112901,CellInfo(OPTIONAL,NOCOLOR,"圣斯德望(殉道 St. Stephen the Younger)")));
        mapPropers.insert(std::make_pair(1112902,CellInfo(OPTIONAL,NOCOLOR,"圣胡伯(列日主教 St. Hubert -727)")));
		mapPropers.insert(std::make_pair(1113001,CellInfo(FEAST,RED,"圣安德肋(宗徒 St. Andrew the Apostle)")));
    
		/*******************12月*****************/
        //1日
        mapPropers.insert(std::make_pair(1120101,CellInfo(OPTIONAL,NOCOLOR,"圣安利日(诺雷主教 St. Eligius -660)")));
        mapPropers.insert(std::make_pair(1120102,CellInfo(OPTIONAL,NOCOLOR,"真福爱德门•江本(Bd. Edmund Campion)")));
        mapPropers.insert(std::make_pair(1120201,CellInfo(OPTIONAL,NOCOLOR,"圣女彼彼亚纳(童贞殉道 St. Bibiana)")));
        mapPropers.insert(std::make_pair(1120301,CellInfo(MEMORIAL,WHITE,"圣方济各•沙勿略(St. Francis Xavier)")));
        mapPropers.insert(std::make_pair(1120401,CellInfo(OPTIONAL,NOCOLOR,"圣若望•达玛森(圣师 St. John Damascene)")));
        mapPropers.insert(std::make_pair(1120501,CellInfo(OPTIONAL,NOCOLOR,"圣撒巴(院长 St. Sabas -532)")));
        //6日
        mapPropers.insert(std::make_pair(1120601,CellInfo(OPTIONAL,NOCOLOR,"圣尼各老(米辣主教 St. Nicholas of Myra)")));
        mapPropers.insert(std::make_pair(1120701,CellInfo(MEMORIAL,WHITE,"圣盎博罗削(米兰主教圣师 St. Ambrose 340-397)")));
        mapPropers.insert(std::make_pair(1120702,CellInfo(OPTIONAL,NOCOLOR,"圣女若撒法•罗撒洛(童贞仁慈圣母女修会创办人 St. Josepha ROssello 1811-1880)")));
        mapPropers.insert(std::make_pair(1120801,CellInfo(FEAST,WHITE,"圣母无原罪始胎(The Immaculate Conception of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1120901,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•傅雷(圣母奥斯定女修会副会祖 St. Peter Fourier 1565-1640)")));
        mapPropers.insert(std::make_pair(1121001,CellInfo(MEMORIAL,WHITE,"洛雷托圣母")));    //我灵赞颂主有
        mapPropers.insert(std::make_pair(1121002,CellInfo(OPTIONAL,NOCOLOR,"圣米济亚德(教宗殉道 St. Miltiades -314)")));
        //11日
		mapPropers.insert(std::make_pair(1121101,CellInfo(OPTIONAL,NOCOLOR,"圣达玛稣一世(圣达生 St. Damasus 366-384)")));
        mapPropers.insert(std::make_pair(1121201,CellInfo(FEAST,WHITE,"瓜达卢佩圣母(Our Lady of Guadalupe)")));
        mapPropers.insert(std::make_pair(1121202,CellInfo(OPTIONAL,NOCOLOR,"圣妇若翰纳•方济加•尚达尔(圣母往见会创办人 St. Jane Frances de Chantal -1641)")));
        mapPropers.insert(std::make_pair(1121301,CellInfo(MEMORIAL,RED,"圣女路济亚(圣路琪童贞殉道 St. Lucy)")));
        mapPropers.insert(std::make_pair(1121401,CellInfo(MEMORIAL,WHITE,"圣若望“由十字架者”(圣师 St. John of the Cross)")));
        mapPropers.insert(std::make_pair(1121402,CellInfo(OPTIONAL,NOCOLOR,"圣史比利廷(德米杜主教 St. Spiridion)")));
        mapPropers.insert(std::make_pair(1121501,CellInfo(OPTIONAL,NOCOLOR,"圣万南修•福多诺(波蒂亚主教 St. Venantius Fotunatus)")));
        mapPropers.insert(std::make_pair(1121502,CellInfo(OPTIONAL,NOCOLOR,"圣女尼诺(童贞 St. Nino)")));
        mapPropers.insert(std::make_pair(1121503,CellInfo(OPTIONAL,NOCOLOR,"圣女玛利亚•罗撒(童贞伯来西亚仁爱婢女会创办人 St. Mary di Rosa 1813-1855)")));
        //16日
        mapPropers.insert(std::make_pair(1121601,CellInfo(OPTIONAL,NOCOLOR,"圣妇亚德莱(St. Adelaide)")));
        mapPropers.insert(std::make_pair(1121701,CellInfo(MEMORIAL,NOCOLOR,"圣拉匝禄(St. Lazarus)")));
        mapPropers.insert(std::make_pair(1121702,CellInfo(OPTIONAL,NOCOLOR,"圣妇奥林比亚(St. Olympias 361-408)")));
        mapPropers.insert(std::make_pair(1121703,CellInfo(MEMORIAL,PURPLE,"将临期 十二月十七日")));
        mapPropers.insert(std::make_pair(1121801,CellInfo(OPTIONAL,NOCOLOR,"圣威纳巴(院长 St. Wunibald)")));
        mapPropers.insert(std::make_pair(1121802,CellInfo(OPTIONAL,NOCOLOR,"圣斯多米(院长 St. Sturmi)")));
        mapPropers.insert(std::make_pair(1121803,CellInfo(MEMORIAL,PURPLE,"将临期 十二月十八日")));
        mapPropers.insert(std::make_pair(1121901,CellInfo(OPTIONAL,NOCOLOR,"圣南米修及其他殉道烈士(Ss. Nemesius and other Martyrs)")));
        mapPropers.insert(std::make_pair(1121902,CellInfo(MEMORIAL,PURPLE,"将临期 十二月十九日")));
        mapPropers.insert(std::make_pair(1122001,CellInfo(OPTIONAL,NOCOLOR,"圣多明我•西洛(院长 St. Dominic of Silos -1073)")));
        mapPropers.insert(std::make_pair(1122002,CellInfo(MEMORIAL,PURPLE,"将临期 十二月二十日")));
        //21日
        mapPropers.insert(std::make_pair(1122101,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄•加尼削(圣师 St. Peter Canisius)")));
        mapPropers.insert(std::make_pair(1122102,CellInfo(MEMORIAL,PURPLE,"将临期 十二月二十一日")));
        mapPropers.insert(std::make_pair(1122201,CellInfo(OPTIONAL,NOCOLOR,"圣女方济加(童贞 圣心传教女修会创办人 St. Frances Xavier Cabrini 1850-1917)")));
        mapPropers.insert(std::make_pair(1122202,CellInfo(MEMORIAL,PURPLE,"将临期 十二月二十二日")));
        mapPropers.insert(std::make_pair(1122301,CellInfo(OPTIONAL,NOCOLOR,"圣若望根地(St. John of Kanti 1297-1473)")));
        mapPropers.insert(std::make_pair(1122302,CellInfo(MEMORIAL,PURPLE,"将临期 十二月二十三日")));
        mapPropers.insert(std::make_pair(1122401,CellInfo(SOLEMNITY,WHITE,"耶稣圣诞节望日")));
        mapPropers.insert(std::make_pair(1122501,CellInfo(SOLEMNITY,WHITE,"耶稣圣诞(The Birthday of Our Lord Jesus Christ)")));
        //26日
        mapPropers.insert(std::make_pair(1122601,CellInfo(FEAST,RED,"圣斯德望(首位殉道 St. Stephen -34)")));
        mapPropers.insert(std::make_pair(1122602,CellInfo(OPTIONAL,NOCOLOR,"真福味增济亚(童贞 无玷圣母修会创办人 Bd. Vincentia Lopez 1847-1890)")));
		mapPropers.insert(std::make_pair(1122701,CellInfo(FEAST,WHITE,"圣若望(宗徒兼圣史 St. John the Evangelist -100)")));
		mapPropers.insert(std::make_pair(1122801,CellInfo(FEAST,RED,"诸圣婴孩(The Holy Innocents)")));
        mapPropers.insert(std::make_pair(1122901,CellInfo(OPTIONAL,NOCOLOR,"圣多默•贝凯(St. Thomas Becket)")));
		mapPropers.insert(std::make_pair(1122902,CellInfo(LORD,WHITE,"圣诞节庆期第五日")));
        mapPropers.insert(std::make_pair(1123001,CellInfo(OPTIONAL,NOCOLOR,"圣撒比诺等殉道者(Ss. Sabinus and his Companions)")));
		mapPropers.insert(std::make_pair(1123002,CellInfo(LORD,WHITE,"圣诞节庆期第六日")));
        mapPropers.insert(std::make_pair(1123101,CellInfo(OPTIONAL,NOCOLOR,"圣西尔物斯德肋(思维 St. Silvestes 314-335)")));
        mapPropers.insert(std::make_pair(1123102,CellInfo(OPTIONAL,NOCOLOR,"圣妇幼梅肋尼亚(St. Melania the Younger -439)")));
		mapPropers.insert(std::make_pair(1123103,CellInfo(LORD,WHITE,"圣诞节庆期第七日")));
	}


	/*
	// 由礼仪年确定的特殊节日
	// 规则：采用十进制（共六位）
	// 前面两位为：Season
	// 中间两位为：主日编号
	// 最后两位为：星期几
	*/
	{
        //常年期
		mapPropers.insert(std::make_pair(ORDINARY*10000+300+0,CellInfo(SUNDAY,GREEN,"常年期第三主日(圣言主日)")));
		//四旬期第0主日星期三（圣灰礼仪）
		mapPropers.insert(std::make_pair(LENT*10000+3,CellInfo(ASHWED,PURPLE,"圣灰礼仪")));
		//四旬期第六主日（圣周）
		mapPropers.insert(std::make_pair(LENT*10000+600+0,CellInfo(HOLYWEEK,RED,"圣枝主日(基督苦难主日)")));
		mapPropers.insert(std::make_pair(LENT*10000+600+1,CellInfo(HOLYWEEK,PURPLE,"圣周一")));
		mapPropers.insert(std::make_pair(LENT*10000+600+2,CellInfo(HOLYWEEK,PURPLE,"圣周二")));
		mapPropers.insert(std::make_pair(LENT*10000+600+3,CellInfo(HOLYWEEK,PURPLE,"圣周三")));
		mapPropers.insert(std::make_pair(LENT*10000+600+4,CellInfo(TRIDUUM,WHITE,"主的晚餐")));
		mapPropers.insert(std::make_pair(LENT*10000+600+5,CellInfo(TRIDUUM,RED,"耶稣受难")));
		mapPropers.insert(std::make_pair(LENT*10000+600+6,CellInfo(TRIDUUM,WHITE,"基督安眠墓中(复活节前夕)")));

		//复活期第一主日（复活节）
		mapPropers.insert(std::make_pair(EASTER*10000+100+0,CellInfo(SOLEMNITY,WHITE,"复活节")));
		mapPropers.insert(std::make_pair(EASTER*10000+100+1,CellInfo(SOLEMNITY,WHITE,"复活节庆期第二日")));
		mapPropers.insert(std::make_pair(EASTER*10000+100+2,CellInfo(SOLEMNITY,WHITE,"复活节庆期第三日")));
		mapPropers.insert(std::make_pair(EASTER*10000+100+3,CellInfo(SOLEMNITY,WHITE,"复活节庆期第四日")));
		mapPropers.insert(std::make_pair(EASTER*10000+100+4,CellInfo(SOLEMNITY,WHITE,"复活节庆期第五日")));
		mapPropers.insert(std::make_pair(EASTER*10000+100+5,CellInfo(SOLEMNITY,WHITE,"复活节庆期第六日")));
		mapPropers.insert(std::make_pair(EASTER*10000+100+6,CellInfo(SOLEMNITY,WHITE,"复活节庆期第七日")));
		mapPropers.insert(std::make_pair(EASTER*10000+200+0,CellInfo(SOLEMNITY,WHITE,"复活节庆期第八日(慈悲主日)")));
		//复活期第四主日
		mapPropers.insert(std::make_pair(EASTER*10000+400+0,CellInfo(SUNDAY,WHITE,"复活期第四主日(善牧主日)")));

		//圣神降临节（复活期第八主日）
		//mapPropers.insert(std::make_pair(EASTER*10000+700+6,CellInfo(FEAST,RED,"圣神降临节前夕")));
		mapPropers.insert(std::make_pair(EASTER*10000+800+0,CellInfo(SOLEMNITY,RED,"圣神降临节")));

       //常年期第三十三主日（世界穷人日）
        mapPropers.insert(std::make_pair(ORDINARY*10000+3300+0,CellInfo(SUNDAY,WHITE,"常年期第三十三主日(世界穷人日)")));
		//常年期第三十四主日（基督普世君王节）
		mapPropers.insert(std::make_pair(ORDINARY*10000+3400+0,CellInfo(SOLEMNITY,WHITE,"基督普世君王节")));
	}

	/*
	// 特殊节日
	// 索引从1开始
	*/
	{
		mapPropers.insert(std::make_pair(1,CellInfo(SOLEMNITY,WHITE,"主显节(Epiphany of the Lord)")));
		mapPropers.insert(std::make_pair(2,CellInfo(LORD,WHITE,"主受洗日(Baptism of the Lord)")));

		//从复活节算起的节日
		mapPropers.insert(std::make_pair(3,CellInfo(LORD,WHITE,"我们的主耶稣基督—永恒的大司祭")));	//复活节后53日
		mapPropers.insert(std::make_pair(4,CellInfo(SOLEMNITY,WHITE,"圣三主日")));				//复活节后56日（复活期后的主日）
		mapPropers.insert(std::make_pair(5,CellInfo(SOLEMNITY,WHITE,"基督圣体圣血节")));			//复活节后60日
		mapPropers.insert(std::make_pair(6,CellInfo(SOLEMNITY,WHITE,"耶稣圣心节")));				//复活节后68日
		mapPropers.insert(std::make_pair(7,CellInfo(MEMORIAL,WHITE,"圣母无玷圣心")));				//复活节后69日

		//圣诞期
		mapPropers.insert(std::make_pair(8,CellInfo(LORD,WHITE,"圣家节")));

		//中华圣母（五月份的第二个星期六）
		mapPropers.insert(std::make_pair(9,CellInfo(FEAST,WHITE,"中华圣母")));
        //教会之母节（圣神降临节后星期一）
        mapPropers.insert(std::make_pair(10,CellInfo(MEMORIAL,WHITE,"教会之母")));

        //农历除夕
        mapPropers.insert(std::make_pair(11,CellInfo(FEAST,NOCOLOR,"农历除夕")));
        //农历春节
        mapPropers.insert(std::make_pair(12,CellInfo(FEAST,NOCOLOR,"农历新春")));
        //普世传教节
        mapPropers.insert(std::make_pair(13,CellInfo(LORD,GREEN,"普世传教节")));

		//耶稣升天（固定在复活期第六主日星期四，但可能因牧灵需要调整到第七主日）
		mapPropers.insert(std::make_pair(14,CellInfo(SOLEMNITY,WHITE,"耶稣升天节")));
	}
    
    // 将节日编码插入到节日里
    auto iter = mapPropers.begin();
    while(iter != mapPropers.end()) {
        iter->second.code = iter->first;
        ++iter;
    }
}

CathAssist::Calendar::CellInfo CathAssist::Calendar::LiturgicYear::getCellInfo(const int& id)
{
	auto iter = mapPropers.find(id);
	if(iter != mapPropers.end())
		return iter->second;

	return CellInfo(CathAssist::Calendar::ErrorRank,CathAssist::Calendar::NOCOLOR,"");
}


LiturgicYear::LiturgicYear(const int& y)
	: year(y)
{
	init();
}

LiturgicYear::~LiturgicYear(void)
{
}

LiturgicDay LiturgicYear::getLiturgicDay(const Date& d)
{
	if(d.year() != year)
		return LiturgicDay();

    //填充数据
    LiturgicDay ld = d;
	if(ld<=bl)
	{
		testChristmas1(ld);
	}
	else if(ld<aw)
	{
		testOrdinary1(ld);
	}
	else if(ld<easter)
	{
		testLent(ld);
	}
	else if(ld<=ps)
	{
		testEaster(ld);
	}
	else if(ld<av)
	{
		testOrdinary2(ld);
	}
	else if(ld<cm)
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
    ostr<<"年份:"<<year<<std::endl;
	ostr<<"主显节\t\t:\t"<<ep.toString()<<std::endl;
	ostr<<"主受洗日\t\t:\t"<<bl.toString()<<std::endl;
	ostr<<"圣灰礼仪\t\t:\t"<<aw.toString()<<std::endl;
	ostr<<"复活节\t\t:\t"<<easter.toString()<<std::endl;
    ostr<<"圣神降临\t\t:\t"<<ps.toString()<<std::endl;
    ostr<<"将临期第一主日\t:\t"<<av.toString()<<std::endl;
    
    return ostr.str();
}

void LiturgicYear::init()
{
	//主显节
	LiturgicDay t(year,1,2);
	ep = t.addDays((7-t.dayOfWeek())%7);

	//主受洗日(圣诞期的结束)
	if(ep.day()>6)
	{
		bl = ep.addDays(1);
	}
	else
	{
		bl = ep.addDays(7);
	}

	//复活节
	{
		int y,c,n,k,i,j,l,m,d;
		y = year;

		c = y/100;
		n = y - 19*(y/19);
		k = (c - 17)/25;
		i = c - c/4 - (c-k)/3 + 19*n + 15;
		i = i - 30*(i/30);
		i = i - (i/28) * (1 - (i/28) * (29/(i+1)) * ((21 - n)/11));
		j = y + y/4 + i + 2 - c + c/4;
		j = j - 7*(j/7);
		l = i - j;

		m = 3 + (l+40)/44;
		d = l + 28 - 31*(m/4);

		easter.setDate(year, m, d);
	}

	//圣灰礼仪（周三 四旬期开始）
	aw = easter.addDays(-46);

	//圣神降临节瞻礼
	ps = easter.addDays(49);

	t.setDate(year,11,30);
	//将临期第一主日
    if(t.dayOfWeek() > Days::WED)
    {
        av = t.addDays(7-t.dayOfWeek());
    }
    else
    {
        av = t.addDays(0-t.dayOfWeek());
    }

	//圣诞节
	cm.setDate(year,12,25);
}

void LiturgicYear::testChristmas1(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<LiturgicDay(year,1,1) || ld>bl)
		return;

	ld.setSeason(CHRISTMAS);
    ld.setWeekOfSeason(2);
	if(ld<ep)
	{
        //主显节前都是第一周
        ld.setWeekOfSeason(1);
	}
	else if(ld==ep)
	{
		ld.appendCell(1);	//主显节（普世教会）
	}
	else if(ld==bl)
	{
		ld.appendCell(2);	//主受洗日
        ld.setWeekOfSeason(-1); //不归属于常年期或圣诞期
	}

	if(ld.month()==1&&ld.day()==6)
	{
        // 移除 1 月 6 日的主显节
//		ld.appendCell(1);	//主显节（大陆教会）
	}
}

void LiturgicYear::testOrdinary1(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<=bl || ld>=aw)
		return;

	ld.setSeason(ORDINARY);
//	int weekBegin = aw.weekNumber();
	ld.setWeekOfSeason( ld.weekNumber()-bl.weekNumber()+1 );
}

void LiturgicYear::testLent(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<aw || ld>=easter)
		return;

	ld.setSeason(LENT);
	ld.setWeekOfSeason( ld.weekNumber()-aw.weekNumber() );
}

void LiturgicYear::testEaster(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<easter || ld>ps)
		return;

	ld.setSeason(EASTER);
	ld.setWeekOfSeason(ld.weekNumber()-easter.weekNumber()+1);

    if(ld.getLiturgicId() == EASTER*10000+600+4) {
        ld.appendCell(14); //耶稣升天节（复活期第六主日星期四）
    }
    if(ld.getLiturgicId() == EASTER*10000+700+0) {
        ld.appendCell(14); //耶稣升天节（可挪到主日庆祝）
    }
}

void LiturgicYear::testOrdinary2(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<=ps || ld>=av)
		return;

	int weekEnd = av.weekNumber() - 1;		//将临期第一主日为常年期的结束
	ld.setWeekOfSeason( 34-(weekEnd-ld.weekNumber()) );

	int dayFromEaster = easter.daysTo(ld);

	if(dayFromEaster == 53)
	{
		ld.appendCell(3);	//我们的主耶稣基督—永恒的大司祭
	}
	else if(dayFromEaster == 56)
	{
		ld.appendCell(4);	//圣三主日
	}
	else if(dayFromEaster == 60 || dayFromEaster == 63)
	{
		//圣三主日的星期四(+60)，可移至主日庆祝(+63)
		ld.appendCell(5);	//基督圣体圣血节
	}
	else if(dayFromEaster == 68)
	{
		ld.appendCell(6);	//耶稣圣心节
	}
	else if(dayFromEaster == 69)
	{
		ld.appendCell(7);	//圣母无玷圣心
	}

    if(SUN == ld.dayOfWeek() && 10 == ld.month() && ld.day() >=18 && ld.day()<=24) {
        // 普世传教节，10月倒数第二个主日
        ld.appendCell(13);
    }

	ld.setSeason(ORDINARY);
}

void LiturgicYear::testAdvent(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<av || ld>=cm)
		return;

	ld.setSeason(ADVENT);
	ld.setWeekOfSeason(ld.weekNumber()-av.weekNumber()+1);
}

void LiturgicYear::testChristmas2(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<cm || ld>LiturgicDay(year,12,31))
		return;

	ld.setSeason(CHRISTMAS);
    //12 月份全是圣诞节八日庆期
    ld.setWeekOfSeason(-1);

	//圣家节
	if(cm.dayOfWeek() == SUN)
	{
		if(ld == Date(year,12,30))
			ld.appendCell(8);
	}
	else
	{
		if(ld.dayOfWeek() == SUN)
			ld.appendCell(8);
	}
}

void LiturgicYear::testProper(LiturgicDay& ld)
{
    {
        //教会之母（圣神降临节后星期一）
        if(ld.daysTo(ps) == -1) {
            ld.appendCell(10);
        }
    }

	{
		//中华圣母（5月的第二个周六）
		if(ld.month() == 5 && ld.dayOfWeek() == 6)
		{
			if(ld.day() >= 7 && ld.day()<=13)
			{
				ld.appendCell(9);
			}
		}
	}

    {
        //中国农历新年
        if(LiturgicDay::isSpringFestival(ld)) {
            ld.appendCell(12);
        }
        //中国农历除夕
        if(LiturgicDay::isNewYearEve(ld)) {
            ld.appendCell(11);
        }
    }

	{
		//礼仪年特殊节日
		int id = ld.getLiturgicId();
		auto iter = mapPropers.find(id);
		if(iter!=mapPropers.end())
		{
			ld.appendCell(iter->first);
		}
	}
	{
		int v = 1000000 + ld.month()*10000+ld.day()*100;

		auto iter = mapPropers.lower_bound(v);
		while (iter!=mapPropers.end())
		{
			int key = iter->first;
			if(key/100 != v/100)
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
        for(int i=1; i<=4; ++i) {
            for(int j=0; j<=6; ++j) {
                int code = ADVENT*10000 + i*100 + j;
                days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        // 圣诞期
        for(int i=1; i<=3; ++i) {
            for(int j=0; j<=6; ++j) {
                int code = CHRISTMAS*10000 + i*100 + j;
                days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        //四旬期
        //圣灰礼仪后三天（周四、周五、周六）
        int code = LENT*10000 + 0*100 + 4;
        days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
        code++;
        days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
        code++;
        days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
        for(int i=1; i<=6; ++i) {
            for(int j=0; j<=6; ++j) {
                int code = LENT*10000 + i*100 + j;
                days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        //复活期
        for(int i=1; i<=7; ++i) {
            for(int j=0; j<=6; ++j) {
                int code = EASTER*10000 + i*100 + j;
                days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    {
        //常年期
        for(int i=1; i<=34; ++i) {
            for(int j=0; j<=6; ++j) {
                int code = ORDINARY*10000 + i*100 + j;
                days.push_back(CellInfo(code, OPTIONAL, NOCOLOR, LiturgicDay::getWeekdayString(code)));
            }
        }
    }
    
    return days;
}

