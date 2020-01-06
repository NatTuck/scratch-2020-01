    .global main

    .text
dub:
    enter $0, $0
    mov 8(%ebp), %eax

    # y = y + y
    add %eax, %eax

    # return y

    leave
    ret

main:
    enter $0, $0

    mov $5, %edi

    push %edi
    call dub

    mov $long_fmt, %edi
    push %eax
    push %edi
    call printf

    leave
    ret


    .data
long_fmt: .string "%ld\n"
