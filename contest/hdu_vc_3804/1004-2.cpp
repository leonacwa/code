/* Trouble
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int64;
const int MAX_HASH = 1638400 + 1;

int64 s[5][205];

struct Node {
	int64 key;
	Node * next;
};
int nM = 0;
Node mem[MAX_HASH], *hash[MAX_HASH];

void ins(int64 v) {
	int64 p = (v % MAX_HASH + MAX_HASH) % MAX_HASH;
	while (p < 0) ;
	Node * ptr = hash[p];
	while (ptr) {
		if (ptr->key == v) return;
		ptr = ptr->next;
	}
	mem[nM].key = v;
	mem[nM].next = hash[p];
	hash[p] = mem + nM++;
}

bool find(int64 v) {
	int64 p = (v % MAX_HASH + MAX_HASH) % MAX_HASH;
	while (p < 0) ;
	Node * ptr = hash[p];
	while (ptr) {
		if (ptr->key == v) return true;
		ptr = ptr->next;
	}
	return false;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%lld", &s[i][j]);
				//scanf("%I64d", &s[i][j]);
			}
		}
		memset(hash, 0, sizeof(hash));
		nM = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				ins(-(s[0][i] + s[1][j]));
			}
		}
		bool ans = false;
		for (int i = 0; i < n && !ans; ++i) {
			for (int j = 0; j < n && !ans ; ++j) {
				int64 t2 = s[2][i] + s[3][j];
				for (int k = 0; k < n && !ans; ++k) {
					if (find(t2 + s[4][k])) {
						ans = true;
						break;
					}
				}
			}
		}
		puts(ans ? "Yes" : "No");
	}
	return 0;
}
