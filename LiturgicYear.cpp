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
        mapPropers.insert(std::make_pair(1010201,CellInfo(MEMORIAL,WHITE,"圣巴西略(凯撒利亚主教圣师 St. Basil the Great)")));
        mapPropers.insert(std::make_pair(1010202,CellInfo(MEMORIAL,WHITE,"圣额我略•纳齐盎(国瑞•纳祥 St. Gregory Nazianxen)")));
        
        //3日
        mapPropers.insert(std::make_pair(1010301,CellInfo(OPTIONAL,NOCOLOR,"耶稣圣名节")));
        mapPropers.insert(std::make_pair(1010302,CellInfo(OPTIONAL,NOCOLOR,"真福查瓦拉(Bd. Kuriakose Elias Chavara)")));
        mapPropers.insert(std::make_pair(1010303,CellInfo(OPTIONAL,NOCOLOR,"圣女日南斐法(童贞 St. Genevieve)")));
        //4日
        mapPropers.insert(std::make_pair(1010401,CellInfo(OPTIONAL,NOCOLOR,"圣安•贝兰•丝彤(依丽莎白 St. Eizabeth Ann Bayley Seton")));
        mapPropers.insert(std::make_pair(1010402,CellInfo(OPTIONAL,NOCOLOR,"圣女法拉意弟(St. Pharaildis)")));
        //5日
        mapPropers.insert(std::make_pair(1010501,CellInfo(OPTIONAL,NOCOLOR,"圣牛曼(St. John Nepornucene Neumann)")));
        mapPropers.insert(std::make_pair(1010502,CellInfo(OPTIONAL,NOCOLOR,"圣西默盎“石柱人”(St. Simeon the Stylite)")));
        
		//1月6日的主显节方式已不再使用（但因没有经过主教团批准，所以暂时未在大陆使用）
        mapPropers.insert(std::make_pair(1010601,CellInfo(SOLEMNITY,WHITE,"主显节(三王来朝 The Epiphany of Our Lord Christ)")));
        mapPropers.insert(std::make_pair(1010602,CellInfo(OPTIONAL,NOCOLOR,"真福辣法厄尔•玛利亚(童贞圣心婢女会会祖 Bd Raphaela Mary)")));
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
        mapPropers.insert(std::make_pair(1012101,CellInfo(OPTIONAL,NOCOLOR,"圣女依搦斯(雅妮童贞殉道 St. Agnes)")));
        //22日
        mapPropers.insert(std::make_pair(1012201,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵(文生殉道 St. Vincent of Saragossa)")));
        mapPropers.insert(std::make_pair(1012202,CellInfo(OPTIONAL,NOCOLOR,"圣亚纳大削(殉道 St. Anastasius the Persian)")));
        mapPropers.insert(std::make_pair(1012203,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵•柏乐天(St. Vincent Polloti)")));
        //23日
        mapPropers.insert(std::make_pair(1012301,CellInfo(OPTIONAL,NOCOLOR,"圣爱美兰霞(童贞殉道 St. Emerentiana)")));
        mapPropers.insert(std::make_pair(1012401,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•撒肋爵(主教圣师 St. Francis de Sales)")));
        mapPropers.insert(std::make_pair(1012501,CellInfo(OPTIONAL,NOCOLOR,"圣保禄宗徒归化(The Conversion of St. Paul)")));
        mapPropers.insert(std::make_pair(1012601,CellInfo(OPTIONAL,NOCOLOR,"圣弟茂德(主教精修 St. Timothy 32-97)")));
        mapPropers.insert(std::make_pair(1012602,CellInfo(OPTIONAL,NOCOLOR,"圣弟铎(克里特主教迪德 St. Titus)")));
        //27日
        mapPropers.insert(std::make_pair(1012701,CellInfo(OPTIONAL,NOCOLOR,"圣女安琪拉(童贞圣乌苏拉女修会会祖 St. Angela Merici)")));
        mapPropers.insert(std::make_pair(1012801,CellInfo(OPTIONAL,NOCOLOR,"圣多玛斯•阿奎那(圣师雅奎 St. Thomas Aquinas)")));
        mapPropers.insert(std::make_pair(1012901,CellInfo(OPTIONAL,NOCOLOR,"圣亚波罗尼(殉道 St. Apoelonius the Apologist)")));
        mapPropers.insert(std::make_pair(1013001,CellInfo(OPTIONAL,NOCOLOR,"圣女玛蒂娜(童贞致命 St. Martina)")));
        mapPropers.insert(std::make_pair(1013002,CellInfo(OPTIONAL,NOCOLOR,"圣妇巴蒂弟(St. Bathildis)")));
        mapPropers.insert(std::make_pair(1013101,CellInfo(OPTIONAL,NOCOLOR,"圣鲍思高(慈幼会会祖 St. John Bosco)")));
        mapPropers.insert(std::make_pair(1013102,CellInfo(OPTIONAL,NOCOLOR,"圣方济各•沙勿略•白英奇(St. Francis Xavier Bianchi)")));
        
        /**********************2月*********************/
        //1日
        mapPropers.insert(std::make_pair(1020101,CellInfo(OPTIONAL,NOCOLOR,"圣亨利•莫斯(殉道 St. Herry Morse)")));
        mapPropers.insert(std::make_pair(1020201,CellInfo(LORD,WHITE,"献耶稣于圣殿(Preselltation of the Lord)")));
        mapPropers.insert(std::make_pair(1020301,CellInfo(OPTIONAL,NOCOLOR,"圣巴拉削(主教殉道 St. Blaise)")));
        mapPropers.insert(std::make_pair(1020302,CellInfo(OPTIONAL,NOCOLOR,"圣老楞佐(主教 St. Laurence)")));
        //4日
        mapPropers.insert(std::make_pair(1020401,CellInfo(OPTIONAL,NOCOLOR,"圣若望•波利多(殉道 St. John de Britto)")));
        mapPropers.insert(std::make_pair(1020402,CellInfo(OPTIONAL,NOCOLOR,"圣妇若翰纳(圣母领报会会祖 St. John of France)")));
        mapPropers.insert(std::make_pair(1020501,CellInfo(MEMORIAL,RED,"圣女亚加大(童贞殉道 St. Agatha)")));
        //6日
        mapPropers.insert(std::make_pair(1020601,CellInfo(MEMORIAL,RED,"日本殉道烈士诸圣(the Martyrs of Japan)")));
        mapPropers.insert(std::make_pair(1020602,CellInfo(OPTIONAL,NOCOLOR,"圣童郑安道")));
        mapPropers.insert(std::make_pair(1020701,CellInfo(OPTIONAL,NOCOLOR,"圣女尤丽娜(童贞 St. Juliana Falconieri)")));
        mapPropers.insert(std::make_pair(1020801,CellInfo(OPTIONAL,NOCOLOR,"圣热罗莫•爱弥廉(St. Jierome Emiliani)")));
        mapPropers.insert(std::make_pair(1020802,CellInfo(OPTIONAL,NOCOLOR,"圣若望•玛达(圣三赎虏会副会祖 St. John of Matha)")));
        //9日
        mapPropers.insert(std::make_pair(1020901,CellInfo(OPTIONAL,NOCOLOR,"圣高德乐(精修 St. Miguel Febres Cordero)")));
        mapPropers.insert(std::make_pair(1020902,CellInfo(OPTIONAL,NOCOLOR,"圣撒比诺(嘉诺沙主教 St. Sabinus)")));
        //10日
        mapPropers.insert(std::make_pair(1021001,CellInfo(MEMORIAL,WHITE,"圣女斯高拉蒂加(圣思嘉童贞 Scholastica)")));
        mapPropers.insert(std::make_pair(1021101,CellInfo(OPTIONAL,NOCOLOR,"露德圣母显现(the Appearing of our Lady at Lourdes)")));
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
        mapPropers.insert(std::make_pair(1031901,CellInfo(SOLEMNITY,WHITE,"圣若瑟(圣母净配中国主保 St. Joseph)")));
        mapPropers.insert(std::make_pair(1032001,CellInfo(OPTIONAL,NOCOLOR,"圣格时白(主教 St. Cuthbert)")));
        //21日
        mapPropers.insert(std::make_pair(1032101,CellInfo(OPTIONAL,NOCOLOR,"圣尼格老•冯物洛(St. Nicholas de flue)")));
        mapPropers.insert(std::make_pair(1032102,CellInfo(OPTIONAL,NOCOLOR,"圣恩达（院长）、圣女芳佳（童贞）(St. Enda and St. Fanchea)")));
        mapPropers.insert(std::make_pair(1032201,CellInfo(OPTIONAL,NOCOLOR,"圣婴西满和圣童威廉(殉道者 Ss. Simen of Trent and William of Norwich)")));
        mapPropers.insert(std::make_pair(1032301,CellInfo(OPTIONAL,NOCOLOR,"圣多利波(利马总主教 St. Turibius)")));
        mapPropers.insert(std::make_pair(1032302,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟•奥利沃(St. Joseph Oriol)")));
        mapPropers.insert(std::make_pair(1032401,CellInfo(OPTIONAL,NOCOLOR,"圣女加大利纳•瑞典(童贞 St. Catherine of Sweden)")));
        mapPropers.insert(std::make_pair(1032402,CellInfo(OPTIONAL,NOCOLOR,"圣依勒内(殉道 St. Irenaeus)")));
        mapPropers.insert(std::make_pair(1032501,CellInfo(SOLEMNITY,WHITE,"圣母领报(the Annunciation of the Blessed Virgin Mary)")));
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
        mapPropers.insert(std::make_pair(1041802,CellInfo(OPTIONAL,NOCOLOR,"福女玛利亚(Bl. Mary of the Incarnation)")));
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
        mapPropers.insert(std::make_pair(1050101,CellInfo(OPTIONAL,NOCOLOR,"大圣若瑟劳工主保(St. Joseph the Worker)")));
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
        mapPropers.insert(std::make_pair(1051301,CellInfo(OPTIONAL,NOCOLOR,"法蒂玛圣母(Our Lady of Fatima)")));
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
        mapPropers.insert(std::make_pair(1053001,CellInfo(OPTIONAL,NOCOLOR,"圣女贞德(童贞 St. Joan of Arc)")));
        mapPropers.insert(std::make_pair(1053101,CellInfo(FEAST,WHITE,"圣母访亲节(the Vistation of the Blessed Virgin Mary)")));
        mapPropers.insert(std::make_pair(1053102,CellInfo(OPTIONAL,NOCOLOR,"圣母诸宠中保及中华圣母节(Our Lady of all Graces and Queen of China)")));
        
        /*************6月***************/
		//1日
        mapPropers.insert(std::make_pair(1060101,CellInfo(MEMORIAL,RED,"圣犹思定殉道(St. Justin)")));
        mapPropers.insert(std::make_pair(1060102,CellInfo(OPTIONAL,NOCOLOR,"日本殉道烈士(The Martyrs of Japan, II)")));
        mapPropers.insert(std::make_pair(1060201,CellInfo(OPTIONAL,NOCOLOR,"圣玛策林、圣伯多禄(殉道 Ss. Marcellinus and Peter)")));
        mapPropers.insert(std::make_pair(1060202,CellInfo(OPTIONAL,NOCOLOR,"里昂及维安殉道烈士(St. Pothinus and his Companions, the Martyrs of Lyons and Vienne)")));
        mapPropers.insert(std::make_pair(1060301,CellInfo(MEMORIAL,RED,"圣查理王加、圣若瑟加萨及其他殉道烈士(Ss. Charles Lwanga, Joseph Mkasa and their Companions)")));
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
        mapPropers.insert(std::make_pair(1061101,CellInfo(MEMORIAL,RED,"圣巴尔纳伯(宗徒 St. Barnabas)")));
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
        mapPropers.insert(std::make_pair(1062401,CellInfo(SOLEMNITY,WHITE,"圣若翰洗者诞辰(The Birthday of St. John the Baptist)")));
        mapPropers.insert(std::make_pair(1062501,CellInfo(OPTIONAL,NOCOLOR,"圣威廉•维吉尔(维吉尔修院院长 St. William of Monte Vergine)")));
        mapPropers.insert(std::make_pair(1062502,CellInfo(OPTIONAL,NOCOLOR,"圣女佛波罗尼(童贞殉道 St. Febronia)")));
        //26日
        mapPropers.insert(std::make_pair(1062601,CellInfo(OPTIONAL,NOCOLOR,"圣安德莫(比利主教 St. Anthelm)")));
        mapPropers.insert(std::make_pair(1062701,CellInfo(OPTIONAL,NOCOLOR,"圣济利禄(亚历山大主教圣师 St. Cyril)")));
        mapPropers.insert(std::make_pair(1062801,CellInfo(MEMORIAL,RED,"圣依勒内(里昂主教殉道 St. Irenaeus)")));
        mapPropers.insert(std::make_pair(1062802,CellInfo(OPTIONAL,NOCOLOR,"圣波罗德格、圣波太米诺及其他殉道烈士(Ss. Blutarch Potamiaena and their Companions)")));
        mapPropers.insert(std::make_pair(1062901,CellInfo(SOLEMNITY,RED,"圣伯多禄宗徒(St. Peter Apostle)")));
        mapPropers.insert(std::make_pair(1062902,CellInfo(SOLEMNITY,RED,"圣保禄宗徒(St. Paul Apostle)")));
		mapPropers.insert(std::make_pair(1063001,CellInfo(MEMORIAL,RED,"罗马第一批殉道烈士(Martyrs of Rome, I)")));
    
		/*************7月**************/
        //1日
		mapPropers.insert(std::make_pair(1070301,CellInfo(FEAST,RED,"圣多默（宗徒）")));
		mapPropers.insert(std::make_pair(1070401,CellInfo(OPTIONAL,NOCOLOR,"葡萄牙的圣依撒伯尔")));
		mapPropers.insert(std::make_pair(1070501,CellInfo(OPTIONAL,NOCOLOR,"圣安多尼·匝加利（司铎）")));
		mapPropers.insert(std::make_pair(1070601,CellInfo(OPTIONAL,NOCOLOR,"圣玛利亚·葛莱蒂（童贞、殉道）")));
		mapPropers.insert(std::make_pair(1070901,CellInfo(OPTIONAL,NOCOLOR,"中华诸圣及圣赵荣思定神父（司铎、殉道）")));
		mapPropers.insert(std::make_pair(1071101,CellInfo(MEMORIAL,WHITE,"圣本笃（院长）")));
		mapPropers.insert(std::make_pair(1071301,CellInfo(OPTIONAL,NOCOLOR,"圣皇亨利")));
		mapPropers.insert(std::make_pair(1071401,CellInfo(OPTIONAL,NOCOLOR,"圣加弥禄·弥理（司铎）")));
		mapPropers.insert(std::make_pair(1071501,CellInfo(MEMORIAL,WHITE,"圣文德（主教、圣师）")));
		mapPropers.insert(std::make_pair(1071601,CellInfo(OPTIONAL,NOCOLOR,"加尔默罗山圣母")));
		mapPropers.insert(std::make_pair(1072101,CellInfo(OPTIONAL,NOCOLOR,"Saint Apollinaris（主教、殉道）")));
		mapPropers.insert(std::make_pair(1072101,CellInfo(OPTIONAL,NOCOLOR,"圣老楞佐·布林希（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1072201,CellInfo(MEMORIAL,WHITE,"圣玛利亚·玛达肋纳")));
		mapPropers.insert(std::make_pair(1072301,CellInfo(OPTIONAL,NOCOLOR,"圣妇彼济大（会士）")));
		mapPropers.insert(std::make_pair(1072501,CellInfo(FEAST,RED,"圣雅各伯（宗徒）")));
		mapPropers.insert(std::make_pair(1072601,CellInfo(MEMORIAL,WHITE,"圣若亚敬及圣亚纳（圣母双亲）")));
		mapPropers.insert(std::make_pair(1072901,CellInfo(MEMORIAL,WHITE,"圣玛尔大")));
		mapPropers.insert(std::make_pair(1073001,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄·金言（主教、圣师）")));
		mapPropers.insert(std::make_pair(1073101,CellInfo(OPTIONAL,NOCOLOR,"圣依纳爵·罗耀拉（司铎）")));
    
		//8月
		mapPropers.insert(std::make_pair(1080101,CellInfo(MEMORIAL,WHITE,"圣亚丰索（主教、圣师）")));
		mapPropers.insert(std::make_pair(1080201,CellInfo(OPTIONAL,NOCOLOR,"圣艾伯铎（司铎）")));
		mapPropers.insert(std::make_pair(1080201,CellInfo(OPTIONAL,NOCOLOR,"圣欧瑟伯（主教）")));
		mapPropers.insert(std::make_pair(1080401,CellInfo(MEMORIAL,WHITE,"圣若翰·维雅纳（司铎）")));
		mapPropers.insert(std::make_pair(1080501,CellInfo(OPTIONAL,NOCOLOR,"圣母大殿奉献日")));
		mapPropers.insert(std::make_pair(1080601,CellInfo(LORD,WHITE,"耶稣显圣容")));
		mapPropers.insert(std::make_pair(1080701,CellInfo(OPTIONAL,NOCOLOR,"圣嘉耶当（司铎）")));
		mapPropers.insert(std::make_pair(1080701,CellInfo(OPTIONAL,NOCOLOR,"圣思道二世（教宗）及同伴（殉道）")));
		mapPropers.insert(std::make_pair(1080801,CellInfo(MEMORIAL,WHITE,"圣道明（司铎）")));
		mapPropers.insert(std::make_pair(1080901,CellInfo(OPTIONAL,NOCOLOR,"St. Teresa Benedicta of the Cross（童贞、殉道）")));
		mapPropers.insert(std::make_pair(1081001,CellInfo(FEAST,RED,"圣老楞佐（执事、殉道）")));
		mapPropers.insert(std::make_pair(1081101,CellInfo(MEMORIAL,WHITE,"圣女佳兰")));
		mapPropers.insert(std::make_pair(1081201,CellInfo(OPTIONAL,NOCOLOR,"Saint Jane Frances de Chantal（会士）")));
		mapPropers.insert(std::make_pair(1081301,CellInfo(OPTIONAL,NOCOLOR,"圣彭谦（教宗、殉道）及圣希玻里（司铎、殉道）")));
		mapPropers.insert(std::make_pair(1081401,CellInfo(MEMORIAL,RED,"圣高比（司铎、殉道）")));
		mapPropers.insert(std::make_pair(1081501,CellInfo(SOLEMNITY,WHITE,"圣母蒙召升天节")));
		mapPropers.insert(std::make_pair(1081601,CellInfo(OPTIONAL,NOCOLOR,"匈牙利的圣斯德望国王")));
		mapPropers.insert(std::make_pair(1081901,CellInfo(OPTIONAL,NOCOLOR,"圣若望·欧德（司铎）")));
		mapPropers.insert(std::make_pair(1082001,CellInfo(MEMORIAL,WHITE,"圣伯尔纳铎（院长、圣师）")));
		mapPropers.insert(std::make_pair(1082101,CellInfo(MEMORIAL,WHITE,"圣庇护十世（教宗）")));
		mapPropers.insert(std::make_pair(1082201,CellInfo(MEMORIAL,WHITE,"圣母天后(圣母无玷圣心瞻礼)")));
		mapPropers.insert(std::make_pair(1082301,CellInfo(OPTIONAL,NOCOLOR,"圣罗撒")));
		mapPropers.insert(std::make_pair(1082401,CellInfo(FEAST,RED,"圣巴尔多禄茂（宗徒）")));
		mapPropers.insert(std::make_pair(1082501,CellInfo(OPTIONAL,NOCOLOR,"圣路易国王；或圣若瑟·加拉桑（司铎）")));
		mapPropers.insert(std::make_pair(1082701,CellInfo(MEMORIAL,WHITE,"圣莫尼加")));
		mapPropers.insert(std::make_pair(1082801,CellInfo(MEMORIAL,WHITE,"圣奥思定（主教、圣师）")));
		mapPropers.insert(std::make_pair(1082901,CellInfo(MEMORIAL,RED,"圣若翰洗者受难（殉道）")));
    
		//9月
		mapPropers.insert(std::make_pair(1090301,CellInfo(MEMORIAL,WHITE,"圣额我略一世（教宗、圣师）")));
		mapPropers.insert(std::make_pair(1090801,CellInfo(FEAST,WHITE,"圣母诞辰")));
		mapPropers.insert(std::make_pair(1090901,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄·高华（司铎）")));
		mapPropers.insert(std::make_pair(1091201,CellInfo(OPTIONAL,NOCOLOR,"圣母圣名节")));
		mapPropers.insert(std::make_pair(1091301,CellInfo(MEMORIAL,WHITE,"圣金口若望（主教、圣师）")));
		mapPropers.insert(std::make_pair(1091401,CellInfo(LORD,RED,"光荣十字圣架")));
		mapPropers.insert(std::make_pair(1091501,CellInfo(MEMORIAL,WHITE,"痛苦圣母")));
		mapPropers.insert(std::make_pair(1091601,CellInfo(MEMORIAL,RED,"圣高尔乃略（教宗、殉道）及圣西彼廉（主教、殉道）")));
		mapPropers.insert(std::make_pair(1091701,CellInfo(OPTIONAL,NOCOLOR,"圣罗伯·白敏（主教、圣师）")));
		mapPropers.insert(std::make_pair(1091901,CellInfo(OPTIONAL,NOCOLOR,"圣雅纳略（主教、殉道）")));
		mapPropers.insert(std::make_pair(1092001,CellInfo(MEMORIAL,RED,"圣金大建及同伴（殉道）")));
		mapPropers.insert(std::make_pair(1092101,CellInfo(FEAST,RED,"圣玛窦（宗徒、圣史）")));
		mapPropers.insert(std::make_pair(1092301,CellInfo(OPTIONAL,NOCOLOR,"圣比约神父（司铎）")));
		mapPropers.insert(std::make_pair(1092601,CellInfo(OPTIONAL,NOCOLOR,"圣葛斯及圣达弥盎（殉道）")));
		mapPropers.insert(std::make_pair(1092701,CellInfo(MEMORIAL,WHITE,"圣云先（司铎）")));
		mapPropers.insert(std::make_pair(1092801,CellInfo(OPTIONAL,NOCOLOR,"圣文策老（殉道）")));
		mapPropers.insert(std::make_pair(1092801,CellInfo(OPTIONAL,NOCOLOR,"圣老楞佐·卢斯及同伴（殉道）")));
		mapPropers.insert(std::make_pair(1092901,CellInfo(FEAST,WHITE,"圣弥额尔大天使、圣加俾额尔大天使、圣辣法尔大天使")));
		mapPropers.insert(std::make_pair(1093001,CellInfo(MEMORIAL,WHITE,"圣热罗尼莫（司铎、圣师）")));
    
		//10月
		mapPropers.insert(std::make_pair(1100101,CellInfo(MEMORIAL,WHITE,"里修的圣德兰（小德兰）（童贞、圣师）")));
		mapPropers.insert(std::make_pair(1100201,CellInfo(MEMORIAL,WHITE,"护守天使")));
		mapPropers.insert(std::make_pair(1100401,CellInfo(MEMORIAL,WHITE,"亚西西的圣方济各")));
		mapPropers.insert(std::make_pair(1100601,CellInfo(OPTIONAL,NOCOLOR,"圣博诺（司铎）")));
		mapPropers.insert(std::make_pair(1100701,CellInfo(MEMORIAL,WHITE,"玫瑰圣母")));
		mapPropers.insert(std::make_pair(1100901,CellInfo(OPTIONAL,NOCOLOR,"圣德尼及同伴（殉道）")));
		mapPropers.insert(std::make_pair(1100901,CellInfo(OPTIONAL,NOCOLOR,"圣若望·良纳第（司铎）")));
		mapPropers.insert(std::make_pair(1101101,CellInfo(MEMORIAL,WHITE,"圣若望廿三世（教宗）")));
		mapPropers.insert(std::make_pair(1101401,CellInfo(OPTIONAL,NOCOLOR,"圣加理斯多一世（教宗、殉道）")));
		mapPropers.insert(std::make_pair(1101501,CellInfo(MEMORIAL,WHITE,"亚维拉的圣德兰（大德兰）（童贞、圣师）")));
		mapPropers.insert(std::make_pair(1101601,CellInfo(OPTIONAL,NOCOLOR,"圣玛加利大·亚拉高（童贞）")));
		mapPropers.insert(std::make_pair(1101601,CellInfo(OPTIONAL,NOCOLOR,"圣赫德维（圣妇、会士）")));
		mapPropers.insert(std::make_pair(1101701,CellInfo(MEMORIAL,RED,"圣依纳爵·安提约基亚（主教、殉道）")));
		mapPropers.insert(std::make_pair(1101801,CellInfo(FEAST,RED,"圣路加（宗徒、圣史）")));
		mapPropers.insert(std::make_pair(1101901,CellInfo(MEMORIAL,RED,"圣若望·贝巴（司铎）及圣依撒格·饶觉（司铎）及同伴（殉道）")));
		mapPropers.insert(std::make_pair(1102001,CellInfo(OPTIONAL,NOCOLOR,"圣十字保禄瞻礼（司铎）")));
		mapPropers.insert(std::make_pair(1102201,CellInfo(MEMORIAL,WHITE,"圣若望·保禄二世（教宗）")));
		mapPropers.insert(std::make_pair(1102301,CellInfo(OPTIONAL,NOCOLOR,"圣若望·嘉庇当（司铎）")));
		mapPropers.insert(std::make_pair(1102401,CellInfo(OPTIONAL,NOCOLOR,"圣安多尼·加烈)（主教）")));
		mapPropers.insert(std::make_pair(1102801,CellInfo(FEAST,RED,"圣西满及圣犹达（宗徒）")));
    
		//11月
		mapPropers.insert(std::make_pair(1110101,CellInfo(SOLEMNITY,WHITE,"诸圣节")));
		mapPropers.insert(std::make_pair(1110201,CellInfo(LORD,WHITE,"追思亡者")));
		mapPropers.insert(std::make_pair(1110301,CellInfo(OPTIONAL,NOCOLOR,"圣玛尔定·包瑞斯（修士）")));
		mapPropers.insert(std::make_pair(1110401,CellInfo(MEMORIAL,WHITE,"圣嘉禄·鲍荣茂（主教）")));
		mapPropers.insert(std::make_pair(1110901,CellInfo(LORD,WHITE,"祝圣拉特朗大殿")));
		mapPropers.insert(std::make_pair(1111001,CellInfo(MEMORIAL,WHITE,"大圣良一世（教宗、圣师）")));
		mapPropers.insert(std::make_pair(1111101,CellInfo(MEMORIAL,WHITE,"圣玛尔定（都尔主教）")));
		mapPropers.insert(std::make_pair(1111201,CellInfo(MEMORIAL,RED,"圣若撒法（主教、殉道）")));
		mapPropers.insert(std::make_pair(1111501,CellInfo(OPTIONAL,NOCOLOR,"圣亚尔伯（主教、圣师）")));
		mapPropers.insert(std::make_pair(1111601,CellInfo(OPTIONAL,NOCOLOR,"苏格兰的圣玛加利大")));
		mapPropers.insert(std::make_pair(1111601,CellInfo(OPTIONAL,NOCOLOR,"圣日多达（童贞）")));
		mapPropers.insert(std::make_pair(1111701,CellInfo(MEMORIAL,WHITE,"匈牙利的圣依撒伯尔（会士）")));
		mapPropers.insert(std::make_pair(1111801,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄及圣保禄大殿奉献日")));
		mapPropers.insert(std::make_pair(1112101,CellInfo(MEMORIAL,WHITE,"献圣母于主堂")));
		mapPropers.insert(std::make_pair(1112201,CellInfo(MEMORIAL,RED,"圣则济利亚（童贞、殉道）")));
		mapPropers.insert(std::make_pair(1112301,CellInfo(OPTIONAL,NOCOLOR,"圣克来孟一世（教宗、殉道）")));
		mapPropers.insert(std::make_pair(1112301,CellInfo(OPTIONAL,NOCOLOR,"圣高隆邦（院长）")));
		mapPropers.insert(std::make_pair(1112401,CellInfo(MEMORIAL,RED,"圣陈安勇乐（司铎）及同伴（殉道）")));
		mapPropers.insert(std::make_pair(1112501,CellInfo(OPTIONAL,NOCOLOR,"亚历山大的圣凯瑟琳（童贞、殉道）")));
		mapPropers.insert(std::make_pair(1113001,CellInfo(FEAST,RED,"圣安德肋（宗徒）")));
    
		//12月
		mapPropers.insert(std::make_pair(1120301,CellInfo(MEMORIAL,WHITE,"圣方济沙勿略（司铎）")));
		mapPropers.insert(std::make_pair(1120401,CellInfo(OPTIONAL,NOCOLOR,"圣若望·达玛森（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1120601,CellInfo(OPTIONAL,NOCOLOR,"圣尼各老（主教）")));
		mapPropers.insert(std::make_pair(1120701,CellInfo(MEMORIAL,WHITE,"圣安博（主教、圣师）")));
		mapPropers.insert(std::make_pair(1120801,CellInfo(SOLEMNITY,WHITE,"圣母无玷始胎")));
		mapPropers.insert(std::make_pair(1120901,CellInfo(OPTIONAL,NOCOLOR,"圣若望·迭戈")));
		mapPropers.insert(std::make_pair(1121001,CellInfo(MEMORIAL,WHITE,"洛雷托圣母")));
		mapPropers.insert(std::make_pair(1121101,CellInfo(OPTIONAL,NOCOLOR,"圣达玛稣一世（教宗）")));
		mapPropers.insert(std::make_pair(1121201,CellInfo(FEAST,WHITE,"瓜达卢佩圣母")));
		mapPropers.insert(std::make_pair(1121301,CellInfo(MEMORIAL,RED,"圣路济亚（贞女、殉道）")));
		mapPropers.insert(std::make_pair(1121401,CellInfo(MEMORIAL,WHITE,"圣十字若望（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1122101,CellInfo(OPTIONAL,NOCOLOR,"圣加尼修（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1122301,CellInfo(OPTIONAL,NOCOLOR,"圣若望·甘迪")));
		mapPropers.insert(std::make_pair(1122501,CellInfo(SOLEMNITY,WHITE,"吾主诞生日（圣诞节）")));
		mapPropers.insert(std::make_pair(1122601,CellInfo(FEAST,RED,"圣斯德望（首位殉道）")));
		mapPropers.insert(std::make_pair(1122701,CellInfo(FEAST,WHITE,"圣若望（宗徒、圣史）")));
		mapPropers.insert(std::make_pair(1122801,CellInfo(FEAST,RED,"诸圣婴孩")));
		mapPropers.insert(std::make_pair(1122901,CellInfo(OPTIONAL,NOCOLOR,"圣多玛斯·百克（主教、殉道）")));
		mapPropers.insert(std::make_pair(1123101,CellInfo(OPTIONAL,NOCOLOR,"圣西物斯德一世（教宗）")));
	}


	/*
	// 由礼仪年确定的特殊节日
	// 规则：采用十进制（共六位）
	// 前面两位为：Season
	// 中间两位为：主日编号
	// 最后两位为：星期几
	*/
	{
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
		mapPropers.insert(std::make_pair(EASTER*10000+400+0,CellInfo(SUNDAY,WHITE,"复活期第四主日（善牧主日）")));
		//耶稣升天（复活期第六主日星期四）
		mapPropers.insert(std::make_pair(EASTER*10000+600+4,CellInfo(SOLEMNITY,WHITE,"耶稣升天")));
		//圣神降临节（复活期第八主日）
		mapPropers.insert(std::make_pair(EASTER*10000+800+0,CellInfo(SOLEMNITY,RED,"圣神降临节")));

		//常年期第三十四主日（基督普世君王节）
		mapPropers.insert(std::make_pair(ORDINARY*10000+3400+0,CellInfo(SOLEMNITY,WHITE,"基督普世君王节")));
	}

	/*
	// 特殊节日
	// 索引从1开始
	*/
	{
		mapPropers.insert(std::make_pair(1,CellInfo(SOLEMNITY,WHITE,"主显节")));
		mapPropers.insert(std::make_pair(2,CellInfo(LORD,WHITE,"主受洗日")));

		//从复活节算起的节日
		mapPropers.insert(std::make_pair(3,CellInfo(LORD,WHITE,"我们的主耶稣基督—永恒的大司祭")));	//复活节后53日
		mapPropers.insert(std::make_pair(4,CellInfo(SOLEMNITY,WHITE,"圣三主日")));					//复活节后56日（复活期后的主日）
		mapPropers.insert(std::make_pair(5,CellInfo(SOLEMNITY,WHITE,"基督圣体圣血节")));			//复活节后60日
		mapPropers.insert(std::make_pair(6,CellInfo(SOLEMNITY,WHITE,"耶稣圣心节")));				//复活节后68日
		mapPropers.insert(std::make_pair(7,CellInfo(MEMORIAL,WHITE,"圣母无玷圣心")));				//复活节后69日

		//圣诞期
		mapPropers.insert(std::make_pair(8,CellInfo(LORD,WHITE,"圣家节")));

		//中华圣母（五月份的第二个星期六）
		mapPropers.insert(std::make_pair(9,CellInfo(MEMORIAL,WHITE,"中华圣母")));
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
	if(ld<bl)
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
	av = t.addDays(0-t.dayOfWeek());

	//圣诞节
	cm.setDate(year,12,25);
}

void LiturgicYear::testChristmas1(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<LiturgicDay(year,1,1) || ld>bl)
		return;

	ld.setSeason(CHRISTMAS);

	Date lastChristmas(year-1,12,25);
	int dayFromLC = lastChristmas.daysTo(ld);
	ld.setWeekOfSeason((dayFromLC-(lastChristmas.dayOfWeek()-1))/7 + 1);

	if(ld<ep)
	{

	}
	else if(ld==ep)
	{
		ld.appendCell(1);	//主显节（普世教会）
	}
	else if(ld<bl)
	{

	}

	if(ld.month()==1&&ld.day()==6)
	{
		ld.appendCell(1);	//主显节（大陆教会）
	}
}

void LiturgicYear::testOrdinary1(LiturgicDay& ld)
{
	if((!ld.isValid()) || ld<bl || ld>=aw)
		return;

	ld.setSeason(ORDINARY);
//	int weekBegin = aw.weekNumber();
	ld.setWeekOfSeason( ld.weekNumber()-bl.weekNumber()+1 );

	if(ld == bl)
	{
		ld.appendCell(2);	//主受洗日
	}

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
	else if(dayFromEaster == 60)
	{
		//可移至主日庆祝 + 63
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
	if(cm.dayOfWeek() == SUN && ld==Date(year,12,31))
	{
		ld.setWeekOfSeason(2);
	}
	else
	{
		ld.setWeekOfSeason(1);
	}

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
