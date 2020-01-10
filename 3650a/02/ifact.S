/*
    #include <stdio.h>

int
main(int argc, char* argv[])
{
    long x;
    scanf("%ld", &x);

    long y = 1;
    for (int ii = x; ii > 0; ii--) {
        y = y * ii;
    }

    printf("fact(%ld) = %ld\n", x, y);
    return 0;
}
    */

    .global main

    .data
scanfmt:     .string "%ld"
printfmt:    .string "fact(%ld) = %ld\n"

    .text
main:
    enter $16, $0
    // we now have 16 bytes available at 0(%rsp)
    // 0(%rsp)
    // 8(%rsp)

    // 8(%rsp) is x

    mov $scanfmt, %rdi
    lea 8(%rsp), %rsi   // arg2 is &x
    mov $0, %al
    call scanf

    //long y = 1;
    mov $1, %rax    // %rax is y

    // for (int ii = x; ii > 0; ii--) {
    mov 8(%rsp), %rcx  // %rcx is ii

for_loop_cond:
    cmp $0, %rcx
    jle for_loop_done

    //    y = y * ii;
    imul %rcx

    dec %rcx
    jmp for_loop_cond
for_loop_done:

    mov $printfmt, %rdi
    mov 8(%rsp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret
