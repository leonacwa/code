#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <set>
using namespace std;
int main() {
	int n, k, x, nmin, ans;
	char str[10];
	multiset<int, greater<int> > st;
	multiset<int, greater<int> > :: reverse_iterator it;
	while (scanf("%d%d", &n, &k) != EOF) {
		st.clear();
		while (n--) {
			scanf("%s", str);
			if (str[0] == 'I') {
				scanf("%d", &x);
				if (st.size() >= k) {
					nmin = *(st.rbegin());
					if (x > nmin) {
						st.erase(st.find(nmin));
						st.insert(x);
					}
				} else {
					st.insert(x);
				}
			} else {
				it = st.rbegin();
				ans = *it;
				printf("%d\n", ans);
			}
		}
		
	}
}
