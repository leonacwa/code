/* 后缀数组 + 单调栈，单调栈需要压缩
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long llong;

const int MAXM = 2*100000 + 10;

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

char stra[MAXM], strb[MAXM];
int num[MAXM];
int st[MAXM];
int cnt[MAXM];

llong cal(int n, int k, int m, bool f)
{
    int top = -1;
    llong res = 0, sum = 0;
    for (int i = 2; i < n; ++i) {
        if (height[i] < k) {
            top = -1;
            sum = 0;
        } else {
            int count = 0;
            for (int j = top; j >= 0; --j) {
                if (st[j] >= height[i]) {
                    sum -= (st[j] - height[i]) * cnt[j];
                    st[j] = height[i];
                    count += cnt[j];
                } else {
                    if (j+1 < top) { //  压缩单调栈
                        top = j + 1;
                        st[top] = height[i];
                        cnt[top] = count;
                    }
                    break;
                }
            }
            if (f) {
                if (sa[i-1] < m) {
                    if (st[top] != height[i]) {
                        st[++top] = height[i];
                        cnt[top] = 1;
                    } else
                        cnt[top]++;
                    sum += height[i] - k + 1;
                }
                if (sa[i] > m) {
                    res += sum;
                }
            } else {
                if (sa[i-1] > m) {
                    if (st[top] != height[i]) {
                        st[++top] = height[i];
                        cnt[top] = 1;
                    } else
                        cnt[top]++;
                    sum += height[i] - k + 1;
                }
                if (sa[i] < m) {
                    res += sum;
                }
            }
        }
    }
    return res;
}

int main()
{
    int k;
    while (EOF != scanf("%d", &k) && k) {
        scanf("%s%s", stra, strb);
        int la, lb, l = 0;
        for (la = 0; stra[la]; ++la) num[l++] = stra[la];
        num[l++] = 127;
        for (lb = 0; strb[lb]; ++lb) num[l++] = strb[lb];
        num[l] = 0;
        suffix(num, l+1, 256);
        llong ans = cal(l, k, la, true) + cal(l, k, la, false);
        //printf("%lld\n", ans);
        printf("%I64d\n", ans);
    }
	return 0;
}

