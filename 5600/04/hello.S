    .global main
    .text
main:
    enter $0, $0

    mov $1, %rax     // write is syscall #1
    mov $1, %rdi     // fd 1 = stdout
    mov $msg, %rsi   // buffer
    mov $6, %rdx     // strlen(msg) == 6
    syscall
   
    leave
    ret

    .data
msg:    .string "Hello\n"
