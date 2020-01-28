    .global main
    .data
hello:  .string "Hello\n"
there:  .string "There\n"
    .text
main:
    enter $0, $0

    mov $1, %rax
    mov $1, %rdi
    mov $hello, %rsi
    mov $6, %rdx
    syscall

    leave
    ret
