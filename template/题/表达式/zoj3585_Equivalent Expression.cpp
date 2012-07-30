/*
* zoj3585 Equivalent Expression
* 根据编译原理，写出文法诡诈，然后对每个元素写过程进行解析，这样能大大降低编码难度，好挑错，好更改 
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

char aVar[16][16];
int nVar;

/*
void p_exp(char s[])
{
	for (int i = 0; s[i]; ++i) {
		if (s[i] < 16) printf("%d", s[i]);
		else putchar(s[i]);
	}
	printf("\n");
}
void p_v( int v)
{
	for (int i = 0; i < nVar; ++i) {
		printf("%s %d, ", aVar[i], 0 != v & (1 << i));
	}
	puts("");
}
*/
int find(char s[]) 
{
	for (int i = 0; i < nVar; ++i) {
		if (0 == strcmp(s, aVar[i])) return i + 1;
	}
	return 0;
}

int add(char s[])
{
	strcpy(aVar[nVar], s);
	++nVar;
	return nVar;
}

bool isOP(char c) {
	return (c == '!') || (c == '&') || (c == '|') || (c == '^') || (c == '(') || (c == ')');
}

char *s;
int p, v;
bool exp();
bool term();
bool fact();
bool var();

bool exp()
{
	bool a, b;
	a = term();
	while (s[p] == '^') {
		++p;
		b = term();
		a ^= b;
	}
	return a;
}
bool term()
{
	bool a, b;
	a = fact();
	while (s[p] == '|') {
		++p;
		b = fact();
		a |= b;
	}
	return a;
}
bool fact()
{
	bool a, b;
	a = var();
	while (s[p] == '&') {
		++p;
		b = var();
		a &= b;
	}
	return a;
}
bool var()
{
	bool a = false;
	if (s[p] <= nVar) {
		a = (v & (1 << (s[p] - 1))) > 0;
		++p;
	} else if (s[p] == '!') {
		++p;
		a = var();
		a = !a;
	} else if (s[p] == '(') {
		++p; // (
		a = exp();
		++p; // )
	} else {
		while (1) puts("error");
	}
	return a;
}

int main()
{
	char sa[256], sb[256];
	char e0[256], e1[256];
	int le0, le1;
	char name[16];
	int ln;

	while (gets(sa) && sa[0] != 0) {
		if (NULL == gets(sb)) break;
		
		nVar = 0;
		le0 = 0;
		for (int i = 0; sa[i]; ++i) {
			if (isalpha(sa[i])) {
				ln = 0;
				while (isalpha(sa[i])) {
					name[ln++] = sa[i];
					++i;
				}
				name[ln] = 0;
				--i;
				int id = find(name);
				if (id == 0) id = add(name);
				e0[le0++] = id;
			} else if (isOP(sa[i])) {
				e0[le0++] = sa[i];
			}
		}
		e0[le0] = 0;

		le1 = 0;
		for (int i = 0; sb[i]; ++i) {
			if (isalpha(sb[i])) {
				ln = 0;
				while (isalpha(sb[i])) {
					name[ln++] = sb[i];
					++i;
				}
				name[ln] = 0;
				--i;
				int id = find(name);
				if (id == 0) id = add(name);
				e1[le1++] = id;
			} else if (isOP(sb[i])) {
				e1[le1++] = sb[i];
			}
		}
		e1[le1] = 0;
		/*
		for (int i = 0; i < nVar; ++i) {
			printf("%s ", aVar[i]);
		}
		puts("");
		p_exp(e0);
		p_exp(e1);
		*/
		bool a = true, b = true;
		for (v = (1 << nVar); v >= 0; --v) {
			//p_v(v);
			s = e0;
			p = 0;
			a = exp();
			s = e1;
			p = 0;
			b = exp();
	//		printf("  %d   %d\n", a, b);
			if (a != b) break;
		}
		if (a == b) {
			puts("TRUE");
		} else {
			puts("FALSE");
		}
	}
	return 0;
}

