
	.include	iocscall.mac
	.include	doscall.mac

	.globl	_INT_CHK

*========================================================================
*　わ　り　こ　み　を　し　ら　べ　る
*========================================================================

	.text
	.even

_INT_CHK:
	sub.l	a1,a1			*To Super Visor Mode
	iocs	_B_SUPER
	move.l	d0,USER_SSP

	move.l	#$e88007,a0		*Timer-A Interrupt Check
	lea		err0,a1
	btst.b	#5,(a0)
	bne		INT_ERR

	lea		err1,a1
	btst.b	#7,(a0)			*H-Sync  Interrupt Check
	bne		INT_ERR

	lea		err2,a1
	btst.b	#6,(a0)			*Raster  Interrupt Check
	bne		INT_ERR

	lea		err3,a1
	move.l	#$e88009,a0		*Timer-D Interrupt Check
	btst.b	#4,(a0)
	bne		INT_ERR

INT_OK:
	move.l	USER_SSP,a1		*To User Mode
	iocs	_B_SUPER
	clr.l	d0
	rts

INT_ERR:
	move.l	#$21,d0
	iocs	_B_PRINT
	move.l	USER_SSP,a1		*To User Mode
	iocs	_B_SUPER
	moveq	#$ff,d0
	rts



	.data
	.even

USER_SSP:
	ds.l	1

err0:
	dc.b	'垂直同期割り込みが使用されています',$d,$a,0
.even
err1:
	dc.b	'水平同期割り込みが使用されています',$d,$a,0
.even
err2:
	dc.b	'ラスター走査割り込みが使用されています',$d,$a,0
.even
err3:
	dc.b	'タイマーＤ割り込みが使用されています',$d,$a,0

	.end

