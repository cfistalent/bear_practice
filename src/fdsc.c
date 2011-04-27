#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers.h"

/*
 *Function:	sort fuction autotest programme.
 *In:		func	function pointer to be tested
 *Out:		-
 *Note:		get datalen from tester,generate data from rand(),
 *			just test if it's working correctly.
 *LM:		2011-4-1
 */
int sort_autotest(Sort_Func func)
{
	ret_val_if_fail(func != NULL, -1);
	int		datalen = 0;
	int*	dataptr = NULL;
	int		tret = 0;
	int		i = 0;

	printf("Sort Function testing...\n");
	while(1)
	{
		printf("Please input data length(10 to 32766) :\n");
		scanf("%d",&datalen);
		if((datalen < 327667) && (datalen > 9))
		{
			break;
		}
		printf("Incorrect input, input again.\n");
	}
	dataptr = (int*)malloc(sizeof(int) * datalen);
	if(dataptr == NULL)
	{
		printf("Mem alloc fail.\n");
		return -1;
	}
	srand((int)time(NULL));
	for(i=0; i<datalen; i++)
	{
		dataptr[i] = rand() % 32766;
	}
	
	tret = func(dataptr, datalen);
	if(tret < 0)
	{
		printf("func test fail.\n");
		free(dataptr);
		return -1;
	}
	for(i=1; i<datalen; i++)
	{
		if(dataptr[i] < dataptr[i-1])
		{
			printf("func is not working correctly.\n");
		}
	}
	printf("func is working correctly.\n");
	
	free(dataptr);
	return 0;		
}

/*
 *Function:	sort by selection
 *In:		p_data	pointer to data buffer
 *			size	data length
 *Out:		-1 means faild while 0 means OK
 *Note:		-
 *LM:		2011-4-1
 */
int sort_select(int* p_data, int size)
{
	ret_val_if_fail(p_data != NULL && size > 1, -1);
	int		i,j;
	int		smallest;
	int		tmp;

	for(i=0; i<(size-1); i++)
	{
		smallest = i;
		for(j=i+1; j<size; j++)
		{
			if(p_data[j] < p_data[smallest])
			{
				smallest = j;
			}
		}
		if(smallest != i)
		{
			SWAP(p_data[i],p_data[smallest],tmp);	
		}
	}
		
	return 0;
}

/*
 *
 *
 */
int bin_search(int* p_data, int size, int dat2search)
{
	ret_val_if_fail(p_data != NULL && size > 0, -1);
	int low,high,mid;
	int ret = 0;
	int judge = 0;

	low = 0;
	high = size - 1;
	mid = ((low + high) >> 1);
	while(low <= high)
	{
		judge = (p_data[mid] < dat2search ? -1 : (p_data[mid] = dat2search) ? 0 : 1 );
		switch(judge)
		{
			case -1:
				low = mid + 1;
				mid = ((low + high) >> 1);
				break;
			case 0:
				printf("match %d in %d place.\n",dat2search,mid);
				goto MATCH;
			case 1:
				high = mid - 1;
				mid = ((low + high) >> 1);
				break;
			default:
				break;
		}
	}

	return -1;
MATCH:
	return mid;
}

/*
 *Function:	show all possible permutation from a array recursively
 *In:		list	source array
 *			s		start position to generate permutation
 *			e		end position to generate permutation
 *Out:		None
 *Note:		-
 *LM:		2011-4-2
 */
void perm_rec(char* list, int s, int e)
{
	int i,j;
	int tmp;

	if(s == e)
	{
		for(i=0; i<=e; i++)
		{
			printf("%c ",list[i]);
		}
		printf("\n");
	}
	else
	{
		for(j=s; j<=e; j++)
		{
			SWAP(list[j],list[s],tmp);
			perm_rec(list, s+1, e);
			SWAP(list[j],list[s],tmp);
		}
	}
}

/*
 *Function:	Return a value of a multinomial when x is given a specified value
 *In:		a		coefficient of multinomial,a0,a1...an
 *			n		length
 *			x		given value of x
 *Out:		value of the multinomial when x is given 
 *Note:		Useage of Horner principle.P9,2.
 *LM:		2011-4-2
 */
int horner(int* a, int n, int x)
{
	ret_val_if_fail(a != NULL && n > 0, -1);
	int i;
	int sum;

	sum = a[n-1];
	for(i=n-2; i>=0; i--)
	{
		sum = sum*x + a[i];
	}

	return sum;
}

/*
 *Function:	output all permutation of bool array recursively
 *In:		bit		bool array
 *			s		from bit[s] to process
 *			e		end position
 *Out:		None
 *Note:		It use recursive function calling 
 *LM:		2011-4-2
 */
void perm_bool_rec0(unsigned char* bit, int s, int e)
{
	int i;

	if(s > e)
	{
		for(i=0; i<=e; i++)
		{
			printf("%d ",bit[i]);
		}
		printf("\n");
	}
	else
	{
		bit[s] = 0;
		perm_bool_rec0(bit, s+1, e);
		bit[s] = 1;
		perm_bool_rec0(bit, s+1, e);
	}
}

int perm_bool_rec(int n)
{
	ret_val_if_fail(n > 0, -1);
	unsigned char* bit;

	bit = (unsigned char*)malloc(sizeof(*bit) * n);
	if(bit == NULL)
	{
		printf("Memory allocation failed!\n");
		return -1;
	}
	 
	perm_bool_rec0(bit, 0, n-1);	

	free(bit);
}

/*
 *Function:	Hanota game solution using recursive algorithm
 *In:		n		number of plates,assuming the biggist plate under buttom 
 *					has the biggist number N,while the smallest has number 0
 *			a,b,c	moving plate from a to c by the way of b
 *Out:		None
 *Note:		P9,11.
 *LM:		2011-4-2
 */
int hanota(int n, char a, char b, char c)
{
	if(n == 1)
	{
		printf("move %d from %c to %c\n",n,a,c);
	}
	else
	{
		hanota(n-1,a,c,b);
		printf("move %d from %c to %c\n",n,a,c);
		hanota(n-1,b,a,c);
	}

	return 0;
}

/*
 *Function:	Magic square creator.To form a NxN matrix that has the 
 *			same value in any row ,any column and two diagonals
 *In:		n		size of the matrix
 *Out:		-
 *Note:		-
 *LM:		2011-4-3
 */
void magic_square_creator(int n)
{
	int**	square;
	int		i,j;
	int		cnt;
	int		row,col;
	int		total;

	if(!(n > 0 && (n % 2)))
	{
		printf("Invalid input paramater.Programe %s quit.\n",__func__);
		return;
	}
	else
	{
		total = n * n;
		for(i=0; i<n; i++)
		{
			square = (int**)malloc(sizeof(int*) * n);
		}
		for(i=0; i<n; i++)
		{
			square[i] = (int*)malloc(sizeof(int) * n);
		}
		if(square == NULL)
		{
			printf("Memory allocation fail.\n");
			return;
		}
		for(i=0; i<n; i++)
		{
			for(j=0; j<n; j++)
			{
				square[i][j] = 0;
			}
		}

		i=0;
		j=((n-1)>>1);
		square[i][j] = 1;
		for(cnt=2; cnt<=total; cnt++)
		{
			row = (((i - 1) < 0) ? (n - 1) : (i - 1));
			col = (((j - 1) < 0) ? (n - 1) : (j - 1));
			if(square[row][col] != 0)
			{
				col = j;
				row = (((i + 1) >= n) ? (0) : (i + 1));
			}
			i = row;
			j = col;
			square[i][j] = cnt;
		}

		for(i=0; i<n; i++)
		{
			printf("Line%d:\t",i);
			for(j=0; j<n; j++)
			{
				printf("%d\t",square[i][j]);
			}
			printf("\n");
		}

		for(i=0; i<n; i++)
		{
			free(square[i]);
		}
		free(square);
	}
}

/*
 *Function:	create a sparse matrix.It's row,column and none-zero elements are
 *			set by user.
 *In:		-
 *Out:		SparseMatrix*	a pointer which points to the matrix array
 *Note:		-
 *LM:		2011-4-8
 */
SparseMatrix* sparse_matrix_create(void)
{
	SparseMatrix* ptr = NULL;
	int row,col,number;
	int cnt;

	printf("Start to create a sparse matrix.\n");
	printf("Input row,column and numbers of non-zero elements:\n");
	while(1)
	{
		printf("row= \n");
		scanf("%d",&row);
		if(row <= 0)
		{
			printf("row should larger than Zero!\n");
		}
		else
		{
			break;		
		}
	}
	while(1)
	{
		printf("col= \n");
		scanf("%d",&col);
		if(col <= 0)
		{
			printf("col should larger than Zero!\n");
		}
		else
		{
			break;		
		}
	}
	while(1)
	{
		printf("number= \n");
		scanf("%d",&number);
		if(number <= 0)
		{
			printf("number should larger than Zero!\n");
		}
		else
		{
			break;		
		}
	}
	ptr = (SparseMatrix*)malloc(sizeof(*ptr) * (number + 1));
	if(ptr == NULL)
	{
		printf("Memory alloc fail\n");
		goto QUIT;
	}
	ptr[0].row = row;
	ptr[0].col = col;
	ptr[0].value = number;
	for(cnt = 1; cnt <= number; cnt++)
	{
		printf("Ele %d: row\n",cnt);
		scanf("%d",&ptr[cnt].row);
		printf("Ele %d: col\n",cnt);
		scanf("%d",&ptr[cnt].col);
		printf("Ele %d: value\n",cnt);
		scanf("%d",&ptr[cnt].value);
	}
	sparse_matrix_print(ptr);

QUIT:
	return ptr;
}

/*
 *Function:	print the whole matrix
 *In:		ptr		pointer to sparse matrix
 *Out:		-1 means fail, 0 means OK
 *Note:		-
 *LM:		2011-4-8
 */
int sparse_matrix_print(SparseMatrix* ptr)
{
	ret_val_if_fail(ptr != NULL, -1);

	int col,row,number;
	int i,j,cnt;

	row = ptr[0].row;
	col = ptr[0].col;
	number = ptr[0].value;

	printf("the %d x %d matrix is:\n",row,col);
	cnt = 1;
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
			if(cnt <= number)
			{
				if((ptr[cnt].row == i) && (ptr[cnt].col == j))
				{
					printf("%d\t",ptr[cnt].value);
					cnt++;
				}
				else
				{
					printf("0\t");
				}
			}
			else
			{
				printf("0\t");
			}
		}
		printf("\n");
	}

	return 0;
}

/*
 *Function:	sort the matrix in increasing order of row and col
 *In:		ptr		pointer to matix
 *Out:		-
 *Note:		-
 *LM:		2011-4-8
 */
int sparse_matrix_sort(SparseMatrix* ptr)
{
	ret_val_if_fail(ptr != NULL, -1);
	int number;
	int i,j;
	SparseMatrix tmp;

	number = ptr[0].value;
	for(i=number; i>1; i--)
	{
		for(j=1; j<i; j++)
		{
			if(ptr[j].row > ptr[j+1].row)		//if row is bigger,switch
			{
				SWAP(ptr[j],ptr[j+1],tmp);
			}
			else if(ptr[j].row == ptr[j+1].row)
			{
				if(ptr[j].col > ptr[j+1].col)	//if in the same row,but col bigger,switch
				{
					SWAP(ptr[j],ptr[j+1],tmp);
				}
			}
		}
	}
}

/*
 *Function:	the following three functions realize transposing of matrix.
 *In:		ptr		pointer to the sparse matrix
 *Out:		-
 *Note:		the fast transpose algorithm use the method in counting sort
 *LM:		2011-4-8
 */
int sparse_matrix_transpose_0(SparseMatrix* ptr)
{
	ret_val_if_fail(ptr != NULL, -1);

	int number;
	int i;
	int tmp;

	number = ptr[0].value;

	for(i=0; i<= number; i++)
	{
		SWAP(ptr[i].row,ptr[i].col,tmp);	
	}
	sparse_matrix_sort(ptr);

	return 0;
}

int sparse_matrix_transpose_1(SparseMatrix* ptr)
{
	ret_val_if_fail(ptr != NULL, -1);

	int row,col,number;
	int i,j;
	int cnt;
	int tmp;
	SparseMatrix* o_ptr = NULL;

	row = ptr[0].row;
	col = ptr[0].col;
	number = ptr[0].value;
	o_ptr = (SparseMatrix*)malloc(sizeof(*o_ptr) * (number + 1));
	if(o_ptr != NULL)
	{
		o_ptr[0].row = col;
		o_ptr[0].col = row;
		o_ptr[0].value = number;
		cnt = 1;
		for(i=0; i<col; i++)
		{
			for(j=1; j<=number; j++)
			{
				if(ptr[j].col == i)
				{
					o_ptr[cnt].row = ptr[j].col;
					o_ptr[cnt].col = ptr[j].row;
					o_ptr[cnt].value = ptr[j].value;
					cnt++;
				}
			}
		}
		memcpy(ptr, o_ptr, sizeof(*ptr) * (number + 1));

		free(o_ptr);
		return 0;
	}
	
	return -1;
}

int sparse_matrix_transpose_fast(SparseMatrix* ptr)
{
	ret_val_if_fail(ptr != NULL, -1);

	int row,col,number;
	int i,j;
	int cnt;
	int* col_num;
	int* col_start_pos;
	SparseMatrix* o_ptr = NULL;

	row = ptr[0].row;
	col = ptr[0].col;
	number = ptr[0].value;
	col_num = (int*)malloc(sizeof(*col_num) * col);
	memset(col_num,0,sizeof(*col_num) * col);	
	col_start_pos = (int*)malloc(sizeof(*col_start_pos) * col);
	memset(col_start_pos,0,sizeof(*col_start_pos) * col);
	o_ptr = (SparseMatrix*)malloc(sizeof(*o_ptr) * (number + 1));
	for(i=1; i<=number; i++)
	{
		col_num[ptr[i].col]++;
	}
	col_start_pos[0] = 1;	
	for(i=1; i<col; i++)
	{
		col_start_pos[i] = col_start_pos[i-1] + col_num[i-1];
	}
	o_ptr[0].row = col;
	o_ptr[0].col = row;
	o_ptr[0].value = number;
	for(i=1; i<=number; i++)
	{
		j = col_start_pos[ptr[i].col];
		o_ptr[j].row = ptr[i].col;
		o_ptr[j].col = ptr[i].row;
		o_ptr[j].value = ptr[i].value;
		col_start_pos[ptr[i].col]++;
	}
	memcpy(ptr, o_ptr, sizeof(*ptr) * (number + 1));

	free(col_num);
	free(col_start_pos);
	free(o_ptr);
	return 0;
}

/*
 *Function:	create mismatch-jump-array used in KMP
 *In:		pat		sub string for pattern match
 *			array	mismatch-jump-array
 *			size	size of the pat and array.the two are as long
 *Note:		-
 *LM:		2011-4-9
 */
int kmp_mismatch(char* pat, int* array, int size)
{
	ret_val_if_fail(pat != NULL && size > 0 && array != NULL, -1);

	int i,j;

	array[0] = -1;
	i = 0;
	j = -1;
	while(i < size)
	{
		if((j == -1) || (pat[i] == pat[j]))
		{
			i++;
			j++;
			array[i] = j;
		}
		else
		{
			j = array[j];
		}
	}
	
	DBG("the mismatch-jump-array is:\n");
	for(i=0; i<size; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");

	return 0;
}

/*
 *Function:	match specified sub string in main string using KMP algorithm
 *In:		s		main string
 *			pat		sub string
 *Out:		char*	the position in main string, NULL if not found		
 *Note:		-
 *LM:		2011-4-9
 */
char* string_match_kmp(char* s, char* pat)
{
	ret_val_if_fail(s != NULL && pat != NULL, NULL);

	int		i,j;
	int		s_len;
	int		pat_len;
	int*	next;
	char*	ret_pos;

	ret_pos = NULL;
	s_len = strlen(s);
	pat_len = strlen(pat);
	next = (int*)malloc(sizeof(*next) * pat_len);
	if(next == NULL)
	{
		printf("Memory allocation fail\n");
		return NULL;
	}
	i = 0;
	j = 0;
	if(!kmp_mismatch(pat, next, pat_len))
	{
		while(i < s_len)
		{
			if((j == -1) || (s[i] == pat[j]))
			{
				i++;
				j++;			
			}
			else
			{
				j = next[j];
			}
			if(j == pat_len)
			{
				ret_pos = s + (i - pat_len);
				DBG("found sub string in %d pos.\n",i-pat_len);
			}
		}
	}

	return ret_pos;
}

int pattern_match_test(void)
{
	char	s[512];
	char	pat[512];

	printf("Start to test the pattern match algorithm\n");
	printf("please input main string:\n");
	gets(s);
	printf("main string is:%s\n",s);
	printf("please input sub string:\n");
	gets(pat);
	printf("sub string is :%s\n",pat);
	string_match_kmp(s,pat);

	return 0;
}
