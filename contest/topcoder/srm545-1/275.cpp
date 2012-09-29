#define noDEBUG

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int MAXN = 30;
bool vis[MAXN];

int minCan(int n, string str, char ch) {
	str += ch;
	for (char c = 'a'+n-1; c >= 'a'; --c) {
		//for (char c = 'a'; c <'a'+n; ++c) {
		if (!vis[c-'a'] && c != ch) str += c;
	}
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			if (str[i] > str[j]) ++ret;
		}
	}
	return ret;
}

class StrIIRec {
	public:
		string recovstr(int n, int minInv, string minStr) {
			string ans = "";
			bool big = false;
			memset(vis, 0, sizeof(vis));
			for (int i = 0; i < n; ++i) {
				for (char c = 'a'; c < 'a' + n; ++c) {
					if ((big || c >= minStr[i]) &&  !vis[c-'a'] && minCan(n, ans, c) >= minInv) {
						ans += c;
						vis[c - 'a'] = true;
						if (c > minStr[i]) big = true;
						break;
					}
				}
				if (ans.length() < i+1) return "";
			}
			return ans;
		}
	protected:
	private:
};

#ifdef DEBUG
int main()
{
	int n, minInv;
	string minStr;
	StrIIRec sol;
	while (cin >> n >> minInv >> minStr) {
		cout << n << " " << minInv << " " << minStr << endl;
		string ans = sol.recovstr(n, minInv, minStr);
		cout << ans.length() << " " << ans << endl;
		int ret = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				if (ans[i] > ans[j]) ++ret;
			}
		}
		cout << "Inv:" << ret << endl;
	}
	return 0;
}
#endif

