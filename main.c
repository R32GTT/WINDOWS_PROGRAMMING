#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
typedef union {
	char oper;
	int  op;
}Content;

typedef struct Stack
{
	Content* data;
	int top;
	int capacity;
}Stack;

int is_empty(Stack* s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

void init(Stack* s, int cap)
{
	
	s->data = (Content*)malloc(sizeof(Content) * cap);
	s->capacity = cap;
	s->top = -1;

}

void push(Stack* s, Content data)
{
	if (s->top == s->capacity - 1)

	{
		s->capacity += 5;
		s->data = (Content*)realloc(s->data, s->capacity);
	}
	s->data[++s->top] = data;

}

Content peek(Stack* s)
{
	if (is_empty(s))
		exit(0);
	return s->data[s->top];

}

Content pop(Stack* s)
{
	if (is_empty(s))
		exit(0);
	return s->data[s->top--];
}

void Free(Stack* s)
{
	free(s->data);
	free(s);
}

int prec(char op)
{
	switch (op)
	{
	case '(': case ')':
		return 0;
	case '+': case '-':
		return 1;
	case '*': case '/':
		return 2;
	}
	return -1;
}

void infix_to_postfix(const char* ex, char* pex)
{
	Stack* stk;
	stk = (Stack*)malloc(sizeof(Stack));
	init(stk, 50);

	int i = 0;
	Content top_op;
	Content ch;
	int x = 0;
	int len = strlen(ex);
	for (i = 0; i < len; i++) {
		ch.oper = ex[i];
		switch (ch.oper) {
		case '+': case '-': case '*': case '/': 
			while (!is_empty(stk) && (prec(ch.oper) <=
				prec(peek(stk).oper)))
			{//printf("%c", pop(stk).oper);
				pex[x++] = pop(stk).oper;
			}
			push(stk, ch);
			break;
		case '(':
			// 왼쪽 괄호
			push(stk, ch);
			break;

		case ')':
			// 오른쪽 괄호
			top_op.oper = pop(stk).oper;
			// 왼쪽 괄호를만날때까지출력
			while (top_op.oper != '(') {
				//printf("%c", top_op.oper);
				pex[x++] = top_op.oper;
				top_op = pop(stk);
			}
			break;
		default:
			// 피연산자
			//printf("%c", ch.oper);
			pex[x++] = ch.oper;
			break;
		}
	}
	while (!is_empty(stk)) // 스택에 저장된 연산자들 출력
		//printf("%c", pop(stk).oper);
		pex[x++] = pop(stk).oper;
}

	



int eval(const char* pex)
{
	Stack* stk;
	stk = (Stack*)malloc(sizeof(Stack));
	init(stk, 50);
	int i,op1,op2, n = strlen(pex);
	int cnt = 0;
	int res;
	Content tem;
	char ch;
	char* end;
	char temp[20] = {""};
	//피연산자 넣고 연산자 뜨면 피연산자 2번 pop 그리고 연산
	
	for (i = 0; i < n; i++)
	{
		ch = pex[i];
		switch (ch)
		{
		case ' ':
		if(cnt>0){
			tem.op = atoi(temp);
			memset(temp, "", sizeof(char)*20);
			push(stk, tem);
			cnt = 0;
		}
			break;
		case '+': 
			if (cnt > 0)
			{
				tem.op = atoi(temp);
				memset(temp, "", sizeof(char));
				push(stk, tem);
				cnt = 0;
			}
				op2 = pop(stk).op;
				op1 = pop(stk).op;
				tem.op = op1 + op2;
				push(stk, tem);

			break;
		case '-': 
			if (cnt > 0)
			{
				tem.op = atoi(temp);
				memset(temp, "", sizeof(char));
				push(stk, tem);
				cnt = 0;
			}

				op2 = pop(stk).op;
				op1 = pop(stk).op;
				tem.op = op1 - op2;
				push(stk, tem);
			
			break;
		case '*': 
			if (cnt > 0)
			{
				tem.op = atoi(temp);
				memset(temp, "", sizeof(char));
				push(stk, tem);
				cnt = 0;
			}

				op2 = pop(stk).op;
				op1 = pop(stk).op;
				tem.op = op1 * op2;
				push(stk, tem);
			
			break;
		case '/':
			if (cnt > 0)
			{
				tem.op = atoi(temp);
				memset(temp, "", sizeof(char));
				push(stk, tem);
				cnt = 0;
			}

				op2 = pop(stk).op;
				op1 = pop(stk).op;
				tem.op = op1 / op2;
				push(stk, tem);
			
			break;

		default:
			temp[cnt++] = ch;
			break;
		}
	}
	
	res = pop(stk).op;

	if (!is_empty(stk))
	{
		Free(stk);
		return -1;
	}

	Free(stk);
	return res;
}

// main 함수
int main(void)
{


	char* expr = "100 + 11 * 20 *(20+ 10) / 100 +5 -3";
	//char* expr = "30 - 25 * (2 3 * 3)";

	char pexpr[100] = ""; // 후위표기 수직 저장용

	int result; // 연산 결과 저장용


	printf("중위표기 수식 : %s \n", expr);
	infix_to_postfix(expr, pexpr);
	printf("후위표기 수식 : %s \n", pexpr);
	result = eval(pexpr);
	if (result == -1)
	{
		printf("수식 오류");
		return 0;
	}
	printf("연산 결과 : %d \n", result);
	return 0;
}
#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

#define MAZE_SIZE 6
char maze[MAZE_SIZE][MAZE_SIZE] = {
{'e', '0', '1', '1', '1', '1'},
{'1', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '1'},
{'1', '0', '1', '0', '1', '1'},
{'1', '0', '1', '0', '0', 'x'},
{'1', '1', '1', '1', '1', '1'},
};


//typedef union {
//	char oper;
//	int  op;
//}Content;

typedef struct
{
	int x;
	int y;
}Content;

typedef struct Stack
{
	Content* data;
	int top;
	int capacity;
}Stack;

int is_empty(Stack* s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

void init(Stack* s, int cap)
{

	s->data = (Content*)malloc(sizeof(Content) * cap);
	s->capacity = cap;
	s->top = -1;

}

void push(Stack* s, Content data)
{
	if (s->top == s->capacity - 1)
	{
		s->capacity += 5;
		s->data = (Content*)realloc(s->data, s->capacity);
	}
	s->data[++s->top] = data;
}

Content peek(Stack* s)
{
	if (is_empty(s))
		exit(0);
	return s->data[s->top];

}

Content pop(Stack* s)
{
	if (is_empty(s))
		exit(0);
	return s->data[s->top--];
}

void Free(Stack* s)
{
	free(s->data);
	free(s);
}

enum
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

void SolveMaze()
{
	Stack* Pdes; Stack* route;
	Pdes = (Stack*)malloc(sizeof(Stack));
	route = (Stack*)malloc(sizeof(Stack));

	init(Pdes, 20);
	init(route, 50);


	Content curpos, nextpos, endpos;
	int isend = 0;

	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int f = 0; f < MAZE_SIZE; f++)
		{
			if (maze[i][f] == 'e')
			{
				curpos.x = f; curpos.y = i;
				break;
			}
			else if (maze[i][f] == 'x');
			{
				endpos.y = i, endpos.x = f;
			}
		}
	}


	while (!isend)
	{
		int isblocked = 0;
		if()

	}

}

int main()
{




}
#endif