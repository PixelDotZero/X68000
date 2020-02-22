	.include	doscall.mac
	.include	iocscall.mac

	.xref	S32_ARRAY00
	.xref	S32_ARRAY16

	.global		_SRCH32_
	.global		_SRCH32
	.global		_SRCHRND
	.global		_NNPCMON
	.global		_NNPCMOFF
	.global		_NNINIT
	.global		_NNPLAY
	.global		_NNSTOP
	.global		_NNSTAT
	.global		_GPUT
	.global		_SAC_COLOR2
	.global		_SAC_COLOR3


	.text

_SAC_COLOR2:
	movem.l	d2/a0-a1,-(sp)
	move.w	18(sp),d2
	move.l	20(sp),a0

	suba.l	a1,a1
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	lea.l	$e82000,a1
	add.w	d2,d2
	adda.w	PLT_TBL(pc,d2.w),a1

	moveq.l	#8-1,d2
PAL_SET:
	move.l	(a0)+,(a1)+
	dbra	d2,PAL_SET
	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d2/a0-a1
	rts

PLT_TBL:
	dc.w	$200,$220,$240,$260,$280,$2a0,$2c0,$2e0
	dc.w	$300,$320,$340,$360,$380,$3a0,$3c0,$3e0

.text
*=============================================================================
*	方向検索ルーチン（TBL_2DOT）           by さこぉ．    Updated:90/07/15
*=============================================================================
*［使い方］
*
*	ＳＲＣＨ３２（ｘ１，ｙ１，ｘ２，ｙ２）
*
*		ｘ１：自機のｘ座標
*		ｙ１：自機のｙ座標
*		ｘ２：敵のｘ座標
*		ｙ２：敵のｙ座標
*
*［戻り値］
*
*	真上？の方向から３６０度を時計周りに３２に分けて
*
*	敵から見た自機の方向を０－３１の値で返す。
*
*	多少は、早くなりまった。
*
*-----------------------------------------------------------------------------
*
	.even
*
_SRCH32_:
	movem.l	d1-d4/a0,-(sp)

	move.w	26(sp),d1		*じぶんＸ
	move.w	30(sp),d2		*じぶんＹ
	move.w	34(sp),d3		*てき　Ｘ
	move.w	38(sp),d4		*てき　Ｙ

	moveq.l	#0,d0

	cmp.w	d1,d3			*自分と敵のＸを比較
	bpl.w	Y_CHECK
	addq.w	#2,d0
Y_CHECK:
	cmp.w	d2,d4			*自分と敵のＹを比較
	bpl.w	CHECK_END
	addq.w	#4,d0
CHECK_END:
	jmp	JMP_TBL(pc,d0.w)

DIR_S00:
	sub.w	d1,d3			*Ｘ－Ｘ→Ｘ
	sub.w	d4,d2			*Ｙ－Ｙ→Ｙ
*	andi.w	#$00ff,d3
	lsr.w	#1,d3			*Ｘ／２→Ｘ
	andi.w	#$00fe,d2		*1111_1110・・・２の倍数にする
	lsl.w	#6,d2			*Ｙ＊128
	add.w	d3,d2
	lea.l	S32_ARRAY00,a0
	move.b	0(a0,d2.w),d0
	addi.w	#16,d0
	movem.l	(sp)+,d1-d4/a0
	rts

DIR_S04:
	sub.w	d1,d3
	sub.w	d2,d4
*	andi.w	#$00ff,d3
	lsr.w	#1,d3
	andi.w	#$00fe,d4
	lsl.w	#6,d4
	add.w	d3,d4
	lea.l	S32_ARRAY16,a0
	move.b	0(a0,d4.w),d0
	addi.w	#24,d0
	cmpi.w	#32,d0
	bne.w	CHECK_OVER		*この部分は、テストの為のもので
	moveq.l	#0,d0			*使用する場合は、消して下さい。
CHECK_OVER:				*
	movem.l	(sp)+,d1-d4/a0
	rts

JMP_TBL:
	bra.s	DIR_S04			*ここにジャンプテーブルを置くことにより、
	bra.s	DIR_S08			*全てがショートブランチですむ。
	bra.s	DIR_S00
	bra.s	DIR_S12

DIR_S08:
	sub.w	d3,d1
	sub.w	d2,d4
*	andi.w	#$00ff,d1
	lsr.w	#1,d1
	andi.w	#$00fe,d4
	lsl.w	#6,d4
	add.w	d1,d4
	lea.l	S32_ARRAY00,a0
	move.b	0(a0,d4.w),d0
	movem.l	(sp)+,d1-d4/a0
	rts

DIR_S12:
	sub.w	d3,d1
	sub.w	d4,d2
*	andi.w	#$00ff,d1
	lsr.w	#1,d1
	andi.w	#$00fe,d2
	lsl.w	#6,d2
	add.w	d1,d2
	lea.l	S32_ARRAY16,a0
	move.b	0(a0,d2.w),d0
	addi.w	#8,d0
	movem.l	(sp)+,d1-d4/a0
	rts

	.text
*=============================================================================
*	方向検索ルーチン（TBL_4DOT）           by さこぉ．    Updated:90/07/15
*=============================================================================
*［使い方］
*
*	ＳＲＣＨ３２４（ｘ１，ｙ１，ｘ２，ｙ２）
*
*		ｘ１：自機のｘ座標
*		ｙ１：自機のｙ座標
*		ｘ２：敵のｘ座標
*		ｙ２：敵のｙ座標
*
*［戻り値］
*
*	真上？の方向から３６０度を時計周りに３２に分けて
*
*	敵から見た自機の方向を０－３１の値で返す。
*
*	上のより早い。なぜでしょう？　それは、シフトする数が少ないからです。江っ変
*
*-----------------------------------------------------------------------------
*
	.even

_SRCH32:
	movem.l	d1-d4/a0,-(sp)

	move.w	26(sp),d1		*じぶんＸ
	ext.l	d1
	move.w	30(sp),d2		*じぶんＹ
	move.w	34(sp),d3		*てき　Ｘ
	move.w	38(sp),d4		*てき　Ｙ



	moveq.l	#0,d0

	cmp.w	d1,d3			*自分と敵のＸを比較
	bpl.w	Y_CHECK4
	addq.w	#2,d0
Y_CHECK4:
	cmp.w	d2,d4			*自分と敵のＹを比較
	bpl.w	CHECK_END4
	addq.w	#4,d0
CHECK_END4:
	jmp	JMP_TBL4(pc,d0.w)

DIR_S004:
	sub.w	d1,d3			*Ｘ－Ｘ→Ｘ
	sub.w	d4,d2			*Ｙ－Ｙ→Ｙ
*	andi.w	#$00ff,d3
	lsr.w	#2,d3			*Ｘ／４→Ｘ
	andi.w	#$00fc,d2		*1111_1100・・・4の倍数にする
	lsl.w	#4,d2			*Ｙ＊64
	add.w	d3,d2
	lea.l	S32_ARRAY00,a0
	move.b	0(a0,d2.w),d0
	addi.w	#16,d0
	movem.l	(sp)+,d1-d4/a0
	rts

DIR_S044:
	sub.w	d1,d3
	sub.w	d2,d4
*	andi.w	#$00ff,d3
	lsr.w	#2,d3
	andi.w	#$00fc,d4
	lsl.w	#4,d4
	add.w	d3,d4
	lea.l	S32_ARRAY16,a0
	move.b	0(a0,d4.w),d0
	addi.w	#24,d0
	cmpi.w	#32,d0
	bne.w	CHECK_OVER4		*この部分は、テストの為のもので
	moveq.l	#0,d0			*使用する場合は、消して下さい。
CHECK_OVER4:				*
	movem.l	(sp)+,d1-d4/a0
	rts

JMP_TBL4:
	bra.s	DIR_S044		*ここにジャンプテーブルを置くことにより、
	bra.s	DIR_S084		*全てがショートブランチですむ。
	bra.s	DIR_S004
	bra.s	DIR_S124

DIR_S084:
	sub.w	d3,d1
	sub.w	d2,d4
*	andi.w	#$00ff,d1
	lsr.w	#2,d1
	andi.w	#$00fc,d4
	lsl.w	#4,d4
	add.w	d1,d4
	lea.l	S32_ARRAY00,a0
	move.b	0(a0,d4.w),d0
	movem.l	(sp)+,d1-d4/a0
	rts

DIR_S124:
	sub.w	d3,d1
	sub.w	d4,d2
*	andi.w	#$00ff,d1
	lsr.w	#2,d1
	andi.w	#$00fc,d2
	lsl.w	#4,d2
	add.w	d1,d2
	lea.l	S32_ARRAY16,a0
	move.b	0(a0,d2.w),d0
	addq.w	#8,d0
	movem.l	(sp)+,d1-d4/a0
	rts

***************************************************************************************
	.even

_SRCHRND:
	movem.l	d1-d4/a0,-(sp)

	move.w	26(sp),d1		*じぶんＸ
	move.w	30(sp),d2		*じぶんＹ
	move.w	34(sp),d3		*てき　Ｘ
	move.w	38(sp),d4		*てき　Ｙ

	moveq.l	#0,d0

	cmp.w	d1,d3			*自分と敵のＸを比較
	bpl.s	Y_CHECKR
	addq.w	#2,d0
Y_CHECKR:
	cmp.w	d2,d4			*自分と敵のＹを比較
	bpl.s	CHECK_ENDR
	addq.w	#4,d0
CHECK_ENDR:
	jmp	JMP_TBLR(pc,d0.w)

DIR_S00R:
	sub.w	d1,d3			*Ｘ－Ｘ→Ｘ
	sub.w	d4,d2			*Ｙ－Ｙ→Ｙ
	lsr.w	#2,d3			*Ｘ／２→Ｘ
	andi.w	#$00fc,d2		*1111_1110・・・２の倍数にする
	lsl.w	#4,d2			*Ｙ＊128
	add.w	d3,d2
	lea.l	S32_ARRAY00,a0
	move.b	0(a0,d2.w),d0
	addi.w	#16,d0
	move.w	_main_cnt,d1
	andi.w	#5,d1
	add.b	d1,d0
	movem.l	(sp)+,d1-d4/a0
	rts

DIR_S04R:
	sub.w	d1,d3
	sub.w	d2,d4
	lsr.w	#2,d3
	andi.w	#$00fc,d4
	lsl.w	#4,d4
	add.w	d3,d4
	lea.l	S32_ARRAY16,a0
	move.b	0(a0,d4.w),d0
	addi.w	#24,d0
	move.w	_main_cnt,d1
	andi.w	#5,d1
	sub.b	d1,d0
	cmpi.b	#32,d0
	bne.w	RND_SKIP
	moveq.l	#0,d0
RND_SKIP:
	movem.l	(sp)+,d1-d4/a0
	rts

JMP_TBLR:
	bra.s	DIR_S04R			*ここにジャンプテーブルを置くことにより、
	bra.s	DIR_S08R			*全てがショートブランチですむ。
	bra.s	DIR_S00R
	bra.s	DIR_S12R

DIR_S08R:
	sub.w	d3,d1
	sub.w	d2,d4
	lsr.w	#2,d1
	andi.w	#$00fc,d4
	lsl.w	#4,d4
	add.w	d1,d4
	lea.l	S32_ARRAY00,a0
	move.b	0(a0,d4.w),d0
	move.w	_main_cnt,d1
	andi.w	#5,d1
	add.b	d1,d0
	movem.l	(sp)+,d1-d4/a0
	rts

DIR_S12R:
	sub.w	d3,d1
	sub.w	d4,d2
	lsr.w	#2,d1
	andi.w	#$00fc,d2
	lsl.w	#4,d2
	add.w	d1,d2
	lea.l	S32_ARRAY16,a0
	move.b	0(a0,d2.w),d0
	addi.w	#8,d0
	move.w	_main_cnt,d1
	andi.w	#5,d1
	sub.b	d1,d0
	movem.l	(sp)+,d1-d4/a0
	rts

	.even
*---------------------------------------------------------------------------------------------
*	ＡＤＰＣＭ　ＤＲＩＶＩＮＧ　ＳＹＳＴＥＭ　（ＮＮＰＣＭＤＲＶ）		ＧＯＲＲＹ．
*								UPDATED:90/07/24   BY さこぉ．
*---------------------------------------------------------------------------------------------
*
*［使用方法］
*
*	ＮＮＰＣＭＯＮ（）		常駐開始
*	ＮＮＰＣＭＯＦＦ（）		常駐解除
*	ＮＮＩＮＩＴ（）
*	ＮＮＰＬＡＹ（ＰＣＭ先頭アドレス，ｐａｎ＊２５６＋再生周波数，再生する長さ）
*	ＮＮＳＴＯＰ（）
*	ＮＮＳＴＡＴ（）	[返り値]	　　０：非再生中
*						その他：再生中
*
*		再生周波数	０　～　４
*		パンポット	０　～　３
*		再生する長さは６４ｋまでです。
*
*---------------------------------------------------------------------------------------------

_NNPCMON:
	movem.l	d1-d7/a0-a7,-(sp)
	bsr	adpcm_routine_set
	movem.l	(sp)+,d1-d7/a0-a7
	rts

_NNPCMOFF:
	moveq.l	#0,d1
	moveq.l	#5,d0
	trap	#2
	moveq.l	#4,d0
	trap	#2
	moveq.l	#-1,d0
	trap	#2
	rts

_NNINIT:
	moveq.l	#6,d0
	trap	#2
	rts

_NNPLAY:
	movem.l	d1-d2/a1,-(sp)
	moveq.l	#0,d1
	moveq.l	#5,d0
	trap	#2
	move.l	16(sp),a1
	move.w	22(sp),d1
	move.w	26(sp),d2
	moveq.l	#0,d0
	trap	#2
	movem.l	(sp)+,d1-d2/a1
	rts

_NNSTOP:
	moveq.l	#0,d1
	moveq.l	#5,d0
	trap	#2
	rts

_NNSTAT:
	moveq.l	#3,d0
	trap	#2
	ext.w	d0
	ext.l	d0
	rts

*---------------------------------------------------------------------------------------------
adpcm_routine_set

	moveq.l	#$80,d0		*B_INTVCS
	moveq.l	#$6a,d1		*adpcm stop interrupt vector
	lea	adpcm_stop_int(pc),a1
	trap	#15
	lea	before_adpcm_stop_int(pc),a0
	move.l	d0,(a0)

	moveq.l	#$80,d0		*B_INTVCS
	moveq.l	#$22,d1		*trap 2 vector
	lea	adpcm_control_trapin(pc),a1
	trap	#15
	lea	before_trap2_vec(pc),a0
	move.l	d0,(a0)

	lea	adpcm_init_data(pc),a0
	lea	adpcm_array_chain_data(pc),a1
	move.l	a0,(a1)

	lea	adpcm_status(pc),a0
	clr.b	(a0)

	moveq.l	#6,d0		*adpcm init
	trap	#2

	rts

adpcm_init_data
	dc.b	8,8,8,8,8,8,8,8
	dc.b	8,8,8,8,8,8,8,8
	dc.b	8,8,8,8,8,8,8,8
adpcm_array_chain_data
	dc.l	0
	dc.w	24
	dc.l	0
	dc.w	0

adpcm_control_trapin

	movem.l	d1-d7/a0-a6,-(sp)
	cmpi.w	#-1,d0
	beq	cut_driver

	add.w	d0,d0
	move.w	adpcm_control_jptable(pc,d0),d0
	jsr	adpcm_control_jptable(pc,d0)

adpcm_control_ret
	movem.l	(sp)+,d1-d7/a0-a6
	rte


adpcm_control_jptable
	dc.w	adpcm_play-adpcm_control_jptable
	dc.w	adpcm_record-adpcm_control_jptable
	dc.w	adpcm_stop-adpcm_control_jptable
	dc.w	adpcm_status_get-adpcm_control_jptable
	dc.w	adpcm_off-adpcm_control_jptable
	dc.w	adpcm_monitor-adpcm_control_jptable
	dc.w	adpcm_init-adpcm_control_jptable

adpcm_init
	move.b	#$0b,$E9A005	周波数設定
	lea	$e92001,a0
	move.b	#1,(a0)		ＡＤＰＣＭ stop
	moveq.l	#1,d1
	bsr	adpcm_monitor
	move.w	#500,d0
adpcm_init_1
	dbra	d0,adpcm_init_1

	move.b	#$08,$E9A005	周波数設定
	moveq.l	#0,d1
	bsr	adpcm_monitor
	moveq.l	#127,d0
	rts


adpcm_play
	move.b	#$10,$E840C7	ＤＭＡ強制停止

	moveq.l	#$80,d0		*rate 4MHz
	cmpi.b	#2,d1
	bcs	_skip_1
	moveq.l	#0,d0		*rate 8MHz
	subq.b	#2,d1
_skip_1
	lea	$e90001,a0
_fm_wait_1
	tst.b	2(a0)
	bmi	_fm_wait_1
	move.b	#$1b,(a0)	*本当は割り込みを止めて行うべきなのだ・・・。
	move.b	d0,2(a0)

	cmpi.b	#3,d1
	bcc	ret
	move.b	d1,d0
	lsl.b	#2,d0

	lsr.w	#8,d1		*pan
	eori.b	#3,d1
	or.b	d0,d1

	lea	adpcm_array_chain_data+6(pc),a0
	move.l	a1,(a0)+	*play start address
	move.w	d2,(a0)		*play length
	lea	-10(a0),a0

*　アレイ・チェーン・モード転送			from TONBE.

	move.b	#$3A,$E840C5	ＤＭＡオペレーション設定
	st	$E840C0		チャンネル・ステータス・クリア
	move.l	A0,$E840DC	ベース・アドレス
	move.w	#2,$E840DA	転送ブロック数
	move.b	#$88,$E840C7	ＤＭＡ動作スタート
	move.b	D1,$E9A005	周波数設定
	move.b	#2,$E92001	ＡＤＰＣＭ再生開始

	lea	adpcm_status(pc),a0
	move.b	#1,(a0)

	lea	adpcm_pan(pc),a0
	move.b	d1,(a0)

	lea	adpcm_monitor_switch(pc),a0
	clr.b	(a0)

ret
	rts

adpcm_record

	move.b	#$10,$E840C7	ＤＭＡ強制停止
	moveq.l	#$80,d0		*rate 4MHz
	cmpi.b	#2,d1
	bcs	_skip_2
	moveq.l	#0,d0		*rate 8MHz
	subq.b	#2,d1
_skip_2
	lea	$e90001,a0
_fm_wait_2
	tst.b	2(a0)
	bmi	_fm_wait_2
	move.b	#$1b,(a0)	*本当は割り込みを止めて行うべきなのだ・・・。
	move.b	d0,2(a0)

	cmpi.b	#3,d1
	bcc	ret
	move.b	d1,d0
	lsl.b	#2,d0

	lsr.w	#8,d1		*pan
	eori.b	#3,d1
	or.b	d0,d1

*　ノーマル・モード転送		from TONBE.

	move.b	#$B2,$E840C5	ＤＭＡオペレーション設定
	st	$E840C0		チャンネル・ステータス・クリア
	move.l	A1,$E840CC	メモリ・アドレス
	move.w	D2,$E840CA	転送バイト数
	move.b	#$88,$E840C7	ＤＭＡ動作スタート
	move.b	D1,$E9A005	周波数設定
	move.b	#4,$E92001	ＡＤＰＣＭ録音開始

	lea	adpcm_status(pc),a0
	move.b	#2,(a0)

	lea	adpcm_pan(pc),a0
	move.b	d0,(a0)

	lea	adpcm_monitor_switch(pc),a0
	clr.b	(a0)

	rts

adpcm_stop

*　ＤＭＡ転送終了割り込み（ベクタ＄６Ａ）	*from TONBE.

	move.b	#$10,$E840C7	ＤＭＡ強制停止
	st	$E840C0		チャンネル・ステータス・クリア
	move.b	#$08,$E92003	こうすると、ＯＦＦ時のプツって音が出ない
	clr.w	$000c32		rom routine flag clear.
	move.l	a0,-(sp)
	lea	adpcm_status(pc),a0
	clr.b	(a0)
	lea	adpcm_monitor_switch(pc),a0
	clr.b	(a0)
	move.l	(sp)+,a0

	rts

adpcm_off

	move.b	adpcm_pan(pc),d0
	ori.b	#3,d0
	move.b	d0,$e9a005
	lea	adpcm_monitor_switch(pc),a0
	clr.b	(a0)
	rts

	

adpcm_stop_int
	bsr	adpcm_stop
	rte

adpcm_status_get
	move.b	adpcm_status(pc),d0
	rts

adpcm_monitor
	move.b	#$10,$E840C7	ＤＭＡ強制停止
	st	$E840C0		チャンネル・ステータス・クリア
	lea	adpcm_monitor_switch(pc),a0
	cmpi.b	#2,d1
	beq	adpcm_monitor_change
adpcm_monitor_1
	move.b	d1,(a0)
	moveq.l	#4,d0
	tst.b	d1
	bne	adpcm_monitor_2
	moveq.l	#1,d0
	lea	adpcm_status(pc),a0
	clr.b	(a0)
	move.b	#$08,$E92003	こうすると、ＯＦＦ時のプツって音が出ない
adpcm_monitor_2
	move.b	d0,$e92001		*record on
	rts

adpcm_monitor_change
	move.b	(a0),d1
	eori.b	#1,d1
	bra	adpcm_monitor_1

cut_driver

	moveq.l	#0,d1
	bsr	adpcm_monitor
	move.b	#2,$e92001		*play on
	bsr	adpcm_stop
	bsr	adpcm_off

	movea.l	before_adpcm_stop_int(pc),a1
	moveq.l	#$80,d0		*B_INTVCS
	moveq.l	#$6a,d1		*adpcm stop interrupt vector
	trap	#15

	movea.l	before_trap2_vec(pc),a1
	moveq.l	#$80,d0		*B_INTVCS
	moveq.l	#$22,d1		*trap 2 vector
	trap	#15

	bra	adpcm_control_ret

before_adpcm_stop_int
	ds.l	1
before_trap2_vec
	ds.l	1
adpcm_status
	dc.b	0
adpcm_pan
	dc.b	$08
adpcm_monitor_switch
	dc.b	0
	.even

	.data
	.even

SSP_WORK:
	ds.l	1

	.text
*=============================================================================
*	ＳＡＣ＿ＣＯＬＯＲ３（グラフィックパレット一括設定）
*=============================================================================
*［使い方］
*
*	ＳＡＣ＿ＣＯＬＯＲ３（　アドレス　）
*
*-----------------------------------------------------------------------------
*
	.even
*
_SAC_COLOR3:
	movem.l	a0-a1,-(sp)
	move.l	12(sp),a0
	suba.l	a1,a1
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	lea.l	$e82000,a1

	moveq.l	#8-1,d0
GRPAL_SET:
	move.l	(a0)+,(a1)+
	dbra	d0,GRPAL_SET
	move.l	SSP_WORK,a1		*ユーザモードへ

	iocs	_B_SUPER
	movem.l	(sp)+,a0-a1
	rts


	.text
*=============================================================================
*	グラフィックラム・プット・ルーチン 　  by さこぉ．　Ｖｅｒ．０．１３β
*=============================================================================
*［使い方］
*
*	ＧＰＵＴ（ｘ１，ｙ１，ｘ２，ｙ２，ｓｃｒｎ，ａｄｒｓ）
*
*		ｘ１：始点（０～５１１）
*		ｙ１：
*		ｘ２：終点（０～５１１）
*		ｙ２：
*	　　ｓｃｒｎ：プレーン０　（＄Ｃ０００００）
*	　　        ：プレーン１  （＄Ｃ８００００）
*	　　        ：プレーン２　（＄Ｄ０００００）
*	　　        ：プレーン３　（＄Ｄ８００００）
*	　　ａｄｒｓ：書き込むデータのアドレス
*
*［戻り値］
*
*	なくなりました
*
*-----------------------------------------------------------------------------
*
	.even
*
_GPUT:
	movem.l	d1-d4/a0-a2,-(sp)

	move.w	34(sp),d1
	move.w	38(sp),d2
	move.w	42(sp),d3
	move.w	46(sp),d4
	move.l	48(sp),a2
	move.l	52(sp),a0

	sub.w	d2,d4			*ループ回数を求める
	sub.w	d1,d3
	subq.w	#1,d3

	add.w	d1,d1			*アドレスの計算（その１）
	adda.w	d1,a2
	moveq.l	#10,d1
	lsl.l	d1,d2
	adda.l	d2,a2
	move.w	d3,d2
	move.w	#510,d1
	sub.w	d2,d1
	add.w	d1,d1
	lsr.w	#1,d3

	suba.l	a1,a1			*スーパーバイザーへ
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

LOOP1:					*プット（メイン）ルーチン
	move.w	d3,d2
LOOP2:
	move.b	(a0),d0
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+		*２ドット分まとめて書き込む（６CLOCKのもうけ）
	dbra.w	d2,LOOP2
	adda.w	d1,a2			*Ｘ座標のずれの修正
	dbra.w	d4,LOOP1

	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d4/a0-a2
	rts