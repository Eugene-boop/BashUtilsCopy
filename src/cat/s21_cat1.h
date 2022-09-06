#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
typedef struct {
    char error;
    char b;
    char e;
    char n;
    char s;
    char t;
    char T;
    char E;
    char v;
} flags;
int parser(int argc, char *argv[], flags *myflags);
void process_v(unsigned char ch);
void processFiles(int parsed, flags catflags, int argc, char *argv[]);
#endif  // SRC_CAT_S21_CAT_H_
