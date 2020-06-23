	.file	"mutexVar.c"
	.text
	.data
	.align 4
	.type	count, @object
	.size	count, 4
count:
	.long	10
	.text
	.globl	thread1_routine
	.type	thread1_routine, @function
thread1_routine:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	count(%rip), %eax
	addl	$1, %eax
	movl	%eax, count(%rip)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$9999, -4(%rbp)
	jle	.L3
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	thread1_routine, .-thread1_routine
	.globl	thread2_routine
	.type	thread2_routine, @function
thread2_routine:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	movl	count(%rip), %eax
	subl	$1, %eax
	movl	%eax, count(%rip)
	addl	$1, -4(%rbp)
.L5:
	cmpl	$9999, -4(%rbp)
	jle	.L6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	thread2_routine, .-thread2_routine
	.globl	errorEXit
	.type	errorEXit, @function
errorEXit:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE8:
	.size	errorEXit, .-errorEXit
	.section	.rodata
	.align 8
.LC0:
	.string	" El hilo 1 no pudo ser creado "
	.align 8
.LC1:
	.string	" El hilo 2 no pudo ser creado "
.LC2:
	.string	"El valor de count es: %d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-24(%rbp), %rax
	movl	$0, %ecx
	leaq	thread1_routine(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	testl	%eax, %eax
	je	.L9
	leaq	.LC0(%rip), %rdi
	call	errorEXit
.L9:
	leaq	-16(%rbp), %rax
	movl	$0, %ecx
	leaq	thread2_routine(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	testl	%eax, %eax
	je	.L10
	leaq	.LC1(%rip), %rdi
	call	errorEXit
.L10:
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	movl	count(%rip), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.1.0"
	.section	.note.GNU-stack,"",@progbits
