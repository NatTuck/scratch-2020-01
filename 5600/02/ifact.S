    .global main
    .text
main:
    enter $16, $0
    // 0(%rsp) is unused
    // 8(%rsp) is x

    /*
       long x
       scanf("%ld", &x)
	*/

    mov $scanfmt, %rdi
    lea 8(%rsp), %rsi
    mov $0, %al
    call scanf

    /*
	long y = 1
    for (int ii = x, ii > 0, ii--) {
       y *= ii
	}
	*/

    // y is rax
    // ii is rcx
    mov 8(%rsp), %rcx
loop:
    cmp $0, %rcx   // %rcx > 0 ?
    jle loop_done

    imul %rcx

    dec %rcx
    jmp loop
loop_done:

    mov $printfmt, %rdi
    mov 8(%rsp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    leave
    ret

    /*
_start:
    call main (push "line 14" address, jump to main)
    ret
    */

    .data
scanfmt:   .string "%ld"
printfmt:  .string "fact(%ld) = %ld\n"
