#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 2*65535 + 10;

int cover[MAXN<<2];
int c_xor[MAXN<<2];
bool hash[MAXN+1];

void Xor(int rt)
{
    if (cover[rt] != -1) cover[rt] ^= 1;
    else c_xor[rt] ^= 1;
}

void PushDown(int rt)
{
    if (cover[rt] != -1) {
        cover[rt<<1] = cover[rt<<1|1] = cover[rt];
        c_xor[rt<<1] = c_xor[rt<<1|1] = 0;
        cover[rt] = -1;
    }
    if (c_xor[rt]) {
        Xor(rt<<1);
        Xor(rt<<1|1);
        c_xor[rt] = 0;
    }
}

void update(int rt, int L, int R, int l, int r, char op)
{
    if (l <= L && R <= r) {
        if ('U' == op) {
            cover[rt] = 1;
            c_xor[rt] = 0;
        } else if ('D' == op) {
            cover[rt] = 0;
            c_xor[rt] = 0;
        } else if ('C' == op || 'S' == op) {
            Xor(rt);
        }
        return;
    }
    PushDown(rt);
    int m = (L + R) >> 1;
    if (l <= m) update(rt<<1, L, m, l, r, op);
    else if ('I' == op || 'C' == op) {
        cover[rt<<1] = c_xor[rt<<1] = 0;
    }
    if (m < r) update(rt<<1|1, m+1, R, l, r, op);
    else if ('I' == op || 'C' == op) {
        cover[rt<<1|1] = c_xor[rt<<1|1] = 0;
    }
}

void query(int rt, int L, int R)
{
    if (cover[rt] == 0) return;
    else if (cover[rt] == 1) {
        for (int i = L; i <= R; ++i) hash[i] = true;
        return;
    }
    if (L == R) return;
    PushDown(rt);
    int m = (L + R) >> 1;
    query(rt<<1, L, m);
    query(rt<<1|1, m+1, R);
}

int main()
{
    //freopen("p.in", "r", stdin);
    cover[1] = c_xor[1] = 0;
    char op, lb, rb;
    int l, r;
    while (EOF != scanf("%c %c%d,%d%c\n", &op, &lb, &l, &r, &rb)) {
        l <<= 1, r <<= 1;
        if (lb == '(') ++l;
        if (rb == ')') --r;
        if (l > r) {
            if (op == 'I' || op == 'C') {
                cover[1] = c_xor[1] = 0;
            }
        } else {
            update(1, 0, MAXN, l, r, op);
        }
    }
    memset(hash, 0, sizeof(hash));
    query(1, 0, MAXN);
    int s = -1, e;
    bool flag = false;
    for (int i = 0; i <= MAXN; ++i) {
        if (hash[i]) {
            if (s == -1) s = i;
            e = i;
        } else if (s != -1) {
            if (flag) putchar(' ');
            flag = true;
            printf("%c%d,%d%c", s&1 ? '(' : '[', s>>1, (e+1)>>1, e&1 ? ')' : ']');
            s = -1;
        }
    }
    if (!flag) printf("empty set");
    puts("");
	return 0;
}

