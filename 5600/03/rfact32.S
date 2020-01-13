
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

    .global main

    .text
main:
    enter $16, $0
    // -4(%ebp) is x

    lea -4(%ebp), %eax
    push %eax
    push $scanfmt
    call scanf
    add $8, %esp

    mov -4(%ebp), %eax
    push %eax
    call fact
    add $4, %esp

    mov -4(%ebp), %ecx
    push %eax
    push %ecx
    push $printfmt
    call printf
    add $12, %esp

    leave
    ret
    /*
long
fact(long x)
{
    if (x <= 1) {
        return 1;
    }
    else {
        return x * fact(x - 1);
    }
}
    */
fact:
    enter $0, $0
    push %ebx // x is %ebp

    mov 8(%ebp), %ebx

    mov $1, %eax
    cmp $1, %ebx
    jle fact_done

    mov %ebx, %ecx
    dec %ecx
    push %ecx
    call fact
    add $4, %esp

    imul %ebx

fact_done:
    pop %ebx
    leave
    ret

    .data
scanfmt:    .string "%ld"
printfmt:   .string "fact(%ld) = %ld\n"
