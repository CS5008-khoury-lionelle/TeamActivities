	.text
	.file	"shift.c"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movq	8(%rsi), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	callq	strtol@PLT
	movq	%rax, %rbx
	movl	%ebx, %ebp
	shll	$5, %ebp
	addl	%ebx, %ebp
	leaq	.L.str(%rip), %rdi
	movl	%ebx, %esi
	movl	%ebp, %edx
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	.L.str.1(%rip), %rdi
	movl	%ebx, %esi
	movl	%ebp, %edx
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	.L.str.2(%rip), %rdi
	movl	%ebx, %esi
	movl	%ebp, %edx
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d << 5 + x = %d\n"
	.size	.L.str, 18

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%d * 32 + x = %d\n"
	.size	.L.str.1, 18

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"%d * 33 = %d\n"
	.size	.L.str.2, 14

	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
