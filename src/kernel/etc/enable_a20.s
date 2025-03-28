# Section for data
.section .data
BufferBelowMB:  .byte 0
BufferOverMB:   .byte 0

# Section for code
.section .text
.global get_a20_state
.global query_a20_support
.global enable_a20_keyboard_controller
.global enable_a20

get_a20_state:
    pushf
    pushl %esi
    pushl %edi
    pushl %ds
    pushl %es
    cli

    movw $0x0000, %ax
    movw %ax, %ds
    movw $0x0500, %si

    notw %ax
    movw %ax, %es
    movw $0x0510, %di

    movb (%si), %al
    movb %al, BufferBelowMB
    movb (%di), %al
    movb %al, BufferOverMB

    movb $1, %ah
    movb $0, (%si)
    movb $1, (%di)
    movb (%si), %al
    cmpb (%di), %al
    jne 1f
    decb %ah
1:
    movb BufferBelowMB, %al
    movb %al, (%si)
    movb BufferOverMB, %al
    movb %al, (%di)
    shrw $8, %ax
    sti
    popl %es
    popl %ds
    popl %edi
    popl %esi
    popf
    ret

query_a20_support:
    pushl %ebx
    clc

    movw $0x2403, %ax
    int $0x15
    jc 1f

    testb %ah, %ah
    jnz 1f

    movw %bx, %ax
    popl %ebx
    ret
1:
    stc
    popl %ebx
    ret

enable_a20_keyboard_controller:
    cli
    call wait_io1
    movb $0xad, %al
    outb %al, $0x64
    
    call wait_io1
    movb $0xd0, %al
    outb %al, $0x64
    
    call wait_io2
    inb $0x60, %al
    pushl %eax
    
    call wait_io1
    movb $0xd1, %al
    outb %al, $0x64
    
    call wait_io1
    popl %eax
    orb $2, %al
    outb %al, $0x60
    
    call wait_io1
    movb $0xae, %al
    outb %al, $0x64
    
    call wait_io1
    sti
    ret

wait_io1:
    inb $0x64, %al
    testb $2, %al
    jnz wait_io1
    ret

wait_io2:
    inb $0x64, %al
    testb $1, %al
    jz wait_io2
    ret

enable_a20:
    clc
    pusha
    movb $0, %bh

    call get_a20_state
    jc 1f

    testw %ax, %ax
    jnz 2f

    call query_a20_support
    movb %al, %bl
    testb $1, %bl
    jnz 3f

    testb $2, %bl
    jnz 1f

    movw $0x2401, %ax
    int $0x15
    jc 1f
    testb %ah, %ah
    jnz 4f
    call get_a20_state
    testw %ax, %ax
    jnz 2f

1:  # .fast_gate
    inb $0x92, %al
    testb $2, %al
    jnz 2f

    orb $2, %al
    andb $0xfe, %al
    outb %al, $0x92

    call get_a20_state
    testw %ax, %ax
    jnz 2f

    testb %bh, %bh
    jnz 4f

3:  # .keyboard_controller
    call enable_a20_keyboard_controller
    call get_a20_state
    testw %ax, %ax
    jnz 2f

    movb $1, %bh
    testb $2, %bl
    jnz 1b
    jmp 4f

4:  # .failed
    stc
2:  # .done
    popa
    ret