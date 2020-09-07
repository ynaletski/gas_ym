/***** ����� ��室� ���� �����/����, ��⮤ GERG-91,NX-19 ******/
/*10-06-09 ������� ��࠭�祭�� �� �᫮ ��������>1000 ��� �����*/
/*26-06-09 ����� ���ᨢ �����ᮢ ��� ���ମ� ind_prm_alm[8]    */
#include<math.h>


#define Max_dyn_all        43   /**/
#define Max_save          128   /**/
#define Max_conf           43   /*�᫮ ���䨣.��ࠬ��஢ �����*/
#define Max_select        160
#define Max_dyn            18
#define Max_dyn_massive    24
#define Max_main           69   /*�᫮ ���䨣.��ࠬ��஢ �⠭樨*/
#define Max_select_main    64
#define Max_archive         7   /*�᫮ ��娢.��ࠬ��஢ �����*/
#define Max_arch_pnt       40   /*�᫮ ��娢.�祪 �⠭樨*/
#define Max_arch_record   167  /*���� ����� ��娢 ����� � �����*/
#define Max_config_float   29  /*�᫮ ����⢨⥫��� ���䨣.��ࠬ��஢*/
#define Max_icp_prm        74  /*�᫮ ��ࠬ��஢ ����஥� ���㫥�*/
#define Max_exp_prm        60
#define Max_exp_dyn        40
#define Max_exp_const      20

#define Max_error         50  /*�᫮ ⨯�� �訡��*/
#define Max_mvs           4   /*�᫮ �������ࠬ����᪨� ���稪��*/
#define Max_icp           4   /*�᫮ ���㫥� �/�*/
#define Typ_task          2   /*���� ���� ���� ���� �� ����ࠣ��*/
#define Max_icp_ain       2   /*�᫮ ���㫥� ������.�����*/
#define Max_icp_aout      2   /*�᫮ ���㫥� ������.�뢮��*/
#define Max_icp_dio       2   /*�᫮ ���㫥� ����� �����/�뢮��*/
struct dynparams
{
  float dyn[Max_dyn_all];
  unsigned int cnt[4];
};
struct expandparams
{
  float        dyn[256];
  unsigned int cnt[4];
};
struct modbus_config
{
  unsigned char mode;             /*����������� � heat.c*/
  unsigned char protocol;
  unsigned char connect;
  unsigned char delay;
};
struct script
{
  double         accum;
  double	 argum;
  unsigned      count;
  unsigned char buf[6];
  unsigned       wait;
  unsigned char flag;
  unsigned     delay;
};
struct runtime
{
  unsigned char nmb;          /*���浪��� ����� ����� ��� ���稪�*/
  unsigned char nmb_icp;      /*���浪��� ����� �����*/
  unsigned char ind;          /*��� ����樨 ����� ��� ���稪�*/
  unsigned char pnl;          /*���浪��� ����� ��ப� �� ⠡��*/
  unsigned char cnt_avg;      /*����稪 ��।����� �� ���稪��*/
  unsigned char flg_err;      /*䫠��� ���㠫���樨 �訡��*/
  unsigned char old_sec;
  unsigned char old_min;
  unsigned char old_hour;
  unsigned char old_month;
  unsigned char mmi;
};
struct modbus_host
{
  unsigned char num_pool;          /*���浪��� ����� �����*/
  unsigned char stat_pool;         /*����� �믮������ �����*/
  unsigned char adr;               /*���� ���譥�� ���ன�⢠*/
  unsigned char func;              /*�㭪��*/
  unsigned char count;             /*�᫮ ॣ���஢ � �����*/
  unsigned char status;            /*����� ����祭,��� �訡��*/
  unsigned      readr;             /*��ॠ�����*/
  unsigned char flag;            /*�ਧ��� �ਮ�⠭���� ����ᮢ*/
  unsigned      wait;            /*����稪 50 �� ���ࢠ���*/
};
struct modul_dio
{
  unsigned char inp;
  unsigned char out;
  unsigned char stat_out;
  unsigned char status[4];
  unsigned char evt;
};
struct modul_ao
{
  float         prm[4];            /*��ࠬ���� �� 4-� �������*/
  float         lo_brd[4];         /*������ �࠭�� ���������*/
  float         hi_brd[4];         /*���孭�� �࠭�� ���������*/
  unsigned char units[4];
  unsigned char status[6];
  unsigned char evt;
  unsigned char chnl;
};
struct modul_ai
{
  float         prm[8];            /*��ࠬ���� �� 8-�� �������*/
  float         avg[8];            /*��।�����*/
  float         lo_brd[8];         /*������ �࠭�� ���������*/
  float         hi_brd[8];         /*���孭�� �࠭�� ���������*/
  float         alm_set[8][5];    /*��⠢�� ��� �������:��,���,����,��,�����,*/
  unsigned char units[8];
  unsigned char status[4];
  unsigned char evt;
  unsigned char alm_enb;           /*����� ࠧ�襭�/����饭�*/
  unsigned char alm_status[8];        /*䠪� ॣ����樨 ���ଠ */
};
struct counters
{
  unsigned char status[4];
  unsigned char evt;
  unsigned char chan;
  unsigned char start[2];
  float        counter[2];
  float         factor[2];
  float         value[2];
};
struct mvs
{
  float data[21];              /*�������᪨� ��ࠬ���� � ��.�����஢��*/
  float avg[3];                /*��।��� ��.���.��ࠬ��஢*/
  unsigned char setup[13];     /*⥣,����,�����,�������*/
  unsigned char wait;           /*�᫮ �६����� ���ࢠ��� ����*/
  unsigned char evt;            /*ᮡ�⨥*/
  unsigned char alm_enb;      /*����� ࠧ�襭�/����饭�*/
  float alm_set[3][3];         /* ��⠢�� ��� ��९���:���,����,�����*/
  unsigned char alm_status[3];       /* 䠪� ॣ����樨 ���ଠ */
};
struct comport
{
  unsigned char buf[256]; /*����� �����*/
  unsigned char status; /*������ ���������� ��������:
			 0-��������,1-� ������ ���� ������,2-������ ����*/
  unsigned char index;  /*������ ������ �����*/
  unsigned char timer;  /*������� ��������� ����������*/
  unsigned char ta;     /*�������� ����-���� ������� 50 ����*/
  unsigned char reinst;
};
struct modbus_config       Modbus;
const unsigned char size_conf[8]={139,139,139,139,240,0,224,236};
const unsigned char etl[10] = {1,2,4,8,16,32,64,128,256,512};
const unsigned char ind_prm_alm[8]={26,27,29,30,32,33,24,25};
const unsigned char typ_port[4] = {3,2,1,1};
unsigned char ind_accum[4]={1,2,4,6};
/*������ ��� �������, ������ � �� ��� ������� � ��,
  ������ �� �� ��� ������� �� ��*/
const unsigned char sel_units[3][2]={{6,7},{15,16},{12,19}};
unsigned char exp_dyn[Max_exp_dyn][5];
float exp_const[Max_exp_const];
const unsigned char conf_menu[8][6]={
 {1,1,2,3,4,5},/*��騥 ��⠭����*/{1,6,7,8,0,0},/*��ࢠ� �窠*/
 {1,6,7,8,0,0},/*���� �窠*/   {1,6,7,8,0,0},/*����� �窠*/
 {1,6,7,8,0,0},/*������ �窠*/{1,9,10,0,0,0},/*��� �窠*/
 {1,11,0,0,0,0},/*���㫨 �/�*/    {0,0,0,0,0,0}/*१��*/};
/*[0]-��砫�� ����,
/*[1]-ࠧ��� ᬥ饭��,
  [2]-�ਧ��� ��࠭���� � ���:>1- ��,2-����������,3-��।�����*/
const unsigned char main_dyn[Max_dyn][3]={
 {0,4,3},/*��९��*/      {4,4,3},/*�������� ���*/  {8,4,3},/*���������*/
 {12,4,3},/*���⭮���*/   {16,4,3},/*����*/         {20,4,3},/*���.���*/
 {24,8,2},/*���室*/      {32,1,0},/*� ᦨ�������*/{33,1,0},/*� ��⮪�*/
 {34,1,0},/*� ���७��*/{35,1,0},/*� ��������*/  {36,1,0},/*� ��客����*/
 {37,1,0},/*� ��������*/{38,1,0},/*��᫮ ������*/ {39,1,0},/*�離���� ���*/
 {40,1,0},/*�������*/    {41,1,0},/*� ��������*/   {42,1,0} /*����.ࠡ*/
};
/*����.���.��ࠬ����[0]-��砫�� ����,[1]-������ ᬥ饭��,[2]-������ �����
[3]-������ ������,[4]-�ਧ��� �����������,[5]-�ਧ��� ����ન:1-��室��,>1-��室��
[6]-������:64-� ����⢥ �⢥�稪�,128-� ����⢥ �����稪�,192-���+��� ��
  [7]-�ਯ��,[8]-�ਧ��� ���⪨ ��ࠬ���*/
const unsigned char dyn_set[Max_dyn_massive][9]={{0,0,1,2,0,2,66,1,0},
 {4,0,2,2,0,3,194,1,0},{8,0,3,3,0,4,194,1,0},{12,0,4,8,0,0,194,1,0},
 {16,0,12,20,0,0,66,1,0},{20,0,13,20,0,0,66,1,0},{24,0,48,17,2,1,194,1,0},
 {24,1,48,18,2,0,66,0,1},{24,2,48,18,2,0,66,0,1},{24,3,48,18,2,0,66,0,1},
 {24,4,48,18,2,0,66,0,1},{24,5,48,18,2,0,66,0,1},{24,6,48,18,2,0,66,0,1},
 {32,0,20,0,0,1,0,0,0},{33,0,21,0,0,1,0,0,0},{34,0,22,0,0,1,0,0,0},
 {35,0,23,0,0,1,0,0,0},{36,0,24,0,0,1,0,0,0},{37,0,25,0,0,1,0,0,0},
 {38,0,26,0,0,1,0,0,0},{39,0,27,29,0,1,1,0,0},{40,0,28,10,0,1,1,0,0},
 {41,0,30,0,0,1,1,0,0},{42,0,49,8,0,1,1,0,0}};
/*[0]-������ �����,[1]-����� ��ࠬ���,[2]-���� ��砫��
⨯ ������:��ப�-0,����-1,������� �롮�-2,����.�롮�-3,�����.�᫮-4
[3]-⨯ ������,[4]-����� ��� ����⨯���,����-128 [5]-������ ������,
  [6]-��஫� ��� ��������� �㦥�:1,2-��������� �१ MMI ����������*/
unsigned char conf_main[Max_main][7]={
 {36/*���� �⠭樨(0)*/,1,1,1,128,0,1},{37/*����ࠪ� ��(1)*/,1,2,1,128,0,1},
 {38/*��ନ��� ����(2)*/,1,3,2,128,0,1},{39/*���� MVS #1(3)*/,1,4,1,128,0,1},
 {40/*���� MVS #2(4)*/,1,5,1,128,0,1},{41/*���� MVS #3(5)*/,1,6,1,128,0,1},
 {42/*���� MVS #4(6)*/,1,7,1,128,0,1},{45/*���� ICP #1(7)*/,1,8,1,128,0,1},
 {46/*���� ICP #2(8)*/,1,9,1,128,0,1},{47/*���� ICP #3(9)*/,1,10,1,128,0,1},
 {48/*���� ICP #4(10)*/,1,11,1,128,0,1},{43/*��⭥�/������(11)*/,1,12,3,128,0,2},
 {62/*HART(12)*/,1,13,2,128,0,2},{52/*��� ICP #1(13)*/,1,14,2,128,0,1},
 {53/*��� ICP #2(14)*/,1,15,2,128,0,1},{54/*��� ICP #3(15)*/,1,16,2,128,0,1},
 {55/*��� ICP #4(16)*/,1,17,2,128,0,1},{58/*������(17)*/,1,18,7,128,0,2},
 {49/*��஫�(18)*/,4,19,5,128,0,2},{59/*����_1 (19)*/,2,23,6,0,0,2},
 {59/*����_2(20)*/,2,25,6,1,0,2},{59/*����_3 (21)*/,2,27,6,2,0,2},
 {59/*����_4(22)*/,2,29,6,3,0,2},{60/*���_1 (23)*/,4,31,8,0,0,2},
 {60/*���_2(24)*/,4,35,8,1,0,2},{60 /*���_3 (25)*/,4,39,8,2,0,2},
 {60/*���_4(26)*/,4,43,8,3,0,2},{60 /*���_5 (27)*/,4,47,8,4,0,2},
 {60/*���_6(28)*/,4,51,8,5,0,2},{60 /*���_7 (29)*/,4,55,8,6,0,2},
 {60/*���_8 (30)*/,4,59,8,7,0,2},{60 /*���_9 (31)*/,4,63,8,8,0,2},
 {60/*���_10 (32)*/,4,67,8,9,0,2},{60 /*���_11 (33)*/,4,71,8,10,0,2},
 {60/*���_12 (34)*/,4,75,8,11,0,2},{60 /*���_13 (35)*/,4,79,8,12,0,2},
 {60/*���_14 (63)*/,4,83,8,13,0,2},{60 /*���_15 (37)*/,4,87,8,14,0,2},
 {60/*���_16 (38)*/,4,91,8,15,0,2},{60 /*���_17 (39)*/,4,95,8,16,0,2},
 {60/*���_18 (40)*/,4,99,8,17,0,2},{60 /*���_19 (41)*/,4,103,8,18,0,2},
 {60/*���_20 (42)*/,4,107,8,19,0,2},{60 /*���_21 (43)*/,4,111,8,20,0,2},
 {60/*���_22 (44)*/,4,115,8,21,0,2},{60 /*���_23 (45)*/,4,119,8,22,0,2},
 {60/*���_24 (46)*/,4,123,8,23,0,2},{60 /*���_25 (47)*/,4,127,8,24,0,2},
 {60/*���_26 (48)*/,4,131,8,25,0,2},{60 /*���_27 (49)*/,4,135,8,26,0,2},
 {60/*���_28 (50)*/,4,139,8,27,0,2},{60 /*���_29 (51)*/,4,143,8,28,0,2},
 {60/*���_30 (52)*/,4,147,8,29,0,2},{60 /*���_31 (53)*/,4,151,8,30,0,2},
 {60/*���_32 (54)*/,4,155,8,31,0,2},{60 /*���_33 (55)*/,4,159,8,32,0,2},
 {60/*���_34 (56)*/,4,163,8,33,0,2},{60 /*���_35 (57)*/,4,167,8,34,0,2},
 {60/*���_36 (58)*/,4,171,8,35,0,2},{60 /*���_37 (59)*/,4,175,8,36,0,2},
 {60/*���_38 (60)*/,4,179,8,37,0,2},{60 /*���_39 (61)*/,4,183,8,38,0,2},
 {60/*���_40 (62)*/,4,187,8,39,0,2},{35 /*��� (63)*/,10,191,10,128,0,2},
 {50/*�����.�����(64)*/,20,201,0,128,0,2},{51/*�����(65)*/,10,221,10,128,0,2},
 {44/*��஫� �����(66)*/,2,231,9,128,0,1},
 {72/*���ᮡ �����.����(67)*/,1,233,2,128,0,1},
 {74/*��ࠡ�⪠ �ਯ�(68)*/,1,234,2,128,0,1},
};
unsigned char main_select[Max_select_main]={
  10,2,3,0,51,52,  11,2,53,54,  13,7,55,56,57,58,35,36,114,
  14,7,55,56,57,58,35,36,114,  15,7,55,56,57,58,35,36,114,
  16,7,55,56,57,58,35,36,114, 12,2,0,51, 67,2,87,88, 68,2,0,1, 69,2,0,1};
/*[0]-������ �����,[1]-����� ��ࠬ���,[2]-���� ��砫��
⨯ ������:��ப�-0,����-1,������� �롮�-2,����.�롮�-3,�����.�᫮-4
[3]-⨯ ������,[4]-����� ��� ����⨯���,����-128 [5]-������ ������,
  [6]-��஫� ��� ��������� �㦥�:1,2-��������� �१ MMI ����������*/
unsigned char conf_basic[Max_conf][7]={
 {1/*����� �窨(0)*/,1,0,2,128,0,1},{2/*�롮� ᥭ��(1)*/,1,1,2,128,0,1},
 {3/*�롮� ��९(2)*/,1,2,2,128,0,1},{4/*�롮� ����(3)*/,1,3,2,128,0,1},
 {5/*�롮� ⥬�(4)*/,1,4,2,128,0,1},{6/*�롮� �����९(5)*/,1,5,2,128,0,1},
 {61/*�롮� �ମ���(6)*/,1,6,2,128,0,1},{56/*���ਠ� ����(7)*/,1,7,2,128,0,1},
 {57/*���ਠ� ᥭ��(8)*/,1,8,2,128,0,1},{64/*��⮤ �����(9)*/,1,9,2,128,0,1},
 {75/*��ફ �஬��(10)*/,1,10,2,128,0,1},
 {9/*�������� ���(11)*/,4,11,4,128,22,1},
 {11/*������� ����(12)*/,4,15,4,128,1,1},{12/*���� ᥭ��(13)*/,4,19,4,128,1,1},
 {13/*���窠 (14)*/,4,23,4,128,2,1},{16/*������ �஬��(15)*/,4,27,4,128,1,1},
 {17/*���客�����(16)*/,4,31,4,128,1,1},
 {69/*���⭮��� (17)*/,4,35,4,128,8,1},{70/*����  (18)*/,4,39,4,128,20,1},
 {71/*�����.���(19)*/,4,43,4,128,20,1},{18/*��� � ����(20)*/,4,47,4,128,11,1},
 {19/*��� � ���� (21)*/,4,51,4,128,11,1},{20/*��� � ����(22)*/,4,55,4,128,11,1},
 {21/*��� � ᥭ��(23)*/,4,59,4,128,11,1},{22/*��� � ᥭ��(24)*/,4,63,4,128,11,1},
 {23/*��� � ᥭ��(25)*/,4,67,4,128,11,1},
 {63/*���� ���.���(26)*/,1,71,2,128,0,2},{7/*����� ���ମ�(27)*/,1,72,3,128,0,2},
 {14/*������ �࠭��(28)*/,4,73,4,128,2,1},{15/*������ �࠭(29)*/,4,77,4,128,2,1},
 {26/*��� ��� ���(30)*/,4,81,4,128,2,1},
 {27/*���� ��� ��९��(31)*/,4,85,4,128,2,1},{28/*���� ��९��(32)*/,4,89,4,128,2,1},
 {29/*��� ��� ����(33)*/,4,93,4,128,2,1},{30/*���� ��� ����(37)*/,4,97,4,128,2,1},
 {31/*����� ����(35)*/,4,101,4,128,2,1},{32/*��� ��� ⥬�(36)*/,4,105,4,128,3,1},
 {33/*���� ��� ⥬�(37)*/,4,109,4,128,3,1},{34/*����१ ⥬(38)*/,4,113,4,128,3,1},
 {24/*����� ��室(39)*/,4,117,4,128,17,1},{25/*���� ��室 (40)*/,4,121,4,128,17,1},
 {76/*����� ��室 (41)*/,4,125,4,128,17,1},{35/*��� �����(42)*/,10,129,10,128,0,2}
};
unsigned char conf_select[Max_select]={
  13,0,2,0,1, 1,12,2,3,4,5,6,7,8,9,10,11,12,13,
  2,21,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
  3,21,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
  4,21,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
  5,21,0,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
  6,2,59,60, 27,4,45,46,47,48, 26,2,0,1,
  7,11,98,62,63,99,100,66,101,68,102,81,103,
  8,11,72,80,104,81,103,105,106,107,108,109,110, 9,3,84,85,86, 10,2,96,97};
/*[0]-������� ����७��
  [1]-��� ���� ��ࠬ��� � ᯨ᪥ �窨
  [2]-⨯ ��娢�஢����
  [3]-��� ��ࠬ���*/
/*��९��,��������,⥬������,���⭮���,����,㣫.���,��室*/
const unsigned char set_archive[Max_archive][4]={
  {2,0,3,1},{2,4,3,2},{3,8,3,3},{8,12,3,4},{20,16,3,12},
  {20,20,3,13},{18,24,2,48}};
unsigned char conf_icp[Max_icp_prm][7]={
  {65,1,0,12,0,0,2},{65,1,1,12,1,0,2},{65,1,2,12,2,0,2},{65,1,3,12,3,0,2},
  {65,1,4,12,4,0,2},{65,1,5,12,5,0,2},{65,1,6,12,6,0,2},{65,1,7,12,7,0,2},
  {65,1,8,12,8,0,2},{65,1,9,12,9,0,2},{65,1,10,12,10,0,2},
  {65,1,11,12,11,0,2},{65,1,12,12,12,0,2},{65,1,13,12,13,0,2},
  {65,1,14,12,14,0,2},{65,1,15,12,15,0,2},{66,4,16,4,0,0,1},
  {66,4,20,4,1,0,1},{66,4,24,4,2,0,1},{66,4,28,4,3,0,1},{66,4,32,4,4,0,1},
  {66,4,36,4,5,0,1},{66,4,40,4,6,0,1},{66,4,44,4,7,0,1},{66,4,48,4,8,0,1},
  {66,4,52,4,9,0,1},{66,4,56,4,10,0,1},{66,4,60,4,11,0,1},{66,4,64,4,12,0,1},
  {66,4,68,4,13,0,1},{66,4,72,4,14,0,1},{66,4,76,4,15,0,1},{67,4,80,4,0,0,1},
  {67,4,84,4,1,0,1},{67,4,88,4,2,0,1},{67,4,92,4,3,0,1},{67,4,96,4,4,0,1},
  {67,4,100,4,5,0,1},{67,4,104,4,6,0,1},{67,4,108,4,7,0,1},{67,4,112,4,8,0,1},
  {67,4,116,4,9,0,1},{67,4,120,4,10,0,1},{67,4,124,4,11,0,1},
  {67,4,128,4,12,0,1},{67,4,132,4,13,0,1},{67,4,136,4,14,0,1},{67,4,140,4,15,0,1},
  {77,1,144,12,0,0,2},{77,1,145,12,1,0,2},{77,1,146,12,2,0,2},{77,1,147,12,3,0,2},
  {77,1,148,12,4,0,2},{77,1,149,12,5,0,2},{77,1,150,12,6,0,2},{77,1,151,12,7,0,2},
  {78,4,152,4,0,0,1},{78,4,156,4,1,0,1},{78,4,160,4,2,0,1},{78,4,164,4,3,0,1},
  {78,4,168,4,4,0,1},{78,4,172,4,5,0,1},{78,4,176,4,6,0,1},{78,4,180,4,7,0,1},
  {79,4,184,4,0,0,1},{79,4,188,4,1,0,1},{79,4,192,4,2,0,1},{79,4,196,4,3,0,1},
  {79,4,200,4,4,0,1},{79,4,204,4,5,0,1},{79,4,208,4,6,0,1},{79,4,212,4,7,0,1},
  {99,4,216,4,0,0,1},{99,4,220,4,1,0,1},
};
unsigned char conf_exp[Max_exp_prm][5]={
 {68,4,0,14,0},{68,4,4,14,1},{68,4,8,14,2},{68,4,12,14,3},
 {68,4,16,14,4},{68,4,20,14,5},{68,4,24,14,6},{68,4,28,14,7},
 {68,4,32,14,8},{68,4,36,14,9},{68,4,40,14,10},{68,4,44,14,11},
 {68,4,48,14,12},{68,4,52,14,13},{68,4,56,14,14},{68,4,60,14,15},
 {68,4,64,14,16},{68,4,68,14,17},{68,4,72,14,18},{68,4,76,14,19},
 {68,4,80,14,20},{68,4,84,14,21},{68,4,88,14,22},{68,4,92,14,23},
 {68,4,96,14,24},{68,4,100,14,25},{68,4,104,14,26},{68,4,108,14,27},
 {68,4,112,14,28},{68,4,116,14,29},{68,4,120,14,30},{68,4,124,14,31},
 {68,4,128,14,32},{68,4,132,14,33},{68,4,136,14,34},{68,4,140,14,35},
 {68,4,144,14,36},{68,4,148,14,37},{68,4,152,14,38},{68,4,156,14,39},
 {73,4,160,4,0},{73,4,164,4,1},{73,4,168,4,2},{73,4,172,4,3},{73,4,176,4,4},
 {73,4,180,4,5},{73,4,184,4,6},{73,4,188,4,7},{73,4,192,4,8},{73,4,196,4,9},
 {73,4,200,4,10},{73,4,204,4,11},{73,4,208,4,12},{73,4,212,4,13},
 {73,4,216,4,14},{73,4,220,4,15},{73,4,224,4,16},{73,4,228,4,17},
 {73,4,232,4,18},{73,4,236,4,19}};
struct station
{
  unsigned char task;        /*⨯ �蠥��� �����*/
  unsigned char addr;        /*���� ����஫���*/
  unsigned char contrh;       /*����ࠪ�� ��*/
  unsigned char mmi;         /*�ਬ������ �ନ���� ������*/
  unsigned char adr_mvs[4];  /*���� ᥭ�஢*/
  unsigned char mvs_eep[4];  /*���� �祩�� � EEPROM*/
  unsigned char adr_icp[4];  /*���� ���㫥�*/
  unsigned char autogo;      /*��⮯��室 �� ��⭥�/������ �६�*/
  unsigned char hart;
  unsigned char typ_icp[4];              /*⨯ �����*/
  unsigned char modbus;
  unsigned char passw[4];               /*��஫� �� ��������� ���䨣��樨*/
  unsigned char com[4][2];               /*����ன�� ���⮢*/
  unsigned char arch[Max_arch_pnt][4];   /*����ன�� ��娢��� �祪*/
  unsigned char tag[10];
  unsigned char phone[20];
  unsigned char at[10];
  unsigned char set_com;                 /*ࠧ�襭�� �� ���4*/
  unsigned      passw_op;                /*��஫� ������*/
  unsigned char script;
  unsigned char units;
  unsigned char panel;
};
struct configparam
{
  unsigned char status;       /*�窠 ����祭� ��� �몫�祭�*/
  unsigned char sensor;       /*�롮� ᥭ��*/
  unsigned char s_diff;       /*�롮� ���筨�� ��९���*/
  unsigned char s_press;      /*�롮� ���筨�� ��������*/
  unsigned char s_tempr;      /*�롮� ���筨�� ⥬����*/
  unsigned char stack;        /*�롮� ���筨�� ���.��९���*/
  unsigned char enable_alm;   /*����� ���ମ�*/
  unsigned char therm_corr;    /*�롮� �ମ���४樨*/
  unsigned char flow_corr;    /*����祭�� ���४樨 ��室�*/
  unsigned char m_pipe;       /*���ਠ� ����*/
  unsigned char m_sens;
  unsigned char method;
  unsigned char cur_sens;     /*⥪�騩 ��९��稪*/
  unsigned char s_egle;
  float         interv;       /*��������.����*/
  float         pipe_size;    /*������� ����*/
  float         sens_size;    /*������� ᥭ��*/
  float         cut_flow;     /*���窠 ���.��室�*/
  float         hi_stack;     /**/
  float         lo_stack;     /**/
  float         radius;       /*ࠤ��� �஬�� �����*/
  float         rougness;     /*��客����� ����*/
  float         k_pipe[3];      /*�����樥��� �ମ���७��*/
  float         k_sens[3];
  float         borders[4][3];
  unsigned char tag[10];
  unsigned char flag;         /*䫠� ४�����樨*/
  unsigned char status_alm[4];/*⥪�饥 ���ﭨ� ���ମ�*/
};
/******** ��⠭���� ��� ���⪠ ���ମ� ��ࠬ���****************/
unsigned char SetClearAlarmsPrm (float borders[],unsigned char status,
				 float value,unsigned char num_pnt,
				 unsigned char num_prm)
{ /*�����: 0-��� ���ମ�, 1-������, 2-���孨�*/
  /*��砫�� ���� ����ᮢ ���ମ� � ��� : 0�320 */
  const unsigned char num_alm[4][2]={{0,1},{2,3},{4,5},{6,7}};
  unsigned char flag,cr[4],j,buf_alm[16];
  if (borders[2]<=0.0 || (borders[1]-borders[0])<=0.0) {flag=2;goto M;}
  FormateEvent(buf_alm);buf_alm[13]=num_pnt;flag=0;
  if (status == 0  && value > borders[1])
  {status=2;flag=1;buf_alm[10]=1;buf_alm[14]=num_alm[num_prm][1];} else
  if (status == 2 && value<=(borders[1]-borders[2]))
  {status=0;flag=1;buf_alm[10]=0;buf_alm[14]=num_alm[num_prm][1];} else
  if (status == 0 && value < borders[0])
  {status=1;flag=1;buf_alm[10]=1;buf_alm[14]=num_alm[num_prm][0];} else
  if (status == 1 && value>= (borders[0]+borders[2]))
  {status=0;flag=1;buf_alm[10]=0;buf_alm[14]=num_alm[num_prm][0];}
  if (flag == 1)
  {
    ConvToBynare(value,cr);
    for (j=0;j<4;j++) buf_alm[6+j]=cr[j];WriteEvent(buf_alm,1);
    X607_Write(390,32+num_pnt*4+num_prm,status);
  }
  M:return status;
}
/******** ��⠭���� ��� ���⪠ ���ମ� �窨 ���� ***************/
void  SetClearAlarms (struct configparam *cnf,struct dynparams bs,
		      unsigned char num_pnt)
{
  unsigned char i;
  for (i=0;i<3;i++) if ((cnf->enable_alm & etl[i]) > 0)
  cnf->status_alm[i]=SetClearAlarmsPrm(cnf->borders[i],cnf->status_alm[i],
		    bs.dyn[main_dyn[i][0]],num_pnt,i);
  if ((cnf->enable_alm & etl[3]) > 0) /*��� ���ᮢ��� ��室�*/
  cnf->status_alm[3]=SetClearAlarmsPrm(cnf->borders[3],cnf->status_alm[3],
		    bs.dyn[main_dyn[6][0]],num_pnt,3);
}
/******* ���樠������ ��ࠬ��஢ ��������: �⠭�� ***********/
void InitStationStruct (struct station *dv)
{
  unsigned char i;
  dv->task=ReadEEP(7,0);dv->addr=ReadEEP(7,1);
  dv->contrh=ReadEEP(7,2);dv->mmi=ReadEEP(7,3);
  for (i=0;i<4;i++) dv->adr_mvs[i]=ReadEEP(7,4+i);
  for (i=0;i<4;i++) dv->mvs_eep[i]=4+i;
  for (i=0;i<4;i++) dv->adr_icp[i]=ReadEEP(7,8+i);
  for (i=0;i<4;i++) dv->typ_icp[i]=ReadEEP(7,14+i);
  for (i=0;i<4;i++) dv->passw[i]=ReadEEP(7,19+i);
  dv->autogo=ReadEEP(7,12);dv->hart=ReadEEP(7,13);
  dv->modbus=ReadEEP(7,18);
  for (i=0;i<4;i++)
  {dv->com[i][0]=ReadEEP(7,23+i*2);dv->com[i][1]=ReadEEP(7,24+i*2);}
  for (i=0;i<10;i++) dv->tag[i]=ReadEEP(7,191+i);
  for (i=0;i<20;i++) dv->phone[i]=ReadEEP(7,201+i);
  for (i=0;i<10;i++) dv->at[i]=ReadEEP(7,221+i);
  Modbus.mode=(dv->modbus & 16) >> 4;Modbus.delay=dv->modbus & 7;
  Modbus.protocol=(dv->modbus & 8) >> 3;
  Modbus.connect=(dv->modbus & 96) >> 5;dv->set_com=ReadEEP(7,233);
  dv->passw_op=ReadEEP(7,231)*256+ReadEEP(7,232);
  dv->script=ReadEEP(7,234);dv->panel=ReadEEP(7,235);
}
/******* ���樠������ ��������:���䨣���� ���� ����**********/
void InitBasicStruct (unsigned char num,struct configparam *cnf,
		      struct dynparams *bs)
{
  unsigned char i,j,k,cr[4];float buf[16];
  cnf->status=ReadEEP(num,0);cnf->sensor=ReadEEP(num,1);
  cnf->s_diff=ReadEEP(num,2);cnf->s_press=ReadEEP(num,3);
  cnf->s_tempr=ReadEEP(num,4);cnf->stack=ReadEEP(num,5);
  cnf->enable_alm=ReadEEP(num,72);
  cnf->therm_corr=ReadEEP(num,6);cnf->flow_corr=ReadEEP(num,71);
  cnf->m_pipe=ReadEEP(num,7);cnf->m_sens=ReadEEP(num,8);
  cnf->method=ReadEEP(num,9);cnf->s_egle=ReadEEP(num,10);
  for (i=0;i<15;i++)
  { /*����祭�� �᭮���� ���䨣.��ࠬ��஢*/
    j=i*4;
    if (SecurityConvert(ReadEEP(num,11+j),ReadEEP(num,12+j),
       ReadEEP(num,13+j),ReadEEP(num,14+j),cr)==0)
    buf[i]=ConvToFloat(cr[0],cr[1],cr[2],cr[3]);
  } cnf->interv=buf[0];cnf->pipe_size=buf[1];cnf->sens_size=buf[2];
  cnf->cut_flow=buf[3];cnf->radius=buf[4];cnf->rougness=buf[5];
  bs->dyn[12]=buf[6];bs->dyn[16]=buf[7];bs->dyn[20]=buf[8];
  for (k=0;k<3;k++) {cnf->k_pipe[k]=buf[9+k];cnf->k_sens[k]=buf[12+k];}
  for (i=0;i<14;i++)
  { /*����祭�� ��⠢�� ���ମ�*/
    j=i*4;
    if (SecurityConvert(ReadEEP(num,73+j),ReadEEP(num,74+j),
       ReadEEP(num,75+j),ReadEEP(num,76+j),cr)==0)
    buf[i]=ConvToFloat(cr[0],cr[1],cr[2],cr[3]);
  } cnf->hi_stack=buf[0];cnf->lo_stack=buf[1];
  for (i=0;i<4;i++) for (j=0;j<3;j++) cnf->borders[i][j]=buf[2+3*i+j];
  for (i=0;i<10;i++) cnf->tag[i]=ReadEEP(num,129+i);
}
/******* ���樠������ ��ࠬ��஢ ��娢� *************/
unsigned char InitArchive (struct station *dv)
{
  unsigned char i,k;k=0;
  for (i=0;i<Max_arch_pnt;i++)
  {
    dv->arch[i][0]=ReadEEP(7,31+i*4);dv->arch[i][1]=ReadEEP(7,32+i*4);
    dv->arch[i][2]=ReadEEP(7,33+i*4);dv->arch[i][3]=ReadEEP(7,34+i*4);
    if (dv->arch[i][0] != 0) k++;
  } return 7+k*4;
}
/******** �஢�ઠ �ਭ� ���㡠� � ���४�� �᫨ +- 10% *******/
unsigned char VerifyAnnubar (unsigned char tp,float *annubar)
{
  const float d[8] = {4.3942,9.271,21.7424,31.369,49.53,14.986,
		      26.924,48.768};/*�।��� �ਭ� ���㡠�*/
  if ((*annubar > 1.1 * d[tp])||(*annubar < 0.9 * d[tp]))
  { *annubar=d[tp];return 1;} else return 0;
}
/******** ���᫥��� �����樥�� �����஢�� ���� ***************/
double BettaKoeff (float pipe,float annubar)
 {
   return 1.273239 * annubar / pipe;
 }
/********* ���᫥��� �����樥�� ��⮪� �� ⨯� ���㡠� *******/
double AnnubarKoeff (double betta,unsigned char type)
 {
   const double c1[8] = {-0.8212,-1.3452,-1.43,-1.3416,-1.2957,-1.515,
			-1.492,-1.5856};
   const double c2[8] = {0.7269,0.92,1.265,1.2075,1.24,1.4229,1.4179,
			1.3318};
   double a,c,d; a=0.0;
   if (type == 0) a = c1[type] * betta + c2[type];
   else if (type < 8)
     {
       d = 1 - c2[type] * betta;c = d * d;
       c = sqrt(1 - c1[type] * c);a = d / c;
     }
   return a;
 }
/*** ���᫥��� �����.��⮪� �� ⨯� ����ࠣ��:䫠�楢��,㣫�� ***/
float CalcOrifNewC (float rein,float betta,float pipe,float b4,
		    unsigned char type)
{ /*������� ���� � �����*/
  double A,M1,M2,L1,L2;
  if (rein>1000)
  {
    switch (type)
    {
      case 0:L1=L2=0;break; /*㣫����*/
      case 1:L1=L2=0.0254/pipe;break;/*䫠�楢�*/
      case 2:L1=1;L2=0.47;break;/*����ࠤ����*/
    } A=pow(19000*betta/rein,0.8);M1=2*L2/(1-betta);
    if (pipe<0.07112) M2=0.011*(0.75-betta)*(2.8-pipe/0.0254);else M2=0;
    return 0.5961+0.0261*betta*betta-0.216*b4*b4+
	 0.000521*pow(1E6*betta/rein,0.7)+(0.0188+0.0063*A)*pow(betta,3.5)*
	 pow(1E6/rein,0.3)+(0.043+0.08*exp(-10*L1)-0.123*exp(-7*L1))*
	 (1-0.11*A)*b4/(1-b4)-0.031*(M1-0.8*pow(M1,1.1))*pow(betta,1.3)+M2;
  } else return 1.0;
}
/********* ���᫥��� ���ࠢ�� �� ���㯫���� �஬��**************/
/** ������� �����. � ࠤ��� � �,���������� ����.� ����� ****/
float CalcOrifNewEgle (double radius,float sensor,float interv,
		       unsigned char stack)
{
  double rk;radius=radius/1E3;
  if (stack == 0 && interv > 0)
  rk=0.000195-(3.0/interv)*(0.000195-radius)*(1-exp(-interv/3.0));
  if (stack == 1) rk=0.000195-(0.000195-radius)*exp(-interv/3.0);
  if (rk <= 0.0004*sensor) return 1.0;else
  return 0.9826+pow((rk/sensor+0.0007773),0.6);
}
/************ ���᫥��� �����.���७�� �� ����ࠣ�� **********/
float CalcOrifNewExpand (float diff,float press,double b4,float adiab)
{ /*��९�� � �������� � ��᪠���*/
  return 1-(0.351+0.256*b4+0.93*b4*b4)*(1-pow(1-diff/press,1/adiab));
}
/************** �믮���� ���㣫���� �� 楫��� ******************/
float RoundFloat (double value)
{
  float a,b;a=fabs(value);b=floor(a);if ((a-b)>=0.5) b=b+1;
  if (value < 0) b=-b;return b;
}
/************** ���㣫�� �� ���� ����� ࠧ�冷� **************/
float RoundToTwo (double value)
{
  int a;
  a=log10(value);
  if (a>1) value=RoundFloat(value/pow(10,a-1))*pow(10,a-1); else
  if (a>-2) value=RoundFloat(value*10)/10;else value=0.0; return value;
}
/********* ������ ���ࠢ�� �� ��客����� ���� ************/
float CalcOrifNewRougness (float rein,float betta,double pipe,
			   double rougness)
{ /*�� ࠧ���� � �����*/
  const double kf1[3][4]={{8.87,-3.7114,0.41841,0.0},
			  {6.7307,-5.5844,0.732485,0.0},
			  {-10.244,5.7094,-0.76477,0.0}};
  const double kf2[3][4]={{27.23,-11.458,1.6117,-0.07567},
			  {-25.928,12.426,-2.09397,0.106143},
			  {1.7622,-3.8765,1.05567,-0.076764}};
  const double kf3[3][4]={{16.5416,-6.60709,0.88147,-0.039226},
			  {322.594,-132.2,17.795,-0.799765},
			  {-92.029,37.935,-5.1885,0.23583}};
  const float pi=3.141592;
  double max,min,logrein,lj,lj1,kr,kd,Ash,A[3],avg;unsigned char i,k;
  if (rein > 1000)
  {
    logrein=log10(rein);rougness=rougness/1E3;
    for (i=0;i<3;i++) A[i]=0.0;avg=rougness/pi;
    if (rein>1E4 && rein<=1E5) for (i=0;i<3;i++) for (k=0;k<4;k++)
      A[i]=A[i]+kf1[i][k]*pow(logrein,k); else
    if (rein>1E5 && rein<=3E6) for (i=0;i<3;i++) for (k=0;k<4;k++)
      A[i]=A[i]+kf2[i][k]*pow(logrein,k); else
    if (rein>3E6 && rein<=1E8) for (i=0;i<3;i++) for (k=0;k<4;k++)
      A[i]=A[i]+kf3[i][k]*pow(logrein,k);
    if (rein<=1E4) max=0.718866*pow(betta,-3.887)+0.364; else
    if (rein>1E4 && betta<0.65) max=A[0]*pow(betta,A[1])+A[2]; else
    if (rein>1E4 && betta>=0.65) max=A[0]*pow(0.65,A[1])+A[2];
    if (max>=15) max=15*pipe/1E4;else {max=RoundToTwo(max);max=max*pipe/1E4;}
    if (rein < 3E6) min=0.0;else
    {
      if (betta<0.65) min=7.1592-12.387*betta-(2.0118-3.469*betta)*logrein+
		      (0.1382-0.23762*betta)*logrein*logrein; else
       min=-0.892353+0.24308*logrein-0.0162562*logrein*logrein;
      if (min <= 0) min=0;else {min=RoundFloat(min*1E3)/1E3;min=min*pipe/1E4;}
    }
    if (avg > max || avg < min)
    {
      Ash=rougness;kd=0.26954*rougness/pipe;kr=5.035/rein;
      lj=1.74-2*log10(2*Ash/pipe-37.36*log10(kd-kr*log10(kd+3.3333*kr))/rein);
      lj=pow(lj,-2.0);
      if (avg>max) {Ash=pi*max;kd=0.846784*max/pipe;}
      if (avg<min) {Ash=pi*min;kd=0.846784*min/pipe;}
      lj1=1.74-2*log10(2*Ash/pipe-37.36*log10(kd-kr*log10(kd+3.3333*kr))/rein);
      lj1=pow(lj1,-2.0);return 1+5.22*pow(betta,3.5)*(lj-lj1);
    } else return 1.0;
  } else return 1.0;
}
/************** ���᫥��� ������⥫� �������� ******************/
float CalcAdiabat (float abstemp,float pmega,float azot,float dens)
{
  return 1.556 * (1 + 0.074 * azot) - 3.9E-4 * abstemp * (1 - 0.68 * azot)
  - 0.208 * dens + pow(pmega/abstemp,1.43) * (384 * (1 - azot) *
  pow(pmega/abstemp,0.8) + 26.4 * azot);
}
/************ ���᫥��� �����樥�� ���७�� ****************/
float YaKoeff (float betta,float diff,float press,float adiabat)
 {
   double expan;
   expan = (1 - betta) * (1 - betta) * 0.31424 - 0.09484;
   if (press > 0)
     return (1 - expan * diff / press / adiabat);else return 1.0;
 }
/*** ⥬�����ୠ� ���४�� ������� ���� �� ⨯� ���ਠ�� ****/
double DiameterCorrectP(float diametr,float temper,unsigned char type)
 {
   const float ka[11] = {10.821,10.8,11.1,11.66,10.75,11.1,10.26,10.2,
			 11.6,10.0,16.206};
   const float kb[11] = {17.872,9.0,7.9,9.0,12.5,7.7,14.0,10.4,0.0,9.6,6.571};
   const float kc[11] = {-10.986,-4.2,-3.9,0.0,0.0,-3.4,0.0,-5.6,0.0,-6.0,0.0};
   double a;
   a = 1.0E-6*(ka[type]+1.0E-3*temper*kb[type]-1.0E-6*temper*temper*kc[type]);
   return diametr*(1+a*(temper-20));
 }
/************* ⥬�����ୠ� ���४�� ������� �� ***************/
double DiameterCorrectD(float diametr,float temper,unsigned char type)
 {
   const float ka[11] = {15.2,14.7,16.466,10.0,16.206,10.235,11.065,15.6,
			 15.22,16.216,15.8};
   const float kb[11] = {6.6,9.8,5.36,9.6,6.571,18.64,11.224,8.3,13.0,6.4,0.0};
   const float kc[11] = {0.6,7.4,3.0,-6.0,0.0,-13.0,-5.381,-6.5,0.0,0.0,0.0};
   double a;
   a = 1.0E-6*(ka[type]+1.0E-3*temper*kb[type]-1.0E-6*temper*temper*kc[type]);
   return diametr*(1+a*(temper-20));
 }
/*********** ���᫥��� �����樥�� ᦨ������� �� �⠭�.��.*****/
 double CalcSFactor (float density,float N2,float CO2)
 {
   double factor;
   factor = 0.0741 * density - 0.006 - 0.063 * N2 - 0.0575 * CO2;
   factor = factor * factor;return (1 - factor);
 }
/*****************************************************************/
 double CalcPpk (float density,float N2,float CO2)
 {
   return 2.9585 *(1.608 - 0.05994*density - 0.392 * N2 + CO2);
 }
/*****************************************************************/
 double CalcTpk (float density,float N2,float CO2)
 {
   return 88.25 *(0.9915 + 1.759*density - 1.681 * N2 - CO2);
 }
/********* ���᫥��� �����樥�� ᦨ������� �� NX-19 **********/
/* �������� � ���,⥬������ � ��.���좨�� */
unsigned char CalcNX19Koeff (double Ppk,double Tpk,float press,
		   float temper,float standart,float *compress)
 {
   double Pa,Ta,Ta2,Ta4,Pa2,musor,factor;unsigned char type;
   double Q0,Q1,Q02,B0,B1,B2,dTa,F,Pa23,dTa05,dTa2,E20dTa;

   Pa = 0.6714 * press / Ppk + 0.0147;Ta = 0.71892 * temper / Tpk + 0.0007;
   type=0;dTa =Ta - 1.09;
   if (Pa >= 0) if (Pa <= 2) if (dTa >= 0) if (dTa <= 0.3) type=1;
   if (Pa >= 0) if (Pa < 1.3) if (dTa >= -0.25) if (dTa < 0) type=2;
   if (Pa >= 1.3) if (Pa < 2) if (dTa >= -0.25) if (dTa < 0) type=3;
   if (type != 0)
   {
     Pa2 = Pa * Pa;Ta2 = Ta * Ta;Ta4 = Ta2 * Ta2;
     Q1 = Ta4 * Ta / (Ta2 * (6.60756 * Ta - 4.42646) + 3.22706);
     Q0 = Ta2 * (1.77218 - 0.8879 * Ta) + 0.30513;
     Q0 = Q0 * Q1 / Ta4;Q02 = Q0 * Q0;
     B1 = 2 * Q1 / 3 - Q02;dTa2 = dTa * dTa;
     Pa23 = 0.00075 * pow(Pa,2.3);E20dTa = exp(20 * dTa);
     switch (type)
     {
       case 1:dTa05 = sqrt(dTa);musor = Pa * (2.17 - Pa +1.4 * dTa05);
	      F = Pa23 / E20dTa + 0.0011 * dTa05 * musor * musor;break;
       case 2:F = Pa23 * (2 - E20dTa) + 1.317 * Pa * (1.69 - Pa2) * dTa2 *
		  dTa2;break;
       case 3:F = Pa23 * (2 - E20dTa) + 0.455 * (1.3 - Pa) * (4.01952 - Pa2) *
		  (dTa *(0.03249 + 18.028 * dTa2) + dTa2 *(2.0167 + dTa2 *
		  (42.844 + 200 * dTa2)));break;
     }
     B0 = Q0 * (Q1 - Q02) + 0.1 * Q1 * Pa * (F - 1);
     B2 = B0 + sqrt(B0 * B0 + B1 * B1 * B1);B2 = pow(B2,0.3333333);
     factor = 1 + 0.00132 / pow(Ta,3.25); factor = factor * factor;
     factor = factor * Pa * 0.1 / (B1 / B2 - B2 + Q0);
     *compress=factor / standart;return 0;
   } else {*compress=1.0;return 1;}
 }
/********* ���᫥��� �����樥�� ᦨ������� �� GERG-91 **********/
/* �������� � ���,⥬������ � ��.���좨��,���� � �.��� � ����� */
unsigned char CalcGERG91Koeff (float azt,float ugl,float press,
	   float temper,float standart,float dens,float *compress)
{
  double b,Xe,Xe2,Me,H,H2,T,T2,B1,B2,B23,B3,C1,C2,C3,Az2,Ug2;
  double C0,B0,A0,A1,A2,C223,C233,Bz,Cz,Bm,Cm,Z,aa,k;
  T=temper;b=1000*press/(2.7715*T);T2=T*T;Az2=azt*azt;Ug2=ugl*ugl;
  Xe=1-azt-ugl;k=0.3333333333;
  Me=(24.05525*standart*dens-28.0135*azt-44.01*ugl)/Xe;Xe2=Xe*Xe;
  H=128.64+47.479*Me;H2=H*H;
  B1=-0.425468+2.865*T/1000-4.62073*T2/1E6+
     (8.77118/10000-5.56281*T/1E6+8.8151*T2/1E9)*H+
     (-8.24747/1E7+4.31436*T/1E9-6.08319*T2/1E12)*H2;
  B2=-0.1446+7.4091*T/10000-9.1195*T2/1E7;
  B23=-0.339693+1.61176*T/1000-2.04429*T2/1E6;
  B3=-0.86834+4.0376*T/1000-5.1657*T2/1E6;
  C1=-0.302488+1.95861*T/1000-3.16303*T2/1E6+
     (6.46422/10000-4.22876*T/1E6+6.88157*T2/1E9)*H+
     (-3.32805/1E7+2.2316*T/1E9-3.67713*T2/1E12)*H2;
  C2=7.8498/1000-3.9895*T/1E5+6.1187*T2/1E8;
  C3=2.0513/1000+3.4888*T/1E5-8.3703*T2/1E8;
  C223=5.52066/1000-1.68609*T/1E5+1.57169*T2/1E8;
  C233=3.58783/1000+8.06674*T/1E6-3.25798*T2/1E8;
  Bz=0.72+1.875/1E5*(320-T)*(320-T);
  Cz=0.92+0.0013*(T-270);
  Bm=Xe2*B1+Xe*azt*Bz*(B1+B2)-1.73*Xe*ugl*sqrt(B1*B3)+
     Az2*B2+2*azt*ugl*B23+Ug2*B3;
  Cm=Xe2*Xe*C1+3*Xe2*azt*Cz*pow(C1*C1*C2,k)+2.76*Xe2*ugl*pow(C1*C1*C3,k)+
     3*Xe*Az2*Cz*pow(C1*C2*C2,k)+6.6*Xe*azt*ugl*pow(C1*C2*C3,k)+
     2.76*Xe*Ug2*pow(C1*C3*C3,k)+Az2*azt*C2+3*Az2*ugl*C223+
     3*azt*Ug2*C233+Ug2*ugl*C3;
  C0=b*b*Cm;B0=b*Bm;A1=1+B0;A0=1+1.5*(B0+C0);aa=A0*A0-A1*A1*A1;
  if (aa>=0)
  {
    aa=A0-sqrt(aa);if (aa>=0)
    {
      A2=pow(aa,k);Z=(1+A2+A1/A2)/3.0;*compress=Z/standart;return 0;
    } else  {*compress=1.0;return 1;}
  } else {*compress=1.0;return 1;}
}
/********* ���᫥��� ����������� ��室� �� �⠭�. ��.**********/
float CalcFlowRate (double pipe,float diff,float press,float temper,
	    float density,float Z,float Ya,float Ka,float cut_flow)
 {
   if ((diff>=(cut_flow*1000))&&(diff>0))
    return 0.78539816 * Ka * Ya * pipe * pipe * 3600 *
	    sqrt(0.00578632 * diff * press / temper / density / Z);
   else return 0.0;
 }
/********** ���᫥��� �������᪮� �離��� ********************/
float CalcViscosity (float temper,float density,float N2,float CO2)
{
  return 3.24 * (sqrt(temper) + 1.37 - 9.09 * pow(density,0.125)) /
	(sqrt(density) + 2.08 - 1.5 * (N2 + CO2))/1E3;
}
/*********** ���᫥��� �������᪮� �離��� �� �����. ����.******/
float CalcViscExt (float Vs,float Ppk,float Tpk,float press,
		   float temper)
{
  press = press / Ppk;temper = temper / Tpk;
  return  Vs * (1 + press * press / 30 / (temper - 1));
}
/*********** ���᫥��� ���⭮�� �� ࠡ. ��. � ��/� **********/
float CalcDensWork (float density,float press,float temper,float Z)
 {
   if ((temper > 0)&&(Z > 0))
     return density * press * 2.893165 / temper / Z;
   else return 0.0;
 }
/********** ���᫥��� ᪮��� ��⮪� � �/ᥪ *******************/
float CalcVelosity (float density,float flow,float work,float pipe)
 {
  if (work > 0)
     return 0.000353675 * flow * density / pipe / pipe / work;
   else return 0.0;
 }
/************* ���᫥��� �᫠ �������� ��� ���㡠� **********/
float CalcReinAnnubar (float sens_m,float velosity,float density,
		       float visc)
{
  float value;
  if (visc > 0) value=sens_m*velosity*density/visc;else value=0;
  return value;
}
/*****************************************************************/
/******** ���᫥��� ��� ��ࠬ��஢ ��室� *********************/
/* �室�� ��ࠬ����:��९��(0),��������(4),⥬������(8),
  ���⭮���(12),����(16),㣫��.���(20),�����.��室(24),�����.ᦨ�������(32),
  �����.��⮪�(33),�����.���७��(34),�����.�離����(39),
  ࠡ��.���⭮���(42),᪮���� ��⮪�(40),�᫮ ��������(38),
  ���ࠢ�� �� �������� �஬��(35),���ࠢ�� �� ��客�����(36),
  ���ࠢ�� �� �᫮ ��������(37),������⥫� ��������(41) *******/
unsigned char CalcFlowMain (struct configparam Prm,struct dynparams *Bs)
{
   float B,azt,ugl,std,Pp,Tp,tabs,pmega,d_pa,p_pa,Z,mass,E,
	 c_10e6,ru_10e6,re_zvz,re_new,c_new,ru_new;
   double b4,pipe_m,sens_m;
   unsigned char result, step, flag; result=flag=0;Bs->dyn[24]=0.0;
   if (Prm.pipe_size<=0 || Prm.m_pipe>11) {result=1; flag=1;}
   if (Prm.sens_size<=0 || Prm.m_sens>11 || Prm.sensor>10)
     {result=result+2; flag=1;}
   if ((Bs->dyn[12]<0.6)||
       (Bs->dyn[12]>0.75)||(Bs->dyn[16]>10)||(Bs->dyn[20]>5))
     {result=result+4; flag=1;}
   if (Bs->dyn[0]>128) {result=result+8; flag=1;}
   if (Bs->dyn[4]<=0 || Bs->dyn[4]>5500)  {result=result+16;flag=1;}
   if (Bs->dyn[8]< -50 || Bs->dyn[8]>50)  {result=result+32;flag=1;}
   if (flag==1) {Bs->dyn[24]=0.0; goto M;} /*���室 �� �訡��*/
   azt=Bs->dyn[16]/100;ugl=Bs->dyn[20]/100;tabs=Bs->dyn[8]+273.15;
   pmega=Bs->dyn[4]/1E3;p_pa=Bs->dyn[4]*1E3;d_pa=Bs->dyn[0]*1E3;
   if ((Prm.sensor>2)&&(Prm.sensor<11))
   if (VerifyAnnubar (Prm.sensor-3,& Prm.sens_size)==1)
     result=result+2;/*�஢�ઠ �ਭ� ���㡠�*/
   Prm.pipe_size= DiameterCorrectP(Prm.pipe_size,Bs->dyn[8],Prm.m_pipe);
   Prm.sens_size= DiameterCorrectD(Prm.sens_size,Bs->dyn[8],Prm.m_sens);
   Bs->dyn[41]=CalcAdiabat(tabs,pmega,azt,Bs->dyn[12]);
   std= CalcSFactor(Bs->dyn[12],azt,ugl);
   Pp= CalcPpk(Bs->dyn[12],azt,ugl);Tp= CalcTpk(Bs->dyn[12],azt,ugl);
   if (Prm.method==0)
   { if (CalcNX19Koeff(Pp,Tp,pmega,tabs,std,&Z)!=0) result=result+4;}/*�஢�ઠ*/
   else
   {
     if (CalcGERG91Koeff(azt,ugl,pmega,tabs,std,Bs->dyn[12],&Z)!=0)
     result=result+4;
   }
   Bs->dyn[32]=Z;pipe_m=Prm.pipe_size/1E3;
   Bs->dyn[39]= CalcViscosity(tabs,Bs->dyn[12],azt,ugl);
   if (Bs->dyn[4] > 500)
   Bs->dyn[39]= CalcViscExt(Bs->dyn[39],Pp,Tp,pmega,tabs);
   Bs->dyn[42]= CalcDensWork(Bs->dyn[12],Bs->dyn[4],tabs,Bs->dyn[32]);
   if ((Prm.sensor>2)&&(Prm.sensor<11))
   {
     B= BettaKoeff(Prm.pipe_size,Prm.sens_size);
     Bs->dyn[33]= AnnubarKoeff(B,Prm.sensor-3);
     Bs->dyn[34]= YaKoeff(B,Bs->dyn[0],Bs->dyn[4],Bs->dyn[41]);
     Bs->dyn[24]= CalcFlowRate(pipe_m,d_pa,p_pa,tabs,Bs->dyn[12],
		  Bs->dyn[32],Bs->dyn[34],Bs->dyn[33],Prm.cut_flow);
     Bs->dyn[40]= CalcVelosity(Bs->dyn[12],Bs->dyn[24],Bs->dyn[42],pipe_m);
     Bs->dyn[38]= CalcReinAnnubar(Prm.sens_size,Bs->dyn[40],Bs->dyn[42],
				  Bs->dyn[39]);
   } else
   if (Prm.sensor<3 && Bs->dyn[0]>=Prm.cut_flow && Bs->dyn[12]>0)
   {
     B=Prm.sens_size/Prm.pipe_size;
     if ((B > 0.75)||(B < 0.2)) {result=result+2;Bs->dyn[24]=0.0;goto M;}
     b4=B*B*B*B;sens_m=Prm.sens_size/1E3;E=1/sqrt(1-b4);
     Bs->dyn[34]=CalcOrifNewExpand(d_pa,p_pa,b4,Bs->dyn[41]);
     Bs->dyn[35]=CalcOrifNewEgle(Prm.radius,sens_m,Prm.interv,Prm.s_egle);
     c_10e6=CalcOrifNewC(1E6,B,pipe_m,b4,Prm.sensor);
     ru_10e6=CalcOrifNewRougness(1E6,B,pipe_m,Prm.rougness);
     re_zvz=c_10e6*ru_10e6*sens_m*Prm.sens_size*E*Bs->dyn[35]*
	    Bs->dyn[34]*sqrt(2*d_pa*Bs->dyn[42])/Prm.pipe_size/
	    (Bs->dyn[39]/1E3);re_new=re_zvz;step=1;
   M2:c_new=CalcOrifNewC(re_new,B,pipe_m,b4,Prm.sensor);
      ru_new=CalcOrifNewRougness(re_new,B,pipe_m,Prm.rougness);
      Bs->dyn[38]=c_new*ru_new*re_zvz/c_10e6/ru_10e6;
      if (Bs->dyn[38]>1000)
      if (fabs((Bs->dyn[38]-re_new)/Bs->dyn[38]) > 1E-4) if (step<=5)
      {re_new=Bs->dyn[38];step++;goto M2;}
     Bs->dyn[37]=0;Bs->dyn[36]=ru_new;
     Bs->dyn[24]=2827.43337*sens_m*sens_m*c_new*E*ru_new*Bs->dyn[35]*
		 Bs->dyn[34]*sqrt(2*d_pa*p_pa*293.15/Bs->dyn[12]/
		 101325/tabs/Bs->dyn[32]);
     Bs->dyn[33]=c_new*E;
     Bs->dyn[40]=CalcVelosity(Bs->dyn[12],Bs->dyn[24],Bs->dyn[42],pipe_m);
   } else Bs->dyn[24]=0.0;
   M:return result;
}
/******** �ନ஢���� ��娢��� ����� �� ⨯� ��娢� � �窠� ***/
unsigned char FormateArchive (struct station dv,struct dynparams bs[],
			  unsigned char typ_arc,unsigned char buf[],
			  struct expandparams exp)
{
  unsigned char i,j,ind_pnt,cr[4];float value;ind_pnt=0;
 /* printf(" begin "); */
  for (i=0;i<Max_arch_pnt;i++)
  if (dv.arch[i][0] !=0 && dv.arch[i][1]<4 && dv.arch[i][3]<7)
  {
    /*printf(" point %d %d %d %d",dv.arch[i][0],dv.arch[i][1],dv.arch[i][2],dv.arch[i][3]);*/
    value=0.0;
    switch (dv.arch[i][0])
    { case 1:if (dv.arch[i][2]<Max_dyn_all)
	     switch (dv.arch[i][3])
	     {
	       case 1:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]];break;
	       case 2:
	       switch (typ_arc)
	       {
		 case 0:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+2];break;
		 case 1:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+1];break;
		 case 2:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+7];break;
	       } break;
	       case 3:
		 value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+typ_arc+1];break;
	       case 4: case 6:
		 value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+dv.arch[i][3]];break;
	     } break;
      case 2:switch (dv.arch[i][3])
	     {
	       case 1:value=exp.dyn[dv.arch[i][2]];break;
	       case 2:
	       switch (typ_arc)
	       {
		 case 0:value=exp.dyn[dv.arch[i][2]+2];break;
		 case 1:value=exp.dyn[dv.arch[i][2]+1];break;
		 case 2:value=exp.dyn[dv.arch[i][2]+7];break;
	       } break;
	       case 3:
		 value=exp.dyn[dv.arch[i][2]+typ_arc+1];break;
	       case 4: case 6:
		 value=exp.dyn[dv.arch[i][2]+dv.arch[i][3]];break;
	     } break;
    } ConvToBynare(value,cr);
      for (j=0;j<4;j++) buf[7+ind_pnt*4+j]=cr[j];ind_pnt++;
  } return ind_pnt;
}
/******************************************************************/