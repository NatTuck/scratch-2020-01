    .global main

    .data
fmt: .string "%ld\n"

    .text
    /* long
    /* add1(long x)
    /* {
	 *    //return x + 1
	 *    long y = x
	 *    y += 1
	 *    return y
	 * }
    */
add1:
    // First six arguments to a function go in regs:
    //   %rdi, %rsi, %rdx, %rcx, %r8, %r9
    // Return value goes in %rax
    enter $0, $0
    mov %rdi, %rax
    add $1, %rax
    leave
    ret

main:
    enter $0, $0

    mov $5, %rdi
    call add1

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret
