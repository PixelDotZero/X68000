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
	.global		_EGPUT
	.global		_TPUT
	.global		_SAC_COLOR
	.global		_SAC_COLOR2
	.global		_SAC_COLOR3
	.global		_GTSPRW
	.global		_TEX512CLR
	.global		_TEXSCROLL
	.global		_TEX_DISP
	.global		_VRAMCHK

	.global		_dotclr

	.text
*=============================================================================
*	�e�L�X�g�����E�v�b�g�E���[�`�� �@�@�@  by �������D�@�u�����D�Ă��ƔŁ{
*=============================================================================
*�m�g�����n
*
*	�s�o�t�s�i���P�C���P�C���Q�C���Q�C���������j
*
*		���P�F�n�_�i�O�`�P�O�Q�R�j
*		���P�F�n�_�i�O�`�P�O�Q�R�j
*		���Q�F�I�_�i�O�`�P�O�Q�R�j
*		���Q�F�I�_�i�O�`�P�O�Q�R�j
*	�@�@���������F�������ރf�[�^�̃A�h���X
*
*�m�߂�l�n
*
*	�Ȃ��Ȃ�܂���
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

	sub.w	d2,d4			*���[�v�񐔂����߂�
	sub.w	d1,d3

	lsl.l	#7,d2			*�A�h���X�v�Z
	add.l	d1,d2

	adda.l	d2,a2
	adda.l	d2,a3
	adda.l	d2,a4
	adda.l	d2,a5

	move.w	#127,d2
	sub.w	d3,d2

	suba.l	a1,a1			*�X�[�p�[�o�C�U�[��
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

LOOP_Y:
	move.w	d3,d1

LOOP_X:
	move.b	(a0)+,d0		*�ȉ��A�f�[�^�̃Z�b�g�B�������炵�����ǁA
	btst.l	#7,d0			*���̕����������炵�������Ȃ��H
	bne.w	LP_1
	bclr.b	#7,(a5)			*��ʂ��N���A����Ă���ΕK�v�Ȃ�
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

	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d4/a0-a5
	rts

	.even
*
_SAC_COLOR:
	movem.l	d1-d3/a0-a1,-(sp)
	move.w	26(sp),d1		*�p���b�g�E�i���o�[�i�O�`�P�T�j
	move.w	30(sp),d2		*�J���[�@�@�@�@�@�@�i�O�`�U�T�T�R�T�j
	move.w	34(sp),d3		*�p���b�g�E�u���b�N�i�P�`�P�T�j

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
	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER
	movem.l	(sp)+,d2/a0-a1
	rts

PLT_TBL:
	dc.w	$200,$220,$240,$260,$280,$2a0,$2c0,$2e0
	dc.w	$300,$320,$340,$360,$380,$3a0,$3c0,$3e0

.text
*=============================================================================
*	�����������[�`���iTBL_2DOT�j           by �������D    Updated:90/07/15
*=============================================================================
*�m�g�����n
*
*	�r�q�b�g�R�Q�i���P�C���P�C���Q�C���Q�j
*
*		���P�F���@�̂����W
*		���P�F���@�̂����W
*		���Q�F�G�̂����W
*		���Q�F�G�̂����W
*
*�m�߂�l�n
*
*	�^��H�̕�������R�U�O�x�����v����ɂR�Q�ɕ�����
*
*	�G���猩�����@�̕������O�|�R�P�̒l�ŕԂ��B
*
*	�����́A�����Ȃ�܂����B
*
*-----------------------------------------------------------------------------
*
	.even
*
_SRCH32_:
	movem.l	d1-d4/a0,-(sp)

	move.w	26(sp),d1		*���Ԃ�w
	move.w	30(sp),d2		*���Ԃ�x
	move.w	34(sp),d3		*�Ă��@�w
	move.w	38(sp),d4		*�Ă��@�x

	moveq.l	#0,d0

	cmp.w	d1,d3			*�����ƓG�̂w���r
	bpl.w	Y_CHECK
	addq.w	#2,d0
Y_CHECK:
	cmp.w	d2,d4			*�����ƓG�̂x���r
	bpl.w	CHECK_END
	addq.w	#4,d0
CHECK_END:
	jmp	JMP_TBL(pc,d0.w)

DIR_S00:
	sub.w	d1,d3			*�w�|�w���w
	sub.w	d4,d2			*�x�|�x���x
*	andi.w	#$00ff,d3
	lsr.w	#1,d3			*�w�^�Q���w
	andi.w	#$00fe,d2		*1111_1110�E�E�E�Q�̔{���ɂ���
	lsl.w	#6,d2			*�x��128
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
	bne.w	CHECK_OVER		*���̕����́A�e�X�g�ׂ̈̂��̂�
	moveq.l	#0,d0			*�g�p����ꍇ�́A�����ĉ������B
CHECK_OVER:				*
	movem.l	(sp)+,d1-d4/a0
	rts

JMP_TBL:
	bra.s	DIR_S04			*�����ɃW�����v�e�[�u����u�����Ƃɂ��A
	bra.s	DIR_S08			*�S�Ă��V���[�g�u�����`�ł��ށB
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
*	�����������[�`���iTBL_4DOT�j           by �������D    Updated:90/07/15
*=============================================================================
*�m�g�����n
*
*	�r�q�b�g�R�Q�S�i���P�C���P�C���Q�C���Q�j
*
*		���P�F���@�̂����W
*		���P�F���@�̂����W
*		���Q�F�G�̂����W
*		���Q�F�G�̂����W
*
*�m�߂�l�n
*
*	�^��H�̕�������R�U�O�x�����v����ɂR�Q�ɕ�����
*
*	�G���猩�����@�̕������O�|�R�P�̒l�ŕԂ��B
*
*	��̂�葁���B�Ȃ��ł��傤�H�@����́A�V�t�g���鐔�����Ȃ�����ł��B�]����
*
*-----------------------------------------------------------------------------
*
	.even

_SRCH32:
	movem.l	d1-d4/a0,-(sp)

	move.w	26(sp),d1		*���Ԃ�w
	ext.l	d1
	move.w	30(sp),d2		*���Ԃ�x
	move.w	34(sp),d3		*�Ă��@�w
	move.w	38(sp),d4		*�Ă��@�x



	moveq.l	#0,d0

	cmp.w	d1,d3			*�����ƓG�̂w���r
	bpl.w	Y_CHECK4
	addq.w	#2,d0
Y_CHECK4:
	cmp.w	d2,d4			*�����ƓG�̂x���r
	bpl.w	CHECK_END4
	addq.w	#4,d0
CHECK_END4:
	jmp	JMP_TBL4(pc,d0.w)

DIR_S004:
	sub.w	d1,d3			*�w�|�w���w
	sub.w	d4,d2			*�x�|�x���x
*	andi.w	#$00ff,d3
	lsr.w	#2,d3			*�w�^�S���w
	andi.w	#$00fc,d2		*1111_1100�E�E�E4�̔{���ɂ���
	lsl.w	#4,d2			*�x��64
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
	bne.w	CHECK_OVER4		*���̕����́A�e�X�g�ׂ̈̂��̂�
	moveq.l	#0,d0			*�g�p����ꍇ�́A�����ĉ������B
CHECK_OVER4:				*
	movem.l	(sp)+,d1-d4/a0
	rts

JMP_TBL4:
	bra.s	DIR_S044		*�����ɃW�����v�e�[�u����u�����Ƃɂ��A
	bra.s	DIR_S084		*�S�Ă��V���[�g�u�����`�ł��ށB
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

	move.w	26(sp),d1		*���Ԃ�w
	move.w	30(sp),d2		*���Ԃ�x
	move.w	34(sp),d3		*�Ă��@�w
	move.w	38(sp),d4		*�Ă��@�x

	moveq.l	#0,d0

	cmp.w	d1,d3			*�����ƓG�̂w���r
	bpl.s	Y_CHECKR
	addq.w	#2,d0
Y_CHECKR:
	cmp.w	d2,d4			*�����ƓG�̂x���r
	bpl.s	CHECK_ENDR
	addq.w	#4,d0
CHECK_ENDR:
	jmp	JMP_TBLR(pc,d0.w)

DIR_S00R:
	sub.w	d1,d3			*�w�|�w���w
	sub.w	d4,d2			*�x�|�x���x
	lsr.w	#2,d3			*�w�^�Q���w
	andi.w	#$00fc,d2		*1111_1110�E�E�E�Q�̔{���ɂ���
	lsl.w	#4,d2			*�x��128
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
	bra.s	DIR_S04R			*�����ɃW�����v�e�[�u����u�����Ƃɂ��A
	bra.s	DIR_S08R			*�S�Ă��V���[�g�u�����`�ł��ށB
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
*	�`�c�o�b�l�@�c�q�h�u�h�m�f�@�r�x�r�s�d�l�@�i�m�m�o�b�l�c�q�u�j		�f�n�q�q�x�D
*								UPDATED:90/07/24   BY �������D
*---------------------------------------------------------------------------------------------
*
*�m�g�p���@�n
*
*	�m�m�o�b�l�n�m�i�j		�풓�J�n
*	�m�m�o�b�l�n�e�e�i�j		�풓����
*	�m�m�h�m�h�s�i�j
*	�m�m�o�k�`�x�i�o�b�l�擪�A�h���X�C���������Q�T�U�{�Đ����g���C�Đ����钷���j
*	�m�m�r�s�n�o�i�j
*	�m�m�r�s�`�s�i�j	[�Ԃ�l]	�@�@�O�F��Đ���
*						���̑��F�Đ���
*
*		�Đ����g��	�O�@�`�@�S
*		�p���|�b�g	�O�@�`�@�R
*		�Đ����钷���͂U�S���܂łł��B
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
	move.b	#$0b,$E9A005	���g���ݒ�
	lea	$e92001,a0
	move.b	#1,(a0)		�`�c�o�b�l stop
	moveq.l	#1,d1
	bsr	adpcm_monitor
	move.w	#500,d0
adpcm_init_1
	dbra	d0,adpcm_init_1

	move.b	#$08,$E9A005	���g���ݒ�
	moveq.l	#0,d1
	bsr	adpcm_monitor
	moveq.l	#127,d0
	rts


adpcm_play
	move.b	#$10,$E840C7	�c�l�`������~

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
	move.b	#$1b,(a0)	*�{���͊��荞�݂��~�߂čs���ׂ��Ȃ̂��E�E�E�B
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

*�@�A���C�E�`�F�[���E���[�h�]��			from TONBE.

	move.b	#$3A,$E840C5	�c�l�`�I�y���[�V�����ݒ�
	st	$E840C0		�`�����l���E�X�e�[�^�X�E�N���A
	move.l	A0,$E840DC	�x�[�X�E�A�h���X
	move.w	#2,$E840DA	�]���u���b�N��
	move.b	#$88,$E840C7	�c�l�`����X�^�[�g
	move.b	D1,$E9A005	���g���ݒ�
	move.b	#2,$E92001	�`�c�o�b�l�Đ��J�n

	lea	adpcm_status(pc),a0
	move.b	#1,(a0)

	lea	adpcm_pan(pc),a0
	move.b	d1,(a0)

	lea	adpcm_monitor_switch(pc),a0
	clr.b	(a0)

ret
	rts

adpcm_record

	move.b	#$10,$E840C7	�c�l�`������~
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
	move.b	#$1b,(a0)	*�{���͊��荞�݂��~�߂čs���ׂ��Ȃ̂��E�E�E�B
	move.b	d0,2(a0)

	cmpi.b	#3,d1
	bcc	ret
	move.b	d1,d0
	lsl.b	#2,d0

	lsr.w	#8,d1		*pan
	eori.b	#3,d1
	or.b	d0,d1

*�@�m�[�}���E���[�h�]��		from TONBE.

	move.b	#$B2,$E840C5	�c�l�`�I�y���[�V�����ݒ�
	st	$E840C0		�`�����l���E�X�e�[�^�X�E�N���A
	move.l	A1,$E840CC	�������E�A�h���X
	move.w	D2,$E840CA	�]���o�C�g��
	move.b	#$88,$E840C7	�c�l�`����X�^�[�g
	move.b	D1,$E9A005	���g���ݒ�
	move.b	#4,$E92001	�`�c�o�b�l�^���J�n

	lea	adpcm_status(pc),a0
	move.b	#2,(a0)

	lea	adpcm_pan(pc),a0
	move.b	d0,(a0)

	lea	adpcm_monitor_switch(pc),a0
	clr.b	(a0)

	rts

adpcm_stop

*�@�c�l�`�]���I�����荞�݁i�x�N�^���U�`�j	*from TONBE.

	move.b	#$10,$E840C7	�c�l�`������~
	st	$E840C0		�`�����l���E�X�e�[�^�X�E�N���A
	move.b	#$08,$E92003	��������ƁA�n�e�e���̃v�c���ĉ����o�Ȃ�
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
	move.b	#$10,$E840C7	�c�l�`������~
	st	$E840C0		�`�����l���E�X�e�[�^�X�E�N���A
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
	move.b	#$08,$E92003	��������ƁA�n�e�e���̃v�c���ĉ����o�Ȃ�
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
*	�r�`�b�Q�b�n�k�n�q�R�i�O���t�B�b�N�p���b�g�ꊇ�ݒ�j
*=============================================================================
*�m�g�����n
*
*	�r�`�b�Q�b�n�k�n�q�R�i�@�A�h���X�@�j
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
	move.l	SSP_WORK,a1		*���[�U���[�h��

	iocs	_B_SUPER
	movem.l	(sp)+,a0-a1
	rts


	.text
*=============================================================================
*	�f�q�^�s�w�^�r�o�ԗD��x�ݒ�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ by �������D
*=============================================================================
*�m�g�����n
*00 00.1001
*	�f�s�r�o�q�v�i�r�o�D��x �s�w�D��x �f�q�D��x�j
*
*	�@�@�@      �@�D��x�P�@�O�O�@��
*	�@�@�@�@�@ �@ �D��x�Q�@�O�P�@�b
*	�@    �@�@ �@ �D��x�R�@�P�O�@��
*
*	�@�@�@��F�r�o�@���@�f�q�@���@�s�w�@�̏ꍇ
*
*	�@      �@�r�o���O�O�C�s�w���P�O�C�f�q���O�P�Ȃ̂ŁA
*
*	          �f�s�r�o�q�v�i�O���O�X�j�ƂȂ�
*
*	���ӁF��ʂQ�r�b�g�͂O�ɂ��ĉ������܂��B
*	�@�@�@�v����ɁA�r�o�̑O�̂Q�r�b�g�B
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
*=============================================================================
*�e�L�X�g512x512��ʂ̍���?�N���A								   BY ���ψ���
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
*�e�L�X�g��ʂ̕\���n�m�^�n�e�e
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

	.text
*=================================================================================
*	�^���r���I�_���a�O���t�B�b�N�����E�v�b�g�E���[�`���@  UPDATE by ���ψ���
*=================================================================================
*�m�g�����n
*	�f�[�^���e���[���̏ꍇ�A���́A���ɂu�q�`�l�̓��e���[���ȊO�̃f�[�^�������ꍇ��
*	�������݂��܂���B
*
*	�d�f�o�t�s�i���P�C���P�C���Q�C���Q�C���������C���������j
*
*		���P�F�n�_�i�O�`�T�P�P�j
*		���P�F
*		���Q�F�I�_�i�O�`�T�P�P�j
*		���Q�F
*	�@�@���������F�v���[���O�@�i���b�O�O�O�O�O�j
*	�@�@        �F�v���[���P  �i���b�W�O�O�O�O�j
*	�@�@        �F�v���[���Q�@�i���c�O�O�O�O�O�j
*	�@�@        �F�v���[���R�@�i���c�W�O�O�O�O�j
*	�@�@���������F�f�[�^�̃A�h���X
*---------------------------------------------------------------------------------
	.even
*
_EGPUT:
	movem.l	d1-d4/a0-a2,-(sp)

	move.w	34(sp),d1		*X1
	move.w	38(sp),d2		*Y1
	move.w	42(sp),d3		*X2
	move.w	46(sp),d4		*Y2
	move.l	48(sp),a2		*PLEAN
	move.l	52(sp),a0		*ADDRESS

	sub.w	d2,d4			*���[�v�񐔂����߂�
	sub.w	d1,d3
	subq.w	#1,d3

	add.w	d1,d1			*�A�h���X�̌v�Z�i���̂P�j
	adda.w	d1,a2
	moveq.l	#10,d1
	lsl.l	d1,d2
	adda.l	d2,a2
	move.w	d3,d2
	move.w	#510,d1
	sub.w	d2,d1
	add.w	d1,d1
	lsr.w	#1,d3
	moveq.l	#0,d0
	suba.l	a1,a1			*�X�[�p�[�o�C�U�[��
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

LOOP1:					*�v�b�g�i���C���j���[�`��
	move.w	d3,d2
LOOP2:

**	cmpi.w	#0,(a2)			*VRAM�Ƀf�[�^�����邩?
	tst.w	(a2)			*VRAM�Ƀf�[�^�����邩?
	bne.w	EGPUT00
	move.b	(a0),d0			*�f�[�^�ڑ�
	lsr.b	#4,d0
**	cmpi.b	#0,d0			*�f�[�^�̓[����?
	beq.w	EGPUT00
	move.w	d0,(a2)+		*��������
	bra.w	EGPUT01
EGPUT00:
	adda.w	#2,a2			*�������܂Ȃ������̂ŃA�h���X��i�߂�
EGPUT01:

	tst.w	(a2)			*VRAM�Ƀf�[�^�����邩?
	bne.w	EGPUT02
	move.b	(a0)+,d0		*�f�[�^�ڑ�
	andi.b	#$0f,d0
**	cmpi.b	#0,d0			*�f�[�^�̓[����?
	beq.w	EGPUT03
	move.w	d0,(a2)+		*��������
	bra.w	EGPUT04
EGPUT02:
	adda.w	#1,a0
EGPUT03:
	adda.w	#2,a2			*�������܂Ȃ������̂ŃA�h���X��i�߂�
EGPUT04:

	dbra.w	d2,LOOP2
	adda.w	d1,a2			*�w���W�̂���̏C��
	dbra.w	d4,LOOP1
	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d4/a0-a2
	rts
*=================================================================================
*	�O���t�B�b�N�����E�f�[�^�`�F�b�N�E���[�`���@   by ���ψ���
*=================================================================================
*�m�g�����n
*	�u�q�`�l�̓��e���[���ȊO�̃f�[�^�������ꍇ�A�P��Ԃ��܂��B
*	�f�[�^���e���[���Ȃ�[����Ԃ��܂��B
*
*	�u�q�`�l�b�g�j�i���C���C���������j
*
*			��	�F�O�`�T�P�P
*			��	�F�O�`�T�P�P
*	�@�@���������F�v���[���O�@�i���b�O�O�O�O�O�j
*	�@�@        �F�v���[���P  �i���b�W�O�O�O�O�j
*	�@�@        �F�v���[���Q�@�i���c�O�O�O�O�O�j
*	�@�@        �F�v���[���R�@�i���c�W�O�O�O�O�j

	.even
_VRAMCHK:

	movem.l	d1-d2/a0-a1,-(sp)
	move.l	20(sp),d1		*X
	move.l	24(sp),d2		*Y
	move.l	28(sp),a0		*PLEAN
	suba.l	a1,a1			*�X�[�p�[�o�C�U�[��
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	add.w	d1,d1
	adda.l	d1,a0
	moveq.l	#10,d1
	lsl.l	d1,d2
	adda.l	d2,a0
**	cmpi.w	#0,(a0)
	tst.w	(a0)
	bne		VRAMCHK00
	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER
	moveq.l	#0,d0			*�O������
	bra.w	VRAMCHK01
VRAMCHK00:					*�O�łȂ��������h�b�g���`����Ă�
	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER
	moveq.l	#1,d0
VRAMCHK01:

	movem.l	(sp)+,d1-d2/a0-a1
	rts

*�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
*		�s�`�h�s�n���j�n�m�`�l�h�I��ʃN���A
*	dotclr( int�@�J�E���^,char�@*�z��A�h���X,void	*�f�q�`�l�`�����D)
*�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	.text
	.even
_dotclr
	move.l	4(sp),d1		*�����J�E���^
	movea.l	8(sp),a0		*�ԍ��z��A�h���X
	move.l	12(sp),a2

	suba.l	a1,a1			*�X�[�p�[�o�C�U�[��
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

	moveq.l	#-1,d0			*�J�E���^������

dot_lp1
	addq.w	#1,d0			*���l�̂������ʒu�𓾂�

	move.b	(a0,d0.w),d2		*
	cmp.b	d1,d2			
	bne	dot_lp1

	ext.l	d0
	move.l	d0,d1

	andi.l	#$00000007,d0		*���ʂR�r�b�g���c���ă}�X�N
	add.l	d0,d0			*���[�h�A�N�Z�X�̂��߂Q�{����

	lsr.l	#3,d1			*�P�^�W
	moveq.l	#10,d2
	lsl.l	d2,d1			*�P�O�Q�S�{�i�P���C�����j

	add.l	d1,d0			*�������݃A�h���X�P

	move.w	#0,d1
dot_lp2
	movea.l	a2,a1
	move.w	#0,d2
	adda.l	d0,a1
dot_lp3
	move.w	#$0000,(a1)
	adda.l	#$10,a1

	addq.w	#1,d2
	cmpi.w	#64,d2
	blt	dot_lp3

	adda.l	#$2000,a2

	addq.w	#1,d1
	cmpi.w	#64,d1
	blt	dot_lp2

	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER

	rts


*=============================================================================
*	�e�L�X�g�X�N���[��
*=============================================================================
*�m�g�����n
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
