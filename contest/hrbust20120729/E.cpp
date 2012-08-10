#include <cstdio>
#include <cstring>

bool match(char *s, char *p) {
	char *f, *rp = p;
	bool w = false;
	char b[256];
	int l;
	for (; *p; ++p) {
		if (*p == '*') w = true;
		else {
			l = 0;
			rp = p;
			while (*p && *p != '*') b[l++] = *p++;
			b[l] = 0;
			f = strstr(s, b);
			if (f == NULL) return false;
			if (!w && f != s) return false;
			if (*p == '\0') {
				//printf("0 %s %s\n", s, rp);
				int ls = strlen(s), lp = strlen(rp);
				if (!w && ls != lp) return false;
				for (int i = lp-1, j = ls-1; i >= 0 && j >= 0; --i, --j) {
					if (s[j] != rp[i]) return false;
				}
				break;
			}
			s = f + l;
			w = false;
			--p;
		}
	}
	return true;
}

int main() {
	char p[256], s[256];
	int n;
	while (EOF != scanf("%s", p)) {
		scanf("%d", &n);
		while (n--) {
			scanf("%s",s);
			if (match(s,p)) puts(s);
		}
	}
	return 0;
}
