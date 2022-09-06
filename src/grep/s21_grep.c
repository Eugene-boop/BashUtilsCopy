#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    flags myflags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // printf("%d\n", myflags.fl_i);
    myflags = Get_Flags(argc, argv, myflags);
    // myflags.fl_i = 1;
    // printf("%d\n", myflags.fl_i);
    myflags.pattern = argv[optind];  // патерн объяеляем до
    // printf("%s\n", argv[optind]);  // optind  это pattern
    // printf("%s\n", argv[optind + 1]);  // optind + 1 это имя файла
    if (myflags.fl_e == 1) {
        Get_pattern_E(argc, argv);
    } else if (myflags.fl_i == 1) {
        Get_pattern_I(argc, argv, myflags);
    } else if (myflags.fl_v == 1) {
        Get_pattern_V(argc, argv, myflags);
    } else if (myflags.fl_c == 1) {
        Get_pattern_C(argc, argv, myflags);
    } else if (myflags.fl_l == 1) {
        Get_pattern_L(argc, argv, myflags);
    } else if (myflags.fl_n == 1) {
        Get_pattern_N(argc, argv, myflags);
    } else if (myflags.fl_h == 1) {
        Get_pattern_H(argc, argv, myflags);
    } else if (myflags.fl_s == 1) {
        Get_pattern_S(argc, argv);
    } else if (myflags.fl_f == 1) {
        Get_pattern_F(argc, argv);
    } else if (myflags.fl_o == 1) {
        Get_pattern_O(argc, argv);
    }
    // myflags.pattern = argv[optind]; // не правильное объявление патерна

    return 0;
}

flags Get_Flags(int argc, char *const argv[], flags myflags) {
    int rezult = 0;
    opterr = 0;
    while ((rezult = getopt(argc, argv, "eivclnhsfo")) != -1) {
        switch (rezult) {
            case 'e':
                myflags.fl_e = 1;
                break;
            case 'i':
                myflags.fl_i = 1;
                break;
            case 'v':
                myflags.fl_v = 1;
                break;
            case 'c':
                myflags.fl_c = 1;
                break;
            case 'l':
                myflags.fl_l = 1;
                break;
            case 'n':
                myflags.fl_n = 1;
                break;
            case 'h':
                myflags.fl_h = 1;
                break;
            case 's':
                myflags.fl_s = 1;
                break;
            case 'f':
                myflags.fl_f = 1;
                break;
            case 'o':
                myflags.fl_o = 1;
                break;
            case '?':
                printf("Error found !\n");
                break;
        }
    }
    return myflags;
}

void Get_pattern_E(int argc, char *argv[]) {
    // FILE *f;  // для файла
    char c[1000];  // мфссив для считывания строки из файла
    // int reti;  //
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;  // для файла
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, argv[optind], 0);
        if (f != NULL) {  // если ф существует
            while (fgets(c, 1000, f) != NULL) {  // пока не считали все строки
            // ищем регулярное выражение в с
                reti = regexec(&regex, c, 0, NULL,
                0);
                if (reti == 0) {  // если нашли, то 0
                    // проверка на количество файлов
                    if ((argc - 1) - (optind + 1) > 0) {
                        printf("%s:", argv[i]);
                    }
                    if (!feof(f)) {
                        printf("%s", c);
                    } else {
                        printf("%s\n", c);
                    }
                }
            }
            regfree(&regex);
            fclose(f);
        } else {
            printf("grep: %s: No such file or directory\n",
                   argv[i]);  // сделать обработку на не существующий файл
        }
        // fclose(f);
    }
}

void Get_pattern_I(int argc, char *argv[], flags myflags) {
    // FILE *f;
    char c[1000];
    opterr = 0;
    // int reti;
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        regex_t regex;
        reti = regcomp(&regex, myflags.pattern, REG_ICASE);
        f = fopen(argv[i], "r");
        if (f != NULL) {
            while (!feof(f)) {
                if (fgets(c, 1000, f) != NULL) {
                    reti = regexec(&regex, c, 0, NULL, 0);
                    if (reti == 0) {
                        if ((argc - 1) - (optind + 1) > 0) {
                            printf("%s:", argv[i]);
                        }
                        if (!feof(f)) {
                            printf("%s", c);
                        } else {
                            printf("%s\n", c);
                        }
                    }
                }
            }
            regfree(&regex);
            fclose(f);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
        // fclose(f);
    }
}

void Get_pattern_V(int argc, char *argv[], flags myflags) {
    // FILE *f;
    char c[1000];
    opterr = 0;
    // int reti;

    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, myflags.pattern, 0);
        if (f != NULL) {
            while (!feof(f)) {
                if (fgets(c, 1000, f) != NULL) {
                    reti = regexec(&regex, c, 0, NULL, 0);
                    if (reti != 0) {
                        if ((argc - 1) - (optind + 1) > 0) {
                            printf("%s:", argv[i]);
                        }
                        if (!feof(f)) {
                            printf("%s", c);
                        } else {
                            printf("%s\n", c);
                        }
                    }
                }
            }
            regfree(&regex);
            // fclose(f);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
        fclose(f);
    }
}

void Get_pattern_C(int argc, char *argv[], flags myflags) {
    // FILE *f;
    char c[1000];
    opterr = 0;
    // int reti;

    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        f = fopen(argv[i], "r");
        // int count = 0;
        regex_t regex;
        reti = regcomp(&regex, myflags.pattern, 0);
        if (f != NULL) {
            int count = 0;
            while (!feof(f)) {
                if (fgets(c, 1000, f) != NULL) {
                    reti = regexec(&regex, c, 0, NULL, 0);
                    if (reti == 0) {
                        count++;
                    }
                }
            }
            regfree(&regex);
            if ((argc - 1) - (optind + 1) > 0) {
                printf("%s:%d\n", argv[i], count);
            } else {
                printf("%d\n", count);
            }
            fclose(f);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
    }
}

void Get_pattern_L(int argc, char *argv[], flags myflags) {
    // FILE *f;
    char c[1000];
    opterr = 0;

    // int reti;
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, myflags.pattern, 0);
        if (f != NULL) {
            while (!feof(f)) {
                if (fgets(c, 1000, f) != NULL) {
                    reti = regexec(&regex, c, 0, NULL, 0);
                    if (reti == 0) {
                        if ((argc - 1) - (optind + 1) > 0) {
                            printf("%s\n", argv[i]);
                            break;
                        } else {
                            printf("%s\n", argv[i]);
                            break;
                        }
                    }
                }
            }
            regfree(&regex);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
        fclose(f);
    }
}

void Get_pattern_N(int argc, char *argv[], flags myflags) {
    // FILE *f;
    char c[1000];
    opterr = 0;
    int count = 0;
    // int reti;
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, myflags.pattern, 0);
        if (f != NULL) {
            while (!feof(f)) {
                if (fgets(c, 1000, f) != NULL) {
                    count++;
                    reti = regexec(&regex, c, 0, NULL, 0);
                    if (reti == 0) {
                        if ((argc - 1) - (optind + 1) > 0) {
                            printf("%s:", argv[i]);
                        }
                        if (!feof(f)) {
                            printf("%d:%s", count, c);
                        } else {
                            printf("%d:%s", count, c);
                        }
                    }
                }
            }
            regfree(&regex);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
        fclose(f);
    }
}

void Get_pattern_H(int argc, char *argv[], flags myflags) {
    // FILE *f;
    char c[1000];
    opterr = 0;
    // int reti;

    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, myflags.pattern, 0);
        if (f != NULL) {
            while (!feof(f)) {
                if (fgets(c, 1000, f) != NULL) {
                    reti = regexec(&regex, c, 0, NULL, 0);
                    if (reti == 0) {
                        if ((argc - 1) - (optind + 1) > 0) {
                            printf("%s:", argv[i]);
                        }
                        if (!feof(f)) {
                            printf("%s", c);
                        } else {
                            printf("%s\n", c);
                        }
                    }
                }
            }
            regfree(&regex);
            fclose(f);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
        // fclose(f);
    }
}

void Get_pattern_S(int argc, char *argv[]) {
    // FILE *f;  // для файла
    char c[1000];  // мфссив для считывания строки из файла
    opterr = 0;  // предотовращает ошибки
    // int reti;
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, argv[optind], 0);
        if (f != NULL) {
            while (fgets(c, 1000, f) != NULL) {
                reti = regexec(&regex, c, 0, NULL, 0);
                if (reti == 0) {
                    if ((argc - 1) - (optind + 1) > 0) {
                        printf("%s:", argv[i]);
                    }
                    if (!feof(f)) {
                        printf("%s", c);
                    } else {
                        printf("%s\n", c);
                    }
                }
            }
            regfree(&regex);
            fclose(f);
        } else {
            printf(
                "grep: %s: No such file or directory\n",
                argv[optind + 1]);  // сделать обработку на не существующий файл
        }
        // fclose(f);
    }
}

void Get_pattern_F(int argc, char *argv[]) {
    // FILE *f;
    // FILE *f_pattern;
    char c[1000];
    char c_pattern[1000];
    opterr = 0;

    // int reti;
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;
        FILE *f_pattern;
        f_pattern = fopen(argv[optind], "r");
        while (f_pattern != NULL && !feof(f_pattern)) {
            if (fgets(c_pattern, 1000, f_pattern) != NULL) {
                if (c_pattern[strlen(c_pattern) - 1] == '\n')
                    c_pattern[strlen(c_pattern) - 1] = 0;
                regex_t regex;
                reti = regcomp(&regex, c_pattern, 0);
                f = fopen(argv[i], "r");
                if (f != NULL) {
                    while (fgets(c, 1000, f) != NULL) {
                        reti = regexec(&regex, c, 0, NULL, 0);
                        if (reti == 0) {
                            if ((argc - 1) - (optind + 1) > 0) {
                                printf("%s:", argv[i]);
                            }
                            if (!feof(f)) {
                                printf("%s", c);
                            } else {
                                printf("%s\n", c);
                            }
                        }
                    }
                    regfree(&regex);
                    fclose(f);
                    fclose(f_pattern);
                } else {
                    printf(
                        "grep: %s: No such file or directory\n",
                        argv[i]);  // сделать обработку на не существующий файл
                }
                // fclose(f);
            }
        }
        // fclose(f_pattern);
    }
}

void Get_pattern_O(int argc, char *argv[]) {
    // FILE *f;  // для файла
    char c[1000];  // мфссив для считывания строки из файла
    // int reti;  //
    regmatch_t pmatch[2];
    // struct_count = 0};
    for (int i = optind + 1; i < argc; i++) {
        int reti;
        FILE *f;  // для файла
        f = fopen(argv[i], "r");
        regex_t regex;
        reti = regcomp(&regex, argv[optind], 0);
        // size_t nmatch = 0;
        if (f != NULL) {  // если ф существует
            // size_t nmatch = 0;
            while (fgets(c, 1000, f) != NULL) {  // пока не считали все строки
                int offset = 0;
                int count_pat_in_str = 0;
                while (*(c + offset) != 0) {
                    reti = regexec(&regex, c + offset, 2, pmatch,
                                   0);  // ищем регулярное выражение в с
                    if (reti == 0) {  // если нашли, то 0
                        ++count_pat_in_str;
                        int len_match = pmatch[0].rm_eo - pmatch[0].rm_so;
                        if ((argc - 1) - (optind + 1) > 0 &&
                            count_pat_in_str <=
                                1) {  // проверка на количество файлов
                            printf("%s:%.*s\n", argv[i], len_match,
                                   c + pmatch[0].rm_so + offset);
                        } else {
                            printf("%.*s\n", len_match,
                            c + pmatch[0].rm_so + offset);
                        }

                        offset += pmatch[0].rm_eo;
                    } else {
                        break;
                    }
                }
                // printf("%lld\n", struct_count.rm_eo);
                // printf("%ld\n", nmatch);
            }
            regfree(&regex);
            fclose(f);
        } else {
            printf("grep: %s: No such file or directory\n",
                   argv[i]);  // сделать обработку на не существующий файл
        }
        // fclose(f);
    }
}
