/* Test-only SysV AMD64 call driver. Seed unused stack BEFORE entering the
   actual C owner, just as the original Unicorn fixture seeds its stack.
   No production instruction, local variable, or object layout is replaced. */
.text
.globl dxball_test_invoke_seeded
.type dxball_test_invoke_seeded,@function
dxball_test_invoke_seeded:
 pushq %rbp
 pushq %r12
 pushq %r13
 pushq %r14
 movq %rdi,%r12
 movq %rsi,%r13
 movq %rdx,%r14
 movl %ecx,%eax
 subq $65544,%rsp
 movq %rsp,%rdi
 movl $65536,%ecx
 cld
 rep stosb
 addq $65536,%rsp
 movq %r13,%rdi
 movq %r14,%rsi
 call *%r12
 addq $8,%rsp
 popq %r14
 popq %r13
 popq %r12
 popq %rbp
 ret
.size dxball_test_invoke_seeded,.-dxball_test_invoke_seeded
.section .note.GNU-stack,"",@progbits
