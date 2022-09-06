#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
union {
    int flag;
    typedef struct all_flags {
        int fl_e : 1;
        int fl_i : 1;
        int fl_v : 1;
        int fl_c : 1;
        int fl_l : 1;
        int fl_n : 1;
        int fl_h : 1;
    } flags;
}


flags Get_Flags(int argc, char *const argv[], flags myflags);
void Get_pattern_E(int argc, char *argv[]);  // доделать E если несколько флагов
void Get_pattern_I(int argc, char *argv[], flags myflags);
void Get_pattern_V(int argc, char *argv[], flags myflags);
void Get_pattern_C(int argc, char *argv[], flags myflags);
void Get_pattern_L(int argc, char *argv[], flags myflags);
void Get_pattern_N(int argc, char *argv[], flags myflags);
void Get_pattern_H(int argc, char *argv[], flags myflags);
void Get_pattern_S(int argc, char *argv[]);
void Get_pattern_F(int argc, char *argv[]);
void Get_pattern_O(int argc, char *argv[]);

#endif  // SRC_GREP_S21_GREP_H_
