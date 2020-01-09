    .global main
    .text

main:
    enter $0, $0

    mov $40, %rax
    mov $30, %rbx
    mov $20, %rcx
    mov $10, %rdx

    mov %rdx, %rdi

    cqo
    idiv %rdi     // %rdx:%rax = 10*2^64 + 40 * 2^0

    mov $longfmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret


    .data
longfmt:    .string "%ld\n"
