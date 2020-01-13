    .global main

    .text

    /*
    int
main(int _ac, char* _av[])
{
    long x;
    scanf("%ld", &x);

    long y = fact(x);
    printf("fact(%ld) = %ld\n", x, y);

    return 0;
}
    */
main:
    enter $16, $0
    // -8(%rbp) is x

    mov $scanfmt, %rdi
    lea -8(%rbp), %rsi
    mov $0, %al
    call scanf

    mov -8(%rbp), %rdi
    call fact

    mov $printfmt, %rdi
    mov -8(%rbp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    leave
    ret

fact:
    enter $0, $0
    push %rbx // x is %rbx
    mov %rdi, %rbx

    mov $1, %rax
    cmp $1, %rbx
    jle fact_done

    dec %rdi
    call fact

    imul %rbx

fact_done:
    pop %rbx
    leave
    ret

    .data
scanfmt:    .string "%ld"
printfmt:   .string "fact(%ld) = %ld\n"
