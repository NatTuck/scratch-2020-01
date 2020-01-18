    .global main
    .text

//long iterate(long x)

    /*
    if (x % 2 == 0) {
        return x / 2;
    }
    else {
        return 3 * x + 1;
    }

	Variable mapping:
	  - x is %rdi
	  - temporaries are in %r10
    */
iterate:
    enter $0, $0

    mov %rdi, %rax
    mov $2, %r11
    cqo
    idiv %r11   // does %rdx:%rax / ARG ; quot in %rax, rem in %rdx
    mov %rdx, %r10

    cmp $0, %r10
    je its_even

its_odd:
    //return 3 * x + 1;
    mov $3, %r10
    imul %rdi, %r10
    mov %r10, %rax
    inc %rax
    jmp iterate_done

its_even:
    //return x / 2;
    // the thing is already where we want it

iterate_done:
    leave
    ret

// int main(int argc, char* argv[])


    /*
    argv // %rsi

    long x = atol(argv[1]);  // x is %r15

    long i = 0; // i is %r14
    while (x > 1) {
        printf("%ld\n", x);
        x = iterate(x);
        i++;
    }

    printf("i = %ld\n", i);
    return 0;
    */

main:
    push %r15
    push %r14
    enter $0, $0

    // long x = atol(argv[1]);  // x is %r15
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %r15

    /*
    long i = 0; // i is %r14
    while (x > 1) {
        printf("%ld\n", x);
        x = iterate(x);
        i++;
    }
	*/
    mov $0, %r14
start_the_while_loop:
    cmp $1, %r15
    jle out_of_the_loop

    mov $print_ld, %rdi
    mov %r15, %rsi
    mov $0, %al
    call printf

    mov %r15, %rdi
    call iterate
    mov %rax, %r15

    inc %r14
    jmp start_the_while_loop
out_of_the_loop:

    //printf("i = %ld\n", i);
    //return 0;
    mov $print_i_ld, %rdi
    mov %r14, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    pop %r14
    pop %r15
    ret

    .data
print_ld:   .string "%ld\n"
print_i_ld:   .string "i = %ld\n"
