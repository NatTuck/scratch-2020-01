    .global main

    .data
fmt: .string "%ld\n"

    .text
add1:
    enter $0, $0

    mov %rdi, %rax
    add $1, %rax   # %rax = %rax + 1

    leave
    ret

main:
    enter $0, $0

    mov $1, %rdi
    call add1

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %ax
    call printf

    leave
    ret
