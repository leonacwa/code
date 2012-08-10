#include <cstdio>
#include <cstring>

char str[8024];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			char *first, *second;
			bool can = false;
			/*
			first = strchr(str, 'C');
			while (first && (second = strchr(first + 1, 'D'))) {
				if (first + 1 < second) {
					can = true;
					break;
				}
				first = strchr(first + 1, 'C');
			}
			*/
			/*
			if (can == false) {
				first = strchr(str, 'D');
				while (first && (second = strchr(first + 1, 'C'))) {
					if (first < second) {
						can = true;
						break;
					}
					first = strchr(first + 1, 'D');
				}
			}
			if (can) ++ans;
			*/
			//if (strstr(str, "DC") == NULL) ++ans;
			if (strstr(str, "CD") == NULL) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}

