    .global main

    .text
dub:
    enter $0, $0

    // first argument is in %rdi
    mov %rdi, %rax
    add %rax, %rax

    leave
    ret

main:
    enter $0, $0

    mov $5, %rdi

    call dub

    mov $long_fmt, %rdi  // first argument register
    mov %rax, %rsi       // second arg register
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

    .data
long_fmt:   .string "%ld\n"
