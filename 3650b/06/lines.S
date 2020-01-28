    .global main
    .data
file_name:   .string "msg.txt"
out_fmt:     .string "msg.txt has # of lines: %ld\n"
    .text

main:
    push %rbx
    push %r12
    push %r13
    push %r14
    push %r15
    //enter $264, $0
    //lea 0(%rsp), %r12
    //lea 192(%rsp), %r13
    enter $8, $0
    //char in_buf[192];    %r12
    sub $192, %rsp
    mov %rsp, %r12
    //char out_buf[64];    %r13
    sub $64, %rsp
    mov %rsp, %r13

    //long fd = open("msg.txt", O_RDONLY);  // %r14
    mov $2, %rax   // open
    mov $file_name, %rdi
    mov $0, %rsi
    syscall
    mov %rax, %r14

    //long count = read(fd, in_buf, 192); // %r15
    mov $0, %rax   // read
    mov %r14, %rdi
    mov %r12, %rsi
    mov $192, %rdx
    syscall
    mov %rax, %r15

    //long lines = 0;  // %rbx
    /*
    for(long ii = 0; ii < count; ++ii) { // ii is %rcx
        if (in_buf[ii] == '\n') {
            lines += 1;
        }
    }
    */
    mov $0, %rbx
    mov $0, %rcx
main_loop_cond:
    cmp %r15, %rcx
    jge main_loop_done

    mov (%r12, %rcx, 1), %dl
    cmp $'\n', %dl
    jne main_loop_inc

    inc %rbx

main_loop_inc:
    inc %rcx
    jmp main_loop_cond
main_loop_done:

    //count = sprintf(out_buf, "msg.txt has # of lines: %ld\n", lines);

    mov %r13, %rdi
    mov $out_fmt, %rsi
    mov %rbx, %rdx
    mov $0, %al
    call sprintf
    mov %rax, %r15

    //write(1, out_buf, count);
    mov $1, %rax   // syscall write
    mov $1, %rdi   // fd = stdout
    mov %r13, %rsi
    mov %r15, %rdx
    syscall

    //close(fd);
    mov $3, %rax
    mov %r14, %rdi
    syscall
    //return 0;

    mov $0, %rax
    leave
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    ret
