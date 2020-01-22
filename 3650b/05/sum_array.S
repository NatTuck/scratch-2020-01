    .global main
	// long sum_array(long* xs, long nn) // %rdi, %rsi

    /*
    long yy = 0; %rcx
    for (long ii = 0; ii < nn; ++ii) { // %rdx
        yy += xs[ii];
    }
    return yy;
    */
sum_array:
    enter $0, $0

    mov $0, %rcx

    mov $0, %rdx
sum_loop_cond:
    cmp %rsi, %rdx
    jge sum_loop_done

    add (%rdi, %rdx, 8), %rcx

    inc %rdx
    jmp sum_loop_cond

sum_loop_done:
    mov %rcx, %rax
    leave
    ret

    .data
usage_msg:   .string "usage: ./sum_array N"
scan_fmt:    .string "%ld"

    .text
    // int main(int argc, char* argv[]) // %rdi, %rsi
main:
    push %r12
    push %r13
    push %r14
    push %r15
    enter $0, $0
    /*
    if (argc != 2) {
        puts("usage: ./sum_array N");
        return 1;
    }
    */
    cmp $2, %rdi
    je main_good_args

    mov $usage_msg, %rdi
    call puts
    mov $1, %rax
    jmp main_done

main_good_args:
    //long nn = atol(argv[1]); // nn is %r12
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %r12

    //long* xs = malloc(nn * sizeof(long)); // xs is %r13
    //long xs[nn];
    //long* xs = alloca(nn * sizeof(long));

    mov $8, %r10
    imul %r10
    mov %rax, %rdi

    sub %rdi, %rsp
    mov %rsp, %r13

    mov $15, %r10
    not %r10
    and %r10, %rsp

    //call malloc
    //mov %rax, %r13

    /*
    for (long ii = 0; ii < nn; ++ii) {  // ii is %r14
        long count = scanf("%ld", &(xs[ii]));
        if (count != 1) { abort(); }
    }
    */

    mov $0, %r14
main_loop_cond:
    cmp %r12, %r14
    jge main_loop_done

    mov $scan_fmt, %rdi
    lea (%r13, %r14, 8), %rsi
    mov $0, %al
    call scanf

    cmp $1, %rax
    jne explode

    inc %r14
    jmp main_loop_cond
explode:
    call abort

main_loop_done:

    //printf("sum is: %ld\n", sum_array(xs, nn));
    mov %r13, %rdi
    mov %r12, %rsi
    call sum_array

    mov $sum_fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov %r13, %rdi
    //call free
    //free(xs);
    //return 0;
    mov $0, %rax

main_done:
    leave
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    ret

    .data
sum_fmt:  .string "sum is: %ld\n"
