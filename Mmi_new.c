
#include<7188xa.h>
#include<math.h>

#define Max_pnt           4   /*ç¨á«® â®ç¥ª ãçñâ */
#define Key_0        0x30
#define Key_1        0x31
#define Key_2        0x32
#define Key_3        0x33
#define Key_4        0x34
#define Key_5        0x35
#define Key_6        0x36
#define Key_7        0x37
#define Key_8        0x38
#define Key_9        0x39
#define Key_A        0x41
#define Key_B        0x42
#define Key_C        0x43
#define Key_D        0x44
#define Key_E        0x45
#define Key_F        0x46
#define Key_K        0x4b
#define Key_M        0x4d
#define Key_N        0x4e
#define Key_O        0x4f
#define Key_P        0x50
#define Key_T        0x54
#define Key_S        0x53

#define Key_blank    0x20
#define Key_dot      0x2e
#define Key_comma    0x2c
#define Key_termin    0xd
#define Key_modbus    0xa
#define Key_mask      0xf
#define Key_minus    0x2d
#define Key_dies     0x23
#define Key_cursor   0x5f
#define Key_usa      0x24
#define Key_adr      0x40

#define Len_name       16
#define Max_mmi_main   11
#define Max_mmi_point   7
#define Max_mmi_select  6
#define Max_mmi_exp     7
#define Len_select      4
#define Max_conf_all  101
#define Max_units_all  33
#define Max_sel_all   123
#define Max_number     40
#define Max_name_pnt    3
#define Max_dynam_all  71
struct cursor_mmi
{
  unsigned char enb; 
  unsigned char mode;
  unsigned char row,old;
  unsigned char size;
};
struct display_mmi
{
  unsigned char row,         /*áâà®ª  ®â 0 ¤® 5*/
		point,       /*­®¬¥à ¢ë¡à ­­®© â®çª¨*/
		flag,        /*¯à¨§­ ª ®¡­®¢«¥­¨ï ¢ë¢®¤  á¯¨áª  ¨¬ñ­*/
		num,         /*­®¬¥à à è¨à¥­¨ï ®â 0 ¤® 6*/
		evt,         /*á®¡ëâ¨¥(¢á¥£® âà¨)*/
		write,       /*¯à¨§­ ª ¨§¬¥­¥­¨ï ª®­ä¨£ãà æ¨¨*/
		prm,         /*­®¬¥à ¯ à ¬¥âà  ¢ á¯¨áª¥ ¤¨­ ¬.¯ à ¬¥âà®¢*/
		page,        /*áâà ­¨æ  ¤¨á¯«¥ï*/
		old,         /*åà ­¨â áâà ­¨æã ¬¥­î ¤«ï ¢®§¢à â */
	     suspend;        /*¯à¨®áâ ­®¢ª  ®¯à®á  ª« ¢¨ â ¤«ï ¬¥­î*/
  int pointer;
  unsigned char arch_num,size;
  unsigned char ret[5],ind_ret;
};
struct cursor_mmi             Cursor;
struct display_mmi            Display;
unsigned char *str_menu[]={
 "Îáùèå íàñòðîéêè âû÷èñëèòåëÿ",
 "Ïåðåìåííûå ïðîöåññà","Íàñòðîéêè ïðîöåññà","Àðõèâ ïàðàìåòðîâ ñóòî÷íûé",
 "Àðõèâ ïàðàìåòðîâ ÷àñîâîé","Íàñòðîéêè òîêîâûõ ìîäóëåé","Ìîäóëè òîêîâîãî âõîäà",
 "Ìíîãîêàíàëüíûå äàò÷èêè","Ñ÷åò÷èêè èìïóëüñîâ","Èíèöèàëèçàöèÿ ìîäåìà","Êîððåêöèÿ äàòà-âðåìÿ"};
unsigned char *str_menu1[]={
 "Ïåðâàÿ òî÷êà ó÷åòà",
 "Âòîðàÿ òî÷êà ó÷åòà","Òðåòüÿ òî÷êà ó÷åòà","×åòâåðòàÿ òî÷êà ó÷åòà"};
unsigned char *str_menu2[]={"Ïåðâûé ïðèáîð","Âòîðîé ïðèáîð","Òðåòèé ïðèáîð","×åòâåðòûé ïðèáîð"};


const unsigned char psw[10] = {205,229,228,238,241,242,243,239,229,237};
/*­ áâà®©ª¨ ¯®àâ */
const unsigned char set_pr[3] = {0,2,1};
const unsigned char set_st[2] = {1,2};
const unsigned char set_dt[2] = {8,7};
const unsigned long set_bd[8] = {1200,2400,4800,9600,19200,38400,57600,115200};
const char *conf_all[]={
" ",
"Ñòàòóñ òî÷êè","Âûáîð ñóæàþùåãî óñòðîéñòâà","Âûáîð âõîäà äèôôäàâëåíèÿ",
"Âûáîð âõîäà äàâëåíèÿ","Âûáîð âõîäà òåìïåðàòóðû","Âûáîð âõîäà âò. äèôô",
"Ñòàòóñ àëàðìîâ","Âûáîð òåïëîíîñèòåëÿ","Ìåæïîâåðî÷íûé èíòåðâàë",
"Åäèíèöû ýíåðãèè","Äèàìåòð òðóáîïðîâîäà","Äèàìåòð (øèðèíà) ÑÓ",
"Îòñå÷êà ìèíèì ðàñõîäà","Âåðõíèé ïåðåêë äèôôìàí","Íèæíèé ïåðåêë äèôôìàí",
"Íà÷àëüíûé ðàäèóñ êðîìêè","Øåðîõîâàòîñòü òðóáîïðîâîäà",
"ÊÒÐ À òðóáîïðîâîäà","ÊÒÐ Â òðóáîïðîâîäà","ÊÒÐ Ñ òðóáîïðîâîäà",
"ÊÒÐ À ñóæàþùåãî óñòð","ÊÒÐ Â ñóæàþùåãî óñòð","ÊÒÐ Ñ ñóæàþùåãî óñòð",
"Íèæíèé àëàðì ðàñõîäà","Âåðõíèé àëàðì ðàñõîäà","Íèæíèé àëàðì äèôôäàâë",
"Âåðõíèé àëàðì äèôôäàâë","Ãèñòåðåç àëì äèôôäàâ","Íèæíèé àëàðì äàâëåíèÿ",
"Âåðõíèé àëàðì äàâëåíèÿ","Ãèñòåðåç àëì äàâëåíèÿ","Íèæíèé àëàðì òåìïåðàòóðû",
"Âåðõíèé àëàðì òåìïåðàò","Ãèñòåðåç àëì òåìïåðàò","Òåã èäåíòèôèêàòîð",
"Àäðåñ âû÷èñëèòåëÿ","Êîíòðàêòíûé ÷àñ","Òåðìèíàë îïåðàòîðà",
"Àäðåñ äàò÷èêà MVS #1","Àäðåñ äàò÷èêà MVS #2","Àäðåñ äàò÷èêà MVS #3",
"Àäðåñ äàò÷èêà MVS #4","Ïåðåõîä íà çèìíåå/ëåò","Ïàðîëü îïåðàòîðà",
"Àäðåñ ìîäóëÿ ICP #1","Àäðåñ ìîäóëÿ ICP #2","Àäðåñ ìîäóëÿ ICP #3",
"Àäðåñ ìîäóëÿ ICP #4","Ãëàâíûé ïàðîëü","Òåëåôîííûé íîìåð",
"Íàñòðîéêà ìîäåìà","Òèï ìîäóëÿ ICP #1","Òèï ìîäóëÿ ICP #2",
"Òèï ìîäóëÿ ICP #3","Òèï ìîäóëÿ ICP #4","Ìàòåðèàë òðóáîïðîâîäà",
"Ìàòåðèàë ñóæ óñòð","Êîíôèãóðàöèÿ Modbus","Íàñòðîéêè ïîðòà COM",
"Àðõèâíàÿ #","Ñïîñîá òåðìîêîððåêöèè","Êîíôèãóðàöèÿ Hart",
"Êîððåêöèÿ ìèí ðàñõîäà","Ìåòîä ðàñ÷åòà","Åäèíèöû èçìåðåí AIN #",
"Íèæíÿÿ ãðàíèöà AIN #","Âåðõíÿÿ ãðàíèöà AIN #","Ïàðàìåòð #",
"Ïëîòíîñòü","Àçîò","Óãëåêèñëûé ãàç","Ïîðò îïåðàòîðà","Data #",
"Îáðàáîòêà ñêðèïòà","Ñïîñîá ðàñ÷åòà êðîìêè","Ãèñòåðåç àëì ðàñõîäà",
"Åäèíèöû èçìåðåíèÿ AOT #","Íèæíÿÿ ãðàíèöà AOT #",
"Âåðõíÿÿ ãðàíèöà AOT #"," "," "," "," "," "," "," "," "," "," ",
"Ãîä","Ìåñÿö","Äåíü","×àñ","Ìèíóòà"," "," "," "," ","Èìïóëüñ/åäèíèöà #",
"Ñóõîñòü ïàðà","Âûáîð âõîäà ðàñõîä",
};
 const char *dyn_all[]={
 " ","Äèôôäàâëåíèå","Äàâëåíèå àáñ","Òåìïåðàòóðà",
 "Ïëîòíîñòü","Ðàñõîä ìàñ","Ðàñõîä îáì","Ýíòàëüïèÿ",
 "Ìàññà çà ïð.÷àñ ","Îáúåì çà ïð.÷àñ ","Ìàññà ìåñÿö ","Ýíåðãèÿ çà ïð.÷àñ ",
 "Àçîò","Óãë ãàç","Îáúåì ìåñÿö","Ìåòàí", "Ýòàí","Ïðîïàí",
 "Ýíåðãèÿ ìåñ","í-Áóòàí","Ê ñæèìàåìîñòè",
 "Ê ðàñõîäà","Ê ðàñøèðåíèÿ","Ê íåîñòðîòû","Ê øåðîõîâàòîñòè",
 "Ê Ðåéíîëüäñà","×èñëî Ðåéíîëüäñà","Âÿçêîñòü",
 "Ñêîðîñòü ïîòîêà","Äàâëåíèå íàñûùåí","Ïîêàçàòåëü àäèàáàòû",
 "Ìàññà íàêîï","Îáúåì íàêîï","è-Áóòàí","í-Ïåíòàí","è-Ïåíòàí",
 "Ãåêñàí","Ýíåðãèÿ","Ýíåðãèÿ íàê","Ãåïòàí","Îêòàí",
 "Íîíàí","Äåêàí","Óãàð ãàç","Êèñëîðîä","Âîäîðîä","Ñåðíèñò ãàç",
 "Ãåëèé","Ðàñõîä","Ïëîòíîñòü ðàá","Êàíàë "," "," "," "," ",
 " "," "," "," "," "," "," "," "," "," "," "," "," "," ",
 "Ðàñõîä ïð ÷àñ ","Ê èñòå÷åíèÿ"
 };
/*[0]-­®¬¥à ¯ à ¬¥âà 
  [1]- ¤à¥á ¯¥à¢®£® ¡ ©â  ¯ à ¬¥âà 
  [2]-¯à¨§­ ª ¯ à®«ï:1-¯ à®«ì ­ã¦¥­
  [3]-â¨¯ ¤ ­­ëå:0-áâà®ª ,1-¡ ©â,2-®¤¨­.¢ë¡®à,3-¬­®¦.¢ë¡®à,
      4-¢¥é¥áâ¢.,5-¤«¨­.æ¥«®¥*/
const char *name_mmi_exp[]={
 " "," ÷àñ"," ñóòêè"," ï ñóò"," ìåñÿö", " ï ìåñ"," ãîä"};
const char *units_all[]={
 " "," ìì"," êÏà"," ãðÑ"," ì3/÷"," ò/÷",
 " ÃÄæ"," Ãêàë"," êã/ì3"," Ïà*ñ"," ì/ñ"," Å-6/ãÑ",
 " êÄæ/êã"," ò"," ì3"," ÃÄæ/÷"," Ãêë/÷"," ñòì3/÷",
 " ñò.ì3"," êêë/êã"," ìîëü %"," îáì %"," ãîä"," ò ñòì3",
 " êã/÷"," ëèòð/÷"," êã"," ëèòðû"," áë ðóá"," ìÏà*ñ",
 " %"," B"," ã/ñì3"
};
const char *name_sel_all[]={
"Îòêëþ÷åíî","Âêëþ÷åíî","Äèàôðàãìà (Óãëîâîé)",
"Äèàôðàãìà (Ôëàíöåâ)","Äèàôðàãìà (Òðåõðàä)",
"Àííóáàð +10S","Àííóáàð +15/16S","Àííóáàð +25/26S",
"Àííóáàð +35/36S","Àííóáàð +45/46S","Àííóáàð 485_Size_1",
"Àííóáàð 485_Size_2","Àííóáàð 485_Size_3",
"Âíåøíèé ðàñõîäîìåð","Êîíñòàíòà","MVS #1","MVS #2","MVS #3",
"MVS #4","AIN #1","AIN #2","AIN #3","AIN #4","AIN #5",
"AIN #6","AIN #7","AIN #8","AIN #9","AIN #10","AIN #11",
"AIN #12","AIN #13","AIN #14","AIN #15","AIN #16",
"Ìîäóëü DIO ïåðâûé","Ìîäóëü DIO âòîðîé","RTD #3","RTD #4",
"RTD #5","RTD #6","Âîäà","Ïàð","Ñòàíäàðò (äæîóëè)",
"Ïîëüçîâàò (êàëîðèè)","Äèôôäàâëåíèå","Äàâëåíèå",
"Òåìïåðàòóðà","Ðàñõîä ìãíîâåííûé","Áðóòòî ",
" ",
"Ïîäêëþ÷åí ê ÑÎÌ1","Ïîäêëþ÷åí ê ÑÎÌ2","Àâòî",
"Çèìíåå","Ìîäóëü AIN ïåðâûé","Ìîäóëü AIN âòîðîé",
"Ìîäóëü AOUT ïåðâûé","Ìîäóëü AOUT âòîðîé","Ìàòåðèàë",
"Êîýôôèöèåíò","Ñòàëü 8","Ñòàëü 10","Ñòàëü 15",
"Ñò 15Ì/20Ì","Ñòàëü 16Ì","Ñòàëü 20","Ñòàëü 25",
"Ñòàëü 30/35","Õ6ÑÌ/Õ7ÑÌ","12ÌÕ","12Õ18Í9/10Ò",
"316 (S31600/CF8M)","14X17H2","15ÕÌÀ","15X1Ì10",
"15Õ5Ì","17Õ18Í9","20Õ23Í13","36Õ18Í25Ñ2","301 (S30100)",
"12X1ÌÔ","15Õ1Ì1Ô","15Õ12ÅÍÌÔ","NX-19 mod","GERG-91 mod",
"ÂÍÈÖ-ÑÌÂ","Ôèêñèðîâàííàÿ","Èçìåíÿåìàÿ","I-7060","I-7080",
"I-7040","Äîçèðîâàííîå","Äî çàïîëíåíèÿ","Îò êîìïüþòåðà",
"Àâòîíîìíîå","Çà ïåðèîä ïîâåðêè","Çà âðåìÿ ýêñïëóàòàö",
"Ñòàëü 40/45","Ñòàëü 20Ë","Ñòàëü 25Ë","Ñòàëü 35Ë",
"Ñòàëü 45Ë","12Õ18Í10Ò/12Ò","12Õ18Í9ÒË","25Õ1ÌÔ",
"18Õ2Í4ÌÀ","12Õ19Í9Ò","10Õ14Ã14Í4Ò","31Õ19Í9ÌÂÁÒ",
"37Õ12Í8Ã8ÌÔÁ"," "," "," ","Ìîäóëü PIN ïåðâûé ","Äèàôðàãìà 1195",
"Ìîäóëü RTD","RTD #1","RTD #2","RTD #3","RTD #4",
"RTD #5","RTD #6"
};
const unsigned char name_mmi_select[Max_mmi_select][Len_select]={
 {0x22,0x31,0x22,0x20},{0x22,0x32,0x22,0x20},{0x22,0x33,0x22,0x20},
 {0x22,0x34,0x22,0x20},{0x22,0x35,0x22,0x20},{0x22,0x36,0x22,0x20},};
const unsigned char name_arch[Max_name_pnt][6]={{205,229,238,239,240,0x20},/*¥®¯à*/
 {193,224,231,238,226,Key_dies},/* §®¢*/{196,238,239,238,235,237}/*„®¯®«­*/};
unsigned char mmi_str[30],Size_str;/* ¡ãä¥à ª« ¢¨ âãàë ¨ ¤¨á¯«¥ï âà¥â¨© ¯®àâ */
unsigned char Vertical,Horizont,/*¯®§¨æ¨ï á¨¬¢®«  8*30 */
	      mmi_pass,/*­®¬¥à ¯à®å®¤  ¯à¨ ®â®¡à ¦¥­¨¨ áâà®ª¨*/
	      enter_ind,/*¢ ª®­ä¨£:ç¨á«® ¢¢®¤ á¨¬¢®«®¢*/
	      mmi_num_sel,/*ç¨á«® ¢ë¡®à®¢ ¤«ï ¯ à ¬¥âà */
	      mmi_size,mmi_arc_page,flg_init;
unsigned char mmi_val[6],coord[8],count_smb,flg_modem;
int mmi_arc;/*ãª § â¥«ì  àå¨¢ */
unsigned mmi_seg,mmi_adr;/*á¥£¬¥­â ¨  ¤à¥á*/
extern unsigned char size_max;
unsigned char mmi_sel[30];



/********* ãáâ ­®¢ª  áâà ­¨æë ¤¨á¯«¥ï ****************************/
void SetDisplayPage (unsigned char page)
{ Display.evt=1; Display.page=page;}
/*************************/
void SaveOldPageMMI (void)
{
  Display.ret[Display.ind_ret]=Display.page; Display.ind_ret++;
}
/*************************/
void GoToMenuMMI (unsigned char num_page)
{
  Cursor.enb=1; Cursor.row=0; Cursor.mode=1; Display.flag=1;
  Display.row=0; Cursor.size=0; SaveOldPageMMI(); Display.num=0;
  Display.suspend=1;SetDisplayPage(num_page);
}
/******* ä®à¬¨à®¢ ­¨¥ § ¯à®á  ¢ MMI(¨­â¥àä¥©á ç¥«®¢¥ª-¬ è¨­ )****/
unsigned char SendToMMI (unsigned char typ_port)
{
  unsigned char count,i,typ_pool;unsigned char buf_mmi[40],cr[2];
  buf_mmi[0]=Key_usa;buf_mmi[1]=Key_0;buf_mmi[2]=Key_0;
  switch (Display.evt)
  {
    case 0:buf_mmi[3]=Key_K;count=4;typ_pool=15;break;/*®¯à®á ª« ¢¨ âãàë*/
    case 1:buf_mmi[3]=Key_P;buf_mmi[4]=hex_to_ascii[(Display.page >> 4) & Key_mask];
	   buf_mmi[5]=hex_to_ascii[Display.page & Key_mask];count=6;
	   typ_pool=16;Display.evt=0;break;/*ãáâ ­®¢ª  áâà ­¨æë ¤¨á¯«¥ï*/
    case 2:buf_mmi[3]=Key_T;buf_mmi[4]=hex_to_ascii[Vertical];
	   buf_mmi[5]=hex_to_ascii[(Horizont >> 4) & Key_mask];
	   buf_mmi[6]=hex_to_ascii[Horizont & Key_mask];
	   for (i=0;i< count_smb;i++) buf_mmi[7+i]=mmi_str[i];
	   count=7+count_smb;typ_pool=17;if (Display.suspend==0) Display.evt=0;break;/*¯¥à¥¤ ç  áâà®ª¨*/
    case 3:buf_mmi[3]=Key_S;count=4;typ_pool=18;Display.evt=0;break;/*®¯à®á áâà ­¨æë*/
    default:count=0;typ_pool=0;Display.evt=0;break;
  } if (count > 0)
  {
    CalcCheckSum(buf_mmi,count,cr);buf_mmi[count]=hex_to_ascii[cr[0]];
    buf_mmi[count+1]=hex_to_ascii[cr[1]];buf_mmi[count+2]=Key_termin;
    count=count+3;for (i=count;i>0;i--) buf_mmi[i]=buf_mmi[i-1];
    buf_mmi[0]=Key_termin;count++;
    if (typ_port==1) ToComBufn_1(buf_mmi,count);else
    if (typ_port==2) ToComBufn_2(buf_mmi,count);else
    if (typ_port==3) ToComBufn_3(buf_mmi,count);
  } return typ_pool;
}
/********* ¯à®¢¥àª  ­ ¦ â®© ª« ¢¨è¨  *******************************/
unsigned char KeyFound (unsigned char buf_mmi[],unsigned char code_key1,
			unsigned char code_key2,unsigned char count)
{ /*¨á¯®«ì§ã¥âáï ¤«ï ¯®¨áª  ¯ àë ª®¤®¢ ­ ¦ â®© ª« ¢¨è¨*/
  unsigned char i,j;j=0;
  for (i=4;i < count-1;)
  {
    if ((buf_mmi[i]==code_key1)&&(buf_mmi[i+1]==code_key2)) {j=1;break;}
    i=i+2;
  } if (j==0) return 0;else return 1;
}
/*********** ®ç¨áâª  ¡ãä¥à  ¢ë¢®¤  ­  íªà ­ *********************/
void ClearBuffer (void)
{
  unsigned char i;for (i=0;i< 30;i++) mmi_str[i]=Key_blank;
}
/************ ¯à¥®¡à §®¢ ¨¥ ¢ á¨¬¢®«ì­ãî áâà®ªã ******************/
void FloatToString (float val,unsigned char buf_str[],
		   unsigned char offset)
{ /*¨á¯®«ì§ã¥âáï ¯à¨ ¢ë¢®¤¥ ª®­ä¨£.¨«¨  àå¨¢­®£® §­ ç¥­¨©*/
  unsigned char i,buf[50],flag,j; double musor,value;
  flag=j=0; if (val < 0) flag=1; value=fabs(val);
  if (value < 100000)
  {
    musor=value;
    M: if (musor < 10) goto M1;
       musor=musor/10; j++; goto M;
    M1:
    value=value*pow(10,5-j); musor=modf(value, &value);
    if (musor >= 0.5) value=value+1; value=value/pow(10,5-j);
  } else modf(value, &value); if (flag == 1) value=-value;
  gcvt(value,10,buf); j=0;
  for (i=0;i<10;i++) if (buf[i] !=0) buf_str[i+offset]=buf[i]; else break;
}
/*********** ¯à¥®¡à §®¢ ­¨¥ ¡ ©â  ¢ ¤¢  á¨¬¢®«  ***********/
void ByteToString (unsigned char val,unsigned char index,unsigned char typ)
{ /*¨á¯®«ì§ã¥âáï ¯à¨ ¢ë¢®¤¥  àå¨¢­ëå ¤ âë ¨ ¢à¥¬¥­¨*/
  unsigned char a,d,e,c,b;c=10;b=val;a=0;
  while (c>=1)
  {
    d=b/c; 
    if (typ==1 && a==0 && d==0) 
    {mmi_str[index]=0x20;index++;goto M;}
    if (d < 10)
    { mmi_str[index]=hex_to_ascii[d & Key_mask];index++;} else
    {
      e=d/10; mmi_str[index]=hex_to_ascii[e & Key_mask];index++;
      e=d-e*10; mmi_str[index]=hex_to_ascii[e & Key_mask];index++;
    } 
M:  b=b-d*c;c=c/10;a++;
  }
}
/************** ¯à¥®¡à §®¢ ­¨¥ æ¥«®£® ¢ áâ®àªã ******************/
unsigned char IntegerToString (unsigned long val)
{
  unsigned long d;unsigned char buf[10],i,j;i=0;
  while (val > 0)
  {
    d=val/10;buf[i]=hex_to_ascii[(val-d*10) & Key_mask];
    i++;val=d;
  } for (j=0;j<i;j++) mmi_str[j]=buf[i-j-1];return i;
}
/*********** ®â®¡à ¦¥­¨¥ ¢¢¥¤ñ­­®£® §­ ª  *******************/
void EnterKey (unsigned char code_symbol,unsigned char *index)
{ /*¨á¯®«ì§ã¥âáï ¯à¨ ¢¢®¤¥ ¯ à®«ï ¨«¨ ª®­ä¨£.§­ ç¥­¨ï*/
   if (*index < 8)
   {
     mmi_str[*index]=code_symbol;count_smb=8;
     mmi_str[*index+1]=Key_cursor;*index=*index+1;Display.evt=2;
   }
}
/*********** ã¤ «¥­¨¥ ¢¢¥¤ñ­­®£® §­ ª  ***********************/
void DeleteKey (unsigned char *index)
{ /*¨á¯®«ì§ã¥âáï ¯à¨ ¢¢®¤¥ ¯ à®«ï ¨«¨ ª®­ä¨£.§­ ç¥­¨ï*/
   if (index > 0)
   {
     mmi_str[*index]=Key_blank;*index=*index-1;
     mmi_str[*index]=Key_cursor;count_smb=8;Display.evt=2;
   }
}
/** ¢¢®¤ æ¨äà®¢®£® §­ ç¥­¨ï ¤«ï:¯ à®«ï,¨§¬¥­.ª®­ä¨£, àå¨¢®¢ **/
unsigned char EnterFigure (unsigned char buf_mmi[],unsigned char count)
{ /*ª®¤ë ª« ¢¨è ®â "0" ¤® "9",¯¥à¥¢®¤ ¢ á¨¬¢®« ¨ æ¨äàã*/
  const unsigned char dec_key[10]={Key_3,Key_C,Key_D,Key_F,Key_E,
				   Key_8,Key_9,Key_B,Key_A,Key_1};
  unsigned char i,flag;/*num_key=16;*/flag=0;
  if (enter_ind < 9) for (i=0;i<10;i++)
  {
    if (KeyFound (buf_mmi,Key_0,dec_key[i],count)==1)
    { EnterKey(Key_0+i,&enter_ind);flag=1;break; }
  } return flag;
}
/********* ¢®§¢à â ¢¢¥¤ñ­­®© æ¨äàë  ******************************/
unsigned char ConvertToDec (unsigned char symbol)
{/*ª®¤"10"¬¨­ãá,ª®¤"11"§ ¯ïâ ï,¯¥à¥¢®¤ ¤¥áïâ¨ç­®£® á¨¬¢®«  ¢ æ¨äàã*/
  unsigned char dec;
  if ((symbol>47)&&(symbol<58)) dec=symbol-48;
  if (symbol==Key_minus) dec=10;if (symbol==Key_dot) dec=11;
  return dec;
}
/******* ¯®ª §ë¢ ¥â ¯®§¨æ¨î ¤«ï ¢¢®¤  á¨¬¢®«  ******************/
void ViewCursor (unsigned char index)
{
   if (index==0)
   { mmi_str[0]=Key_cursor;count_smb=8;Display.evt=2;}
}
/********* ¯®«ãç¥­¨¥ ­®¢ëå ­ áâà®¥ª  àå¨¢  ¯à¨ çâ¥­¨¨ *************/
void GetArcReadPoint(int *pointer,unsigned *segment,unsigned char *page)
{
  switch (*page)
  {
    case 0:*page=2;*segment=0xc000;
	   *pointer=ReadNVRAM(17)*256+ReadNVRAM(18);break;
    case 1:*page=0;*segment=0xd000;
	   *pointer=ReadNVRAM(13)*256+ReadNVRAM(14);break;
    case 2:*page=1;*segment=0xe000;
	   *pointer=ReadNVRAM(15)*256+ReadNVRAM(16);break;
  }
}
/**********************************/
void MoveCursorMMI (unsigned char buf_mmi[],unsigned char broad,
                                             unsigned char count)
{
  M1:if (Cursor.enb==1)
    {
      if (Cursor.mode==1) 
      {
	Horizont=0; Vertical=Cursor.row+1; count_smb=1; ClearBuffer();
        Cursor.enb=0; mmi_str[0]=0x3e; Display.evt=2; goto M2;
      } else
      {
	Vertical=Cursor.old+1; count_smb=1; ClearBuffer(); Display.evt=2;
        Cursor.mode=1; Horizont=0; goto M2;
      }
    } else if (KeyFound(buf_mmi,Key_0,Key_3,count)==1 && Cursor.row<(broad-1))
    {
      Cursor.old=Cursor.row; Cursor.row=Cursor.row+1; Cursor.enb=1;
      Cursor.mode=0; goto M1;
    } else if (KeyFound(buf_mmi,Key_0,Key_F,count)==1 && Cursor.row>0)
    {
      Cursor.old=Cursor.row; Cursor.row=Cursor.row-1; Cursor.enb=1;
      Cursor.mode=0; goto M1;
    }
  M2:
}
/******************************/
void ReturnToMenuMMI (void)
{
  unsigned char num_page;
  Cursor.enb=1; Cursor.row=0; Cursor.mode=1; Display.flag=1;
  Display.row=0; Cursor.size=0; Display.suspend=1; 
  if (Display.ind_ret>0) 
  {
    num_page=Display.ret[Display.ind_ret-1]; Display.ind_ret--;
  } else num_page=10; SetDisplayPage(num_page);
}
/*********** ¨§¬¥­¥­¨¥ ª®­ä¨£ãà æ¨¨ ¨ § ¯¨áì á®¡ëâ¨ï ***************/
unsigned char ConfigParamChange (unsigned char value[],unsigned char size,
				 unsigned char addr)
{
  unsigned char buf_evt[16],j,flag;flag=0;FormateEvent(buf_evt);
  for (j=0;j< size;j++)
  {
    if (value[j] != mmi_val[j])
    {
      EnableEEP();WriteEEP(Display.point,addr+j,value[j]);ProtectEEP();
      flag=1;
    } buf_evt[6+j]=mmi_val[j];buf_evt[10+j]=value[j];
  }
  if (flag == 1) /*§ ¯¨áì á®¡ëâ¨ï ®â â¥à¬¨­ « */
  {
    buf_evt[15]=Display.point+1+128;buf_evt[14]=Display.prm;WriteEvent(buf_evt,0);
    return Display.point+1;
  } else return 0;
}
/******************************/
unsigned char  MoveListMMI (unsigned char buf_mmi[],unsigned char count,
                  unsigned char size_max)
{
  unsigned char flag;
  if (KeyFound(buf_mmi,Key_0,Key_5,count)==1 && Display.num>=6)
  {
    Display.num=Display.num-6;Horizont=0;Display.row=0;Display.flag=1;flag=1;
    Cursor.size=0;Display.suspend=1;
  } else
  if (KeyFound(buf_mmi,Key_0,Key_7,count)==1 && Display.num<(size_max-6))
  {
    Display.num=Display.num+6;Horizont=0;Display.row=0;Display.flag=1;flag=1;
    Cursor.size=0;Display.suspend=1;
  } else flag=0; return flag;
}
/******************************/
void WriteMenuToMMI (unsigned char menu[], unsigned char size_menu)
{
  unsigned char i,j,flag;
  ClearBuffer(); Vertical=Display.row+1;
  if ((Display.num+Display.row)<size_menu)
  {
    j=strlen(menu); for (i=0;i<j;i++) mmi_str[i]=menu[i];
    Cursor.size++;
  } count_smb=28;Horizont=2;Display.evt=2;Display.row++;
  if (Display.row > 5)
  {
    Display.row=0; Display.flag=0; Cursor.mode=0; Cursor.old=Cursor.row;
    Cursor.row=0; Cursor.enb=1;Display.suspend=0;
  }
}
/******* ®¡à ¡®âª  ®â¢¥â  ®â MMI(â¥à¬¨­ « ®¯¥à â®à ) *****/
void ReadFromMMI (unsigned char buf_mmi[],unsigned char count,
		  double dyn_prm)
{
  /*[]-[]-[]-*/
  unsigned char i,j,k,cr[4],buf_evt[16],flg;float value;int pnt_evt;
  switch (Display.page)
  {
    case 0: case 1: case 2: case 3: case 4: case 5:
    case 6: case 7: case 8: case 9:/*§ £®«®¢®ª*/
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*"D"*/
      GoToMenuMMI(10); else
      { /* ¢¨§ã «¨§ æ¨ï ª®­âà®«ì­®© áã¬¬ë */
	ClearBuffer(); Display.suspend=0; k=0;
        for (i=0;i<3;i++) /*¢ë¢®¤¨â ¤ âã*/
        { 
          ByteToString(ReadNVRAM(2-i),k,0);if (i != 2) mmi_str[k+2]=Key_dot;k=k+3;
	} k=9;count_smb=18;
	for (i=0;i<3;i++) /*¢ë¢®¤¨â ¢à¥¬ï*/
	{ 
          ByteToString(ReadNVRAM(3+i),k,0);if (i != 2) mmi_str[k+2]=0x3a;k=k+3;
	} Horizont=5;Vertical=4;Display.evt=2;
      } break;
    case 10:/*®á­®¢­®¥ ¬¥­î*/
       if (Display.flag==1)
       WriteMenuToMMI(str_menu[Display.num+Display.row],11); else
       MoveCursorMMI(buf_mmi,Cursor.size,count);
       MoveListMMI (buf_mmi,count,10);
       if (KeyFound(buf_mmi,Key_0,Key_6,count)==1) 
       { Display.flag=0;ReturnToMenuMMI();} else
       if (KeyFound(buf_mmi,Key_0,Key_2,count)==1) 
       switch (Cursor.row+Display.num)
       { 
	 case 0: Display.point=7; Display.write=0; GoToMenuMMI(20);break;
	 case 1: GoToMenuMMI(11); break;
	 case 2: GoToMenuMMI(12); break;
	 case 3: Display.point=1; GoToMenuMMI(13); break;
	 case 4: Display.point=0; GoToMenuMMI(13); break;
	 case 5: Display.point=6; Display.write=0; GoToMenuMMI(20);break;
	 case 6: Display.prm=5; enter_ind=2;GoToMenuMMI(23); break;
	 case 7: Display.prm=7; enter_ind=4;GoToMenuMMI(23); break;
	 case 8: Display.point=11; Display.row=Horizont=mmi_pass=0;
		 Display.flag=1;Display.num=0;SetDisplayPage(14);break;
	 case 9: flg_modem=2; ClearBuffer();Horizont=10;Vertical=3;
		 SetDisplayPage(17); break;
	 case 10:Display.point=60; Display.write=0;GoToMenuMMI(20);break;
       }
	break;
    case 11:/*¬¥­î ¢ë¡®à  â®çª¨ ¤«ï ¯à®á¬®âà */
      if (Display.flag==1) WriteMenuToMMI(str_menu1[Display.num+Display.row],Max_pnt); else
      MoveCursorMMI(buf_mmi,Cursor.size,count);
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) ReturnToMenuMMI(); else
      if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
      {
	Display.point=Cursor.row; Horizont=0; Display.row=0; Display.num=0; Display.flag=1;
	mmi_pass=0; Display.suspend=1;SaveOldPageMMI(); SetDisplayPage(14);
      } break;
    case 12:/*¬¥­î ¢ë¡®à  â®çª¨ ¤«ï ª®­ä¨£ãà æ¨¨*/
      if (Display.flag==1) WriteMenuToMMI(str_menu1[Display.num+Display.row],Max_pnt); else
      MoveCursorMMI(buf_mmi,Cursor.size,count);
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) ReturnToMenuMMI(); else
      if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
      { Display.point=Cursor.row; Display.write=0; GoToMenuMMI(20);} break;
    case 14:/*¯à®á¬®âà ¤® 6 ¯ à ¬¥âà®¢*/
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
	{Display.num=0;ReturnToMenuMMI();}else/*"D"¯¥à¥å®¤ ¢ ¬¥­î ¢ë¡®à  â®çª¨ ¤«ï ¯à®á¬®âà */
	if (MoveListMMI (buf_mmi,count,size_max)==1) mmi_pass=0;else
        {
	  ClearBuffer();Vertical=Display.row+1;
	  if (mmi_pass==0) /*á¬¥­  á¯¨áª */
	  {  /*¢ë¢®¤ ¨¬¥­¨ ¯ à ¬¥âà  §  ®¤¨­ ¯à®å®¤*/
	    if ((Display.num+Display.row)<size_max && coord[0]<Max_dynam_all)
	    {
	      j=strlen(dyn_all[coord[0]]);
	      for (i=0;i<j;i++) mmi_str[i]=dyn_all[coord[0]][i];
	      if (coord[2]==2 && coord[1]<Max_mmi_exp && coord[1]>0)
	      {
	        k=strlen(name_mmi_exp[coord[1]]);
		for (i=j;i<j+k;i++)
		mmi_str[i]=name_mmi_exp[coord[1]][i-j];
		mmi_size=j+k;
	      } else mmi_size=j; j=strlen(units_all[coord[3]]);
	      for (i=mmi_size;i<mmi_size+j;i++)
	      if (coord[3] < Max_units_all)
	      mmi_str[i]=units_all[coord[3]][i-mmi_size];
              if (coord[4]==1) ByteToString(coord[5],mmi_size,1);
	    } count_smb=22;Horizont=0;mmi_pass=1;Display.evt=2;
	  } else
	  { /*¢ë¢®¤ §­ ç¥­¨ï ¯ à ¬¥âà */
	      if((Display.num+Display.row)<size_max)
		FloatToString(dyn_prm,mmi_str,0);
	      count_smb=8;Horizont=22;Display.row++;
              if (Display.row > 5) {Display.row=Display.flag=0;Display.suspend=0;}	
              if (Display.flag==1) mmi_pass=0;Display.evt=2;
	  }
	} break;
    case 15:/*¢¢®¤ §­ ç¥­¨ï*/
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*®â¬¥­  ¨§¬¥­ ª®­ä¨£*/
	{
	  mmi_pass=Display.write=enter_ind=0;Horizont=0;Display.flag=1;
	  Vertical=2;SetDisplayPage(16);
	} else
	if (KeyFound (buf_mmi,Key_1,Key_E,count)==1) DeleteKey(&enter_ind);else
	if (EnterFigure(buf_mmi,count) != 1)
	{
	  if (KeyFound (buf_mmi,Key_1,Key_B,count)==1) /*§ ¯ïâ ï*/
	      EnterKey(Key_dot,&enter_ind);else
	  if (KeyFound (buf_mmi,Key_0,Key_2,count)==1 && enter_ind>0)
	  { /*¢¢®¤ ­®¢®£® ª®­ä¨£ãà æ¨®­­®£® §­ ç¥­¨ï*/
	    value=atof(mmi_str);
	    if (coord[3] == 1 || coord[3] == 2)
	    { /*¤«ï ¡ ©â®¢ëå §­ ç¥­¨© à §¤¥«¨â¥«ì ®âáãâáâ¢ã¥â*/
	      cr[0]=value;flg_init=ConfigParamChange(cr,1,coord[2]);
	    }
	    if (coord[3] == 4)
	    { /*¤«ï ¤¥©áâ¢¨â¥«ì­ëå §­ ç¥­¨©*/
	      ConvToBynare(value,cr);
	      flg_init=ConfigParamChange(cr,4,coord[2]);
	    }
	    if (coord[3] == 60 && coord[2]<5)
	    {
	      cr[0]=value; WriteNVRAM(coord[2],cr[0]);
	      if (coord[2] == 4) WriteNVRAM(5,0);
	      if (coord[2] >= 3)
		SetTime(ReadNVRAM(3),ReadNVRAM(4),ReadNVRAM(5));
	      if (coord[2] < 3)
		SetDate(ReadNVRAM(0)+2000,ReadNVRAM(1),ReadNVRAM(2));
	    } mmi_pass=Display.write=enter_ind=0;Horizont=0;Display.flag=1;
	      Vertical=2;SetDisplayPage(16);/*¢¨§ã «¨§ æ¨ï ¨§¬¥­¥­¨ï*/
	  } else ViewCursor(enter_ind);
	} break;
    case 16:/*¨§¬¥­¥­¨¥ ª®­ä¨£ãà æ¨¨*/
	if (Display.flag==1)
	{ ClearBuffer();
	  if (mmi_pass==0)
	  {
	    j=strlen(conf_all[coord[0]]);
	    for (i=0;i<j;i++)
	    mmi_str[i]=conf_all[coord[0]][i];k=strlen(units_all[coord[5]]);
	    if (coord[5]>0)
	    for (i=j;i<j+k;i++)
	    mmi_str[i]=units_all[coord[5]][i-j];else
	    if (coord[4]<=40) ByteToString(coord[4]+1,j,1);
	    count_smb=28;mmi_pass=1;
	  } else
	  {
	    if (coord[3]==4)
	    {
	      ConvToFloatVerify(&value,ReadEEP(Display.point,coord[2]),
		ReadEEP(Display.point,coord[2]+1),ReadEEP(Display.point,coord[2]+2),
		ReadEEP(Display.point,coord[2]+3));
	      FloatToString(value,mmi_str,0);
	    } else if (coord[3]==1 || coord[3]==3)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      ByteToString(mmi_val[0],0,1);	      
	    } else if (coord[3]==2)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      j=strlen(name_sel_all[mmi_sel[mmi_val[0]]]);
	      if (mmi_val[0]<30 && mmi_sel[mmi_val[0]]<Max_sel_all)
	      for (i=0;i<j;i++)
	      mmi_str[i]=name_sel_all[mmi_sel[mmi_val[0]]][i];
	    } else if (coord[3]==6)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      i=IntegerToString(set_bd[mmi_val[0] & 15]);
	      mmi_str[i]=mmi_str[i+2]=Key_comma;
	      mmi_str[i+1]=hex_to_ascii[set_dt[(mmi_val[0] &16)>>4] & Key_mask];
	      switch ((mmi_val[0] &192)>>6)
	      {
		case 0:mmi_str[i+3]=Key_N;break;case 1:mmi_str[i+3]=Key_O;break;
		case 2:mmi_str[i+3]=Key_E;break;
	      }
	    } else if (coord[3]==0 || coord[3]==10)
	    {
	      for (i=0;i<8;i++) mmi_str[i]=ReadEEP(Display.point,coord[2]+i);
	    } else if (coord[3]==5 || coord[3]==9)
	    {
	      for (i=0;i<10;i++) mmi_str[i]=psw[i];
	    } else if (coord[3] == 8)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      if (mmi_val[0] < Max_name_pnt) for (i=0;i<6;i++)
	      mmi_str[i]=name_arch[mmi_val[0]][i];
	      if (mmi_val[0] != 0)
	      {
		if (mmi_val[0] == 1)
		{
		  mmi_val[1]=ReadEEP(Display.point,coord[2]+1)+1;
		  mmi_str[6]=hex_to_ascii[mmi_val[1] & Key_mask];
		}
		mmi_str[7]=Key_comma;
		j=strlen(dyn_all[coord[7]]);
		if (coord[7]> 0 && coord[7]<Max_dynam_all)
		for (i=0;i<j;i++)
		mmi_str[8+i]=dyn_all[coord[7]][i];
		mmi_val[3]=ReadEEP(Display.point,coord[2]+3);
		if (mmi_val[3]>3 && mmi_val[3]<Max_mmi_exp)
		for (i=0;i<6;i++)
		mmi_str[8+j+i]=name_mmi_exp[mmi_val[3]][i];
	      } 
	    } if (coord[3] == 12)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      k=strlen(units_all[mmi_val[0]]);
	      if (mmi_val[0]<Max_units_all) for (i=0;i<k;i++)
	      mmi_str[i]=units_all[mmi_val[0]][i];
	    } if (coord[3] == 60)
	    { mmi_val[0]=ReadNVRAM(coord[2]);ByteToString(mmi_val[0],0,1);}
	    Horizont=2;Vertical=4;count_smb=29;Display.flag=0;
	  }   Display.evt=2;
	} else
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*"ESC"¯¥à¥å®¤ ¢ ¬¥­î */
	{ Display.num=Display.old; ReturnToMenuMMI();} else
	if (KeyFound (buf_mmi,Key_0,Key_4,count)==1)
	{
	  if (coord[6] !=2) /*"F1"¢¢®¤ ¯ à®«ï ¤«ï ¨§¬¥­¥­¨ï*/
	  {
	    ClearBuffer();Horizont=10;Vertical=3;
	    if (coord[6]==1) SetDisplayPage(17);else
	    {Display.write=1;enter_ind=0;SetDisplayPage(15);}
	  } else  SetDisplayPage(22);
	} 
	break;
    case 17:/*¢¢®¤ ¯ à®«ï*/
       if (KeyFound(buf_mmi,Key_0,Key_6,count)==1) /*®âª § ®â ¨§¬¥­¥­¨ï*/
       {
	 if (flg_modem==0)
	 {
	   mmi_pass=0;Horizont=0;Display.flag=1;Display.write=0;enter_ind=0;
	   Vertical=2; flg_modem=0; SetDisplayPage(16);
	 } else
	 {
	   flg_modem=0; Cursor.enb=1; Cursor.row=0;
	   Cursor.mode=1; Display.flag=1;Display.row=0; SetDisplayPage(10);
	 }
       } else
       {
	 if (KeyFound(buf_mmi,Key_1,Key_E,count)==1) DeleteKey(&enter_ind);else/*ã¤ «¥­¨¥ ¯®á«¥¤­¥£®*/
	 if (EnterFigure(buf_mmi,count)!=1);/*¢¢®¤ §­ ç¥­¨© ®â "0"¤®"9"*/
	 {
	   if (KeyFound(buf_mmi,Key_0,Key_2,count)==1 && enter_ind>0)
	   { /*¢¢®¤ ¯ à®«ï ­  ¨§¬¥­¥­¨¥ ª®­ä¨£ãà æ¨¨*/
	     /*value=ConvertToNumber(enter_ind); /*¢ëç¨á«¥­¨¥ íâ «®­­®£® ¯ à®«ï*/
	     value=atof(mmi_str);
	     if (value != dyn_prm) SetDisplayPage(18);else
	     { /*¯ à®«ì ¢¢¥¤ñ­ ¯à ¢¨«ì­®*/
	       ClearBuffer();if (coord[3]==2)
	       {
		 Horizont=Display.row=Display.num=0; Display.flag=1;
		 SetDisplayPage(21);
	       } else if (flg_modem==2)
	       {
		 flg_modem=1; Cursor.enb=1; Cursor.row=0; enter_ind=0;
		 Cursor.mode=1; Display.flag=1;Display.row=0; SetDisplayPage(10);
	       } else
	       {
		 SetDisplayPage(15);Display.write=1;enter_ind=0;Horizont=10;
	       }
	     }
	 } else ViewCursor(enter_ind);
       }
      } break;
    case 18: case 22:/*­¥¢¥à­ë© ¯ à®«ì ¨«¨ § ¯à¥â*/
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*"ESC"*/
      {
	mmi_pass=0;Horizont=0;Display.flag=1;Display.write=0;enter_ind=0;
	Vertical=2;SetDisplayPage(16);
      } break;
    case 20:/*¯®¤¬¥­î*/
      if (MoveListMMI (buf_mmi,count,Display.size)==0)
      { 
        if (Display.flag==1) 
        {
          ClearBuffer();Vertical=Display.row+1;
          if ((Display.num+Display.row)<Display.size) 
	  {
	    j=strlen(conf_all[coord[0]]);
	    for (i=0;i<j;i++) mmi_str[i]=conf_all[coord[0]][i];
	    if (coord[1]<=40) ByteToString(coord[1]+1,j,1);
            Cursor.size++;
          } count_smb=27;Horizont=2;Display.evt=2;Display.row++;
          if (Display.row > 5)
          {
            Display.row=0;Display.flag=0;Cursor.mode=0;Cursor.old=Cursor.row;
	    Cursor.row=0;Cursor.enb=1;Display.suspend=0;
	  }
	} else MoveCursorMMI(buf_mmi,Cursor.size,count);
        if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
        { Display.num=0; ReturnToMenuMMI();} else
        if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
	{
	  Display.prm=Display.num+Cursor.row;mmi_pass=0;Display.flag=1;
	  Display.write=0;Horizont=0;enter_ind=0;Vertical=2; SaveOldPageMMI();
	  Display.old=Display.num; SetDisplayPage(16);
        }
      } break;
    case 21:/*¯à®á¬®âà ¤® 6 ¯ã­ªâ®¢ ¢ë¡®à  §­ ç¥­¨ï*/
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
      {
	mmi_pass=Display.write=enter_ind=Horizont=0;
	Display.num=Display.old;
	Display.flag=1; Vertical=2; SetDisplayPage(16);
      } else/*"ESC"®â¬¥­  ¨§¬¥­¥­¨ï ¯ à ¬¥âà */
      {
	MoveListMMI (buf_mmi,count,mmi_num_sel);
	ClearBuffer(); Vertical=Display.row+1;
	if (Display.flag==1) /*á¬¥­  á¯¨áª */
	{ /*¢ë¢®¤ ¯ã­ªâ  ¬¥­î ¢ë¡®à §­ ç¥­¨ï §  ®¤¨­ ¯à®å®¤*/
	  if ((Display.num+Display.row)<mmi_num_sel)
	  {
	    j=strlen(name_sel_all[mmi_sel[Display.num+Display.row]]);
	    for (i=0;i<j;i++)
	    mmi_str[i+3]=name_sel_all[mmi_sel[Display.num+Display.row]][i];
	    Cursor.size++;
	  } count_smb=30; Horizont=0; Display.evt=2; Display.row++;
	  if (Display.row > 5)
	  {
	    Display.row=Display.flag=0;Cursor.mode=0;Cursor.old=Cursor.row;
	    Cursor.row=0; Cursor.enb=1; Display.suspend=0;
	  }
	} else MoveCursorMMI(buf_mmi,Cursor.size,count);
	if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
	{
	  cr[0]=Display.num+Cursor.row;mmi_pass=0;Horizont=0;Display.flag=1;
	  flg_init=ConfigParamChange(cr,1,coord[2]); enter_ind=0;
	  Vertical=2; SetDisplayPage(16);
	}
      } break;
    case 13:/*¯à®á¬®âà ¤® 6 ¯ã­ªâ®¢ ¬¥­î  àå â®ç¥ª*/
      if (MoveListMMI (buf_mmi,count,size_max)==0)
      {
	if (Display.flag==1)
	{
	  ClearBuffer();Vertical=Display.row+1;
          if ((Display.num+Display.row)<size_max)
	  { 
            if (coord[0]<Max_conf_all) for (i=0;i<5;i++)
	      mmi_str[i+2]=conf_all[coord[0]][i];
	      ByteToString(coord[1],8,0);
	      if (coord[2]<3) for (i=0;i<6;i++)
	      mmi_str[i+10]=name_arch[coord[2]][i];
	      if (coord[2]==1) mmi_str[16]=hex_to_ascii[coord[3]+1];
	      if (coord[2]>0)
	      {
		j=strlen(dyn_all[coord[4]]);
		if (coord[4]<Max_dynam_all) for (i=0;i<j;i++)
		mmi_str[i+17]=dyn_all[coord[4]][i];
		mmi_val[Display.row]=coord[6];k=strlen(name_mmi_exp[coord[5]]);
		if (coord[5]<Max_mmi_exp) if (coord[5]==4 || coord[5]==6)
		for (i=j;i<k+j;i++) if ((i+17)<30)
		mmi_str[i+17]=name_mmi_exp[coord[5]][i-j];
	      } else mmi_val[Display.row]=128; Cursor.size++;
	   } count_smb=30;Horizont=0;Display.evt=2;Display.row++;
	  if (Display.row > 5)
	  {
	    Display.row=Display.flag=0;Cursor.mode=0;Cursor.old=Cursor.row;
	    Cursor.row=0;Cursor.enb=1;Display.suspend=0;
	  }
	} else MoveCursorMMI(buf_mmi,Cursor.size,count);
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
	{ Display.num=0; ReturnToMenuMMI();} else
	if (KeyFound (buf_mmi,Key_0,Key_2,count)==1 && mmi_val[Cursor.row]!=128)
	{
	  mmi_arc_page=GetArcPoint(&mmi_arc,&mmi_seg); Display.flag=1;
	  mmi_size=0;Display.prm=Display.num+Cursor.row;SetDisplayPage(19);
	}
      } break;
    case 19:
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
      {Display.flag=1;Display.row=0;Display.suspend=1;SetDisplayPage(13);} else
      { /*"C"«¨áâ âì  àå¨¢ ¢­¨§*/
	if (KeyFound (buf_mmi,Key_0,Key_7,count)==1 && mmi_size<2)
	{Display.row=0;Display.flag=1;} else
	{
	  if (mmi_arc<=0 && mmi_size<2) /*­ ç «® á«¥¤ãîé¥£® ¯à®å®¤ */
	  {mmi_size++;GetArcReadPoint(&mmi_arc,&mmi_seg,&mmi_arc_page);} else
	  M:if (Display.flag == 1)
	  {
	    ClearBuffer();Vertical=Display.row+1;
	    if (mmi_arc > 0)
	    {
	      mmi_arc--;mmi_adr=mmi_arc*Size_str;
	      if (FlashRead(mmi_seg,mmi_adr)==Display.point)
	      {
		k=0;for (i=0;i<3;i++)
		{ /*¯à®ç¨â âì ¨ ¯®ª § âì ¤ âã  àå¨¢ */
		  j=FlashRead(mmi_seg,mmi_adr+3-i);ByteToString(j,k,0);
		  if (i!=2) mmi_str[k+2]=Key_dot;k=k+3;
		} k=9;for (i=0;i<2;i++)
		{ /*¯à®ç¨â âì ¨ ¯®ª § âì ¢à¥¬ï  àå¨¢ */
		  j=FlashRead(mmi_seg,mmi_adr+4+i);ByteToString(j,k,0);
		  if (i==0) mmi_str[k+2]=0x3a;k=k+3;
		} k=15;j=7+(Display.prm)*4;
		ConvToFloatVerify(&value,FlashRead(mmi_seg,mmi_adr+j),
		FlashRead(mmi_seg,mmi_adr+j+1),FlashRead(mmi_seg,mmi_adr+j+2),
		FlashRead(mmi_seg,mmi_adr+j+3));
		FloatToString(value,mmi_str,k);
	      } else goto M;
	    } count_smb=24;Display.row++;Display.evt=2;
	    if (Display.row > 5) Display.flag=0;Horizont=0;
	  }
	}
      } break;
    case 23: /*¬¥­î ¢ë¡®à  ¤ âç¨ª */
     if (Display.flag==1) WriteMenuToMMI(str_menu2[Display.num+Display.row],enter_ind); else
      MoveCursorMMI(buf_mmi,Cursor.size,count);
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) ReturnToMenuMMI(); else
      if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
      {
	Display.point=Cursor.row+Display.prm; Horizont=0; Display.row=0; Display.num=0; Display.flag=1;
	mmi_pass=0; SaveOldPageMMI(); SetDisplayPage(14);
      } break;
    }
}