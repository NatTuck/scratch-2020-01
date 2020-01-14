    .global main

    .text
main:
    push %r14 // %r14 is aa
    push %r15 // %r15 is argv
    enter $0, $0
    // argc is %rdi
    // argv is %rsi -> %r15
    // aa is %r14
    // bb is %rdx
    mov %rsi, %r15

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
    mov $1, %rax    // return 1;
    jmp main_done

main_good_args:
    //long aa = atol(argv[1]);   argv[1], so offset is 1*8 = 8
    mov 8(%r15), %rdi
    call atol
    mov %rax, %r14

    //long bb = atol(argv[2]);   argv[2], so offset is 2*8 = 16
    mov 16(%r15), %rdi
    call atol
    mov %rax, %rdx

    cmp %rdx, %r14
    jg its_gt
    jmp its_le

    //if (aa > bb) {
its_gt:
        //printf("%ld > %ld\n", aa, bb);
    mov $gt_msg, %rdi
    mov %r14, %rsi
    //mov %rdx, %rdx
    mov $0, %al
    call printf
    jmp main_done_ok

	//else {
its_le:
        //printf("%ld <= %ld\n", aa, bb);
    mov $le_msg, %rdi
    mov %r14, %rsi
    //mov %rdx, %rdx
    mov $0, %al
    call printf
    jmp main_done_ok

    //return 0;
main_done_ok:
    mov $0, %rax
main_done:
    leave
    pop %r15
    pop %r14
    ret

    .data
usage_msg:  .string "Usage: ./compare NN NN"
gt_msg: .string "%ld > %ld\n"
le_msg: .string "%ld <= %ld\n"
