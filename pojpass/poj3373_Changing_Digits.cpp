#include <stdio.h>
#include <string.h>

char s[256];
int k;
int sl;
int f[256];
int mem[256][10000+5];

bool ID_dfs(int step, int res, int p)
{
	if (res == 0) {
		return true;
	}
	if (step == 0 || p >= sl || mem[step][res] <= p) {
		return false;
	}
	char ch;
	int tmp = res;
	for (int i = p; i < sl; i++) {
		for (char j = '0'; j < s[i]; j++) {
			if (i == 0 && j == '0') {
				continue;
			}
			ch = s[i];
			s[i] = j;
			tmp = (res - (ch-j)*f[i] % k + k) % k;
			if (ID_dfs(step-1, tmp, i+1)) {
				return true;
			}
			s[i] = ch;
		}
	} 
	for (int i = sl-1; i >= p; i--) {
		for (char j = s[i]+1; j <= '9'; j++) {
			ch = s[i];
			s[i] = j;
			tmp = (res + (j - ch)*f[i] % k) % k;
			if (ID_dfs(step-1, tmp, i+1)) { // i位置改变了，i+1到sl-1就需要重新变化，这样才能保证最小
				return true;
			}
			s[i] = ch;
		}
	} /*
		 if (ID_dfs(step, res, p+1)) {
		 return true;
		 }*/
	mem[step][res] = p;
	return false;
}

int main()
{
	while (EOF != scanf("%s\n", s)) {
		scanf("%d", &k);
		sl = strlen(s);
		f[sl-1] = 1 % k;
		for (int i = sl-2; i >= 0; i--) {
			f[i] = f[i+1]*10 % k;
		}
		int res = 0;
		for (int i = 0; i < sl; i++) {
			res = (res + (s[i]-'0')*f[i]) % k;
		}
		memset(mem, 0x3f, sizeof(mem));
		for (int step = 1; step < sl; step++) {
			if (ID_dfs(step, res, 0)) {
				break;
			}
		}
		puts(s);
	}
	return 0;
}

