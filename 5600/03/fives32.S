    .global main
    .text

main:
    enter $0, $0

    // argc is 8(%ebp)
    // argv is 12(%ebp)

    mov 12(%ebp), %ecx
    mov 4(%ecx), %edx    // argv[1]

    push %edx
    call puts
    add $4, %esp

    mov $0, %eax
    leave
    ret
