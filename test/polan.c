#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int isDigitStr(const char *s)
{
	if (*s == '\0') return 0;
	while (*s && isdigit(*s)) ++s;
	return *s == '\0';
}

int isOP(char c)
{
	return ('+' == c) || ('-' == c) || ('*' == c) || ('/' == c);
}

int calc(int a, int b, char op)
{
	switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
		default:
				  puts("Operator Error!");
	}
	return 0;
}

int main()
{
	int stk[1024];
	int top = -1;
	int a, b;
	char s[1024];
	while (EOF != scanf("%s", s) && s[0] != '#') {
		if (isDigitStr(s)) {
			stk[++top] = atoi(s);
		} else if (isOP(s[0]) && top > 0) {
			b = stk[top--];
			a = stk[top--];
			stk[++top] = calc(a, b, s[0]);
	//		printf("OP:%s  %d\n", s, stk[top]);
		} else {
			puts(s);
			puts("Error!");
			break;
		}
	//	printf("top:%d, %s\n", top, s);
	}
	if (top == 0) 
		printf("%d\n", stk[top]);
	else 
		puts("error");
	return 0;
}

