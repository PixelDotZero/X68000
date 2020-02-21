#include "GREAT.H"

void teki_set()
{
	WORD i;

	if ( disp32() ){
		teki_bcnt[teki_num] = 0;
		switch ( (teki_ptn[teki_num] = enemy_tbl[ p + 3 ]) ){
			case 0:/* START-LOGO LVL1*/
				if ( (teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,10)) ){
					for ( i = 0; i < 10; i++ ) teki_wk5[teki_num][i] = i;
					teki_ft[teki_num] = 1;
					teki_wk0[teki_num] = 0;
					teki_wk1[teki_num] = 1;
					pp[teki_num] = enemy_tbl[ p + 4 ];
					teki_dsp++;
				}
				break;
			case 1:/* グレイト・バトル・シップ */
				ppp=pp0=pp1=pp2=pp3=pp4=pp5=0;
				teki_ft[teki_num] = 1;
				teki_wk0[teki_num] = 1;
				teki_wk1[teki_num] = 0;
				you[teki_num].x = 760;
				you[teki_num].y = 128;
				sys_bg_x=sys_bg_x_d=256+8;
				sys_bg0_y = enemy_tbl[ p + 1 ];
				sys_bg1_y = enemy_tbl[ p + 2 ];
				gbs_xx  = sys_bg_x << 4;
				gbs_yy0 = sys_bg0_y << 4;
				gbs_yy1 = sys_bg1_y << 4;
				teki_dsp++;
				break;
			case 2:/* コア LVL1 */
				if ( (teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,1)) ){
					you[teki_num].x = enemy_tbl[ p + 1 ];
					you[teki_num].y = enemy_tbl[ p + 2 ];
					you[teki_num].xs = 8;
					you[teki_num].ys = 8;
					you[teki_num].id = 0;
					teki_ft[teki_num] = 1;
					teki_wk0[teki_num] = 0;
					teki_wk1[teki_num] = 0;
					teki_wk2[teki_num] = 0x0000;
					teki_wk3[teki_num] = 0;
					teki_wk4[teki_num] = 0;
					teki_dmg[teki_num] = 10;
					pp[teki_num] = 0;
					teki_dsp++;
				}
				break;
			case 3:/* 砲台 LVL3 */
				if ( (teki_pl[teki_num] = palloc( &sp_lvl3,&stc_pl3,4)) ){
					you[teki_num].x = enemy_tbl[ p + 1 ];
					you[teki_num].y = enemy_tbl[ p + 2 ];
					you[teki_num].xs = 6;
					you[teki_num].ys = 6;
					you[teki_num].id = 1;
					teki_ft[teki_num] = 1;
					teki_wk0[teki_num] = 0;
					teki_wk1[teki_num] = tama_tbl[tama_p++];
					teki_wk2[teki_num] = 0x0000;
					teki_wk3[teki_num] = core_x>>4;
					teki_wk4[teki_num] = core_y>>4;
					teki_dmg[teki_num] = 4;
					pp[teki_num] = 0;
					teki_dsp++;
				}
				break;
			case 4:/* 雑魚 LVL1 */
				if ( (teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4)) ){
					you[teki_num].x = enemy_tbl[ p + 1 ];
					teki_xx[teki_num] = you[teki_num].x << 2;
					you[teki_num].y = enemy_tbl[ p + 2 ];
					you[teki_num].xs = 8;
					you[teki_num].ys = 12;
					you[teki_num].id = 1;
					teki_ft[teki_num] = 1;
					teki_wk0[teki_num] = 0;
					teki_wk2[teki_num] = 0x0000;
					teki_wk1[teki_num] = tama_tbl[tama_p];
					teki_dmg[teki_num] = 2;
					pp[teki_num] = 0;
					teki_dsp++;
					tama_p++;
				}
				break;
			case 5:/* コンテナ LVL1 */
				if ( (teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,12)) ){
					you[teki_num].x = enemy_tbl[ p + 1 ];
					you[teki_num].y = enemy_tbl[ p + 2 ];
					you[teki_num].xs = 30;
					you[teki_num].ys = 15;
					you[teki_num].id = 1;
					teki_ft[teki_num] = 1;
					teki_xx[teki_num] = core_x >> 4;
					teki_yy[teki_num] = core_y >> 4;
					if ( you[teki_num].y < 128 ) teki_wk0[teki_num] = 0;
						else teki_wk0[teki_num] = 1;
					teki_wk1[teki_num] = enemy_tbl[ p + 4 ];
					teki_wk2[teki_num] = 0x0000;
					teki_wk3[teki_num] = 0;
					teki_wk4[teki_num] = 0;
					teki_wk5[teki_num][0] = arm_y>>4;
					teki_dmg[teki_num] = 16;
					pp[teki_num] = 0;
					teki_dsp++;
				}
				break;
			case 6:/* コアの合体音出力 Side-A */
				NNPLAY( gooo1, 3*256+3, sizeof(gooo1) );
				pcm0_f = 1;
				break;
			case 7:/* コアの合体音出力 Side-B */
				NNPLAY( gooo2, 3*256+3, sizeof(gooo2) );
				pcm0_f = 1;
				break;
			case 8:/* 3way hodai LVL3 */
				if ( (teki_pl[teki_num] = palloc( &sp_lvl3,&stc_pl3,4)) ){
					you[teki_num].x = enemy_tbl[ p + 1 ];
					you[teki_num].y = enemy_tbl[ p + 2 ];
					you[teki_num].xs = 12;
					you[teki_num].ys = 14;
					you[teki_num].id = 1;
					teki_ft[teki_num] = 1;
					teki_xx[teki_num] = core_x >> 4;
					teki_yy[teki_num] = core_y >> 4;
					teki_wk0[teki_num] = 0;
					teki_wk1[teki_num] = 0;
					teki_wk2[teki_num] = 0x0000;
					teki_wk3[teki_num] = 0;
					teki_wk4[teki_num] = enemy_tbl[ p + 4 ];
					teki_wk5[teki_num][0] = arm_y >> 4;
					teki_wk5[teki_num][1] = you[teki_num].x+16;
					teki_wk5[teki_num][2] = you[teki_num].x+16+16*4-20-8;
					teki_wk5[teki_num][3] = 0;
					teki_wk5[teki_num][4] = 0;
					teki_dmg[teki_num] = 4;
					pp[teki_num] = 0;
					teki_dsp++;
				}
				break;
			case 9:
					m_play(1,2,3,4,5,6,7,8);
					break;
			case 10:/* Back attack 雑魚 LVL1 */
				if ( (teki_pl[teki_num] = palloc( &sp_lvl1,&stc_pl1,4)) ){
					you[teki_num].x = enemy_tbl[ p + 1 ];
					you[teki_num].y = enemy_tbl[ p + 2 ];
					you[teki_num].xs = 14;
					you[teki_num].ys = 8;
					you[teki_num].id = 1;
					teki_ft[teki_num] = 1;
					teki_wk0[teki_num] = teki_wk4[teki_num] = 0;
					if ( you[teki_num].y > 128 ) teki_wk1[teki_num] = -1;
						else teki_wk1[teki_num] = 1;
					teki_wk2[teki_num] = 0x0000;
					teki_wk3[teki_num] = tama_tbl[tama_p++];
					teki_dmg[teki_num] = 2;
					pp[teki_num] = 0;
					teki_dsp++;
				}
				break;
		}
	}
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
}

/********************************************************************************************/

void g_scroll()
{
	WORD g0,g1,g2,g3;

	gp3++;gp2+=2;gp1+=3;gp0+=4;
	g0=gp0>>3;g1=gp1>>3;g2=gp2>>3;g3=gp3>>3;
	if ( g0 > 511 ) gp0 = 0;
	if ( g1 > 511 ) gp1 = 0;
	if ( g2 > 511 ) gp2 = 0;
	if ( g3 > 511 ) gp3 = 0;
	home(0,g0,0);home(1,g1,0);home(2,g2,0);home(3,g3,0);
	/*
	asm("
		movem.l	d0-d3/a1,-(sp)
		move.w	#1,d1
		move.w	#0,d2
		lea.l	yp,a1
		move.w	(a1),d3
		subq.w	#1,d3
		bpl	y0_skip
		move.w	#2048,d3
	y0_skip:
		move.w	d3,(a1)
		asr.w	#2,d3
		iocs	_SCROLL
		move.w	#2,d1
		move.w	$2(a1),d3
		subq.w	#2,d3
		bpl	y1_skip
		move.w	#2048,d3
	y1_skip:
		move.w	d3,$2(a1)
		asr.w	#2,d3
		iocs	_SCROLL
		movem.l	(sp)+,d0-d3/a1
	");
	*/
}

/********************************************************************************************/

void haikei_put()
{
	palet(0,0);
	palet( 1,0x0670);
	palet( 2,0x15ac);
	palet( 3,0x04a4);
	palet( 4,0x039c);
	palet( 5,0x77c8);
	palet( 6,0x5746);
	palet( 7,0x4680);
	palet( 8,0x1d40);
	palet( 9,0x2bc0);
	palet(10,0xe7da);
	palet(11,0xa68c);
	palet(12,0x7ff2);
	palet(13,0x02e6);
	palet(14,0xffff);
	palet(15,0xffff);

	vpage( 15 );
	home(0,0,0);
	home(1,0,0);
	home(2,0,0);
	home(3,0,0);

	GPUT(  0,224,127,255,0xc00000,cloud_B0);
	GPUT(128,224,255,255,0xc00000,cloud_B0);
	GPUT(256,224,383,255,0xc00000,cloud_B0);
	GPUT(384,224,511,255,0xc00000,cloud_B0);
	GPUT(  0, 15,191, 46,0xc00000,cloud_T0);
	GPUT(256, 15,447, 46,0xc00000,cloud_T0);
	GPUT(  0,192,127,255,0xc80000,cloud_B1);
	GPUT(128,192,255,255,0xc80000,cloud_B1);
	GPUT(256,192,383,255,0xc80000,cloud_B1);
	GPUT(384,192,511,255,0xc80000,cloud_B1);
	GPUT( 16, 50,239, 81,0xc80000,cloud_T1);
	GPUT(272, 50,495, 81,0xc80000,cloud_T1);
	GPUT(  0,180,127,211,0xd00000,cloud_B2);
	GPUT(128,180,255,211,0xd00000,cloud_B2);
	GPUT(256,180,383,211,0xd00000,cloud_B2);
	GPUT(384,180,511,211,0xd00000,cloud_B2);
	GPUT(  0, 75,223,106,0xd00000,cloud_T2);
	GPUT(256, 75,479,106,0xd00000,cloud_T2);

	GPUT(  0,165,127,196,0xd80000,cloud_B3);
	GPUT(128,165,255,196,0xd80000,cloud_B3);
	GPUT(256,165,383,196,0xd80000,cloud_B3);
	GPUT(384,165,511,196,0xd80000,cloud_B3);
	GPUT(  0, 95, 79,110,0xd80000,cloud_T3);
	GPUT(128, 95,207,110,0xd80000,cloud_T3);
	GPUT(256, 95,335,110,0xd80000,cloud_T3);
	GPUT(384, 95,463,110,0xd80000,cloud_T3);



/*
	GPUT(  0,  0,127,191,0xd80000,cloud_BG);
	GPUT(128,  0,255,191,0xd80000,cloud_BG);
	GPUT(256,  0,383,191,0xd80000,cloud_BG);
	GPUT(384,  0,511,191,0xd80000,cloud_BG);
*/
}

/********************************************************************************************/

void tama()
{
	UBYTE m = 0;

	while ( m < 32 ){
		if ( dan[m].id ){
			SP_APS(tama_pl[m],dan[m].x+8,dan[m].y+8,tama_atr[m]|tama_col,3);
			tpv[m]++;
			dan[m].x += x_buff[tama_vt[m]][tpv[m]];
			dan[m].y += y_buff[tama_vt[m]][tpv[m]];
			if ( (dan[m].x < -8) || (dan[m].x > 264) || (dan[m].y < -8) || (dan[m].y > 264) ){
				dan[m].id = 0;
				pl_tbl[tama_pl[m]] = 255;
				stc_pl2++;
			}
		}
		m++;
	}

	if ( tama_color_cnt++ > 2 ){
		tama_color_cnt = 0;
		if ( tama_color ){
			tama_col = 0x0c00;
		} else {
			tama_col = 0x0d00;
		}
		tama_color = 1 - tama_color;
	}
}

/********************************************************************************************/

void direct16( UBYTE mm, WORD nn, UWORD atr )
{
	UBYTE w, i;

	if ( (tama_tp = palloc( &sp_lvl2, &stc_pl2, 1 )) ){
		w = tama_tp - sp_lvl2;
		i = SRCH32( my.x, my.y, you[mm].x, you[mm].y );
		tama_pl[w] = tama_tp;
		tama_vt[w] = i;
		tpv[w] = 0;
		dan[w].x = you[mm].x;
		dan[w].y = you[mm].y;
		dan[w].id  = 1;
		tama_atr[w] = atr;
	}
	teki_wk1[mm] = nn;
}

/********************************************************************************************/

void direct_16( WORD xx, WORD yy, UWORD atr )
{
	UBYTE w, i;

	if ( (tama_tp = palloc( &sp_lvl2, &stc_pl2, 1 )) ){
		w = tama_tp - sp_lvl2;
		i = SRCH32( my.x, my.y, xx, yy );
		tama_pl[w] = tama_tp;
		tama_vt[w] = i;
		tpv[w] = 0;
		dan[w].x = xx;
		dan[w].y = yy;
		dan[w].id  = 1;
		tama_atr[w] = atr;
	}
}

/********************************************************************************************/

void direct_16r( WORD xx, WORD yy, UWORD atr )
{
	UBYTE w, i;

	if ( (tama_tp = palloc( &sp_lvl2, &stc_pl2, 1 )) ){
		w = tama_tp - sp_lvl2;
		i = SRCHRND( my.x, my.y, xx, yy );
		tama_pl[w] = tama_tp;
		tama_vt[w] = i;
		tpv[w] = 0;
		dan[w].x = xx;
		dan[w].y = yy;
		dan[w].id  = 1;
		tama_atr[w] = atr;
	}
}

/********************************************************************************************/

void direct__16( UBYTE v, WORD xx, WORD yy, UWORD atr )
{
	UBYTE w, i;

	if ( (tama_tp = palloc( &sp_lvl2, &stc_pl2, 1 )) ){
		w = tama_tp - sp_lvl2;
		tama_pl[w] = tama_tp;
		tama_vt[w] = v;
		tpv[w] = 0;
		dan[w].x = xx;
		dan[w].y = yy;
		dan[w].id  = 1;
		tama_atr[w] = atr;
	}
}


/********************************************************************************************/

void jiki()
{
	WORD r = 0;
	if( !jiki_f ){
		stick_ptn = STICK_INP(1)*2;
		sp_def( 0x78, &jiki_ptn[2+stick_ptn][0], 1 );
		sp_def( 0x79, &jiki_ptn[3+stick_ptn][0], 1 );
		if ( jiki_fire_cnt++ > 2 ){
			jiki_fire_cnt = 0;
			jiki_fire = 1 - jiki_fire;
			if ( jiki_fire ){
				sp_def( 0x7a, &jiki_ptn[6][0], 1 );
			} else {
				sp_def( 0x7a, &jiki_ptn[7][0], 1 );
			}
		}

		if ( muteki_time > 0 ){
			jiki_d = 3 - jiki_d;
			muteki_time--;
			if ( !muteki_time ){
				jiki_d = 3;
				my.id = 1;
			}
		}

		SP_APSV( 1, my.x+16, my.y+8, 0x0179, jiki_d );
		bg_scroll(0,sys_bg_x,sys_bg0_y);
		bg_scroll(1,sys_bg_x,sys_bg1_y);
		TEXSCROLL( body_x>>4, body_y>>4 );
		SP_APS(  2, my.x,    my.y+8, 0x0178, jiki_d );
		SP_APS(  3, my.x,    my.y+8, 0x017a, jiki_d );
		/*----------------------- ＳＨＯＴ ---------------------------*/
		if ( (TRIGGER() & 1) & !trig1_flg  ){
			trig1_flg = 1;
			while( mys[r].id & (r < 2) ) r++;
			if( !mys[r].id & !tb_f[r] ){
				mys[r].x = my.x;
				mys[r].y = my.y+2;
				mys[r].id = 1;
				SP_APS( r+10, mys[r].x+8, mys[r].y+8, tama_ptn, 3 );
				/*m_play(NL,NL,NL,NL,NL,NL, 7,NL);*/
			}
		}
		/*------------------------------------------------------------------------*/
		jiki_xx += speed * STICK_INP(0);		/*遊戯棒より入力*/
		jiki_yy += speed * STICK_INP(1);
		if ( jiki_xx < 128 )  jiki_xx += speed;		/*  8   x 16 */
		if ( jiki_xx > 3952 ) jiki_xx -= speed;		/*  247 x 16 */
		if ( jiki_yy < 400 )  jiki_yy += speed;		/*  26  x 16 */
		if ( jiki_yy > 3840 ) jiki_yy -= speed;		/*  235 x 16 */
		my.x = jiki_xx >> 4;
		my.y = jiki_yy >> 4;
		if ( !TRIGGER() ) trig1_flg = 0;
	} else {
		if ( jiki_f == 1 ){		/*自機爆発*/
			jiki_bcnt = 0;
		}
		jiki_f++;

		if ( jiki_bcnt++ < 16 ){
			SP_APSV( 1, my.x, my.y,       bang_ptbl1[(jiki_bcnt>>2)*4+0], 3 );
			bg_scroll(0,sys_bg_x,sys_bg0_y);
			bg_scroll(1,sys_bg_x,sys_bg1_y);
			TEXSCROLL( body_x>>4, body_y>>4 );
			SP_APS( 2, my.x, my.y+16,    bang_ptbl1[(jiki_bcnt>>2)*4+1], 3 );
			SP_APS( 3, my.x+16, my.y,    bang_ptbl1[(jiki_bcnt>>2)*4+2], 3 );
			SP_APS( 4, my.x+16, my.y+16, bang_ptbl1[(jiki_bcnt>>2)*4+3], 3 );
		} else {
			if ( jiki_bcnt == 16 ){
				my.x = -24; my.y = 128;
				my.id = 0;
			}
			jiki_d = 3 - jiki_d;
			SP_APSV( 1, my.x+16, my.y+8, 0x0179, jiki_d );
			bg_scroll(0,sys_bg_x,sys_bg0_y);
			bg_scroll(1,sys_bg_x,sys_bg1_y);
			TEXSCROLL( body_x>>4, body_y>>4 );
			SP_APS(  2, my.x,    my.y+8, 0x0178, jiki_d );
			SP_APS(  3, my.x,    my.y+8, 0x017a, jiki_d );
			SP_APS( 4, 511, 511, DUMMY, 0 );
			my.x += 2;
			jiki_xx = my.x << 4;
			jiki_yy = my.y << 4;
			if ( my.x >= 110 ){
				jiki_f = 0;
				muteki_time = 100;
			}
		}
	}
}

/********************************************************************************************/

UBYTE pcm_load( char *filename, UBYTE *pcmname, UWORD pcmlen )
{
	FILE *fp;

	if ( !((fp = fopen( filename, "rb" )) == (FILE*)NULL) ){
		fread( pcmname, pcmlen, 1, fp );
		fclose( fp );
		return( 1 );
	} else {
		printf( "'%s' がありません。\n", filename );
		return( 0 );
	}
}

/********************************************************************************************/

void pcmplay( UBYTE *pcmname, UWORD leng )
{
	a_end();
	a_play( pcmname, leng, 3, 3, leng );
}

/********************************************************************************************/

void pause()
{
	while ( SPCSNS() );
	while ( !SPCSNS() );
	while ( SPCSNS() );
}

/********************************************************************************************/

void wait( UBYTE n )
{
	UWORD i,j;
	for ( i = 0; i < n ; i++ ){
		j = 65535;
		while ( j-- );
	}
}

/********************************************************************************************/

UBYTE disp32()
{
	if ( teki_dsp < 32 ){
		teki_num = 0;
		while ( teki_ft[teki_num] ) teki_num++;
		return( 1 );
	} else return( 0 );
}

/********************************************************************************************/

void emyload( WORD *a, char *b )
{
	WORD *c;
	FILE *fp;

	fp = fopen( b, "rb" );
	c = a;
	while( fread( c, 1, 2, fp ) ) c++;
}

/********************************************************************************************/

void pat_load( char *name, UBYTE *val, UBYTE n )
{
	UBYTE i;
	FILE *fp;

	if ( !((fp = fopen( name, "rb" )) == (FILE*)NULL) ){
		for ( i = 0; i < n; i++ ){
			fread( val, 256, 1, fp );
			val += 256;
		}
		printf("*");
		fclose( fp );
	} else {
		printf("'%s'がありません。\n", name );
		exit( 1 );
	}
}

/********************************************************************************************/

void t_move()
{
		if( mys[0].id ){
			mys[0].x += 8;
			SP_APS( 10, mys[0].x+8, mys[0].y+8, tama_ptn, 3 );
			if ( mys[0].x > 256 ){
				mys[0].id = 0;
				SP_APS( 10, 511, 511, DUMMY, 0 );
			}
		}
		if( tb_f[0] & !tb_cnt[0]-- ){
			tb_f[0] = 0;
			SP_APS( 10, 511, 511, DUMMY, 0 );
		}
		if( mys[1].id ){
			mys[1].x += 8;
			SP_APS( 11, mys[1].x+8, mys[1].y+8, tama_ptn, 3 );
			if ( mys[1].x > 256 ){
				mys[1].id = 0;
				SP_APS( 11, 511, 511, DUMMY, 0 );
			}
		}
		if( tb_f[1] & !tb_cnt[1]-- ){
			tb_f[1] = 0;
			SP_APS( 11, 511, 511, DUMMY, 0 );
		}
		if( mys[2].id ){
			mys[2].x += 8;
			SP_APS( 12, mys[2].x+8, mys[2].y+8, tama_ptn, 3 );
			if ( mys[2].x > 256 ){
				mys[2].id = 0;
				SP_APS( 12, 511, 511, DUMMY, 0 );
			}
		}
		if( tb_f[2] & !tb_cnt[2]-- ){
			tb_f[2] = 0;
			SP_APS( 12, 511, 511, DUMMY, 0 );
		}
}

/********************************************************************************************/

void check()
{

	if ( mys[0].id ){
		you_p = 32;
		if ( act2( &mys[0], &you[0], &you_p ) ){
			SP_APS( 10, mys[0].x+8, mys[0].y+8, tama_ptn+1, 0 );
			/*if ( !pcm0_f ) pcmplay(atari01,sizeof(atari01));*/
			tb_cnt[0] = SHOT_BANG;
			mys[0].id = 0;
			tb_f[0] = 1;
			teki_dmg[you_p] -= shot_pow;
			teki_wk2[you_p] = 0x0F00;
		}
	}
	if ( mys[1].id ){
		you_p = 32;
		if ( act2( &mys[1], &you[0], &you_p ) ){
			SP_APS( 11, mys[1].x+8, mys[1].y+8, tama_ptn+1, 0 );
			/*if ( !pcm0_f ) pcmplay(atari01,sizeof(atari01));*/
			tb_cnt[1] = SHOT_BANG;
			mys[1].id = 0;
			tb_f[1] = 1;
			teki_dmg[you_p] -= shot_pow;
			teki_wk2[you_p] = 0x0F00;
		}
	}
	if ( mys[2].id ){
		you_p = 32;
		if ( act2( &mys[2], &you[0], &you_p ) ){
			SP_APS( 12, mys[2].x+8, mys[2].y+8, tama_ptn+1, 0 );
			/*if ( !pcm0_f ) pcmplay(atari01,sizeof(atari01));*/
			tb_cnt[2] = SHOT_BANG;
			mys[2].id = 0;
			tb_f[2] = 1;
			teki_dmg[you_p] -= shot_pow;
			teki_wk2[you_p] = 0x0F00;
		}
	}
}
void	uhyo()
{
	you_p = 32;
	if ( act2( &my, &you[0], &you_p ) ){					/*自機と敵の判定*/
		/*if ( !pcm0_f ) pcmplay(atari01,sizeof(atari01));*/
		/*if ( !pcm0_f ) NNPLAY( atari01, 3*256+3, sizeof(atari01) );*/
		jiki_f = 1;
		j_stock--;
		teki_dmg[you_p] -= 10;
		teki_wk2[you_p] = 0x0F00;
	}
	dan_p = stc_mx2;										/*自機と弾の判定*/
	if ( act2( &my, &dan[0], &dan_p ) ){
		jiki_f = 1;
		j_stock--;
		dan[dan_p].x = 300;
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
		SP_APS( n, 511, 511, DUMMY, 0 );		/*スプライトを消去*/
		w = pl_tbl[n];							/*ワークにテーブルの内容を格納*/
		pl_tbl[n] = 255;						/*テーブルの内容に２５５を代入*/
		(*stock)++;								/*ストック加算*/
		n = w;									/*ポインタを次へ移す*/
	} while ( w != 128 );						/*テーブルの内容が１２８まで繰り返す*/
}
/********************************************************************************************/
asm("
	.globl _ESCSNS
	.globl _SPCSNS
	.globl _XF3SNS
	.globl _OP1SNS
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
	andi.b	#%00100000,d0
	movem.l	(sp)+,d1
	rts

********************************************
*  ＸＦ３が押されていればを128を返し
*  押されていなければゼロを返す。

_XF3SNS
	movem.l	d1,-(sp)
	move.w	#$a,d1
	moveq.l	#$04,d0
	trap	#15
	andi.b	#%10000000,d0
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
");

