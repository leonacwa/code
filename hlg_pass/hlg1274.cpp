/* 1.去掉有日的出现次数为1的月份，留下日出现次数为多次的。
 * 2.去掉日重复的日期，留下日只出现一次的。
 * 3.留下月次数为1的。
 * */
#include <stdio.h>
#include <string.h>

int m[11], n[11];
int cnt[11];
bool del[11];
bool sgl[11];

int main()
{
	int T;
	scanf("%d", &T);
	for (int nCase = 1; nCase <= T; nCase++) {
		memset(del, 0, sizeof(del));
		printf("Case %d:\n", nCase);
		// 1
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < 10; i++) {
			scanf("%d.%d", &m[i], &n[i]);
			cnt[n[i]]++;
		}
		memset(sgl, 0, sizeof(sgl));
		for (int i = 0; i < 10; i++) {
			if (cnt[n[i]] == 1) {
				sgl[m[i]] = true;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (sgl[m[i]]) {
				del[i] = true;
	//			printf("del %d.%d\n", m[i], n[i]);
			}
		}
		// 2
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < 10; i++) {
			if (!del[i]) {
				cnt[n[i]]++;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (!del[i] && cnt[n[i]] != 1) {
				del[i] = true;
	//			printf("del %d.%d\n", m[i], n[i]);
			}
		}
		// 3
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < 10; i++) {
			if (!del[i]) {
				cnt[m[i]]++;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (!del[i] && cnt[m[i]] != 1) {
				del[i] = true;
	//			printf("del %d.%d\n", m[i], n[i]);
			}
		}
		// ans
		for (int i = 0; i < 10; i++) {
			if (!del[i]) {
				printf("%d.%d\n", m[i], n[i]);
			}
		}
	}
	return 0;
}

