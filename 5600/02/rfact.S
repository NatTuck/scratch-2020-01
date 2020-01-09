    .global main
    .text

fact:
    push %rbx
    enter $8, $0
    // x is %rbx

    /*
      if (x <= 1): return 1
      else: return x * fact(x-1)
	*/
    mov $1, %rax
    cmp $1, %rbx
    jle fact_done

    mov %rbx, %rdi
    dec %rdi
    call fact

    imul %rbx

fact_done:
    leave
    pop %rbx
    ret

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

    mov 8(%rsp), %rdi
    call fact

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
