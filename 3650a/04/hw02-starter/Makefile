
all:
	make ccalc || true
	make acalc || true
	make cfib || true
	make afib || true

ccalc: calc.c
	gcc -g -o ccalc calc.c

acalc: calc.S
	gcc -g -no-pie -o acalc calc.S

cfib: fib.c
	gcc -g -o cfib fib.c

afib: fib.S
	gcc -g -no-pie -o afib fib.S

clean:
	rm -f afib cfib acalc ccalc


