#include "s21_grep.h"

int parser(int argc, char *argv[], flags *myflags) {
    char *short_options = "eivclnhsf:o";
    struct option long_options[] = {{"f", no_argument, NULL, 'b'},
                                    {NULL, 0, NULL, 0}};
    int rez;
    int option_index = 0;
    while ((rez = getopt_long(argc, argv, short_options, long_options,
                              &option_index)) != -1) {
        switch (rez) {
            case 'e': {
                myflags->e = 1;
                break;
            };
            case 'i': {
                myflags->i = 1;
                break;
            };
            case 'v': {
                myflags->v = 1;
                break;
            };
            case 'c': {
                myflags->c = 1;
                break;
            };
            case 'l': {
                myflags->l = 1;
                break;
            };
            case 'n': {
                myflags->n = 1;
                break;
            };
            case 'h': {
                myflags->h = 1;
                break;
            };
            case 's': {
                myflags->s = 1;
                break;
            };
            case 'f': {
                myflags->file = optarg;
                myflags->f = 1;
                break;
            };
            case 'o': {
                myflags->o = 1;
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
char *get_pattern(char *filename) {
    FILE *patternFile = fopen(filename, "r");
    char *pattern = malloc(2000);
    char *pattern_p = pattern;
    char *line;
    while ((line = read_line(patternFile))) {
        if (*line == '\n') {
            *line = '.';
        }
        char *line_p = line;
        for (; *line_p; line_p++) {
            if (*line_p == '\n') {
                *pattern_p++ = '|';
                continue;
            }
            *pattern_p++ = *line_p;
        }

        free(line);
    }
    *pattern_p = 0;
    if (*(pattern_p - 1) == '|') *(pattern_p - 1) = 0;
    fclose(patternFile);
    return pattern;
}

void processFiles(int parse_count, flags grepflags, int argc, char *argv[]) {
    // in case of multiple files, so we know to print filename or not, but we
    // always need it for -l
    char is_prefix = argc - parse_count > 1;
    char *pattern;

    if (grepflags.f) {
        pattern = get_pattern(grepflags.file);
    } else {
        pattern = argv[parse_count++];
    }

    for (int i = parse_count; i < argc; i++) {
        char *filename = argv[i];
        FILE *file = fopen(filename, "r");
        if (file) {
            process_file(file, filename, pattern, grepflags, is_prefix);
            fclose(file);
        } else if (!grepflags.s) {
            printf("s21_grep: %s: No such file or directory\n", filename);
        }
    }
    if (grepflags.f) free(pattern);
}

char *read_line(FILE *file) {
    char ch = fgetc(file);
    if (feof(file)) return NULL;
    size_t size = 5;
    char *line = malloc(size + 2);
    char *result = line;
    char multiplier = 1;
    size_t read = 0;
    for (; !feof(file) && ch != '\n'; ch = fgetc(file)) {
        read++;
        if (read > multiplier * size) {
            multiplier++;
            result = realloc(result, multiplier * size + 2);
            line = result + read - 1;
        }
        *line++ = ch;
    }
    if (!feof(file)) *line++ = '\n';
    *line = 0;
    return result;
}

void process_file(FILE *file, char *filename, char *pattern, flags grepflags,
                  char is_prefix) {
    char *line;
    regex_t regex;
    int reti;
    if (grepflags.f) {
        reti = regcomp(&regex, pattern, REG_EXTENDED);
    } else if (grepflags.i) {
        reti = regcomp(&regex, pattern, REG_ICASE);
    } else {
        reti = regcomp(&regex, pattern, 0);
    }

    size_t matches = 0;
    for (int line_number = 1; (line = read_line(file)); line_number++) {
        regmatch_t matched[2];
        int print_size = 0, print_start_index, search_start_index = 0;
        while (1) {
            if (grepflags.o && !grepflags.c && !grepflags.l && !grepflags.v) {
                char *newsearch = line + +search_start_index;
                reti = regexec(&regex, newsearch, 2, matched, 0);
                if (reti) break;
                print_size = matched[0].rm_eo - matched[0].rm_so;
                print_start_index = matched[0].rm_so + search_start_index;
                search_start_index = print_start_index + print_size;
            } else {
                reti = regexec(&regex, line, 0, NULL, 0);
            }

            if ((reti && grepflags.v) || (!reti && !grepflags.v)) {
                if (grepflags.l) {
                    matches++;
                    break;
                } else if (grepflags.c) {
                    matches++;
                    break;
                } else {
                    if (is_prefix && !grepflags.h) printf("%s:", filename);
                    if (grepflags.n) printf("%d:", line_number);
                    if (grepflags.o && !grepflags.c && !grepflags.l &&
                        !grepflags.v) {
                        printf("%.*s\n", print_size, line + print_start_index);
                    } else {
                        printf("%s", line);
                    }
                    if (!(grepflags.o && !grepflags.c && !grepflags.l &&
                          !grepflags.v))
                        break;
                }
            } else {
                break;
            }
        }
        free(line);
        if ((grepflags.l && matches)) break;
    }
    if (grepflags.c) {
        if (is_prefix && !grepflags.h) printf("%s:", filename);
        printf("%lu\n", matches);
    }
    if (grepflags.l && matches) printf("%s\n", filename);
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    flags grepflags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int parse_count = parser(argc, argv, &grepflags);
    if (!grepflags.error) {
        processFiles(parse_count, grepflags, argc, argv);
    } else {
        printf("error");
    }
    return 0;
}
