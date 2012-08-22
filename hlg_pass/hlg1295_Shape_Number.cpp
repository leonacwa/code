#include <stdio.h>
#include <string.h>

const int SL = 300000 + 5;
char s[SL], t[SL];

int MinString(char* s, char* t) 
{
	int ls = strlen(s);
	int i = 0, j = 1, cnt = 0, d;
	while (i < ls && j < ls && cnt < ls) {
		d = s[(i+cnt) % ls] - s[(j+cnt) % ls];
		if (d == 0 ) {
			++cnt;
		} else {
			if (d > 0) {
				i += cnt + 1;
			} else {
				j += cnt + 1;
			}
			if (i == j) ++j;
			cnt = 0;
		}
	}
	if (i < j) j = i;
	if (t) {
		for (i = 0; i < ls; ++i) {
			t[i] = s[(i+j) % ls];
		}
		t[ls] = 0;
	}
	return j;
}

int main()
{
	while (EOF != scanf("%s", s)) {
		int ls = strlen(s);
		for (int i = 0; s[i]; ++i) {
			int j = (i + 1) % ls;
			if (s[i] <= s[j]) {
				t[i] = s[j] - s[i] + '0';
			} else {
				t[i] = 8 - (s[i] - '0') + s[j];
			}
		}
		t[ls] = 0;
		MinString(t, s);
		puts(s);
	}
	return 0;
}

