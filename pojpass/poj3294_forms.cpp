#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 105;
const int MAXM = 100005 + MAXN;
const int LOG_MAXM = 20;

int sa[MAXM], rank[MAXM], height[MAXM];
int X[MAXM], Y[MAXM], buc[MAXM];

bool cmp(int *r, int n, int a, int b, int l) {
    return a+l < n && b+l < n && r[a]==r[b] && r[a+l]==r[b+l];
}

void suffix(int *r, int n, int m)
{
    int i, l, p, *x=X, *y=Y, *t;
    for (i = 0; i < m; ++i) buc[i] = 0;
    for (i = 0; i < n; ++i) buc[x[i]=r[i]]++;
    for (i = 1; i < m; ++i) buc[i] += buc[i-1];
    for (i = n-1; i >= 0; --i) sa[ --buc[x[i]] ] = i;
    for (l=1, p=1; p < n; m=p, l<<=1) {
        for (p=0, i=n-l; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= l) y[p++] = sa[i] - l;
        for (i = 0; i < m; ++i) buc[i] = 0;
        for (i = 0; i < n; ++i) buc[x[y[i]]]++;
        for (i = 1; i < m; ++i) buc[i] += buc[i-1];
        for (i = n-1; i >= 0; --i) sa[ --buc[x[y[i]]] ] = y[i];
        for (t=x, x=y, y=t, x[sa[0]]=0, i=1, p=1; i < n; ++i) {
            x[sa[i]] = cmp(y, n, sa[i-1], sa[i], l) ? p-1 : p++;
        }
    }
    int j, k = 0;
    for (i = 0; i < n; ++i) rank[sa[i]] = i;
    for (i = 0; i < n-1; height[rank[i++]] = k) {
        for (k?--k:0, j=sa[rank[i]-1]; r[j+k]==r[i+k]; ++k) ;
    }
}

int best[MAXM][LOG_MAXM];
void init_rmq(int n)
{
    for (int i = 1; i <= n; ++i) best[i][0] = height[i];
}

char str[MAXN][1005];
int len[MAXN];
bool vis[MAXN];
int num[MAXM], id[MAXM];

int main()
{
    int nCase = 0;
    int n;
    while (EOF != scanf("%d", &n) && n) {
        int l = 0, max_len = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", str[i]);
            int ls = 0;
            for (; str[i][ls]; ++ls) {
                num[l] = str[i][ls];
                id[l++] = i;
            }
            num[l] = 127+i;
            id[l++] = i;
            if (max_len < ls) max_len = ls;
        }
        num[l] = 0;
        id[l] = n;
        suffix(num, l+1, 256);
        int left = 0, right = max_len, half = n / 2 + 1;
        while (left < right) {
            int m = (right - left) / 2 + left + 1;
            int i = 1;
            int len = max_len;
            bool can = false;
            for (int j = i + 1; i < l; ++j) {
                len = min(len, height[j]);
                if (j <= l && len >= m) {
                } else if (j - i < half) {
                    len = max_len;
                    i = j;
                } else {
                    memset(vis, 0, sizeof(vis));
                    int cnt = 0;
                    for (int k = i; k < j; ++k) {
                        if (!vis[id[sa[k]]]) {
                            vis[id[sa[k]]] = true;
                            ++cnt;
                        }
                    }
                    if (cnt >= half) {
                        can = true;
                        break;
                    }
                    i = j;
                    len = max_len;
                }
            }
            if (can) left = m;
            else right = m - 1;
        }

        if (nCase) puts("");
        ++nCase;
        if (left == 0) puts("?");
        else {
            int i = 1;
            int len = max_len;
            for (int j = i + 1; i < l; ++j) {
                len = min(len, height[j]);
                if (j <= l && len >= left) {
                } else if (j - i < half) {
                    len = max_len;
                    i = j;
                } else {
                    memset(vis, 0, sizeof(vis));
                    int cnt = 0;
                    for (int k = i; k < j; ++k) {
                        if (!vis[id[sa[k]]]) {
                            vis[id[sa[k]]] = true;
                            ++cnt;
                        }
                    }
                    if (cnt >= half) {
                        for (int k = 0; k < left; ++k) {
                            printf("%c", num[sa[i]+k]);
                        }
                        puts("");
                    }
                    i = j;
                    len = max_len;
                }
            }
        }
    }
    return 0;
}
