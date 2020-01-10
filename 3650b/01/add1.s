    .global main

    .data
fmt: .string "%ld\n"

    .text
add1:
    enter $0, $0
    mov %rdi, %rax
    add $1, %rax
    leave
    ret

main:
    enter $0, $0

    mov $5, %rdi
    call add1

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret
