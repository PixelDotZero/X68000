	.include	doscall.mac
	.include	iocscall.mac

	.xref	S32_ARRAY00
	.xref	S32_ARRAY16

	.global		_GPUT
	.global		_GPUT11
	.global		_TPUT
	.global		_BSPRW
	.global		_GRPRW
	.global		_GTSPRW
	.global		_SRCH32_
	.global		_SRCH32
	.global		_SRCHRND
	.global		_MAG
	.global		_NNPCMON
	.global		_NNPCMOFF
	.global		_NNINIT
	.global		_NNPLAY
	.global		_NNSTOP
	.global		_NNSTAT
	.global		_SAC_DEF
	.global		_SAC_COLOR
	.global		_SAC_COLOR2
	.global		_SAC_COLOR3
	.global		_TEXSCROLL
	.global		_TEXCLR
	.global		_GRMCLR
	.global		_CRT_OPEN
	.global		_CRT_CLOSE
	.global		_TEX_DISP
	.global		_TEX512CLR
	.xdef	_INTSET
	.xdef	_INTRESET

GPIP	EQU	$E88001
V_DISP	EQU	$4
HSADR	EQU	$E80004			*水平表示開始位置
HEADR	EQU	$E80006
VSADR	EQU	$E8000C			*垂直表示開始位置
VEADR	EQU	$E8000E

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
	rts

	.text
*=============================================================================
*	テキストラム・プット・ルーチン 　　　  by さこぉ．　Ｖｅｒ．てすと版＋
*=============================================================================
*［使い方］
*
*	ＴＰＵＴ（ｘ１，ｙ１，ｘ２，ｙ２，ａｄｒｓ）
*
*		ｘ１：始点（０～１０２３）
*		ｙ１：始点（０～１０２３）
*		ｘ２：終点（０～１０２３）
*		ｙ２：終点（０～１０２３）
*	　　ａｄｒｓ：書き込むデータのアドレス
*
*［戻り値］
*
*	なくなりました
*
*
*-----------------------------------------------------------------------------
*
	.even
*
_TPUT:
	movem.l	d1-d4/a0-a5,-(sp)

	moveq.l	#0,d2
	move.w	46(sp),d1
	move.w	50(sp),d2
	move.w	54(sp),d3
	move.w	58(sp),d4
	move.l	60(sp),a0

	lsr.w	#3,d1
	lsr.w	#3,d3

	lea.l	$e00000,a2
	lea.l	$e20000,a3
	lea.l	$e40000,a4
	lea.l	$e60000,a5

	sub.w	d2,d4			*ループ回数を求める
	sub.w	d1,d3

	lsl.l	#7,d2			*アドレス計算
	add.l	d1,d2

	adda.l	d2,a2
	adda.l	d2,a3
	adda.l	d2,a4
	adda.l	d2,a5

	move.w	#127,d2
	sub.w	d3,d2

	suba.l	a1,a1			*スーパーバイザーへ
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

LOOP_Y:
	move.w	d3,d1

LOOP_X:
	move.b	(a0)+,d0		*以下、データのセット。長ったらしいけど、
	btst.l	#7,d0			*この方が速いからしかたがない？
	bne.w	LP_1
	bclr.b	#7,(a5)			*画面がクリアされていれば必要なし
	bra.s	LP_1_END
LP_1:
	bset.b	#7,(a5)
LP_1_END:
	btst.l	#6,d0
	bne.w	LP_2
	bclr.b	#7,(a4)
	bra.s	LP_2_END
LP_2:
	bset.b	#7,(a4)
LP_2_END:
	btst.l	#5,d0
	bne.w	LP_3
	bclr.b	#7,(a3)
	bra.s	LP_3_END
LP_3:
	bset.b	#7,(a3)
LP_3_END:
	btst.l	#4,d0
	bne.w	LP_4
	bclr.b	#7,(a2)
	bra.s	LP_4_END
LP_4:
	bset.b	#7,(a2)
LP_4_END:
	btst.l	#3,d0
	bne.w	LP_5
	bclr.b	#6,(a5)
	bra.s	LP_5_END
LP_5:
	bset.b	#6,(a5)
LP_5_END:
	btst.l	#2,d0
	bne.w	LP_6
	bclr.b	#6,(a4)
	bra.s	LP_6_END
LP_6:
	bset.b	#6,(a4)
LP_6_END:
	btst.l	#1,d0
	bne.w	LP_7
	bclr.b	#6,(a3)
	bra.s	LP_7_END
LP_7:
	bset.b	#6,(a3)
LP_7_END:
	btst.l	#0,d0
	bne.w	LP_8
	bclr.b	#6,(a2)
	bra.s	LP_8_END
LP_8:
	bset.b	#6,(a2)
LP_8_END:

	move.b	(a0)+,d0
	btst.l	#7,d0
	bne.w	LP_9
	bclr.b	#5,(a5)
	bra.s	LP_9_END
LP_9:
	bset.b	#5,(a5)
LP_9_END:
	btst.l	#6,d0
	bne.w	LP_10
	bclr.b	#5,(a4)
	bra.s	LP_10_END
LP_10:
	bset.b	#5,(a4)
LP_10_END:
	btst.l	#5,d0
	bne.w	LP_11
	bclr.b	#5,(a3)
	bra.s	LP_11_END
LP_11:
	bset.b	#5,(a3)
LP_11_END:
	btst.l	#4,d0
	bne.w	LP_12
	bclr.b	#5,(a2)
	bra.s	LP_12_END
LP_12:
	bset.b	#5,(a2)
LP_12_END:

	btst.l	#3,d0
	bne.w	LP_13
	bclr.b	#4,(a5)
	bra.s	LP_13_END
LP_13:
	bset.b	#4,(a5)
LP_13_END:
	btst.l	#2,d0
	bne.w	LP_14
	bclr.b	#4,(a4)
	bra.s	LP_14_END
LP_14:
	bset.b	#4,(a4)
LP_14_END:
	btst.l	#1,d0
	bne.w	LP_15
	bclr.b	#4,(a3)
	bra.s	LP_15_END
LP_15:
	bset.b	#4,(a3)
LP_15_END:
	btst.l	#0,d0
	bne.w	LP_16
	bclr.b	#4,(a2)
	bra.s	LP_16_END
LP_16:
	bset.b	#4,(a2)
LP_16_END:

	move.b	(a0)+,d0
	btst.l	#7,d0
	bne.w	LP_17
	bclr.b	#3,(a5)
	bra.s	LP_17_END
LP_17:
	bset.b	#3,(a5)
LP_17_END:
	btst.l	#6,d0
	bne.w	LP_18
	bclr.b	#3,(a4)
	bra.s	LP_18_END
LP_18:
	bset.b	#3,(a4)
LP_18_END:
	btst.l	#5,d0
	bne.w	LP_19
	bclr.b	#3,(a3)
	bra.s	LP_19_END
LP_19:
	bset.b	#3,(a3)
LP_19_END:
	btst.l	#4,d0
	bne.w	LP_20
	bclr.b	#3,(a2)
	bra.s	LP_20_END
LP_20:
	bset.b	#3,(a2)
LP_20_END:

	btst.l	#3,d0
	bne.w	LP_21
	bclr.b	#2,(a5)
	bra.s	LP_21_END
LP_21:
	bset.b	#2,(a5)
LP_21_END:
	btst.l	#2,d0
	bne.w	LP_22
	bclr.b	#2,(a4)
	bra.s	LP_22_END
LP_22:
	bset.b	#2,(a4)
LP_22_END:
	btst.l	#1,d0
	bne.w	LP_23
	bclr.b	#2,(a3)
	bra.s	LP_23_END
LP_23:
	bset.b	#2,(a3)
LP_23_END:
	btst.l	#0,d0
	bne.w	LP_24
	bclr.b	#2,(a2)
	bra.s	LP_24_END
LP_24:
	bset.b	#2,(a2)
LP_24_END:

	move.b	(a0)+,d0
	btst.l	#7,d0
	bne.w	LP_25
	bclr.b	#1,(a5)
	bra.s	LP_25_END
LP_25:
	bset.b	#1,(a5)
LP_25_END:
	btst.l	#6,d0
	bne.w	LP_26
	bclr.b	#1,(a4)
	bra.s	LP_26_END
LP_26:
	bset.b	#1,(a4)
LP_26_END:
	btst.l	#5,d0
	bne.w	LP_27
	bclr.b	#1,(a3)
	bra.s	LP_27_END
LP_27:
	bset.b	#1,(a3)
LP_27_END:
	btst.l	#4,d0
	bne.w	LP_28
	bclr.b	#1,(a2)
	bra.s	LP_28_END
LP_28:
	bset.b	#1,(a2)
LP_28_END:
	btst.l	#3,d0
	bne.w	LP_29
	bclr.b	#0,(a5)+
	bra.s	LP_29_END
LP_29:
	bset.b	#0,(a5)+
LP_29_END:
	btst.l	#2,d0
	bne.w	LP_30
	bclr.b	#0,(a4)+
	bra.s	LP_30_END
LP_30:
	bset.b	#0,(a4)+
LP_30_END:
	btst.l	#1,d0
	bne.w	LP_31
	bclr.b	#0,(a3)+
	bra.s	LP_31_END
LP_31:
	bset.b	#0,(a3)+
LP_31_END:
	btst.l	#0,d0
	bne.w	LP_32
	bclr.b	#0,(a2)+
	bra.s	LP_32_END
LP_32:
	bset.b	#0,(a2)+
LP_32_END:

	dbra	d1,LOOP_X
	adda.w	d2,a2
	adda.w	d2,a3
	adda.w	d2,a4
	adda.w	d2,a5

	dbra	d4,LOOP_Y

	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d4/a0-a5
	rts

	.text
*=============================================================================
*	ＢＧ／ＳＰ間優先度設定　　　　　　　　　　　　　　　　     by さこぉ．
*=============================================================================
*［使い方］
*
*	ＢＧＰＲＷ（プライオリティ）
*
*	プライオリティ：１　ＢＧ０＞ＢＧ１＞ＳＰ
*	              ：２　ＢＧ０＞ＳＰ＞ＢＧ１
*	　　　　　　　：３　ＳＰ＞ＢＧ０＞ＢＧ１
*
*-----------------------------------------------------------------------------
*
	.even
*
_BSPRW:
	movem.l	d1/a1,-(sp)

	move.l	12(sp),d1
	suba.l	a1,a1
	iocs	_B_SUPER

	move.l	#$E82404,a1
	andi.w	#0,(a1)
	or.w	d1,(a1)

	move.l	d0,a1
	iocs	_B_SUPER

	movem.l	(sp)+,d1/a1
	rts

	.text
*=============================================================================
*	グラフィック画面優先度設定ルーチン（１６色専用）　　　　　 by さこぉ．
*=============================================================================
*［使い方］
*
*	ＧＲＰＲＷ（優先度４ 優先度３ 優先度２ 優先度１）
*
*	              低  　←　 優先度  　→　　高
*
*	それぞれの優先度（２ビット）に、プレーン番号が入る。
*
*	　　　　　　　プレーン番号０　：　００Ｂ
*	　　　　　　　プレーン番号１　：　０１Ｂ
*	　　　　　　　プレーン番号２　：　１０Ｂ
*	　　　　　　　プレーン番号２　：　１１Ｂ
*
*
*	　　　例：ＧＲ３＞ＧＲ０＞ＧＲ１＞ＧＲ２　の場合
*	　　　　　　　↓　　　↓　　　↓　　　↓
*	　　　　　　１１Ｂ　００Ｂ　０１Ｂ　１０Ｂとなるので
*	　　　　　　　　　∨　　　　　　　∨
*	　　　　　　　　　Ｃ        　　　６
*
*	          ＧＲＰＲＷ（０ｘＣ６）となる
*
*-----------------------------------------------------------------------------
*
	.even
*
_GRPRW:
	movem.l	d1/a1,-(sp)

	move.l	12(sp),d1
	suba.l	a1,a1
	iocs	_B_SUPER

	move.l	#$E82501,a1
	andi.b	#0,(a1)
	or.b	d1,(a1)

	move.l	d0,a1
	iocs	_B_SUPER

	movem.l	(sp)+,d1/a1
	rts

	.text
*=============================================================================
*	ＧＲ／ＴＸ／ＳＰ間優先度設定　　　　　　　　　　　　　　　 by さこぉ．
*=============================================================================
*［使い方］
*00 00.1001
*	ＧＴＳＰＲＷ（ＳＰ優先度 ＴＸ優先度 ＧＲ優先度）
*
*	　　　      　優先度１　００　高
*	　　　　　 　 優先度２　０１　｜
*	　    　　 　 優先度３　１０　低
*
*	　　　例：ＳＰ　＞　ＧＲ　＞　ＴＸ　の場合
*
*	　      　ＳＰ＝００，ＴＸ＝１０，ＧＲ＝０１なので、
*
*	          ＧＴＳＰＲＷ（０ｘ０９）となる
*
*	注意：上位２ビットは０にして下さいませ。
*	　　　要するに、ＳＰの前の２ビット。
*
*-----------------------------------------------------------------------------
*
	.even
*
_GTSPRW:
	movem.l	d1/a1,-(sp)

	move.l	12(sp),d1
	suba.l	a1,a1
	iocs	_B_SUPER

	move.l	#$E82500,a1
	andi.b	#$c0,(a1)
	or.b	d1,(a1)

	move.l	d0,a1
	iocs	_B_SUPER

	movem.l	(sp)+,d1/a1
	rts

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

	.text
*=============================================================================
*	グラフィック拡大・プット・ルーチン 　  by さこぉ． 　Updated: 90/07/15
*=============================================================================
*［使い方］
*
*	ＭＡＧ（ｘ１，ｙ１，ｘ２，ｙ２，ｓｃｒｎ，ａｄｒｓ，ｍ１，ｍ２）
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
*	　　　　ｍ１：拡大率
*	　　　　ｍ２：まびきりつ
*
*［戻り値］
*
*	なくなりました
*
*-----------------------------------------------------------------------------
*
	.even
*
_MAG:
	movem.l	d1-d7/a0-a4,-(sp)

	move.w	54(sp),d1
	move.w	58(sp),d2
	move.w	62(sp),d3
	move.w	66(sp),d4
	move.l	68(sp),a2
	move.l	72(sp),a0
	move.w	78(sp),d5
	move.w	82(sp),a4		*まびきすう

	sub.w	d2,d4			*ループ回数を求める
	sub.w	d1,d3
	add.w	d1,d1			*アドレスの計算
	add.w	d1,a2			*の始点
	moveq.l	#10,d1
	lsl.l	d1,d2
	add.l	d2,a2			*Ｘの始点
	move.w	d3,d2			*アドレス補正の計算
	move.w	#512,d1
	sub.w	d2,d1
	add.w	d1,d1
	move.w	d1,a3
	subq.l	#1,d3			*ループ回数ー１

	suba.l	a1,a1			*スーパーバイザーへ
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	move.w	d5,d7			*ドットの複製回数退避
	move.w	a4,d1
MLOOP1:					*プット（メイン）ルーチン
	move.w	d3,d2
	move.w	a4,d0
	suba.l	a1,a1
MLOOP2:
	addq.w	#1,a2			*通常の書き込み
	move.b	(a0)+,(a2)+

	subq.w	#1,d0			*以下複製処理
	bne.w	MLOOP2_SKIP		*複製するかしないか
DOT_COPY:
	subq.w	#1,a0
	addq.w	#2,a1
	addq.w	#1,a2
	move.b	(a0)+,(a2)+
	dbra	d7,DOT_COPY

	move.w	a4,d0
	move.w	d5,d7
MLOOP2_SKIP:
	dbra.w	d2,MLOOP2
	adda.w	a3,a2			*Ｘ座標のずれの修正
	suba.w	a1,a2			*拡大によるずれの補正

	subq.w	#1,d1
	bne.w	MLOOP1_SKIP
	move.w	a4,d1
	move.w	d5,d6

YCOPY:
	move.w	d3,d2
	move.w	a4,d0
	suba.w	d3,a0			*拡大によるアドレス修正
	sub.w	#1,a0
	suba.l	a1,a1
YMLOOP2:
	addq.w	#1,a2			*通常の書き込み
	move.b	(a0)+,(a2)+
	subq.w	#1,d0			*以下複製処理
	bne.w	YMLOOP2_SKIP		*複製するかしないか
YDOT_COPY:
	subq.w	#1,a0
	addq.w	#2,a1
	addq.w	#1,a2
	move.b	(a0)+,(a2)+
	dbra	d7,YDOT_COPY
	move.w	a4,d0
	move.w	d5,d7
YMLOOP2_SKIP:
	dbra.w	d2,YMLOOP2
	adda.w	a3,a2			*Ｘ座標のずれの修正
	suba.w	a1,a2			*拡大によるずれの補正
	dbra.w	d6,YCOPY

MLOOP1_SKIP:
	dbra.w	d4,MLOOP1

	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d7/a0-a4
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
	andi.w	#%0000_0101,d1
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
	andi.w	#%0000_0101,d1
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
	andi.w	#%0000_0101,d1
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
	andi.w	#%0000_0101,d1
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
*	ＳＡＣ＿ＣＯＬＯＲ（スプライト＆テキストカラー設定）
*=============================================================================
*［使い方］
*
*	ＳＡＣ＿ＣＯＬＯＲ（パレット番号、カラーコード、パレットブロック）
*
*	パレット番号：    ０～１５
*	カラーコード：    ０～６５５３５
*	パレットブロック：０～１５（０はテキストパレット）
*
*-----------------------------------------------------------------------------
*
	.even
*
_SAC_COLOR:
	movem.l	d1-d3/a0-a1,-(sp)
	move.w	26(sp),d1		*パレット・ナンバー（０～１５）
	move.w	30(sp),d2		*カラー　　　　　　（０～６５５３５）
	move.w	34(sp),d3		*パレット・ブロック（１～１５）

	add.w	d1,d1
	add.w	d3,d3

	suba.l	a1,a1
	iocs	_B_SUPER

	lea.l	$e82000,a1
	adda.w	PLT_TBL(pc,d3.w),a1
	adda.w	d1,a1
	move.w	d2,(a1)

	move.l	d0,a1
	iocs	_B_SUPER

	movem.l	(sp)+,d1-d3/a0-a1
	rts

PLT_TBL:
	dc.w	$200,$220,$240,$260,$280,$2a0,$2c0,$2e0
	dc.w	$300,$320,$340,$360,$380,$3a0,$3c0,$3e0

	.text
*=============================================================================
*	ＳＡＣ＿ＣＯＬＯＲ２（スプライト＆テキストパレット一括設定）
*=============================================================================
*［使い方］
*
*	ＳＡＣ＿ＣＯＬＯＲ２（パレットブロック，アドレス）
*
*-----------------------------------------------------------------------------
*
	.even
*
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
*	ＳＡＣ＿ＤＥＦ（ＤＭＡ転送だ！）
*=============================================================================
*［使い方］
*
*	ＳＡＣ＿ＤＥＦ（ＰＣＧ番号(int)，アドレス(int)，転送バイト数(int)）
*
*		転送バイト数・・・定義個数×１２８（１２８バイト～無制限）
*
*-----------------------------------------------------------------------------
*
	.even
*
_SAC_DEF:
	movem.l	d1-d2/a1-a2,-(sp)
	move.l	20(sp),d1			*念の為、ロング・ワードで転送。
	move.l	24(sp),a1
	move.l	28(sp),d2

	lsl.w	#7,d1

	lea.l	$eb8000,a2
	adda.w	d1,a2

	moveq.l	#%0000_0101,d1
	iocs	_DMAMOVE

	movem.l	(sp)+,d1-d2/a1-a2
	rts

	.text
*=============================================================================
*	グラフィックラム・１６ドットプット 　  by さこぉ．　Ｖｅｒ．０．１３？
*=============================================================================
*［使い方］
*
*	ＧＰＵＴ１１（ｘ，ｙ＊１０２４，ｓｃｒｎ，ａｄｒｓ）
*
*		ｘ：始点（０～５１１）
*		ｙ：
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
_GPUT11:
	movem.l	d1-d2/a0-a2,-(sp)

	move.w	26(sp),d1
	move.l	28(sp),d2
	move.l	32(sp),a2
	move.l	36(sp),a0

	add.w	d1,d1			*アドレスの計算（最初の始点のみ）
	adda.w	d1,a2
	adda.l	d2,a2

	move.l	#496*2,d1

	suba.l	a1,a1			*スーパーバイザーへ
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	moveq.l	#16-1,d2

LOOP_11:					*プット（メイン）ルーチン

	move.b	(a0),d0			*0,1
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+		*２ドット分まとめて書き込む（６CLOCKのもうけ）
	move.b	(a0),d0			*2,3
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+
	move.b	(a0),d0			*4,5
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+
	move.b	(a0),d0			*6,7
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+
	move.b	(a0),d0			*8,9
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+
	move.b	(a0),d0			*10,11
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+
	move.b	(a0),d0			*12,13
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+
	move.b	(a0),d0			*14,15
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+

	adda.w	d1,a2			*Ｘ座標のずれの修正
	dbra.w	d2,LOOP_11

	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d2/a0-a2
	rts

*=============================================================================
*	テキストスクロール
*=============================================================================
*［使い方］
*
*	TEXSCROLL( x, y );

	.even
_TEXSCROLL
	movem.l	d1-d3,-(sp)
	move.w	18(sp),d2
	move.w	22(sp),d3
	moveq.l	#$1d,d0
	moveq.l	#8,d1
	trap	#15
	movem.l	(sp)+,d1-d3
	rts

	.text
*=============================================================================
*	テキストクリア（０～３）プレーンをクリアする
*=============================================================================
	.even

_TEXCLR
	movem.l	d1/a0-a1,-(sp)
	suba.l	a1,a1			*スーパーバイザーへ
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	lea.l	$e00000,a0
	move.l	#$20000-1,d1
TEXCLR_LOOP:
	move.l	#0,(a0)+
	SUBQ.L	#1,d1
	BNE		TEXCLR_LOOP

	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d1/a0-a1
	rts

	.text
*=============================================================================
*	G-RAMクリア（０～３）プレーンをクリアする
*=============================================================================
	.even

_GRMCLR
	movem.l	d1/a0-a1,-(sp)
	suba.l	a1,a1			*スーパーバイザーへ
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	lea.l	$c00000,a0
	move.l	#$20000-1,d1
GRMCLR_LOOP:
	move.l	#0,(a0)+
	SUBQ.L	#1,d1
	BNE		GRMCLR_LOOP

	move.l	SSP_WORK,a1		*ユーザモードへ
	iocs	_B_SUPER
	movem.l	(sp)+,d1/a0-a1
	rts

*=============================================================================
*ラスターによる画面オープン
*=============================================================================
	.text
	.even

_CRT_OPEN:
	movem.l	d1-d7/a1,-(sp)
	suba.l	a1,a1
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	ori.w	#$700,sr

	move.w	#49,d1
	move.w	#49,d2
	move.w	#296,d3
	move.w	#296,d4

	move.w	#31,d0
OPEN_CRT:
	btst.b	#V_DISP,GPIP
	bne.s	OPEN_CRT
	move.w	d1,HSADR
	move.w	d2,HEADR

	subq.w	#1,d1
	addq.w	#1,d2

	moveq.l	#7,d6
OPEN_:
	btst.b	#V_DISP,GPIP
	bne.s	OPEN_

	move.w	d3,VSADR
	move.w	d4,VEADR

	sub.w	#1,d3
	add.w	#1,d4

	dbra	d6,OPEN_

	move.w	#$2FFF,d7
OPEN_WAIT:
	dbra	d7,OPEN_WAIT
	dbra	d0,OPEN_CRT

	andi.w	#$F8FF,sr

	move.l	SSP_WORK,a1
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d7/a1
	rts

*=============================================================================
*ラスターによる画面クローズ
*=============================================================================
	.text
	.even

_CRT_CLOSE:
	movem.l	d1-d7/a1,-(sp)
	suba.l	a1,a1
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	ori.w	#$700,sr

	move.w	#17,d1
	move.w	#81,d2
	move.w	#40,d3
	move.w	#552,d4

	move.w	d3,VSADR
	move.w	d4,VEADR

	move.w	#31,d0
CLOSE_CRT:
	btst.b	#V_DISP,GPIP
	bne.s	CLOSE_CRT
	move.w	d1,HSADR
	move.w	d2,HEADR

	addq.w	#1,d1
	subq.w	#1,d2

	moveq.l	#7,d6
CLOSE_:
		btst.b	#V_DISP,GPIP
		bne.s	CLOSE_
		move.w	d3,VSADR
		move.w	d4,VEADR

		addq.w	#1,d3
		subq.w	#1,d4

	dbra	d6,CLOSE_

	move.w	#$2FFF,d7
CLOSE_WAIT:
	dbra	d7,CLOSE_WAIT
	dbra	d0,CLOSE_CRT

CLOSE_WAIT_:
	btst.b	#V_DISP,GPIP
	bne.s	CLOSE_WAIT_
	move.w	#0,HSADR
	move.w	#0,HEADR
	move.w	#0,VSADR
	move.w	#0,VEADR

	andi.w	#$F8FF,sr

	move.l	SSP_WORK,a1
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d7/a1
	rts

*=============================================================================
*テキスト画面の表示ＯＮ／ＯＦＦ
*=============================================================================
.even

_TEX_DISP:
	movem.l	d1-d2/a1,-(sp)
	suba.l	a1,a1
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	lea		$E82601,a1
	move.w	18(sp),d1
	bne		TEX_BIT_SET
	bclr.b	#5,(a1)
	bra		TEX_END
TEX_BIT_SET:
	bset.b	#5,(a1)

TEX_END:
	movea.l	SSP_WORK,a1
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d2/a1
	rts

*=============================================================================
*テキスト512x512画面のクリア
*=============================================================================
.even
_TEX512CLR:

	movem.l	d2/a1,-(sp)
	sub.l	a1,a1			*Super Visor Mode
	IOCS	_B_SUPER
	move.l	d0,SSP_WORK
	move.w	#512-1,d2

	move.w	d2,d0
	lea		$E00000,a1
tex0_loop:
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	lea.l	$40(a1),a1
	dbra	d0,tex0_loop

	move.w	d2,d0
	lea		$E20000,a1
tex2_loop:
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	lea.l	$40(a1),a1
	dbra	d0,tex2_loop

	move.w	d2,d0
	lea		$E40000,a1
tex4_loop:
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	lea.l	$40(a1),a1
	dbra	d0,tex4_loop

	move.w	d2,d0
	lea		$E60000,a1
tex6_loop:
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	clr.l	(a1)+
	lea.l	$40(a1),a1
	dbra	d0,tex6_loop

	move.l	SSP_WORK,a1		*User Mode
	IOCS	_B_SUPER
	movem.l	(sp)+,d2/a1
	rts
*=============================================================================
*=============================================================================

	.xref	_copykey	*Ｃでかく
	.xref	_breakkey	*Ｃでかく
	.xref	_INTFLG		*Ｃソースじょうでせんげんする	.text

	.even
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
*	わりこみセット
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
_INTSET
	clr.l	-(sp)
	DOS	_SUPER
	addq.l	#4,sp
	move.l	d0,-(sp)		*keep	USP

	move.w	#$2600,sr

	move.l	$0000007c,NMIVEC	*keep old vector
	move.l	#nmi,$0000007c		*set new vector

	move.l	$000000b0,COPYVEC	*keep old vector
	move.l	#copy,$000000b0		*set new vector

	move.l	$000000b4,BREAKVEC	*keep old vector
	move.l	#break,$000000b4	*set new vector

	move.w	#$2000,sr

	DOS	_SUPER
	addq.l	#4,sp

	rts

*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
*	わりこみリセット
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
_INTRESET
	
	clr.l	-(sp)
	DOS	_SUPER
	addq.l	#4,sp
	move.l	d0,-(sp)		*keep	USP

	move.w	#$2600,sr
	move.l	NMIVEC,$0000007c	*reset NMI vector
	move.l	COPYVEC,$000000b0	*reset COPY vector
	move.l	BREAKVEC,$000000b4	*reset BREAK vector
	move.w	#$2000,sr

	DOS	_SUPER
	addq.l	#4,sp

	rts

*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
*ＮＭＩフラグセット
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
nmi
	st.b	_INTFLG
	ori.b	#$0c,$00e8e007		*End Of Interrupt
	rte

*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
*コピーキーわりこみサブルーチンよびだし
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
copy
	jsr	_copykey
	ori.b	#$0c,$00e8e007
	rte
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
*ブレークキーわりこみサブルーチンよびだし
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
break
	jsr	_breakkey
	ori.b	#$0c,$00e8e007
	rte

*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
*わりこみベクタほぞんりょういき
*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	.data
	.even
NMIVEC
	ds.l	1
COPYVEC
	ds.l	1
BREAKVEC
	ds.l	1

	.end
