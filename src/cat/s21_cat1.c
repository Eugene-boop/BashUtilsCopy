#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int parser(int argc, char *argv[], flags *myflags) {
    char *short_options = "vbenstTE";
    struct option long_options[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"show-ends", no_argument, NULL, 'E'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {"show-tabs", no_argument, NULL, 'T'},
        {"show-nonprinting", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}};
    int rez;
    int option_index = 0;
    while ((rez = getopt_long(argc, argv, short_options, long_options,
                              &option_index)) != -1) {
        switch (rez) {
            case 'v': {
                myflags->v = 1;
                break;
            };
            case 'b': {
                myflags->b = 1;
                break;
            };
            case 'e': {
                myflags->v = 1;
                myflags->e = 1;
                break;
            };
            case 'n': {
                myflags->n = 1;
                break;
            };
            case 's': {
                myflags->s = 1;
                break;
            };
            case 't': {
                myflags->v = 1;
                myflags->t = 1;
                break;
            };
            case 'T': {
                myflags->T = 1;
                break;
            };
            case 'E': {
                myflags->E = 1;
                break;
            };
            case '?':
            default: {
                myflags->error = 1;
                break;
            }
        }
    }
    return optind;
}
void process_v(unsigned char ch) {
    if (ch > 127 && ch < 160) {
        printf("M-^%d", ch - 64);
    } else if (ch >= 0 && ch < 32) {
        printf("^%c", ch + 64);
    } else if (ch == 127) {
        printf("^?");
    } else {
        printf("%c", ch);
    }
}
void processFiles(int parsed, flags catflags, int argc, char *argv[]) {
    for (int i = parsed; i < argc; i++) {
        char *filename = argv[i];
        FILE *file = fopen(filename, "r");
        if (file) {
            size_t line = 1;
            char is_break = 1;
            char emptyline = 0;
            unsigned char ch;
            size_t count_emptyline = 0;
            ch = fgetc(file);
            for (; !feof(file); ch = fgetc(file)) {
                if (catflags.s) {
                    if (ch != '\n') count_emptyline = 0;
                    if (ch == '\n') count_emptyline++;
                    if (count_emptyline > 2) continue;
                }
                if (catflags.b) {
                    if (is_break && ch == '\n') emptyline = 1;
                    if (is_break) {
                        if (!emptyline) {
                            printf("%6lu\t", line);
                            line++;
                        }
                        is_break = 0;
                    }
                    is_break = (ch == '\n');
                    emptyline = 0;
                } else if (catflags.n) {
                    if (is_break) {
                        printf("%6lu\t", line);
                        line++;
                        is_break = 0;
                    }
                    is_break = (ch == '\n');
                }
                if (catflags.e && ch == '\n') {
                    printf("$");
                }
                if (catflags.t && ch == '\t') {
                    printf("^I");
                    continue;
                }
                if (catflags.v && ch != '\t' && ch != '\n') {
                    process_v(ch);
                    continue;
                }
                printf("%c", ch);
            }
        } else {
            printf("Error cannot find %s file\n", filename);
        }
    }
}

int main(int argc, char *argv[], double (*func)(double, double)) {
    flags catflags = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int parsed = parser(argc, argv, &catflags);
    if (!catflags.error) {
        processFiles(parsed, catflags, argc, argv);
    } else {
        printf("error");
    }
    return 0;
}
