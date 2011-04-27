#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

/*
 *Function:	parse input expression string
 *			into an array of operands and operators
 *In:		str			expression string
 *			str_size	string len
 *			expr		pointer to the array, it's a two-dimensional pointer
 *			esize		pointer to the array len
 *Out:		-1 fail; 0 success
 *Note:		-
 *LM:		2011-4-18
 */
ExpEle*	express_parse(char* str,int str_size, int* esize)
{
	ret_val_if_fail(str != NULL && str_size > 0, NULL);
	int i,cnt,tmp;
	int max_size = DEFAULT_SIZE;
	ExpEle* expr;

	expr = (ExpEle*)malloc(sizeof(ExpEle) * max_size);
	ret_val_if_fail(expr != NULL, NULL);

	cnt = 0;
	for(i=0; i<str_size; i++)
	{
		switch(str[i])
		{
			case '(':
				(expr)[cnt].type = lp;
				break;
			case ')':
				(expr)[cnt].type = rp;
				break;
			case '+':
				(expr)[cnt].type = plus;
				break;
			case '-':
				(expr)[cnt].type = minus;
				break;
			case '*':
				(expr)[cnt].type = multi;
				break;
			case '/':
				(expr)[cnt].type = divi;
				break;
			case ' ':
				cnt--;
				break;
			default:
				(expr)[cnt].type = op;
				tmp = 0;
				while(IS_DIGIT(str[i+1]) == 0)
				{
					tmp = tmp * 10 + (str[i] - '0');
					i++;
				}
				tmp = tmp * 10 + (str[i] - '0');
				(expr)[cnt].val = tmp;
				break;
		}
		cnt++;
		if(cnt >= max_size)
		{
			max_size = max_size + (max_size >> 1);
			expr = realloc(expr, max_size);
		}
	}
	*esize = cnt;

	return expr;
}

ExpEle* express_postfix(ExpEle* eptr, int len, int* out_len)
{
	ret_val_if_fail(eptr != NULL && len > 0, NULL);
	ExpEle*	stack = NULL;
	ExpEle*	out = NULL;
	int		stack_cur = -1;
	int		out_cur = 0;
	int		i;
	int		pri_instack[] = {0,10,2,2,4,4};
	int		pri_outstack[] = {8,10,2,2,4,4};

	stack = (ExpEle*)malloc(sizeof(ExpEle) * len);
	ret_val_if_fail(stack != NULL, NULL);
	out = (ExpEle*)malloc(sizeof(ExpEle) * len);
	if(out == NULL)
	{
		printf("Mem alloc fail\n");
		free(stack);
		return NULL;
	}
	for(i=0; i<len; i++)
	{
		if(eptr[i].type == op)
		{
			out[out_cur++] = eptr[i];
		}
		else if(eptr[i].type == rp)
		{
			while(stack[stack_cur].type != lp)
			{
				out[out_cur++] = stack[stack_cur--];
			}
			stack_cur--;
		}
		else
		{
			while((stack_cur >= 0) && (pri_instack[stack[stack_cur].type] >= pri_outstack[eptr[i].type]))
			{
				out[out_cur++] = stack[stack_cur--];
			}
			stack[++stack_cur] = eptr[i];
		}
	}
	while(stack_cur >= 0)
	{
		out[out_cur++] = stack[stack_cur--];
	}

	free(stack);
	free(eptr);	
	*out_len = out_cur;

	return out;
}

int express_cal(int op1, int op2, expr_type x)
{
	int result;

	switch(x)
	{
		case plus:
			result = op1 + op2;
			DBG("%d + %d = %d\n",op1,op2,result);
			break;
		case minus:
			result = op2 - op1;
			DBG("%d - %d = %d\n",op1,op2,result);
			break;
		case multi:
			result = op1 * op2;
			DBG("%d * %d = %d\n",op1,op2,result);
			break;
		case divi:
			result = op2 / op1;
			DBG("%d / %d = %d\n",op1,op2,result);
			break;
		defalut:
			break;
	}
	return result;
}

int express_value(ExpEle* eptr, int len, int* result)
{
	ret_val_if_fail(eptr != NULL && len > 0 && result != NULL, -1);
	int*	stack;
	int		stack_cur;
	int		op1,op2;
	int		i;

	stack = (int*)malloc(sizeof(*stack) * len);
	ret_val_if_fail(stack != NULL, -1);
	stack_cur = -1;
	for(i=0; i<len; i++)
	{
		if(eptr[i].type != op)
		{
			op1 = stack[stack_cur--];
			op2 = stack[stack_cur--];
			stack[++stack_cur] = express_cal(op1,op2,eptr[i].type);
		}
		else
		{
			stack[++stack_cur] = eptr[i].val;
		}
	}
	*result = stack[0];

	free(stack);
	return 0;
}

/*
 *Function:	print the expression
 *In:		expr		pointer to the expression array
 *			len			expression array len
 *Out:		-1 fail; 0 success
 *Note:		-
 *LM:		2011-4-18
 */
int express_print(ExpEle* expr, int len)
{
	ret_val_if_fail(expr != NULL && len > 0, -1);
	int i;
	char expr_table[] = {'(',')','+','-','*','/'};

	for(i = 0; i < len; i++)
	{
		if(expr[i].type == op)
		{
			printf("%d",expr[i].val);
		}
		else
		{
			printf("%c",expr_table[expr[i].type]);
		}
	}
	printf("\n");
}

int express_test(void)
{
	char	str_buffer[1024];
	ExpEle*	eptr = NULL;
	ExpEle* post_eptr = NULL;
	int		len;
	int		post_len;
	int		result;

	printf("Input your expression:\n");
	gets(str_buffer);
	eptr = express_parse(str_buffer, strlen(str_buffer), &len);
	express_print(eptr, len);
	post_eptr = express_postfix(eptr, len, &post_len);
	express_print(post_eptr, post_len);
	express_value(post_eptr, post_len, &result);
	printf("Result is:%d\n",result);

	free(post_eptr);
	return 0;
}
