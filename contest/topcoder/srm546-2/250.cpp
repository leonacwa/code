#define DEBUG

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1000000;

struct Contestant {
	int id, solve, time;
	bool operator < (const Contestant &B) const {
		if (solve != B.solve) return solve > B.solve;
		return time < B.time;
	}
} con[MAXN+1];

class ContestWinner {
	public:
		int getWinner(vector <int> events) {
			int n = events.size();
			memset(con, 0, sizeof(con));
			for (int i = 0; i <= MAXN; ++i) con[i].id = i;
			for (int i = 0; i < n; ++i) {
				int id = events[i];
				++con[id].solve;
				con[id].time = i;
			}
			sort(con+1, con+MAXN+1);
			return con[1].id;
		}
};

#ifdef DEBUG
int main()
{
	return 0;
}
#endif

