/*****************************************************************************

							 グラディウス III
							- 伝説から神話へ -

					<< キューブ９９連発シミュレーション >>

										作成開始年月日／平成３年２月１２日
*****************************************************************************/

#include <iocslib.h>
#include <stdio.h>
#include <basic.h>
#include <basic0.h>
#include <class.h>
#include <sprite.h>
#define	NL	1312904009

int ESCSNS();
int SPCSNS();
int HLPSNS();
int OP1CSNS();
int SNS2();
int SNS4();
int SNS6();
int SNS8();
void teki();
void X68ooo();
UBYTE palloc( UBYTE *, UBYTE *, UBYTE );
void  pfree( UBYTE *, UBYTE );
void enemy_load( char * );
void g_scroll0111();
void bgmes( UBYTE, UBYTE, UWORD, char *, int );
void sp_clear( int, int );
UBYTE pcm_load( char *, char *, UWORD );
void direct_load( char *, char *, char *, WORD );
void spl_load( char * );
void spp_load( char * );
void palet_light( UWORD *, UWORD * );
void palet_dark( UWORD * );
void put_star();

char cube_app[9][9]={							/*出現座標データ*/
{	6,	10,	2,	6,	2,	2,	6,	9,	6},
{	1,	8,	6,	1,	5,	6,	2,	8,	2},
{	8,	3,	11,	8,	11,	11,	8,	3,	8},
{	5,	9,	7,	5,	7,	7,	5,	9,	5},
{	11,	3,	11,	7,	10,	11,	8,	3,	8},
{	8,	2,	6,	7,	6,	6,	8,	3,	8},
{	9,	5,	12,	8,	13,	13,	9,	5,	9},
{	11,	6,	3,	11,	3,	3,	11,	6,	11},
{	2,	8,	6,	1,	7,	7,	5,	9,	5}
};
int app_point,rand_num;

WORD enemy_tbl[4*100];
UBYTE pl_tbl[128];
struct GEAS {
	char		id,		/*キャラクタＩＤ*/
				atr,	/*未使用*/
				xs,		/*キャラクタ半径*/
				ys;
	WORD		x,		/*中心座標*/
				y;
};
struct GEAS my,you[128];
int main_cnt,p,teki_num;
int tama_p;
int speed;
int pro_up_down_flg,pro_up_down_cnt;
int stick_ptn0;
int stick_ptn1;
int jiki_p;
int jiki_xx,jiki_yy,jiki_wx,jiki_wy;
int end_flg;
WORD teki_ptn[128];
WORD teki_pl[128];
WORD teki_ft[128];
WORD teki_wk0[128];
WORD teki_wk1[128];
WORD teki_wk2[128];
WORD teki_wk3[128];
WORD teki_wk4[128];
WORD pp[128];
char vct[128],gage_pat[1792],score_pat[1920],bgcube_pat[8192],title_pat[14336];
char block[8][512],se00[24963],se01[5639],se02[6325],se03[2400];
UBYTE sp_lvl1,stc_pl1;
int you_p;
char x_buffE[32][70],y_buffE[32][70];
char x_buffB[32][200],y_buffB[32][200];
char *char_num[20]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J"};
UWORD txt_pal[16]={0,65534,54648,1792,2114,0x6830,65534,65534,65534,65534,65534,65534,65534,65534,65534,65534};
UWORD grp_pal[16]={0,65534,58558,48062,41023,28735,36921,32821,28719,26660,22560,18460,51090,41010,1,65534};
int wk[20];
int exit_flg;
UWORD jiki_pro_ptn[5][2]={		/*自機プロのパターン*/
	{0x0210,0x0111},
	{0x0212,0x0113},
	{0x0214,0x0115},
	{0x0216,0x0117},
	{0x0218,0x0119}
};
UBYTE bgmes0[]={
	 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
	10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
	26,27,28,29,30,31,32,33,34,35,36,37,38,39
};
int pcm_flg;
UWORD g_pal[16]={0,65535,61307,57079,52851,48623,44395,40167,35939,31711,27483,23255,21141,19027,16913,14799};
UWORD d_pal[16];
UWORD star_pal[16]={				/*星のパレット*/
	0x0000,0x07fe,0x07fe,0xb7c0,
	0xffc0,0xb7c0,0x07c0,0x07c0,
	0xffc0,0x003e,0x003e,0x003e,
	0xb7c0,0xb7c0,0xffff,0xffff};
int mei0,mei1,mei2,mei3,mei4,mei5;
WORD cube_ptn[8][4]={							/*キューブＳＰパターン*/
	{0x0f40,0x0f41,0x0f48,0x0f49},
	{0x0f42,0x0f43,0x0f4a,0x0f4b},
	{0x0f40,0x0f41,0x0f48,0x0f49},
	{0x0f44,0x0f45,0x0f4c,0x0f4d},
	{0x0f46,0x0f47,0x0f4e,0x0f4f},
	{0x0f40,0x0f41,0x0f48,0x0f49},
	{0x8f4e,0x8f4f,0x8f46,0x8f47},
	{0x8f4c,0x8f4d,0x8f44,0x8f45}};
char rnd_tbl[32]={								/*ランダムテーブル*/
	11,80,-20,51,20,-12,-81,-55,40,-32,
	33,-10,-61,-20,8,80,5,-60,-22,-8,
	60,-70,-38,18,44,61,-51,42,-10,-20,
	26,-49
};
char rnd_tbl1[16]={-64,-120,-94,-110,-94,-80,-112,-64,-92,-72,-104,-40,-101,-80,-102,-84};

UBYTE v70[11*5]={									/*音色*/
	58,15, 0, 0, 0, 0, 0, 0, 0, 3, 0,31,15, 0, 8,15,18, 0, 2, 7, 0, 0,31,15, 0, 8,15,15, 0, 2, 7, 0, 0,31,15, 0, 8,15,16, 0, 2, 3, 0, 0,31,24, 0,12,15, 0, 0, 2, 3, 0, 0};
UBYTE v71[11*5]={									/*音色*/
	58,15, 0, 0, 0, 0, 0, 0, 0, 3, 0,31,15, 0, 8,15,35, 0, 2, 7, 0, 0,25,15, 0, 8,15,44, 0, 2, 3, 0, 0,31,15, 0, 8,15,50, 0, 2, 7, 0, 0,25,24, 0,12,15, 0, 0, 2, 3, 0, 0};
UBYTE v72[11*5]={									/*音色*/
	28,15, 0, 0, 0, 0, 0, 0, 0, 3, 0,31,24, 0,12,15,28, 0,14, 2, 0, 0,31,15, 0, 8,15, 0, 0, 2, 0, 0, 0,31,20, 0, 4,15,20, 0,15, 0, 0, 0,31,14, 0, 5,15, 0, 0, 2, 0, 0, 0};

WORD bgx0,bgx1,gx;
WORD bang_ptn[5]={0x051a,0x051b,0x051c,0x051d,0x051e};
UBYTE way3[32][3]={
{ 0,30, 2},
{ 1,31, 3},
{ 2, 0, 4},
{ 3, 1, 5},
{ 4, 2, 6},
{ 5, 3, 7},
{ 6, 4, 8},
{ 7, 5, 9},
{ 8, 6,10},
{ 9, 7,11},
{10, 8,12},
{11, 9,13},
{12,10,14},
{13,11,15},
{14,12,16},
{15,13,17},
{16,14,18},
{17,15,19},
{18,16,20},
{19,17,21},
{20,18,22},
{21,19,23},
{22,20,30},
{23,21,17},
{24,22,26},
{25,23,29},
{26,24,20},
{27,25,29},
{28,26,30},
{29,27,31},
{30,28, 0},
{31,29, 1}
};

UBYTE wayr[32][3]={
{ 0, 0, 2},
{ 1, 1, 2},
{ 2, 2, 2},
{ 3, 6, 4},
{ 4, 5, 4},
{ 5, 4, 5},
{ 6, 6, 8},
{ 7, 5, 6},
{ 8, 8, 4},
{ 9, 9, 8},
{10,11,12},
{11,11,10},
{12,12,14},
{13,11,13},
{14,13,12},
{15,15,14},
{16,14,15},

{17,16,16},
{18,17,18},
{19,18,18},
{20,19,20},
{21,20,20},
{22,21,22},
{23,22,22},

{24,23,24},
{25,26,25},
{26,27,29},
{27,28,30},
{28,29,31},
{29,30, 0},
{30,31, 1},
{31, 0, 2}
};
UBYTE wayrr[32][3]={
{ 6,30, 4},
{ 1,24, 8},
{18,20,14},
{ 4, 1,30},
{11, 9, 2},
{ 1, 0,16},
{16,14,18},
{ 7,28,12},
{ 0, 4,30},
{12, 8,24},
{23, 5, 3},
{14,19, 4},
{30,31, 0},
{29, 8,15},
{11, 2, 6},
{20, 3,17},
{11,12,22},
{27,25, 9},
{ 8, 6,28},
{ 9,27,11},
{10, 8, 2},
{21,20,11},
{ 2, 0,17},
{14,11,12},
{20,12, 6},
{ 5,30,17},
{11, 3, 2},
{ 0, 0,16},
{15,24,23},
{22, 5, 9},
{ 8,12, 0},
{16,15,28}
};

int jiki_flg;
WORD option0_wx[16],option0_wy[16];
WORD option1_wx[16],option1_wy[16];
WORD option2_wx[16],option2_wy[16];
WORD option3_wx[16],option3_wy[16];
WORD option4_wx[16],option4_wy[16];
WORD option5_wx[16],option5_wy[16];
WORD option6_wx[16],option6_wy[16];
WORD option7_wx[16],option7_wy[16];

WORD option_cnt,wk0;
WORD option_ptn[4]={0x0720,0x0721,0x0722,0x0721};
char option_chk,muteki;
char option_num;	/*オプション個数*/
WORD app_xy[14]={18,36,54,72,88,106,124,140,158,176,184,202,220,238};

/*ＧＲＡＭ消去優先順位*/
char	pri0[]={
	0,	1,	2,	3,	4,	5,	6,	7,
	27,	28,	29,	30,	31,	32,	33,	8,
	26,	47,	48,	49,	50,	51,	34,	9,
	25,	46,	59,	60,	61,	52,	35,	10,
	24,	45,	58,	63,	62,	53,	36,	11,
	23,	44,	57,	56,	55,	54,	37,	12,
	22,	43,	42,	41,	40,	39,	38,	13,
	21,	20,	19,	18,	17,	16,	15,	14
};
char pri[]={
	 1, 7,19,34,56,37, 8, 2,
	 4,15,30,49,45,43,16, 5,
	12,27,51,54,40,29,47,13,
	23,33,57,62,32,14,58,21,
	28,55,63,38,20,22,53,60,
	31,61,52,25,11,18,42,50,
	46,59,41,10, 6,24,35,44,
	36,48, 9, 3, 0,17,26,39
};
char special,opd1,opd2,opd3,opd4,opd5,opd6,opd7,opd8;
WORD hosi_pal[6][6]={			/*★のパレット*/
{0xffff,0xdef6,0xbdee,0x94a4,0xbdee,0xdef6},
{0x9782,0x7ec0,0x6600,0x4d00,0x6600,0x7ec0},
{0x603e,0x4838,0x3032,0x182a,0x3032,0x4838},
{0x0780,0x06c0,0x0600,0x0540,0x0600,0x06c0},
{0xc000,0xa800,0x9000,0x7800,0x9000,0xa800},
{0xe700,0xce40,0xb580,0x9cc0,0xb580,0xce40}};

void main( int argc, char *argv[] )
{
	int i,j,k,a,b,c,d,e;
	FILE *fp;

	asm("
		pea		title_mes
		dc.w	$ff09
		addq.l	#4,sp
	");
	if ( INT_CHK() ) exit( -1 );				/*割り込みチェック*/

	direct_load("DB.DAT",&x_buffB[0][0], &y_buffB[0][0], 200 );
	direct_load("DE.DAT",&x_buffE[0][0], &y_buffE[0][0], 70 );
	enemy_load("CUBE.APP");
	pcm_load( "BANG.PCM",    &se00[0],      (UWORD)sizeof( se00 ) );
	pcm_load( "1UP.PCM",     &se01[0],      (UWORD)sizeof( se01 ) );
	pcm_load( "WARNING.PCM", &se02[0],      (UWORD)sizeof( se02 ) );
	pcm_load( "HIT.PCM",     &se03[0],      (UWORD)sizeof( se03 ) );
	pcm_load( "GAGE.DAT",   &gage_pat[0],   (UWORD)sizeof( gage_pat ) );
	pcm_load( "SCORE.DAT",  &score_pat[0],  (UWORD)sizeof( score_pat ) );
	pcm_load( "BGCUBE.DAT", &bgcube_pat[0], (UWORD)sizeof( bgcube_pat ) );
	pcm_load( "TITLE.DAT",  &title_pat[0],  (UWORD)sizeof( title_pat ) );
	pcm_load( "BLOCK0.GRD", &block[0][0], 512 );
	pcm_load( "BLOCK1.GRD", &block[1][0], 512 );
	pcm_load( "BLOCK2.GRD", &block[3][0], 512 );
	pcm_load( "BLOCK3.GRD", &block[4][0], 512 );
	pcm_load( "BLOCK4.GRD", &block[6][0], 512 );
	pcm_load( "BLOCK5.GRD", &block[7][0], 512 );
	for ( i=0; i<512; i++ ) block[2][i] = block[5][i] = block[0][i];

	asm("
		.include iocscall.mac
		.include  doscall.mac
		movem.l		d1-d4,-(sp)
		iocs		_MS_INIT		*マウスカーソル表示禁止
		moveq.l		#$1,d1
		moveq.l		#$1,d2
		iocs		_TGUSEMD
		IOCS		_MS_CUROF
		moveq.l		#$1,d1
		moveq.l		#$2,d2
		iocs		_TGUSEMD
		iocs		_OS_CUROF		*カ－ソルＯＦＦ
		move.w		#6,d1			*256*256 ２５６色モード
		iocs		_CRTMOD			*screen(0,1,1,1)
		iocs		_G_CLR_ON		*グラフィック画面の初期化
		move.w		#0,d1			*ウィンドウの設定 window(0,0,511,511)
		move.w		#0,d2
		move.w		#511,d3
		move.w		#511,d4
		iocs		_WINDOW
		move.w		#2,-(sp)
		move.w		#14,-(sp)
		dc.w		_CONCTRL
		addq.l		#4,sp
		move.w		#2,-(sp)
		move.w		#10,-(sp)
		dc.w		_CONCTRL
		addq.l		#4,sp
		move.w		#18,-(sp)
		dc.w		_CONCTRL
		addq.l		#2,sp
		movem.l		(sp)+,d1-d4
	");

	sp_disp( 0 );
	sp_clear(0,127);
	bg_fill(0,0x0127);
	bg_fill(1,0x0127);
	vpage( 0 );
	spp_load("CUBE.SPP");
	spl_load("CUBE.SPL");
	bg_set(0,0,1);
	bg_set(1,1,1);
	NNPCMON();
	speed = 1;
	my.id = 1;
	my.xs = 6;
	my.ys = 2;
	TEX_DISP( 0 );
	TEX512CLR();
	TPUT( 0+16, 246, 223+16, 261, gage_pat );
	TPUT( 0+8,   1, 239+8,  16, score_pat );
	TPUT( 0+256, 16, 256+255, 16+111, title_pat );
	SAC_COLOR3( grp_pal );									/* グラフィックパレット設定	*/
	GTSPRW( 0x21 );											/* 優先度設定 TX > GR > SP 	*/
	apage( 0 );
	m_init();												/* ＦＭ音源					*/
	for(i=1 ;i< 9; i++){
		m_alloc(i,1000);
		m_assign(i,i);
	}
	m_vset(70,v70);
	m_vset(71,v71);
	m_vset(72,v72);
	m_trk(1,"t190 @72 o5 l20 p3 q8 y48,00v10a+ <v8q5e32r32rv0e8");
	m_trk(2,"@72 o7 l20 p3 q8 y49,36v8a+ <v12@70q3e+32r32rv0e8");
	m_trk(3,"@72 o3 l20 p3 q8 y50,20v10a+ <v6q4e32r32rv0e8");
	m_trk(4,"@72 o5 l20 p3 q8 y51,40v8a+ <@70q5v5e+32r32rv0e8");
	m_trk(5,"@72 o6 l20 p3 q8 y52,60v11a+ <<v9e2r32r@72v0e8");

	sp_disp( 1 );
	option_num = 4;											/*オプション個数初期値*/
	special = 0;											/*スペシャルモード*/
/*******************************ここよりループ***********************************************/
	while ( 1 ){
		SAC_COLOR2( 0, grp_pal );							/* テキストパレット設定		*/
		bg_scroll(0,0,0);
		bg_scroll(1,0,128);
		sp_disp( 0 );
		TEX_DISP( 0 );
		TEXSCROLL( 256, 0 );
		vpage( 0 );
		bg_set(0,0,1);
		bg_set(1,1,1);
		bg_fill(0,0x0127);
		bg_fill(1,0x0127);
		wipe();
		sp_clear(0,127);
		jiki_xx = jiki_wx = 128 << 4;
		jiki_yy = jiki_wy = 128 << 4;
		my.x = jiki_xx >> 4;
		my.y = jiki_yy >> 4;
		end_flg = 0;
		main_cnt = 0;
		bgmes(4,17,14,"GRADIUS3 CUBE SIMULATION",0);
		bgmes(2,31,14,"@1991 DRY  ALL RIGHT RESERVED",0);
		sp_disp( 1 );
		vpage( 15 );
		bgx0 = 0;
		bgx1 = 128;
		for ( i=0; i<16; i++ ){
			option0_wx[i] = option1_wx[i] = option2_wx[i] = option3_wx[i] = my.x;
			option0_wy[i] = option1_wy[i] = option2_wy[i] = option3_wy[i] = my.y;
			option4_wx[i] = option5_wx[i] = option6_wx[i] = option7_wx[i] = my.x;
			option4_wy[i] = option5_wy[i] = option6_wy[i] = option7_wy[i] = my.y;
		}
		TEX_DISP( 1 );
/*******************************タイトル*****************************************************/
		a = 0;
		while ( !end_flg ){
			if ( ESCSNS() ){
				TEX512CLR();
				asm("
					moveq.l	#$1,d1		*マウスカーソル表示許可
					moveq.l	#$1,d2
					iocs	_TGUSEMD
					iocs	_OS_CURON	*カーソルＯＮ
					move.w	#16,d1		*768*512モード
					iocs	_CRTMOD
					moveq	#3,d0		*キーバッファ・クリア
					move.b	#%000000,d1
					trap	#15
				");
				wipe();
				TEX_DISP( 1 );
				NNPCMOFF();
				exit( 1 );
			}
			wk[0] = 12;
			wk[1] = 12;
			wk[2] = 12;
			wk[3] = 12;
			wk[exit_flg] = 14;
			bgmes(13,22,wk[0],"START",0);
			bgmes(13,23,wk[1],"SPEED",0);
			bgmes(13,24,wk[2],"OPTION",0);
			bgmes(13,25,wk[3],"MODE",0);
			if ( exit_flg == 0 && (TRIGGER_NML()|SPCSNS()) ){				/*スタート*/
				end_flg = 1;
			}
			b = a;
			if ( !a ){
				if ( STICK_INP_NML(1) > 0 || SNS2() ){
					if ( exit_flg < 3 ) exit_flg++;
					a = 1;
				}
				if ( STICK_INP_NML(1) < 0 || SNS8() ){
					if ( exit_flg > 0 ) exit_flg--;
					a = 1;
				}
				if ( exit_flg == 1 ){											/*スピード選択*/
					if ( STICK_INP_NML(0) > 0 || SNS6() ){
						if ( speed < 10 ) speed++;
						a = 1;
					} else {
						if ( STICK_INP_NML(0) < 0 || SNS4() ){
							if ( speed > 1 ) speed--;
							a = 1;
						}
					}
					rand_num++;
					bgmes(20,23,14,char_num[speed-1],0);
				} else bgmes(20,23,12,char_num[speed-1],0);
				if ( exit_flg == 2 ){											/*オプション選択*/
					if ( STICK_INP_NML(0) > 0 || SNS6() ){
						if ( option_num < 8 ) option_num++;
						a = 1;
					} else {
						if ( STICK_INP_NML(0) < 0 || SNS4() ){
							if ( option_num > 0 ) option_num--;
							a = 1;
						}
					}
					bgmes(20,24,14,char_num[option_num],0);
				} else bgmes(20,24,12,char_num[option_num],0);
				if ( exit_flg == 3 ){											/*モード選択*/
					if ( STICK_INP_NML(0) || SNS6() || SNS4() ){
						special = 1 - special;
						a = 1;
					}
					if ( !special ) bgmes(18,25,14," NOMAL ",0);
						else 		bgmes(18,25,14,"SPECIAL",0);
				} else {
					if ( !special ) bgmes(18,25,12," NOMAL ",0);
						else 		bgmes(18,25,12,"SPECIAL",0);
				}
				if ( HLPSNS() ){
					NNPLAY(se00, 3*256+4, sizeof(se00) );
					muteki = 1 - muteki;
					a = 1;
				}
			} else {
				if ( !HLPSNS() && !STICK_INP_NML(1) && !STICK_INP_NML(0) && !SNS6() && !SNS4() && !SNS8() && !SNS2() ){
					a = 0;
				}
			}
			if ( a != b ) NNPLAY(se03, 3*256+4, sizeof(se03) );
			main_cnt++;
			if ( (main_cnt>>3) > 1024-256 ) main_cnt = 0;
			demo( main_cnt>>3 );
			rand_num += 3;
			tama_p = tama_p++ & 0x1f;
		}
		end_flg = 0;
/*******************************タイトル終わり***********************************************/
		pcm_flg = 0;
		for ( i=0; i<128; i++ ){
			you[i].id = teki_ft[i] = 0;
			you[i].xs = 10;						/*スプライトのキューブサイズ*/
			you[i].ys = 11;
			pl_tbl[i] = 255;
		}
		rand_num += main_cnt;
		main_cnt = 0;
		vpage( 0 );
		for ( i=0; i<16; i++ ) d_pal[i] = star_pal[i];
		if ( !special ){
			EGPUT( 128-40, 128, 128+63-40, 128+255, 0xc00000, bgcube_pat );	/*背景キューブ*/
			home( 0, 88, 128 );
			gx = 88<<2;
		} else {
			home( 0, 128, 128 );
			gx = 128<<2;
		}
		bg_fill(0,0x0127);
		bg_fill(1,0x0127);
		TEX_DISP( 0 );
		SAC_COLOR2( 0, txt_pal );						/* テキストパレット設定		*/
		sp_clear(0,127);
		vpage( 15 );
		mei0 = 20; mei1 = 1; mei2 = 100;
		mei3 = 40; mei4 = 200; mei5 = 500;
		d_pal[6] = d_pal[7] = d_pal[8] = d_pal[9] = d_pal[10] = 0x0000;
		pro_up_down_flg=0;
		pro_up_down_cnt=40;
		p = 0;
		sp_lvl1 = 0;
		stc_pl1 = 100;
		TEXSCROLL( 0, 0 );
		TEX_DISP( 1 );
		teki_num = 1;
		put_star();
		jiki_flg = 0;
		option_cnt = option_chk = 0;
		tama_p = tama_p & 0x1f;
		app_point = rand() % 9;
		randomize( rand_num*tama_p );
		opd1 = opd2 = opd3 = opd4 = 0;
		opd5 = opd6 = opd7 = opd8 = 0;
		switch ( option_num ){
			case 8:
				opd8 = 3;
			case 7:
				opd7 = 3;
			case 6:
				opd6 = 3;
			case 5:
				opd5 = 3;
			case 4:
				opd4 = 3;
			case 3:
				opd3 = 3;
			case 2:
				opd2 = 3;
			case 1:
				opd1 = 3;
		}
/*******************************メインルーチン***********************************************/
		while ( !end_flg ){
			g_scroll0111();
			if ( !special ){							/*ノーマルモード*/
				if ( gx>>2 < 128-14 ){						/*スタート直後のスクロール*/
					gx++;
					home( 0, gx>>2, 128 );
				}
				while ( enemy_tbl[p] == main_cnt ){			/*出現時間とカウンタが同じなら発生*/
					wk0 = rand() % 63;
					again:;
					i = rand()%14;							/*０～１３*/
					if ( you[teki_num-1].y == app_xy[i] ) goto again;
					pp[teki_num] = 0;
					switch ( (teki_ptn[teki_num] = enemy_tbl[ p + 3 ]) ){
					case 0:/* 直進 */
							teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4);
							you[teki_num].x = 272;
							if ( teki_num < 9 ) you[teki_num].y = app_xy[cube_app[app_point][teki_num]];
								else you[teki_num].y = app_xy[i];
							you[teki_num].id = 1;
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = 0;
							teki_wk1[teki_num] = wk0;
						break;
					case 1:/* 前でサーチ */
							teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4);
							you[teki_num].x = 272;
							if ( teki_num < 9 ){
								you[teki_num].y = app_xy[cube_app[app_point][teki_num]];
								teki_wk2[teki_num] = rnd_tbl1[(tama_p++)&15];
							} else {
								you[teki_num].y = app_xy[i];
								teki_wk2[teki_num] = rnd_tbl[tama_p++];
							}
							you[teki_num].id = 1;
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = 0;
							teki_wk1[teki_num] = wk0;
							teki_wk3[teki_num] = 0;
						break;
					case 2:/* 後ろでサーチ */
							teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4);
							you[teki_num].x = 272;
							if ( teki_num < 9 ) you[teki_num].y = app_xy[cube_app[app_point][teki_num]];
								else you[teki_num].y = app_xy[i];
							you[teki_num].id = 1;
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = 0;
							teki_wk1[teki_num] = wk0;
							teki_wk2[teki_num] = rnd_tbl[tama_p++];
							teki_wk3[teki_num] = 0;
						break;
					case 99:/* クリア */
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = 0;
						break;
					}
					teki_num++;
					p += 4;
				}
				teki();
			} else {										/*スペシャルモード*/
				while ( enemy_tbl[p] == main_cnt ){
					wk0 = (rand_num&(main_cnt<<1)) & 63;
					pp[teki_num] = 0;
					teki_wk4[teki_num] = 40;	/*予告時間*/
					switch ( (teki_ptn[teki_num] = enemy_tbl[ p + 3 ]) ){
					case 0:/* 直進 */
							vct[teki_num] = way3[SRCH32( my.x+16, my.y, you[teki_num].x, you[teki_num].y )][rand()%3];
							teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4);
							you[teki_num].x = (rand()%191)+32;
							you[teki_num].y = (rand()%191)+32;
							you[teki_num].id = 0;
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = 0;
							teki_wk1[teki_num] = wk0;
						break;
					case 1:/* 前でサーチ */
					case 2:/* 後ろでサーチ */
							vct[teki_num] = wayrr[SRCH32( my.x+16, my.y, you[teki_num].x, you[teki_num].y )][rand()%3];
							teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4);
							you[teki_num].x = (rand()%191)+32;
							you[teki_num].y = (rand()%191)+32;
							teki_wk2[teki_num] = rnd_tbl[tama_p++]+80;
							you[teki_num].id = 0;
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = 0;
							teki_wk1[teki_num] = wk0;
							teki_wk3[teki_num] = 0;
						break;
					case 99:/* クリア */
							teki_ft[teki_num] = 1;
							teki_wk0[teki_num] = -1;
							pp[teki_num] = 0;
						break;
					}
					teki_num++;
					p += 4;
				}
				teki_special();
			}
			X68ooo();
			if ( tama_p  > 31 ) tama_p  = 0;
			if ( !muteki ){										/*自機判定*/
				you_p = 127;									/*スプライトの判定*/
				if ( ACT2( &my, &you[0], &you_p ) ){
					if ( !jiki_flg ) jiki_flg = 1;
				}
				i = gx>>2;										/* グラフィックの判定 */
				if ( 
VRAMCHK( my.x+i+1, my.y+125, 0xc00000 )|
VRAMCHK( my.x+i  , my.y+125, 0xc00000 )|
VRAMCHK( my.x+i+1, my.y+126, 0xc00000 )|
VRAMCHK( my.x+i  , my.y+126, 0xc00000 ) ){
					if ( !jiki_flg ) jiki_flg = 1;
				}
			}
			if ( ESCSNS() ) end_flg = 1;
			if ( pcm_flg & !NNSTAT() ) pcm_flg = 0;
			main_cnt++;
		}
	}
}
/********************************************************************************************/
void teki()
{
	UBYTE m = 0;
	WORD i, j, n, w;
	while ( m < 128 ){
		if ( m > 127  ){
			printf("添え字範囲オーバー発生 %d\n",main_cnt);
		}
		if ( teki_ft[m] ){
			switch ( teki_ptn[m] ){
			case 0:							/*直進*/
				if ( !teki_wk0[m] ){
					you[m].x-=2;
					i = teki_wk1[m]>>3;
					SP_APS(teki_pl[m],you[m].x,you[m].y,cube_ptn[i][0],3);
					w = teki_pl[m];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y,cube_ptn[i][1],3);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x,you[m].y+16,cube_ptn[i][2],3);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y+16,cube_ptn[i][3],3);
					teki_wk1[m]++;
					if ( teki_wk1[m] > 63 ) teki_wk1[m] = 0;
					if ( you[m].y < 8 || you[m].y > 248-8 ){
						teki_wk0[m] = 1;
					}
					if ( you[m].x < -48 || you[m].x > 300 || you[m].y < -16 || you[m].y > 272 ){
						pfree( &stc_pl1, teki_pl[m] );
						teki_ft[m]=you[m].id=0;
					}
					if ( VRAMCHK( you[m].x+128-1-14, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128-1-14, you[m].y+128+1, 0xc00000 )|VRAMCHK( you[m].x+128+1-14, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128+1-14, you[m].y+128+1, 0xc00000 ) ){
						teki_wk0[m] = 1;
					}
				} else {
					m_play(1,2,3,4,5,NL,NL,NL);
					EGPUT( you[m].x-16+128-14, you[m].y-16+128, you[m].x+15+128-14, you[m].y+15+128, 0xc00000, &block[teki_wk1[m]>>3][0] );
					pfree( &stc_pl1, teki_pl[m] );
					teki_ft[m]=0;
					you[m].id=0;
				}
				break;
			case 1:							/*前でサーチ*/
				if ( !teki_wk0[m] ){
					if ( !teki_wk3[m] ){
						you[m].x-=2;
						if ( you[m].x - 96 + teki_wk2[m] < my.x ){
							teki_wk3[m] = 1;
							if ( m < 13 ){
								if ( m < 3 ){
									/*vct[m] = wayr[SRCH32( my.x, my.y, you[m].x, you[m].y )][rand()%3];*/
									vct[m] = SRCH32( my.x+32, my.y, you[m].x, you[m].y );
								} else {
									vct[m] = SRCH32( my.x+32, my.y, you[m].x, you[m].y );
								}
							} else {
								if ( main_cnt | 3 ){
									vct[m] = SRCH32( my.x+20, my.y, you[m].x, you[m].y );
								} else {
									vct[m] = way3[SRCH32( my.x+20, my.y, you[m].x, you[m].y )][rand()%3];
								}
							}
						}
					} else {
						you[m].x += x_buffE[vct[m]][pp[m]];
						you[m].y += y_buffE[vct[m]][pp[m]++];
					}
					i = teki_wk1[m]>>3;
					SP_APS(teki_pl[m],you[m].x,you[m].y,cube_ptn[i][0],3);
					w = teki_pl[m];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y,cube_ptn[i][1],3);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x,you[m].y+16,cube_ptn[i][2],3);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y+16,cube_ptn[i][3],3);
					teki_wk1[m]++;
					if ( teki_wk1[m] > 63 ) teki_wk1[m] = 0;
					if ( you[m].y < 8 || you[m].y > 248-8 ){
						teki_wk0[m] = 1;
					}
					if ( you[m].x < -48 || you[m].x > 300 || you[m].y < -16 || you[m].y > 272 ){
						pfree( &stc_pl1, teki_pl[m] );
						teki_ft[m]=you[m].id=0;
					}
					if ( VRAMCHK( you[m].x+128-1-14, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128-1-14, you[m].y+128+1, 0xc00000 )|VRAMCHK( you[m].x+128+1-14, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128+1-14, you[m].y+128+1, 0xc00000 ) ){
						teki_wk0[m] = 1;
					}
				} else {
					m_play(1,2,3,4,5,NL,NL,NL);
					EGPUT( you[m].x-16+128-14, you[m].y-16+128, you[m].x+15+128-14, you[m].y+15+128, 0xc00000, &block[teki_wk1[m]>>3][0] );
					pfree( &stc_pl1, teki_pl[m] );
					teki_ft[m]=0;
					you[m].id=0;
				}
				break;
			case 2:							/*後ろでサーチ*/
				if ( !teki_wk0[m] ){
					if ( !teki_wk3[m] ){
						you[m].x-=2;
						if ( you[m].x + 48 + teki_wk2[m] < my.x ){
							teki_wk3[m] = 1;
							vct[m] = SRCH32( my.x, my.y, you[m].x, you[m].y );
						}
					} else {
						you[m].x += x_buffE[vct[m]][pp[m]];
						you[m].y += y_buffE[vct[m]][pp[m]++];
					}
					i = teki_wk1[m]>>3;
					SP_APS(teki_pl[m],you[m].x,you[m].y,cube_ptn[i][0],3);
					w = teki_pl[m];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y,cube_ptn[i][1],3);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x,you[m].y+16,cube_ptn[i][2],3);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y+16,cube_ptn[i][3],3);
					teki_wk1[m]++;
					if ( teki_wk1[m] > 63 ) teki_wk1[m] = 0;
					if ( you[m].y < 8 || you[m].y > 248-8 ){
						teki_wk0[m] = 1;
					}
					if ( you[m].x < -48 || you[m].x > 300 || you[m].y < -16 || you[m].y > 272 ){
						pfree( &stc_pl1, teki_pl[m] );
						teki_ft[m]=you[m].id=0;
					}
					if ( VRAMCHK( you[m].x+128-1-14, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128-1-14, you[m].y+128+1, 0xc00000 )|VRAMCHK( you[m].x+128+1-14, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128+1-14, you[m].y+128+1, 0xc00000 ) ){
						teki_wk0[m] = 1;
					}
				} else {
					m_play(1,2,3,4,5,NL,NL,NL);
					EGPUT( you[m].x-16+128-14, you[m].y-16+128, you[m].x+15+128-14, you[m].y+15+128, 0xc00000, &block[teki_wk1[m]>>3][0] );
					pfree( &stc_pl1, teki_pl[m] );
					teki_ft[m]=0;
					you[m].id=0;
				}
				break;
			case 99:						/* クリア */
				switch ( teki_wk0[m] ){
					case 0:
						if ( gx>>2 < 128+14-14 ){
							gx += main_cnt&1;
							home( 0, gx>>2, 128 );
						} else {
							teki_wk0[m] = 1;
							pp[m] = 0;
						}
						break;
					case 1:
						if ( pp[m]++ > 30 ) {
							teki_wk0[m] = 2;
							pp[m]=0;
						}
						break;
					case 2:
						dotclr( pp[m]++,pri,0xC00000 );
						/*dotclr( pp[m]++,pri,0xC00000 );*/
						if ( pp[m] > 63 ){
							for ( i=0; i<128; i++ ) you[i].id = 0;
							teki_wk0[m] = 3;
							pp[m] = 0;
						}
						break;
					case 3:
						if ( pp[m]++ > 128 ){
							NNPLAY(se01, 3*256+4, sizeof(se01) );
							end_flg = 1;
							bg_set(1,1,0);
							sp_clear(0,127);
							bg_fill(0,0x0127);
							bg_scroll(0,0,0);
							GTSPRW( 0x12 );					/* 優先度設定 TX > SP > GR 	*/
							bgmes(8,14,11,"CONGRATULATIONS",0);
							bgmes(3,16,11,"GO TO THE AMUSEMENT CENTER",0);
							while ( !TRIGGER_NML() && !ESCSNS() );
							GTSPRW( 0x21 );					/* 優先度設定 TX > GR > SP 	*/
						}
						break;
				}
				break;
			}
		}
		m++;
	}
}
/***********************************スペシャルモード*****************************************/
void teki_special()
{
	UBYTE m = 0;
	WORD i, j, n, w;
	while ( m < 128 ){
		if ( m > 127  ){
			printf("添え字範囲オーバー発生 %d\n",main_cnt);
		}
		if ( teki_ft[m] ){
			switch ( teki_ptn[m] ){
			case 0:							/*直進*/
				if ( !teki_wk0[m] ){
					if ( teki_wk4[m]-- < 0 ){
						you[m].x += x_buffB[vct[m]][pp[m]];
						you[m].y += y_buffB[vct[m]][pp[m]++];
						j = 3;
						you[m].id = 1;
						if ( VRAMCHK( you[m].x+128-2, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128-2, you[m].y+128+2, 0xc00000 )|VRAMCHK( you[m].x+128+2, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128+2, you[m].y+128+2, 0xc00000 ) ){
							teki_wk0[m] = 1;
						}
					} else {
						j = (main_cnt&1) * 3;
					}
					i = teki_wk1[m]>>3;
					SP_APS(teki_pl[m],you[m].x,you[m].y,cube_ptn[i][0],j);
					w = teki_pl[m];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y,cube_ptn[i][1],j);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x,you[m].y+16,cube_ptn[i][2],j);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y+16,cube_ptn[i][3],j);
					teki_wk1[m]++;
					if ( teki_wk1[m] > 63 ) teki_wk1[m] = 0;
					if ( you[m].y < 8 || you[m].y > 256-8 || you[m].x < 8 || you[m].x > 256-8 ){
						teki_wk0[m] = 1;
					}
				} else {
					m_play(1,2,3,4,5,NL,NL,NL);
					EGPUT( you[m].x-16+128, you[m].y-16+128, you[m].x+15+128, you[m].y+15+128, 0xc00000, &block[teki_wk1[m]>>3][0] );
					pfree( &stc_pl1, teki_pl[m] );
					teki_ft[m]=you[m].id=0;
				}
				break;
			case 1:				/*サーチ*/
			case 2:
				if ( !teki_wk0[m] ){
					if ( teki_wk4[m]-- < 0 ){
						j = 3;
						you[m].id = 1;
						if ( !teki_wk3[m] ){	/*サーチしていない*/
							you[m].x += x_buffB[vct[m]][pp[m]];
							you[m].y += y_buffB[vct[m]][pp[m]++];
							if ( !teki_wk2[m]-- ){
								teki_wk3[m] = 1;
								vct[m] = wayr[SRCH32( my.x, my.y, you[m].x, you[m].y )][rand()%3];
								pp[m] = 0;
							}
						} else {
							you[m].x += x_buffE[vct[m]][pp[m]];
							you[m].y += y_buffE[vct[m]][pp[m]++];
						}
						i = teki_wk1[m]>>3;
						if ( VRAMCHK( you[m].x+128-2, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128-2, you[m].y+128+2, 0xc00000 )|VRAMCHK( you[m].x+128+2, you[m].y+128-2, 0xc00000 )|VRAMCHK( you[m].x+128+2, you[m].y+128+2, 0xc00000 ) ){
							teki_wk0[m] = 1;
						}
					} else {
						j = (main_cnt&1) * 3;
					}
					i = teki_wk1[m]>>3;
					SP_APS(teki_pl[m],you[m].x,you[m].y,cube_ptn[i][0],j);
					w = teki_pl[m];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y,cube_ptn[i][1],j);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x,you[m].y+16,cube_ptn[i][2],j);
					w = pl_tbl[w];
					SP_APS(pl_tbl[w],you[m].x+16,you[m].y+16,cube_ptn[i][3],j);
					teki_wk1[m]++;
					if ( teki_wk1[m] > 63 ) teki_wk1[m] = 0;
					if ( you[m].y < 8 || you[m].y > 256-8 || you[m].x < 8 || you[m].x > 256-8 ){
						teki_wk0[m] = 1;
					}
				} else {
					m_play(1,2,3,4,5,NL,NL,NL);
					EGPUT( you[m].x-16+128, you[m].y-16+128, you[m].x+15+128, you[m].y+15+128, 0xc00000, &block[teki_wk1[m]>>3][0] );
					pfree( &stc_pl1, teki_pl[m] );
					teki_ft[m]=you[m].id=0;
				}
				break;
			case 99:						/* クリア */
				switch ( teki_wk0[m] ){
					case -1:
						if ( !NNSTAT() ){
							NNPLAY(se02, 3*256+4, sizeof(se02) );
							pp[m]++;
						}
						if ( pp[m] > 3 ){
							if ( pp[m]++ > 256 ){
								teki_wk0[m] = 0;
							}
						}
						break;
					case 0:
						if ( gx>>2 < 128+16 ){
							gx += main_cnt&1;
							home( 0, gx>>2, 128 );
						} else {
							teki_wk0[m] = 1;
						}
						break;
					case 1:
						if ( gx>>2 > 128-32 ){
							gx -= main_cnt&1;
							home( 0, gx>>2, 128 );
						} else {
							teki_wk0[m] = 2;
							pp[m] = 0;
						}
						break;
					case 2:
						if ( pp[m]++ > 20 ) {
							teki_wk0[m] = 3;
							pp[m]=0;
						}
						break;
					case 3:
						dotclr( pp[m]++,pri0,0xC00000 );
						if ( pp[m] > 63 ){
							for ( i=0; i<128; i++ ) you[i].id = 0;
							teki_wk0[m] = 4;
							pp[m] = 0;
						}
						break;
					case 4:
						if ( pp[m]++ > 128 ){
							NNPLAY(se01, 3*256+4, sizeof(se01) );
							end_flg = 1;
							bg_set(1,1,0);
							sp_clear(0,127);
							bg_fill(0,0x0127);
							bg_scroll(0,0,0);
							GTSPRW( 0x12 );					/* 優先度設定 TX > SP > GR 	*/
							bgmes(8,13,11,"CONGRATULATIONS",0);
							bgmes(5,15,11,"THANK YOU FOR PLAYING",0);
							bgmes(10,17,11,"SEE YOU NEXT",0);
							while ( !TRIGGER_NML() && !ESCSNS() );
							GTSPRW( 0x21 );					/* 優先度設定 TX > GR > SP 	*/
						}
						break;
				}
				break;
			}
		}
		m++;
	}
}

/***********************************自機移動*************************************************
	自機		２		102,103
	オプション	４		104,107
	ショット	１０	108,117
	ミサイル	１０	118,127
*********************************************************************************************/
void X68ooo()
{
	int i,j,r;

	if ( !jiki_flg ){
		stick_ptn0 = STICK_INP_NML(0);
		if ( SNS6() ) stick_ptn0 = 1;
		if ( SNS4() ) stick_ptn0 = -1;
		stick_ptn1 = STICK_INP_NML(1);
		if ( SNS2() ) stick_ptn1 = 1;
		if ( SNS8() ) stick_ptn1 = -1;
		i = speed * 15;
		jiki_xx += i*stick_ptn0;		/*遊戯棒より入力*/
		jiki_yy += i*stick_ptn1;
		pro_up_down_flg = STICK_INP(1);
		option_chk = 0;
		if ( jiki_xx < 192 ){  jiki_xx += i;option_chk = 1;}		/*  12  x 16 */
		if ( jiki_xx > 3744 ){ jiki_xx -= i;option_chk = 1;}		/*  234 x 16 */
		if ( jiki_yy < 320 ){  jiki_yy += i;option_chk = 2;}		/*  20  x 16 */
		if ( jiki_yy > 3856 ){ jiki_yy -= i;option_chk = 2;}		/*  241 x 16 */
		if ( option_chk == 2 && jiki_xx != jiki_wx ){
			j = i>>1;
			if ( jiki_xx > jiki_wx ){
				jiki_xx -= j;
			} else {
				jiki_xx += j;
			}
			if ( jiki_xx < 192 )  jiki_xx += j;
			if ( jiki_xx > 3744 ) jiki_xx -= j;
		}
		if ( option_chk == 1 && jiki_yy != jiki_wy ){
			j = i>>1;
			if ( jiki_yy > jiki_wy ){
				jiki_yy -= j;
			} else {
				jiki_yy += j;
			}
			if ( jiki_yy < 256 )  jiki_yy += j;
			if ( jiki_yy > 3856 ) jiki_yy -= j;
		}
		my.x = jiki_xx >> 4;
		my.y = jiki_yy >> 4;
		if ( pro_up_down_flg ){
			pro_up_down_cnt += pro_up_down_flg;
		} else {
			if ( pro_up_down_cnt > 40 ){
				pro_up_down_cnt--;
			} else {
				if ( pro_up_down_cnt < 40 ) pro_up_down_cnt++;
			}
		}
		if ( pro_up_down_cnt > 79 ){
			pro_up_down_cnt = 79;
		} else {
			if ( pro_up_down_cnt < 0 ) pro_up_down_cnt = 0;
		}
		r = pro_up_down_cnt >> 4;				/*1001111*/
		if ( main_cnt & 2 ){
			SP_APSV( 102, my.x,   my.y+8, jiki_pro_ptn[r][0], 3 );
			SP_APS(  103, my.x+16,my.y+8, jiki_pro_ptn[r][1], 3 );
		} else {
			SP_APSV( 102, my.x,   my.y+8, jiki_pro_ptn[r][0]+0x0100, 3 );
			SP_APS(  103, my.x+16,my.y+8, jiki_pro_ptn[r][1], 3 );
		}
		if ( my.x != option0_wx[0] || my.y != option0_wy[0] || option_chk ){
			option0_wx[15]=option0_wx[14];
			option0_wy[15]=option0_wy[14];
			option0_wx[14]=option0_wx[13];
			option0_wy[14]=option0_wy[13];
			option0_wx[13]=option0_wx[12];
			option0_wy[13]=option0_wy[12];
			option0_wx[12]=option0_wx[11];
			option0_wy[12]=option0_wy[11];
			option0_wx[11]=option0_wx[10];
			option0_wy[11]=option0_wy[10];
			option0_wx[10]=option0_wx[ 9];
			option0_wy[10]=option0_wy[ 9];
			option0_wx[ 9]=option0_wx[ 8];
			option0_wy[ 9]=option0_wy[ 8];
			option0_wx[ 8]=option0_wx[ 7];
			option0_wy[ 8]=option0_wy[ 7];
			option0_wx[ 7]=option0_wx[ 6];
			option0_wy[ 7]=option0_wy[ 6];
			option0_wx[ 6]=option0_wx[ 5];
			option0_wy[ 6]=option0_wy[ 5];
			option0_wx[ 5]=option0_wx[ 4];
			option0_wy[ 5]=option0_wy[ 4];
			option0_wx[ 4]=option0_wx[ 3];
			option0_wy[ 4]=option0_wy[ 3];
			option0_wx[ 3]=option0_wx[ 2];
			option0_wy[ 3]=option0_wy[ 2];
			option0_wx[ 2]=option0_wx[ 1];
			option0_wy[ 2]=option0_wy[ 1];
			option0_wx[ 1]=option0_wx[ 0];
			option0_wy[ 1]=option0_wy[ 0];
			option0_wx[ 0]=my.x;
			option0_wy[ 0]=my.y;
		}
		if ( option0_wx[15] != option1_wx[0] || option0_wy[15] != option1_wy[0] || option_chk ){
			option1_wx[15]=option1_wx[14];
			option1_wy[15]=option1_wy[14];
			option1_wx[14]=option1_wx[13];
			option1_wy[14]=option1_wy[13];
			option1_wx[13]=option1_wx[12];
			option1_wy[13]=option1_wy[12];
			option1_wx[12]=option1_wx[11];
			option1_wy[12]=option1_wy[11];
			option1_wx[11]=option1_wx[10];
			option1_wy[11]=option1_wy[10];
			option1_wx[10]=option1_wx[ 9];
			option1_wy[10]=option1_wy[ 9];
			option1_wx[ 9]=option1_wx[ 8];
			option1_wy[ 9]=option1_wy[ 8];
			option1_wx[ 8]=option1_wx[ 7];
			option1_wy[ 8]=option1_wy[ 7];
			option1_wx[ 7]=option1_wx[ 6];
			option1_wy[ 7]=option1_wy[ 6];
			option1_wx[ 6]=option1_wx[ 5];
			option1_wy[ 6]=option1_wy[ 5];
			option1_wx[ 5]=option1_wx[ 4];
			option1_wy[ 5]=option1_wy[ 4];
			option1_wx[ 4]=option1_wx[ 3];
			option1_wy[ 4]=option1_wy[ 3];
			option1_wx[ 3]=option1_wx[ 2];
			option1_wy[ 3]=option1_wy[ 2];
			option1_wx[ 2]=option1_wx[ 1];
			option1_wy[ 2]=option1_wy[ 1];
			option1_wx[ 1]=option1_wx[ 0];
			option1_wy[ 1]=option1_wy[ 0];
			option1_wx[ 0]=option0_wx[15];
			option1_wy[ 0]=option0_wy[15];
		}
		if ( option1_wx[15] != option2_wx[0] || option1_wy[15] != option2_wy[0] || option_chk ){
			option2_wx[15]=option2_wx[14];
			option2_wy[15]=option2_wy[14];
			option2_wx[14]=option2_wx[13];
			option2_wy[14]=option2_wy[13];
			option2_wx[13]=option2_wx[12];
			option2_wy[13]=option2_wy[12];
			option2_wx[12]=option2_wx[11];
			option2_wy[12]=option2_wy[11];
			option2_wx[11]=option2_wx[10];
			option2_wy[11]=option2_wy[10];
			option2_wx[10]=option2_wx[ 9];
			option2_wy[10]=option2_wy[ 9];
			option2_wx[ 9]=option2_wx[ 8];
			option2_wy[ 9]=option2_wy[ 8];
			option2_wx[ 8]=option2_wx[ 7];
			option2_wy[ 8]=option2_wy[ 7];
			option2_wx[ 7]=option2_wx[ 6];
			option2_wy[ 7]=option2_wy[ 6];
			option2_wx[ 6]=option2_wx[ 5];
			option2_wy[ 6]=option2_wy[ 5];
			option2_wx[ 5]=option2_wx[ 4];
			option2_wy[ 5]=option2_wy[ 4];
			option2_wx[ 4]=option2_wx[ 3];
			option2_wy[ 4]=option2_wy[ 3];
			option2_wx[ 3]=option2_wx[ 2];
			option2_wy[ 3]=option2_wy[ 2];
			option2_wx[ 2]=option2_wx[ 1];
			option2_wy[ 2]=option2_wy[ 1];
			option2_wx[ 1]=option2_wx[ 0];
			option2_wy[ 1]=option2_wy[ 0];
			option2_wx[ 0]=option1_wx[15];
			option2_wy[ 0]=option1_wy[15];
		}
		if ( option2_wx[15] != option3_wx[0] || option2_wy[15] != option3_wy[0] || option_chk ){
			option3_wx[15]=option3_wx[14];
			option3_wy[15]=option3_wy[14];
			option3_wx[14]=option3_wx[13];
			option3_wy[14]=option3_wy[13];
			option3_wx[13]=option3_wx[12];
			option3_wy[13]=option3_wy[12];
			option3_wx[12]=option3_wx[11];
			option3_wy[12]=option3_wy[11];
			option3_wx[11]=option3_wx[10];
			option3_wy[11]=option3_wy[10];
			option3_wx[10]=option3_wx[ 9];
			option3_wy[10]=option3_wy[ 9];
			option3_wx[ 9]=option3_wx[ 8];
			option3_wy[ 9]=option3_wy[ 8];
			option3_wx[ 8]=option3_wx[ 7];
			option3_wy[ 8]=option3_wy[ 7];
			option3_wx[ 7]=option3_wx[ 6];
			option3_wy[ 7]=option3_wy[ 6];
			option3_wx[ 6]=option3_wx[ 5];
			option3_wy[ 6]=option3_wy[ 5];
			option3_wx[ 5]=option3_wx[ 4];
			option3_wy[ 5]=option3_wy[ 4];
			option3_wx[ 4]=option3_wx[ 3];
			option3_wy[ 4]=option3_wy[ 3];
			option3_wx[ 3]=option3_wx[ 2];
			option3_wy[ 3]=option3_wy[ 2];
			option3_wx[ 2]=option3_wx[ 1];
			option3_wy[ 2]=option3_wy[ 1];
			option3_wx[ 1]=option3_wx[ 0];
			option3_wy[ 1]=option3_wy[ 0];
			option3_wx[ 0]=option2_wx[15];
			option3_wy[ 0]=option2_wy[15];
		}

		if ( option3_wx[15] != option4_wx[0] || option3_wy[15] != option4_wy[0] || option_chk ){
			option4_wx[15]=option4_wx[14];
			option4_wy[15]=option4_wy[14];
			option4_wx[14]=option4_wx[13];
			option4_wy[14]=option4_wy[13];
			option4_wx[13]=option4_wx[12];
			option4_wy[13]=option4_wy[12];
			option4_wx[12]=option4_wx[11];
			option4_wy[12]=option4_wy[11];
			option4_wx[11]=option4_wx[10];
			option4_wy[11]=option4_wy[10];
			option4_wx[10]=option4_wx[ 9];
			option4_wy[10]=option4_wy[ 9];
			option4_wx[ 9]=option4_wx[ 8];
			option4_wy[ 9]=option4_wy[ 8];
			option4_wx[ 8]=option4_wx[ 7];
			option4_wy[ 8]=option4_wy[ 7];
			option4_wx[ 7]=option4_wx[ 6];
			option4_wy[ 7]=option4_wy[ 6];
			option4_wx[ 6]=option4_wx[ 5];
			option4_wy[ 6]=option4_wy[ 5];
			option4_wx[ 5]=option4_wx[ 4];
			option4_wy[ 5]=option4_wy[ 4];
			option4_wx[ 4]=option4_wx[ 3];
			option4_wy[ 4]=option4_wy[ 3];
			option4_wx[ 3]=option4_wx[ 2];
			option4_wy[ 3]=option4_wy[ 2];
			option4_wx[ 2]=option4_wx[ 1];
			option4_wy[ 2]=option4_wy[ 1];
			option4_wx[ 1]=option4_wx[ 0];
			option4_wy[ 1]=option4_wy[ 0];
			option4_wx[ 0]=option3_wx[15];
			option4_wy[ 0]=option3_wy[15];
		}
		if ( option4_wx[15] != option5_wx[0] || option4_wy[15] != option5_wy[0] || option_chk ){
			option5_wx[15]=option5_wx[14];
			option5_wy[15]=option5_wy[14];
			option5_wx[14]=option5_wx[13];
			option5_wy[14]=option5_wy[13];
			option5_wx[13]=option5_wx[12];
			option5_wy[13]=option5_wy[12];
			option5_wx[12]=option5_wx[11];
			option5_wy[12]=option5_wy[11];
			option5_wx[11]=option5_wx[10];
			option5_wy[11]=option5_wy[10];
			option5_wx[10]=option5_wx[ 9];
			option5_wy[10]=option5_wy[ 9];
			option5_wx[ 9]=option5_wx[ 8];
			option5_wy[ 9]=option5_wy[ 8];
			option5_wx[ 8]=option5_wx[ 7];
			option5_wy[ 8]=option5_wy[ 7];
			option5_wx[ 7]=option5_wx[ 6];
			option5_wy[ 7]=option5_wy[ 6];
			option5_wx[ 6]=option5_wx[ 5];
			option5_wy[ 6]=option5_wy[ 5];
			option5_wx[ 5]=option5_wx[ 4];
			option5_wy[ 5]=option5_wy[ 4];
			option5_wx[ 4]=option5_wx[ 3];
			option5_wy[ 4]=option5_wy[ 3];
			option5_wx[ 3]=option5_wx[ 2];
			option5_wy[ 3]=option5_wy[ 2];
			option5_wx[ 2]=option5_wx[ 1];
			option5_wy[ 2]=option5_wy[ 1];
			option5_wx[ 1]=option5_wx[ 0];
			option5_wy[ 1]=option5_wy[ 0];
			option5_wx[ 0]=option4_wx[15];
			option5_wy[ 0]=option4_wy[15];
		}
		if ( option5_wx[15] != option6_wx[0] || option5_wy[15] != option6_wy[0] || option_chk ){
			option6_wx[15]=option6_wx[14];
			option6_wy[15]=option6_wy[14];
			option6_wx[14]=option6_wx[13];
			option6_wy[14]=option6_wy[13];
			option6_wx[13]=option6_wx[12];
			option6_wy[13]=option6_wy[12];
			option6_wx[12]=option6_wx[11];
			option6_wy[12]=option6_wy[11];
			option6_wx[11]=option6_wx[10];
			option6_wy[11]=option6_wy[10];
			option6_wx[10]=option6_wx[ 9];
			option6_wy[10]=option6_wy[ 9];
			option6_wx[ 9]=option6_wx[ 8];
			option6_wy[ 9]=option6_wy[ 8];
			option6_wx[ 8]=option6_wx[ 7];
			option6_wy[ 8]=option6_wy[ 7];
			option6_wx[ 7]=option6_wx[ 6];
			option6_wy[ 7]=option6_wy[ 6];
			option6_wx[ 6]=option6_wx[ 5];
			option6_wy[ 6]=option6_wy[ 5];
			option6_wx[ 5]=option6_wx[ 4];
			option6_wy[ 5]=option6_wy[ 4];
			option6_wx[ 4]=option6_wx[ 3];
			option6_wy[ 4]=option6_wy[ 3];
			option6_wx[ 3]=option6_wx[ 2];
			option6_wy[ 3]=option6_wy[ 2];
			option6_wx[ 2]=option6_wx[ 1];
			option6_wy[ 2]=option6_wy[ 1];
			option6_wx[ 1]=option6_wx[ 0];
			option6_wy[ 1]=option6_wy[ 0];
			option6_wx[ 0]=option5_wx[15];
			option6_wy[ 0]=option5_wy[15];
		}
		if ( option6_wx[15] != option7_wx[0] || option6_wy[15] != option7_wy[0] || option_chk ){
			option7_wx[15]=option7_wx[14];
			option7_wy[15]=option7_wy[14];
			option7_wx[14]=option7_wx[13];
			option7_wy[14]=option7_wy[13];
			option7_wx[13]=option7_wx[12];
			option7_wy[13]=option7_wy[12];
			option7_wx[12]=option7_wx[11];
			option7_wy[12]=option7_wy[11];
			option7_wx[11]=option7_wx[10];
			option7_wy[11]=option7_wy[10];
			option7_wx[10]=option7_wx[ 9];
			option7_wy[10]=option7_wy[ 9];
			option7_wx[ 9]=option7_wx[ 8];
			option7_wy[ 9]=option7_wy[ 8];
			option7_wx[ 8]=option7_wx[ 7];
			option7_wy[ 8]=option7_wy[ 7];
			option7_wx[ 7]=option7_wx[ 6];
			option7_wy[ 7]=option7_wy[ 6];
			option7_wx[ 6]=option7_wx[ 5];
			option7_wy[ 6]=option7_wy[ 5];
			option7_wx[ 5]=option7_wx[ 4];
			option7_wy[ 5]=option7_wy[ 4];
			option7_wx[ 4]=option7_wx[ 3];
			option7_wy[ 4]=option7_wy[ 3];
			option7_wx[ 3]=option7_wx[ 2];
			option7_wy[ 3]=option7_wy[ 2];
			option7_wx[ 2]=option7_wx[ 1];
			option7_wy[ 2]=option7_wy[ 1];
			option7_wx[ 1]=option7_wx[ 0];
			option7_wy[ 1]=option7_wy[ 0];
			option7_wx[ 0]=option6_wx[15];
			option7_wy[ 0]=option6_wy[15];
		}
		i = option_ptn[option_cnt>>2];
		SP_APS(104,option0_wx[15]+8,option0_wy[15]+8,i,opd1);
		SP_APS(105,option1_wx[15]+8,option1_wy[15]+8,i,opd2);
		SP_APS(106,option2_wx[15]+8,option2_wy[15]+8,i,opd3);
		SP_APS(107,option3_wx[15]+8,option3_wy[15]+8,i,opd4);
		SP_APS(108,option4_wx[15]+8,option4_wy[15]+8,i,opd5);
		SP_APS(109,option5_wx[15]+8,option5_wy[15]+8,i,opd6);
		SP_APS(110,option6_wx[15]+8,option6_wy[15]+8,i,opd7);
		SP_APS(111,option7_wx[15]+8,option7_wy[15]+8,i,opd8);
		option_cnt++;
		if ( option_cnt>>2 > 3 ) option_cnt = 0;
		jiki_wx = jiki_xx;
		jiki_wy = jiki_yy;
	} else {																/*ミスった処理*/
		NNPLAY(se00, 3*256+4, sizeof(se00) );
		while ( jiki_flg>>6 < 5 ){
			SP_APSV( 102, my.x,   my.y+8, bang_ptn[jiki_flg>>6], 3 );
			SP_APS(  103, my.x+16,my.y+8, bang_ptn[jiki_flg>>6]|0x4000, 3 );
			jiki_flg++;
		}
		end_flg = 1;
		i = 30000*12;
		while ( i-- );
	}
}
/***********************************スプライト消去*******************************************/
void sp_clear( int a, int b )
{
	int i;

	SP_APSV( 0, 511, 511, 256, 0);
	for ( i=a; i<b+1; i++ ){
		SP_APS( i, 511, 511, 256, 0 );
	}
	SP_APSV( 0, 511, 511, 256, 0);
}
/***********************************ＢＧメッセージ表示関数***********************************/
void bgmes( UBYTE x, UBYTE y, UWORD col, char *mes, int pl )
{
	col <<= 8;
	while ( *mes != (char)NULL ){
		if ( *mes == ' ' ) bg_put(0,x,y,0x0127);
		else bg_put(pl,x,y,bgmes0[(*mes-0x30)]|col);
		mes++;
		x++;
	}
}
/********************************************************************************************/
void spp_load( char *name )
{
	FILE *f;
	UBYTE dummy[128],pat[256];
	WORD i,j,cnt;
	if ( (f = fopen( name, "rb" )) == (FILE*)NULL ){
		printf("%s がありません.\n", name );
		exit( 1 );
	} else {
		for( i = 0; i < 128; i++ ){
			cnt = 0;
			fread( dummy, 1, 128, f );
			for ( j = 0; j < 128; j++ ){
				pat[cnt]   = (dummy[j]>>4)&0x0f;
				pat[cnt+1] = dummy[j]&0x0f;
				cnt += 2;
			}
			sp_def( i, pat, 1 );
		}
		fclose( f );
	}
}

/********************************************************************************************/
void spl_load( char *name )
{
	FILE *f;
	WORD i,j;
	UWORD pal[16][16];

	if ( (f = fopen( name, "rb" )) == (FILE*)NULL ){
		printf("%s がありません.\n", name );
		exit( 1 );
	} else {
		for( i = 1; i < 16; i++ ){
			for( j = 0; j < 16; j++ ){
				fread( &pal[i][j], 1, 2, f );
				sp_color( j, pal[i][j], i );
			}
		}
		fclose( f );
	}
}
/********************************************************************************************/
void direct_load( char *name, char *xbuff, char *ybuff, WORD byt )
{
	FILE *fp;
	int i;

	if ( !((fp = fopen( name, "rb" )) == (FILE*)NULL) ){
		for ( i = 0; i < 32; i++ ){
			fread( xbuff, byt, 1, fp );
			fread( ybuff, byt, 1, fp );
			xbuff+=byt;
			ybuff+=byt;
		}
		fclose( fp );
	} else {
		printf("%s がありません\n",name);
		exit( 1 );
	}
}
/********************************************************************************************/
UBYTE pcm_load( char *filename, char *pcmname, UWORD pcmlen )
{
	FILE *fp;

	if ( !((fp = fopen( filename, "rb" )) == (FILE*)NULL) ){
		fread( pcmname, pcmlen, 1, fp );
		fclose( fp );
		printf("*");
		return( 1 );
	} else {
		printf( "'%s' がありません。\n", filename );
		return( 0 );
	}
}
/********************************************************************************************/
asm("
	.globl	___mulsi3
	.globl	___umulsi3
	.text
	.even
___mulsi3
___umulsi3
	movem.l	4(sp),d1
	move.l	d1,d0
	swap	d1
	or.w	8(sp),d1
	bne	_mult
	mulu	10(sp),d0
	rts
_mult
	move.l	8(sp),d1
	move.l	d3,a0
	move.l	d0,d2
	mulu.w	d1,d0		d0.low * d1.low
	move.l	d2,d3
	swap	d3
	mulu.w	d1,d3		d0.hi  * d1.low
	swap	d0
	add.w	d3,d0
	swap	d1
	mulu.w	d2,d1		d0.low * d1.hi
	add.w	d1,d0
	swap	d0
	move.l	a0,d3
	rts

	.globl _ESCSNS
	.globl _SPCSNS
	.globl _OP1SNS
	.globl _SNS4
	.globl _SNS6
	.globl _SNS8
	.globl _SNS2
	.text
	.even
********************************************
*  ＥＳＣキーが押されていれば２を返し
*  押されていなければゼロを返す。

_ESCSNS
	movem.l	d1,-(sp)
	move.w	#0,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%00000010,d0
	movem.l	(sp)+,d1
	rts

********************************************
*  スペースキーが押されていればを32を返し
*  押されていなければゼロを返す。

_SPCSNS
	movem.l	d1,-(sp)
	move.w	#6,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%0010_0000,d0
	movem.l	(sp)+,d1
	rts

********************************************
*  OPT1キーが押されていればを４を返し
*  押されていなければゼロを返す。

_OP1SNS
	movem.l	d1,-(sp)
	move.w	#$e,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%00000100,d0
	movem.l	(sp)+,d1
	rts
********************************************
_HLPSNS
	movem.l	d1,-(sp)
	move.w	#$a,d1
	moveq.l	#$4,d0
	trap	#15
	andi.b	#%00010000,d0
	movem.l	(sp)+,d1
	rts
_SNSS
	movem.l	d1,-(sp)
	move.w	#$3,d1
	moveq.l	#$4,d0
	trap	#15
	andi.b	#%10000000,d0
	movem.l	(sp)+,d1
	rts
_SNS4
	movem.l	d1,-(sp)
	move.w	#$8,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%1000_0000,d0
	movem.l	(sp)+,d1
	rts
_SNS6
	movem.l	d1,-(sp)
	move.w	#$9,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%0000_0010,d0
	movem.l	(sp)+,d1
	rts
_SNS8
	movem.l	d1,-(sp)
	move.w	#$8,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%0001_0000,d0
	movem.l	(sp)+,d1
	rts
_SNS2
	movem.l	d1,-(sp)
	move.w	#$9,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%0001_0000,d0
	movem.l	(sp)+,d1
	rts

	.data
	.even
title_mes:
	dc.b	'Hyper Picopico System',$0d,$0a
	dc.b	'    tiny version',$0d,$0a
	dc.b	' ＧＲＡＤＩＵＳ III',$0d,$0a
	dc.b	' - 伝説から神話へ -',$0d,$0a
	dc.b	'<< CUBE SIMULATION >>',$0d,$0a
	dc.b	'  (c)1991  副委員長',$0d,$0a,0
");
/********************************************************************************************/
void put_star()
{
	int i,j,k;
	for ( j=0; j<16; j++ ){
		for ( k=0; k<4; k++ ){
			bg_put( 0, ((rand()&0x3f)&rand() & 63), rand()& 63,  0x000d*4+k+0x0d00 );
			bg_put( 0, ((rand()&0xff)&rand() & 63), rand()& 63,  0x000e*4+k+0x0d00 );
			bg_put( 0, rand() & 63, ((rand()&0x03f)&rand()) & 63, 0x000f*4+k+0x0d00 );
		}
	}
	for ( j=0; j<16; j++ ){
		for ( k=0; k<4; k++ ){
			bg_put( 1, ((rand()&0x3f)&rand() & 63), rand()& 63,  0x000d*4+k+0x0d00 );
			bg_put( 1, ((rand()&0x7f)&rand() & 63), rand()& 63,  0x000e*4+k+0x0d00 );
			bg_put( 1, rand() & 63, ((rand()&0x03f)&rand()) & 63, 0x000f*4+k+0x0d00 );
		}
	}
}
/********************************************************************************************/
void g_scroll0111()		/*スクロール*/
{
	bg_scroll(0,bgx0>>1,0);
	bg_scroll(1,bgx1>>2,128);
	bgx0++;
	bgx1++;
	if ( bgx0>>1 > 511 ) bgx0 = 0;
	if ( bgx1>>2 > 511 ) bgx1 = 0;
	mei0++;
	mei1++;
	mei2++;
	mei3++;
	mei4++;
	mei5++;
	if ( mei0>>4 > 5 ) mei0 = 0;
	if ( mei1>>4 > 5 ) mei1 = 0;
	if ( mei2>>4 > 5 ) mei2 = 0;
	if ( mei3>>4 > 5 ) mei3 = 0;
	if ( mei4>>4 > 5 ) mei4 = 0;
	if ( mei5>>4 > 5 ) mei5 = 0;
	SAC_COLOR(1,hosi_pal[0][mei0>>4],0xd);
	SAC_COLOR(2,hosi_pal[1][mei1>>4],0xd);
	SAC_COLOR(3,hosi_pal[2][mei2>>4],0xd);
	SAC_COLOR(4,hosi_pal[3][mei3>>4],0xd);
	SAC_COLOR(5,hosi_pal[4][mei4>>4],0xd);
	SAC_COLOR(6,hosi_pal[5][mei5>>4],0xd);
}
/********************************************************************************************/
void enemy_load( char *name )
{
	FILE *fp;
	WORD i;

	if ( (fp = fopen( name, "rb" )) == (FILE*)NULL ){
		printf("%s がありません\n", name );
		exit( 1 );
	}
	i = 0;
	while ( fread( &enemy_tbl[i], 1, 2, fp ) == 2 ) i++;
	fclose( fp );
}
/********************************************************************************************
		スプライトプレーンを確保する関数

	palloc( &sp_lvl2, &stc_pl2, 2 )
		第一引数  プレーンレベルのアドレス
		第二引数  レベルストックのアドレス
		第三引数  確保数
		戻り値    確保成功ならチェーンテーブルの先頭引数
		　　　　　不成功ならゼロを返す
********************************************************************/
UBYTE palloc( UBYTE *level, UBYTE *stock, UBYTE n )
{
	UBYTE lvl, w, i = 0;

	lvl = *level;
	if ( *stock >= n ){					/*プレーンの確保可か？*/
		*stock -= n;					/*ストックから確保数を引く*/
		if ( pl_tbl[*level] != 255 )	/*トップレベルが使用中なら待避*/
			i = pl_tbl[*level];
		do {
			w = lvl;
			while ( pl_tbl[lvl] != 255 ) lvl++;
			pl_tbl[w] = lvl;
			pl_tbl[lvl] = 128;
		} while ( --n );
		if ( i ){						/*トップレベル使用中だったので復元*/
			lvl = pl_tbl[*level];		/*戻り値をセット*/
			pl_tbl[*level] = i;
		} else lvl = *level;
		return ( lvl );					/*戻り値は pl_tbl の引数*/
	} else  return ( 0 );				/*確保出来ない場合はゼロを返す*/
}

/********************************************************************************************
		スプライトプレーンを解放する関数

	pfree( &stc_pl2, teki_pl[m] )
		第一引数  レベルストックのアドレス
		第二引数  チェーンテーブルの引数
		戻り値    なし
********************************************************************/
void  pfree( UBYTE *stock, UBYTE n )
{
	UBYTE w;

	do {
		SP_APS( n, 511, 511, 255, 0 );		/*スプライトを消去*/
		w = pl_tbl[n];							/*ワークにテーブルの内容を格納*/
		pl_tbl[n] = 255;						/*テーブルの内容に２５５を代入*/
		(*stock)++;								/*ストック加算*/
		n = w;									/*ポインタを次へ移す*/
	} while ( w != 128 );						/*テーブルの内容が１２８まで繰り返す*/
}
/********************************************************************************************/
/*
	出現パターン一覧表

	01	02	03	04	05	06	07	08	09	10	11	12	13	14
   +------------------------------------------------------+
	6	10	2	6	2	2	6	9	6	6	10	8	3	8
	1	8	6	1	5	6	2	8	2	2	8	11	6	9
	8	3	11	8	11	11	8	3	8	8	3	6	11	6
	5	9	7	5	7	7	5	9	5	5	9	13	7	10
	11	3	11	7	10	11	8	3	8	8	3	5	10	5
	8	2	6	7	6	6	8	3	8	8	3	11	6
	9	5	12	8	13	13	9	5	9	9	5	7	13	7
	11	6	3	11	3	3	11	6	11
	2	8	6	1	7	7	5	9	5	5	9	13	7

*/


void demo( int cnt )
/*
cnt....０～１０２４-256
*/
{
	int i,j,k;

	i = cnt - 32;
	j =  cnt & 1;

	SP_APSV( 102, i,    168, jiki_pro_ptn[2][0]+(j * 0x0100), 3 );
	SP_APS(  103, i+16, 168, jiki_pro_ptn[2][1], 3 );
	k = option_ptn[option_cnt>>2];
	SP_APS( 104, i-20,  168, k, 3 );
	SP_APS( 105, i-40,  168, k, 3 );
	SP_APS( 106, i-60,  168, k, 3 );
	SP_APS( 107, i-80,  168, k, 3 );
	SP_APS( 108, i-100, 168, k, 3 );
	SP_APS( 109, i-120, 168, k, 3 );
	SP_APS( 110, i-140, 168, k, 3 );
	SP_APS( 111, i-160, 168, k, 3 );
	SP_APS( 112, i-180, 168, k, 3 );
	SP_APS( 113, i-200, 168, k, 3 );
	SP_APS( 114, i-220, 168, k, 3 );
	SP_APS( 115, i-240, 168, k, 3 );
	SP_APS( 116, i-260, 168, k, 3 );
	SP_APS( 117, i-280, 168, k, 3 );
	SP_APS( 118, i-300, 168, k, 3 );
	SP_APS( 119, i-320, 168, k, 3 );
	option_cnt++;
	if ( option_cnt>>2 > 3 ) option_cnt = 0;
}
