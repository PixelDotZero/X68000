#include <iocslib.h>
#include <stdio.h>
#include <basic.h>
#include <basic0.h>
#include <class.h>
#include <sprite.h>

void g_scroll0111();
void hit_put( int );
int ESCSNS();
int SPCSNS();
int HLPSNS();
int OP1CSNS();
int SNS2();
int SNS4();
int SNS6();
int SNS8();
void X68ooo();
void bgmes( UBYTE, UBYTE, UWORD, char *, int );
void sp_clear( int, int );
void direct__16( int, WORD, WORD, int );
void direct_16( WORD, WORD, int );
void tama();
void score_put( UWORD );
UBYTE pcm_load( char *, char *, UWORD );
void direct_load( char *, char *, char *, WORD );
void spl_load( char * );
void spp_load( char * );
void para_put( int, int, int, int );
void dat_write( char *, char *, UWORD );
void palet_light( UWORD *, UWORD * );
void palet_dark( UWORD * );
void put_star();

int rol;
int wait_mode;
UBYTE rand_num;
int demo_flg,demo_cnt;
struct GEAS {
	char		id,		/*キャラクタＩＤ*/
				atr,	/*未使用*/
				xs,		/*キャラクタ半径*/
				ys;
	WORD		x,		/*中心座標*/
				y;
};
struct GEAS my,dan[128];
char move[10005];		/* 10001:レベル   10002:スピード   10003:弾   10004:ランダマイズ */
int main_cnt;
int tama_p;
int tama_cnt,tama_cnt1,tama_cnt2,tama_cnt3,tama_cnt4,tama_cnt5,tama_cnt6,tama_cnt7;
int level;
int speed;
int stick_ptn0;
int stick_ptn1;
int jiki_p;
int jiki_xx,jiki_yy;
int end_flg;
int score,old_score;
int tama_x[128], tama_y[128], tama_vt[128], tama_ft[128], tpv[128], tama_pl[128], tama_w[128];
int tama_w0[128],tama_w1[128];
int tama_ft[128];
char tama_lvl[128];
int dan_p;
char x_buffA[32][300],y_buffA[32][300];
char x_buffB[32][300],y_buffB[32][300];
char x_buffC[32][200],y_buffC[32][200];
char x_buffD[32][140],y_buffD[32][140];
char *char_num[20]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J"};
int wk[20];
int exit_flg;

UBYTE bgmes0[]={
	 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
	10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
	26,27,28,29,30,31,32,33,34,35,36,37,38,39
};
UWORD dan_rol_tbl[80]={
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000,
	0x0000,0x4000,0xc000,0x8000,0x0000,0x4000,0xc000,0x8000
};

WORD hm_ptn[32]={
0x0c32,0x0c34,0x0c36,0x0c38,0x0c3a,0x0c3c,0x0c3e,0x0c40,0x0c42,
0x8c40,0x8c3e,0x8c3c,0x8c3a,0x8c38,0x8c36,0x8c34,0x8c32,
0xcc34,0xcc36,0xcc38,0xcc3a,0xcc3c,0xcc3e,0xcc40,0x4c42,
0x4c40,0x4c3e,0x4c3c,0x4c3a,0x4c38,0x4c36,0x4c34
};

/*      LEVEL    0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F     G     H     I     J*/
/*通常サーチ弾*/
int t0[]={      30,   40,   35,   40,   30,   25,   20,   15,   30,   15,10001,10001,   20,10001,    1,    0,  500,10001,10001,    2};
char t0s[]={     0,    0,    3,    1,    1,    2,    2,    2,    2,    3,    1,    1,    1,    0,    1,    1,    1,    0,    0,    0};
/*高速サーチ弾*/
int t1[]={      80,  512,  350,  300,  250,  200,  180,  120,   50,    8,10001,10001,  200,10001,    5,    2,10001,10001,10001,    8};
char t1s[]={     1,    1,    1,    2,    2,    2,    3,    3,    3,    3,    0,    0,    0,    2,    0,    0,    0,    0,    0,    2};
/*３２方向弾*/
int t2[]={   50000, 3020, 2200,  405, 2100, 1520, 1300, 1900, 1200,  300,10001, 1000,10001,10001,10001,10001,10001,10001,10001,  500};
char t2s[]={     0,    0,    0,    0,    1,    1,    1,    1,    0,    2,    1,    1,    1,    1,    1,    1,    0,    0,    0,    0};
/*レーザー*/
int t3[]={    9800,  100,  600,  500,   40,  300,  250,   30, 1200,   50,  320,  220,  800,   10,  310,10001,10001,    4,10001,  100};
char t3s[]={     2,    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    0,    3,    0,    3};
/*１６方向弾*/
int t4[]={    2000, 1400, 1120,  150,  900,  700,  550,  400,   90,  200,10001,  100,10001,10001,  500,10001,10001,10001,10001,  330};
char t4s[]={     0,    0,    0,    0,    1,    1,    1,    0,    1,    2,    2,    1,    1,    1,    1,    1,    0,    0,    0,    2};
/*スプリンクラー弾*/
int t5[]={   10001,10001,10001,10001,10001,10001,10001,10001,10001,10001,10001,  250,  120,10001,10001,10001,10001,10001,10001,  205};
char t5s[]={     0,    0,    0,    0,    1,    1,    1,    0,    1,    2,    1,    0,    0,    1,    1,    1,    0,    0,    0,    2};
/*花火弾*/
int t6[]={   10001,10001,10001,10001,10001,10001,10001,10001,10001,10001,  210,10001,10001,10001,10001,10001,10001,10001,10001,10001};
char t6s[]={     0,    0,    0,    0,    1,    1,    1,    0,    1,    2,    2,    0,    1,    1,    1,    1,    0,    0,    0,    0};
/*ホーミング*/
int t7[]={   10001,10001,10001,10001,10001,10001,10001,10001,10001,10001,  200,10001,10001,10001,10001,10001,   20,10001,    3,   32};
char t7s[]={     0,    0,    0,    0,    1,    1,    1,    0,    1,    2,    2,    0,    1,    1,    1,    1,    0,    0,    0,    0};
int wait[]={  2000, 1000,  100,   50,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,30000,    0,    0,    0,30000,30000};

UBYTE hmtbl32[32][32]={		/*ホーミングサーチテーブル（３２方向版）*/
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{ 2, 2, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
{ 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{ 4, 4, 4, 4, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
{ 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
{ 6, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6},
{ 7, 7, 7, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7},
{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 8, 8, 8, 8, 8, 8, 8},
{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, 9, 9, 9, 9, 9, 9},
{10,10,10,10,10,10,10,10,10,10,10,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,10,10,10,10,10},
{11,11,11,11,11,11,11,11,11,11,11,11,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,11,11,11,11},
{12,12,12,12,12,12,12,12,12,12,12,12,12,13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,12,12,12},
{13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,13,13},
{14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,14},
{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
{18,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18},
{19,19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,19,19,19,19,19,19,19,19,19,19,19,19,19},
{20,20,20,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,19,20,20,20,20,20,20,20,20,20,20,20,20},
{21,21,21,21,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,20,21,21,21,21,21,21,21,21,21,21,21},
{22,22,22,22,22,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,21,22,22,22,22,22,22,22,22,22,22},
{23,23,23,23,23,23,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,22,23,23,23,23,23,23,23,23,23},
{24,24,24,24,24,24,24,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,23,24,24,24,24,24,24,24,24},
{25,25,25,25,25,25,25,25,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,24,25,25,25,25,25,25,25},
{26,26,26,26,26,26,26,26,26,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,25,26,26,26,26,26,26},
{27,27,27,27,27,27,27,27,27,27,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,26,27,27,27,27,27},
{28,28,28,28,28,28,28,28,28,28,28,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,27,28,28,28,28},
{29,29,29,29,29,29,29,29,29,29,29,29,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,29,29,29},
{30,30,30,30,30,30,30,30,30,30,30,30,30,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,29,30,30},
{31,31,31,31,31,31,31,31,31,31,31,31,31,31,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,30,31},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,31}
};

char se00[315],se01[4932],se02[3839],se03[4351],se04[723],se05[4356];
int pcm_flg;
UWORD g_pal[16]={0,65535,61307,57079,52851,48623,44395,40167,35939,31711,27483,23255,21141,19027,16913,14799};
char logo[3072];
int ball;
WORD ball_p[7]={0x0211,0x0212,0x0213,0x0214,0x0215,0x0216,0x0217};	/*弾のパターン*/
char tama_size[7]={1,2,3,4,2,3,5};									/*弾のサイズ*/
WORD ball_ptn;
int tama_wk0[128];
WORD laser_ptn0[16]={
	0x0d22,0x0d24,0x0d26,0x0d28,0x0d2a,
	0x8d28,0x8d26,0x8d24,0x8d22,0xcd24,
	0xcd26,0xcd28,0x4d2a,0x4d28,0x4d26,
	0x4d24};
WORD laser_ptn1[16]={
	0x0d21,0x0d23,0x0d25,0x0d27,0x0d29,
	0x8d27,0x8d25,0x8d23,0x8d21,0xcd23,
	0xcd25,0xcd27,0x4d29,0x4d27,0x4d25,
	0x4d23};
WORD laser_ptn2[16]={
	0x0d2b,0x0d2c,0x0d2d,0x0d2e,0x0d2f,
	0x8d2e,0x8d2d,0x8d2c,0x8d2b,0xcd2c,
	0xcd2d,0xcd2e,0x4d2f,0x4d2e,0x4d2d,
	0x4d2c};
char laser_psx[16]={
	0, 2, 4, 3, 3, 3, 4, 2,
	0,-2,-4,-3,-3,-3,-4,-2};
char laser_psy[16]={
	-4, -3, -4, -1, 0, 1, 4, 3,
	 4,  3,  4,  1, 0,-1,-4,-3};
int hi_score[20];
int hi_hit[20];
int hi_ball[20];
int hit_cnt,old_hit_cnt;
UWORD d_pal[16];
UWORD star_pal[16]={				/*星のパレット*/
	0x0000,0x07fe,0x07fe,0xb7c0,
	0xffc0,0xb7c0,0x07c0,0x07c0,
	0xffc0,0x003e,0x003e,0x003e,
	0xb7c0,0xb7c0,0xffff,0xffff};
int mei0,mei1,mei2,meic0,meic1,meic2,meicc0,meicc1,meicc2;
WORD laser_moto[8]={0x0d20,0x0d1f,0x0d1e,0x0d1d,0x0d1d,0x0d1e,0x0d1f,0x0d20};
int rand_flg;
int fu_dsp;
WORD sara_pal[16]={0,53,45119,57,37693,1,19086,21264,27606,36062,48682,61306,63420,47998,0,0};
WORD x68_pal[16]={0,40101,35873,29530,25302,18960,20416,55296,64511,57407,45118,14846,44,32,1,65534};

int jiki_ppp;


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

	if ( argc == 2 ){
		if ( (fp = fopen( argv[1], "rb" )) == (FILE*)NULL ){
			printf("%s がありません.\n", argv[1] );
			exit( 1 );
		} else {
			asm("
				pea		load_mes
				dc.w	$ff09
				addq.l	#4,sp
			");
			pcm_load( argv[1], &move[0], 10005 );
			exit_flg = 4;
		}
	} else {
		exit_flg = 0;
		rand_flg = 0;		/* 0:パターン   1:ランダム*/
	}

	pcm_load( "LOGO.DAT", logo, (UWORD)sizeof( logo ) );
	pcm_load( "SE00.PCM", se00, (UWORD)sizeof( se00 ) );
	pcm_load( "SE01.PCM", se01, (UWORD)sizeof( se01 ) );
	pcm_load( "SE02.PCM", se02, (UWORD)sizeof( se02 ) );
	pcm_load( "SE03.PCM", se03, (UWORD)sizeof( se03 ) );
	pcm_load( "SE04.PCM", se04, (UWORD)sizeof( se04 ) );
	pcm_load( "SE05.PCM", se05, (UWORD)sizeof( se05 ) );
	direct_load("DA.DAT",&x_buffA[0][0], &y_buffA[0][0], 300 );
	direct_load("DC.DAT",&x_buffB[0][0], &y_buffB[0][0], 300 );
	direct_load("DB.DAT",&x_buffC[0][0], &y_buffC[0][0], 200 );
	direct_load("DD.DAT",&x_buffD[0][0], &y_buffD[0][0], 140 );

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

	vpage( 0 );
	GPUT( 0+80, 0+40, 95+80, 63+40, 0xc00000, &logo[0] );
	sp_off();sp_disp(1);
	spp_load("SATORI2.SPP");
	spl_load("SATORI2.SPL");
	bg_set(0,0,1);
	bg_set(1,1,1);
	bg_scroll(0,0,0);
	bg_scroll(1,0,0);
	bg_fill(0,0x0127);
	bg_fill(1,0x0127);
	NNPCMON();

	jiki_ppp = 0;		/* 0...６８　1...サラマンダ*/
	level = 0;
	speed = 1;
	ball = 0;

	my.id = 1;
	my.xs = 2;
	my.ys = 7;
	for ( i=0; i<20; i++ ){
		hi_score[i]=hi_ball[i]=hi_hit[i]=0;
	}
	put_star();
	rand_num = 16;		/*乱数系列初期値*/
	wait_mode = 0;		/*ウェイトモード*/

/*******************************ここよりループ***********************************************/
	while ( 1 ){
		sp_clear(0,127);
		jiki_xx = 128 << 4;
		jiki_yy = 128 << 4;
		end_flg = 0;
		main_cnt = 0;
		tama_p = 4;
		bgmes(3,16,5,"SHOOTING PRACTICE PROGRAM",0);
		bgmes(2,31,5,"@1991 DRY  ALL RIGHT RESEVED",0);
		if ( !my.id ) bgmes(10,14,14,"NODEATH MODE",0);
		i=50000;while(i--);
		for ( i=0; i<16; i++ ) d_pal[i] = 0x0000;
		SAC_COLOR3( &d_pal[0] );
		vpage( 1 );
		bgmes(10,35,14,"BEST PLAYERS",1);
		bgmes(0,37,6, "LV  SCR HIT BAL  LV  SCR HIT BAL",1);			/*ハイ・スコアの出力*/
		for ( i=0; i<10; i++ ){
			bgmes(    0,i*2+39,5,char_num[19-i],1);
			para_put( 5,i*2+39,hi_hit[19-i],1);
			para_put( 2,i*2+39,hi_score[19-i],1);
			bgmes(   17,i*2+39,5,char_num[9-i],1);
			para_put(22,i*2+39,hi_hit[9-i],1);
			para_put(19,i*2+39,hi_score[9-i],1);
		}

/*******************************タイトル*****************************************************/
		a = j = 0;
		while ( a < 32 ){
			j++;
			if ( j > 4096 ){				/*ＧＲパレットを明るくする*/
				a++;
				j = 0;
				for ( i=0; i<16; i++ ){
					palet_light( &d_pal[i], &g_pal[i] );
				}
				SAC_COLOR3( &d_pal[0] );
			}
		}

		rol = 0;
		demo_flg = demo_cnt = 0;
		a = exit_flg;
		b = level;
		c = speed;
		d = ball;
		e = rand_flg;
		while ( !end_flg ){
			if ( ESCSNS() ){
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
					pea		end_mes
					dc.w	$ff09
					addq.l	#4,sp
				");
				NNPCMOFF();
				exit( 1 );
			}

			if ( OP1SNS() && SNS6() && SNS8() ){				/*ウェイトモード設定*/
				NNPLAY(se05, 3*256+3, sizeof(se05));
				wait_mode = 1;
			} else {
				if ( OP1SNS() && SNS2() && SNS4() ){
					NNPLAY(se05, 3*256+3, sizeof(se05));
					wait_mode = 0;
				}
			}

			if ( HLPSNS() ){									/*無敵モード設定*/
				my.id = 1 - my.id;
				NNPLAY(se05, 3*256+3, sizeof(se05));
				if ( !my.id ) bgmes(10,14,14,"NODEATH MODE",0);
					else bgmes(10,14,14,"            ",0);
				while ( HLPSNS() );
			}

			if ( SNSS() ){										/*自機設定*/
				jiki_ppp = 1 - jiki_ppp;
				NNPLAY(se05, 3*256+3, sizeof(se05));
			}

			if ( STICK_INP_NML(1) > 0 || SNS2() ){
				if ( exit_flg < 6 ) exit_flg++;
			}
			if ( STICK_INP_NML(1) < 0 || SNS8() ){
				if ( exit_flg > 0 ) exit_flg--;
			}
			wk[0] = 5;
			wk[1] = 5;
			wk[2] = 5;
			wk[3] = 5;
			wk[4] = 5;
			wk[5] = 5;
			wk[6] = 5;
			wk[exit_flg] = 6;
			bgmes(13,20,wk[0],"START",0);
			bgmes(13,21,wk[1],"LEVEL",0);
			bgmes(13,22,wk[2],"SPEED",0);
			bgmes(13,23,wk[3],"SAVE",0);
			bgmes(13,24,wk[4],"REPLAY",0);
			if ( !rand_flg ) bgmes(13,25,wk[5],"PATTERN",0);
						else bgmes(13,25,wk[5],"RANDOM ",0);
			bgmes(13,26,wk[6],"BALL",0);
			bgmes(19,21,5,char_num[level],0);
			bgmes(19,22,5,char_num[speed-1],0);
			i=80000;while(i--);
			SP_APSV( 0, 128+8, 168+14+48+4, ball_p[ball]|dan_rol_tbl[(rol++)>>1], 1 );
			if ( rol > 40 ) rol = 0;
			if ( exit_flg == 0 && (TRIGGER_NML()|SPCSNS()) ){				/*スタート*/
				end_flg = 1;
			}
			if ( exit_flg == 1 ){											/*レベル選択*/
				if ( STICK_INP_NML(0) > 0 || SNS6() ){
					if ( level < 15+4 ) level++;
				} else {
					if ( STICK_INP_NML(0) < 0 || SNS4() ){
						if ( level > 0 ) level--;
					}
				}
			}
			if ( exit_flg == 2 ){											/*スピード選択*/
				if ( STICK_INP_NML(0) > 0 || SNS6() ){
					if ( speed < 10 ) speed++;
				} else {
					if ( STICK_INP_NML(0) < 0 || SNS4() ){
						if ( speed > 1 ) speed--;
					}
				}
			}
			if ( exit_flg == 3 && (TRIGGER_NML()|SPCSNS()) && move[10002] ){/*データ書き込み*/
				dat_write( "SATORI.PLY", &move[0], sizeof( move ) );
			}
			if ( exit_flg == 4 && (TRIGGER_NML()|SPCSNS()) && move[10002] ){/*リプレイ*/
				end_flg = 1;	/*スピードは１～１０なので    */
				demo_flg = 1;	/*０以外ならデータが入っている*/
				while ( TRIGGER_NML() || SPCSNS() );
			}
			if ( exit_flg == 5  ){											/*乱数系列選択*/
				if ( STICK_INP_NML(0) || SNS6() || SNS4() ){
					rand_flg = 1 - rand_flg;
				}
			}
			if ( exit_flg == 6 ){											/*ボール選択*/
				if ( STICK_INP_NML(0) > 0 || SNS6() ){
					ball++;
					if ( ball > 6 ) ball = 0;
				} else {
					if ( STICK_INP_NML(0) < 0 || SNS4() ){
						ball--;
						if ( ball < 0 ) ball = 6;
					}
				}
			}
			if ( exit_flg != a || level != b || speed != c || ball != d || rand_flg != e ){
				NNPLAY(se04, 3*256+3, sizeof(se04));
				a = exit_flg;
				b = level;
				c = speed;
				d = ball;
				e = rand_flg;
				rand_num = (rand_num+1+a*b-d+a) & 0xfe;
				main_cnt = 0;
			}
			rand_num++;
			main_cnt++;											/*ハイ・スコアの表示*/
			rand_num=(rand_num+1)&0xfe;
			if ( main_cnt > 100 ){
				rand_num=(rand_num+11)&0xfe;
				if ( demo_cnt++ > 1 && move[10002] ){
					end_flg = demo_flg = 1;	/*３回目ならデモプレイ実行*/
				} else {
					main_cnt = 0;
					bg_set(0,0,0);
					a = j = 0;				/*ＧＲパレット暗くする*/
					while ( a < 13 ){
						j++;
						if ( j > 1024 ){
							a++;
							j = 0;
							for ( i=0; i<16; i++ ){
								palet_dark( &d_pal[i] );
							}
							SAC_COLOR3( &d_pal[0] );
						}
					}
					i=j=0;
					while ( (i>>3) < 256 && !TRIGGER_NML() && !SPCSNS() ){
						bg_scroll(1,0,i>>3);
						for ( a=0; a<10; a++ ){
							SP_APS(a+1,248,(404+64-(i>>3))-(a*16),ball_p[hi_ball[a]],1);
							SP_APS(a+11,112,(404+64-(i>>3))-(a*16),ball_p[hi_ball[a+10]],1);
						}
						SP_APSV(0,511,511,256,0);
						i+=8;
					}
					j=  120000;while(j-- && !TRIGGER_NML() && !SPCSNS() );
					j=   20000;while(j--);
					bg_scroll(1,0,0);
					sp_clear(0,127);
					bg_set(0,0,1);
					for ( i=0; i<16; i++ ) d_pal[i] = g_pal[i];
					SAC_COLOR3( &d_pal[0] );
				}
			}
		}
		end_flg = 0;
/*******************************タイトル終わり***********************************************/

		if ( !jiki_ppp ){
			jiki_p = 0x010c;
			SAC_COLOR2(1,x68_pal);
		} else {
			jiki_p = 0x0146;
			SAC_COLOR2(1,sara_pal);
		}

		if ( demo_flg ){							/*リプレイ設定*/
			level    = move[10000+1];
			speed    = move[10000+2];
			ball     = move[10000+3];
			rand_num = move[10000+4];
			randomize( rand_num );
		} else {									/*乱数系列設定*/
			if ( !rand_flg ) rand_num = 1;
			randomize( rand_num );
		}

		bgmes(13,20,6,"     ",  0);
		bgmes(13,21,5,"       ",0);
		bgmes(13,22,5,"       ",0);
		bgmes(13,23,5,"    ", 0);
		bgmes(13,24,5,"      ", 0);
		bgmes(13,25,5,"       ",0);
		bgmes(13,26,5,"    ",   0);
		bgmes(3,16,5,"                         ",0);
		bgmes(2,31,5,"                            ",0);
		bgmes(10,14,14,"            ",0);
		SP_APSV( 0, 511,511,256,0 );
		pcm_flg = 0;
		ball_ptn = ball_p[ball];
		for ( i=0; i<128; i++ ){
			dan[i].id = 0;
			dan[i].xs = dan[i].ys = tama_size[ball];
			tama_w[i] = tama_ft[i] = 0;
		}
		tama_cnt=tama_cnt1=tama_cnt2=tama_cnt3=tama_cnt4=tama_cnt5=tama_cnt6=tama_cnt7=0;
		hit_cnt = old_hit_cnt = 0;
		bgmes(0,31,5,"SCORE",0);
		if ( rand_num == 1 ) bgmes(23,31,5,"P",0);
						else bgmes(23,31,5,"R",0);
		bgmes(24,31,5,char_num[speed-1],0);
		bgmes(26,31,6,"LEVEL",0);
		bgmes(31,31,6,char_num[level],0);
		if ( demo_flg ) bgmes(13,0,6,"REPLAY",0);

		main_cnt = score = old_score = 0;
		vpage( 0 );
		for ( i=0; i<16; i++ ) d_pal[i] = star_pal[i];
		SAC_COLOR3( &d_pal[0] );
		vpage( 14 );
		mei0 = 0; mei1 = 1; mei2 = 0;
		meic0 = meic1 = meic2 = 0;
		meicc0 = 10; meicc1 = 2; meicc2 = 0;
		d_pal[6] = d_pal[7] = d_pal[8] = d_pal[9] = d_pal[10] = 0x0000;
		fu_dsp = 0;

/*******************************メインルーチン***********************************************/
		while ( !end_flg ){
			tama();
			X68ooo();
			g_scroll0111();
			dan_p = 127;												/*自機と弾の判定*/
			if ( my.id && ACT2( &my, &dan[0], &dan_p ) ){
				dan[dan_p].xs = dan[dan_p].ys = tama_size[ball];
				dan[dan_p].x = 300;
				dan[dan_p].id = 0;
				if ( !jiki_ppp ) jiki_p = 0x0f0c; else jiki_p = 0x0f46;
				pcm_flg = 1;
				NNPLAY(se02, 3*256+3, sizeof(se02) );
				hit_cnt++;
			}
			if ( score != old_score ) score_put( score );
			if ( hit_cnt != old_hit_cnt ) hit_put( hit_cnt );
			if ( ESCSNS() ) end_flg = 1;
			if ( (TRIGGER_NML() && demo_flg)|(SPCSNS() && demo_flg) ) end_flg = 1;
			if ( pcm_flg & !NNSTAT() ) pcm_flg = 0;
			main_cnt++;
			score++;
			if ( score >= 10000 ) end_flg = 1;
			if ( hit_cnt > 2 ) end_flg = 1;
			if ( score > 5000 & score < 5100 ) fu_dsp = 1; else fu_dsp = 0;
			if ( wait_mode ){
				i=30000+wait[level];while(i--);
			} else {
				i=wait[level];while(i--);
			}
		}
		hit_put( hit_cnt );
		score_put( score );
		SP_APS(  1, my.x+7, my.y+16, jiki_p   +1 +(stick_ptn0<<1), 1 );
		SP_APSV( 0, my.x+7, my.y,    jiki_p      +(stick_ptn0<<1), 1 );
		SP_APSV( 0, my.x+7, my.y,    jiki_p      +(stick_ptn0<<1), 1 );
/********************************************************************************************/
		/*ハイスコアの更新*/
		if ( hi_score[level] <= score ){
			if ( score == 10000 ){
				bgmes( 5,16,14,"YOU COMPLETE THIS LEVEL",0);
				j+=20000;
			}
			if ( hi_hit[level] == 0 || hi_hit[level] >= hit_cnt ){
				j=   20000;
				NNPLAY(se05, 3*256+3, sizeof(se05));
				bgmes( 8,14,6,"HI SCORE",0);
				para_put(19,14,score,0);

				hi_hit[level] = hit_cnt;
				hi_score[level] = score;
				hi_ball[level] = ball;
				while(j-- && !TRIGGER_NML() && !ESCSNS() );
				bgmes( 8,14,6,"                ",0);
			}
			bgmes( 5,16,6,"                       ",0);
		} else {
			bgmes(11,15,6,"GAME  OVER",0);
			j = 50000;
			while ( j-- && !TRIGGER_NML() && !SPCSNS() );
			bgmes(11,15,6,"          ",0);
		}
		bgmes(0,31,5,"                                ",0);
		if ( demo_flg ) bgmes(13,0,6,"      ",0);
		if ( !demo_flg ){				/*リプレイではないので記憶*/
			move[10000+1] = level;
			move[10000+2] = speed;
			move[10000+3] = ball;
			move[10000+4] = rand_num;
		}
	}
}
/***********************************自機移動*************************************************/
void X68ooo()
{
	int i;
	char j;

	if ( !demo_flg ){													/*通常*/
		stick_ptn0 = STICK_INP_NML(0);
		if ( SNS6() ) stick_ptn0 = 1;
		if ( SNS4() ) stick_ptn0 = -1;
		stick_ptn1 = STICK_INP_NML(1);
		if ( SNS2() ) stick_ptn1 = 1;
		if ( SNS8() ) stick_ptn1 = -1;
		move[main_cnt] = ((((char)stick_ptn0)<<4) & 0xf0)|(((char)stick_ptn1) & 0x0f);
	} else {															/*リプレイ*/
		stick_ptn0 = (int)(((char)(move[main_cnt]&0xf0))>>4);
		j =    ((UBYTE)(move[main_cnt]&0x0f))<<4;
		stick_ptn1 = (int)(j>>4);
		if ( OP1SNS() ){ i=50000;while(i--);}
	}

	i = speed * 16;
	jiki_xx += i * stick_ptn0;
	jiki_yy += i * stick_ptn1;
	if ( jiki_xx < 128 )  jiki_xx += i;		/*  8   x 16 */
	if ( jiki_xx > 3968 ) jiki_xx -= i;		/*  247 x 16 */
	if ( jiki_yy < 416 )  jiki_yy += i;		/*  26  x 16 */
	if ( jiki_yy > 3760 ) jiki_yy -= i;		/*  235 x 16 */
	my.x = jiki_xx >> 4;
	my.y = jiki_yy >> 4;
	SP_APSV( 0, my.x+7, my.y,    jiki_p      +(stick_ptn0<<1), 1 );
	SP_APS(  1, my.x+7, my.y+16, jiki_p   +1 +(stick_ptn0<<1), 1 );
	SP_APS(  2, my.x+7+16, my.y-16, 0x0930, fu_dsp );
	SP_APS(  3, my.x+7+16, my.y,    0x0931, fu_dsp );
	if ( !jiki_ppp ){
		if ( jiki_p != 0x010c ) jiki_p = 0x010c;
	} else {
		if ( jiki_p != 0x0146 ) jiki_p = 0x0146;
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

	.globl	___divsi3
	.globl	___udivsi3

___divsi3
	move.l	4(sp),d1
	move.l	d1,d0
	swap	d0
	or.w	8(sp),d0
	bne	__divs

	divu	10(sp),d1
	moveq.l	#0,d0
	move.w	d1,d0
	rts

__divs
	move.l	d1,d0
	bpl	__divpn
__divmn
	neg.l	d0
	move.l	8(sp),d1
	beq	__zero
	bpl	__divmp
__divmm
	neg.l	d1
__divpp
	bra	__udiv
__divmp
	bsr	__udiv
	neg.l	d0
	rts
__divpn
	move.l	8(sp),d1
	beq	__zero
	bpl	__divpp
__divpm
	neg.l	d1
	bsr	__udiv
	neg.l	d0
	rts

*////////////////////////////////////////////////
*
__zero
	moveq.l	#0,d0
	rts
__one
	moveq.l	#1,d0
	rts
__byzero
	moveq.l	#0,d1
	divu	d1,d0
	rts
__udivw
	move.l	d0,d2
	clr.w	d2
	swap	d2
	divu	d1,d2
	move.l	d2,a0
	move.w	d0,d2
	divu	d1,d2
	move.w	a0,d0
	swap	d0
	move.w	d2,d0
	rts

__udivss
	swap	d0
	swap	d1
	divu	d1,d0
	and.l	#$0000ffff,d0
	rts

*////////////////////////////////////////////////
*
___udivsi3
	move.l	4(sp),d1
	move.l	d1,d0
	swap	d0
	or.w	8(sp),d0
	bne	__divu

	divu	10(sp),d1
	moveq.l	#0,d0
	move.w	d1,d0
	rts
__divu
	move.l	d1,d0
	move.l	8(sp),d1
	beq	__zero

*////////////////////////////////////////////////
*
*	d0.l /= d1.l
*
__udiv
	cmp.l	d0,d1
	beq	__one
	bhi	__zero

	cmp.l	#$00010000,d1
	bcs	__udivw

	move.w	d0,d2
	or.w	d1,d2
	beq	__udivss

	lea.l	__sfttbl(pc),a0
	move.l	d0,a1
	move.l	d1,a2
	cmp.l	#$01000000,d1
	bcc	__dsft16
__dsft8
	move.l	d1,d2
	swap	d2
	move.b	(a0,d2.w),d2
	lsr.l	d2,d1
	lsr.l	d2,d0
	bra	__div
__dsft16
	move.l	d1,d2
	swap	d2
	lsr.w	#8,d2
	move.b	(a0,d2.w),d2
	addq.w	#8,d2
	lsr.l	d2,d1
	lsr.l	d2,d0
__div
	divu	d1,d0
	and.l	#$0000ffff,d0
	move.l	d0,d2

	move.l	a2,d1
	mulu	d1,d2		; d0 = d1.low * d0
	swap	d1
	mulu	d0,d1		; d1 = d1.hi  * d0
	swap	d1
	clr.w	d1
	add.l	d1,d2
	cmp.l	a1,d2
	bls	__over
	subq.l	#1,d0
__over
	rts

*////////////////////////////////////////////////
*
__sfttbl
	dc.b	0		; 00
	dc.b	1		; 01
	dc.b	2		; 02
	dc.b	2		; 03
	dc.b	3		; 04
	dc.b	3		; 05
	dc.b	3		; 06
	dc.b	3		; 07
	dc.b	4		; 08
	dc.b	4		; 09
	dc.b	4		; 0a
	dc.b	4		; 0b
	dc.b	4		; 0c
	dc.b	4		; 0d
	dc.b	4		; 0e
	dc.b	4		; 0f
	dc.b	5		; 10
	dc.b	5		; 11
	dc.b	5		; 12
	dc.b	5		; 13
	dc.b	5		; 14
	dc.b	5		; 15
	dc.b	5		; 16
	dc.b	5		; 17
	dc.b	5		; 18
	dc.b	5		; 19
	dc.b	5		; 1a
	dc.b	5		; 1b
	dc.b	5		; 1c
	dc.b	5		; 1d
	dc.b	5		; 1e
	dc.b	5		; 1f
	dc.b	6		; 20
	dc.b	6		; 21
	dc.b	6		; 22
	dc.b	6		; 23
	dc.b	6		; 24
	dc.b	6		; 25
	dc.b	6		; 26
	dc.b	6		; 27
	dc.b	6		; 28
	dc.b	6		; 29
	dc.b	6		; 2a
	dc.b	6		; 2b
	dc.b	6		; 2c
	dc.b	6		; 2d
	dc.b	6		; 2e
	dc.b	6		; 2f
	dc.b	6		; 30
	dc.b	6		; 31
	dc.b	6		; 32
	dc.b	6		; 33
	dc.b	6		; 34
	dc.b	6		; 35
	dc.b	6		; 36
	dc.b	6		; 37
	dc.b	6		; 38
	dc.b	6		; 39
	dc.b	6		; 3a
	dc.b	6		; 3b
	dc.b	6		; 3c
	dc.b	6		; 3d
	dc.b	6		; 3e
	dc.b	6		; 3f
	dc.b	7		; 40
	dc.b	7		; 41
	dc.b	7		; 42
	dc.b	7		; 43
	dc.b	7		; 44
	dc.b	7		; 45
	dc.b	7		; 46
	dc.b	7		; 47
	dc.b	7		; 48
	dc.b	7		; 49
	dc.b	7		; 4a
	dc.b	7		; 4b
	dc.b	7		; 4c
	dc.b	7		; 4d
	dc.b	7		; 4e
	dc.b	7		; 4f
	dc.b	7		; 50
	dc.b	7		; 51
	dc.b	7		; 52
	dc.b	7		; 53
	dc.b	7		; 54
	dc.b	7		; 55
	dc.b	7		; 56
	dc.b	7		; 57
	dc.b	7		; 58
	dc.b	7		; 59
	dc.b	7		; 5a
	dc.b	7		; 5b
	dc.b	7		; 5c
	dc.b	7		; 5d
	dc.b	7		; 5e
	dc.b	7		; 5f
	dc.b	7		; 60
	dc.b	7		; 61
	dc.b	7		; 62
	dc.b	7		; 63
	dc.b	7		; 64
	dc.b	7		; 65
	dc.b	7		; 66
	dc.b	7		; 67
	dc.b	7		; 68
	dc.b	7		; 69
	dc.b	7		; 6a
	dc.b	7		; 6b
	dc.b	7		; 6c
	dc.b	7		; 6d
	dc.b	7		; 6e
	dc.b	7		; 6f
	dc.b	7		; 70
	dc.b	7		; 71
	dc.b	7		; 72
	dc.b	7		; 73
	dc.b	7		; 74
	dc.b	7		; 75
	dc.b	7		; 76
	dc.b	7		; 77
	dc.b	7		; 78
	dc.b	7		; 79
	dc.b	7		; 7a
	dc.b	7		; 7b
	dc.b	7		; 7c
	dc.b	7		; 7d
	dc.b	7		; 7e
	dc.b	7		; 7f
	dc.b	8		; 80
	dc.b	8		; 81
	dc.b	8		; 82
	dc.b	8		; 83
	dc.b	8		; 84
	dc.b	8		; 85
	dc.b	8		; 86
	dc.b	8		; 87
	dc.b	8		; 88
	dc.b	8		; 89
	dc.b	8		; 8a
	dc.b	8		; 8b
	dc.b	8		; 8c
	dc.b	8		; 8d
	dc.b	8		; 8e
	dc.b	8		; 8f
	dc.b	8		; 90
	dc.b	8		; 91
	dc.b	8		; 92
	dc.b	8		; 93
	dc.b	8		; 94
	dc.b	8		; 95
	dc.b	8		; 96
	dc.b	8		; 97
	dc.b	8		; 98
	dc.b	8		; 99
	dc.b	8		; 9a
	dc.b	8		; 9b
	dc.b	8		; 9c
	dc.b	8		; 9d
	dc.b	8		; 9e
	dc.b	8		; 9f
	dc.b	8		; a0
	dc.b	8		; a1
	dc.b	8		; a2
	dc.b	8		; a3
	dc.b	8		; a4
	dc.b	8		; a5
	dc.b	8		; a6
	dc.b	8		; a7
	dc.b	8		; a8
	dc.b	8		; a9
	dc.b	8		; aa
	dc.b	8		; ab
	dc.b	8		; ac
	dc.b	8		; ad
	dc.b	8		; ae
	dc.b	8		; af
	dc.b	8		; b0
	dc.b	8		; b1
	dc.b	8		; b2
	dc.b	8		; b3
	dc.b	8		; b4
	dc.b	8		; b5
	dc.b	8		; b6
	dc.b	8		; b7
	dc.b	8		; b8
	dc.b	8		; b9
	dc.b	8		; ba
	dc.b	8		; bb
	dc.b	8		; bc
	dc.b	8		; bd
	dc.b	8		; be
	dc.b	8		; bf
	dc.b	8		; c0
	dc.b	8		; c1
	dc.b	8		; c2
	dc.b	8		; c3
	dc.b	8		; c4
	dc.b	8		; c5
	dc.b	8		; c6
	dc.b	8		; c7
	dc.b	8		; c8
	dc.b	8		; c9
	dc.b	8		; ca
	dc.b	8		; cb
	dc.b	8		; cc
	dc.b	8		; cd
	dc.b	8		; ce
	dc.b	8		; cf
	dc.b	8		; d0
	dc.b	8		; d1
	dc.b	8		; d2
	dc.b	8		; d3
	dc.b	8		; d4
	dc.b	8		; d5
	dc.b	8		; d6
	dc.b	8		; d7
	dc.b	8		; d8
	dc.b	8		; d9
	dc.b	8		; da
	dc.b	8		; db
	dc.b	8		; dc
	dc.b	8		; dd
	dc.b	8		; de
	dc.b	8		; df
	dc.b	8		; e0
	dc.b	8		; e1
	dc.b	8		; e2
	dc.b	8		; e3
	dc.b	8		; e4
	dc.b	8		; e5
	dc.b	8		; e6
	dc.b	8		; e7
	dc.b	8		; e8
	dc.b	8		; e9
	dc.b	8		; ea
	dc.b	8		; eb
	dc.b	8		; ec
	dc.b	8		; ed
	dc.b	8		; ee
	dc.b	8		; ef
	dc.b	8		; f0
	dc.b	8		; f1
	dc.b	8		; f2
	dc.b	8		; f3
	dc.b	8		; f4
	dc.b	8		; f5
	dc.b	8		; f6
	dc.b	8		; f7
	dc.b	8		; f8
	dc.b	8		; f9
	dc.b	8		; fa
	dc.b	8		; fb
	dc.b	8		; fc
	dc.b	8		; fd
	dc.b	8		; fe
	dc.b	8		; ff



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
yp1:
	dc.w	1024
	dc.w	1024
	dc.w	1024
	.even
title_mes:
	dc.b	'  Hyper Picopico System',$0d,$0a
	dc.b	'       tiny version',$0d,$0a
	dc.b	'SHOOTING PRACTICE PROGRAM',$0d,$0a
	dc.b	'      ‥… 悟り …‥',$0d,$0a
	dc.b	'        VERSION 2',$0d,$0a
	dc.b	'    (c)1991  副委員長',$0d,$0a,0
	.even
load_mes:
	dc.b	'プレイデータを読み込みます',$0d,$0a,0
.even
end_mes:
	dc.b	'遊んで頂き誠に有難う御座いました!!',$0d,$0a,0
");
/********************************************************************************************/
void tama()
{
	int k,m,n,o,i,p,q,j,r;

	tama_cnt++;
	tama_cnt1++;
	tama_cnt2++;
	tama_cnt3++;
	tama_cnt4++;
	tama_cnt5++;
	tama_cnt6++;
	tama_cnt7++;
	if ( tama_cnt > t0[level]+(rand()&0x3f) ){		/*通常サーチ弾発生*/
		tama_cnt = 0;
		direct_16( (rand() & 0x1ff)>>1,(rand() & 0x1ff)>>1, t0s[level] );
	}
	if ( tama_cnt1 > t1[level] ){						/*高速サーチ弾発生*/
		tama_cnt1 = 0;
		direct_16( (rand() & 0x1ff)>>1,(rand() & 0x1ff)>>1, t1s[level] );
	}
	if ( tama_cnt2 > t2[level] ){						/*３２方向弾発生*/
		tama_cnt2 = 0;
		if ( !tama_ft[tama_p] ){
			k = rand()&0xff;
			n = rand()&0xff;
			tama_pl[tama_p] = tama_p;
			tpv[tama_p] = 0;
			dan[tama_p].x = k;
			dan[tama_p].y = n;
			tama_ft[tama_p]  = 2;
			tama_w[tama_p] = -30;
			dan[tama_p].id = 0;
			SP_APS(tama_pl[tama_p],k+8,n+8,0x041c,1);
			tama_p++;
			if ( tama_p > 127 ) tama_p = 4;
		}
	}
	if ( tama_cnt3 > t3[level] ){						/*レーザー発生*/
		tama_cnt3 = 0;
		if ( !tama_ft[tama_p] ){
			k = rand()&0xff;
			n = rand()&0xff;
			tama_pl[tama_p] = tama_p;
			tpv[tama_p] = 0;
			dan[tama_p].x = k;
			dan[tama_p].y = n;
			tama_ft[tama_p]  = 6;
			tama_w[tama_p] = -8;
			dan[tama_p].id = 0;
			SP_APS(tama_pl[tama_p],k+8,n+8,0x081c,1);
			tama_p++;
			if ( tama_p > 127 ) tama_p = 4;
		}
	}
	if ( tama_cnt4 > t4[level] ){						/*１６方向弾発生*/
		tama_cnt4 = 0;
		if ( !tama_ft[tama_p] ){
			k = 64+(rand()&0x7f);
			n = 64+(rand()&0x7f);
			tama_pl[tama_p] = tama_p;
			tpv[tama_p] = 0;
			dan[tama_p].x = k;
			dan[tama_p].y = n;
			tama_ft[tama_p]  = 5;
			tama_w[tama_p] = -30;
			dan[tama_p].id = 0;
			SP_APS(tama_pl[tama_p],k+8,n+8,0x071c,1);
			tama_p++;
			if ( tama_p > 127 ) tama_p = 4;
		}
	}
	if ( tama_cnt5 > t5[level] ){						/*スプリンクラー弾発生*/
		tama_cnt5 = 0;
		if ( !tama_ft[tama_p] ){
			k = rand()&0xff;
			n = rand()&0xff;
			tama_pl[tama_p] = tama_p;
			tpv[tama_p] = 0;
			dan[tama_p].x = k;
			dan[tama_p].y = n;
			tama_ft[tama_p]  = 10;
			tama_w[tama_p] = -128-30;
			tama_w1[tama_p] = 0;
			dan[tama_p].id = 0;
			SP_APS(tama_pl[tama_p],k+8,n+8,0x0a1c,1);
			tama_p++;
			if ( tama_p > 127 ) tama_p = 4;
		}
	}
	if ( tama_cnt6 > t6[level] ){						/*花火弾発生*/
		tama_cnt6 = 0;
		if ( !tama_ft[tama_p] ){
			k = 64+(rand()&0x7f);
			n = 64+(rand()&0x7f);
			tama_pl[tama_p] = tama_p;
			tpv[tama_p] = 0;
			dan[tama_p].x = k;
			dan[tama_p].y = n;
			tama_ft[tama_p]  = 20;
			tama_w[tama_p] = -75-30;
			dan[tama_p].id = 0;
			SP_APS(tama_pl[tama_p],k+8,n+8,0x0b1c,1);
			tama_p++;
			if ( tama_p > 127 ) tama_p = 4;
		}
	}
	if ( tama_cnt7 > t7[level] ){						/*ホーミング発生*/
		tama_cnt7 = 0;
		if ( !tama_ft[tama_p] ){
			k = rand()&0xff;
			n = ((rand()&0xff)+(rand()&0xff))&0xff;
			tama_pl[tama_p] = tama_p;
			tpv[tama_p] = 0;
			dan[tama_p].x = k;
			dan[tama_p].y = n;
			tama_ft[tama_p]  = 30;
			tama_w[tama_p] = -10;
			dan[tama_p].id = 0;
			SP_APS(tama_pl[tama_p],k+8,n+8,0x0d1c,1);
			tama_p++;
			if ( tama_p > 127 ) tama_p = 4;
		}
	}


	k = m = 4;
	while ( m < 128 ){
		if ( tama_ft[m] ){
/*以下、予告パターン発生より tama_w が 0x0000001f より大きい場合の処理*/
			if ( tama_w[m] > 0x0000001f ){
				if ( tama_ft[m] != 4 && tama_ft[m] != 31 ){		/*弾の移動*/
					SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,ball_ptn|dan_rol_tbl[tpv[m]>>3],1);
					switch ( tama_lvl[m] ){
						case 0:
							dan[m].x += x_buffA[tama_vt[m]][tpv[m]];
							dan[m].y += y_buffA[tama_vt[m]][tpv[m]];
							break;
						case 1:
							dan[m].x += x_buffB[tama_vt[m]][tpv[m]];
							dan[m].y += y_buffB[tama_vt[m]][tpv[m]];
							break;
						case 2:
							dan[m].x += x_buffC[tama_vt[m]][tpv[m]];
							dan[m].y += y_buffC[tama_vt[m]][tpv[m]];
							break;
						case 3:
							dan[m].x += x_buffD[tama_vt[m]][tpv[m]];
							dan[m].y += y_buffD[tama_vt[m]][tpv[m]];
							break;
					}
					tpv[m]++;
					if ( (dan[m].x < -12) || (dan[m].x > 268) || (dan[m].y < -16) || (dan[m].y > 272) ){
						tama_ft[m] = dan[m].id = 0;
					}
				} else {
					if ( tama_ft[m] == 4 ){			/*レーザーの移動*/
						switch ( tama_wk0[m] ){
							case 0:SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_ptn0[tama_vt[m]],1);
								break;
							case 7:SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_ptn2[tama_vt[m]],1);
								break;
							default:SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_ptn1[tama_vt[m]],1);
								break;
						}
						switch ( tama_lvl[m] ){
							case 2:
								dan[m].x += x_buffC[tama_vt[m]<<1][tpv[m]];
								dan[m].y += y_buffC[tama_vt[m]<<1][tpv[m]];
								break;
							case 3:
								dan[m].x += x_buffD[tama_vt[m]<<1][tpv[m]];
								dan[m].y += y_buffD[tama_vt[m]<<1][tpv[m]];
								break;
						}
						tpv[m]++;
						if ( (dan[m].x < -16) || (dan[m].x > 272) || (dan[m].y < -16) || (dan[m].y > 272) ){
							dan[m].xs = dan[m].ys = tama_size[ball];
							tama_ft[m] = dan[m].id = 0;
						}
					} else {		/*ホーミングの移動*/
/*
		tama_vt:方向　０～３１
		tama_w0:サーチカウンタ
		tama_w1:ついび終了カウンタ
*/
						tama_w0[m]++;
						if ( tama_w1[m] < 8 ){
							j = 1;
							dan[m].x += x_buffA[tama_vt[m]][tpv[m]];
							dan[m].y += y_buffA[tama_vt[m]][tpv[m]++];
						} else {
							j = 3;
							if ( tama_w1[m] > 7 && tama_w1[m] < 16 ){
								dan[m].x += x_buffC[tama_vt[m]][tpv[m]];
								dan[m].y += y_buffC[tama_vt[m]][tpv[m]++];
							} else {
								dan[m].x += x_buffD[tama_vt[m]][tpv[m]];
								dan[m].y += y_buffD[tama_vt[m]][tpv[m]++];
							}
						}

						if ( tama_w0[m] > j && tama_w1[m] < 32 ){
							tpv[m] = 0;
							tama_w0[m] = 0;
							tama_vt[m] = hmtbl32[tama_vt[m]][SRCH32(my.x,my.y,dan[m].x,dan[m].y)];
							tama_w1[m]++;
						}
						if ( tama_w0[m] > 3 ) tama_w0[m] = 0;
						SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,hm_ptn[tama_vt[m]]+(tama_w0[m]>>1),1);
						if ( (dan[m].x < -12) || (dan[m].x > 268) || (dan[m].y < -16) || (dan[m].y > 272) ){
							tama_ft[m] = dan[m].id = 0;
							dan[m].xs = dan[m].ys = tama_size[ball];
						}
					}
				}

			} else {
/*以下、予告パターン発生より tama_w が 0x0000001f と等しい場合の処理*/
				if ( tama_w[m] == 0x0000001f ){
/*通常弾発射*/
					if ( tama_ft[m] == 1 ){
						if ( !pcm_flg ) NNPLAY(se00, 3*256+3, sizeof(se00) );
						if ( m & 1 ) tama_vt[m] = (int)SRCH32( my.x, my.y, dan[m].x, dan[m].y );
							   else tama_vt[m] = (int)SRCHRND( my.x, my.y, dan[m].x, dan[m].y );
						dan[m].id = 1;
					} else {
/*レーザー本体消滅*/
						if ( tama_ft[m] == 3 ){
							tama_ft[m] = 0;
							SP_APS(tama_pl[m],511,511,256,0);
						} else {
/*レーザー何もしない*/
							if ( tama_ft[m] == 4 ){
								switch ( tama_wk0[m] ){
									case 0:SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_ptn0[tama_vt[m]],1);
										break;
									case 7:SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_ptn2[tama_vt[m]],1);
										break;
									default:SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_ptn1[tama_vt[m]],1);
										break;
								}
								switch ( tama_lvl[m] ){
									case 2:
										dan[m].x += x_buffC[tama_vt[m]<<1][tpv[m]];
										dan[m].y += y_buffC[tama_vt[m]<<1][tpv[m]];
										break;
									case 3:
										dan[m].x += x_buffD[tama_vt[m]<<1][tpv[m]];
										dan[m].y += y_buffD[tama_vt[m]<<1][tpv[m]];
										break;
								}
								tpv[m]++;
							} else {
/*３２方向弾発射*/
								if ( tama_ft[m] == 2 ){
									for ( n=0; n<32; n++ ){
										direct__16( n, dan[m].x, dan[m].y, t2s[level] );
									}
									NNPLAY(se01, 3*256+3, sizeof(se01));
									pcm_flg = 1;
									tama_ft[m] = dan[m].id = 0;
									SP_APS(tama_pl[m],511,511,256,0);
								} else {
/*１６方向弾発射*/
									if ( tama_ft[m] == 5 ){
										for ( n=0; n<16; n++ ){
											direct__16( n*2, dan[m].x, dan[m].y, t2s[level] );
										}
										SP_APS(tama_pl[m],511,511,256,0);
										tama_ft[m] = dan[m].id = 0;
										NNPLAY(se01, 3*256+3, sizeof(se01));
										pcm_flg = 1;
									} else {
/*レーザークリスタル消滅と本体発生*/
										if ( tama_ft[m] == 6 ){
											tama_ft[m] = 3;
											tpv[m] = 0;
											tama_w[m] = 0;
										} else {
/*スプリンクラー消滅*/
											if ( tama_ft[m] == 10 ){
												tama_ft[m] = 0;
												SP_APS(tama_pl[m],511,511,256,0);
											} else {
/*花火消滅*/
												if ( tama_ft[m] == 20 ){
													tama_ft[m] = 0;
													SP_APS(tama_pl[m],511,511,256,0);
												} else {
/*ホーミング*/
													if ( tama_ft[m] == 30 ){
														tama_ft[m] = 31;
														tpv[m] = 0;
														tama_vt[m] = (int)SRCHRND( my.x, my.y, dan[m].x, dan[m].y );
														if ( m&1 ){;
															if ( tama_vt[m] < 16 ) tama_vt[m]+=16; else tama_vt[m]-=16;
														}
														tama_w[m] = 0x20;
														tama_w0[m] = 0;
														tama_w1[m] = 0;
														dan[tama_p].xs = dan[tama_p].ys = 2;
														dan[m].id = 1;
														if ( !pcm_flg ) NNPLAY(se00, 3*256+3, sizeof(se00) );
													}
												}
											}
										}
									}
								}
							}
						}
					}
				} else {
/*以下、予告パターン発生より tama_w が 0x0000001f より小さい場合の処理*/
					if ( tama_ft[m] == 1 ){
						SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,0x0718+(tama_w[m]>>3),1);
					} else {
						if ( tama_ft[m] == 3 ){
							SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,laser_moto[tama_w[m]>>2],1);
							if ( tama_w[m] == 8 ){					/*レーザーの発生*/
								n = SRCH16N( my.x, my.y, dan[m].x, dan[m].y );
								o = t3s[level];
								p = laser_psx[n];
								q = laser_psy[n];
								j = 0;
								r = tama_p;
								for ( i=0; i<8; i++ ){				/*確保可能か確認*/
									if ( !tama_ft[r] ){
										j++;
										r++;
										if ( r > 127 ) r = 4;
									}
								}
								if ( j == 8 ){
									for ( i=0; i<8; i++ ){
										if ( !tama_ft[tama_p] ){
											j++;
											tama_pl[tama_p] = tama_p;
											tpv[tama_p] = 0;
											dan[tama_p].x = dan[m].x+p;
											dan[tama_p].y = dan[m].y+q;
											tama_ft[tama_p]  = 4;
											tama_vt[tama_p] = n;
											tama_w[tama_p] = 0x00000020-(i*2);
											tama_lvl[tama_p] = o;
											tama_wk0[tama_p] = i;
											dan[tama_p].id = 1;
											dan[tama_p].xs = dan[tama_p].ys = 2;
											tama_p++;
											if ( tama_p > 127 ) tama_p = 4;
										}
									}
									NNPLAY(se03, 3*256+3, sizeof(se03));
									pcm_flg = 1;
								}
							}
						} else {
							if ( tama_ft[m] == 10 ){
								if ( tama_w[m] == -128-2 ){
									tama_w0[m] = SRCH16N( my.x, my.y, dan[m].x, dan[m].y );
								}
								if ( tama_w[m] > -128 ){
									if ( tama_w1[m]++ > 3 ){
										direct__16( tama_w0[m]<<1, dan[m].x, dan[m].y, t5s[level] );
										tama_w1[m] = 0;
										tama_w0[m]++;
										if ( tama_w0[m] > 15 ) tama_w0[m] = 0;
										if ( !pcm_flg ) NNPLAY(se00, 3*256+3, sizeof(se00) );
									}
								}
							} else {
								if ( tama_ft[m] == 20 ){
									switch ( tama_w[m] ){
									case -75:
										for ( i=0; i<32; i++ ){
											direct__16( i, dan[m].x, dan[m].y, t6s[level] );
										}
										NNPLAY(se00, 3*256+3, sizeof(se00) );
										break;
									case -60:
										for ( i=0; i<16; i++ ){
											direct__16( i<<1, dan[m].x, dan[m].y, 0 );
										}
										NNPLAY(se00, 3*256+3, sizeof(se00) );
										break;
									case -45:
										for ( i=0; i<16; i++ ){
											direct__16( (i<<1)+1, dan[m].x, dan[m].y, t6s[level] );
										}
										NNPLAY(se00, 3*256+3, sizeof(se00) );
										break;
									case -30:
										for ( i=0; i<16; i++ ){
											direct__16( i<<1, dan[m].x, dan[m].y, t6s[level] );
										}
										NNPLAY(se00, 3*256+3, sizeof(se00) );
										break;
									case -15:
										for ( i=0; i<16; i++ ){
											direct__16( (i<<1)+1, dan[m].x, dan[m].y, t6s[level] );
										}
										NNPLAY(se00, 3*256+3, sizeof(se00) );
										break;
									case -1:
										direct_16( dan[m].x, dan[m].y, 3 );
										NNPLAY(se00, 3*256+3, sizeof(se00) );
										break;
									}
								}
							}
						}
					}
				}
				tama_w[m]++;
			}
			m++;
		} else {
			m++;
		}
	}
}
/********************************************************************************************/
void direct_16( WORD xx, WORD yy, int lvl )
{
	if ( !tama_ft[tama_p] ){
		tama_pl[tama_p] = tama_p;
		tpv[tama_p] = 0;
		dan[tama_p].x = xx;
		dan[tama_p].y = yy;
		dan[tama_p].id = 0;
		tama_ft[tama_p]  = 1;
		tama_w[tama_p] = 0;
		tama_lvl[tama_p] = lvl;
		SP_APS(tama_pl[tama_p],xx+8,yy+8,0x0718,1);
		tama_p++;
		if ( tama_p > 127 ) tama_p = 4;
	}
}
/********************************************************************************************/
void direct__16( int v, WORD xx, WORD yy, int lvl )
{
	if ( !tama_ft[tama_p] ){
		tama_pl[tama_p] = tama_p;
		tpv[tama_p] = 0;
		dan[tama_p].x = xx;
		dan[tama_p].y = yy;
		tama_ft[tama_p]  = 1;
		tama_vt[tama_p] = v;
		tama_w[tama_p] = 0x00000020;
		tama_lvl[tama_p] = lvl;
		dan[tama_p].id = 1;
		SP_APS(tama_pl[tama_p],xx+8,yy+8,0x0718,1);
		tama_p++;
		if ( tama_p > 127 ) tama_p = 4;
	}
}
/********************************************************************************************/
void score_put( UWORD ssa )
{
	UBYTE c[5+1];
	UBYTE strtmp[32];

	b_strncpy(sizeof(c),c,b_itoa(strtmp,ssa));
	if( ssa > 999 & ssa < 10000 ){
		c[4]= c[3];
		c[3]= c[2];
		c[2]= c[1];
		c[1]= c[0];
		c[0]= 0x57;
	} else {
		if( ssa > 99 & ssa < 1000 ){
			c[4]= c[2];
			c[3]= c[1];
			c[2]= c[0];
			c[1]= 0x57;
			c[0]= 0x57;
		} else {
			if( ssa > 9  & ssa < 100  ){
				c[4]= c[1];
				c[3]= c[0];
				c[2]= 0x57;
				c[1]= 0x57;
				c[0]= 0x57;
			} else {
				if( ssa < 10 ){
					c[4]= c[0];
					c[3]= 0x57;
					c[2]= 0x57;
					c[1]= 0x57;
					c[0]= 0x57;
				}
			}
		}
	}
	bg_put(0,10,31,(c[4]-0x30)|0x500);
	bg_put(0, 9,31,(c[3]-0x30)|0x500);
	bg_put(0, 8,31,(c[2]-0x30)|0x500);
	bg_put(0, 7,31,(c[1]-0x30)|0x500);
	bg_put(0, 6,31,(c[0]-0x30)|0x500);
	old_score = score;
}
void para_put( int x, int y, int s0, int pl )
{
	UBYTE c0[6];
	UBYTE str0[32];
	b_strncpy(sizeof(c0),c0,b_itoa(str0,s0));
	if ( !s0 ){
		c0[4] = '0';
		c0[3] = 0x57;
		c0[2] = 0x57;
		c0[1] = 0x57;
		c0[0] = 0x57;
	} else {
		if( s0 >= 1000  & s0 <= 9999 ){
			c0[4] = c0[3];
			c0[3] = c0[2];
			c0[2] = c0[1];
			c0[1] = c0[0];
			c0[0] = 0x57;
		} else {
			if( s0 >= 100  & s0 <= 999 ){
				c0[4] = c0[2];
				c0[3] = c0[1];
				c0[2] = c0[0];
				c0[1] = 0x57;
				c0[0] = 0x57;
			} else {
				if( s0 >= 10  & s0 <= 99 ){
					c0[4] = c0[1];
					c0[3] = c0[0];
					c0[2] = 0x57;
					c0[1] = 0x57;
					c0[0] = 0x57;
				} else {
					if( s0 <= 9 ){
						c0[4] = c0[0];
						c0[3] = 0x57;
						c0[2] = 0x57;
						c0[1] = 0x57;
						c0[0] = 0x57;
					}
				}
			}
		}
	}
	bg_put(pl,x+4, y,(c0[4]-0x30)|0x500);
	bg_put(pl,x+3, y,(c0[3]-0x30)|0x500);
	bg_put(pl,x+2, y,(c0[2]-0x30)|0x500);
	bg_put(pl,x+1, y,(c0[1]-0x30)|0x500);
	bg_put(pl,x,   y,(c0[0]-0x30)|0x500);
}
/***********************************パレットを暗くする***************************************/
void palet_dark( UWORD *pn )
/*
0000_0000_0000_0000
1111 1					green
0000 0111 11			red
0000 0000 0011 111		blue
*/
{
UWORD green,red,blue;
	green = *pn & 0xf800;
	red   = *pn & 0x07c0;
	blue  = *pn & 0x003e;
	if ( green < 0x0800 ) green = 0x0001;
		else green -= 0x0800;
	if ( red   < 0x0040 ) red   = 0x0001;
		else red   -= 0x0040;
	if ( blue  < 0x0002 ) blue  = 0x0001;
		else blue  -= 0x0002;
	*pn =  green | red;
	*pn = *pn | blue;
}
/***********************************パレットを明るく*****************************************/
void palet_light( UWORD *pa, UWORD *pb )
/*
*pa...変換させるパレットのアドレス
*pb...一番明るくなった時のパレットのアドレス
0000_0000_0000_0000
1111 1					green
0000 0111 11			red
0000 0000 0011 111		blue
0000 0000 0000 0001		輝度ビット
*/
{
UWORD greena,reda,bluea,greenb,redb,blueb;

	greena = *pa & 0xf800;
	reda   = *pa & 0x07c0;
	bluea  = *pa & 0x003e;
	greenb = *pb & 0xf800;
	redb   = *pb & 0x07c0;
	blueb  = *pb & 0x003e;

	if ( greena < greenb ) greena += 0x0800;
	if ( reda   < redb   ) reda   += 0x0040;
	if ( bluea  < blueb  ) bluea  += 0x0002;

	*pa =  greena | reda;
	*pa = *pa | bluea;
}
/********************************************************************************************/
void dat_write( char *filename, char *pcmname, UWORD pcmlen )
{
	int i;
	FILE *fp;

	if ( !((fp = fopen( filename, "wb" )) == (FILE*)NULL) ){
		if ( fwrite( pcmname, 1, pcmlen, fp ) != pcmlen ){
			bgmes(18,23,5,"WRITE ERR",0);
			NNPLAY(se02, 3*256+3, sizeof(se02) );
			i = 400000; while ( i-- );
			bgmes(18,23,5,"         ",0);
		} else {
			bgmes(18,23,5,"OK",0);
			i = 400000; while ( i-- );
			bgmes(18,23,5,"  ",0);
		}
		fclose( fp );
	} else {
		bgmes(18,23,5,"OPEN ERR",0);
		NNPLAY(se02, 3*256+3, sizeof(se02) );
		i = 400000; while ( i-- );
		bgmes(18,23,5,"        ",0);
	}
}
/********************************************************************************************/
void put_star()
{
	int i,j,k;
	for( i = 1; i < 4; i++ ){
		apage( i );
		for( j = 0; j <= i*4; j++ ){
			for ( k=1; k<16; k++ ){
				pset((rand()/128),(rand()/32),k);
			}
		}
	}
}
/********************************************************************************************/
void g_scroll0111()		/*スクロール*/
{
	int i;
	asm("
		movem.l	d0-d3/a1,-(sp)
		move.w	#1,d1				*P1
		move.w	#0,d2
		lea.l	yp1,a1
		move.w	(a1),d3
		subq.w	#4,d3		*
		bpl	y02_skip
		move.w	#1024,d3
	y02_skip:
		move.w	d3,(a1)
		asr.w	#1,d3
		iocs	_SCROLL

		move.w	#2,d1				*P2
		move.w	$2(a1),d3
		subq.w	#2,d3		*
		bpl	y03_skip
		move.w	#1024,d3
	y03_skip:
		move.w	d3,$2(a1)
		asr.w	#1,d3
		iocs	_SCROLL

		move.w	#3,d1				*P3
		move.w	$4(a1),d3
		subq.w	#1,d3		*
		bpl	y04_skip
		move.w	#1024,d3
	y04_skip:
		move.w	d3,$4(a1)
		asr.w	#1,d3
		iocs	_SCROLL
		movem.l	(sp)+,d0-d3/a1
	");

	if ( !mei0 ){
		palet_dark( &d_pal[1] );
		palet_dark( &d_pal[2] );
		palet_dark( &d_pal[3] );
		palet_dark( &d_pal[4] );
		palet_dark( &d_pal[5] );
		meic0 = 0;
		if ( meicc0++ > 30 ){
			mei0 = 1;
			meicc0 = 0;
		}
	} else {
		palet_light( &d_pal[1],&star_pal[1] );
		palet_light( &d_pal[2],&star_pal[2] );
		palet_light( &d_pal[3],&star_pal[3] );
		palet_light( &d_pal[4],&star_pal[4] );
		palet_light( &d_pal[5],&star_pal[5] );
		meic0 = 0;
		if ( meicc0++ > 30 ){
			mei0 = meicc0 = 0;
		}
	}


	if ( !mei1 ){
		palet_dark( &d_pal[6] );
		palet_dark( &d_pal[7] );
		palet_dark( &d_pal[8] );
		palet_dark( &d_pal[9] );
		palet_dark( &d_pal[10] );
		meic1 = 0;
		if ( meicc1++ > 30 ){
			mei1 = 1;
			meicc1 = 0;
		}
	} else {
		palet_light( &d_pal[6],&star_pal[6] );
		palet_light( &d_pal[7],&star_pal[7] );
		palet_light( &d_pal[8],&star_pal[8] );
		palet_light( &d_pal[9],&star_pal[9] );
		palet_light( &d_pal[10],&star_pal[10] );
		meic1 = 0;
		if ( meicc1++ > 30 ){
			mei1 = meicc1 = 0;
		}
	}


	if ( !mei2 ){
		if ( meic2++ > 0 ){
			palet_dark( &d_pal[11] );
			palet_dark( &d_pal[12] );
			palet_dark( &d_pal[13] );
			palet_dark( &d_pal[14] );
			palet_dark( &d_pal[15] );
			meic2 = 0;
			if ( meicc2++ > 20 ){
				mei2 = 1;
				meicc2 = 0;
			}
		}
	} else {
		palet_light( &d_pal[11],&star_pal[11] );
		palet_light( &d_pal[12],&star_pal[12] );
		palet_light( &d_pal[13],&star_pal[13] );
		palet_light( &d_pal[14],&star_pal[14] );
		palet_light( &d_pal[15],&star_pal[15] );
		meic2 = 0;
		if ( meicc2++ > 30 ){
			mei2 = meicc2 = 0;
		}
	}
	SAC_COLOR3( &d_pal[0] );
}
/********************************************************************************************/
void hit_put( int i )
{
	switch ( i ){
		case 0:
			bgmes(14,31,5,"      ",0);
			break;
		case 1:
			bg_put(0,18,31,0x0425);
			bg_put(0,19,31,0x0426);
			break;
		case 2:
			bg_put(0,16,31,0x0425);
			bg_put(0,17,31,0x0426);
			break;
		case 3:
			bg_put(0,14,31,0x0425);
			bg_put(0,15,31,0x0426);
			break;
	}
	old_hit_cnt = hit_cnt;
}
