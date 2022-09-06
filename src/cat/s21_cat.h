#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>

#define no_argument 0

typedef struct all_flags {
    int fl_b;
    int fl_e;
    int fl_n;
    int fl_s;
    int fl_t;
    int fl_v;
    char *name;
} flags;

void Shove_to_array(char *argv[], int argc);
void Paste_to_number_str(char *argv[], int argc);
void Paste_to_number_all_str(char *argv[], int argc);
void Paste_to_dallar_end_str(char *argv[], int argc);
void Paste_to_delete_str(char *argv[], int argc);
void Paste_to_hellikopt_from_tab(char *argv[], int argc);
void show_to_array_V(char *argv[], int argc, int isE);
flags Get_Flags(int argc, char *const argv[], flags short_flags,
const char *short_options, const struct option long_options[]);

#endif  // SRC_CAT_S21_CAT_H_
