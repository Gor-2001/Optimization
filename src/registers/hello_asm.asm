.global print_asm_message
.intel_syntax noprefix

.section .data
msg:    .ascii "Hello World !\n "
len = . - msg

.section .text
print_asm_message:
    push rbp
    mov rbp, rsp

    mov rax, 1      # sys_write
    mov rdi, 1      # stdout
    lea rsi, [rip + msg]
    mov rdx, len
    syscall         # 64-bit system call

    mov rsp, rbp
    pop rbp
    ret
