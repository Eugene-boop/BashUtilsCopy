#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "s21_cat.h"

#define no_argument 0

int main(int argc, char *argv[]) {
    flags short_flags = {0, 0, 0, 0, 0, 0, 0};
    const char *short_options = "benstv";
    const struct option long_options[] = {
        {"number-nonblank", no_argument, &short_flags.fl_b, 'b'},
        {"E", no_argument, &short_flags.fl_e, 'e'},
        {"number", no_argument, &short_flags.fl_n, 'n'},
        {"squeeze-blank", no_argument, &short_flags.fl_s, 's'},
        {"T", no_argument, &short_flags.fl_t, 't'},
        {NULL, 0, NULL, 0},
    };
    short_flags =
    Get_Flags(argc, argv, short_flags, short_options, long_options);
    if (short_flags.fl_b == 1) {
        Paste_to_number_str(argv, argc);
    } else if (short_flags.fl_e == 1) {
        show_to_array_V(argv, argc, 1);
    } else if (short_flags.fl_n == 1) {
        Paste_to_number_all_str(argv, argc);
    } else if (short_flags.fl_s == 1) {
        Paste_to_delete_str(argv, argc);
    } else if (short_flags.fl_t == 1) {
        Paste_to_hellikopt_from_tab(argv, argc);
    } else if (short_flags.fl_v == 1) {
        show_to_array_V(argv, argc, 0);
    } else {
        Shove_to_array(argv, argc);
    }
}

void Shove_to_array(char *argv[], int argc) {
    for (int i = optind; i < argc; i++) {
        FILE *f_readed;
        f_readed = fopen(argv[i], "r");
        if (f_readed != NULL) {
            char c[1000];
            while (!feof(f_readed)) {
                if (fgets(c, 1000, f_readed) != NULL) {
                    if (!feof(f_readed))
                        printf("%s", c);
                    else
                        printf("%s", c);
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[i]);
        }
    }
}

void Paste_to_number_str(char *argv[], int argc) {
    char c[1000];
    for (int j = optind; j < argc; j++) {
        FILE *f_readed = fopen(argv[j], "r");
        if (f_readed != NULL) {
            int i = 1;
            while (!feof(f_readed)) {
                if (fgets(c, 1000, f_readed) != NULL) {
                    if (c[0] == '\n') {
                        printf("%s", c);
                    } else {
                        printf("%6d\t%s", i, c);
                        i++;
                    }
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[j]);
        }
    }
}

void Paste_to_number_all_str(char *argv[], int argc) {
    for (int j = optind; j < argc; j++) {
        FILE *f_readed;
        f_readed = fopen(argv[j], "r");
        if (f_readed != NULL) {
            char c[1000];
            int i = 1;
            while (!feof(f_readed)) {
                if (fgets(c, 1000, f_readed) != NULL) {
                    printf("%6d\t%s", i, c);
                    i++;
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[j]);
        }
    }
}

void Paste_to_dallar_end_str(char *argv[], int argc) {
    for (int j = optind; j < argc; j++) {
        FILE *f_readed;
        f_readed = fopen(argv[j], "r");
        if (f_readed != NULL) {
            while (!feof(f_readed)) {
                char c[1000];
                if (fgets(c, 1000, f_readed) != NULL) {
                    for (int i = 0; i < 1000; i++) {
                        if (c[i] == '\n') {
                            c[i] = '$';
                        }
                    }
                    if (!feof(f_readed))
                        printf("%s\n", c);
                    else
                        printf("%s", c);
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[j]);
        }
    }
}

void Paste_to_delete_str(char *argv[], int argc) {
    for (int j = optind; j < argc; j++) {
        FILE *f_readed;
        f_readed = fopen(argv[j], "r");
        if (f_readed != NULL) {
            int count = 0;
            while (!feof(f_readed)) {
                char c[1000];
                if (fgets(c, 1000, f_readed) != NULL) {
                    if ((c[0] == '\n' && count < 1) || c[0] != '\n') {
                        printf("%s", c);
                        if (c[0] == '\n') count++;
                        // continue;
                        if (c[0] != '\n') {
                            // printf("\n");
                            count = 0;
                        }
                    }
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[j]);
        }
    }
}

void Paste_to_hellikopt_from_tab(char *argv[], int argc) {
    for (int e = optind; e < argc; e++) {
        FILE *f_readed;
        f_readed = fopen(argv[e], "r");
        if (f_readed != NULL) {
            while (!feof(f_readed)) {
                char c[1000];
                if (fgets(c, 1000, f_readed) != NULL) {
                    int i = 0;
                    int j = 0;
                    char c_copy[1000];
                    while (c[i] != '\0') {
                        if (c[i] == '\t') {
                            c_copy[j] = '^';
                            j++;
                            c_copy[j] = 'I';
                        } else {
                            c_copy[j] = c[i];
                        }
                        i++;
                        j++;
                    }
                    c_copy[j] = '\0';
                    if (!feof(f_readed)) printf("%s", c_copy);
                    else
                        printf("%s", c);
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[e]);
        }
    }
}

void show_to_array_V(char *argv[], int argc, int isE) {
    for (int e = optind; e < argc; e++) {
        FILE *f_readed;
        f_readed = fopen(argv[e], "r");
        if (f_readed != NULL) {
            while (!feof(f_readed)) {
                unsigned char c[1000] = "";
                c[0] = 0;
                if (fgets((char*)c, 1000, f_readed) != NULL) {
                    unsigned char c_copy[1000] = "";
                    int i = 0;
                    int j = 0;
                    while (c[i] != '\0') {
                        if (((char)c[i] >= 0 && (char)c[i] < 9) || \
                        ((char)c[i] > 10 && (char)c[i] < 32)) {
                            c_copy[j++] = '^';
                            c_copy[j] = c[i] + 64;
                        } else if (c[i] == 127) {
                            c_copy[j++] = '^';
                            c_copy[j] = '?';
                        } else if (c[i] > 127 && c[i] < 160) {
                            c_copy[j++] = 'M';
                            c_copy[j++] = '-';
                            c_copy[j++] = '^';
                            c_copy[j] = c[i] - 64;
                        } else if (isE) {
                            if (c[i] == '\n')
                                c[i] = '$';
                            c_copy[j] = c[i];    
                        } else {
                            if (c[i] == '\n')
                                c[i] = '\0';
                            c_copy[j] = c[i];
                        }
                        i++;
                        j++;

                    }
                    // if (isE) c_copy[j++] = '$';
                    // c_copy[j] = '\0';
                    if (!feof(f_readed))
                        printf("%s\n", c_copy);
                    else
                        printf("%s", c_copy);
                }
            }
            fclose(f_readed);
        } else {
            printf("cat: %s: No such file or directory\n", argv[e]);
        }
    }
}

flags Get_Flags(int argc, char *const argv[], flags short_flags, \
const char *short_options, const struct option long_options[]) {
    int rezult = 0;
    opterr = 0;
    while ((rezult = getopt_long(argc, argv, short_options, long_options, NULL)) !=
           -1) {
        switch (rezult) {
            case 'b':
                short_flags.fl_b = 1;
                // Paste_to_number_str(name);
                break;  // нумерует не пустые строки
            case 'e':
                short_flags.fl_e = 1;
                // Paste_to_dallar_end_str(name);
                break;  // вставляет доллар
            case 'n':
                short_flags.fl_n = 1;
                // Paste_to_number_all_str(name);
                break;  // нумерует все выходные строки
            case 's':
                short_flags.fl_s = 1;
                // Paste_to_delete_str(name);
                break;  // сжимает несколько соседних строк
            case 't':
                short_flags.fl_t = 1;
                // Paste_to_hellikopt_from_tab(name);
                break;  // вместо \t вставляем ^|
            case 'v':
                short_flags.fl_v = 1;
                // show_to_array_V(name);
                break;  // переводит из двоичной системы в десятичную, читаемый
                        // вид
            case '?':
                printf("Error found !\n");
                break;
        }
    }
    return short_flags;
}
