/* HDU 4286 Data Handler
 * 看了别人的解法
 * 双链表模拟题：直接用双向链表模拟，因为不能在Reverse的时候真的Reverse，所以只能用特殊的变量判断了
 * */
#include <cstdio>
#include <cstring>

struct Node {
	int v;
	int n1, n2;
} nd[1000000+5];

template <class T>
int scan_i(T &x) {
	int ch;
	bool ne = false;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9') && ch != '-') ;
	if (EOF == ch) return EOF;
	if (ch == '-') {
		ne = 1;
		ch = getchar();
	}
	x = 0;
	while ('0' <= ch && ch <= '9') {
		x *= 10;
		x += ch - '0';
		ch = getchar();
	}
	if (ne) x = -x;
	return 1;
}

template <class T>
int print_i(const T &t) {
	T x = t;
	int l = 0, i;
	bool ne = false;
	if (x == (T)0) {
		putchar('0');
		l = 1;
	} else {
		if (x < 0) {
			putchar('-');
			x = -x;
			ne = true;
		}
		char buf[32];
		while (x > 0) {
			buf[l++] = '0' + x % 10;
			x /= 10;
		}
		for (i = l-1; i >= 0; --i) putchar(buf[i]);
	}
	return ne? l+1 : l;
}

int main() {
	int runs;
	//scanf("%d", &runs);
	scan_i(runs);
	while (runs--) {
		int n, l, r, fl, fr, m, nnd;
		//scanf("%d", &n);
		scan_i(n);
		for (int i = 1; i <= n; ++i) {
			//scanf("%d", &nd[i].v);
			scan_i(nd[i].v);
			nd[i].n1 = i - 1;
			nd[i].n2 = i + 1;
		}
		nd[0].n2 = 1;
		nd[n+1].n1 = n;
		nnd = n+1;
		//scanf("%d%d", &l, &r); 
		scan_i(l);
		scan_i(r);
		/* [L,R]区间，其中[FL,FR]包含[L,R]，FL FR用来确定节点的n1和n2表示哪个方向的变量 */
		fl = l - 1;
		fr = r + 1;
		scanf("%d", &m);
		while (m--) {
			char ch, cmd[31];
			scanf("%s", cmd);
			if (cmd[0] == 'M') { /* Move */
				ch = cmd[4];
				scanf("%s", cmd);
				if (ch == 'L') { /* Left */
					if (cmd[0] == 'L') { /* 左移L的时候，FL是观察点，不同的移动方式，观察点不同 */
						if (nd[fl].n2 == l) {
							l = fl;
							fl = nd[fl].n1;
						} else {
							l = fl;
							fl = nd[fl].n2;
						}
					} else {
						if (nd[r].n2 == fr) {
							fr = r;
							r = nd[r].n1;
						} else {
							fr = r;
							r = nd[r].n2;
						}
					}
				} else { /* Right */
					if (cmd[0] == 'L') {
						if (nd[l].n1 == fl) {
							fl = l;
							l = nd[l].n2;
						} else {
							fl = l;
							l = nd[l].n1;
						}
					} else {
						if (nd[fr].n1 == r) {
							r = fr;
							fr = nd[fr].n2;
						} else {
							r = fr;
							fr = nd[fr].n1;
						}
					}
				}
			} else if (cmd[0] == 'I') { /* Insert */
				++nnd;
			//	scanf("%s%d", cmd, &nd[nnd].v);
				scanf("%s", cmd);
				scan_i(nd[nnd].v);
				if (cmd[0] == 'L') {
					nd[nnd].n1 = fl;
					nd[nnd].n2 = l;
					if (nd[fl].n2 == l) {
						nd[fl].n2 = nnd;
					} else {
						nd[fl].n1 = nnd;
					}
					if (nd[l].n1 == fl) {
						nd[l].n1 = nnd;
					} else {
						nd[l].n2 = nnd;
					}
					l = nnd;
				} else {
					nd[nnd].n1 = r;
					nd[nnd].n2 = fr;
					if (nd[fr].n1 == r) {
						nd[fr].n1 = nnd;
					} else {
						nd[fr].n2 = nnd;
					}
					if (nd[r].n2 == fr) {
						nd[r].n2 = nnd;
					} else {
						nd[r].n1 = nnd;
					}
					r = nnd;
				}
			} else if (cmd[0] == 'D') { /* Delete */
				scanf("%s", cmd);
				int nxt;
				if (cmd[0] == 'L') {
					if (nd[l].n1 == fl) {
						nxt = nd[l].n2;
					} else {
						nxt = nd[l].n1;
					}
					if (nd[fl].n2 == l) {
						nd[fl].n2 = nxt;
					} else {
						nd[fl].n1 = nxt;
					}
					if (nd[nxt].n1 == l) {
						nd[nxt].n1 = fl;
					} else {
						nd[nxt].n2 = fl;
					}
					l = nxt;
				} else {
					if (nd[r].n2 == fr) {
						nxt = nd[r].n1;
					} else {
						nxt = nd[r].n2;
					}
					if (nd[fr].n1 == r) {
						nd[fr].n1 = nxt;
					} else {
						nd[fr].n2 = nxt;
					}
					if (nd[nxt].n2 == r) {
						nd[nxt].n2 = fr;
					} else {
						nd[nxt].n1 = fr;
					}
					r = nxt;
				}
			} else if (cmd[0] == 'R') { /* Reverse */
				if (nd[fl].n2 == l) {
					nd[fl].n2 = r;
				} else {
					nd[fl].n1 = r;
				}
				if (nd[fr].n1 == r) {
					nd[fr].n1 = l;
				} else {
					nd[fr].n2 = l;
				}
				if (nd[l].n1 == fl) {
					nd[l].n1 = fr;
				} else {
					nd[l].n2 = fr;
				}
				if (nd[r].n2 == fr) {
					nd[r].n2 = fl;
				} else {
					nd[r].n1 = fl;
				}
				l ^= r;
				r ^= l;
				l ^= r;
			} else {
				for(;;);
			}
		}
		
		/* Ouptut Answer */
		fl = 0;
		l = nd[0].n2;
		bool out = false;
		while (l != n+1) {
			/*
			printf("%s%d", out ? " " : "", nd[l].v);
			if (!out) out = true;
			*/
			if (out) {
				putchar(' ');
			} else out = true;
			print_i(nd[l].v);
			if (nd[l].n1 == fl) {
				fl = l;
				l = nd[l].n2;
			} else {
				fl = l;
				l = nd[l].n1;
			}
		}
		puts("");
	}
	return 0;
}
