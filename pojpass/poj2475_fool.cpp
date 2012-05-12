#include <stdio.h>
#include <string.h>
const int nSet = 0;
const int nElemlist = 1;
const int nList = 2;
const int nElem = 3;
const int nAtom = 4;

char s[201];
int mem[201][201][5];

int set(int f, int r);
int elemlist(int f, int r);
int list(int f, int r);
int elem(int f, int r);
int atom(int f, int r);

int set(int f, int r)
{
	if (mem[f][r][nSet] != -1) return mem[f][r][nSet];
	if (s[f] == '{' && s[r] == '}' && elemlist(f+1, r-1)) {
		return mem[f][r][nSet] = 1;
	}
	return mem[f][r][nSet] = 0;
}

int elemlist(int f, int r)
{
	if (mem[f][r][nElemlist] != -1) return mem[f][r][nElemlist];
	if (f == r+1) return mem[f][r][nElemlist] = 1;
	return mem[f][r][nElemlist] = list(f, r);
}

int list(int f, int r)
{
	if (mem[f][r][nList] != -1) return mem[f][r][nList];
	if (elem(f, r)) {
		return mem[f][r][nList] = 1;
	}
	for (int i = f; i <= r; ++i) {
		if (s[i] == ',') {
			mem[f][r][nList] = elem(f, i-1) && list(i+1, r);
			if (mem[f][r][nList]) {
				return mem[f][r][nList];
			}
		}
	}
	return mem[f][r][nList] = 0;
}

int elem(int f, int r)
{
	if (mem[f][r][nElem] != -1) return mem[f][r][nElem];
	mem[f][r][nElem] = atom(f, r);
	if (mem[f][r][nElem] == 0) {
		mem[f][r][nElem] = set(f, r);
	}
	return mem[f][r][nElem];
}

int atom(int f, int r)
{
	if (mem[f][r][nAtom] != -1) return mem[f][r][nAtom];
	return mem[f][r][nAtom] = f == r;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int nCase = 1; nCase <= n; ++nCase) {
		scanf("%s", s);
		memset(mem, -1, sizeof(mem));
		printf("Word #%d:%s Set\n", nCase, set(0, strlen(s) -1) ? "" : " No");
	}
	return 0;
}

