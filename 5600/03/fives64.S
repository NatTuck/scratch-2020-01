    .global main

    .text
main:
    enter $0, $0
/*
    int
main(int argc, char* argv[])
{
	*/
    // argc is %rdi
    // argv is %rsi

    /*
    if (argc != 2) {
        puts("Usage: ./fives arg");
        return 1;
    }
	*/

    cmp $2, %rdi
    jne show_usage

    mov 8(%rsi), %rdi // pass argv[1] as first arg to all_match
    mov $'5, %rsi
    call all_match

    cmp $0, %rax
    je main_else
    // all_match returned true

    mov $all5s_msg, %rdi
    call puts
    mov $0, %rax

    jmp main_done
main_else:
    // all_match returned false
    mov $notall_msg, %rdi
    call puts
    mov $0, %rax

    jmp main_done
    /*

    if (all_match(argv[1], '5')) {
        puts("all fives");
    }
    else {
        puts("not all fives");
    }

    return 0;
}
    */
show_usage:
    mov $usage_msg, %rdi
    call puts
    mov $1, %rax

main_done:
    leave
    ret

all_match:
    enter $0, $0
    // %rdi is text
    // %rsi is cc
    // %rcx is ii
    // %rax is result
    // %rdx is tmp

    mov $1, %rax
    mov $0, %rcx
am_loop_cond:
    mov (%rdi, %rcx, 1), %dl     // calculates %rdi + (%rcx * 1) as address
    cmp $0, %dl
    je am_done

    cmp %sil, %dl
    je am_loop_again

    mov $0, %rax
    jmp am_done

am_loop_again:
    inc %rcx
    jmp am_loop_cond

am_done:
    leave
    ret

/*
int
all_match(char* text, char cc)
{
    for (long ii = 0; text[ii] != 0; ++ii) {
        if (text[ii] != cc) {
            return 0;
        }
    }
    return 1;
}
*/


    .data
usage_msg:  .string "Usage: ./fives arg"
all5s_msg:  .string "all fives"
notall_msg: .string "not all fives"
