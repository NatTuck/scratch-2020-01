    .global main
    .text

// long iterate(long x)
    /*
    if (x % 2 == 0) {
        return x / 2;
    }
    else {
        return x * 3 + 1;
    }

	Variable mapping:
      - x is %rdi
	  - temporaries in %r10
    */
iterate:
    enter $0, $0

    mov %rdi, %rax
    mov $2, %r10
    cqo
    idiv %r10 // does %rdx:%rax / %r10, quot = %rax, rem = %rdx

    cmp $0, %rdx
    je iterate_done
    // if jump, the division we want happens to be in %rax

    // return x * 3 + 1;

    mov $3, %r11
    mov %rdi, %r10
    imul %r11, %r10

    add $1, %r10
    mov %r10, %rax

iterate_done:
    leave
    ret



// int main(int argc, char* argv[])

    /*
    long x = atol(argv[1]);

    long i = 0;
    while (x > 1) {
        printf("%ld\n", x);
        x = iterate(x);
        i++;
    }

    printf("i = %ld\n", i);
    return 0;

    Variable mapping:
	  - argv is %rsi
	  - x is %r12
	  - i is %rbx
    */

main:
    push %rbx
    push %r12
    enter $0, $0

    // long x = atol(argv[1]);
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %r12  // x is %r12

    /*
    long i = 0; // i is %rbx
    while (x > 1) {
        printf("%ld\n", x);
        x = iterate(x);
        i++;
    }
    */
    mov $0, %rbx   // i is %rbx
loop_start:
    cmp $1, %r12
    jle loop_end

    mov $intfmt, %rdi
    mov %r12, %rsi
    mov $0, %al
    call printf

    mov %r12, %rdi
    call iterate
    mov %rax, %r12

    inc %rbx
    jmp loop_start

loop_end:
    //printf("i = %ld\n", i);

    mov $ifmt, %rdi
    mov %rbx, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    pop %r12
    pop %rbx
    ret

    .data
intfmt: .string "%ld\n"
ifmt:   .string "i = %ld\n"
