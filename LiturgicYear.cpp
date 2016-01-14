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
		//1月
		mapPropers.insert(std::make_pair(1010101,CellInfo(SOLEMNITY,WHITE,"天主之母节")));
		mapPropers.insert(std::make_pair(1010201,CellInfo(MEMORIAL,WHITE,"圣巴西略及圣额我略·纳齐安（主教、圣师)")));
		mapPropers.insert(std::make_pair(1010301,CellInfo(OPTIONAL,NOCOLOR,"耶稣圣名节")));
		//1月6日的主显节方式已不再使用（但因没有经过主教团批准，所以暂时未在大陆使用）
		//mapPropers.insert(std::make_pair(1010601,CellInfo(SOLEMNITY,WHITE,"主显节")));
		mapPropers.insert(std::make_pair(1010701,CellInfo(OPTIONAL,NOCOLOR,"圣雷孟（司铎）")));
		mapPropers.insert(std::make_pair(1011301,CellInfo(OPTIONAL,NOCOLOR,"圣依拉略（主教、圣师）")));
		mapPropers.insert(std::make_pair(1011701,CellInfo(MEMORIAL,WHITE,"圣安东尼（院长）")));
		mapPropers.insert(std::make_pair(1011801,CellInfo(OPTIONAL,NOCOLOR,"为基督徒合一祈祷周（18 - 25日）")));
		mapPropers.insert(std::make_pair(1012001,CellInfo(OPTIONAL,NOCOLOR,"圣法比盎（教宗、殉道)")));
		mapPropers.insert(std::make_pair(1012001,CellInfo(OPTIONAL,NOCOLOR,"圣巴斯弟盎（殉道）")));
		mapPropers.insert(std::make_pair(1012101,CellInfo(MEMORIAL,RED,"圣依搦斯（童贞、殉道)")));
		mapPropers.insert(std::make_pair(1012201,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵（执事、殉道）")));
		mapPropers.insert(std::make_pair(1012401,CellInfo(MEMORIAL,WHITE,"圣方济各·沙雷氏（主教、圣师）")));
		mapPropers.insert(std::make_pair(1012501,CellInfo(FEAST,WHITE,"圣保禄归化（宗徒）")));
		mapPropers.insert(std::make_pair(1012601,CellInfo(MEMORIAL,WHITE,"圣弟茂德与圣弟铎（主教）")));
		mapPropers.insert(std::make_pair(1012701,CellInfo(OPTIONAL,NOCOLOR,"圣安琪拉·美利西（童贞）")));
		mapPropers.insert(std::make_pair(1012801,CellInfo(MEMORIAL,WHITE,"圣多玛斯·阿奎纳（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1013101,CellInfo(MEMORIAL,WHITE,"圣若望·鲍思高（司铎）")));

		//2月
		mapPropers.insert(std::make_pair(1020201,CellInfo(LORD,WHITE,"献主节")));
		mapPropers.insert(std::make_pair(1020301,CellInfo(OPTIONAL,NOCOLOR,"圣巴拉斯（主教、殉道）")));
		mapPropers.insert(std::make_pair(1020301,CellInfo(OPTIONAL,NOCOLOR,"圣安斯卡（主教）")));
		mapPropers.insert(std::make_pair(1020501,CellInfo(MEMORIAL,RED,"圣女亚加大（殉道）")));
		mapPropers.insert(std::make_pair(1020601,CellInfo(MEMORIAL,RED,"圣保禄三木及同伴（日本殉道者）")));
		mapPropers.insert(std::make_pair(1020801,CellInfo(OPTIONAL,NOCOLOR,"圣热罗尼莫·艾明廉")));
		mapPropers.insert(std::make_pair(1020801,CellInfo(OPTIONAL,NOCOLOR,"St. Josephine Margaret Bakhita（童贞）")));
		mapPropers.insert(std::make_pair(1021001,CellInfo(MEMORIAL,WHITE,"圣思嘉（童贞）")));
		mapPropers.insert(std::make_pair(1021101,CellInfo(OPTIONAL,NOCOLOR,"露德圣母")));
		mapPropers.insert(std::make_pair(1021401,CellInfo(MEMORIAL,WHITE,"圣济利禄（隐修士）及圣默多狄（主教）")));
		mapPropers.insert(std::make_pair(1021701,CellInfo(OPTIONAL,NOCOLOR,"圣母忠仆会七位会祖")));
		mapPropers.insert(std::make_pair(1022101,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄·达弥盎（主教、圣师）")));
		mapPropers.insert(std::make_pair(1022201,CellInfo(FEAST,WHITE,"建立圣伯多禄宗座")));
		mapPropers.insert(std::make_pair(1022301,CellInfo(MEMORIAL,RED,"圣玻里加（主教、殉道）")));
    
		//3月
		mapPropers.insert(std::make_pair(1030401,CellInfo(OPTIONAL,NOCOLOR,"圣加西弥禄（殉道）")));
		mapPropers.insert(std::make_pair(1030701,CellInfo(MEMORIAL,RED,"圣女伯尔都亚及圣女斐尼丝（殉道)")));
		mapPropers.insert(std::make_pair(1030801,CellInfo(OPTIONAL,NOCOLOR,"圣若望由天主者（会士）")));
		mapPropers.insert(std::make_pair(1030901,CellInfo(OPTIONAL,NOCOLOR,"圣女方济加·露雯（修女）")));
		mapPropers.insert(std::make_pair(1031701,CellInfo(OPTIONAL,NOCOLOR,"圣博德（主教）")));
		mapPropers.insert(std::make_pair(1031801,CellInfo(OPTIONAL,NOCOLOR,"耶路撒冷的圣济利禄（主教、圣师）")));
		mapPropers.insert(std::make_pair(1031901,CellInfo(SOLEMNITY,WHITE,"大圣若瑟，童贞圣母玛利亚净配")));
		mapPropers.insert(std::make_pair(1032301,CellInfo(OPTIONAL,NOCOLOR,"圣多利坡（主教）")));
		mapPropers.insert(std::make_pair(1032501,CellInfo(SOLEMNITY,WHITE,"圣母领报")));
    
		//4月
		mapPropers.insert(std::make_pair(1040201,CellInfo(OPTIONAL,NOCOLOR,"圣方济各保拉（隐修士）")));
		mapPropers.insert(std::make_pair(1040401,CellInfo(OPTIONAL,NOCOLOR,"圣依西多禄（主教、圣师）")));
		mapPropers.insert(std::make_pair(1040501,CellInfo(OPTIONAL,NOCOLOR,"圣味增爵斐洛（司铎）")));
		mapPropers.insert(std::make_pair(1040701,CellInfo(MEMORIAL,WHITE,"圣若翰·喇沙（司铎）")));
		mapPropers.insert(std::make_pair(1041101,CellInfo(MEMORIAL,RED,"圣达尼老（主教、殉道）")));
		mapPropers.insert(std::make_pair(1041301,CellInfo(OPTIONAL,NOCOLOR,"圣玛尔定一世（教宗、殉道）")));
		mapPropers.insert(std::make_pair(1042101,CellInfo(OPTIONAL,NOCOLOR,"圣安瑟莫（主教、圣师）")));
		mapPropers.insert(std::make_pair(1042301,CellInfo(OPTIONAL,NOCOLOR,"圣乔治（殉道）")));
		mapPropers.insert(std::make_pair(1042301,CellInfo(OPTIONAL,NOCOLOR,"布拉格的圣道博")));
		mapPropers.insert(std::make_pair(1042401,CellInfo(OPTIONAL,NOCOLOR,"圣斐德理（司铎、殉道）")));
		mapPropers.insert(std::make_pair(1042501,CellInfo(FEAST,RED,"圣马尔谷（圣史）")));
		mapPropers.insert(std::make_pair(1042801,CellInfo(OPTIONAL,NOCOLOR,"圣伯多禄·查纳（司铎、殉道）")));
		mapPropers.insert(std::make_pair(1042801,CellInfo(OPTIONAL,NOCOLOR,"圣路易·蒙福（司铎）")));
		mapPropers.insert(std::make_pair(1042901,CellInfo(MEMORIAL,WHITE,"圣女加大利纳（贞女、圣师）")));
		mapPropers.insert(std::make_pair(1043001,CellInfo(OPTIONAL,NOCOLOR,"圣庇护五世（教宗）")));
    
		//5月
		mapPropers.insert(std::make_pair(1050101,CellInfo(OPTIONAL,NOCOLOR,"圣若瑟劳工主保")));
		mapPropers.insert(std::make_pair(1050201,CellInfo(MEMORIAL,WHITE,"圣亚大纳修（主教、圣师）")));
		mapPropers.insert(std::make_pair(1050301,CellInfo(FEAST,RED,"圣斐理伯与圣雅各伯（宗徒）")));
		mapPropers.insert(std::make_pair(1051201,CellInfo(OPTIONAL,NOCOLOR,"圣庞加爵（殉道）")));
		mapPropers.insert(std::make_pair(1051201,CellInfo(OPTIONAL,NOCOLOR,"圣聂勒及圣亚基略（殉道）")));
		mapPropers.insert(std::make_pair(1051301,CellInfo(OPTIONAL,NOCOLOR,"花地玛圣母")));
		mapPropers.insert(std::make_pair(1051401,CellInfo(FEAST,RED,"圣玛弟亚（宗徒）")));
		mapPropers.insert(std::make_pair(1051801,CellInfo(OPTIONAL,NOCOLOR,"圣若望一世（教宗、殉道）")));
		mapPropers.insert(std::make_pair(1052001,CellInfo(OPTIONAL,NOCOLOR,"圣伯尔纳定（司铎）")));
		mapPropers.insert(std::make_pair(1052101,CellInfo(OPTIONAL,NOCOLOR,"圣多福·麦哲伦（司铎）及其他殉道者（殉道）")));
		mapPropers.insert(std::make_pair(1052201,CellInfo(OPTIONAL,NOCOLOR,"圣李达（绝望主保）")));
		mapPropers.insert(std::make_pair(1052401,CellInfo(FEAST,WHITE,"进教之佑圣母")));
		mapPropers.insert(std::make_pair(1052501,CellInfo(OPTIONAL,NOCOLOR,"圣伯达（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1052501,CellInfo(OPTIONAL,NOCOLOR,"圣额我略七世（教宗）")));
		mapPropers.insert(std::make_pair(1052501,CellInfo(OPTIONAL,NOCOLOR,"圣玛达肋纳·巴斯（童贞）")));
		mapPropers.insert(std::make_pair(1052601,CellInfo(MEMORIAL,WHITE,"圣斐理伯·内利（司铎）")));
		mapPropers.insert(std::make_pair(1052701,CellInfo(OPTIONAL,NOCOLOR,"坎特伯雷的圣奥思定（主教）")));
		mapPropers.insert(std::make_pair(1053101,CellInfo(FEAST,WHITE,"圣母访亲")));
    
		//6月
		mapPropers.insert(std::make_pair(1060101,CellInfo(MEMORIAL,RED,"圣犹思定（殉道）")));
		mapPropers.insert(std::make_pair(1060201,CellInfo(OPTIONAL,NOCOLOR,"圣玛策林及圣伯多禄（殉道）")));
		mapPropers.insert(std::make_pair(1060301,CellInfo(MEMORIAL,RED,"圣嘉禄·安加及同伴（乌干达殉道者）")));
		mapPropers.insert(std::make_pair(1060501,CellInfo(MEMORIAL,RED,"圣玻尼法（主教、殉道）")));
		mapPropers.insert(std::make_pair(1060601,CellInfo(OPTIONAL,NOCOLOR,"圣诺伯多（主教）")));
		mapPropers.insert(std::make_pair(1060901,CellInfo(OPTIONAL,NOCOLOR,"圣义范（执事、圣师）")));
		mapPropers.insert(std::make_pair(1061101,CellInfo(MEMORIAL,RED,"圣巴尔纳伯（宗徒）")));
		mapPropers.insert(std::make_pair(1061301,CellInfo(MEMORIAL,WHITE,"圣安多尼·巴都亚（司铎、圣师）")));
		mapPropers.insert(std::make_pair(1061901,CellInfo(OPTIONAL,NOCOLOR,"圣罗慕德（院长）")));
		mapPropers.insert(std::make_pair(1062101,CellInfo(MEMORIAL,WHITE,"圣类思·公撒格（会士）")));
		mapPropers.insert(std::make_pair(1062201,CellInfo(OPTIONAL,NOCOLOR,"圣保林（主教）")));
		mapPropers.insert(std::make_pair(1062201,CellInfo(OPTIONAL,NOCOLOR,"圣若望·费舍（主教、殉道）及圣托马斯·莫尔（殉道）")));
		mapPropers.insert(std::make_pair(1062401,CellInfo(SOLEMNITY,WHITE,"圣若翰洗者诞生")));
		mapPropers.insert(std::make_pair(1062701,CellInfo(OPTIONAL,NOCOLOR,"圣济利禄（主教、圣师）")));
		mapPropers.insert(std::make_pair(1062801,CellInfo(MEMORIAL,RED,"圣爱任纽（主教、殉道）")));
		mapPropers.insert(std::make_pair(1062901,CellInfo(SOLEMNITY,RED,"圣伯多禄及圣保禄（宗徒）")));
		mapPropers.insert(std::make_pair(1063001,CellInfo(OPTIONAL,NOCOLOR,"罗马教会初期殉道烈士")));
    
		//7月
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
