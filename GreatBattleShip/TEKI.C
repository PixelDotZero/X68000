#include	"GREAT.H"

static char x2y2[8]={0,0,0,16,16,0,16,16};
static char core_anime[8]={0,1,2,3,4,3,2,1};
static WORD tyoku_zako_ptn[8]={
	0x0361,0x8361,0x0362,0x8362,
	0x0361,0x8361,0x0363,0x8363
};
static WORD back_zako_ptn[8]={
	0x035b,0x035c,0x035d,0x035e,
	0x035f,0x0360,0x835d,0x835e
};
WORD ship_bang_color[16]={
	0x0000,0xfff2,0xefe2,0xd7dc,0xbfce,0xb7d4,0xafc0,0xa7c0,
	0x97c0,0x7f40,0x7700,0x5680,0x4580,0x2d80,0x058e,0x5640
};



void teki()
{
	UBYTE m = 0, k = 0;
	WORD i, j, n, w, v;

	while ( m < 32 ){
		if ( teki_ft[m] ){
			switch ( teki_ptn[m] ){

/* ＳＴＡＲＴロゴ */
			case 0:
				w = teki_pl[m];
				for ( i = 0; i < 10; i++ ){
					SP_APS(w,start_logo_x[i],start_logo_y[i],START_LOGO_NUM+i,3);
					w = pl_tbl[w];
				}
				sp_color( 1,start_logo_pal[teki_wk5[m][0]--],14);
				sp_color( 2,start_logo_pal[teki_wk5[m][1]--],14);
				sp_color( 3,start_logo_pal[teki_wk5[m][2]--],14);
				sp_color( 4,start_logo_pal[teki_wk5[m][3]--],14);
				sp_color( 5,start_logo_pal[teki_wk5[m][4]--],14);
				sp_color( 6,start_logo_pal[teki_wk5[m][5]--],14);
				sp_color( 7,start_logo_pal[teki_wk5[m][6]--],14);
				sp_color( 8,start_logo_pal[teki_wk5[m][7]--],14);
				sp_color( 9,start_logo_pal[teki_wk5[m][8]--],14);
				sp_color(10,start_logo_pal[teki_wk5[m][9]--],14);
				for ( i = 0; i < 10; i++ )
					if ( teki_wk5[m][i] == -1 ) teki_wk5[m][i] = 51;
				if ( teki_wk0[m]++ > pp[m] ){
					teki_ft[m] = 0;
					teki_dsp--;
					pfree( &stc_pl1, teki_pl[m] );
				}
				break;



/* グレイト・バトル・シップ
wk0:ＢＧの表示・消去のＸ座標ポインタ
wk1:ＢＧへ表示するパターンデータのポインタ
wk2:ダメージ色
ppp: 移動・アーム開閉データへのポインタ
pp0:移動速度
pp1:本体移動方向
pp2:アーム開閉

			<<<データフォーマット>>>
				gbs_mov[64]={ A, B, C, D, E,......
				A...メインカウント  
				B...移動速度
				C...本体移動方向    0:停止  4:左  6:右  8:上  2:下
				                    7:左上  1:左下  9:右上  3:右下
				D...アーム開閉      0:そのまま  1:閉じる  2:開く
				E...敵キャラ番号（発生させない時は -1 ）
*/
				case 1:


					if ( !boss ){
						if ( gbs_mov[ppp] == main_cnt ){
							pp0 = gbs_mov[ ppp + 1 ];
							pp1 = gbs_mov[ ppp + 2 ];
							pp2 = gbs_mov[ ppp + 3 ];
							ppp += 5;
						}
					} else {
						pp0 = 4;
						pp1 = 3;
						pp2 = 0;
						if ( (core_y>>4) > 300 ){
							bg_set( 0, 0, 0 );
							bg_set( 1, 1, 0 );
							body_x = body_y = 0;
							pp0 = 0;
							pp1 = 0;
							boss = 0xff;
						}
					}

					if ( pp2 == 1 ){
						gbs_yy0 += 2;
						gbs_yy1 -= 2;
						arm_y += 2;
						if ( gbs_yy0 >= 8192 ) gbs_yy0 = 0;
						if ( gbs_yy1 <=   -1 ) gbs_yy1 = 8191;
					}
					if ( pp2 == 2 ){
						gbs_yy0 -= 2;
						gbs_yy1 += 2;
						arm_y -= 2;
						if ( gbs_yy1 >= 8192 ) gbs_yy1 = 0;
						if ( gbs_yy0 <=   -1 ) gbs_yy0 = 8191;
					}
					switch ( pp1 ){
						case 4:
								gbs_xx += pp0;
								body_x += pp0;
								core_x -= pp0;break;
						case 6:
								gbs_xx -= pp0;
								body_x -= pp0;
								core_x += pp0;break;
						case 2:
								gbs_yy0 -= pp0;
								gbs_yy1 -= pp0;
								body_y  -= pp0;
								core_y  += pp0;break;
						case 8:
								gbs_yy0 += pp0;
								gbs_yy1 += pp0;
								body_y  += pp0;
								core_y  -= pp0;break;
						case 7:
								gbs_xx  += pp0;
								body_x  += pp0;
								body_y  += pp0;
								gbs_yy0 += pp0;
								gbs_yy1 += pp0;
								core_x  -= pp0;
								core_y  -= pp0;break;
						case 1:
								gbs_xx  += pp0;
								body_x  += pp0;
								body_y  -= pp0;
								gbs_yy0 -= pp0;
								gbs_yy1 -= pp0;
								core_x  -= pp0;
								core_y  += pp0;break;
						case 9:
								gbs_xx  -= pp0;
								body_x  -= pp0;
								body_y  += pp0;
								gbs_yy0 += pp0;
								gbs_yy1 += pp0;
								core_x  += pp0;
								core_y  -= pp0;break;
						case 3:
								gbs_xx  -= pp0;
								body_x  -= pp0;
								body_y  -= pp0;
								gbs_yy0 -= pp0;
								gbs_yy1 -= pp0;
								core_x  += pp0;
								core_y  += pp0;break;
					}
					if ( gbs_yy0 >= 8192 ) gbs_yy0 = 0;
					if ( gbs_yy1 <=   -1 ) gbs_yy1 = 8191;
					if ( gbs_yy1 >= 8192 ) gbs_yy1 = 0;
					if ( gbs_yy0 <=   -1 ) gbs_yy0 = 8191;
					sys_bg_x  = gbs_xx  >> 4;
					sys_bg0_y = gbs_yy0 >> 4;
					sys_bg1_y = gbs_yy1 >> 4;

					if ( sys_bg_x == sys_bg_x_d-8 || sys_bg_x == sys_bg_x_d+504 ){
						sys_bg_x_d = sys_bg_x;
						bg_put(0,teki_wk0[m],0,0x200);bg_put(0,teki_wk0[m],1,0x200);
						bg_put(0,teki_wk0[m],2,0x200);bg_put(0,teki_wk0[m],3,0x200);
						bg_put(0,teki_wk0[m],4,0x200);bg_put(0,teki_wk0[m],5,0x200);
						bg_put(0,teki_wk0[m],6,0x200);bg_put(0,teki_wk0[m],7,0x200);
						bg_put(0,teki_wk0[m],8,0x200);bg_put(0,teki_wk0[m],9,0x200);
						bg_put(1,teki_wk0[m],0,0x200);bg_put(1,teki_wk0[m],1,0x200);
						bg_put(1,teki_wk0[m],2,0x200);bg_put(1,teki_wk0[m],3,0x200);
						bg_put(1,teki_wk0[m],4,0x200);bg_put(1,teki_wk0[m],5,0x200);
						bg_put(1,teki_wk0[m],6,0x200);bg_put(1,teki_wk0[m],7,0x200);
						bg_put(1,teki_wk0[m],8,0x200);bg_put(1,teki_wk0[m],9,0x200);
						teki_wk0[m]--;
						if( teki_wk0[m] == -1 ) teki_wk0[m] = 63;
						teki_wk1[m]--;
						/*if ( teki_wk1[m] < 0 ) pcmplay(clp,sizeof(clp));*/

					}
					if( sys_bg_x == sys_bg_x_d+8 || sys_bg_x+504 == sys_bg_x_d ){
						sys_bg_x_d = sys_bg_x;
						teki_wk0[m]++;
						if( teki_wk0[m] == 64 ) teki_wk0[m] = 0;
						bg_put(0,teki_wk0[m],0,arm_up[0][teki_wk1[m]]);bg_put(0,teki_wk0[m],1,arm_up[1][teki_wk1[m]]);
						bg_put(0,teki_wk0[m],2,arm_up[2][teki_wk1[m]]);bg_put(0,teki_wk0[m],3,arm_up[3][teki_wk1[m]]);
						bg_put(0,teki_wk0[m],4,arm_up[4][teki_wk1[m]]);bg_put(0,teki_wk0[m],5,arm_up[5][teki_wk1[m]]);
						bg_put(0,teki_wk0[m],6,arm_up[6][teki_wk1[m]]);bg_put(0,teki_wk0[m],7,arm_up[7][teki_wk1[m]]);
						bg_put(0,teki_wk0[m],8,arm_up[8][teki_wk1[m]]);bg_put(0,teki_wk0[m],9,arm_up[9][teki_wk1[m]]);
						bg_put(1,teki_wk0[m],0,arm_down[0][teki_wk1[m]]);bg_put(1,teki_wk0[m],1,arm_down[1][teki_wk1[m]]);
						bg_put(1,teki_wk0[m],2,arm_down[2][teki_wk1[m]]);bg_put(1,teki_wk0[m],3,arm_down[3][teki_wk1[m]]);
						bg_put(1,teki_wk0[m],4,arm_down[4][teki_wk1[m]]);bg_put(1,teki_wk0[m],5,arm_down[5][teki_wk1[m]]);
						bg_put(1,teki_wk0[m],6,arm_down[6][teki_wk1[m]]);bg_put(1,teki_wk0[m],7,arm_down[7][teki_wk1[m]]);
						bg_put(1,teki_wk0[m],8,arm_down[8][teki_wk1[m]]);bg_put(1,teki_wk0[m],9,arm_down[9][teki_wk1[m]]);
						teki_wk1[m]++;
						if ( teki_wk1[m] > 49 ){
							/*pcmplay(clp,sizeof(clp));*/
							teki_wk1[m]--;
						}
					}
					break;

/* コア LVL1
wk0:パターン定義カウンタ(0~32)
wk1:移動フラグ 0...出現から合体まで（左へ移動）  1..全体と同等に移動
wk2:ダメージ色
wk3:
wk4:
*/
			case 2:
					sp_def( CORE_NUM, &core_ptn[core_anime[teki_wk0[m]>>2]][0], 1 );
					teki_wk0[m]++;
					if ( teki_wk0[m] >= 32 ) teki_wk0[m] = 0;
					if ( teki_dmg[m] > 0 ){
						switch ( teki_wk1[m] ){
							case 0:
								you[m].x++;
								if ( you[m].x >= 256-8 ){
									teki_wk1[m] = 1;
									you[m].x = core_x>>4;
									you[m].y = core_y>>4;
								}
								break;
							case 1:
								you[m].x = core_x>>4;
								you[m].y = core_y>>4;
								if ( main_cnt > 10000 ) you[m].id = 1;
								break;
						}
						SP_APS(teki_pl[m],you[m].x+8,you[m].y+8,CORE_NUM|0x0400,3 );
					} else {
						boss = 1;
						you[m].id = 0;
						you[m].x++;
						SAC_COLOR2( 0, ship_bang_color );
						SAC_COLOR2( 2, ship_bang_color );
						SP_APS(teki_pl[m],you[m].x+8,you[m].y+8,CORE_NUM|0x400,3 );
						if ( you[m].x > 256+8 ){
							pfree( &stc_pl1, teki_pl[m] );
							teki_dsp--;
							teki_ft[m] = 0;
						}
					}
					break;

/* 砲台 LVL3
wk0:パターン番号
wk1:弾発射カウンタ
wk2:ダメージ色
wk3:ＧＢＳ本体Ｘ座標
wk4:ＧＢＳ本体Ｙ座標
*/
			case 3:
					if ( teki_wk3[m] > (core_x>>4) ){
						teki_wk3[m] = core_x>>4;
						you[m].x--;
					} else {
						if ( teki_wk3[m] < (core_x>>4) ){
							teki_wk3[m] = core_x>>4;
							you[m].x++;
						}
					}
					if ( teki_wk4[m] > (core_y>>4) ){
						teki_wk4[m] = core_y>>4;
						you[m].y--;
					} else {
						if ( teki_wk4[m] < (core_y>>4) ){
							teki_wk4[m] = core_y>>4;
							you[m].y++;
						}
					}
					if ( teki_dmg[m] > 0 ){
						teki_wk0[m]=hodai_ptn[hodai_dir[SRCH32(my.x,my.y,you[m].x,you[m].y)]];
						SP_APS(teki_pl[m],you[m].x+8,you[m].y+8,teki_wk0[m]|teki_wk2[m],3 );
						if ( teki_wk2[m] ) teki_wk2[m] = 0x0000;
						if ( teki_wk1[m]-- < 0 ){
							teki_wk1[m] = 500;
							direct_16( you[m].x, you[m].y, 0x007e );
						}
					} else {
						if ( teki_bcnt[m] < 16 ){
							if ( !teki_bcnt[m] ){
								/*if ( !pcm0_f ) pcmplay(bang02,sizeof(bang02));*/
								teki_wk0[m] = 0;
								teki_wk1[m] = 0;
								you[m].id = 0;
							}
							w = teki_pl[m];
							for ( i = 0; i < 4; i++ ){
								SP_APS(w,you[m].x+x2y2[i*2],you[m].y+x2y2[i*2+1],bang_ptbl1[(teki_bcnt[m]>>2)*4+i],3);
								w = pl_tbl[w];
							}
							teki_bcnt[m]++;
							if ( teki_bcnt[m] == 16 ){
								w = teki_pl[m];
								for ( i = 0; i < 4; i++ ){
									SP_APS(w,511,511,DUMMY,0);
									w = pl_tbl[w];
								}
							}
						} else {
							if ( teki_wk1[m]++ > 3 ){
								teki_wk1[m] = 0;
								sp_def( SMOKE_NUM,   &smoke_ptn[teki_wk0[m]][0], 1 );
								sp_def( SMOKE_NUM+1, &smoke_ptn[teki_wk0[m]+1][0], 1 );
								teki_wk0[m] += 2;
								if ( teki_wk0[m] == 6 ) teki_wk0[m] = 0;
							}
							SP_APS(teki_pl[m],        you[m].x+15,you[m].y+8,0x0471,3 );
							SP_APS(pl_tbl[teki_pl[m]],you[m].x+31,you[m].y+8,0x0472,3 );
						}
					}
					break;


/* 特攻ザコ LVL1 */
			case 4: if ( teki_dmg[m] > 0 ){
						you[m].x--;
						if ( teki_wk3[m]++ > 1 ){
							teki_wk0[m] = 4 - teki_wk0[m];
							teki_wk3[m] = 0;
						}
						w = teki_pl[m];
						for ( i = 0; i < 4; i++ ){
							SP_APS(w,you[m].x+x2y2_x[i],you[m].y+x2y2_y[i],tyoku_zako_ptn[i+teki_wk0[m]],3 );
							w = pl_tbl[w];
						}
						if ( !teki_wk1[m]-- ){
							teki_wk1[m] = 200;
							direct__16(24,you[m].x-9,you[m].y+11,0x007f);
							direct__16(24,you[m].x-9,you[m].y-11,0x007f);
						}
						if ( you[m].x < -16 ) {
							w = teki_pl[m];
							for ( i = 0; i < 4; i++ ){
								SP_APS(w,511,511,DUMMY,0 );
								w = pl_tbl[w];
							}
							pp[m] = you[m].id = 0;
							teki_dsp--;
							pfree( &stc_pl1, teki_pl[m] );
							teki_ft[m] = 0;
						}
					} else {
						if ( !teki_bcnt[m] ){
							/*if ( !pcm0_f ) pcmplay(bang02,sizeof(bang02));*/
							you[m].id = 0;
						}
						w = teki_pl[m];
						for ( i = 0; i < 4; i++ ){
							SP_APS(w,you[m].x+x2y2[i*2],you[m].y+x2y2[i*2+1],bang_ptbl1[(teki_bcnt[m]>>2)*4+i],3);
							w = pl_tbl[w];
						}
						teki_bcnt[m]++;
						if ( teki_bcnt[m] > 16 ){
							pfree( &stc_pl1, teki_pl[m] );
							teki_dsp--;
							teki_ft[m] = 0;
						}
					}
					break;





/* コンテナ LVL1
wk0:上下フラグ  0...上  1...下
wk1:離脱カウンタ
wk2:ダメージ色
wk3:離脱後移動フラグ  0...上下斜め  1...左へ  2...追尾
wk4:離脱降下移動カウンタ(220)
wk5[m][0]:アーム移動フラグ
wk5[m][1]:追尾サーチ間隔(30)
wk5[m][2]:追尾方向(24/2)
pp :１６方向移動ポインタ
*/
			case 5:
				contena( m );
					break;

/* 3WAYザコ TYPE2 LVL3 */
			case 8:
					hodai3( m );
					break;

/* Back Attackザコ LVL1 */
			case 10:
					back_atc_zako( m );
					break;

			}
		}
		m++;
	}
}

/********************************************************************************************/


void hodai3( UBYTE m )
{
/* 3WAYザコ TYPE2 LVL3
wk0:Animeation Patern
wk1:Animeation Patern Counter
wk2:ダメージ色
wk3:Move Flag    0...Right 1...Left 2...Stop
wk4:Shot Counter
wk5[m][0]:アーム移動フラグ  arm_y>>4
wk5[m][1]:Max Leftmove point  you[m].x+16
wk5[m][2]:Max Rightmove point you[m].x+16+16*4
wk5[m][3]:teki_wk3[m]saver
wk5[m][4]:My crash counter
teki_xx:core_x>>4
teki_yy:core_y>>4
*/
	WORD w,i;

	if ( teki_dmg[m] > 0 ){
		if ( teki_xx[m] > (core_x>>4) ){
			teki_xx[m] = core_x>>4;
			you[m].x--;
			teki_wk5[m][1]--;
			teki_wk5[m][2]--;
		} else {
			if ( teki_xx[m] < (core_x>>4) ){
				teki_xx[m] = core_x>>4;
				you[m].x++;
				teki_wk5[m][1]++;
				teki_wk5[m][2]++;
			}
		}
		if ( teki_yy[m] > (core_y>>4) ){
			teki_yy[m] = core_y>>4;
			you[m].y--;
		} else {
			if ( teki_yy[m] < (core_y>>4) ){
				teki_yy[m] = core_y>>4;
				you[m].y++;
			}
		}
		if ( teki_wk0[m] == 0 ){
			if ( teki_wk5[m][0] > arm_y>>4 ){
				teki_wk5[m][0] = arm_y>>4;
				you[m].y++;
			} else {
				if ( teki_wk5[m][0] < arm_y>>4 ){
					teki_wk5[m][0] = arm_y>>4;
					you[m].y--;
				}
			}
		} else {
			if ( teki_wk5[m][0] > arm_y>>4 ){
				teki_wk5[m][0] = arm_y>>4;
				you[m].y--;
			} else {
				if ( teki_wk5[m][0] < arm_y>>4 ){
					teki_wk5[m][0] = arm_y>>4;
					you[m].y++;
				}
			}
		}
		if ( !teki_wk4[m]-- ){
			teki_wk1[m] = 0;
			teki_wk5[m][3] = teki_wk3[m];
			teki_wk3[m] = 2;
			teki_wk4[m] = 256;
		}
		teki_wk6[m][0] = 0x0266;			/*パターン設定*/
		teki_wk6[m][1] = 0x0267;
		teki_wk6[m][2] = 0x4266;
		teki_wk6[m][3] = 0x4267;
		switch ( teki_wk3[m] ){
			case 0:
				if ( you[m].x++ > teki_wk5[m][2] )
					teki_wk3[m] = 1;
				break;
			case 1:
				if ( you[m].x-- < teki_wk5[m][1] )
					teki_wk3[m] = 0;
				break;
			case 2:
				teki_wk1[m]++;
				if ( teki_wk1[m] > 30 && teki_wk1[m] < 70 ){
					teki_wk6[m][0] = 0x0266;			/*パターン設定*/
					teki_wk6[m][1] = 0x0268;
					teki_wk6[m][2] = 0x4266;
					teki_wk6[m][3] = 0x4268;
					if ( teki_wk1[m] == 50 ){
						direct__16(13, you[m].x+6, you[m].y,   0x4064);
						direct__16(16, you[m].x,   you[m].y+8, 0x0065);
						direct__16(19, you[m].x-6, you[m].y,   0x0064);
					}
				} else {
					/* Fst patern set */
					if ( teki_wk1[m] > 100 ){
						teki_wk3[m] = teki_wk5[m][3];
					}
				}
				break;
		}
		if ( teki_wk5[m][4]++ > 1024 ) teki_dmg[m] = -1;

		w = teki_pl[m];
		for ( i = 0; i < 4; i++ ){
			SP_APS( w, you[m].x+x2y2[i*2], you[m].y+x2y2[i*2+1], teki_wk6[m][i], 3 );
			w = pl_tbl[w];
		}

	} else {
		if ( !teki_bcnt[m] ){
			you[m].id = 0;
		}
		w = teki_pl[m];
		for ( i = 0; i < 4; i++ ){
			SP_APS(w,you[m].x+x2y2[i*2],you[m].y+x2y2[i*2+1],bang_ptbl1[(teki_bcnt[m]>>2)*4+i],3);
			w = pl_tbl[w];
		}
		teki_bcnt[m]++;
		if ( teki_bcnt[m] > 16 ){
			pfree( &stc_pl3, teki_pl[m] );
			teki_dsp--;
			teki_ft[m] = 0;
		}
	}
}


/* Back attackザコ LVL1
wk0:Animation pattern
wk1:Up Down flg
wk2:Damage color
wk3:Shot time
wk4:anime count
*/
void back_atc_zako( UBYTE m )
{
	WORD i,w;

	if ( teki_dmg[m] > 0 ){
		you[m].x++;
		you[m].y+=teki_wk1[m];

		SP_APS(teki_pl[m],        you[m].x,   you[m].y,back_zako_ptn[teki_wk0[m]],3 );
		SP_APS(pl_tbl[teki_pl[m]],you[m].x+16,you[m].y,back_zako_ptn[teki_wk0[m]+1],3 );
		if ( teki_wk4[m]++ > 5 ){
			teki_wk4[m] = 0;
			teki_wk0[m] += 2;
			if ( teki_wk0[m] >= 8 ) teki_wk0[m] = 0;
		}

		if ( !teki_wk3[m]-- ){
			teki_wk3[m] = 128;
			direct_16(you[m].x,you[m].y,0x007e);
		}

		if ( you[m].x > 272 ) {
			pp[m] = you[m].id = 0;
			teki_dsp--;
			pfree( &stc_pl1, teki_pl[m] );
			teki_ft[m] = 0;
		}
	} else {
		if ( !teki_bcnt[m] ){
			you[m].id = 0;
		}
		w = teki_pl[m];
		for ( i = 0; i < 4; i++ ){
			SP_APS(w,you[m].x+x2y2[i*2],you[m].y+x2y2[i*2+1],bang_ptbl1[(teki_bcnt[m]>>2)*4+i],3);
			w = pl_tbl[w];
		}
		teki_bcnt[m]++;
		if ( teki_bcnt[m] > 16 ){
			pfree( &stc_pl1, teki_pl[m] );
			teki_dsp--;
			teki_ft[m] = 0;
		}
	}
}

void contena( UBYTE m )
{
	WORD i,j,w;

		if ( teki_dmg[m] > 0 ){
			teki_wk1[m]--;
			if ( teki_wk1[m] == 0 ){				/* 離脱直前に座標セット */
				teki_xx[m] = you[m].x<<4;
				teki_yy[m] = you[m].y<<4;
				teki_wk1[m] = -1;
				teki_wk3[m] = 0;
			}
			if ( teki_wk1[m] > 0 ){					/* 離脱前処理 */
				if ( teki_xx[m] > (core_x>>4) ){
					teki_xx[m] = core_x>>4;
					you[m].x--;
				} else {
					if ( teki_xx[m] < (core_x>>4) ){
						teki_xx[m] = core_x>>4;
						you[m].x++;
					}
				}
				if ( teki_yy[m] > (core_y>>4) ){
					teki_yy[m] = core_y>>4;
					you[m].y--;
				} else {
					if ( teki_yy[m] < (core_y>>4) ){
						teki_yy[m] = core_y>>4;
						you[m].y++;
					}
				}
				if ( teki_wk0[m] == 0 ){
					if ( teki_wk5[m][0] > arm_y>>4 ){
						teki_wk5[m][0] = arm_y>>4;
						you[m].y++;
					} else {
						if ( teki_wk5[m][0] < arm_y>>4 ){
							teki_wk5[m][0] = arm_y>>4;
							you[m].y--;
						}
					}
				} else {
					if ( teki_wk5[m][0] > arm_y>>4 ){
						teki_wk5[m][0] = arm_y>>4;
						you[m].y--;
					} else {
						if ( teki_wk5[m][0] < arm_y>>4 ){
							teki_wk5[m][0] = arm_y>>4;
							you[m].y++;
						}
					}
				}
			} else {							/* 離脱後処理 */
				switch ( teki_wk3[m] ){
					case 0:
						teki_xx[m] -= 3;
						if ( teki_wk0[m] == 0 ) teki_yy[m] += 5;
							else teki_yy[m] -= 5;
						if ( teki_wk4[m]++ > 220 ){
							teki_wk3[m] = 1;
							teki_wk4[m] = 0;
						}
						break;
					case 1:
						teki_xx[m] -= 3;
						if ( teki_wk4[m]++ > 100 ){
							teki_wk3[m] = 2;
							teki_wk5[m][1] = 0;
							teki_wk5[m][2] = 12;
							pp[m] = 0;
						}
						break;
					case 2:
						teki_xx[m] += x_buff[teki_wk5[m][2]<<1][pp[m]]<<1;
						teki_yy[m] += y_buff[teki_wk5[m][2]<<1][pp[m]]<<1;
						pp[m]++;
						if ( teki_wk5[m][1]++ > 30 ){
							teki_wk5[m][1] = 0;
							teki_wk5[m][2] = hmtbl[teki_wk5[m][2]][SRCH16N( my.x, my.y, you[m].x, you[m].y )];
							pp[m] = 0;
						}
						break;
				}
				you[m].x = teki_xx[m] >> 4;
				you[m].y = teki_yy[m] >> 4;
			}
			if ( teki_wk0[m] ){
				w = teki_pl[m];
				for ( i = 0; i < 8; i++ ){
					SP_APS(w,you[m].x+contena_x[i],you[m].y+contena_y[i],contena_d_ptn[i]|teki_wk2[m],3 );
					w = pl_tbl[w];
				}
			} else {
				w = teki_pl[m];
				for ( i = 0; i < 8; i++ ){
					SP_APS(w,you[m].x+contena_x[i],you[m].y+contena_y[i],contena_u_ptn[i]|teki_wk2[m],3 );
					w = pl_tbl[w];
				}
			}
			if ( teki_wk2[m] ) teki_wk2[m] = 0x0000;
		} else {
			if ( !teki_bcnt[m] ){
				/*if ( !pcm0_f ) pcmplay(bang02,sizeof(bang02));*/
				you[m].id = 0;
			}
			j = teki_bcnt[m]>>2;
			w = teki_pl[m];
			for ( i = 0; i < 12; i++ ){
				SP_APS(w,you[m].x+bang_x[j][i],you[m].y+bang_y[j][i],bang_tbl2[j][i],3 );
				w = pl_tbl[w];
			}
			teki_bcnt[m]++;
			if ( teki_bcnt[m] > 11 ){
				pfree( &stc_pl1, teki_pl[m] );
				teki_dsp--;
				teki_ft[m] = 0;
			}
		}
}
