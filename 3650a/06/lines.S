    .global main
    .data
file_name:  .string "msg.txt"
out_fmt:    .string "Lines in msg.txt: %ld\n"

    .text
main:
    push %rbx
    push %r12
    push %r13
    enter $264, $0

	/*
    char in_buf[192];   // 0(%rsp)
    char out_buf[64];   // 192(%rsp)
    */

    //int fd = open("msg.txt", O_RDONLY);  // %rbx
    mov $2, %rax   // syscall: open
    mov $file_name, %rdi
    mov $0, %rsi
    syscall
    mov %rax, %rbx

    //long count = read(fd, in_buf, 192);  // %r12
    mov $0, %rax    // syscall: read
    mov %rbx, %rdi
    lea 0(%rsp), %rsi
    mov $192, %rdx
    syscall
    mov %rax, %r12

    /*
    long lines = 0;   // %r13
    for (long ii = 0; ii < count; ++ii) {  // %rcx
        if (in_buf[ii] == '\n') {
            lines += 1;
        }
    }
    */
    mov $0, %r13
    mov $0, %rcx
main_loop_cond:
    cmp %r12, %rcx
    jge main_loop_done

    mov (%rsp, %rcx, 1), %dl
    cmp $'\n', %dl
    jne not_a_newline

    inc %r13

not_a_newline:
    inc %rcx
    jmp main_loop_cond
main_loop_done:

    //count = sprintf(out_buf, "Lines in msg.txt: %ld\n", lines);
    lea 192(%rsp), %rdi
    mov $out_fmt, %rsi
    mov %r13, %rdx
    mov $0, %al
    call sprintf
    mov %rax, %r12

    //write(1, out_buf, count);
    mov $1, %rax
    mov $1, %rdi
    lea 192(%rsp), %rsi
    mov %r12, %rdx
    syscall

    //close(fd);
    mov $3, %rax
    mov %rbx, %rdi
    syscall

    //return 0;
    mov $0, %rax

    leave
    pop %r13
    pop %r12
    pop %rbx
    ret
