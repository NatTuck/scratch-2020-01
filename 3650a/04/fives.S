    .global main
    .text

// int all_match(char* text, char cc)
    /*
    for (int ii = 0; text[ii]; ++ii) {
        if (text[ii] != cc) {
            return 0;
        }
    }
    return 1;

    Variable mapping:
	  - text is %rdi
	  - cc is %sil
	  - ii is %rcx
    */
all_match:
    enter $0, $0
    mov $0, %rcx
all_match_loop_start:
    cmpb $0, (%rdi,%rcx,1)
    je all_match_success

    cmpb %sil, (%rdi,%rcx,1)
    jne all_match_fail

    inc %rcx
    jmp all_match_loop_start

all_match_success:
    mov $1, %rax
    jmp all_match_done

all_match_fail:
    mov $0, %rax

all_match_done:
    leave
    ret




// int main(int argc, char* argv[])
    /*
    if (all_match(argv[1], '5')) {
        puts("all five");
    }
    else {
        puts("not all five");
    }
    return 0;

	Variable mapping:
	 - argv is %rsi
    */

main:
    enter $0, $0

    mov 8(%rsi), %rdi
    mov $'5, %rsi             // "\n"     $'\n'
    call all_match

    cmp $1, %rax
    je all_fives

not_all_fives:
    mov $not_five_msg, %rdi
    call puts
    jmp main_done

all_fives:
    mov $all_five_msg, %rdi
    call puts

main_done:
    mov $0, %rax
    leave
    ret

    .data
all_five_msg:   .string "all five"
not_five_msg:   .string "not all five"
