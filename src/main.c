#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(int argc,char* argv[])
{
	int ret = 0;
	SparseMatrix sm[5]={{4,4,4},{0,3,1},{1,2,2},{2,1,3},{3,0,4}};

#if 0
	sparse_matrix_print(sm);
	sparse_matrix_transpose_fast(sm);
	sparse_matrix_print(sm);
#endif
	poly_test();

	return ret;
}
