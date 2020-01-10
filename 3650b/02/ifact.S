    .global main
    .data
scanfmt:   .string "%ld"
printfmt:  .string "fact(%ld) = %ld\n"

    .text
main:
    enter $16, $0
    // Space for two words:
    //   0(%rsp)
    //   8(%rsp) - we'll put x here
    /*
    long x;
    scanf("%ld", &x);
	*/

    mov $scanfmt, %rdi
    lea 8(%rsp), %rsi
    mov $0, %al
    call scanf


    //long y = 1;
    mov $1, %rax    // y is %rax

    mov 8(%rsp), %rcx  // ii is %rcx
loop_cond:
    cmp $0, %rcx
    jle loop_done

    //for (int ii = x; ii > 0; ii--) {
        //y = y * ii;
    imul %rcx

    //}
    dec %rcx
    jmp loop_cond
loop_done:

    /*
    printf("fact(%ld) = %ld\n", x, y);
    */
    mov $printfmt, %rdi
    mov 8(%rsp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    leave
    ret
