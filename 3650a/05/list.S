    .global cons
    .global car
    .global cdr
    .global free_list
    .text

    /*
    * A LinedList is one of:
	*  - 0 (a null pointer), for an empty list
    *  - The (non-zero) address of a Cell.
	*
	* A Cell is a struct with two fields:
	*  - head: A long
	*  - tail: A LinkedList
    */

// LinkedList operation:
//  - cons       - allocate a cell
//  - car        - get first item in list
//  - cdr        - get the rest of the list
//  - free_list  - recursively free list

cons:
    push %r12
    push %r13
    enter $0, $0
    mov %rdi, %r12
    mov %rsi, %r13

    mov $16, %rdi
    call malloc

    mov %r12, 0(%rax)
    mov %r13, 8(%rax)

    leave
    pop %r13
    pop %r12
    ret

car:
    mov 0(%rdi), %rax
    ret

cdr:
    mov 8(%rdi), %rax
    ret

free_list:
    push %r12 // xs
    enter $8, $0
    cmp $0, %rdi
    je free_list_done

    mov %rdi, %r12

    // free_list(xs->rest)
    // free(xs)

    call cdr
    mov %rax, %rdi
    call free_list

    mov %r12, %rdi
    call free

free_list_done:
    leave
    pop %r12
    ret
