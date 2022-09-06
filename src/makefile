fl = -std=c11 -g
fl =  
    
all: s21_cat s21_grep
s21_cat:
	gcc $(fl) cat/s21_cat.c -o cat/s21_cat
s21_grep:
	gcc $(fl) grep/s21_grep.c -o grep/s21_grep
test:
gcov_report:
clean:
	rm -f cat/s21_cat
	rm -f grep/s21_grep
