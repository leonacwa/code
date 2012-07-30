#include <cstdio>
#include <cstring>

char pwd[32], word[32];
char str[1000000+100];

int main()
{
    while (EOF != scanf("%s", str)) {
		int m, n, ans = 0;
        scanf("%d%s", &m, pwd);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", word);
			if (strlen(word) != m) puts("word length error");
			for (int l = 0; str[l]; ++l) {
				int j;
				for (j = 0; j < m; ++j) {
					if(pwd[j] == '1' || str[l+j] == word[j]) {
					} else {
						break;
					}
				}
				if (j == m) {
					++ans;
					break;
				}
			}
		}
        printf("%d\n", ans);
    }
    return 0;
}

