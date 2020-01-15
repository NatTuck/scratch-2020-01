    .global main
    .text

main:
    enter $0, $0
    push %ebx

    mov $4, %eax    // syscall #4 is write
    mov $1, %ebx    // 1 is stdout
    mov $msg, %ecx
    mov $6, %edx    // strlen(msg) == 0
    int $0x80

    pop %ebx
    leave
    ret

    .data
msg:    .string "Hello\n"
