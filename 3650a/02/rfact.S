/*
    #include <stdio.h>

long
fact(long x)
{
	if (x <= 1) {
        return 1
	}
    return x * fact(x-1)
}

int
main(int argc, char* argv[])
{
    long x;
    scanf("%ld", &x);

    long y = fact(x)

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

    //long y = fact(x);
    mov 8(%rsp), %rdi
    call fact

    mov $printfmt, %rdi
    mov 8(%rsp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

fact:
    enter $16, $0

    mov $1, %rax
    cmp $1, %rdi
    jle fact_done

    // return x * fact(x-1)
    mov %rdi, 0(%rsp)
    dec %rdi
    call fact

    mov 0(%rsp), %rdi
    imul %rdi

fact_done:
    leave
    ret
