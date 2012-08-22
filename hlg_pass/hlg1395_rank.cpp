#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 205;
const int MAXM = 21;
const int STRLEN = 32;
struct TeamSubmit {
	char name[STRLEN];
	int submit[MAXM], penalty[MAXM];
} TS[MAXN];
struct TeamInfo {
	char name[STRLEN];
	int solve, penalty, weight;
} TI[MAXN];

bool cmpTI(const TeamInfo &A, const TeamInfo &B) {
	if (A.solve != B.solve) return A.solve > B.solve;
	if (A.penalty != B.penalty) return A.penalty < B.penalty;
	if (A.weight != B.weight) return A.weight > B.weight;
	return strcmp(A.name, B.name) < 0;
}

int weight[MAXM];
int solve[MAXM];
int fb[MAXM];

int main()
{
	int n, m;
	while (2 == scanf("%d %d", &n, &m)) {
		for (int i = 0; i < m; ++i) {
			weight[i] = 0;
			solve[i] = 0;
			fb[i] = INT_MAX;
		}
		for (int i = 0; i < n; ++i) {
			scanf("%s", TS[i].name);
			char str[256];
			for (int j = 0; j < m; ++j) {
				TS[i].submit[j] = -1;
				TS[i].penalty[j] = -1;
				scanf("%s", str);
				char* p = strchr(str, '\\');
				*p = 0;
				if (str[0] != '-') {
					TS[i].submit[j] = atoi(str);
				} else {
					TS[i].submit[j] = 0;
				}
				if (*(p+1) != '-') {
					TS[i].penalty[j] = atoi(p+1);
					fb[j] = min(fb[j], TS[i].penalty[j]);
					++solve[j];
				} else {
					TS[i].penalty[j] = 0;
				}
			}
		}
		for (int i = 0; i < m; ++i) {
			if (solve[i] > 0) {
				weight[i] = n / solve[i];
			} else {
				weight[i] = 0;
			}
		}
		for (int i = 0; i < n; ++i) {
			strcpy(TI[i].name, TS[i].name);
			TI[i].solve = 0;
			TI[i].penalty = 0;
			TI[i].weight = 0;
			for (int j = 0; j < m; ++j) {
				if (TS[i].penalty[j] > 0) {
					TI[i].solve++;
					TI[i].weight += weight[j];
					TI[i].penalty += TS[i].penalty[j];
					if (fb[j] != TS[i].penalty[j]) {
						TI[i].penalty += (TS[i].submit[j] - 1) * 20;
					}
				}
			}
		}
		sort(TI, TI + n, cmpTI);
		int rank = 0;
		int last_solve = INT_MAX, last_penalty = 0, last_weight = INT_MAX;
		for (int i = 0; i < n; ++i) {
			if (last_solve != TI[i].solve || last_penalty != TI[i].penalty || last_weight != TI[i].weight) {
				rank = i + 1;
			}
			last_solve = TI[i].solve;
			last_penalty = TI[i].penalty;
			last_weight = TI[i].weight;

			printf("%3d %20s %2d %6d %4d\n", rank, TI[i].name, last_solve, last_penalty, last_weight);
		}
	}
	return 0;
}

