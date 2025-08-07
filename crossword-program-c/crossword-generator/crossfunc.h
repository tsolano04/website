//Thomas Solano
//Fund Comp
//Lab8
//crossfunc.h

#define word_length 15
#define num_words 20

int check_word(char*);
void uppercase(char*);
void create_board(char[][word_length], char);
void print_board(char[][word_length]);
void fprint_board(char[][word_length], FILE*);
void sort_words(char[][word_length], int);
void make_clues(char[][word_length], char[][word_length], int);
void build_puzzle(char[][word_length], char[][word_length], char*, int[num_words], int, int[][word_length], int[], int[]);
int check_across(char [][word_length], int, int, int, int, char);
int check_down(char [][word_length], int, int, int, int, char);

