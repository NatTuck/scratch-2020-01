    .global main

    .text
main:
    push %r14   // fd
    push %r15   // # of bytes read
    enter $256, $0
    // 0(%rsp) is read_buf (192 bytes)
    // 192(%rsp) is print_buf (64 bytes)

    /*
    char* intro = "Lines in msg.txt:\n";
    write(1, intro, strlen(intro));

    int fd = open("msg.txt", O_RDONLY);
    long size = read(fd, read_buf, 192);
	*/

    mov $intro, %rdi
    call strlen

    mov $1, %rdi     // file descriptor 1 = stdout
    mov $intro, %rsi // buf
    mov %rax, %rdx   // len
    mov $1, %rax     // syscall 1 = write
    syscall

    mov $name, %rdi
    mov $0, %rsi     // O_RDONLY; see bits/fcntl-linux.h
    mov $0, %rdx     // third arg, unused
    mov $2, %rax     // syscall 2 = open
    syscall
    mov %rax, %r14   // new fd

    mov %r14, %rdi     // fd
    lea 0(%rsp), %rsi  // buffer is read_buf
    mov $192, %rdx     // buffer size
    mov $0, %rax       // syscall 0 = read
    syscall
    mov %rax, %r15     // # of bytes read

    mov $0, %rcx   // ii
    mov $0, %rdx   // lines

loop_cond:
    cmp %r15, %rcx
    jge loop_done

    mov (%rsp, %rcx, 1), %al
    mov $0, %r11
    cmp $'\n', %al
    sete %r11b
    add %r11, %rdx

    inc %rcx
    jmp loop_cond
loop_done:
    /*
    long lines = 0;
    for (long ii = 0; ii < size; ++ii) {
        if (read_buf[ii] == '\n') {
            lines += 1;
        }
    }
	*/

    lea 192(%rsp), %rdi
    mov $outfmt, %rsi
    //mov %rdx, %rdx
    mov $0, %al
    call sprintf

    mov $3, %rax
    mov %r15, %rdi
    syscall

    lea 192(%rsp), %rdi
    call strlen

    mov $1, %rdi
    lea 192(%rsp), %rsi
    mov %rax, %rdx
    mov $1, %rax
    syscall

    /*
    close(fd);

    sprintf(print_buf, "lines = %ld\n", lines);
    write(1, print_buf, strlen(print_buf));

    return 0;
    */

    leave
    pop %r15
    pop %r14
    ret

    .data
name:   .string "msg.txt"
intro:  .string "Lines in msg.txt\n"
outfmt: .string "lines = %ld\n"
