    .global main
    .text

//int all_match(char* text, char cc)
    /*
	// text is %rdi, cc is %sil, ii is %rcx
    for (int ii = 0; text[ii]; ++ii) {
        if (text[ii] != cc) {
            return 0;
        }
    }
    return 1;
    */
all_match:
    enter $0, $0

    mov $0, %rcx
am_loop:
    cmpb $0, (%rdi, %rcx, 1)
    je am_return_true

    mov (%rdi, %rcx, 1), %r11b
    cmpb %sil, %r11b
    jne am_return_false

    inc %rcx
    jmp am_loop

am_return_false:
    mov $0, %rax
    jmp am_done

am_return_true:
    mov $1, %rax

am_done:
    leave
    ret

//int main(int argc, char* argv[])
    /*
    if (all_match(argv[1], '5')) {
        puts("all five");
    }
    else {
        puts("not all five");
    }
    return 0;
    */

main:
    enter $0, $0

    mov 8(%rsi), %rdi
    mov $'5, %rsi
    call all_match

    cmp $0, %rax
    jne main_else

    mov $itsall, %rdi
    call puts

    jmp main_done

main_else:

    mov $notall, %rdi
    call puts

main_done:
    mov $0, %rax
    leave
    ret

    .data
notall: .string "not all five"
itsall: .string "all five"
