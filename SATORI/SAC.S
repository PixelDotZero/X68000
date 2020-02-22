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
*	�O���t�B�b�N�����E�v�b�g�E���[�`�� �@  by �������D�@�u�����D�O�D�P�R��
*=============================================================================
*�m�g�����n
*
*	�f�o�t�s�i���P�C���P�C���Q�C���Q�C���������C���������j
*
*		���P�F�n�_�i�O�`�T�P�P�j
*		���P�F
*		���Q�F�I�_�i�O�`�T�P�P�j
*		���Q�F
*	�@�@���������F�v���[���O�@�i���b�O�O�O�O�O�j
*	�@�@        �F�v���[���P  �i���b�W�O�O�O�O�j
*	�@�@        �F�v���[���Q�@�i���c�O�O�O�O�O�j
*	�@�@        �F�v���[���R�@�i���c�W�O�O�O�O�j
*	�@�@���������F�������ރf�[�^�̃A�h���X
*
*�m�߂�l�n
*
*	�Ȃ��Ȃ�܂���
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

	suba.l	a1,a1			*�X�[�p�[�o�C�U�[��
	iocs	_B_SUPER
	move.l	d0,SSP_WORK

LOOP1:					*�v�b�g�i���C���j���[�`��
	move.w	d3,d2
LOOP2:
	move.b	(a0),d0
	lsr.b	#4,d0
	swap.w	d0
	move.b	(a0)+,d0
	move.l	d0,(a2)+		*�Q�h�b�g���܂Ƃ߂ď������ށi�UCLOCK�̂������j
	dbra.w	d2,LOOP2
	adda.w	d1,a2			*�w���W�̂���̏C��
	dbra.w	d4,LOOP1

	move.l	SSP_WORK,a1		*���[�U���[�h��
	iocs	_B_SUPER
	movem.l	(sp)+,d1-d4/a0-a2
	rts