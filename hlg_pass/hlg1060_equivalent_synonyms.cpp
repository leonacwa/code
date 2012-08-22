#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
const int MAXN = 200000+5;

map<string, int> dict;
vector<string> in;
vector<string> syn[MAXN];
vector<string> ans[MAXN];

bool check(int i, int j)
{
	int p, q;
	for (p = 0; p < syn[i].size(); p++) {
		if (syn[i][p] == syn[j][0]) {
			break;
		}
	}
	if (p == syn[i].size()) {
		return false;
	}
	for (q = 0; q < syn[j].size(); q++) {
		if (syn[j][q] == syn[i][0]) {
			break;
		}
	}
	if (q == syn[j].size()) {
		return false;
	}
	return true;
}

int main()
{
	string buf;
	while (getline(cin, buf) && buf != "###") {
		in.push_back(buf);
	}
	sort(in.begin(), in.end());
	in.push_back("###");

	string ts, cur_word = " ";
	vector<string> words;
	int index = 0;
	int cnt = 0;

	for (int i = 0; i < in.size(); i++) {
		stringstream ss(in[i]);
		ss >> ts;
		if (ts != cur_word && cur_word != " ") {
			if (dict[cur_word] == 0) {
				dict[cur_word] = ++index;
				syn[index].push_back(cur_word);
			}
			sort(words.begin(), words.end());
			if (words.size() > 0) {
				int repeat = 1;
				for (int j = 1; j < words.size(); j++) {
					if (words[j-1] == words[j]) {
						repeat++;
					} else {
						if (repeat >= cnt && words[j-1] != cur_word) {
							syn[index].push_back(words[j-1]);
						}
						repeat = 1;
					}
				}
				if (repeat >= cnt) {
					syn[index].push_back(words[words.size()-1]);
				}
			}
			words.clear();
			cnt = 0;
		}
		cnt++;
		cur_word = ts;
		while (ss >> ts) {
			words.push_back(ts);
		}
	}

	for (int i = 1; i <= index; i++) {
		for (int j = 1; j < syn[i].size(); j++) {
			int p = dict[syn[i][j]];
			if (p > 0 && p != i && check(i, p)) {
				ans[i].push_back(syn[i][j]);
			}
		}
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> ts;
		int p = dict[ts];
		if (p == 0 || ans[p].size() == 0) {
			cout << "No Equivalent Synonym" << endl;
		} else {
			for (int j = 0; j < ans[p].size()-1; j++) {
				cout << ans[p][j] << " ";
			}
			cout << ans[p][ans[p].size()-1];
			cout << endl;
		}
	}
	return 0;
}

