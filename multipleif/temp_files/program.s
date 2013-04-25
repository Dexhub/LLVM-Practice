	.file	"program.prof"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	subq	$24, %rsp
.Ltmp1:
	.cfi_def_cfa_offset 32
	xorl	%edi, %edi
	xorl	%esi, %esi
	movl	$EdgeProfCounters, %edx
	movl	$15, %ecx
	callq	llvm_start_edge_profiling
	incl	EdgeProfCounters(%rip)
	movl	$0, 20(%rsp)
	movl	$0, 16(%rsp)
	movl	$0, 12(%rsp)
	movl	$0, 8(%rsp)
	incl	EdgeProfCounters+4(%rip)
	jmp	.LBB0_1
	.align	16, 0x90
.LBB0_11:                               # %do.cond.do.body_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+52(%rip)
.LBB0_1:                                # %do.body
                                        # =>This Inner Loop Header: Depth=1
	movl	16(%rsp), %eax
	incl	%eax
	movslq	%eax, %rax
	imulq	$1717986919, %rax, %rcx # imm = 0x66666667
	movl	%eax, 16(%rsp)
	movq	%rcx, %rdx
	shrq	$63, %rdx
	sarq	$34, %rcx
	addl	%edx, %ecx
	imull	$10, %ecx, %ecx
	cmpl	%ecx, %eax
	je	.LBB0_3
# BB#2:                                 # %if.then
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+8(%rip)
	movl	16(%rsp), %esi
	movl	$.L.str, %edi
	xorb	%al, %al
	callq	printf
	incl	EdgeProfCounters+16(%rip)
	jmp	.LBB0_10
	.align	16, 0x90
.LBB0_3:                                # %if.else
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+12(%rip)
	movl	$.L.str1, %edi
	xorb	%al, %al
	callq	printf
	incl	EdgeProfCounters+20(%rip)
	movl	$.L.str2, %edi
	xorb	%al, %al
	callq	printf
	movl	16(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	andl	$-2, %ecx
	cmpl	%ecx, %eax
	jne	.LBB0_5
# BB#4:                                 # %if.end.if.then7_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+24(%rip)
	jmp	.LBB0_7
	.align	16, 0x90
.LBB0_5:                                # %lor.lhs.false
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+28(%rip)
	movslq	16(%rsp), %rax
	imulq	$1431655766, %rax, %rcx # imm = 0x55555556
	movq	%rcx, %rdx
	shrq	$63, %rdx
	shrq	$32, %rcx
	addl	%edx, %ecx
	leal	(%rcx,%rcx,2), %ecx
	cmpl	%ecx, %eax
	jne	.LBB0_8
# BB#6:                                 # %lor.lhs.false.if.then7_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+32(%rip)
.LBB0_7:                                # %if.then7
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	12(%rsp)
	incl	EdgeProfCounters+40(%rip)
	jmp	.LBB0_9
.LBB0_8:                                # %if.else9
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+36(%rip)
	incl	8(%rsp)
	incl	EdgeProfCounters+44(%rip)
.LBB0_9:                                # %if.end11
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	12(%rsp), %esi
	movl	$.L.str3, %edi
	xorb	%al, %al
	callq	printf
	movl	8(%rsp), %esi
	movl	$.L.str4, %edi
	xorb	%al, %al
	callq	printf
	incl	EdgeProfCounters+48(%rip)
.LBB0_10:                               # %do.cond
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpl	$99, 16(%rsp)
	jle	.LBB0_11
# BB#12:                                # %do.end
	incl	EdgeProfCounters+56(%rip)
	xorl	%eax, %eax
	addq	$24, %rsp
	ret
.Ltmp2:
	.size	main, .Ltmp2-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "%d"
	.size	.L.str, 3

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "\n"
	.size	.L.str1, 2

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "Next IF statement"
	.size	.L.str2, 18

	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	 "J : %d"
	.size	.L.str3, 7

	.type	.L.str4,@object         # @.str4
.L.str4:
	.asciz	 "K : %d"
	.size	.L.str4, 7

	.type	EdgeProfCounters,@object # @EdgeProfCounters
	.local	EdgeProfCounters
	.comm	EdgeProfCounters,60,16

	.section	".note.GNU-stack","",@progbits
