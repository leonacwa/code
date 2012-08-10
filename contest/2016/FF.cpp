#include <stdio.h>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
struct NODE {
	NODE() {}
	NODE(int a, int b) : num(a), cnt(b) {}
	int num, cnt;
	bool operator<(const NODE &b) const {
		return cnt < b.cnt;
	}

};
int opt[100005][3];
int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		map<int, int> mp;
		priority_queue<NODE> qu;
		for (int i = 0; i < n; i++) {
			int num;
			scanf("%d", &num);
			mp[num]++;
		}
		for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
			qu.push(NODE(it->first, it->second));
		}
		int ans = 0;
		while (qu.size() >= 3) {
			NODE np[3];
			for (int i = 0; i < 3; i++) {
				np[i] = qu.top();
				qu.pop();
				opt[ans][i] = np[i].num;
				np[i].cnt--;
			}
			for (int i = 0; i < 3; i++) {
				if (np[i].cnt != 0) {
					qu.push(np[i]);
				}
			}
			sort(opt[ans], opt[ans] + 3);
			ans++;
		}
		printf("%d\n", ans);
		for (int i = 0; i < ans; i++) {
			printf("%d %d %d\n", opt[i][2], opt[i][1], opt[i][0]);
		}
	}
}