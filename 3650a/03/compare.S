    .global main

    .text
main:
    // args come in in registers:
    //    %rdi, %rsi, %rdx, %rcx, %r8, %r9
    // initially:
    //    argc is %rdi
    //    argv is %rsi
    push %rbx
    push %r12
    enter $0, $0
    // argv is %rbx
    mov %rsi, %rbx
    // aa is %r12
    // bb is %rdx

	/*
    if (argc != 3) {
        puts("Usage: ./compare NN NN");
        return 1;
    }
	*/

    cmp $3, %rdi
    je main_good_args

    mov $usage_msg, %rdi
    call puts

    mov $1, %rax
    jmp main_done

main_good_args:
    //long aa = atol(argv[1]);  <- index is 1, so offset is 1*8
    mov 8(%rbx), %rdi
    call atol
    mov %rax, %r12

    //long bb = atol(argv[2]); <- index is 2, so offset is 2*8
    mov 16(%rbx), %rdi
    call atol
    mov %rax, %rdx

	/*
    if (aa > bb) {
        printf("%ld > %ld\n", aa, bb);
    }
    else {
        printf("%ld <= %ld\n", aa, bb);
    }
	*/
    cmp %rdx, %r12
    jg got_gt
    jmp got_le

got_gt:
    mov $gt_msg, %rdi
    mov %r12, %rsi
    mov %rdx, %rdx
    mov $0, %al
    call printf
    mov $0, %rax
    jmp main_done

got_le:
    mov $le_msg, %rdi
    mov %r12, %rsi
    mov %rdx, %rdx
    mov $0, %al
    call printf
    mov $0, %rax
    jmp main_done

main_done:
    leave
    pop %r12
    pop %rbx
    ret

    .data
usage_msg:  .string "Usage: ./compare NN NN"
gt_msg: .string "%ld > %ld\n"
le_msg: .string "%ld <= %ld\n"
