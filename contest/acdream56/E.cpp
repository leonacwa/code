/* Distinct Primes
 * */
#include <cstdio>
#include <cstring>

const int MAX_PM = 1000000;
bool is[MAX_PM];
int prm_cnt, prm[1111];

int cnt;
int a[1111];

void init_prime() {
	prm_cnt = 0;
	memset(is, 1, sizeof(is));
	is[0] = is[1] = false;
	for (int i = 2; i < MAX_PM; ++i) {
		if (is[i]) {
			prm[prm_cnt++] = i;
			if (prm_cnt >= 1000) {
	//			printf("end %d\n", i);
				break;
			}
			for (int j = i + i; j < MAX_PM; j += i) {
				is[j] = false;
			}
		}
	}
	/*
	printf("prm_cnt %d\n", prm_cnt);
	for (int i = 0; i < prm_cnt; ++i) printf("%d,", prm[i]);
	puts("");
	*/
}

bool check(int x) {
	int s = 0;
	for (int i = 0; i < prm_cnt && prm[i] <= x; ++i) {
		if (x % prm[i] == 0) ++s;
		if (s >= 3) return true;
	}
	return false;
}

void init_ans() {
	cnt = 0;
	for (int i = 30; i < MAX_PM; ++i) {
		if (check(i)) a[cnt++] = i;
		if (cnt >= 1000) {
		//	printf("end ans %d\n", i);
			break;
		}
	}
	//printf("ans_cnt %d\n", cnt);
}

int main() {
	init_prime();
	init_ans();
	int runs, n;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d", &n);
		printf("%d\n", a[n-1]);
	}
	return 0;
}
