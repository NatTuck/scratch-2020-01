    .global main

    .text

	//long sum_array(long* xs, long nn) // %rdi, %rsi

    /*
    long yy = 0; // %rax
    for (long ii = 0; ii < nn; ++ii) { // %rcx
        yy += xs[ii];
    }
    return yy;
    */
sum_array:
    enter $0, $0

    mov $0, %rax

    mov $0, %rcx
sum_loop_cond:
    cmp %rsi, %rcx
    jge sum_loop_done

    add (%rdi, %rcx, 8), %rax

    inc %rcx
    jmp sum_loop_cond

sum_loop_done:
    leave
    ret

    //int main(int argc, char* argv[])  // %rdi, %rsi
main:
    push %rbx
    push %r12
    push %r13
    enter $8, $0

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
    //long nn = atol(argv[1]);   // nn is %rbx
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rbx

    // calculate byte size of xs
    mov $8, %r10
    imul %r10

    //long* xs = malloc(nn * sizeof(long));  // xs is %r12
    //   mov %rax, %rdi
    //call malloc
    //mov %rax, %r12

    //long xs[nn];
    //long* xs = alloca(nn * sizeof(long));
    sub %rax, %rsp
    mov %rsp, %r12

    // Force stack to be aligned by maybe
    // allocating another 8 bytes of space.
    mov $15, %r10
    not %r10
    and %r10, %rsp

    /*
    for (long ii = 0; ii < nn; ++ii) {  // ii is %r13
        int count = scanf("%ld", &(xs[ii])); // count is %rax
        if (count != 1) { abort(); }
    }
    */
    mov $0, %r13
main_read_loop_cond:
    cmp %rbx, %r13
    jge main_read_loop_done

    mov $scanfmt, %rdi
    lea (%r12, %r13, 8), %rsi
    mov $0, %al
    call scanf

    cmp $1, %rax
    jne explode

    inc %r13
    jmp main_read_loop_cond

explode:
    call abort

main_read_loop_done:
    //printf("sum of array = %ld\n", sum_array(xs, nn));

    mov %r12, %rdi
    mov %rbx, %rsi
    call sum_array

    mov $sumfmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    //free(xs);
    //mov %r12, %rdi
    //call free

    //return 0;
    mov $0, %rax

main_done:
    leave
    pop %r13
    pop %r12
    pop %rbx
    ret

    .data
usage_msg:   .string "usage: ./sum_array N"
scanfmt:     .string "%ld"
sumfmt:      .string "sum of array = %ld\n"
