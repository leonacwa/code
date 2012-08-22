#include <iostream>
using namespace std;
struct Window{
	int x1, y1, x2, y2,i;
};
Window w[101];
bool in_w(int x, int y, const  Window w) {
	return (w.x1 <= x && x <= w.x2) && (w.y2 <= y && y <= w.y1);
}

int main()
{
	int T;
	cin >> T;
	while (T--) {
		int n, x, y;
		cin >> n >> x >> y;
		for (int i = 1; i <= n; ++i) {
			int x1, y1, x2, y2, k;
			cin >> x1 >> y1 >> x2 >> y2 >> k;
			w[k].x1 = x1;
			w[k].y1 = y1;
			w[k].x2 = x2;
			w[k].y2 = y2;
			w[k].i = i;
		}
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			if (in_w(x, y, w[i])) {
				cout << w[i].i << endl;
				flag = false;
				break;
			}
		}
		if (flag)
			cout << "Vagaa" << endl;
	}
	return 0;
}

