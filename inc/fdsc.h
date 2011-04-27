#ifndef FDSC_H
#define FDSC_H

#define SWAP(x,y,tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

struct _sSMatrix
{
	int row;
	int col;
	int value;
};

typedef struct _sSMatrix SparseMatrix;

typedef int (*Sort_Func)(int* ptr, int size);

int sort_autotest(Sort_Func func);

int sort_select(int* p_data, int size);

void perm_rec(char* list, int s, int e);

int horner(int* a, int n, int x);

void perm_bool_rec0(unsigned char* bit, int s, int e);

int perm_bool_rec(int n);

int hanota(int n, char a, char b, char c);

void magic_square_creator(int n);

SparseMatrix* sparse_matrix_create(void);

int sparse_matrix_print(SparseMatrix* ptr);

int sparse_matrix_sort(SparseMatrix* ptr);

int sparse_matrix_transpose_0(SparseMatrix* ptr);

int sparse_matrix_transpose_1(SparseMatrix* ptr);

int sparse_matrix_transpose_fast(SparseMatrix* ptr);

int kmp_mismatch(char* pat, int* array, int size);

char* string_match_kmp(char* s, char* pat);

int pattern_match_test(void);




#endif
