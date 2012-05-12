#include <stdio.h>
#include <ctype.h>
#include <string.h>
const int NN = 1000;
struct Node {
	char type;
	int value;
	struct Node *left, *right;
};
int cnt_node;
Node node[NN];
Node *st[NN];
int top;
char op_st[NN];
int op_top;
char str[NN];

bool isOP(char c)
{
	return '+' == c || '-' == c || '*' == c || '/' == c || '(' == c || ')' == c;
}
bool can(char a, char b)
{
	if (a == '(' && b == ')') return false;
	if (a == '(') return false;
	if (b == '+' || b == '-' || b == ')') return true;
	if (a == '*' || a == '/') return true;
	return false;
}

Node* exp(const char *s)
{
	top = -1;
	op_top = -1;
	cnt_node = 0;
	while (*s) {
		if (isdigit(*s)) {
			int v = 0;
			while (isdigit(*s)) {
				v = v * 10 + *s - '0';
				++s;
			}
			Node * ptr = node + cnt_node++;
			ptr->type = 'n';
			ptr->value = v;
			ptr->left = NULL;
			ptr->right = NULL;
			st[++top] = ptr;
		} else if (isOP(*s)) {
			while (op_top > -1 && can(op_st[op_top], *s)) {
				Node * ptr = node + cnt_node++;
				ptr->type = op_st[op_top--];
				ptr->right = st[top--];
				ptr->left = st[top--];
				st[++top] = ptr;
			}
			if (op_top > -1 && op_st[op_top] == '(' && *s == ')') {
				--op_top;
			} else if (*s != ')') {
				op_st[++op_top] = *s;
			} else {
				printf("error:%c %c\n", op_st[op_top], *s);
				return NULL;
			}
			++s;
		} else if (isspace(*s)) {
			++s;
		} else {
			return NULL;
		}
	}
	while (top > -1 && op_top > -1) {
		Node * ptr = node + cnt_node++;
		ptr->type = op_st[op_top--];
		ptr->right = st[top--];
		ptr->left = st[top--];
		st[++top] = ptr;
	}
	return st[top];
}

void post_dfs(Node *root)
{
	if (root == NULL) return;
	post_dfs(root->left);
	post_dfs(root->right);
	if (root->type == 'n') {
		printf("%d ", root->value);
	} else {
		printf("%c ", root->type);
	}
}

int main()
{
	while (gets(str)) {
		printf("%s\n", str);
		Node *ptr = exp(str);
		if (ptr == NULL) {
			puts("error");
		} else {
			post_dfs(ptr);
		}
	}
	puts("");
	return 0;
}

