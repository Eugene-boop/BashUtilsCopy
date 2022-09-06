fl = -Wall -Werror -Wextra -fsanitize=address -g -std=c11
all: s21_grep
s21_cat:
	gcc $(fl) ../s21_cat/s21_cat.c -o s21_cat
s21_grep:
	gcc $(fl) s21_grep.c -o s21_grep
test: s21_grep
	sh grep_check.sh
lint: 
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *h
	rm -f CPPLINT.cfg
cppcheck:
	cppcheck missingInclude=system --enable=all *.c
clean:
	rm -f s21_cat
	rm -f s21_grep
