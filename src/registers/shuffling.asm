.global transform_sample_asm
.intel_syntax noprefix

# void transform_sample_asm(uint8_t* sample, uint16_t rounds);
# sample points to 4x16 bytes = 64 bytes total

.section .text
transform_sample_asm:
    push rbp
    mov rbp, rsp
    push rbx

    mov rbx, rdi          # rdi = sample pointer
    mov cx, si            # rcx = rounds counter

loop_rounds:
    # Load all 4 rows
    movdqu xmm0, [rbx]          # Row 0
    movdqu xmm1, [rbx + 16]     # Row 1
    movdqu xmm2, [rbx + 32]     # Row 2
    movdqu xmm3, [rbx + 48]     # Row 3

    # --- Row arithmetic ---
    paddb xmm0, xmm1            # row0 += row1
    paddb xmm2, xmm3            # row2 += row3

    # --- Swap rows 1 and 2 ---
    movdqa xmm4, xmm1
    movdqa xmm1, xmm2
    movdqa xmm2, xmm4

    # --- Cyclic shifts ---
    # Row 0: left by 1 byte
    pshufb xmm0, [rip + rotl1_mask]
    # Row 1: right by 1 byte
    pshufb xmm1, [rip + rotr1_mask]
    # Row 2: left by 2 bytes
    pshufb xmm2, [rip + rotl2_mask]
    # Row 3: right by 2 bytes
    pshufb xmm3, [rip + rotr2_mask]

    # Store back
    movdqu [rbx], xmm0
    movdqu [rbx + 16], xmm1
    movdqu [rbx + 32], xmm2
    movdqu [rbx + 48], xmm3

    # Decrement counter and loop
    dec cx
    jnz loop_rounds

    pop rbx
    mov rsp, rbp
    pop rbp
    ret

.section .rodata
.align 16

rotl1_mask:
    .byte 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0

rotr1_mask:
    .byte 15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14

rotl2_mask:
    .byte 2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1

rotr2_mask:
    .byte 14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13

