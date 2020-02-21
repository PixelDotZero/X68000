#include	<stdio.h>
#include	<stdlib.h>
#include	<basic.h>
#include	<class.h>
#include	<graph.h>
#include	<music.h>
#include	<audio.h>
#include	<sprite.h>
#include	<iocslib.h>

#define		DUMMY 256
#define		SHOT_BANG 1
#define		NL 'NASI'
#define		START_LOGO_NUM	0x0e38
#define		CORE_NUM		0x0076
#define		SMOKE_NUM		0x0071





struct GEAS {
	char		id,
				atr,
				xs,
				ys;
	WORD		x,
				y;
};

void	direct16( UBYTE, WORD, UWORD );
void	direct_16( WORD, WORD, UWORD );
void	direct_16r( WORD, WORD, UWORD );
void	direct__16( UBYTE, WORD, WORD, UWORD );
void	tama();
void	jiki();
void	teki();
void	t_move();
void	check();
void	haikei_put();
void	g_scroll();
void	enemy_load( char* );
void	pfree( UBYTE*, UBYTE );
UBYTE	palloc( UBYTE*, UBYTE*, UBYTE );
UBYTE	pcm_load( char*, UBYTE*, UWORD );
void	pcmplay( UBYTE*, UWORD );
void	pause();
void	wait( UBYTE );
UBYTE	disp32();
void	emyload( WORD*, char* );
void	pat_load( char*, UBYTE*, UBYTE );
void	spp_load( char* );
void	spl_load( char* );
void	TEXSCROLL( WORD, WORD );
UBYTE	ESCSNS( void );
UBYTE	SPCSNS( void );
UBYTE	XF3SNS( void );
UBYTE	OP1SNS( void );
UBYTE	TRIGGER( void );
void	SP_APSV( UBYTE, WORD, WORD, UWORD, UBYTE );
void	SP_APS( UBYTE, WORD, WORD, UWORD, UBYTE );
UBYTE	SRCH16( WORD, WORD, WORD, WORD );
UBYTE	SRCH16N( WORD, WORD, WORD, WORD );
UBYTE	SRCH32( WORD, WORD, WORD, WORD );
int		ATARI( WORD, WORD, WORD, WORD, WORD, WORD, WORD, WORD );
int		ATARIQ( WORD, WORD, WORD, WORD, WORD, WORD, WORD, WORD );
int		STICK_INP( int );
int		act2( struct GEAS*, struct GEAS*, int* );
void	hodai3( UBYTE );
void	back_atc_zako( UBYTE );
void	NNPCMON( void );
void	NNPCMOFF( void );
void	NNINIT( void );
void	NNPLAY( int, WORD, WORD );
void	NNSTOP( void );
int		NNSTAT( void );
void	teki_set( void );
void	copykey( void );
void	breakkey( void );





EXTERN struct GEAS my;			/*自機*/
EXTERN struct GEAS mys[32];	/*自機の弾*/
EXTERN struct GEAS you[32];	/*敵*/
EXTERN struct GEAS dan[32];	/*敵の弾*/
EXTERN int you_p, dan_p;
EXTERN UBYTE sp_lvl0, sp_lvl1, sp_lvl2, sp_lvl3;	/*プレーンポインタ*/
EXTERN UBYTE stc_pl0, stc_pl1, stc_pl2, stc_pl3;	/*使用可能プレーン数*/
EXTERN UBYTE stc_mx0, stc_mx1, stc_mx2, stc_mx3;	/*使用可能プレーン最大数*/
EXTERN UBYTE pl_tbl[128];							/* プレーン使用状況テーブル */
EXTERN WORD enemy_tbl[1500];
EXTERN WORD ppp,pp0,pp1,pp2,pp3,pp4,pp5;
EXTERN WORD jiki_f;				/*自機のフラグ*/
EXTERN WORD jiki_xx, jiki_yy;		/*自機座標のダミー値*/
EXTERN WORD j_stock,j_stock_old;	/*残機数*/
EXTERN char stick_ptn;
EXTERN UBYTE jiki_fire,jiki_fire_cnt;
EXTERN WORD jiki_p;				/*自機キャラパターン*/
EXTERN WORD speed;					/*自機の移動スピード*/
EXTERN WORD speed_flg;				/*増加減少フラグ*/
EXTERN WORD trig_flg;				/*トリガーのフラグ*/
EXTERN WORD tama_ptn;				/*自機ショットのパターン*/
EXTERN UBYTE shot_pow,dshot_pow;	/*自機ショットの強さ*/
EXTERN WORD t_f[12];			/*自機ショットのフラグ*/
EXTERN WORD tb_f[12];			/*自機ショット爆発のフラグ*/
EXTERN WORD tb_cnt[12];		/*自機ショット爆発のカウンタ*/
EXTERN char trig1_flg;			/*トリガー１のフラグ*/
EXTERN WORD pp[32];			/*敵移動配列のポインタ*/
EXTERN char pcm0_f,pcm1_f;
EXTERN UWORD score, old_score;
EXTERN UBYTE powup00[4863],powup01[2559],atari00[511],atari01[1023];			/* ＰＣＭバッファ */
EXTERN UBYTE bang00[4095],bang01[4351],bang02[2047],bang03[7167],bang04[2282];
EXTERN UBYTE gooo1[46847],gooo2[45823],clp[928];
EXTERN WORD wk0, wk1;
EXTERN char teki_ft[32];
EXTERN int teki_xx[32], teki_yy[32];	/*敵座標値*/
EXTERN WORD teki_dmg[32];			/*敵の固さ*/
EXTERN WORD teki_bcnt[32];			/*敵の爆発カウンタ*/
EXTERN int teki_ptn[32];			/*敵のキャラ番号*/
EXTERN UBYTE teki_pl[32];			/*敵のプレーンNo.*/
EXTERN UBYTE teki_dsp;				/*出現中の敵数*/
EXTERN UBYTE teki_num;				/*敵のポインタ*/
EXTERN WORD teki_wk0[32],teki_wk1[32],teki_wk2[32],teki_wk3[32],teki_wk4[32];
EXTERN WORD teki_wk5[32][16],teki_wk6[32][16];
EXTERN UBYTE hmtbl[16][16];
EXTERN UWORD hm_ptn[16];
EXTERN WORD tama_tbl[20];
EXTERN UWORD bang_ptbl1[20];
EXTERN WORD tama_x[32], tama_y[32], tama_vt[32], tama_ft[32], tpv[32], tama_atr[32], tama_col;
EXTERN UBYTE tama_pl[32];
EXTERN char x_buff[32][300],y_buff[32][300];	/*32方向のバッファ*/
EXTERN char tama_p;
EXTERN UBYTE tama_tp,tama_color,tama_color_cnt;
EXTERN char twk_f,twk_n,kwk_f,kwk_n;
EXTERN WORD p,main_cnt;
EXTERN UWORD start_logo_pal[52];
EXTERN UWORD arm_up[10][50],arm_down[10][50];
EXTERN char cloud_B0[2048],cloud_B1[3072],cloud_B2[2048],cloud_B3[2048];
EXTERN char cloud_T0[3072],cloud_T1[3584],cloud_T2[3584],cloud_T3[640];
EXTERN char cloud_BG[12288],ship_body_u[7168],ship_body_d[7168];
EXTERN WORD bgx,bgx_d;
EXTERN WORD core_x,core_y;
EXTERN WORD gp0,gp1,gp2,gp3;
EXTERN WORD sys_bg_x,sys_bg_x_d,sys_bg0_y,sys_bg1_y,gbs_xx,gbs_yy0,gbs_yy1;
EXTERN UBYTE boss;
EXTERN UBYTE start_logo_x[10],start_logo_y[10];
EXTERN WORD gbs_mov[512];
EXTERN char x2y2_x[4],x2y2_y[4];
EXTERN UWORD ship_body_pal[16];
EXTERN char core_ptn[5][256], smoke_ptn[6][256], jiki_ptn[8][256];
EXTERN WORD body_x,body_y;									/* ＧＢＳ本体中心（コア）座標 */
EXTERN UWORD hodai_ptn[5];
EXTERN char hodai_dir[32];
EXTERN UWORD contena_d_ptn[8],contena_u_ptn[8];
EXTERN char contena_x[8],contena_y[8];
EXTERN WORD arm_y;
EXTERN INT jiki_d,muteki_time,jiki_bcnt;
EXTERN WORD ship_bang_color[16];
EXTERN UWORD bang_tbl2[3][12];
EXTERN char bang_x[3][12],bang_y[3][12],INTFLG;

