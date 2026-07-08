	.file	"stoib.c"
	.option pic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	char_to_digit
	.type	char_to_digit, @function
char_to_digit:
.LFB23:
	.cfi_startproc
	addiw	a5,a0,-48
	andi	a5,a5,0xff
	li	a4,9
	bgtu	a5,a4,.L2
	addiw	a0,a0,-48
.L3:
	sext.w	a1,a1
	ble	a1,a0,.L7
.L4:
	ret
.L2:
	addiw	a5,a0,-65
	andi	a5,a5,0xff
	li	a4,25
	bgtu	a5,a4,.L5
	addiw	a0,a0,-55
	j	.L3
.L5:
	li	a0,-1
	ret
.L7:
	li	a0,-1
	ret
	.cfi_endproc
.LFE23:
	.size	char_to_digit, .-char_to_digit
	.align	1
	.globl	stoib
	.type	stoib, @function
stoib:
.LFB24:
	.cfi_startproc
	addi	sp,sp,-80
	.cfi_def_cfa_offset 80
	sd	ra,72(sp)
	sd	s1,56(sp)
	.cfi_offset 1, -8
	.cfi_offset 9, -24
	beq	a0,zero,.L16
	sd	s0,64(sp)
	sd	s3,40(sp)
	sd	s4,32(sp)
	.cfi_offset 8, -16
	.cfi_offset 19, -40
	.cfi_offset 20, -48
	mv	s0,a0
	mv	s3,a1
	mv	s4,a2
	beq	a2,zero,.L17
	addiw	a5,a1,-2
	slli	a5,a5,48
	srli	a5,a5,48
	li	a4,34
	li	s1,0
	bgtu	a5,a4,.L24
	sd	s6,16(sp)
	li	a3,32
	li	a0,4
	.cfi_offset 22, -64
	j	.L10
.L11:
	addi	s0,s0,1
	addiw	s1,s1,1
.L10:
	lbu	a5,0(s0)
	beq	a5,a3,.L11
	addiw	a4,a5,-9
	andi	a4,a4,0xff
	bleu	a4,a0,.L11
	li	a4,45
	beq	a5,a4,.L25
	li	a4,43
	li	s6,1
	beq	a5,a4,.L26
.L13:
	lbu	a0,0(s0)
	beq	a0,zero,.L20
	sd	s2,48(sp)
	sd	s5,24(sp)
	sd	s7,8(sp)
	.cfi_offset 18, -32
	.cfi_offset 21, -56
	.cfi_offset 23, -72
	li	s5,0
	li	s2,0
	li	s7,-1
.L15:
	mv	a1,s3
	call	char_to_digit
	beq	a0,s7,.L14
	mulw	s2,s3,s2
	addw	s2,s2,a0
	addi	s0,s0,1
	addiw	s1,s1,1
	addiw	s5,s5,1
	lbu	a0,0(s0)
	bne	a0,zero,.L15
.L14:
	beq	s5,zero,.L21
	mulw	s6,s6,s2
	sw	s6,0(s4)
	ld	s0,64(sp)
	.cfi_restore 8
	ld	s2,48(sp)
	.cfi_restore 18
	ld	s3,40(sp)
	.cfi_restore 19
	ld	s4,32(sp)
	.cfi_restore 20
	ld	s5,24(sp)
	.cfi_restore 21
	ld	s6,16(sp)
	.cfi_restore 22
	ld	s7,8(sp)
	.cfi_restore 23
.L9:
	mv	a0,s1
	ld	ra,72(sp)
	.cfi_restore 1
	ld	s1,56(sp)
	.cfi_restore 9
	addi	sp,sp,80
	.cfi_def_cfa_offset 0
	jr	ra
.L25:
	.cfi_def_cfa_offset 80
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	.cfi_offset 9, -24
	.cfi_offset 19, -40
	.cfi_offset 20, -48
	.cfi_offset 22, -64
	addi	s0,s0,1
	addiw	s1,s1,1
	li	s6,-1
	j	.L13
.L26:
	addi	s0,s0,1
	addiw	s1,s1,1
	j	.L13
.L16:
	.cfi_restore 8
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 22
	li	s1,0
	j	.L9
.L17:
	.cfi_offset 8, -16
	.cfi_offset 19, -40
	.cfi_offset 20, -48
	li	s1,0
	ld	s0,64(sp)
	.cfi_restore 8
	ld	s3,40(sp)
	.cfi_restore 19
	ld	s4,32(sp)
	.cfi_restore 20
	j	.L9
.L20:
	.cfi_offset 8, -16
	.cfi_offset 19, -40
	.cfi_offset 20, -48
	.cfi_offset 22, -64
	li	s1,0
	ld	s0,64(sp)
	.cfi_restore 8
	ld	s3,40(sp)
	.cfi_restore 19
	ld	s4,32(sp)
	.cfi_restore 20
	ld	s6,16(sp)
	.cfi_restore 22
	j	.L9
.L21:
	.cfi_offset 8, -16
	.cfi_offset 18, -32
	.cfi_offset 19, -40
	.cfi_offset 20, -48
	.cfi_offset 21, -56
	.cfi_offset 22, -64
	.cfi_offset 23, -72
	mv	s1,s5
	ld	s0,64(sp)
	.cfi_restore 8
	ld	s2,48(sp)
	.cfi_restore 18
	ld	s3,40(sp)
	.cfi_restore 19
	ld	s4,32(sp)
	.cfi_restore 20
	ld	s5,24(sp)
	.cfi_restore 21
	ld	s6,16(sp)
	.cfi_restore 22
	ld	s7,8(sp)
	.cfi_restore 23
	j	.L9
.L24:
	.cfi_offset 8, -16
	.cfi_offset 19, -40
	.cfi_offset 20, -48
	ld	s0,64(sp)
	.cfi_restore 8
	ld	s3,40(sp)
	.cfi_restore 19
	ld	s4,32(sp)
	.cfi_restore 20
	j	.L9
	.cfi_endproc
.LFE24:
	.size	stoib, .-stoib
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
