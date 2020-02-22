*=============================================================================
*	ＭＢ　ＩＩ　ＰＲＯＧＲＡＭ　ＬＩＢＲＡＲＹ	更新日／１９９０年１１月１４日
*					   Programmed by A.P.S. & Fake Manager
*=============================================================================

	.include	iocscall.mac
	.include	doscall.mac

	.globl		_STICK_INP
	.globl		_STICK_INP_NML
	.globl		_TRIGGER
	.globl		_TRIGGER_NML
	.globl		_SP_APS
	.globl		_SP_APSV
	.globl		_SRCH16
	.globl		_SRCH16N
	.globl		_ATARI
	.globl		_ATARIQ


*=============================================================================
*		ジ　ョ　イ　ス　テ　ィ　ッ　ク　入　力
*=============================================================================
*［使い方］
*
*	ＳＴＩＣＫ＿ＩＮＰ（ｎ）
*
*		ｎ＝０：Ｘ方向のスティックの検索
*		ｎ＝１：Ｙ方向のスティックの検索
*
*［戻り値］
*
*		－１，０，１
*
*-----------------------------------------------------------------------------
	.text
	.even

_STICK_INP:
	move.w	JOY_BUF,d0
	lea	STICK_STICK,a0
	tst.w	6(sp)
	beq	STICK_X

STICK_Y:
	add.w	d0,d0
	add.w	d0,d0
	andi.w	#12,d0
	adda.w	d0,a0
	move.l	(a0),d0
	rts

STICK_X:
	andi.w	#12,d0
	adda.w	d0,a0
	move.l	(a0),d0
	rts

STICK_STICK:

	dc.l	0,1,-1,0

REG_REG:
	dc.l	0

JOY_BUF:
	dc.w	$000f

*=============================================================================
*		ト　リ　ガ　入　力
*=============================================================================
*［使い方］
*
*	ＴＲＩＧＧＥＲ（）	引き数は無し
*
*［戻り値］
*
*		０：ボタンがどちらも押されていない
*		１：Ａボタンが押されている
*		２：Ｂボタンが押されている
*		３：Ａボタン，Ｂボタンとも押されている
*
*-----------------------------------------------------------------------------
	.even

_TRIGGER:
	move.w	JOY_BUF,d0
	not.w	d0
	lsr.w	#5,d0
	andi.w	#3,d0
	ext.l	d0			*リターン　０－３
	rts


*=============================================================================
*　　 	ス　プ　ラ　イ　ト　格　納
*=============================================================================
*［使い方］
*
*	ＳＰ＿ＡＰＳ（Ｐｎｏ，Ｘ，Ｙ，Ｐｃｏ，Ｐｌ）
*
*		Ｐｎｏ：プレーン番号		（０－１２７）
*		Ｘ，Ｙ：表示座標		（０－２５５，０－２５５）
*		Ｐｃｏ：パターンコード
*		Ｐｌ　：プライオリティ指定	（０－３）
*
*-----------------------------------------------------------------------------
	.even

_SP_APS:

	move.l	#$eb0000,d0		*Sprite Register Adress
	move.w	6(sp),d0
	lsl.w	#3,d0

	move.l	END_ADR,a0

	move.l	d0,(a0)+
	move.w	10(sp),(a0)+		*Write Sprite Datas
	move.w	14(sp),(a0)+
	move.w	18(sp),(a0)+
	move.w	22(sp),(a0)+

	move.l	a0,END_ADR

	rts

*=============================================================================
*　　	ス　プ　ラ　イ　ト　一　括　表　示　ル　ー　チ　ン
*=============================================================================
*［使い方］
*
*	ＳＰ＿ＡＰＳＶ（Ｐｎｏ，Ｘ，Ｙ，Ｐｃｏ，Ｐｌ）
*
*		Ｐｎｏ：プレーン番号		（０－１２７）
*		Ｘ，Ｙ：表示座標		（０－２５５，０－２５５）
*		Ｐｃｏ：パターンコード
*		Ｐｌ　：プライオリティ指定	（０－３	）
*

*-----------------------------------------------------------------------------
	.even

_SP_APSV:

	movem.l	a1-a2,-(sp)		*Push Registers

	move.l	END_ADR,a1
	clr.l	(a1)

	sub.l	a1,a1			*Super Visor Mode
	IOCS	_B_SUPER
	move.l	d0,SSP_SAVE

	move.w	$e9a000,JOY_BUF		*Read Joy Stick Data

	movea.l	#$e88001,a1		*Gpip Data Register
APSV_VDISP:
	btst.b	#4,(a1)			*V-DISP Check
	bne	APSV_VDISP

*	bclr	#9,$EB0808		*Disp Off（チラツキの原因）

	lea	BUF_TOP,a1
	move.l	(a1)+,d0
	beq	APSV_SKIP

APSV_LOOP:
	movea.l	d0,a2
	move.l	(a1)+,(a2)+		*Write Sprite Registers
	move.l	(a1)+,(a2)+
	move.l	(a1)+,d0
	bne	APSV_LOOP

APSV_SKIP:
*	bset	#9,$EB0808		*DISP On（こっちも）

	move.l	SSP_SAVE,a1		*User Mode
	IOCS	_B_SUPER

APSV_SKIP2:
	move.l	#$eb0000,d0
	move.w	14(sp),d0
	lsl.w	#3,d0

	lea	BUF_TOP,a1

	move.l	d0,(a1)+
	move.w	18(sp),(a1)+		*Write Sprite Datas
	move.w	22(sp),(a1)+
	move.w	26(sp),(a1)+
	move.w	30(sp),(a1)+

	move.l	a1,END_ADR

	movem.l	(sp)+,a1-a2		*POP Registers

	rts

SSP_SAVE:
	.dc.l	0

END_ADR:
	.dc.l	BUF_TOP

	.bss
BUF_TOP:
	.ds.w	1000			*SP REG buffer











	.text
	.even

*=============================================================================
*　　 		１　６　方　向　サ　ー　チ　Ｖｅｒ２．１０
*=============================================================================
*［使い方］
*
*	ＳＲＣＨ１６（ｘ１，ｙ１，ｘ２，ｙ２）
*
*		ｘ１：自機のｘ座標
*		ｙ１：自機のｙ座標
*		ｘ２：敵のｘ座標
*		ｙ１：敵のｙ座標
*
*［戻り値］
*
*	真上の方向から３６０度を時計周りに１６に分けて
*
*	敵から見た自機の方向を０－１５の値で返す
*
*-----------------------------------------------------------------------------

	.even

_SRCH16:
	movem.l	d2-d5/a0,-(sp)

	moveq	#0,d3
	moveq	#0,d4
	move.w	26(sp),d3		*自機の座標	Ｘ
	move.w	30(sp),d4		*		Ｙ

	moveq	#0,d5

	sub.w	34(sp),d3		*敵の座標	Ｘ
	bpl	S16_TOBI1
	addq	#4,d5

S16_TOBI1:
	sub.w	38(sp),d4		*		Ｙ
	bpl	S16_TOBI2
	addq	#2,d5

S16_TOBI2:
	tst.w	d3			*Ｘは０か？
	bne	S16_REG_SET
	addq.l	#1,d3			*０で除算すると
					*ERRORなので＋１する
S16_REG_SET:
	lea	S16_JMP_TBL,a0
	jmp	0(a0,d5.l)
	nop

S16_JMP_TBL:
	bra	S16_D04_R1
	bra	S16_D00_R0
	bra	S16_D08_R0
	bra	S16_D12_R1
	nop

S16_D04_R1:
	moveq	#4,d0			*ｄｉｒ＝４　，Ｒｖ＝１
	moveq	#1,d2
	bra	S16_MAIN

S16_D00_R0:
	neg.w	d4			*ｄｉｒ＝０　，Ｒｖ＝０
	moveq	#0,d0
	moveq	#0,d2
	bra	S16_MAIN

S16_D08_R0:
	neg.w	d3			*ｄｉｒ＝８　，Ｒｖ＝０
	moveq	#8,d0
	moveq	#0,d2
	bra	S16_MAIN

S16_D12_R1:
	neg.w	d3			*ｄｉｒ＝１２，Ｒｖ＝１
	neg.w	d4
	moveq	#12,d0
	moveq	#1,d2

S16_MAIN:
	lsl.w	#7,d4
	divu	d3,d4

	tst.b	d2			*Ｒｖ（リバース）が
	bne	S16_RV_1		*１ならジャンプ

S16_RV_0:
	cmpi.w	#531,d4
	bpl	S16_EXIT1
	addq	#1,d0

	cmpi.w	#282,d4
	bpl	S16_EXIT1
	addq	#1,d0

	cmpi.w	#91,d4
	bpl	S16_EXIT1
	addq	#1,d0

	cmpi.w	#39,d4
	bpl	S16_EXIT1
	addq	#1,d0

S16_EXIT1:
	andi.l	#$0000_000f,d0
	add.w	d0,d0
	movem.l	(sp)+,d2-d5/a0
	rts

S16_RV_1:
	cmpi.w	#39,d4
	bmi	S16_EXIT2
	addq	#1,d0

	cmpi.w	#91,d4
	bmi	S16_EXIT2
	addq	#1,d0

	cmpi	#282,d4
	bmi	S16_EXIT2
	addq	#1,d0

	cmpi.w	#531,d4
	bmi	S16_EXIT2
	addq	#1,d0

S16_EXIT2:
	andi.l	#$000f,d0
	add.w	d0,d0
	movem.l	(sp)+,d2-d5/a0
	rts

*********************************************************************************************
	.text
	.even

_SRCH16N:
	movem.l	d2-d5/a0,-(sp)

	moveq	#0,d3
	moveq	#0,d4
	move.w	26(sp),d3		*自機の座標	Ｘ
	move.w	30(sp),d4		*		Ｙ

	moveq	#0,d5

	sub.w	34(sp),d3		*敵の座標	Ｘ
	bpl	S16N_TOBI1
	addq	#4,d5

S16N_TOBI1:
	sub.w	38(sp),d4		*		Ｙ
	bpl	S16N_TOBI2
	addq	#2,d5

S16N_TOBI2:
	tst.w	d3			*Ｘは０か？
	bne	S16N_REG_SET
	addq.l	#1,d3			*０で除算すると
					*ERRORなので＋１する
S16N_REG_SET:
	lea	S16N_JMP_TBL,a0
	jmp	0(a0,d5.l)
	nop

S16N_JMP_TBL:
	bra	S16N_D04_R1
	bra	S16N_D00_R0
	bra	S16N_D08_R0
	bra	S16N_D12_R1
	nop

S16N_D04_R1:
	moveq	#4,d0			*ｄｉｒ＝４　，Ｒｖ＝１
	moveq	#1,d2
	bra	S16N_MAIN

S16N_D00_R0:
	neg.w	d4			*ｄｉｒ＝０　，Ｒｖ＝０
	moveq	#0,d0
	moveq	#0,d2
	bra	S16N_MAIN

S16N_D08_R0:
	neg.w	d3			*ｄｉｒ＝８　，Ｒｖ＝０
	moveq	#8,d0
	moveq	#0,d2
	bra	S16N_MAIN

S16N_D12_R1:
	neg.w	d3			*ｄｉｒ＝１２，Ｒｖ＝１
	neg.w	d4
	moveq	#12,d0
	moveq	#1,d2

S16N_MAIN:
	lsl.w	#7,d4
	divu	d3,d4

	tst.b	d2			*Ｒｖ（リバース）が
	bne	S16N_RV_1		*１ならジャンプ

S16N_RV_0:
	cmpi.w	#531,d4
	bpl	S16N_EXIT1
	addq	#1,d0

	cmpi.w	#282,d4
	bpl	S16N_EXIT1
	addq	#1,d0

	cmpi.w	#91,d4
	bpl	S16N_EXIT1
	addq	#1,d0

	cmpi.w	#39,d4
	bpl	S16N_EXIT1
	addq	#1,d0

S16N_EXIT1:
	andi.l	#$0000_000f,d0
*	add.w	d0,d0
	movem.l	(sp)+,d2-d5/a0
	rts

S16N_RV_1:
	cmpi.w	#39,d4
	bmi	S16N_EXIT2
	addq	#1,d0

	cmpi.w	#91,d4
	bmi	S16N_EXIT2
	addq	#1,d0

	cmpi	#282,d4
	bmi	S16N_EXIT2
	addq	#1,d0

	cmpi.w	#531,d4
	bmi	S16N_EXIT2
	addq	#1,d0

S16N_EXIT2:
	andi.l	#$000f,d0
*	add.w	d0,d0
	movem.l	(sp)+,d2-d5/a0
	rts






	.even
	.text
*=============================================================================
*	座　標　に　よ　る　当　た　り　判　定		Ｖｅｒ２．００
*=============================================================================
*［使い方］
*
*	ＡＴＡＲＩＱ（ｘ１，ｙ１，ｘ２，ｙ２，ｅｘ１，ｅｙ１，ｅｘ２，ｅｙ２）
*
*		ｘ１　：自機の左上のＸ座標	20(sp)
*		ｙ１　：自機の左上のＹ座標	24(sp)
*		ｘ２　：自機の右下のＸ座標	28(sp)
*		ｙ２　：自機の右下のＹ座標	32(sp)
*		ｅｘ１：敵の左上のＸ座標	36(sp)
*		ｅｙ１：敵の左上のＹ座標	40(sp)
*		ｅｘ２：敵の右下のＸ座標	44(sp)
*		ｅｙ２：敵の右下のＹ座標	48(sp)
*
*［戻り値］
*		０　　：当たっていない
*		１　　：当たっている
*
*-----------------------------------------------------------------------------

	.even

X1	equ	6
Y1	equ	10
X2	equ	14
Y2	equ	18
EX1	equ	22
EY1	equ	26
EX2	equ	30
EY2	equ	34

_ATARIQ:
A2_Y_CHK:
	move.w	Y1(sp),d0
	sub.w	EY1(sp),d0
	bmi	A2_SKIP1

	sub.w	EY2(sp),d0
	bge	A2_D0_0
	bra	A2_X_CHK

A2_SKIP1:
	neg.w	d0
	sub.w	Y2(sp),d0
	bge	A2_D0_0

A2_X_CHK:
	move.w	X1(sp),d0
	sub.w	EX1(sp),d0
	bmi	A2_SKIP2

	sub.w	EX2(sp),d0
	bge	A2_D0_0
	moveq	#1,d0
	rts

A2_SKIP2:
	neg.w	d0
	sub.w	X2(sp),d0
	bge	A2_D0_0
	moveq	#1,d0
	rts

A2_D0_0:
	moveq	#0,d0
	rts

*=============================================================================
*	座　標　に　よ　る　当　た　り　判　定		Ｖｅｒ２．００
*=============================================================================
*	ＡＴＡＲＩ（ｘ１，ｙ１，ｘ２，ｙ２，ｅｘ１，ｅｙ１，ｅｘ２，ｅｙ２）
*
*		ｘ１　：自機の左上のＸ座標	20(sp)
*		ｙ１　：自機の左上のＹ座標	24(sp)
*		ｘ２　：自機の右下のＸ座標	28(sp)
*		ｙ２　：自機の右下のＹ座標	32(sp)
*		ｅｘ１：敵の左上のＸ座標	36(sp)
*		ｅｙ１：敵の左上のＹ座標	40(sp)
*		ｅｘ２：敵の右下のＸ座標	44(sp)
*		ｅｙ２：敵の右下のＹ座標	48(sp)
*
*［戻り値］
*		０　　：当たっていない
*		１　　：当たっている
*
*-----------------------------------------------------------------------------

	.even

XX1	equ	22
YY1	equ	26
XX2	equ	30
YY2	equ	34
EXX1	equ	38
EYY1	equ	42
EXX2	equ	46
EYY2	equ	50

_ATARI:
	movem.l	d1-d3/a0,-(sp)		*レジスタを待避

	moveq	#0,d1
	moveq	#0,d2
	moveq	#0,d3
	move.w	XX1(sp),d1		*ｄ１＝ｘ１
	move.w	YY1(sp),d2		*ｄ２＝ｙ１

	sub.w	EXX1(sp),d1		*ｄ１－＝ｅｘ１
	bpl	ATARI_SKIP1
	moveq	#4,d3

ATARI_SKIP1:
	sub.w	EYY1(sp),d2		*ｄ２－＝ｅｙ１
	bpl	ATARI_CHK1
	addq	#2,d3

ATARI_CHK1:
	lea	ATARI_JTBL1,a0		*ｄ３をインデックス
	jmp	0(a0,d3.l)		*にしてジャンプ

ATARI_JTBL1:
	bra	ATARI_XP_YP		*ｘ＝正，ｙ＝正
	bra	ATARI_XP_YM		*ｘ＝正，ｙ＝負
	bra	ATARI_XM_YP		*ｘ＝負，ｙ＝正
	bra	ATARI_XM_YM		*ｘ＝負，ｙ＝負
	nop

ATARI_XP_YP:
	move.w	EYY2(sp),d2		*ｄ２＝ｅｙ２
	sub.w	YY1(sp),d2		*ｄ２－＝ｙ１
	bmi	ATARI_D0_0

	move.w	EXX2(sp),d1		*ｄ１＝ｅｘ２
	sub.w	XX1(sp),d1		*ｄ１－＝ｘ１
	bmi	ATARI_D0_0
	bra	ATARI_D0_1

ATARI_XP_YM:

	move.w	YY2(sp),d2		*ｄ２＝ｙ２
	sub.w	EYY1(sp),d2		*ｄ２－＝ｅｙ１
	bmi	ATARI_D0_0

	move.w	XX1(sp),d1		*ｄ１＝ｘ１
	sub.w	EXX2(sp),d1		*ｄ１－＝ｅｘ２
	bpl	ATARI_D0_0
	bra	ATARI_D0_1

ATARI_XM_YP:
	move.w	EYY2(sp),d2		*ｄ２＝ｅｙ２
	sub.w	YY1(sp),d2		*ｄ２－＝ｙ１
	bmi	ATARI_D0_0

	move.w	EXX1(sp),d1		*ｄ１＝ｅｘ１
	sub.w	XX2(sp),d1		*ｄ１－＝ｘ２
	bpl	ATARI_D0_0
	bra	ATARI_D0_1

ATARI_XM_YM:
	move.w	YY2(sp),d2		*ｄ２＝ｙ２
	sub.w	EYY1(sp),d2		*ｄ２－＝ｅｙ１
	bmi	ATARI_D0_0

	move.w	XX2(sp),d1		*ｄ１＝ｘ２
	sub.w	EXX1(sp),d1		*ｄ１－＝ｅｘ１
	bmi	ATARI_D0_0
	bra	ATARI_D0_1

ATARI_D0_0:
	moveq.l	#0,d0			*ｄ０＝０（ハズレ）
	movem.l	(sp)+,d1-d3/a0		*レジスタを復帰
	rts

ATARI_D0_1:
	moveq.l	#1,d0			*ｄ０＝１（アタリ）
	movem.l	(sp)+,d1-d3/a0		*レジスタを復帰
	rts



	.text
*=============================================================================
*		ジ　ョ　イ　ス　テ　ィ　ッ　ク　入　力
*=============================================================================
*［使い方］
*
*	ＳＴＩＣＫ＿ＩＮＰ（ｎ）
*
*		ｎ＝０：Ｘ方向のスティックの検索
*		ｎ＝１：Ｙ方向のスティックの検索
*
*［戻り値］
*
*		－１，０，１
*
*-----------------------------------------------------------------------------
	.even

_STICK_INP_NML:
	movem.l	d1-d2/a0,-(sp)		*PUSH d1,d2,a0

	move.l	16(sp),d2
	andi.l	#1,d2

	moveq	#0,d1			*ジョイスティック入力
	IOCS	_JOYGET

	lsl.w	#2,d2
	lea	STICK_TBL0,a0
	jmp	0(a0,d2.l)

STICK_TBL0:
	lsr.w	#1,d0
	bra	STICK_FIX
	lsl.w	#1,d0
	bra	STICK_FIX

	nop

STICK_FIX:
	andi.l	#6,d0
	lea	STICK_TBL,a0
	jmp	0(a0,d0.l)

STICK_TBL:
	nop
	bra.s	STICK_LU
	bra.s	STICK_RD
	bra.s	STICK_D0_0

STICK_LU:
	moveq	#1,d0
	movem.l	(sp)+,d1-d2/a0		*POP  d1,d2,a0
	rts

STICK_RD:
	moveq	#-1,d0
	movem.l	(sp)+,d1-d2/a0
	rts

STICK_D0_0:
	moveq	#0,d0
	movem.l	(sp)+,d1-d2/a0
	rts

*=============================================================================
*		ト　リ　ガ　入　力
*=============================================================================
*［使い方］
*
*	ＴＲＩＧＧＥＲ（）	引き数は無し
*
*［戻り値］
*
*		０：ボタンがどちらも押されていない
*		１：Ａボタンが押されている
*		２：Ｂボタンが押されている
*		３：Ａボタン，Ｂボタンとも押されている
*
*-----------------------------------------------------------------------------
		.even

_TRIGGER_NML:
	movem.l	d1,-(sp)		*PUSH d1

	moveq	#0,d1
	IOCS	_JOYGET

	neg.b	d0
	lsr.b	#5,d0
	andi.l	#$0000_0003,d0		*リターン　０－３

	movem.l	(sp)+,d1		*POP  d1

	rts




*=============================================================================
*	　　Ｅ　ｎ　ｄ　　Ｏ　ｆ　　Ｐ　ｒ　ｏ　ｇ　ｒ　ａ　ｍ
*=============================================================================
