# double.s
  .global main

  .text
# long double(long x)
#   - the argument comes in on the stack at 8(%ebp)
#   - there's some other stuff below it we'll talk about later
#   - we return the result by putting it in %eax
dub:
  enter $0, $0

  # long y = x;
  mov 8(%ebp), %eax

  # y = y + y;
  add %eax, %eax

  # return y;
  leave
  ret

main:
  enter $0, $0

  # long x = 5;
  mov $5, %edi

  # y = double(x)
  push %edi
  call dub
  # result in %eax

  # printf("%ld\n", y)
  # arguments are pushed to the stack in reverse order
  mov $long_fmt, %edi
  push %eax
  push %edi
  call printf

  leave
  ret

  .data
long_fmt: .string "%ld\n"
