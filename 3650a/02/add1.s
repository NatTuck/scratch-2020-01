    .global main

    .data
fmt: .string "%ld\n"

    .text
add1:
    /* long
       add1(long x)
	   {
	       long y = x
	       y += 1
	       return y
	   }
    */
    enter $0, $0
    // First 6 arguments go in:
    //  %rdi, %rsi, %rdx, %rcx, %r8, %r9

    mov %rdi, %rax
    add $1, %rax   # %rax = %rax + 1

    // Functions return the value in %rax
    // when they return
    leave
    ret

main:
    // int main(int argc, char* argv[])
    enter $0, $0

    mov $1, %rdi
    call add1

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %ax
    call printf

    leave
    ret
